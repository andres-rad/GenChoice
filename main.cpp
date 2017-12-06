#include <bits/stdc++.h>
#include "gen.cpp"
#define debug(v) cerr<< #v << ": " << v << endl
using namespace std;


enum Order {LT, EQ, GT};

Order evaluar(const vector<unsigned int>& v, GenChoice& gen, unsigned int left, unsigned int right, unsigned int target){
    unsigned int guess = gen.guess(left, right);
    if (target < v[guess]){
        return LT;
    } else if (v[guess] == target){
        return EQ;
    } else {
        return GT;
    }
}

unsigned int cantPasos(const vector<unsigned int>& v, GenChoice& gen, unsigned int target){
    
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

    } while(clue != EQ);

    return n;
}

float fitness(const vector<unsigned int>& v, const GenChoice& gen){
    float suma = 0;
    for(unsigned int target = 0; target < gen.size(); target++)
        suma += cantPasos(v, gen, target);

    return suma / (float)gen.size();
}

vector<GenChoice> generarPoblacion(unsigned int range, unsigned int pop){
    poblacion = vector<GenChoice>;
    
    for(unsigned int i = 0; i < pop; i++)
        poblacion.push_back(GenChoice(range));
    
    return poblacion;
}

void avanzarGen(const vector<unsigned int>& v, vector<GenChoice>& poblacion, unsigned int target){
    sort(v.begin(), v.end(), [](GenChoice g1, GenChoice g2) { return fitness(v, g1) >= fitness(v, g2) });

}

int main(){
    vector<int> s;
    
    for(int i = 0; i < 100; i++){
        s.push_back(i);
    }

    GenChoice g = GenChoice(100);
    cout << g << endl;
    return 0;
}