#include <iostream>
#include <string>
#include <cmath>

class RSA {

    public:
        RSA(int e, int n, int m);
        void calculate();
        
        int getP() const { return p; }
        int getQ() const { return q; }
        int getPhi() const { return phi; }
        int getD() const { return d; }

    private:
        int d, e, n, m, p, q, phi;

        void calculatePQ();
        bool isValidE() const;
        bool isPrime(int) const;
        int gcd(int, int) const;
        int extendedEuclid(int, int, int&, int&) const;
};

RSA::RSA(int e, int n, int m) {
    this->e = e;
    this->n = n;
    this->m = m;
}

void RSA::calculate() {
    calculatePQ();
    this->phi = (p - 1) * (q - 1);

    if (!isValidE())
        throw std::runtime_error("Invalid e!");

    int A, B;
    extendedEuclid(e, phi, A, B);
    d = (A % phi + phi) % phi;
}

bool RSA::isPrime(int x) const {
    if (x <= 1) return false;

    for (int i = 2; i <= sqrt(x); i++)
        if (x % i == 0)
            return false;

    return true;
}

int RSA::extendedEuclid(int a, int b, int& alpha, int& beta) const {
    if (b == 0) {
        alpha = 1;
        beta = 0;
        return a;
    }

    int A, B;
    int gcd = extendedEuclid(b, a%b, A, B);
    alpha = B;
    beta = A - a/b*B;
    
    return gcd;
}

int RSA::gcd(int a, int b) const {
    return b == 0 ? a : gcd(b, a % b);
}

bool RSA::isValidE() const {
    return gcd(e, phi) == 1;
}

void RSA::calculatePQ() {
    p = 2;
    while (p <= sqrt(n)) {
        if (n%p==0) {
            q = n/p;
            if (p == q || !isPrime(q))
                throw std::runtime_error("Invalid Key!");

            return;
        }
        p++;
    }
    throw std::runtime_error("Invalid Key!");
}

