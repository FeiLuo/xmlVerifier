#include "XmlErrorReporter.h"
//#include <stdlib.h>
//#include <string.h>
#include <xercesc/dom/DOMError.hpp>
#include <xercesc/dom/DOMLocator.hpp>

XmlErrorReporter::XmlErrorReporter() :

    fSawErrors(false)
{
}

XmlErrorReporter::~XmlErrorReporter()
{
}


// ---------------------------------------------------------------------------
//  DOMCountHandlers: Overrides of the DOM ErrorHandler interface
// ---------------------------------------------------------------------------
bool XmlErrorReporter::handleError(const DOMError& domError)
{
    if (domError.getSeverity() == DOMError::DOM_SEVERITY_WARNING)
    {
        cerr << "\nWarning at file ";
    }
    else if (domError.getSeverity() == DOMError::DOM_SEVERITY_ERROR)
    {
        fSawErrors = true;
        cerr << "\nError at file ";
    }
    else
    {
        fSawErrors = true;
        cerr << "\nFatal Error at file ";
    }

    cerr << StrX(domError.getLocation()->getURI())
         << ", line " << domError.getLocation()->getLineNumber()
         << ", char " << domError.getLocation()->getColumnNumber()
         << "\n  Message: " << StrX(domError.getMessage()) << XERCES_STD_QUALIFIER endl;

    return true;
}

void XmlErrorReporter::resetErrors()
{
    fSawErrors = false;
}

