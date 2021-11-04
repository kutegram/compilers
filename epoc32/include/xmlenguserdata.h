/*
 * ==============================================================================
 *  Name        : XmlEngUserData.h
 *  Part of     : Xml Engine / DOM XPath C++ Wrapper
 *  Interface   : Domain, XML Engine DOM API
 *  Description : Interface class describing class that may contains user
 *                 data aded to node
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

#ifndef XMLENGINE_USERDATA_H_INCLUDED
#define XMLENGINE_USERDATA_H_INCLUDED

#include <e32def.h>

/**
 * MXmlEngUserData is an abstract base class (interface) for user data that can be
 * stored in the DOM tree. Applications that wish to store user data in the 
 * DOM tree must wrap the user data in a class that implemens this interface.
 *
 * @lib XmlEngineDOM.lib
 * @since S60 v3.1
 */
class MXmlEngUserData {
public:
    /**
     * Free memory that is allocated and do other case specific cleanup.
     *
     * @since S60 v3.1
     */
    virtual void Destroy() = 0;
    
    /**
     * Make a copy of the the object. Note that if reference counting is used or
     * the same pointer can be safely copied to other places the implementation
     * of this method may just return a pointer to self.
     *
     * Copying user data when copying nodes has not been implemented
     * so this method is for future use (though there's no harm in implementing 
     * it, of course).
     *
     * @since S60 v3.1
     * @return Pointer to a copy of this object.
     */
    virtual MXmlEngUserData* CloneL() = 0;

    /**
     * Get id of the object. It is up to user-data provider what the result is.
     * Such a "user data identification" may be in use if several types of
     * MXmlEngUserData objects are used.
     *
     * @since S60 v3.1
     * @return Pointer that somehow identifies the type of MXmlEngUserData (NULL by default)
     */
    virtual void* ID() {return NULL;}
};



#endif /* XMLENGINE_USERDATA_H_INCLUDED*/
