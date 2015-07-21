#include "BTSPD_Utils.h"

#include <IPAddressResolver.h>
#include <IInterfaceTable.h>
#include <InterfaceEntry.h>
#include "../../networklayer/ipv4/IPv4InterfaceData.h"
#include "../../networklayer/ipv6/IPv6InterfaceData.h"

void BTSPD_Utils::findAndSetIPAddress(cModule * comp)
{
    IInterfaceTable* ift    = NULL;
    InterfaceEntry* iff = NULL;
    cModule* mod        = comp;
    IPvXAddress         ipaddress_var;

    // traverse the hierarchy to grab the interface table
    while((ift = IPAddressResolver().findInterfaceTableOf(mod)) == NULL)
        mod = mod->getParentModule();

    // no interface table found? -- something nasty is happening here
    if(ift == NULL)
        // report the error
        throw cRuntimeError("%s:%d at %s() self-address resolution failed\n", __FILE__, __LINE__, __func__);

    // traverse the interface table and grab the appropriate IP address
    for(int i=0; i<ift->getNumInterfaces(); i++)
    {
        iff = ift->getInterface(i);

        // ignore loopbacks
        if(iff->isLoopback())
            continue;

        // if the interface has an IPv4 address then use it
        if(iff->ipv4Data() != NULL)
        {
            // update the address value
            ipaddress_var = IPvXAddress(iff->ipv4Data()->getIPAddress().str().c_str());
            // update the address parameter - just in case other objects use it (e.g., TCPSocket...)
            comp->par("address").setStringValue(ipaddress_var.str().c_str());
            break;
        }
        // try with IPv6
        else
        {
            // update the address value
            ipaddress_var = IPvXAddress(iff->ipv6Data()->getPreferredAddress().str().c_str());
            // update the address parameter - just in case other objects use it (e.g., TCPSocket...)
            comp->par("address").setStringValue(ipaddress_var.str().c_str());
            break;
        }
    }
}
