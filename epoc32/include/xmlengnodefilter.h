/*
* ==============================================================================
*  Name        : xmlengnodefilter.h
*  Part of     : XmlEngine / DOM XPath C++ Wrapper
*  Interface   : Domain, XML Engine DOM API
*  Description : Node filter interface
*  Version     : %version: 2 %
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

#ifndef XMLENGINE_NODEFILTER_H_INCLUDED
#define XMLENGINE_NODEFILTER_H_INCLUDED

#include <e32base.h>

class TXmlEngNode;

/** 
 * Results that can be returned by node filter
 */
enum TXmlEngNodeFilterResult
    {
    EAccept = 1,
    EReject = 2,
    ESkip = 3,
    ESkipContents = 4  /** non-standard feature */
    }; 

/** 
 * Interface of nodes filter class
 *
 * @see http://www.w3.org/TR/2000/REC-DOM-Level-2-Traversal-Range-20001113/traversal.html#Traversal-NodeFilter
 *
 * @since S60 v3.1
 */
class MXmlEngNodeFilter
    {
public:
    /** 
     * Check if node is accepted.
     *
     * @since S60 v3.1
     * @param aNode Node to check
     * @return Node filter result
     */ 
    virtual TXmlEngNodeFilterResult AcceptNode(TXmlEngNode aNode) = 0;    
    };


#endif /* XMLENGINE_NODEFILTER_H_INCLUDED */  
