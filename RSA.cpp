#include <iostream>
#include <string>
#include <cmath>

class RSA {

    public:
        bool validateKey();
        void findPQ(int n);
        int calculateD(int e, int n);
        int decrypt(int num);
        std::string toEnglish(int decryptedNum);
        RSA(int e, int n, int m);
    private:
        int p, q, PHI, e, n, d;
        std::string message;
};

RSA::RSA(int e, int n, int m) {
    findPQ(n);
    this->e = e;
    this->n = n;
    this->PHI = (p - 1) * (q - 1);
}

void RSA::findPQ(int n) {
    int _p = -1;
    int _q = -1;
    for (int i = 2; i < sqrt(n); i++) { // Loop through all numbers from 2 to sqrt(n)
        if (i%n == 0) { // Found factors
            _p = i;
            _q = n / i;
            break;
        }
    }
    this->p = _p;
    this->q = _q;
}

bool RSA::validateKey() {
    if (p == -1 || q == -1 || p == q)
        return false;
    else {
        for (int i = 2; i < sqrt(p); i++) {
            if(i%p == 0) 
                return false;
        }
        for (int i = 2; i < sqrt(q); i++) {
            if(i%q == 0)
                return false;
        }
    }
    #TODO need to account for modulus check with PHI
    return true;
}

int RSA::calculateD(int e, int PHI) {
    
}

