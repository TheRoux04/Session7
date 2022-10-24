#pragma once
#include <map>
#include <string>
#include "Observer.hpp"

using namespace std;

class Dispacher
{
private:
    map<string, Observable<string>*> incidents;
public:

    void addIncident(string name)
    {
        incidents[name] = new Observable<string>();
    }

    void removeIncident(string name)
    {
        delete incidents[name];
        incidents.erase(name);
    }

    void available(string incident, Observable<string>* responder)
    {
        incidents[incident]->subscribe(responder);
    }

    void unavailable(string incident, Observable<string>* responder)
    {
        incidents[incident]->unsubscribe(responder);
    }

    void notify(string incident, string data)
    {
        incidents[incident]->notify(data);
    }
};
