#include "FileManager.h"

using namespace std;

const vector<string>& FileManager::get_file_list(const string& directory) {

    string path = directory;   
    
    size_t file_index = 1;

    for (const auto& entry : filesystem::directory_iterator(directory)) {

        if (entry.path().extension() == ".dat") {
            
            string filename = entry.path().filename().string();
            file_list.push_back(filename);
            menu.push_back(to_string(file_index) + ". " + filename);

            file_index++;

        }

    }

    return menu;
}


// возвращет первую строку с ключом
// читает весь файл в 
const string FileManager::open(const size_t index) {

    string first_line;
    string other_line;
    content.clear();

    if (file_list.size() > 0) {
        ifstream file(file_list[index]);        
        file >> first_line;
        
        content.push_back(first_line);

        while (file >> other_line) {
            content.push_back(other_line);
        }
    }

    return first_line;

}

const vector<string>& FileManager::get_conten() {
    
    return content;

}