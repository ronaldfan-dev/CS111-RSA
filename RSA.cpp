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
        int decode(int) const;
        std::string toEnglish(std::string, int) const;

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

int RSA::decode(int cipher) const {
    int exp = d;
    int result = 1;
    while (exp > 0) {
        if (exp % 2 == 1) { // Odd
            result *= cipher;
            result = result % n; // Cut down result
            exp--;
        }
        else {
            exp /= 2; // Half exponent
            cipher *= cipher; // Square
            cipher = cipher % n; // Evaluate mod
        }
    }
    return result;
}

std::string RSA::toEnglish(std::string cipher, int messageLength) const {
    std::string characters[31] = {"A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "M", "N", "O", "P", "Q", "R", "S", "T", "U", "V", "W", "X", "Y", "Z", " ", "\"", ",", "." , "'"};
    std::string finalMessage;
    int cipherInt = std::stoi(cipher);
    cipherInt = cipherInt % 31;
    int count = 0;
    while (count < messageLength) {
        for (int i = 7; i < 37; i++) {
            if (i = cipherInt)
            finalMessage.append(characters[i]);
        }
        count++;
    }
    return finalMessage;
}