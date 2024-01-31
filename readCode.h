#ifndef READCODE_H_INCLUDED
#define READCODE_H_INCLUDED
#include <vector>
#include <string>
struct variable{
    int scope;
    int value;
    std::string name;
};

class readCode{
public:
    void parse();
    void compile();

private:
    std::vector<std::string> code;
    std::vector<variable> allVriables;
    std::vector<variable> localVriables;
    std::vector<int> outputs;

    bool isInLocalVariabbles(int,std::string);
    bool isInAllVariabbles(std::string);
    int getValWithMaxScope(std::string);
    int calculate (std::vector<std::string>);
};


#endif // READCODE_H_INCLUDED
