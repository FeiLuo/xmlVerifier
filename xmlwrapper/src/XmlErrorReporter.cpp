#include "XmlErrorReporter.h"
#include <xercesc/sax/SAXParseException.hpp>
#include <iostream>
#include <stdlib.h>
#include <string.h>
#include "XmlString.h"

void XmlErrorReporter::warning(const SAXParseException&)
{
    //
    // Ignore all warnings.
    //
}

void XmlErrorReporter::error(const SAXParseException& toCatch)
{
    fSawErrors = true;
    cerr << "Error at file \"" << StrX(toCatch.getSystemId())
		 << "\", line " << toCatch.getLineNumber()
		 << ", column " << toCatch.getColumnNumber()
         << "\n   Message: " << StrX(toCatch.getMessage()) << endl;
}

void XmlErrorReporter::fatalError(const SAXParseException& toCatch)
{
    fSawErrors = true;
    cerr << "Fatal Error at file \"" << StrX(toCatch.getSystemId())
		 << "\", line " << toCatch.getLineNumber()
		 << ", column " << toCatch.getColumnNumber()
         << "\n   Message: " << StrX(toCatch.getMessage()) << endl;
}

void XmlErrorReporter::resetErrors()
{
    fSawErrors = false;
}

