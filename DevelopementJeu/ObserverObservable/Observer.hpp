#pragma once
#include <string>
#include <list>

template <typename T>
class Observer {
public:
    virtual void notification(T data) = 0;
};

template <typename T>
class Observable : public Observer<T> {  
private:
        list<Observer<T>*> observers;

public:

    void subscribe(Observer<T>* observer)
    {
        observers.push_back(observer);
    }

    void unsubscribe(Observer<T>* observer)
    {
        observers.remove(observer);
    }

    void notify(string data)
    {
        for (auto it : observers)
        {
            it->notification(data);
        }
    }

};
