#ifndef THING
#define THING

#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <typeinfo>

class Part;

class Thing
{
    public:
    Thing(Part* p);
    Thing(std::vector<Part*> ps);

    void handle();
    void update();
    void render();

    template <typename T>
    T* get()
    {
        if (parts.find(std::string(typeid(T).name())) == parts.end())
            return nullptr;

        return (T*) parts[std::string(typeid(T).name())];
    };

    void set(Part* p);

    private:
    std::map<std::string, Part*> parts;
};

#endif