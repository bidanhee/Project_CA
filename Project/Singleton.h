#pragma once

template <typename T>
class Singleton
{
protected:
    static T* singleton; 
    Singleton() {};
    virtual ~Singleton() {};
public:
    static T* getSingleton() 
    {
        if (!singleton) singleton = new T;
        return singleton;
    }
    static void Release()
    {
        if (singleton)
        {
            delete singleton;
            singleton = nullptr;
        }
    }
};
template <typename T>
T* Singleton<T>::singleton = nullptr;