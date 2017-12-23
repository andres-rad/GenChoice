#include <algorithm>
#include <stdlib.h>
#include <time.h>
#include <map>
#include <utility>
#define debug(v) cerr<< #v << ": " << v << endl

using namespace std;

class GenChoice{
    /* Objeto que elige una posicion dentro de un rango de valores.
       La idea va a ser una heurística genética sobre estos objetos para ver si
       dado un rango de valores ordenados codifican una busqueda binaria.
    */
    public:
        GenChoice(unsigned int size);
        unsigned int guess(unsigned int left,unsigned int right);
        void modify_guess(unsigned int left, unsigned int right, unsigned int choice);
        unsigned int size();
    private:
        unsigned int n;
        map<pair<unsigned int, unsigned int>, unsigned int> eleccion;

};

GenChoice::GenChoice(unsigned int size){
    random_device rd;
    mt19937 mt(rd());
    uniform_int_distribution<unsigned int> dist(0, size-1);

    n = size;

    for(unsigned int i = 0; i <= size; i++){
        for(unsigned int j = i; j <= size; j++){
            if(i == j){
                eleccion[make_pair(i, j)] = i;
            } else {
                eleccion[make_pair(i, j)] = dist(mt);
            }

        }
    }
}


unsigned int GenChoice::guess(unsigned int left, unsigned int right){
    /* Dado un rango [left, right) devuelve el valor que elegido.
    */
    if(right > n || left > right)
        return -1;
    return eleccion[make_pair(left, right)];
}

void GenChoice::modify_guess(unsigned int left, unsigned int right, unsigned int choice){
    /* Permite modificar la elección que realiza para un rango válido
    */
    if(right >= n || left > right || choice < left || choice > right)
        return;
    eleccion[make_pair(left, right)] = choice;
    return;
}

unsigned int GenChoice::size(){
    return n;
}

ostream& operator<<(ostream& out,  GenChoice& g){

    out << g.size() << endl;

    for(int i = 0; i <= g.size(); i++){
        for(int j = i; j <= g.size()-1; j++)
            out << g.guess(i, j) << " ";  
        out << g.guess(g.size(), g.size()) << endl;
    }

    return out;
}

