#ifndef COUNTER
#define COUNTER

#include "Text.h"
#include <string>

template <typename T>
class Counter : public Text
{
    public:
    Counter(std::string l = "", T val = 0, int x = 0, int y = 0, int h = 0);

    void setLabel(std::string l);

    T getValue();
    void setValue(T val = 0);

    void add(T val = 1);

    ~Counter();

    private:
    void updateText(std::string l, double val);
    void updateText(std::string l, std::string val);

    std::string label;
    T value;
};

#include "Counter.tpp"

#endif