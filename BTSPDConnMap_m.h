//
// Generated file, do not edit! Created by opp_msgc 4.2 from applications/BitTorrentSPD/BTSPDConnMap.msg.
//

#ifndef _BTSPDCONNMAP_M_H_
#define _BTSPDCONNMAP_M_H_

#include <omnetpp.h>

// opp_msgc version check
#define MSGC_VERSION 0x0402
#if (MSGC_VERSION!=OMNETPP_VERSION)
#    error Version mismatch! Probably this file was generated by an earlier version of opp_msgc: 'make clean' should help.
#endif



/**
 * Class generated from <tt>applications/BitTorrentSPD/BTSPDConnMap.msg</tt> by opp_msgc.
 * <pre>
 * message BTSPDConnMapMsg
 * {
 *     @omitGetVerb(true);
 *     string myIP;
 *     string remoteIP;    
 * }
 * </pre>
 */
class BTSPDConnMapMsg : public ::cMessage
{
  protected:
    opp_string myIP_var;
    opp_string remoteIP_var;

  private:
    void copy(const BTSPDConnMapMsg& other);

  protected:
    // protected and unimplemented operator==(), to prevent accidental usage
    bool operator==(const BTSPDConnMapMsg&);

  public:
    BTSPDConnMapMsg(const char *name=NULL, int kind=0);
    BTSPDConnMapMsg(const BTSPDConnMapMsg& other);
    virtual ~BTSPDConnMapMsg();
    BTSPDConnMapMsg& operator=(const BTSPDConnMapMsg& other);
    virtual BTSPDConnMapMsg *dup() const {return new BTSPDConnMapMsg(*this);}
    virtual void parsimPack(cCommBuffer *b);
    virtual void parsimUnpack(cCommBuffer *b);

    // field getter/setter methods
    virtual const char * myIP() const;
    virtual void setMyIP(const char * myIP);
    virtual const char * remoteIP() const;
    virtual void setRemoteIP(const char * remoteIP);
};

inline void doPacking(cCommBuffer *b, BTSPDConnMapMsg& obj) {obj.parsimPack(b);}
inline void doUnpacking(cCommBuffer *b, BTSPDConnMapMsg& obj) {obj.parsimUnpack(b);}

/**
 * Class generated from <tt>applications/BitTorrentSPD/BTSPDConnMap.msg</tt> by opp_msgc.
 * <pre>
 * message BTSPDIPtoNameMappingMsg
 * {
 *     @omitGetVerb(true);
 *     string myIP;
 *     string myName;    
 * }
 * </pre>
 */
class BTSPDIPtoNameMappingMsg : public ::cMessage
{
  protected:
    opp_string myIP_var;
    opp_string myName_var;

  private:
    void copy(const BTSPDIPtoNameMappingMsg& other);

  protected:
    // protected and unimplemented operator==(), to prevent accidental usage
    bool operator==(const BTSPDIPtoNameMappingMsg&);

  public:
    BTSPDIPtoNameMappingMsg(const char *name=NULL, int kind=0);
    BTSPDIPtoNameMappingMsg(const BTSPDIPtoNameMappingMsg& other);
    virtual ~BTSPDIPtoNameMappingMsg();
    BTSPDIPtoNameMappingMsg& operator=(const BTSPDIPtoNameMappingMsg& other);
    virtual BTSPDIPtoNameMappingMsg *dup() const {return new BTSPDIPtoNameMappingMsg(*this);}
    virtual void parsimPack(cCommBuffer *b);
    virtual void parsimUnpack(cCommBuffer *b);

    // field getter/setter methods
    virtual const char * myIP() const;
    virtual void setMyIP(const char * myIP);
    virtual const char * myName() const;
    virtual void setMyName(const char * myName);
};

inline void doPacking(cCommBuffer *b, BTSPDIPtoNameMappingMsg& obj) {obj.parsimPack(b);}
inline void doUnpacking(cCommBuffer *b, BTSPDIPtoNameMappingMsg& obj) {obj.parsimUnpack(b);}


#endif // _BTSPDCONNMAP_M_H_
