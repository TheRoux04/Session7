#pragma once
#include <string>
#include "Observer.hpp"
#include <iostream>

using namespace std;

class Policeman : public Observer<string> {
private:
    string name;
public:
    Policeman(string name){
        this->name = name;
    }
    
    void notification(string data)
    {
        cout << "Policeman " << name << " received: " << data << endl;
    }
};

class FireFighter : public Observer<string> {
private:
    string name;
public:
    FireFighter(string name){
        this->name = name;
    }
    
    void notification(string data)
    {
        cout << "FireFighter " << name << " received: " << data << endl;
    }
};

class Paramedic : public Observer<string> {
private:
    string name;
public:
    Paramedic(string name){
        this->name = name;
    }
    
    void notification(string data)
    {
        cout << "Paramedic " << name << " received: " << data << endl;
    }
};


