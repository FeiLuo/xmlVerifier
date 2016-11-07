#include "XmlParser.h"
#include <xercesc/util/PlatformUtils.hpp>

Boolean XmlParser::Initialize()
{
	try 
    {
        XMLPlatformUtils::Initialize(); 
    }   
    catch (const XMLException& toCatch)
    {
        char* message = XMLString::transcode(toCatch.getMessage());
        cout << "Error during initialization! :\n"
            << message << "\n";
        XMLString::release(&message);
        return false; 
    }
    return true;
}

void XmlParser::Uninitialize()
    // And call the termination method
    XMLPlatformUtils::Terminate();
}
