#include "Path.hpp"

Path::Path(){}
Path::Path(const char* inp):path(inp){}
Path::Path(const std::string&  inp):path(inp){}
Path::Path(const std::string&& inp):path(inp){}
Path::Path(const Path&  other):path(other.path){}
Path::Path(const Path&& other):path(other.path){}

void Path::operator= (const std::string&  inp){path = inp;}
void Path::operator= (const std::string&& inp){path = inp;}
void Path::operator= (const Path&  other){path = other.path;}
void Path::operator= (const Path&& other){path = other.path;}

void Path::pop(int num){
    int ind = (int)path.length();
    for(int i = 0; i < num; i++)
        ind = (int)path.find_last_of('/', ind-1);
    path = path.substr(0,ind);
}

void Path::push(const char* inp){
    path = path + '/' + inp;
}
void Path::push(std::string& inp){
    push(inp.c_str());
}
void Path::push(const Path& other){
    push(other.path.c_str());
}

void Path::append(const std::string& str){
    path += str;
}
void Path::append(const char* str){
    path += str;
}

Path Path::rip(int num){
    if(num < 1) num = 1;
    int ind = (int)path.length();
    for(int i = 0; i < num; i++)
        ind = (int)path.find_last_of('/', ind-1);
    return path.substr(ind+1);
}

Path Path::getFilename(){
    Path last = rip();
    if(last.path.find('.') != -1)
        return last;
    return Path("");
}


const std::string& Path::str() const{
    return path;
}
const char* Path::c_str() const{
    return path.c_str();
}

void Path::print(){
    std::cout << path;
}
void Path::println(){
    std::cout << path << std::endl;
}

std::ostream& operator<< (std::ostream& os, Path& path){
    os << path.path;
    return os;
}

std::ostream& operator<< (std::ostream& os, Path&& path){
    os << path.path;
    return os;
}