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

void run_cases(const char* path)
{
    XmlParser parser(path);
    if (parser.IsParseError())
        cout << parser.GetErrorMsg() << endl;
}

int main(int argc, char** argv)
{
    cout << "xml verifier started: " << endl;
    Initialize();

    run_cases(argv[1]);

    Uninitialize();

    cout << "xml verifier finished!" << endl;
    return 1;
}

