#ifndef XML_ERROR_REPORTER
#define XML_ERROR_REPORTER

#include <xercesc/dom/DOMErrorHandler.hpp>
#include <xercesc/util/XMLString.hpp>
#include <iostream>
#include "XmlString.h"
using namespace std;
XERCES_CPP_NAMESPACE_USE

class XmlErrorReporter : public DOMErrorHandler
{
public:
public:
    // -----------------------------------------------------------------------
    //  Constructors and Destructor
    // -----------------------------------------------------------------------
    XmlErrorReporter();
    ~XmlErrorReporter();


    // -----------------------------------------------------------------------
    //  Getter methods
    // -----------------------------------------------------------------------
    bool getSawErrors() const;


    // -----------------------------------------------------------------------
    //  Implementation of the DOM ErrorHandler interface
    // -----------------------------------------------------------------------
    bool handleError(const DOMError& domError);
    void resetErrors();


private :
    // -----------------------------------------------------------------------
    //  Unimplemented constructors and operators
    // -----------------------------------------------------------------------
    XmlErrorReporter(const XmlErrorReporter&);
    void operator=(const XmlErrorReporter&);


    // -----------------------------------------------------------------------
    //  Private data members
    //
    //  fSawErrors
    //      This is set if we get any errors, and is queryable via a getter
    //      method. Its used by the main code to suppress output if there are
    //      errors.
    // -----------------------------------------------------------------------
    bool    fSawErrors;
};

inline bool XmlErrorReporter::getSawErrors() const
{
    return fSawErrors;
}

#endif // XML_ERROR_REPORTER
