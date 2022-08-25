class Entier {
private:
    int* pEntier;

public:
    Entier() { //Constructeur par defaut
        pEntier = new int(0);
    }

    Entier(int entier) {
        pEntier = new int(entier);
    }

    Entier(const Entier& entier) { //Constructeur de copie
        pEntier = new int(*entier.pEntier);
    }

    ~Entier() {
        
    }
};

/*
Pointeurs
*************

    Déclaration:
        int* pEntier;   Pointeur
        int  entier;    Valeur normal
        int& rEntier;   Référence

    Implémentation:
        pEntier = &entier;  Permet d'obtenir l'adresse mémoire plutot que la valeur
        entier  = *pEntier; Permet d'obtenir la valeur ce situent a un adresse en memoire

*/


int main(int argc, char* argv[]){
    return 0;
    Entier entier1(42);
    Entier entier2(entier1); //Entier entier2 = entier1
}