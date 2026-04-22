#include "RSA.cpp"

int main() {

    int e, n, m;
    std::string cipherText;

    std::cout << "Enter your e, n, and m: " << std::endl;
    std::getline(std::cin, e);
    std::getline(std::cin, n);
    std::getline(std::cin, m);
    std::cout << "Input the ciphertext: " << std::endl;
    std::getline(std::cin, cipherText);

    RSA decryption = RSA(e, n, m);

    if (!decryption.validateKey()) {
        std::cout << "Public key is not valid!" << std::endl;
        return 0;
    }

    











    return 0;
}