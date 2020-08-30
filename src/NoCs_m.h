//
// Generated file, do not edit! Created by nedtool 5.6 from NoCs.msg.
//

#ifndef __NOCS_M_H
#define __NOCS_M_H

#if defined(__clang__)
#  pragma clang diagnostic ignored "-Wreserved-id-macro"
#endif
#include <omnetpp.h>

// nedtool version check
#define MSGC_VERSION 0x0506
#if (MSGC_VERSION!=OMNETPP_VERSION)
#    error Version mismatch! Probably this file was generated by an earlier version of nedtool: 'make clean' should help.
#endif



/**
 * Enum generated from <tt>NoCs.msg:18</tt> by nedtool.
 * <pre>
 * //
 * // Copyright (C) 2010-2011 Eitan Zahavi, The Technion EE Department
 * //
 * // This program is free software: you can redistribute it and/or modify
 * // it under the terms of the GNU Lesser General Public License as published by
 * // the Free Software Foundation, either version 3 of the License, or
 * // (at your option) any later version.
 * // 
 * // This program is distributed in the hope that it will be useful,
 * // but WITHOUT ANY WARRANTY; without even the implied warranty of
 * // MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * // GNU Lesser General Public License for more details.
 * // 
 * // You should have received a copy of the GNU Lesser General Public License
 * // along with this program.  If not, see http://www.gnu.org/licenses/.
 * //
 * enum NOC_MSGS
 * {
 *     NOC_FLIT_MSG = 1;
 *     NOC_CREDIT_MSG = 2;
 *     NOC_REQ_MSG = 3;
 *     NOC_GNT_MSG = 4;
 *     NOC_ACK_MSG = 5;
 *     NOC_POP_MSG = 7;
 *     NOC_GEN_MSG = 8;
 *     NOC_APP_MSG = 9;
 *     NOC_CLK_MSG = 10;
 * 
 * }
 * </pre>
 */
enum NOC_MSGS {
    NOC_FLIT_MSG = 1,
    NOC_CREDIT_MSG = 2,
    NOC_REQ_MSG = 3,
    NOC_GNT_MSG = 4,
    NOC_ACK_MSG = 5,
    NOC_POP_MSG = 7,
    NOC_GEN_MSG = 8,
    NOC_APP_MSG = 9,
    NOC_CLK_MSG = 10
};

/**
 * Enum generated from <tt>NoCs.msg:36</tt> by nedtool.
 * <pre>
 * ///////////////////////////////////////////////////////////////////////////
 * //
 * // MESSAGES THAT ARE AVAILABLE ON NOC WIRES (outside of the router)
 * //
 * enum NOC_FLIT_TYPES
 * {
 *     NOC_START_FLIT = 1;
 *     NOC_MID_FLIT = 2;
 *     NOC_END_FLIT = 3;
 * }
 * </pre>
 */
enum NOC_FLIT_TYPES {
    NOC_START_FLIT = 1,
    NOC_MID_FLIT = 2,
    NOC_END_FLIT = 3
};

/**
 * Class generated from <tt>NoCs.msg:43</tt> by nedtool.
 * <pre>
 * packet NoCFlitMsg
 * {
 *     int type;    // first middle end of packet
 *     int VC;      // the VC of the FLIT as on the wire
 *     int SL;      // the QoS SL for the FLIT
 *     int pktId;   // packet id globally unique
 *     int flits;   // number of flits in this message 
 *     int flitIdx; // index within the packet
 *     int srcId;
 *     int dstId;
 *     bool firstNet;
 *     simtime_t InjectTime; // the time the flit is injected to the NoC , i.e: when it leaves the source`s queue. 
 *     simtime_t FirstNetTime; // the time the flit is transimitted by a sched,  in order to mask source-router latency effects 
 * 
 * }
 * </pre>
 */
class NoCFlitMsg : public ::omnetpp::cPacket
{
  protected:
    int type;
    int VC;
    int SL;
    int pktId;
    int flits;
    int flitIdx;
    int srcId;
    int dstId;
    bool firstNet;
    ::omnetpp::simtime_t InjectTime;
    ::omnetpp::simtime_t FirstNetTime;

  private:
    void copy(const NoCFlitMsg& other);

  protected:
    // protected and unimplemented operator==(), to prevent accidental usage
    bool operator==(const NoCFlitMsg&);

  public:
    NoCFlitMsg(const char *name=nullptr, short kind=0);
    NoCFlitMsg(const NoCFlitMsg& other);
    virtual ~NoCFlitMsg();
    NoCFlitMsg& operator=(const NoCFlitMsg& other);
    virtual NoCFlitMsg *dup() const override {return new NoCFlitMsg(*this);}
    virtual void parsimPack(omnetpp::cCommBuffer *b) const override;
    virtual void parsimUnpack(omnetpp::cCommBuffer *b) override;

    // field getter/setter methods
    virtual int getType() const;
    virtual void setType(int type);
    virtual int getVC() const;
    virtual void setVC(int VC);
    virtual int getSL() const;
    virtual void setSL(int SL);
    virtual int getPktId() const;
    virtual void setPktId(int pktId);
    virtual int getFlits() const;
    virtual void setFlits(int flits);
    virtual int getFlitIdx() const;
    virtual void setFlitIdx(int flitIdx);
    virtual int getSrcId() const;
    virtual void setSrcId(int srcId);
    virtual int getDstId() const;
    virtual void setDstId(int dstId);
    virtual bool getFirstNet() const;
    virtual void setFirstNet(bool firstNet);
    virtual ::omnetpp::simtime_t getInjectTime() const;
    virtual void setInjectTime(::omnetpp::simtime_t InjectTime);
    virtual ::omnetpp::simtime_t getFirstNetTime() const;
    virtual void setFirstNetTime(::omnetpp::simtime_t FirstNetTime);
};

inline void doParsimPacking(omnetpp::cCommBuffer *b, const NoCFlitMsg& obj) {obj.parsimPack(b);}
inline void doParsimUnpacking(omnetpp::cCommBuffer *b, NoCFlitMsg& obj) {obj.parsimUnpack(b);}

/**
 * Class generated from <tt>NoCs.msg:59</tt> by nedtool.
 * <pre>
 * message NoCCreditMsg extends cMessage
 * {
 *     int VC;
 *     int flits;
 *     int msgs;
 * }
 * 
 * ///////////////////////////////////////////////////////////////////////////
 * //
 * // MESSAGES THAT ARE INTERNAL TO ROUTERS
 * //
 * </pre>
 */
class NoCCreditMsg : public ::omnetpp::cMessage
{
  protected:
    int VC;
    int flits;
    int msgs;

  private:
    void copy(const NoCCreditMsg& other);

  protected:
    // protected and unimplemented operator==(), to prevent accidental usage
    bool operator==(const NoCCreditMsg&);

  public:
    NoCCreditMsg(const char *name=nullptr, short kind=0);
    NoCCreditMsg(const NoCCreditMsg& other);
    virtual ~NoCCreditMsg();
    NoCCreditMsg& operator=(const NoCCreditMsg& other);
    virtual NoCCreditMsg *dup() const override {return new NoCCreditMsg(*this);}
    virtual void parsimPack(omnetpp::cCommBuffer *b) const override;
    virtual void parsimUnpack(omnetpp::cCommBuffer *b) override;

    // field getter/setter methods
    virtual int getVC() const;
    virtual void setVC(int VC);
    virtual int getFlits() const;
    virtual void setFlits(int flits);
    virtual int getMsgs() const;
    virtual void setMsgs(int msgs);
};

inline void doParsimPacking(omnetpp::cCommBuffer *b, const NoCCreditMsg& obj) {obj.parsimPack(b);}
inline void doParsimUnpacking(omnetpp::cCommBuffer *b, NoCCreditMsg& obj) {obj.parsimUnpack(b);}

/**
 * Class generated from <tt>NoCs.msg:72</tt> by nedtool.
 * <pre>
 * // InPort Request arbitratoin from scheduler 
 * message NoCReqMsg extends cMessage
 * {
 *     int outVC;      // the output VC to send on
 *     int inVC;       // the VC of the input buffer storing this packet
 *     int outPortNum; // the output port  
 *     int pktId;      // packet ID of the sent packet
 *     int numFlits;   // flits of the packet
 *     int numGranted; // number of flits granted
 *     int numAcked;   // number of flits acked 
 * 
 * }
 * </pre>
 */
class NoCReqMsg : public ::omnetpp::cMessage
{
  protected:
    int outVC;
    int inVC;
    int outPortNum;
    int pktId;
    int numFlits;
    int numGranted;
    int numAcked;

  private:
    void copy(const NoCReqMsg& other);

  protected:
    // protected and unimplemented operator==(), to prevent accidental usage
    bool operator==(const NoCReqMsg&);

  public:
    NoCReqMsg(const char *name=nullptr, short kind=0);
    NoCReqMsg(const NoCReqMsg& other);
    virtual ~NoCReqMsg();
    NoCReqMsg& operator=(const NoCReqMsg& other);
    virtual NoCReqMsg *dup() const override {return new NoCReqMsg(*this);}
    virtual void parsimPack(omnetpp::cCommBuffer *b) const override;
    virtual void parsimUnpack(omnetpp::cCommBuffer *b) override;

    // field getter/setter methods
    virtual int getOutVC() const;
    virtual void setOutVC(int outVC);
    virtual int getInVC() const;
    virtual void setInVC(int inVC);
    virtual int getOutPortNum() const;
    virtual void setOutPortNum(int outPortNum);
    virtual int getPktId() const;
    virtual void setPktId(int pktId);
    virtual int getNumFlits() const;
    virtual void setNumFlits(int numFlits);
    virtual int getNumGranted() const;
    virtual void setNumGranted(int numGranted);
    virtual int getNumAcked() const;
    virtual void setNumAcked(int numAcked);
};

inline void doParsimPacking(omnetpp::cCommBuffer *b, const NoCReqMsg& obj) {obj.parsimPack(b);}
inline void doParsimUnpacking(omnetpp::cCommBuffer *b, NoCReqMsg& obj) {obj.parsimUnpack(b);}

/**
 * Class generated from <tt>NoCs.msg:85</tt> by nedtool.
 * <pre>
 * // Scheduler Grant Arbitration to InPort
 * message NoCGntMsg extends cMessage
 * {
 *     int outVC;      // the output VC to send on
 *     int inVC;       // the input VC to take the flit from
 *     int outPortNum; // the output port  
 * 
 * }
 * </pre>
 */
class NoCGntMsg : public ::omnetpp::cMessage
{
  protected:
    int outVC;
    int inVC;
    int outPortNum;

  private:
    void copy(const NoCGntMsg& other);

  protected:
    // protected and unimplemented operator==(), to prevent accidental usage
    bool operator==(const NoCGntMsg&);

  public:
    NoCGntMsg(const char *name=nullptr, short kind=0);
    NoCGntMsg(const NoCGntMsg& other);
    virtual ~NoCGntMsg();
    NoCGntMsg& operator=(const NoCGntMsg& other);
    virtual NoCGntMsg *dup() const override {return new NoCGntMsg(*this);}
    virtual void parsimPack(omnetpp::cCommBuffer *b) const override;
    virtual void parsimUnpack(omnetpp::cCommBuffer *b) override;

    // field getter/setter methods
    virtual int getOutVC() const;
    virtual void setOutVC(int outVC);
    virtual int getInVC() const;
    virtual void setInVC(int inVC);
    virtual int getOutPortNum() const;
    virtual void setOutPortNum(int outPortNum);
};

inline void doParsimPacking(omnetpp::cCommBuffer *b, const NoCGntMsg& obj) {obj.parsimPack(b);}
inline void doParsimUnpacking(omnetpp::cCommBuffer *b, NoCGntMsg& obj) {obj.parsimUnpack(b);}

/**
 * Class generated from <tt>NoCs.msg:94</tt> by nedtool.
 * <pre>
 * // each grant must be either declined or accepted using this ACK message
 * message NoCAckMsg extends cMessage
 * {
 *     bool OK;        // grant can be declined but a response is a must ...
 *     int outVC;      // the output VC to send on
 *     int inVC;
 *     int outPortNum;
 * 
 * }
 * </pre>
 */
class NoCAckMsg : public ::omnetpp::cMessage
{
  protected:
    bool OK;
    int outVC;
    int inVC;
    int outPortNum;

  private:
    void copy(const NoCAckMsg& other);

  protected:
    // protected and unimplemented operator==(), to prevent accidental usage
    bool operator==(const NoCAckMsg&);

  public:
    NoCAckMsg(const char *name=nullptr, short kind=0);
    NoCAckMsg(const NoCAckMsg& other);
    virtual ~NoCAckMsg();
    NoCAckMsg& operator=(const NoCAckMsg& other);
    virtual NoCAckMsg *dup() const override {return new NoCAckMsg(*this);}
    virtual void parsimPack(omnetpp::cCommBuffer *b) const override;
    virtual void parsimUnpack(omnetpp::cCommBuffer *b) override;

    // field getter/setter methods
    virtual bool getOK() const;
    virtual void setOK(bool OK);
    virtual int getOutVC() const;
    virtual void setOutVC(int outVC);
    virtual int getInVC() const;
    virtual void setInVC(int inVC);
    virtual int getOutPortNum() const;
    virtual void setOutPortNum(int outPortNum);
};

inline void doParsimPacking(omnetpp::cCommBuffer *b, const NoCAckMsg& obj) {obj.parsimPack(b);}
inline void doParsimUnpacking(omnetpp::cCommBuffer *b, NoCAckMsg& obj) {obj.parsimUnpack(b);}

/**
 * Class generated from <tt>NoCs.msg:104</tt> by nedtool.
 * <pre>
 * // a pop from a particular VC and OP
 * message NoCPopMsg extends cMessage
 * {
 *     int VC;
 *     int outPortNum;
 * }
 * </pre>
 */
class NoCPopMsg : public ::omnetpp::cMessage
{
  protected:
    int VC;
    int outPortNum;

  private:
    void copy(const NoCPopMsg& other);

  protected:
    // protected and unimplemented operator==(), to prevent accidental usage
    bool operator==(const NoCPopMsg&);

  public:
    NoCPopMsg(const char *name=nullptr, short kind=0);
    NoCPopMsg(const NoCPopMsg& other);
    virtual ~NoCPopMsg();
    NoCPopMsg& operator=(const NoCPopMsg& other);
    virtual NoCPopMsg *dup() const override {return new NoCPopMsg(*this);}
    virtual void parsimPack(omnetpp::cCommBuffer *b) const override;
    virtual void parsimUnpack(omnetpp::cCommBuffer *b) override;

    // field getter/setter methods
    virtual int getVC() const;
    virtual void setVC(int VC);
    virtual int getOutPortNum() const;
    virtual void setOutPortNum(int outPortNum);
};

inline void doParsimPacking(omnetpp::cCommBuffer *b, const NoCPopMsg& obj) {obj.parsimPack(b);}
inline void doParsimUnpacking(omnetpp::cCommBuffer *b, NoCPopMsg& obj) {obj.parsimUnpack(b);}


#endif // ifndef __NOCS_M_H

