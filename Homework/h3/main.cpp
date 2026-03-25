#include <iostream>
#include <string>

#include "h3.h"

using std::cout;
using std::string;

namespace {
struct Config {
    bool isEncrypt = false;
    bool isDecrypt = false;
    bool isSparse = false;
};

string EncryptLetter(char letter) {
    if (letter == ' ') {
        return "000";
    }
    if (letter == 'J') {
        return "100";
    }
    if (letter == 'j') {
        return "200";
    }
    for (int row = 0; row < kGridSize; ++row) {
        for (int col = 0; col < kGridSize; ++col) {
            if (kUppercaseSquare[row][col] == letter) {
                return "1" + std::to_string(row + 1) + std::to_string(col + 1);
            }
            if (kLowercaseSquare[row][col] == letter) {
                return "2" + std::to_string(row + 1) + std::to_string(col + 1);
            }
        }
    }
    return "";
}

char DecryptBlock(const string& block) {
    if (block == "000") {
        return ' ';
    }
    if (block == "100") {
        return 'J';
    }
    if (block == "200") {
        return 'j';
    }
    const int row = block.at(1) - '1';
    const int col = block.at(2) - '1';
    if (block.at(0) == '1') {
        return kUppercaseSquare[row][col];
    }
    return kLowercaseSquare[row][col];
}

bool ParseArgs(int argc, const char* argv[], Config& config) {
    if (argc == 1) {
        cout << "No option!\n";
        return false;
    }
    string cmd = argv[1];
    config.isEncrypt = (cmd == "-e" || cmd == "--encrypt");
    config.isDecrypt = (cmd == "-d" || cmd == "--decrypt");
    const bool isHelp = (cmd == "-h" || cmd == "--help");
    if (argc > 3 || (isHelp && argc > 2)) {
        cout << "Too many options!\n";
        return false;
    }
    if ((!config.isEncrypt) && (!config.isDecrypt) && (!isHelp)) {
        cout << "Invalid option!\n";
        return false;
    }
    if (isHelp) {
        printHelp();
        return false;
    }
    if (argc == 3) {
        string mode = argv[2];
        if (mode == "-s" || mode == "--sparse") {
            config.isSparse = true;
        } else if (mode == "-c" || mode == "--compact") {
            config.isSparse = false;
        } else {
            cout << "Invalid option!\n";
            return false;
        }
    }
    return true;
}

string ProcessEncrypt(const string& input, bool isSparse) {
    string result;
    for (size_t i = 0; i < input.length(); ++i) {
        result += EncryptLetter(input.at(i));
        if (isSparse && i != input.length() - 1) {
            result += " ";
        }
    }
    return result;
}

string ProcessDecrypt(const string& input) {
    string result;
    string currentBlock;
    for (size_t i = 0; i < input.length(); ++i) {
        if (input.at(i) != ' ') {
            currentBlock += input.at(i);
        }
        if (currentBlock.length() == 3) {
            result += DecryptBlock(currentBlock);
            currentBlock = "";
        }
    }
    return result;
}
}  // namespace

int main(int argc, const char* argv[]) {
    try {
        Config config;
        if (!ParseArgs(argc, argv, config)) {
            return 0;
        }
        string input;
        getline(std::cin, input);
        const size_t start = input.find_first_not_of(' ');
        if (start == string::npos) {
            cout << "\n";
            return 0;
        }
        const size_t end = input.find_last_not_of(' ');
        input = input.substr(start, end - start + 1);
        string result;
        if (config.isEncrypt) {
            result = ProcessEncrypt(input, config.isSparse);
        } else if (config.isDecrypt) {
            result = ProcessDecrypt(input);
        }
        cout << result << '\n';
    } catch (...) {
        return 1;
    }
    return 0;
}
