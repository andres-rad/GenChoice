#include <bits/stdc++.h>
#include "gen.cpp"
#define debug(v) cerr<< #v << ": " << v << endl
using namespace std;


enum Order {LT, EQ, GT};

Order evaluar( vector<unsigned int>& v, GenChoice& gen, unsigned int left, unsigned int right, unsigned int target){
    unsigned int guess = gen.guess(left, right);
    if (target < v[guess]){
        return LT;
    } else if (v[guess] == target){
        return EQ;
    } else {
        return GT;
    }
}

unsigned int cantPasos( vector<unsigned int>& v, GenChoice& gen, unsigned int target){
    
    unsigned int n = 0;
    unsigned int left = 0, right = v.size();
    unsigned int guess = 0;
    
    Order clue;
    
    do {
        clue = evaluar(v, gen, left, right, target);
        guess = gen.guess(left, right);
        
        if(clue == LT){
            right = guess;
        } else if(clue == GT){
            left = guess + 1;
        }

        n++;

    } while(clue != EQ and n < v.size());

    return n;
}

unsigned int fitness(vector<unsigned int>& v,  GenChoice& gen){
    unsigned int suma = 0;
    for(unsigned int target = 0; target < gen.size(); target++)
        suma += cantPasos(v, gen, target);

    return suma;
}

vector<GenChoice> generarPoblacion(unsigned int range, unsigned int pop){
    vector<GenChoice> poblacion;
    
    for(unsigned int i = 0; i < pop; i++)
        poblacion.push_back(GenChoice(range));
    
    return poblacion;
}

void crossOver(GenChoice& gen_modif, GenChoice g2, unsigned int mutation){
    random_device rd;
    mt19937 mt(rd());
    uniform_int_distribution<unsigned int> mut(0, 100);
    uniform_int_distribution<unsigned int> dist(0, gen_modif.size()-1);
    
    for(int i = 0; i < gen_modif.size(); i++){
        for(int j = i+1; j <= gen_modif.size(); j++){
            srand(time(NULL));
            if(mut(mt) <= mutation){
                unsigned int new_guess = (gen_modif.guess(i, j) + g2.guess(i, j)) / 2;
                gen_modif.modify_guess(i, j, new_guess);
            } else {
                gen_modif.modify_guess(i, j, dist(mt));
            }
        }
    }
}

void avanzarGen(vector<unsigned int>& v, vector<GenChoice>& poblacion){
    random_device rd;
    mt19937 mt(rd());
    
    sort(poblacion.begin(), poblacion.end(), [&v](GenChoice g1, GenChoice g2) { return fitness(v, g1) <= fitness(v, g2); });
    unsigned int podar = (poblacion.size() + 1) / 2;
    
    uniform_int_distribution<unsigned int> choose(0, podar - 1);
        
    for(int i = podar; i < poblacion.size(); i++){
        unsigned int companion =  choose(mt);
        crossOver(poblacion[i], poblacion[companion], 95);
    }
}

int main(){
    vector<unsigned int> s;
    unsigned int poblacion_size = 50;
    unsigned int gen_range = 100;
    unsigned int n_generaciones = 100;
    
    for(unsigned int i = 0; i < gen_range; i++){
        s.push_back(i);
    }

    vector<GenChoice> poblacion = generarPoblacion(gen_range, poblacion_size);
    vector<GenChoice> best;

    for(int generacion = 0; generacion < n_generaciones; generacion++){
        avanzarGen(s, poblacion);
        best.push_back(poblacion[0]);
        cout << (float)fitness(s, poblacion[0]) << endl;
    }
    
    cout << best[best.size()-1] << endl;

    return 0;
}