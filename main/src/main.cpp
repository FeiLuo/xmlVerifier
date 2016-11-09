#include <iostream>         // For C++ IO streams
#include <string>
#include "XmlParser.h"

using namespace std;
XERCES_CPP_NAMESPACE_USE


void Initialize()
{
    if (!XmlParser::Initialize())
        exit(-1);
    
}

void Uninitialize()
{
    XmlParser::Uninitialize();
}

int main(int argc, char** argv)
{
    Initialize();

    

    Uninitialize();
    return 1;
}

