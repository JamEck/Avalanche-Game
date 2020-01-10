#ifndef Path_hpp
#define Path_hpp

#include <string>
#include <iostream>

class Path{
private:
    std::string path;
public:
    Path();
    Path(const char* path);
    Path(const std::string&  path);
    Path(const std::string&& path);
    Path(const Path&  other);
    Path(const Path&& other);

    void operator= (const std::string&  path);
    void operator= (const std::string&& path);
    void operator= (const Path&  other);
    void operator= (const Path&& other);

    void push(const char* path);
    void push(std::string& path);
    void push(const Path& other);

    void append(const std::string& str);
    void append(const char* str);

    void pop(int num = 1);

    Path rip(int num = 1);
    Path getFilename();

    const std::string& str() const;
    const char* c_str() const;

    void print();
    void println();
    friend std::ostream& operator<< (std::ostream& os, Path& path);
    friend std::ostream& operator<< (std::ostream& os, Path&& path);
};

#endif /* Path_hpp */
