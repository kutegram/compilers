/*
* ==============================================================================
*  Name        : xmlengoutputstream.h
*  Part of     : Xml Engine / DOM XPath C++ Wrapper
*  Interface   : Domain, XML Engine DOM API
*  Description : Interface class describing class that may be used as
*                 output stream for dom tree
*  Version     : %version: 3 %
*
*  Copyright © 2004-2005 Nokia. All rights reserved.
*  This material, including documentation and any related 
*  computer programs, is protected by copyright controlled by 
*  Nokia. All rights are reserved. Copying, including 
*  reproducing, storing, adapting or translating, any 
*  or all of this material requires the prior written consent of 
*  Nokia. This material also contains confidential 
*  information which may not be disclosed to others without the 
*  prior written consent of Nokia.
* ==============================================================================
*/

#ifndef XMLENGINE_MOUTPUTSTREAM_H_INCLUDED
#define XMLENGINE_MOUTPUTSTREAM_H_INCLUDED

#include <e32base.h>



/**
 * MXmlEngOutputStream is used by XML Engine to write serialized XML data
 * to stream. This interface should be implemented by client application
 * when RXmlEngDocument::SaveL() method is used to serialize xml data to stream.
 *
 * @lib XmlEngineDOM.lib
 * @since S60 v3.1
 */
class MXmlEngOutputStream
    {
public:
    /**
     * Callback for writing a buffer with data to output stream
     *
     * @since S60 v3.1
     * @return number of bytes written or -1 in case of error
     */
    virtual TInt Write(const TDesC8& aBuffer) = 0;

    /**
     * Callback for closing output stream
     *
     * @since S60 v3.1
     * @return 
     *       0 is succeeded, 
     *      -1 in case of error
     */
    virtual TInt Close() = 0;
    };



#endif /* XMLENGINE_MOUTPUTSTREAM_H_INCLUDED */  
