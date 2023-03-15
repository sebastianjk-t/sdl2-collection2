#include "Thing.h"
#include "Part.h"

using namespace std;

Thing::Thing(Part* u)
{
    set(u);
}

Thing::Thing(std::vector<Part*> us)
{
    for (Part* u : us)
        set(u);
}

void Thing::handle()
{
    for (pair<string, Part*> pair : parts)
        pair.second -> handle();
}

void Thing::update()
{
    for (pair<string, Part*> pair : parts)
        pair.second -> update();
}

void Thing::render()
{
    for (pair<string, Part*> pair : parts)
        pair.second -> render();
}

void Thing::set(Part* p)
{
    parts[std::string(typeid(*p).name())] = p;
    p -> init(this);
}