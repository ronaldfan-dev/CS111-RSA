#ifndef RSA_H
#define RSA_H

class RSA {
    public:
        RSA(long e, long n, long m);
        void calculate();
        
        long getP() const { return p; }
        long getQ() const { return q; }
        long getPhi() const { return phi; }
        long getD() const { return d; }
        long decode(long) const;
        char toEnglish(long) const;

    private:
        long d, e, n, m, p, q, phi;

        void calculatePQ();
        bool isValidE() const;
        bool isPrime(long) const;
        long gcd(long, long) const;
        long extendedEuclid(long, long, long&, long&) const;
};

#endif