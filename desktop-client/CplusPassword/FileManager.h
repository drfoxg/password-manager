#pragma once

#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <filesystem>

#include "Core.h"

using namespace std;

class FileManager
{
private:
    vector<string> file_list;
    vector<string> menu;
    vector<string> content;

public:
    const vector<string>& get_file_list(const string &directory);
    const string open(const size_t index);
    const vector<string>& get_conten();

};

