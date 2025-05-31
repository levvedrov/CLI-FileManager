#include <iostream>
#include <filesystem>
#include <fstream>
#include <unordered_map>
#include <functional>
namespace fs = std::filesystem;
using namespace std;


class FileManager{
    private:
        string currentDir;
    public:

        FileManager(string root){
            this->currentDir = root;
        }
        void listDir(){
            for (auto& obj : fs::directory_iterator(currentDir)){
                if (fs::is_directory(obj)){
                    cout << "\033[33m[DIR]\033[0m : " << obj << endl;
                }
                else{
                    if(fs::is_regular_file(obj)){
                        cout << "\033[34m[FILE]\033[0m : " << obj << endl;
                    }
                }
            }
        }
        void changeDir(string newdir){
            this->currentDir = newdir;
        }
        void createFile(string filename){
            ofstream file(this->currentDir + filename);
            file.close();
        }
        void createDir(string dirname){
            fs::create_directory(dirname);
        }
        void deleteFile(string filepath){
            fs::remove(filepath);
        }
        void deleteDir(string path){
            fs::remove_all(path);
        }
        void readFile(string filename){
            ifstream file(this->currentDir + filename);
            string line;
            while (!EOF)
            {
                getline(file, line);
                cout<<line<<endl;
            }
            file.close();
        }
        void writeFile(string filename, string data){
            ofstream file(this->currentDir+filename);
            file << data;
            file.close();
        }
        string getCurrentDir(){
            return this->currentDir;
        }

};



int main (){

    FileManager a("/Users/levvedrov/Documents/GitHub/FileManager/");
    cout << """\033[31m\n .d8888b.  888      8888888\nd88P  Y88b 888        888\n888    888 888        888\n888        888        888\n888        888        888\n888    888 888        888\nY88b  d88P 888        888\n'Y8888P'  88888888 8888888\n  By Lev Vedrov\n\n\033[0m""";
    string cmd;


    while(cmd!="out"){
        cout << "\033[0m" << ">" << a.getCurrentDir() << "\033[0m" << "> ";
        cin >> cmd;
        

    }
    return 0;
}