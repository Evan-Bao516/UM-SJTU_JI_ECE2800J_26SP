#include "h3.h"

#include <iostream>

void printHelp() {
    std::cout << "Encrypt or decrypt a message using the Polybius Square cipher.\n"
              << "Usage: ./h3 <command> [outputMode]\n"
              << "Commands:\n"
              << "\t-e, --encrypt\tEncrypt a message\n"
              << "\t-d, --decrypt\tDecrypt a message\n"
              << "Output modes:\n"
              << "\t-c, --compact\tProcess the message without spaces\n"
              << "\t-s, --sparse\tProcess the message with spaces\n";
}
