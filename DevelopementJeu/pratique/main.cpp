#include <iostream>

using namespace std;
/*

Classe virtuel

class ClasseA {
public:
    virtual void afficher() { cout << "Afficher de ClasseA" << endl;}
};

class ClasseB : public ClasseA {
public:
    void afficher() { cout << "Afficher de ClasseB" << endl;}
};

class ClasseC : public ClasseB {
public:
    void afficher() { cout << "Afficher de ClasseC" << endl;}
};
*/

/*
Classe abstraite (Virtuel pure (obliger d'avoir une methode isValid))

class Piece{
public:
    virtual bool isValid() = 0;
};

class Pawn : public Piece{
public:
    bool isValid() {
        return true;
    }
};
*/

int main(int argc, char* argv[]){
    /*ClasseA* instanceA = new ClasseA();
    ClasseA* instanceB = new ClasseB();
    ClasseA* instanceC = new ClasseC(); 

    instanceA->afficher();
    instanceB->afficher();
    instanceC->afficher();*/

    return 0;
}
