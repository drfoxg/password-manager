#include "Core.h"

using namespace std;

Core::Core(const string& square, const size_t square_side) {

    this->square = square;
    this->square_side = square_side;

}

const size_t Core::get_square_side() {
    return square_side;
}

const int Core::strchr_get_index(const string& square, const char msg) {

    size_t result = -1;

    for (size_t i = 0; i < square.length(); i++) {

        if (square[i] == msg) {
            result = i;
        }
    }

    return result;
}

string Core::encrypt(const string& msg) {    
    return encrypt(msg, square, square_side);
}

string Core::decrypt(const string& msg) {

    return decrypt(msg, square, square_side);   
}

string Core::encrypt(const string& msg, const string& square, const size_t square_side) {

    size_t index;

    string encrypted(msg);

    for (size_t i = 0; i < msg.length(); i++) {

        if (msg[i] == '>') {
            continue;
        }

        index = strchr_get_index(square, msg[i]);
        encrypted[i] = square[(index + square_side) % square.length()];

    }

    return encrypted;
}

string Core::decrypt(const string& msg, const string& square, const size_t square_side) {

    int coord;
    size_t index;
    string decrypted(msg);

    for (size_t i = 0; i < msg.length(); i++) {

        if (msg[i] == '>') {
            continue;
        }

        /* Координата может получиться отрицательной. Это значит, что нужный
           нам символ находится в конце массива. */
        coord = strchr_get_index(square, msg[i]) - square_side;
        index = (coord >= 0) ? coord : square.length() + coord;
        decrypted[i] = square[index];

    }

    return decrypted;
}

std::vector<std::string> Core::split(const std::string& str, std::string_view pattern) {
    const auto r = std::regex(pattern.data());

    return std::vector<std::string>{
        std::sregex_token_iterator(cbegin(str), cend(str), r, -1), std::sregex_token_iterator()
    };
}
