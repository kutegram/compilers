/*
* ==============================================================================
*  Name        : xmlengfilecontainer.h
*  Part of     : XmlEngine / DOM XPath C++ Wrapper
*  Interface   : Domain, XML Engine DOM API
*  Description : All file container data functions
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

#ifndef XMLENGINE_FILECONTAINER_H_INCLUDED
#define XMLENGINE_FILECONTAINER_H_INCLUDED

#include "xmlengdatacontainer.h"

class RFile;



/**
* Instance of TXmlEngFileContainer class represents data stored in RFile in DOM tree
*
* RFile container is treated in general as text nodes in DOM tree.
* Some of the fields in xmlNode structure are reused in order to save memory. 
* Data is stored in file system referenced to by RFile handle.
*
* Sample code for creating filecontainer:
* @code  
*      RXmlEngDOMImplementation domImpl;
*      domImpl.OpenL();        ///< opening DOM implementation object 
*      RXmlEngDocument iDoc; 
*      ///< create document element
*      TXmlEngElement elem = iDoc.CreateDocumentElementL(_L8("doc"));
*      ///< create file container from file (file1 is an RFile object) and CID equals cid
*      TXmlEngFileContainer binData = iDoc.CreateFileContainerL(cid, file1);
*      elem.AppendChildL(binData);      ///< append container to the dom tree       
*      iDoc.Close();               ///< closing all opened objects
*      domImpl.Close();
* @endcode 
*
* @lib XmlEngineDOM.lib
* @since S60 v3.2
*/
class TXmlEngFileContainer : public TXmlEngDataContainer
{
public:
    /**
     * Get RFile reference
     *
     * @since S60 v3.2
     * @return RFile reference
     * 
     */
    IMPORT_C RFile& File() const;
	
protected:
    /**
     * Default constructor
	 *
     * @since S60 v3.1
     */
	inline TXmlEngFileContainer(); 
	
    /**
     * Constructor
     *
     * @since S60 v3.1
     * @param aInternal node pointer
     */
	inline TXmlEngFileContainer(void* aInternal);
};



#include "xmlengfilecontainer.inl"

#endif /* XMLENGINE_FILECONTAINER_H_INCLUDED */
