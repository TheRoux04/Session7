
class ClasseBase {
private:
    int donneeA;

protected:
    int donneeB;

public:
    ClasseBase(int donneeA, int donneeB){
        this->donneeA = donneeA;
        this->donneeB = donneeB;
    }
};

class AutreClasseBase {
protected:
    int donneeD;
};

class ClasseDerivee : public ClasseBase, public AutreClasseBase {
private:
    int donneeC;
public:
    ClasseDerivee(int donneeA, int donneeB, int donneeC): ClasseBase(donneeA, donneeB){
        this->donneeC = donneeC;
    }
};



int main(int argc, char* argv[]){
    ClasseDerivee ClasseDerivee(1, 2, 3);
    return 0;
}