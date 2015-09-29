//
// Generated file, do not edit! Created by opp_msgc 4.2 from applications/BitTorrentSPD/BTTrackerMsgSPD.msg.
//

#ifndef _BTTRACKERMSGSPD_M_H_
#define _BTTRACKERMSGSPD_M_H_

#include <omnetpp.h>

// opp_msgc version check
#define MSGC_VERSION 0x0402
#if (MSGC_VERSION!=OMNETPP_VERSION)
#    error Version mismatch! Probably this file was generated by an earlier version of opp_msgc: 'make clean' should help.
#endif

// cplusplus {{
#include "../BitTorrent/BTTrackerMsg_m.h"
// }}



/**
 * Class generated from <tt>applications/BitTorrentSPD/BTTrackerMsgSPD.msg</tt> by opp_msgc.
 * <pre>
 * packet BTTrackerMsgAnnounceSPD extends BTTrackerMsgAnnounce
 * {
 *     @omitGetVerb(true);
 *     double 	relayPeerRatio;
 *     bool	seeder;	
 *     				
 *     				
 * 	bool	isRelay = false; 
 * 
 * 	
 * 	bool	publishInPeerList;    				
 * }
 * </pre>
 */
class BTTrackerMsgAnnounceSPD : public ::BTTrackerMsgAnnounce
{
  protected:
    double relayPeerRatio_var;
    bool seeder_var;
    bool isRelay_var;
    bool publishInPeerList_var;

  private:
    void copy(const BTTrackerMsgAnnounceSPD& other);

  protected:
    // protected and unimplemented operator==(), to prevent accidental usage
    bool operator==(const BTTrackerMsgAnnounceSPD&);

  public:
    BTTrackerMsgAnnounceSPD(const char *name=NULL, int kind=0);
    BTTrackerMsgAnnounceSPD(const BTTrackerMsgAnnounceSPD& other);
    virtual ~BTTrackerMsgAnnounceSPD();
    BTTrackerMsgAnnounceSPD& operator=(const BTTrackerMsgAnnounceSPD& other);
    virtual BTTrackerMsgAnnounceSPD *dup() const {return new BTTrackerMsgAnnounceSPD(*this);}
    virtual void parsimPack(cCommBuffer *b);
    virtual void parsimUnpack(cCommBuffer *b);

    // field getter/setter methods
    virtual double relayPeerRatio() const;
    virtual void setRelayPeerRatio(double relayPeerRatio);
    virtual bool seeder() const;
    virtual void setSeeder(bool seeder);
    virtual bool isRelay() const;
    virtual void setIsRelay(bool isRelay);
    virtual bool publishInPeerList() const;
    virtual void setPublishInPeerList(bool publishInPeerList);
};

inline void doPacking(cCommBuffer *b, BTTrackerMsgAnnounceSPD& obj) {obj.parsimPack(b);}
inline void doUnpacking(cCommBuffer *b, BTTrackerMsgAnnounceSPD& obj) {obj.parsimUnpack(b);}


#endif // _BTTRACKERMSGSPD_M_H_
