#include <iostream>
#include <filesystem>
#include <fstream>
#include <unordered_map>
#include <sstream>
#include <string>
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
            ifstream file(this->currentDir + "/" + filename);
            string line;
            while (getline(file, line))
            {
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

tuple<int, vector<string>> parsLine(string line){
    int cmdi=-1, index=0;
    vector<string> param;
    string word;
    istringstream linestream(line);

    while (linestream >> word){
        if(index == 0){
            if (word == "ls"){ cmdi = 0; }
            if (word == "cd"){ cmdi = 1; }
            if (word == "mkdir"){ cmdi = 2; }
            if (word == "touch"){ cmdi = 3; }
            if (word == "rm"){ cmdi = 4; }
            if (word == "exit"){ cmdi = 5; }
            if (word == "pwd"){ cmdi = 6; }
            if (word == "cat"){ cmdi = 7; }
            if (word == "write"){ cmdi = 8; }
            if (word == "rmdir"){ cmdi = 9; }
            
        }
        else{ 
            param.push_back(word); 
            }
        
        index++;
    }

    return {cmdi, param};
}

void displayError(string msg){
    cout << "\033[31m[ ! ] " << msg << "\033[0m"<<endl;
}

void displaySuccsess(string msg){
    cout << "\033[32m[ * ] " << msg << "\033[0m"<<endl;
}

int main (){

    FileManager a("/Users/levvedrov/Documents/GitHub/CLI-FileManager");
    cout << """\033[31m\n .d8888b.  888      8888888\nd88P  Y88b 888        888\n888    888 888        888\n888        888        888\n888        888        888\n888    888 888        888\nY88b  d88P 888        888\n'Y8888P'  88888888 8888888\n  By Lev Vedrov\n\n\033[0m""";
    string line;


    while(line!="exit"){
        cout << 	"\033[96m" << "" << a.getCurrentDir() << "\033[0m" << " >> " << "\033[0m";
        getline(cin, line);
        auto [cmd, par] = parsLine(line);
        switch (cmd)
        {
        case 0:
            a.listDir();
        break;

        case 1:
            if (par.size() > 1) { displayError("cd : Too many arguments"); }
            else{
                if (par.empty()){ cout << "NotYet"<<endl; }
                else{ a.changeDir(par[0]); }
            }
        break;

        case 2:
            if (par.size() > 1) { displayError("mkdir : Too many arguments"); }
            else{
                if (par.empty()){ displayError("mkdir : Need an argument"); }
                else{
                    a.createDir(par[0]);
                    a.changeDir(a.getCurrentDir()+ "/" + par[0]); 
                }
            }
        break;
        case 3:
            if (par.size() > 1) { displayError("touch : Too many arguments"); }
            else{
                if (par.empty()){ displayError("touch : Need an argument"); }
                else{
                    a.createFile(par[0]);
                }
            }
            break;
        case 4:
            if (par.size() > 1) { displayError("rm : Too many arguments"); }
            else{
                if (par.empty()){ displayError("rm : Need an argument"); }
                else{
                    a.deleteFile(par[0]);
                    
                }
            }
            break;
        case 5:
            // exit
            break;
        case 6:
             // pwd
            break;
        case 7:
            if (par.size() > 1) { displayError("cat : Too many arguments"); }
                else{
                    if (par.empty()){ displayError("cat : Need an argument"); }
                    else{
                        a.readFile(par[0]);
                    }
                }
            break;
        case 8:
            // write
            break;
        case 9:
        if (par.size() > 1) { displayError("rmdir : Too many arguments"); }
        else{
            if (par.empty()){ displayError("rmdir : Need an argument"); }
            else{
                a.deleteDir(par[0]);
            }
        }
            break;
    }
    
    }
    return 0;
}