#include "readCode.h"
#include <iostream>
#include <string>
#include <vector>
#include <stack>


void readCode::parse(){
    int cnt = 0;
    do{
        std::string literal;
        std::cin >> literal;
        if (literal == "{"){
            cnt++;
        }
        if (literal == "}"){
            cnt--;
        }
        this->code.push_back(literal);
    }
    while(cnt != 0);
}


void readCode::compile(){
    std::stack<int> scopes;
    int cnt = -1;
    for(int i = 0; i < code.size(); i++){
        if (code[i] == "{"){
            localVriables.clear();
            cnt++;
            scopes.push(cnt);
        }
        else if(code[i] == "}"){
            std::vector<variable> temp;
            for (auto v : allVriables){
                if(v.scope != scopes.top()){
                    temp.push_back(v);
                }
            }
            allVriables = temp;
            scopes.pop();
            localVriables.clear();
            for (auto v: allVriables){
                if(v.scope == scopes.top()){
                    localVriables.push_back(v);
                }
            }
        }
        else if(code[i] == "set"){
            std::string name = code[i+1];
            if(name == "set" || name == "print"){
                std::cout << "Zelle Error";
                exit(0);
            }
            int scope = scopes.top();
            if(isInLocalVariabbles(scope, name)){
                std::cout << "Zelle Error";
                exit(0);
            }
            i = i + 3;
            std::vector<std::string> value ;
            do{
                value.push_back(code[i]);
                i ++;
            }
            while(code[i] != ";");
            variable var;
            var.name = name;
            var.scope = scope;
            var.value = calculate(value);
            allVriables.push_back(var);
            localVriables.push_back(var);
            }

        else if(code[i] == "print"){
            i = i + 1;
            std::vector<std::string> value ;
            do{
                value.push_back(code[i]);
                i ++;
            }
            while(code[i] != ";");
            outputs.push_back(calculate(value));
        }
        else{
            if(isInAllVariabbles(code[i])){
                std::string name = code[i];
                std::vector<std::string> value;
                i = i + 2;
                do{
                value.push_back(code[i]);
                    i ++;
                }
                while(code[i] != ";");
                int result = calculate(value);
                int j = getValWithMaxScope(name);
                allVriables[j].value = result;
            }
            else{
                std::cout << "Zelle Error";
                exit(0);
            }
        }
    }
    for(int i = 0; i < outputs.size(); i++){
        std::cout << outputs[i];
        if(i != outputs.size() - 1){
            std::cout << std::endl;
        }
    }
}

bool readCode::isInLocalVariabbles(int scope, std::string name){
    for(auto v: this->localVriables){
        if(v.name == name && scope == v.scope){
            return 1;
            }
        }
    return 0;
}


bool readCode::isInAllVariabbles(std::string name){
    for(auto v: this->allVriables){
        if(v.name == name){
            return 1;
            }
        }
    return 0;
}


int readCode::getValWithMaxScope(std::string name){
    for(int i = allVriables.size() - 1; i >= 0; i--){
        if(name == allVriables[i].name){
            return i;
        }
    }
}


int readCode::calculate(std::vector<std::string> value){
    bool negative = 0;
    int result = 0;
        for(auto v: value){
            try{
                int num = stoi(v);
                if(negative){
                    result = result - num;
                    }
                else{
                    result = result + num;
                    }
                }
        catch(std::exception &e){
            if(isInAllVariabbles(v)){
                if(negative){
                    result = result - allVriables[getValWithMaxScope(v)].value;
                    }
                    else{
                    result = result + allVriables[getValWithMaxScope(v)].value;
                    }
                }
                else if(v == "+"){
                    negative = 0;
                }
                else if(v == "-"){
                    negative = 1;
                }
                else {
                    std::cout << "Zelle Error";
                    exit(0);
                }
            }
        }
    return result;
}
