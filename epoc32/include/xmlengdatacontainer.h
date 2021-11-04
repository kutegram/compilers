/*
* ==============================================================================
*  Name        : xmlengdatacontainer.h
*  Part of     : XmlEngine / DOM XPath C++ Wrapper
*  Interface   : Domain, XML Engine DOM API
*  Description : All binary data functions
*  Version     : %version: 2 %
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

#ifndef XMLENGINE_DATACONTAINER_H_INCLUDED
#define XMLENGINE_DATACONTAINER_H_INCLUDED

#include "xmlengnode.h"


/**
* TXmlEngDataContainer is a class for representing different types
* of binary data in DOM tree.
*
* It can be cusom-serialized using MXmlEngDataSerializer interface which can 
* be set in TXmlEngSerializationOptions used for saving the tree.
*
* @lib XmlEngineDOM.lib
* @since S60 v3.2
*/
class TXmlEngDataContainer : public TXmlEngNode
{
public:

    /**
     * Get CID of data container.
     *
     * @since S60 v3.2
     * @return Cid of data container
     * 
     */
    IMPORT_C TPtrC8 Cid() const;
        
    /**
     * Get data size in bytes
     *
     * @since S60 v3.1
     * @return Number of bytes occupied by data
     */
    IMPORT_C TUint Size() const;

protected:
    /**
     * Default constructor
	 *
     * @since S60 v3.1
     */
	inline TXmlEngDataContainer(); 

    /**
     * Constructor
     *
     * @since S60 v3.1
     * @param aInternal node pointer
     */
	inline TXmlEngDataContainer(void* aInternal);
};


 
#include "xmlengdatacontainer.inl"

#endif /* XMLENGINE_DATACONTAINER_H_INCLUDED */
