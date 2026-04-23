#include "RSA.h"
#include <limits>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>

int main() {

    long e, n, m;
    std::string encoded;

    std::cin >> e >> n;
    std::cin >> m;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::getline(std::cin, encoded);
    std::cout << std::endl;

    RSA rsa(e, n, m);
    try {
        rsa.calculate();
    } catch (const std::exception e) {
        std::cout << "Public key is not valid!";
        return 1;
    }

    std::cout << rsa.getP() << " " << rsa.getQ() << " " << rsa.getPhi() << " " << rsa.getD() << std::endl;

    std::vector<long> decodedlongs;   
    std::istringstream iss(encoded);
    long num;

    while (iss >> num) {
        decodedlongs.push_back(rsa.decode(num));
    }

    for (long x : decodedlongs) {
        std::cout << x << " ";
    }

    std::cout << std::endl;

    for (long x : decodedlongs) {
        std::cout << rsa.toEnglish(x);
    }

    return 0;
}