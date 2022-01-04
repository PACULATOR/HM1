#include <iostream>
#include <string>
#include <vector>
#include <fstream>
using namespace std;
int main(int argc, const char* argv[]) {
    if (argc != 3) {
        cerr << "Error: Use three parameters\n";
        return 5;
    }
    const string mode(argv[1]); // Режим работы
    const string file_name(argv[2]); // Имя файла
    if (mode == "encryption") {
// Режим шифрование
        std::cout << "Введите текст";
        std::string str;
        getline(cin, str);
        //bool flag = true;
        std::cout << std:: endl;
        std::cout << "Придумайте числовой пароль";
        unsigned int pw;
        std::cin >> pw;
        const char *chrs = str.data();
        int len = str.size();
        std::vector <char> byte(len);
        std::cout << std:: endl;
        for ( int i=0; i < len;i++){
            byte[i]=chrs[i];
        }
        srand(pw+32768);
        unsigned  int step;
        step = pw%10;
        std::ofstream outpup;
        outpup.open(file_name, ios::binary);
        for (unsigned int i = 0; i < byte.size(); i+=2){
            unsigned  int gamma = rand();
            unsigned char ch1 = byte[i];
            unsigned char ch2 = i + 1 < byte.size() ? byte[i+1] : 0u;
            unsigned  int Xor_and_connect = ((static_cast<unsigned int>(ch1) | static_cast<unsigned int>(ch2)))^gamma;
            unsigned int moved(Xor_and_connect << step | (Xor_and_connect & 0xFFFF) >> (16-step));
            char r1 = moved >> 8;
            char r2 = moved;
            outpup.write(&r1, sizeof(r1));
            outpup.write(&r2, sizeof(r2));
        }
        outpup.close();
    }
    else if (mode == "decryption") {
// Режим расшифрования
    std::ifstream inpup;
    inpup.open(file_name, std::ios::binary);
    std::vector<char> readd ((std::istreambuf_iterator<char>(inpup)),std::istreambuf_iterator<char>());
    std::vector<char> result (readd.size());
    inpup.close();
    std::cout << "Введите числовой пароль: ";
    unsigned int step;
    unsigned  int pw;
    std::cin >> pw;
    step = pw%10;
    srand(pw+32768);
    std::cout << std:: endl;
    for (unsigned int i = 0; i < readd.size(); i++){
        unsigned int gamma = rand();
        unsigned char ch1 = readd[i];
        unsigned char ch2 = i + 1 <readd.size()? readd[i+1] : 0u;
        unsigned  int Xor_connect = (static_cast<unsigned  int>(ch1) << 8 | static_cast<unsigned int>(ch2));
        unsigned int moved = ((Xor_connect & 0xFFFF) >> step | (Xor_connect >> (16-step)));
        moved = moved ^ gamma;
        unsigned  char c1 = moved >> 8;
        unsigned char c2 = moved;
        result[i]=c1;
        result[i+1]=c2;
    }
    for (auto x: result){
        std::cout <<x;
    }
    std::cout<< std::endl;

    }
    return 0;
}