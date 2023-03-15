#include <string>
#include <iostream>

template <typename T>
Counter<T>::Counter(std::string l, T val, int x, int y, int h) : Text("", x, y, h)
{
    std::cout << "creating counter w values " << l << " " << val << " " << x << " " << y << " " << h << std::endl;
    
    label = l;
    value = val;

    updateText(label, value);
}

template <typename T>
void Counter<T>::setLabel(std::string l)
{
    label = l;
    
    updateText(label, value);
}

template <typename T>
T Counter<T>::getValue()
{
    return value;
}

template <typename T>
void Counter<T>::setValue(T val)
{
    value = val;

    updateText(label, value);
}

template <typename T>
void Counter<T>::add(T val)
{
    setValue(value + val);
}

template <typename T>
Counter<T>::~Counter()
{
    SDL_FreeSurface(sprite);
    TTF_CloseFont(font);
}

template <typename T>
void Counter<T>::updateText(std::string l, double val)
{
    setText(l + std::to_string((T) val));
}

template <typename T>
void Counter<T>::updateText(std::string l, std::string val)
{
    setText(l + val);
}