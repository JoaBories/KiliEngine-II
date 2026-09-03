#pragma once

#include "Engine.h"

extern Kili::Engine* Kili::CreateEngine();

int main(int argc, char** argv)
{
    const auto engine = Kili::CreateEngine();
    engine->run();
    
    delete engine;
    
    return 0;
}