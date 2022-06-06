#include "CryptoFileTemplate.h"

using namespace std;

CryptoFileTemplate::CryptoFileTemplate(const size_t square_side) {
    this->square_side = square_side;
}

// Создает файлы с проверочной фразой и мусором для timestamp
void CryptoFileTemplate::generate_file(const string& verification_phrase) {

    create_file_names(kMaxFiles);

    string first_file_string = (verification_phrase == "") ? this->verification_phrase : verification_phrase;
    vector<string> phrase_list = explode(first_file_string, ' ');    

    // тут нужен перебор доступных паролей, а не первый вариант

    for (size_t list = 0; list < file_list.size(); list++) {
        
        Core core(square_list[list], square_side);
        ofstream out(file_list[list]);
        
        out << core.encrypt(first_file_string) << endl;    
        for (size_t i = 0; i < square_side; i++) {
            string encoded_buffer = generate_dumb_line(phrase_list, core);

            // размещаем часы:минуты:секунды через каждые 3 строки
            if ((i % 3) == 0) {
                out << "00" << encoded_buffer << endl;
            } 
            else {
                out << encoded_buffer << endl;
            }
        }

        out.close();

    }
    
}

// создает имена файлов под число паролей с расширением dat
const vector<string> CryptoFileTemplate::create_file_names(const size_t max_files) {
    
    string file_name;

    for (size_t i = 0; i < kMaxFiles; i++) {
        file_name += "file" + to_string(i) + ".dat";
        file_list.push_back(file_name);

        // debug
        cout << file_name << endl;

        file_name.clear();
    }

    return file_list;
}

const string CryptoFileTemplate::generate_dumb_line(const vector<string>& phrase_list, Core& core) {
    
    size_t phrase_count = phrase_list.size();

    // Источник энтропии
    random_device random_device;
    // Генератор случайных чисел
    mt19937 generator(random_device());
    // Равномерное распределение [0, phrase_count - 1]
    uniform_int_distribution<> distribution(0, phrase_count - 1);
    string buffer;
    string encoded_buffer;

    for (size_t i = 0; i < phrase_count; i++) {
        // Случайное число
        int x = distribution(generator);
        buffer += phrase_list[x] + ">>>";
        encoded_buffer += core.encrypt(phrase_list[x]) + ">>>";

        //cout << x << ", ";
    }

    //cout << endl;

    /* // debug
    for (auto pl : phrase_list) {
        cout << pl << endl;
    }

    cout << buffer << endl;
    cout << encoded_buffer << endl;
    */

    return encoded_buffer;

}

void CryptoFileTemplate::create_phrase(const string& square) {
    
    vector<string>::const_iterator it;
    for (it = passwd_list.begin(); it != passwd_list.end(); it++) {

        string square_shifted = *it;
        string passwd = *it;

        square_shifted += exclude(passwd, square);
        
        square_list.push_back(square_shifted);
        // debug
        //cout << square_shifted << endl;

    }

    //generate_file(verification_phrase);

}

std::string CryptoFileTemplate::exclude(const string& passwd, const string& square) {

    const size_t length_passwd = passwd.length();
    size_t length_square = square.length();
    string tempered = square;
    string inner_tempered;

    for (size_t i = 0; i < length_passwd; i++) {

        if (i != 0) {
            length_square = tempered.length();
        }

        for (size_t j = 0; j < length_square; j++) {
            if (passwd[i] != tempered[j]) {
                inner_tempered += tempered[j];
            }
        }

        length_square = inner_tempered.length();
        tempered = inner_tempered;

        inner_tempered.clear();

    }

    return tempered;

}

const vector<string> CryptoFileTemplate::explode(const string& src, const char& separator)
{
    string buff;
    vector<string> words;

    for (auto n : src)
    {
        if (n != separator) {
            buff += n;
        }
        else {
            if (n == separator && buff != "") {
                words.push_back(buff);
                buff = "";
            }
        }

    }

    if (buff != "") {
        words.push_back(buff);
    }

    return words;

}

void CryptoFileTemplate::set_passwd_list(const vector<string>& passwd_list) {

    this->passwd_list = passwd_list;

}

void CryptoFileTemplate::set_verification_phrase(const string& verification_phrase) {

    this->verification_phrase = verification_phrase;

}

const string CryptoFileTemplate::get_square(const size_t index) {

    return square_list[index];

}