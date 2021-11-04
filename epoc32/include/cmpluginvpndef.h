/*
* ============================================================================
*  Name        : cmpluginvpndef.h
*  Part of     : Networking Utilities / Connection Method Manager
*  Description : Attributes for VPN plug-in.
*  Version     : %version: 6 %
*
*  Copyright © 2006 Nokia.  All rights reserved.
*  This material, including documentation and any related computer
*  programs, is protected by copyright controlled by Nokia.  All
*  rights are reserved.  Copying, including reproducing, storing,
*  adapting or translating, any or all of this material requires the
*  prior written consent of Nokia.  This material also contains
*  confidential information which may not be disclosed to others
*  without the prior written consent of Nokia.
* ============================================================================
*/
#ifndef VPN_PLUGIN_DEF_H
#define VPN_PLUGIN_DEF_H

#include <cmconnectionmethoddef.h>

/**  ECOM interface UID */
const TUint KPluginVPNBearerTypeUid = 0x10281BBD;

namespace CMManager
    {
    /**
     VPN specific attributes
     
     Note: ECmProxyPortNumber is a common bearer attribute, but its  default
     value varies in the VPN plug-in, where it is 80
     
     Note2: VPN, as it is a virtual plugin, does not supports the following 
     common attributes (these are valid only for real bearers):
            ECmIFName,                  ECmIFParams,        
            ECmIFNetworks,              ECmIFPromptForAuth,
            ECmIFAuthName,              ECmIFAuthPass,
            ECmIFAuthRetries,           ECmIPNetmask,
            ECmIPGateway,               ECmIPAddFromServer,
            ECmIPAddress,               ECmIPDNSAddrFromServer,
            ECmIPNameServer1,           ECmIPNameServer2,   
            ECmIP6DNSAddrFromServer,    ECmIP6NameServer1,
            ECmIP6NameServer2,          ECmIPAddrLeaseValidFrom,
            ECmIPAddrLeaseValidTo,      ECmConfigDaemonManagerName,
            ECmConfigDaemonName,        ECmEnableLPCExtension,
            ECmDisablePlainTextAuth
     Querying these will leave with KErrNotSupported.
     */
    enum TConnectionMethodVpnSpecificAttributes
        {
        EPluginVpnAttribStart = 30000,  /**<
                                        * Marks the beginning of the VPN
                                        * attributes.
                                        */
        
        EVpnServicePolicyName = 30100,  /**<
                                        * Policy name.
                                        * (String - default: None)
                                        */
                                        
        EVpnServicePolicy,              /**<
                                        * Policy.
                                        * (String - default: None)
                                        */


        EVpnIapId,                      /**<
                                        * Home IAP Id.
                                        * (TUint32 - default: None)
                                        */

        EVpnNetworkId,                  /**<
                                        * Network Id.
                                        * (TUint32 - default: None - read only)
                                        */
                                        
        EVpnServiceEnableLLMNR,         /**<
                                        * LLMNR
                                        * (TBool - default: EFalse)
                                        */

        EPluginVpnAttribRangeMax = 39999    /**<
                                            * Marks the end of the VPN
                                            * attributes.
                                            */
        };
    } // namespace CMManager
    
#endif // VPN_PLUGIN_DEF_H
