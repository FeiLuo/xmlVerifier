#include "XmlParser.h"
#include "XmlString.h"
#include "XmlErrorReporter.h"
#include <xercesc/util/PlatformUtils.hpp>
#include <xercesc/parsers/AbstractDOMParser.hpp>
#include <xercesc/dom/DOMImplementation.hpp>
#include <xercesc/dom/DOMImplementationLS.hpp>
#include <xercesc/dom/DOMImplementationRegistry.hpp>
#include <xercesc/dom/DOMException.hpp>
#include <xercesc/dom/DOMDocument.hpp>
#include <xercesc/dom/DOMNodeList.hpp>
#include <xercesc/dom/DOMError.hpp>
#include <xercesc/dom/DOMLocator.hpp>
#include <xercesc/dom/DOMNamedNodeMap.hpp>
#include <xercesc/dom/DOMAttr.hpp>
#include <xercesc/framework/MemBufInputSource.hpp>
#include <xercesc/framework/Wrapper4InputSource.hpp>
#include <xercesc/util/OutOfMemoryException.hpp>
#include <fstream>

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
{
    // And call the termination method
    XMLPlatformUtils::Terminate();
}

XmlParser::XmlParser(const Uint8* data, const Uint32 len)
  : mParser(NULL),
    mDocument(NULL),
    mParseError(false)
{
    InitializeXmlParser();

    try
    {
        mParser->resetDocumentPool();
        MemBufInputSource* memBufInputSource = new MemBufInputSource((const XMLByte*)data, len, "XmlParser Memeory"); 
        
        Wrapper4InputSource wrapper4InputSource(memBufInputSource);
        mDocument = mParser->parse(&wrapper4InputSource);
    }
    catch (const OutOfMemoryException&)
    {
        ErrorMsg() << "OutOfMemoryException" <<  endl;
        mParseError = true;
    }
    catch (const XMLException& e)
    {
        ErrorMsg() << "An error occurred during parsing\n   Message: "
             << StrX(e.getMessage()) <<  endl;
        mParseError = true;
    }

    catch (const DOMException& e)
    {
        const unsigned int maxChars = 2047;
        XMLCh errText[maxChars + 1];

        if (DOMImplementation::loadDOMExceptionMsg(e.code, errText, maxChars))
              ErrorMsg() << "Message is: " << StrX(errText) <<  endl;

        mParseError = true;
    }
    catch (...)
    {
        ErrorMsg() << "An error occurred during parsing\n " <<  endl;
        mParseError = true;
    }
}

XmlParser::XmlParser(const char* xmlFileName)
  : mParser(NULL),
    mDocument(NULL),
    mParseError(false)
{
    InitializeXmlParser();

    try
    {
        mParser->resetDocumentPool();
        mDocument = mParser->parseURI(xmlFileName);
    }
    catch (const OutOfMemoryException&)
    {
        ErrorMsg() << "OutOfMemoryException" << endl;
        mParseError = true;
    }
    catch (const XMLException& e)
    {
        ErrorMsg() << "An error occurred during parsing\n   Message: "
             << StrX(e.getMessage()) << endl;
        mParseError = true;
    }

    catch (const DOMException& e)
    {
        const unsigned int maxChars = 2047;
        XMLCh errText[maxChars + 1];

        if (DOMImplementation::loadDOMExceptionMsg(e.code, errText, maxChars))
             ErrorMsg() << "Message is: " << StrX(errText) << endl;

        mParseError = true;
    }

    catch (...)
    {
        ErrorMsg() << "An error occurred during parsing\n " << endl;
        mParseError = true;
    }
}

XmlParser::~XmlParser()
{
    UninitializeXmlParser();
}

void XmlParser::InitializeXmlParser()
{
    UninitializeXmlParser();
    
    AbstractDOMParser::ValSchemes valScheme = AbstractDOMParser::Val_Auto;
    bool                       doNamespaces       = false;
    bool                       doSchema           = true;
    bool                       schemaFullChecking = true;
//    bool                       doList = false;
//    bool                       errorOccurred = false;
//    bool                       recognizeNEL = false;
//    bool                       printOutEncounteredEles = false;
    char                       localeStr[64];
    memset(localeStr, 0, sizeof localeStr);

    // Instantiate the DOM mParser.
    static const XMLCh gLS[] = { chLatin_L, chLatin_S, chNull };
    DOMImplementation *impl = DOMImplementationRegistry::getDOMImplementation(gLS);
    mParser = ((DOMImplementationLS*)impl)->createLSParser(DOMImplementationLS::MODE_SYNCHRONOUS, 0);
    DOMConfiguration  *config = mParser->getDomConfig();

    config->setParameter(XMLUni::fgDOMNamespaces, doNamespaces);
    config->setParameter(XMLUni::fgXercesSchema, doSchema);
    config->setParameter(XMLUni::fgXercesHandleMultipleImports, true);
    config->setParameter(XMLUni::fgXercesSchemaFullChecking, schemaFullChecking);

    if (valScheme == AbstractDOMParser::Val_Auto)
    {
        config->setParameter(XMLUni::fgDOMValidateIfSchema, true);
    }
    else if (valScheme == AbstractDOMParser::Val_Never)
    {
        config->setParameter(XMLUni::fgDOMValidate, false);
    }
    else if (valScheme == AbstractDOMParser::Val_Always)
    {
        config->setParameter(XMLUni::fgDOMValidate, true);
    }

    // enable datatype normalization - default is off
    config->setParameter(XMLUni::fgDOMDatatypeNormalization, true);

    XmlErrorReporter *errReporter = new XmlErrorReporter();
    config->setParameter(XMLUni::fgDOMErrorHandler, errReporter);
}

void XmlParser::UninitializeXmlParser()
{
    if (mParser != NULL)
    {
        mParser->release();
        delete mParser;
        mParser = NULL;
        mDocument = NULL;
    }
}


