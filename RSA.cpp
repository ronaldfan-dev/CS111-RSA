#include "RSA.h"
#include <iostream>
#include <string>
#include <cmath>

RSA::RSA(long e, long n, long m) {
    this->e = e;
    this->n = n;
    this->m = m;
}

void RSA::calculate() {
    calculatePQ();
    this->phi = (p - 1) * (q - 1);

    if (!isValidE())
        throw std::runtime_error("Invalid e!");

    long A, B;
    extendedEuclid(e, phi, A, B);
    d = (A % phi + phi) % phi;
}

bool RSA::isPrime(long x) const {
    if (x <= 1) return false;

    for (long i = 2; i <= sqrt(x); i++)
        if (x % i == 0)
            return false;

    return true;
}

long RSA::extendedEuclid(long a, long b, long& alpha, long& beta) const {
    if (b == 0) {
        alpha = 1;
        beta = 0;
        return a;
    }

    long A, B;
    long gcd = extendedEuclid(b, a%b, A, B);
    alpha = B;
    beta = A - a/b*B;
    
    return gcd;
}

long RSA::gcd(long a, long b) const {
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

long RSA::decode(long cipher) const {
    long exp = d;
    long result = 1;
    while (exp >= 1) {
        if (exp % 2 == 1) { //Odd
            result *= cipher;
            exp--;
            if (result > n)
                result = result % n; // Cut down result
        }
        else {
            exp /= 2; // Half exponent
            cipher *= cipher; // Square
            cipher = cipher % n; // Evaluate mod
        }
    }
    return result;
}

char RSA::toEnglish(long num) const {
    char characters[31] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', ' ', '"', ',', '.', '\''};
    return characters[num - 7]; // Subtract the offset
}