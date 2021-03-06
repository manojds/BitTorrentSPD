//
// Generated file, do not edit! Created by opp_msgc 4.2 from applications/BitTorrentSPD/BTHostIntrnlMsgsSPD.msg.
//

#ifndef _BTHOSTINTRNLMSGSSPD_M_H_
#define _BTHOSTINTRNLMSGSSPD_M_H_

#include <omnetpp.h>

// opp_msgc version check
#define MSGC_VERSION 0x0402
#if (MSGC_VERSION!=OMNETPP_VERSION)
#    error Version mismatch! Probably this file was generated by an earlier version of opp_msgc: 'make clean' should help.
#endif



/**
 * Class generated from <tt>applications/BitTorrentSPD/BTHostIntrnlMsgsSPD.msg</tt> by opp_msgc.
 * <pre>
 * message BTRequestTrackerCommSPD extends cMessage
 * {
 *     @omitGetVerb(true);
 *     bool downloader= true;
 *     bool seeder= false;
 *     
 *     
 *     bool	publishInPeerList;
 * }
 * </pre>
 */
class BTRequestTrackerCommSPD : public ::cMessage
{
  protected:
    bool downloader_var;
    bool seeder_var;
    bool publishInPeerList_var;

  private:
    void copy(const BTRequestTrackerCommSPD& other);

  protected:
    // protected and unimplemented operator==(), to prevent accidental usage
    bool operator==(const BTRequestTrackerCommSPD&);

  public:
    BTRequestTrackerCommSPD(const char *name=NULL, int kind=0);
    BTRequestTrackerCommSPD(const BTRequestTrackerCommSPD& other);
    virtual ~BTRequestTrackerCommSPD();
    BTRequestTrackerCommSPD& operator=(const BTRequestTrackerCommSPD& other);
    virtual BTRequestTrackerCommSPD *dup() const {return new BTRequestTrackerCommSPD(*this);}
    virtual void parsimPack(cCommBuffer *b);
    virtual void parsimUnpack(cCommBuffer *b);

    // field getter/setter methods
    virtual bool downloader() const;
    virtual void setDownloader(bool downloader);
    virtual bool seeder() const;
    virtual void setSeeder(bool seeder);
    virtual bool publishInPeerList() const;
    virtual void setPublishInPeerList(bool publishInPeerList);
};

inline void doPacking(cCommBuffer *b, BTRequestTrackerCommSPD& obj) {obj.parsimPack(b);}
inline void doUnpacking(cCommBuffer *b, BTRequestTrackerCommSPD& obj) {obj.parsimUnpack(b);}


#endif // _BTHOSTINTRNLMSGSSPD_M_H_
