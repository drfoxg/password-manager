#pragma once
#include <string>
#include <iterator>
#include <vector>
#include <array>
#include <iostream>
#include <fstream>
#include <random>

#include "Core.h"


using namespace std;

class CryptoFileTemplate
{
private:
    const size_t kMaxFiles = 5;

    size_t square_side;
    string verification_phrase;
    vector<string> square_list;
    vector<string> file_list;
    vector<string> passwd_list;

public:
    CryptoFileTemplate(const size_t square_side);

    void create_phrase(const string& square);
    void generate_file(const string& verification_phrase = "");
    void set_verification_phrase(const string& verification_phrase);
    void set_square_side(const size_t square_side);
    void set_passwd_list(const vector<string>& passwd_list);

    const string get_square(const size_t index = 0);

private:
    string exclude(const string &passwd, const string &square);
    const vector<string> explode(const string& s, const char& c);

    const string generate_dumb_line(const vector<string>& phrase_list, Core& core);
    const vector<string> create_file_names(const size_t max_files);
    
};

