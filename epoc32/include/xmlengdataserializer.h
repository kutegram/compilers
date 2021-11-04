/*
* ==============================================================================
*  Name        : XmlEngDataSerializer.h
*  Part of     : Xml Engine / DOM XPath C++ Wrapper
*  Interface   : Domain, XML Engine DOM API
*  Description : Interface class describing class that may be used as
*                serializer for binary data
*  Version     : %version: 4 %
*
*  Copyright © 2006-2006 Nokia. All rights reserved.
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

#ifndef XMLENGINE_MDATASERIALIZER_H_INCLUDED
#define XMLENGINE_MDATASERIALIZER_H_INCLUDED

#include "xmlengnode.h"

/**
 * MXmlEngDataSerializer interface used by XML Engine to serialize binary data for example binary data
 * stored in node, external memory chunk (RChunk) or file. This interface may be implemented by client application.
 *
 * @lib XmlEngineDOM.lib
 * @since S60 v3.2
 */
class MXmlEngDataSerializer
    {
public:
    /**
     * Callback for serializing data
     *
     * @since S60 v3.1
     * @param aNode is a node to serialize
     * @return Replacement string for node data
     */
    virtual TPtrC8 SerializeDataL(TXmlEngNode aNode) = 0;
    };


#endif /* XMLENGINE_MDATASERIALIZER_H_INCLUDED */  
