/*
* ==============================================================================
*  Name        : xmlengprocessinginstruction.h
*  Part of     : XmlEngine / DOM XPath C++ Wrapper
*  Interface   : Private, XML Engine DOM API
*  Description : Processing instruction node functions
*  Version     : %version: 2 %
*
*  Copyright © 2004-2006 Nokia. All rights reserved.
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

#ifndef XMLENGINE_PROCESSINGINSTRUCTION_H_INCLUDED
#define XMLENGINE_PROCESSINGINSTRUCTION_H_INCLUDED

#include "xmlengnode.h"



/**
 * Instance of TXmlEngProcessingInstruction class represents an XML processing 
 * instruction in the DOM tree.
 * 
 * @lib XmlEngineDOM.lib
 * @since S60 v3.1
 */
class TXmlEngProcessingInstruction : public TXmlEngNode
{
  public:
    /**
     * Default constructor
     *
     * @since S60 v3.1
     */
	inline TXmlEngProcessingInstruction();
    
    /**
     * Get target of processing instruction.
     *
     * @since S60 v3.1
     * @return "Target" part of a processing instruction
     *
     * @code
     *    <?target data?>
     * @endcode
     * @see http://www.w3.org/TR/2004/REC-xml-20040204/#sec-pi
     */
    IMPORT_C TPtrC8 Target() const;

    /**
     * Get data of processing instruction.
     *
     * @since S60 v3.1
     * @return "Data" part of a processing instruction
     *
     * @code
     *    <?target data?>
     * @endcode
     * @see http://www.w3.org/TR/2004/REC-xml-20040204/#sec-pi
     */
    IMPORT_C TPtrC8 Data() const;

    /**
     * Sets data part of processing instruction
     *
     * @since S60 v3.1
     * @param aData New data part of processing instruction
     * @note PI contents should not contain "?>" sequence
     */
    IMPORT_C void SetDataL(const TDesC8& aData);

protected:
    /**
     * Constructor
     *
     * @since S60 v3.1
     * @param aInternal processing instruction pointer
     */
	inline TXmlEngProcessingInstruction(void* aInternal);
};



#include "xmlengprocessinginstruction.inl"
#endif /* XMLENGINE_PROCESSINGINSTRUCTION_H_INCLUDED */
