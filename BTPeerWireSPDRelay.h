/*
 * BTPeerWireBaseRelay.h
 *
 *  Created on: Jan 21, 2015
 *      Author: manojd
 */

#ifndef BTPEERWIREBASERELAY_H_
#define BTPEERWIREBASERELAY_H_
#include "BTPeerWireSPD.h"
#include <map>

#define INTERNAL_TRACKER_REALY_COM_MSG                  251



class INET_API BTPeerWireSPDRelay :public BTPeerWireSPD
{
public:
    BTPeerWireSPDRelay();
    virtual ~BTPeerWireSPDRelay();

    virtual void beADownloader();
    virtual void setPatchInfo(const std::string & _sPatchInfo);
    bool    isPatchInfoAvailable() {return b_PatchInfoAvailable; }

    virtual void startParticipationInSwarm();


    virtual void checkRcvdConnIsViable(const PEER & peer);


protected:
    /* Redefined methods from BTPeerWireSPD */
    virtual void initialize();

    virtual void doStartNode();

    virtual void beActiveInSwarm();
    virtual void beIncativeInSwarm();
    virtual void scheduleRandomExit();

    virtual void handleMessage(cMessage *msg);

    virtual void handleSelfMessage(cMessage* msg);
    virtual void scheduleTrackerCommAt(simtime_t t);

    virtual cMessage * createTrackerCommMsg();

    virtual void notifynodeCreationToStatModule();

    virtual void newConnectionFromPeerEstablished(PEER peer, TCPServerThreadBase* thread);
    virtual void newConnectionToPeerEstablished(PEER peer, TCPServerThreadBase* thread);
    virtual void connectionLostFromPeer(PEER peer, bool isActiveConn);


    /* End of redefined methods from BTPeerWireBase */


    virtual void pauseChokingAlgos();

    virtual void startTrackerComm();
    virtual void stopTrackerComm();

    virtual void notifyNodeLeaveToStatModule();

    virtual void writeStats();

    const char* toString(int);

private:
    void handleMsgFromRelayTracker(cMessage *msg);


    //flag which indicates whether relay peer is currently participating in the swarm
    bool                    b_isParticipatingInSwarm;
    //flag which indicates at some point relay peer has participated in the swarm
    bool                    b_RelayStarted;
    bool                    b_Downloader;
    bool                    b_PatchInfoAvailable;

    cMessage*               evtRelayTrackerComm;   //Timer to schedule communication with the Tracker for Relay purposes
    std::map<IPvXAddress, PEER>   initiatedPeers;     //Peer who initiated connections to this relay peer

};

#endif /* BTPEERWIREBASERELAY_H_ */
