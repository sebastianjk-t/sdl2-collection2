#include "Thing.h"
#include "Part.h"

using namespace std;

Part::Part(Thing* t)
{
    thing = t;
}

void Part::init(Thing* t)
{
    thing = t;
}

void Part::handle()
{

}

void Part::update()
{

}

void Part::render()
{

}