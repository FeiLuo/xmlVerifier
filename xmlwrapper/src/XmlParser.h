#ifndef XML_PARSER_H
#define XML_PARSER_H

#include "Types.h"
#include <xercesc/dom/DOMLSParser.hpp>
#include <xercesc/dom/DOMErrorHandler.hpp>
#include <xercesc/util/XMLString.hpp>
#include <iostream>
#include <sstream>
#include <string>
XERCES_CPP_NAMESPACE_USE
using namespace std;

class XmlParser
{
public:
    static Boolean Initialize();
    static void Uninitialize();

    XmlParser(const Uint8* data, const Uint32 len);
    XmlParser(const char* xmlFileName);
    ~XmlParser();
    
    inline ostringstream& ErrorMsg() { return mErrorMsg; }
    inline string  GetErrorMsg() { return mErrorMsg.str(); }
    
protected:
    void InitializeXmlParser();
    void UninitializeXmlParser();
    
private:
    DOMLSParser*    mParser;
    DOMDocument*    mDocument;
    Boolean         mParseError;
    std::ostringstream   mErrorMsg;
};

#endif // XML_PARSER_H
