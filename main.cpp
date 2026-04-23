#include "RSA.cpp"
#include <limits>

int main() {

    int e, n, m;
    std::string encoded;

    std::cout << "Enter your e, n, and m: " << std::endl;
    std::cin >> e;
    std::cin >> n;
    std::cin >> m;
    std::cout << "Input the ciphertext: " << std::endl;

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

    std::cout << "p = " << rsa.getP() << std::endl;
    std::cout << "q = " << rsa.getQ() << std::endl;
    std::cout << "phi = " << rsa.getPhi() << std::endl;
    std::cout << "d = " << rsa.getD() << std::endl;

    return 0;
}