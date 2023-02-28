#include <iostream>
#include <vector>
#include <string>
#include <filesystem>
#include <fstream>

using std::endl; using std::string;
using std::filesystem::directory_iterator;

std::ofstream fout("all");
string base_path = "/home/gandalfr/CompPro-Workspace/library/";

string get_extention(const string &path){
    int dot_pos = path.find('.');
    if(dot_pos == -1) return "";
    return string(path.begin() + dot_pos + 1, path.end());
}

void file_search(const string &path){
    for (const auto & file : directory_iterator(path)){
        string filename = file.path();
        if(file.is_directory()){
            file_search(filename);
        }
        else if(get_extention(filename).compare("hpp") == 0){
            fout << "#include \"" << string(filename.begin() + base_path.size(), filename.end()) << "\"" << endl;
        }
    }
}

int main() {
    string path = "/home/gandalfr/CompPro-Workspace/library/gandalfr";
    file_search(path);
    return EXIT_SUCCESS;
}
