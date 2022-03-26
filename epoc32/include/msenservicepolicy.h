/*
* ==============================================================================
*  Name        : MServicePolicy.h
*  Part of     : Web Services Description
*  Interface   : 
*  Description : 
*  Version     : 
*
*  Copyright � 2002-2005 Nokia. All rights reserved.
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


#ifndef M_SEN_SERVICE_POLICY_H
#define M_SEN_SERVICE_POLICY_H

//  INCLUDES
#include <e32base.h> // for CActive
#include <badesca.h>

#include "SenDomFragment.h"

typedef RPointerArray<CSenElement> RPolicyArray;

// FORWARD DECLARATION

// CLASS DECLARATION
/*
*   <ServicePolicy>
*       <ClientPolicy>
*			<MetadataEndpoint>uri.1</MetadataEndpoint>
*			<MetadataEndpoint>uri.2</MetadataEndpoint>
*			<MetadataEndpoint>uri.3</MetadataEndpoint>
*           <PolicyValue1/>				
*           <PolicyValue2/>				
*       </ClientPolicy>
*       <PolicyArrray>
*			<wsp:Policy1/>
*			<wsp:Policy2/>
*       </PolicyArrray>
*   </ServicePolicy>
*/
class MSenServicePolicy
    {
    public: // New functions

        /**
        * Adds a policy in SD
        * Method is used to add a RAW policy obtained 
        * by Network or some dynamic means
        * @since S60 5.0
        * @param aPolicy is the Policy Element
        */ 
        virtual TInt AddPolicyL(CSenElement* aPolicy) = 0;

        /**
        * Remove  a Policy from SD
        * @param aPolicyName , Policy with this name will be removed from SD
        * @return
        *  - KErrNone 
        
        */ 
        virtual TInt RemovePolicyL(TDesC8& aPolicyName) = 0;

        /**
        * Method reads provider policy class instance values from given
        * template. 
        * @since S60 5.0
        * @param aTemplate from which the values are read.
        * @return   
        *           
        */ 
        virtual TInt RebuildServicePolicyFrom(MSenServicePolicy& aTemplate) = 0;
        
        /**
        * Checks if policies match.
        * @return ETrue if policies match, EFalse if not.
        */
        virtual TBool Accepts(MSenServicePolicy& aPolicyPattern) = 0;
       
        /**
        * Getter for ServicePolicies
        * @since S60 5.0
        * @return 
        *           
        */ 

		/**
		* Return all of the Services polices from SD only <wsp:Policy> tags
		* @param aPolicies
		* @return KErrNone
		*		  KErrNotFound	
		*/
        virtual TInt ServicePolicies(RPolicyArray& aPolicies) = 0;
        /**
        * Gets the Client Policy
        */
        virtual CSenElement* ClientPolicy() = 0;
        /**
        * Searches for the Client Policy with the given key value
        * @param aKey
        * @return ETrue If the Client Policy is present with the given key value
        *		  EFalse If the Client Policy is not present with the given key value  
        */
        virtual TBool ClientPolicy(const TDesC8& aKey) = 0;
        /**
        * Gets the Client Policy with the given key value
        * @param aKey
        * @return Client Policy Value is returned
        */
        virtual HBufC8* ClientPolicyValue(const TDesC8& aKey) = 0;
    };

#endif //M_SEN_POLICY_H

// End of File
