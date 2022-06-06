// CplusPassword.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iterator>
#include <iostream>
#include <fstream>
#include <string>
#include <string_view>
#include <vector>
#include <regex>
#include <cstdio>

#include <Windows.h>

#include "Addition.h"
#include "Category.h"
#include "Core.h"
#include "Command.h"
#include "CryptoFileTemplate.h"
#include "FileManager.h"
#include "Item.h"

using namespace std;

// нужно ли пересоздать файлы под новые пароли?
bool is_create() {
    return false;
}

int main()
{
    const size_t square_side = 9;

    // Set console code page to UTF-8 so console known how to interpret string data
    SetConsoleOutputCP(CP_UTF8);
    // Enable buffering to prevent VS from chopping up UTF - 8 byte sequences
    setvbuf(stdout, nullptr, _IOFBF, 1000);

    Command command;

    std::string special = ",. -+?!:/&#()@%*^_=";
    std::string digit = "0123456789";
    std::string square_right = "abcdefghijklmnopqrstuvwxyz";
    std::string square_left = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    std::string square_centre(special);

    std::string verification_phrase = "eat some more of these soft French rolls and drink some tea";

    std::string square = square_left + square_centre + square_right + digit;

    Item* password_item = new Item;
    Addition* addtion_item = new Addition;
    Category* category_item = new Category;

    password_item->name = "My lovely password";
    password_item->password = "qwerty";
    addtion_item->login = "root";
    addtion_item->url = "https://fb.com";
    category_item->name = "Common";
    std::string separtor = ">>>";

    std::string input_element = category_item->name + separtor + password_item->name + separtor + password_item->password + separtor + addtion_item->login + separtor + addtion_item->url;

    Core core_test(square, square_side);
    string ecrypt_test = core_test.encrypt(input_element);
    string decript_test = core_test.decrypt(ecrypt_test);
    cout << "Enrypted: " << ecrypt_test << endl;    
    cout << "Decrypted: " << decript_test << endl;
        
    /*
    vector<string> items = split(decript_test, ">>>");
    
    for (auto item : items) {
        std::cout << item << std::endl;
    } 
    */

    CryptoFileTemplate file_template(square_side);
    file_template.set_verification_phrase(verification_phrase);
    
    if (is_create()) {
        vector<string> passwd_list = { "heling", "hingle", "single", "sleigh", "slinge" };
        file_template.set_passwd_list(passwd_list);
        file_template.create_phrase(square);
        file_template.generate_file();
    }  
    
    // получить список файлов с паролями
    FileManager file_manager;
    vector<string> file_list = file_manager.get_file_list(".");
    for (auto list : file_list) {
        cout << list << endl;        
    }

    cout << file_list.size() + 1 << ". Input absolute path" << endl;
    command.show_prompt();

    string user_input;
    cin >> user_input;
    cout << "Please, input main password" << endl;

    size_t file_index = stoi(user_input) - 1;
    
    string first_line = file_manager.open(file_index);

    command.show_prompt();
    cin >> user_input;

    vector<string> passwd;
    passwd.push_back(user_input);
    file_template.set_passwd_list(passwd);
    file_template.create_phrase(square);

    Core core(file_template.get_square(), square_side);
    string key = core.decrypt(first_line);

    if (key != verification_phrase) {
        cout << "Wrong password" << endl;
    }
    else {
        // сделать вывод timestamp
        // show_timestamp();

        cout << "Timestamp: 00:00:00" << endl;
    }
    
    // debug
    // cout << key << endl;    

    // cleanup
    delete password_item;
    delete addtion_item;
    delete category_item;

}