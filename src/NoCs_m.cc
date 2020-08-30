//
// Generated file, do not edit! Created by nedtool 5.6 from NoCs.msg.
//

// Disable warnings about unused variables, empty switch stmts, etc:
#ifdef _MSC_VER
#  pragma warning(disable:4101)
#  pragma warning(disable:4065)
#endif

#if defined(__clang__)
#  pragma clang diagnostic ignored "-Wshadow"
#  pragma clang diagnostic ignored "-Wconversion"
#  pragma clang diagnostic ignored "-Wunused-parameter"
#  pragma clang diagnostic ignored "-Wc++98-compat"
#  pragma clang diagnostic ignored "-Wunreachable-code-break"
#  pragma clang diagnostic ignored "-Wold-style-cast"
#elif defined(__GNUC__)
#  pragma GCC diagnostic ignored "-Wshadow"
#  pragma GCC diagnostic ignored "-Wconversion"
#  pragma GCC diagnostic ignored "-Wunused-parameter"
#  pragma GCC diagnostic ignored "-Wold-style-cast"
#  pragma GCC diagnostic ignored "-Wsuggest-attribute=noreturn"
#  pragma GCC diagnostic ignored "-Wfloat-conversion"
#endif

#include <iostream>
#include <sstream>
#include "NoCs_m.h"

namespace omnetpp {

// Template pack/unpack rules. They are declared *after* a1l type-specific pack functions for multiple reasons.
// They are in the omnetpp namespace, to allow them to be found by argument-dependent lookup via the cCommBuffer argument

// Packing/unpacking an std::vector
template<typename T, typename A>
void doParsimPacking(omnetpp::cCommBuffer *buffer, const std::vector<T,A>& v)
{
    int n = v.size();
    doParsimPacking(buffer, n);
    for (int i = 0; i < n; i++)
        doParsimPacking(buffer, v[i]);
}

template<typename T, typename A>
void doParsimUnpacking(omnetpp::cCommBuffer *buffer, std::vector<T,A>& v)
{
    int n;
    doParsimUnpacking(buffer, n);
    v.resize(n);
    for (int i = 0; i < n; i++)
        doParsimUnpacking(buffer, v[i]);
}

// Packing/unpacking an std::list
template<typename T, typename A>
void doParsimPacking(omnetpp::cCommBuffer *buffer, const std::list<T,A>& l)
{
    doParsimPacking(buffer, (int)l.size());
    for (typename std::list<T,A>::const_iterator it = l.begin(); it != l.end(); ++it)
        doParsimPacking(buffer, (T&)*it);
}

template<typename T, typename A>
void doParsimUnpacking(omnetpp::cCommBuffer *buffer, std::list<T,A>& l)
{
    int n;
    doParsimUnpacking(buffer, n);
    for (int i=0; i<n; i++) {
        l.push_back(T());
        doParsimUnpacking(buffer, l.back());
    }
}

// Packing/unpacking an std::set
template<typename T, typename Tr, typename A>
void doParsimPacking(omnetpp::cCommBuffer *buffer, const std::set<T,Tr,A>& s)
{
    doParsimPacking(buffer, (int)s.size());
    for (typename std::set<T,Tr,A>::const_iterator it = s.begin(); it != s.end(); ++it)
        doParsimPacking(buffer, *it);
}

template<typename T, typename Tr, typename A>
void doParsimUnpacking(omnetpp::cCommBuffer *buffer, std::set<T,Tr,A>& s)
{
    int n;
    doParsimUnpacking(buffer, n);
    for (int i=0; i<n; i++) {
        T x;
        doParsimUnpacking(buffer, x);
        s.insert(x);
    }
}

// Packing/unpacking an std::map
template<typename K, typename V, typename Tr, typename A>
void doParsimPacking(omnetpp::cCommBuffer *buffer, const std::map<K,V,Tr,A>& m)
{
    doParsimPacking(buffer, (int)m.size());
    for (typename std::map<K,V,Tr,A>::const_iterator it = m.begin(); it != m.end(); ++it) {
        doParsimPacking(buffer, it->first);
        doParsimPacking(buffer, it->second);
    }
}

template<typename K, typename V, typename Tr, typename A>
void doParsimUnpacking(omnetpp::cCommBuffer *buffer, std::map<K,V,Tr,A>& m)
{
    int n;
    doParsimUnpacking(buffer, n);
    for (int i=0; i<n; i++) {
        K k; V v;
        doParsimUnpacking(buffer, k);
        doParsimUnpacking(buffer, v);
        m[k] = v;
    }
}

// Default pack/unpack function for arrays
template<typename T>
void doParsimArrayPacking(omnetpp::cCommBuffer *b, const T *t, int n)
{
    for (int i = 0; i < n; i++)
        doParsimPacking(b, t[i]);
}

template<typename T>
void doParsimArrayUnpacking(omnetpp::cCommBuffer *b, T *t, int n)
{
    for (int i = 0; i < n; i++)
        doParsimUnpacking(b, t[i]);
}

// Default rule to prevent compiler from choosing base class' doParsimPacking() function
template<typename T>
void doParsimPacking(omnetpp::cCommBuffer *, const T& t)
{
    throw omnetpp::cRuntimeError("Parsim error: No doParsimPacking() function for type %s", omnetpp::opp_typename(typeid(t)));
}

template<typename T>
void doParsimUnpacking(omnetpp::cCommBuffer *, T& t)
{
    throw omnetpp::cRuntimeError("Parsim error: No doParsimUnpacking() function for type %s", omnetpp::opp_typename(typeid(t)));
}

}  // namespace omnetpp


// forward
template<typename T, typename A>
std::ostream& operator<<(std::ostream& out, const std::vector<T,A>& vec);

// Template rule which fires if a struct or class doesn't have operator<<
template<typename T>
inline std::ostream& operator<<(std::ostream& out,const T&) {return out;}

// operator<< for std::vector<T>
template<typename T, typename A>
inline std::ostream& operator<<(std::ostream& out, const std::vector<T,A>& vec)
{
    out.put('{');
    for(typename std::vector<T,A>::const_iterator it = vec.begin(); it != vec.end(); ++it)
    {
        if (it != vec.begin()) {
            out.put(','); out.put(' ');
        }
        out << *it;
    }
    out.put('}');
    
    char buf[32];
    sprintf(buf, " (size=%u)", (unsigned int)vec.size());
    out.write(buf, strlen(buf));
    return out;
}

EXECUTE_ON_STARTUP(
    omnetpp::cEnum *e = omnetpp::cEnum::find("NOC_MSGS");
    if (!e) omnetpp::enums.getInstance()->add(e = new omnetpp::cEnum("NOC_MSGS"));
    e->insert(NOC_FLIT_MSG, "NOC_FLIT_MSG");
    e->insert(NOC_CREDIT_MSG, "NOC_CREDIT_MSG");
    e->insert(NOC_REQ_MSG, "NOC_REQ_MSG");
    e->insert(NOC_GNT_MSG, "NOC_GNT_MSG");
    e->insert(NOC_ACK_MSG, "NOC_ACK_MSG");
    e->insert(NOC_POP_MSG, "NOC_POP_MSG");
    e->insert(NOC_GEN_MSG, "NOC_GEN_MSG");
    e->insert(NOC_APP_MSG, "NOC_APP_MSG");
    e->insert(NOC_CLK_MSG, "NOC_CLK_MSG");
)

EXECUTE_ON_STARTUP(
    omnetpp::cEnum *e = omnetpp::cEnum::find("NOC_FLIT_TYPES");
    if (!e) omnetpp::enums.getInstance()->add(e = new omnetpp::cEnum("NOC_FLIT_TYPES"));
    e->insert(NOC_START_FLIT, "NOC_START_FLIT");
    e->insert(NOC_MID_FLIT, "NOC_MID_FLIT");
    e->insert(NOC_END_FLIT, "NOC_END_FLIT");
)

Register_Class(NoCFlitMsg)

NoCFlitMsg::NoCFlitMsg(const char *name, short kind) : ::omnetpp::cPacket(name,kind)
{
    this->type = 0;
    this->VC = 0;
    this->SL = 0;
    this->pktId = 0;
    this->flits = 0;
    this->flitIdx = 0;
    this->srcId = 0;
    this->dstId = 0;
    this->firstNet = false;
    this->InjectTime = 0;
    this->FirstNetTime = 0;
}

NoCFlitMsg::NoCFlitMsg(const NoCFlitMsg& other) : ::omnetpp::cPacket(other)
{
    copy(other);
}

NoCFlitMsg::~NoCFlitMsg()
{
}

NoCFlitMsg& NoCFlitMsg::operator=(const NoCFlitMsg& other)
{
    if (this==&other) return *this;
    ::omnetpp::cPacket::operator=(other);
    copy(other);
    return *this;
}

void NoCFlitMsg::copy(const NoCFlitMsg& other)
{
    this->type = other.type;
    this->VC = other.VC;
    this->SL = other.SL;
    this->pktId = other.pktId;
    this->flits = other.flits;
    this->flitIdx = other.flitIdx;
    this->srcId = other.srcId;
    this->dstId = other.dstId;
    this->firstNet = other.firstNet;
    this->InjectTime = other.InjectTime;
    this->FirstNetTime = other.FirstNetTime;
}

void NoCFlitMsg::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::omnetpp::cPacket::parsimPack(b);
    doParsimPacking(b,this->type);
    doParsimPacking(b,this->VC);
    doParsimPacking(b,this->SL);
    doParsimPacking(b,this->pktId);
    doParsimPacking(b,this->flits);
    doParsimPacking(b,this->flitIdx);
    doParsimPacking(b,this->srcId);
    doParsimPacking(b,this->dstId);
    doParsimPacking(b,this->firstNet);
    doParsimPacking(b,this->InjectTime);
    doParsimPacking(b,this->FirstNetTime);
}

void NoCFlitMsg::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::omnetpp::cPacket::parsimUnpack(b);
    doParsimUnpacking(b,this->type);
    doParsimUnpacking(b,this->VC);
    doParsimUnpacking(b,this->SL);
    doParsimUnpacking(b,this->pktId);
    doParsimUnpacking(b,this->flits);
    doParsimUnpacking(b,this->flitIdx);
    doParsimUnpacking(b,this->srcId);
    doParsimUnpacking(b,this->dstId);
    doParsimUnpacking(b,this->firstNet);
    doParsimUnpacking(b,this->InjectTime);
    doParsimUnpacking(b,this->FirstNetTime);
}

int NoCFlitMsg::getType() const
{
    return this->type;
}

void NoCFlitMsg::setType(int type)
{
    this->type = type;
}

int NoCFlitMsg::getVC() const
{
    return this->VC;
}

void NoCFlitMsg::setVC(int VC)
{
    this->VC = VC;
}

int NoCFlitMsg::getSL() const
{
    return this->SL;
}

void NoCFlitMsg::setSL(int SL)
{
    this->SL = SL;
}

int NoCFlitMsg::getPktId() const
{
    return this->pktId;
}

void NoCFlitMsg::setPktId(int pktId)
{
    this->pktId = pktId;
}

int NoCFlitMsg::getFlits() const
{
    return this->flits;
}

void NoCFlitMsg::setFlits(int flits)
{
    this->flits = flits;
}

int NoCFlitMsg::getFlitIdx() const
{
    return this->flitIdx;
}

void NoCFlitMsg::setFlitIdx(int flitIdx)
{
    this->flitIdx = flitIdx;
}

int NoCFlitMsg::getSrcId() const
{
    return this->srcId;
}

void NoCFlitMsg::setSrcId(int srcId)
{
    this->srcId = srcId;
}

int NoCFlitMsg::getDstId() const
{
    return this->dstId;
}

void NoCFlitMsg::setDstId(int dstId)
{
    this->dstId = dstId;
}

bool NoCFlitMsg::getFirstNet() const
{
    return this->firstNet;
}

void NoCFlitMsg::setFirstNet(bool firstNet)
{
    this->firstNet = firstNet;
}

::omnetpp::simtime_t NoCFlitMsg::getInjectTime() const
{
    return this->InjectTime;
}

void NoCFlitMsg::setInjectTime(::omnetpp::simtime_t InjectTime)
{
    this->InjectTime = InjectTime;
}

::omnetpp::simtime_t NoCFlitMsg::getFirstNetTime() const
{
    return this->FirstNetTime;
}

void NoCFlitMsg::setFirstNetTime(::omnetpp::simtime_t FirstNetTime)
{
    this->FirstNetTime = FirstNetTime;
}

class NoCFlitMsgDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertynames;
  public:
    NoCFlitMsgDescriptor();
    virtual ~NoCFlitMsgDescriptor();

    virtual bool doesSupport(omnetpp::cObject *obj) const override;
    virtual const char **getPropertyNames() const override;
    virtual const char *getProperty(const char *propertyname) const override;
    virtual int getFieldCount() const override;
    virtual const char *getFieldName(int field) const override;
    virtual int findField(const char *fieldName) const override;
    virtual unsigned int getFieldTypeFlags(int field) const override;
    virtual const char *getFieldTypeString(int field) const override;
    virtual const char **getFieldPropertyNames(int field) const override;
    virtual const char *getFieldProperty(int field, const char *propertyname) const override;
    virtual int getFieldArraySize(void *object, int field) const override;

    virtual const char *getFieldDynamicTypeString(void *object, int field, int i) const override;
    virtual std::string getFieldValueAsString(void *object, int field, int i) const override;
    virtual bool setFieldValueAsString(void *object, int field, int i, const char *value) const override;

    virtual const char *getFieldStructName(int field) const override;
    virtual void *getFieldStructValuePointer(void *object, int field, int i) const override;
};

Register_ClassDescriptor(NoCFlitMsgDescriptor)

NoCFlitMsgDescriptor::NoCFlitMsgDescriptor() : omnetpp::cClassDescriptor("NoCFlitMsg", "omnetpp::cPacket")
{
    propertynames = nullptr;
}

NoCFlitMsgDescriptor::~NoCFlitMsgDescriptor()
{
    delete[] propertynames;
}

bool NoCFlitMsgDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<NoCFlitMsg *>(obj)!=nullptr;
}

const char **NoCFlitMsgDescriptor::getPropertyNames() const
{
    if (!propertynames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
        const char **basenames = basedesc ? basedesc->getPropertyNames() : nullptr;
        propertynames = mergeLists(basenames, names);
    }
    return propertynames;
}

const char *NoCFlitMsgDescriptor::getProperty(const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : nullptr;
}

int NoCFlitMsgDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 11+basedesc->getFieldCount() : 11;
}

unsigned int NoCFlitMsgDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeFlags(field);
        field -= basedesc->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
    };
    return (field>=0 && field<11) ? fieldTypeFlags[field] : 0;
}

const char *NoCFlitMsgDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldName(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldNames[] = {
        "type",
        "VC",
        "SL",
        "pktId",
        "flits",
        "flitIdx",
        "srcId",
        "dstId",
        "firstNet",
        "InjectTime",
        "FirstNetTime",
    };
    return (field>=0 && field<11) ? fieldNames[field] : nullptr;
}

int NoCFlitMsgDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount() : 0;
    if (fieldName[0]=='t' && strcmp(fieldName, "type")==0) return base+0;
    if (fieldName[0]=='V' && strcmp(fieldName, "VC")==0) return base+1;
    if (fieldName[0]=='S' && strcmp(fieldName, "SL")==0) return base+2;
    if (fieldName[0]=='p' && strcmp(fieldName, "pktId")==0) return base+3;
    if (fieldName[0]=='f' && strcmp(fieldName, "flits")==0) return base+4;
    if (fieldName[0]=='f' && strcmp(fieldName, "flitIdx")==0) return base+5;
    if (fieldName[0]=='s' && strcmp(fieldName, "srcId")==0) return base+6;
    if (fieldName[0]=='d' && strcmp(fieldName, "dstId")==0) return base+7;
    if (fieldName[0]=='f' && strcmp(fieldName, "firstNet")==0) return base+8;
    if (fieldName[0]=='I' && strcmp(fieldName, "InjectTime")==0) return base+9;
    if (fieldName[0]=='F' && strcmp(fieldName, "FirstNetTime")==0) return base+10;
    return basedesc ? basedesc->findField(fieldName) : -1;
}

const char *NoCFlitMsgDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeString(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "int",
        "int",
        "int",
        "int",
        "int",
        "int",
        "int",
        "int",
        "bool",
        "simtime_t",
        "simtime_t",
    };
    return (field>=0 && field<11) ? fieldTypeStrings[field] : nullptr;
}

const char **NoCFlitMsgDescriptor::getFieldPropertyNames(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldPropertyNames(field);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

const char *NoCFlitMsgDescriptor::getFieldProperty(int field, const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldProperty(field, propertyname);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

int NoCFlitMsgDescriptor::getFieldArraySize(void *object, int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldArraySize(object, field);
        field -= basedesc->getFieldCount();
    }
    NoCFlitMsg *pp = (NoCFlitMsg *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

const char *NoCFlitMsgDescriptor::getFieldDynamicTypeString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldDynamicTypeString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    NoCFlitMsg *pp = (NoCFlitMsg *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string NoCFlitMsgDescriptor::getFieldValueAsString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldValueAsString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    NoCFlitMsg *pp = (NoCFlitMsg *)object; (void)pp;
    switch (field) {
        case 0: return long2string(pp->getType());
        case 1: return long2string(pp->getVC());
        case 2: return long2string(pp->getSL());
        case 3: return long2string(pp->getPktId());
        case 4: return long2string(pp->getFlits());
        case 5: return long2string(pp->getFlitIdx());
        case 6: return long2string(pp->getSrcId());
        case 7: return long2string(pp->getDstId());
        case 8: return bool2string(pp->getFirstNet());
        case 9: return simtime2string(pp->getInjectTime());
        case 10: return simtime2string(pp->getFirstNetTime());
        default: return "";
    }
}

bool NoCFlitMsgDescriptor::setFieldValueAsString(void *object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->setFieldValueAsString(object,field,i,value);
        field -= basedesc->getFieldCount();
    }
    NoCFlitMsg *pp = (NoCFlitMsg *)object; (void)pp;
    switch (field) {
        case 0: pp->setType(string2long(value)); return true;
        case 1: pp->setVC(string2long(value)); return true;
        case 2: pp->setSL(string2long(value)); return true;
        case 3: pp->setPktId(string2long(value)); return true;
        case 4: pp->setFlits(string2long(value)); return true;
        case 5: pp->setFlitIdx(string2long(value)); return true;
        case 6: pp->setSrcId(string2long(value)); return true;
        case 7: pp->setDstId(string2long(value)); return true;
        case 8: pp->setFirstNet(string2bool(value)); return true;
        case 9: pp->setInjectTime(string2simtime(value)); return true;
        case 10: pp->setFirstNetTime(string2simtime(value)); return true;
        default: return false;
    }
}

const char *NoCFlitMsgDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructName(field);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    };
}

void *NoCFlitMsgDescriptor::getFieldStructValuePointer(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructValuePointer(object, field, i);
        field -= basedesc->getFieldCount();
    }
    NoCFlitMsg *pp = (NoCFlitMsg *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

Register_Class(NoCCreditMsg)

NoCCreditMsg::NoCCreditMsg(const char *name, short kind) : ::omnetpp::cMessage(name,kind)
{
    this->VC = 0;
    this->flits = 0;
    this->msgs = 0;
}

NoCCreditMsg::NoCCreditMsg(const NoCCreditMsg& other) : ::omnetpp::cMessage(other)
{
    copy(other);
}

NoCCreditMsg::~NoCCreditMsg()
{
}

NoCCreditMsg& NoCCreditMsg::operator=(const NoCCreditMsg& other)
{
    if (this==&other) return *this;
    ::omnetpp::cMessage::operator=(other);
    copy(other);
    return *this;
}

void NoCCreditMsg::copy(const NoCCreditMsg& other)
{
    this->VC = other.VC;
    this->flits = other.flits;
    this->msgs = other.msgs;
}

void NoCCreditMsg::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::omnetpp::cMessage::parsimPack(b);
    doParsimPacking(b,this->VC);
    doParsimPacking(b,this->flits);
    doParsimPacking(b,this->msgs);
}

void NoCCreditMsg::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::omnetpp::cMessage::parsimUnpack(b);
    doParsimUnpacking(b,this->VC);
    doParsimUnpacking(b,this->flits);
    doParsimUnpacking(b,this->msgs);
}

int NoCCreditMsg::getVC() const
{
    return this->VC;
}

void NoCCreditMsg::setVC(int VC)
{
    this->VC = VC;
}

int NoCCreditMsg::getFlits() const
{
    return this->flits;
}

void NoCCreditMsg::setFlits(int flits)
{
    this->flits = flits;
}

int NoCCreditMsg::getMsgs() const
{
    return this->msgs;
}

void NoCCreditMsg::setMsgs(int msgs)
{
    this->msgs = msgs;
}

class NoCCreditMsgDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertynames;
  public:
    NoCCreditMsgDescriptor();
    virtual ~NoCCreditMsgDescriptor();

    virtual bool doesSupport(omnetpp::cObject *obj) const override;
    virtual const char **getPropertyNames() const override;
    virtual const char *getProperty(const char *propertyname) const override;
    virtual int getFieldCount() const override;
    virtual const char *getFieldName(int field) const override;
    virtual int findField(const char *fieldName) const override;
    virtual unsigned int getFieldTypeFlags(int field) const override;
    virtual const char *getFieldTypeString(int field) const override;
    virtual const char **getFieldPropertyNames(int field) const override;
    virtual const char *getFieldProperty(int field, const char *propertyname) const override;
    virtual int getFieldArraySize(void *object, int field) const override;

    virtual const char *getFieldDynamicTypeString(void *object, int field, int i) const override;
    virtual std::string getFieldValueAsString(void *object, int field, int i) const override;
    virtual bool setFieldValueAsString(void *object, int field, int i, const char *value) const override;

    virtual const char *getFieldStructName(int field) const override;
    virtual void *getFieldStructValuePointer(void *object, int field, int i) const override;
};

Register_ClassDescriptor(NoCCreditMsgDescriptor)

NoCCreditMsgDescriptor::NoCCreditMsgDescriptor() : omnetpp::cClassDescriptor("NoCCreditMsg", "omnetpp::cMessage")
{
    propertynames = nullptr;
}

NoCCreditMsgDescriptor::~NoCCreditMsgDescriptor()
{
    delete[] propertynames;
}

bool NoCCreditMsgDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<NoCCreditMsg *>(obj)!=nullptr;
}

const char **NoCCreditMsgDescriptor::getPropertyNames() const
{
    if (!propertynames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
        const char **basenames = basedesc ? basedesc->getPropertyNames() : nullptr;
        propertynames = mergeLists(basenames, names);
    }
    return propertynames;
}

const char *NoCCreditMsgDescriptor::getProperty(const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : nullptr;
}

int NoCCreditMsgDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 3+basedesc->getFieldCount() : 3;
}

unsigned int NoCCreditMsgDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeFlags(field);
        field -= basedesc->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
    };
    return (field>=0 && field<3) ? fieldTypeFlags[field] : 0;
}

const char *NoCCreditMsgDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldName(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldNames[] = {
        "VC",
        "flits",
        "msgs",
    };
    return (field>=0 && field<3) ? fieldNames[field] : nullptr;
}

int NoCCreditMsgDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount() : 0;
    if (fieldName[0]=='V' && strcmp(fieldName, "VC")==0) return base+0;
    if (fieldName[0]=='f' && strcmp(fieldName, "flits")==0) return base+1;
    if (fieldName[0]=='m' && strcmp(fieldName, "msgs")==0) return base+2;
    return basedesc ? basedesc->findField(fieldName) : -1;
}

const char *NoCCreditMsgDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeString(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "int",
        "int",
        "int",
    };
    return (field>=0 && field<3) ? fieldTypeStrings[field] : nullptr;
}

const char **NoCCreditMsgDescriptor::getFieldPropertyNames(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldPropertyNames(field);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

const char *NoCCreditMsgDescriptor::getFieldProperty(int field, const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldProperty(field, propertyname);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

int NoCCreditMsgDescriptor::getFieldArraySize(void *object, int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldArraySize(object, field);
        field -= basedesc->getFieldCount();
    }
    NoCCreditMsg *pp = (NoCCreditMsg *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

const char *NoCCreditMsgDescriptor::getFieldDynamicTypeString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldDynamicTypeString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    NoCCreditMsg *pp = (NoCCreditMsg *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string NoCCreditMsgDescriptor::getFieldValueAsString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldValueAsString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    NoCCreditMsg *pp = (NoCCreditMsg *)object; (void)pp;
    switch (field) {
        case 0: return long2string(pp->getVC());
        case 1: return long2string(pp->getFlits());
        case 2: return long2string(pp->getMsgs());
        default: return "";
    }
}

bool NoCCreditMsgDescriptor::setFieldValueAsString(void *object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->setFieldValueAsString(object,field,i,value);
        field -= basedesc->getFieldCount();
    }
    NoCCreditMsg *pp = (NoCCreditMsg *)object; (void)pp;
    switch (field) {
        case 0: pp->setVC(string2long(value)); return true;
        case 1: pp->setFlits(string2long(value)); return true;
        case 2: pp->setMsgs(string2long(value)); return true;
        default: return false;
    }
}

const char *NoCCreditMsgDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructName(field);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    };
}

void *NoCCreditMsgDescriptor::getFieldStructValuePointer(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructValuePointer(object, field, i);
        field -= basedesc->getFieldCount();
    }
    NoCCreditMsg *pp = (NoCCreditMsg *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

Register_Class(NoCReqMsg)

NoCReqMsg::NoCReqMsg(const char *name, short kind) : ::omnetpp::cMessage(name,kind)
{
    this->outVC = 0;
    this->inVC = 0;
    this->outPortNum = 0;
    this->pktId = 0;
    this->numFlits = 0;
    this->numGranted = 0;
    this->numAcked = 0;
}

NoCReqMsg::NoCReqMsg(const NoCReqMsg& other) : ::omnetpp::cMessage(other)
{
    copy(other);
}

NoCReqMsg::~NoCReqMsg()
{
}

NoCReqMsg& NoCReqMsg::operator=(const NoCReqMsg& other)
{
    if (this==&other) return *this;
    ::omnetpp::cMessage::operator=(other);
    copy(other);
    return *this;
}

void NoCReqMsg::copy(const NoCReqMsg& other)
{
    this->outVC = other.outVC;
    this->inVC = other.inVC;
    this->outPortNum = other.outPortNum;
    this->pktId = other.pktId;
    this->numFlits = other.numFlits;
    this->numGranted = other.numGranted;
    this->numAcked = other.numAcked;
}

void NoCReqMsg::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::omnetpp::cMessage::parsimPack(b);
    doParsimPacking(b,this->outVC);
    doParsimPacking(b,this->inVC);
    doParsimPacking(b,this->outPortNum);
    doParsimPacking(b,this->pktId);
    doParsimPacking(b,this->numFlits);
    doParsimPacking(b,this->numGranted);
    doParsimPacking(b,this->numAcked);
}

void NoCReqMsg::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::omnetpp::cMessage::parsimUnpack(b);
    doParsimUnpacking(b,this->outVC);
    doParsimUnpacking(b,this->inVC);
    doParsimUnpacking(b,this->outPortNum);
    doParsimUnpacking(b,this->pktId);
    doParsimUnpacking(b,this->numFlits);
    doParsimUnpacking(b,this->numGranted);
    doParsimUnpacking(b,this->numAcked);
}

int NoCReqMsg::getOutVC() const
{
    return this->outVC;
}

void NoCReqMsg::setOutVC(int outVC)
{
    this->outVC = outVC;
}

int NoCReqMsg::getInVC() const
{
    return this->inVC;
}

void NoCReqMsg::setInVC(int inVC)
{
    this->inVC = inVC;
}

int NoCReqMsg::getOutPortNum() const
{
    return this->outPortNum;
}

void NoCReqMsg::setOutPortNum(int outPortNum)
{
    this->outPortNum = outPortNum;
}

int NoCReqMsg::getPktId() const
{
    return this->pktId;
}

void NoCReqMsg::setPktId(int pktId)
{
    this->pktId = pktId;
}

int NoCReqMsg::getNumFlits() const
{
    return this->numFlits;
}

void NoCReqMsg::setNumFlits(int numFlits)
{
    this->numFlits = numFlits;
}

int NoCReqMsg::getNumGranted() const
{
    return this->numGranted;
}

void NoCReqMsg::setNumGranted(int numGranted)
{
    this->numGranted = numGranted;
}

int NoCReqMsg::getNumAcked() const
{
    return this->numAcked;
}

void NoCReqMsg::setNumAcked(int numAcked)
{
    this->numAcked = numAcked;
}

class NoCReqMsgDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertynames;
  public:
    NoCReqMsgDescriptor();
    virtual ~NoCReqMsgDescriptor();

    virtual bool doesSupport(omnetpp::cObject *obj) const override;
    virtual const char **getPropertyNames() const override;
    virtual const char *getProperty(const char *propertyname) const override;
    virtual int getFieldCount() const override;
    virtual const char *getFieldName(int field) const override;
    virtual int findField(const char *fieldName) const override;
    virtual unsigned int getFieldTypeFlags(int field) const override;
    virtual const char *getFieldTypeString(int field) const override;
    virtual const char **getFieldPropertyNames(int field) const override;
    virtual const char *getFieldProperty(int field, const char *propertyname) const override;
    virtual int getFieldArraySize(void *object, int field) const override;

    virtual const char *getFieldDynamicTypeString(void *object, int field, int i) const override;
    virtual std::string getFieldValueAsString(void *object, int field, int i) const override;
    virtual bool setFieldValueAsString(void *object, int field, int i, const char *value) const override;

    virtual const char *getFieldStructName(int field) const override;
    virtual void *getFieldStructValuePointer(void *object, int field, int i) const override;
};

Register_ClassDescriptor(NoCReqMsgDescriptor)

NoCReqMsgDescriptor::NoCReqMsgDescriptor() : omnetpp::cClassDescriptor("NoCReqMsg", "omnetpp::cMessage")
{
    propertynames = nullptr;
}

NoCReqMsgDescriptor::~NoCReqMsgDescriptor()
{
    delete[] propertynames;
}

bool NoCReqMsgDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<NoCReqMsg *>(obj)!=nullptr;
}

const char **NoCReqMsgDescriptor::getPropertyNames() const
{
    if (!propertynames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
        const char **basenames = basedesc ? basedesc->getPropertyNames() : nullptr;
        propertynames = mergeLists(basenames, names);
    }
    return propertynames;
}

const char *NoCReqMsgDescriptor::getProperty(const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : nullptr;
}

int NoCReqMsgDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 7+basedesc->getFieldCount() : 7;
}

unsigned int NoCReqMsgDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeFlags(field);
        field -= basedesc->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
    };
    return (field>=0 && field<7) ? fieldTypeFlags[field] : 0;
}

const char *NoCReqMsgDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldName(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldNames[] = {
        "outVC",
        "inVC",
        "outPortNum",
        "pktId",
        "numFlits",
        "numGranted",
        "numAcked",
    };
    return (field>=0 && field<7) ? fieldNames[field] : nullptr;
}

int NoCReqMsgDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount() : 0;
    if (fieldName[0]=='o' && strcmp(fieldName, "outVC")==0) return base+0;
    if (fieldName[0]=='i' && strcmp(fieldName, "inVC")==0) return base+1;
    if (fieldName[0]=='o' && strcmp(fieldName, "outPortNum")==0) return base+2;
    if (fieldName[0]=='p' && strcmp(fieldName, "pktId")==0) return base+3;
    if (fieldName[0]=='n' && strcmp(fieldName, "numFlits")==0) return base+4;
    if (fieldName[0]=='n' && strcmp(fieldName, "numGranted")==0) return base+5;
    if (fieldName[0]=='n' && strcmp(fieldName, "numAcked")==0) return base+6;
    return basedesc ? basedesc->findField(fieldName) : -1;
}

const char *NoCReqMsgDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeString(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "int",
        "int",
        "int",
        "int",
        "int",
        "int",
        "int",
    };
    return (field>=0 && field<7) ? fieldTypeStrings[field] : nullptr;
}

const char **NoCReqMsgDescriptor::getFieldPropertyNames(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldPropertyNames(field);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

const char *NoCReqMsgDescriptor::getFieldProperty(int field, const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldProperty(field, propertyname);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

int NoCReqMsgDescriptor::getFieldArraySize(void *object, int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldArraySize(object, field);
        field -= basedesc->getFieldCount();
    }
    NoCReqMsg *pp = (NoCReqMsg *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

const char *NoCReqMsgDescriptor::getFieldDynamicTypeString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldDynamicTypeString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    NoCReqMsg *pp = (NoCReqMsg *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string NoCReqMsgDescriptor::getFieldValueAsString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldValueAsString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    NoCReqMsg *pp = (NoCReqMsg *)object; (void)pp;
    switch (field) {
        case 0: return long2string(pp->getOutVC());
        case 1: return long2string(pp->getInVC());
        case 2: return long2string(pp->getOutPortNum());
        case 3: return long2string(pp->getPktId());
        case 4: return long2string(pp->getNumFlits());
        case 5: return long2string(pp->getNumGranted());
        case 6: return long2string(pp->getNumAcked());
        default: return "";
    }
}

bool NoCReqMsgDescriptor::setFieldValueAsString(void *object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->setFieldValueAsString(object,field,i,value);
        field -= basedesc->getFieldCount();
    }
    NoCReqMsg *pp = (NoCReqMsg *)object; (void)pp;
    switch (field) {
        case 0: pp->setOutVC(string2long(value)); return true;
        case 1: pp->setInVC(string2long(value)); return true;
        case 2: pp->setOutPortNum(string2long(value)); return true;
        case 3: pp->setPktId(string2long(value)); return true;
        case 4: pp->setNumFlits(string2long(value)); return true;
        case 5: pp->setNumGranted(string2long(value)); return true;
        case 6: pp->setNumAcked(string2long(value)); return true;
        default: return false;
    }
}

const char *NoCReqMsgDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructName(field);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    };
}

void *NoCReqMsgDescriptor::getFieldStructValuePointer(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructValuePointer(object, field, i);
        field -= basedesc->getFieldCount();
    }
    NoCReqMsg *pp = (NoCReqMsg *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

Register_Class(NoCGntMsg)

NoCGntMsg::NoCGntMsg(const char *name, short kind) : ::omnetpp::cMessage(name,kind)
{
    this->outVC = 0;
    this->inVC = 0;
    this->outPortNum = 0;
}

NoCGntMsg::NoCGntMsg(const NoCGntMsg& other) : ::omnetpp::cMessage(other)
{
    copy(other);
}

NoCGntMsg::~NoCGntMsg()
{
}

NoCGntMsg& NoCGntMsg::operator=(const NoCGntMsg& other)
{
    if (this==&other) return *this;
    ::omnetpp::cMessage::operator=(other);
    copy(other);
    return *this;
}

void NoCGntMsg::copy(const NoCGntMsg& other)
{
    this->outVC = other.outVC;
    this->inVC = other.inVC;
    this->outPortNum = other.outPortNum;
}

void NoCGntMsg::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::omnetpp::cMessage::parsimPack(b);
    doParsimPacking(b,this->outVC);
    doParsimPacking(b,this->inVC);
    doParsimPacking(b,this->outPortNum);
}

void NoCGntMsg::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::omnetpp::cMessage::parsimUnpack(b);
    doParsimUnpacking(b,this->outVC);
    doParsimUnpacking(b,this->inVC);
    doParsimUnpacking(b,this->outPortNum);
}

int NoCGntMsg::getOutVC() const
{
    return this->outVC;
}

void NoCGntMsg::setOutVC(int outVC)
{
    this->outVC = outVC;
}

int NoCGntMsg::getInVC() const
{
    return this->inVC;
}

void NoCGntMsg::setInVC(int inVC)
{
    this->inVC = inVC;
}

int NoCGntMsg::getOutPortNum() const
{
    return this->outPortNum;
}

void NoCGntMsg::setOutPortNum(int outPortNum)
{
    this->outPortNum = outPortNum;
}

class NoCGntMsgDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertynames;
  public:
    NoCGntMsgDescriptor();
    virtual ~NoCGntMsgDescriptor();

    virtual bool doesSupport(omnetpp::cObject *obj) const override;
    virtual const char **getPropertyNames() const override;
    virtual const char *getProperty(const char *propertyname) const override;
    virtual int getFieldCount() const override;
    virtual const char *getFieldName(int field) const override;
    virtual int findField(const char *fieldName) const override;
    virtual unsigned int getFieldTypeFlags(int field) const override;
    virtual const char *getFieldTypeString(int field) const override;
    virtual const char **getFieldPropertyNames(int field) const override;
    virtual const char *getFieldProperty(int field, const char *propertyname) const override;
    virtual int getFieldArraySize(void *object, int field) const override;

    virtual const char *getFieldDynamicTypeString(void *object, int field, int i) const override;
    virtual std::string getFieldValueAsString(void *object, int field, int i) const override;
    virtual bool setFieldValueAsString(void *object, int field, int i, const char *value) const override;

    virtual const char *getFieldStructName(int field) const override;
    virtual void *getFieldStructValuePointer(void *object, int field, int i) const override;
};

Register_ClassDescriptor(NoCGntMsgDescriptor)

NoCGntMsgDescriptor::NoCGntMsgDescriptor() : omnetpp::cClassDescriptor("NoCGntMsg", "omnetpp::cMessage")
{
    propertynames = nullptr;
}

NoCGntMsgDescriptor::~NoCGntMsgDescriptor()
{
    delete[] propertynames;
}

bool NoCGntMsgDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<NoCGntMsg *>(obj)!=nullptr;
}

const char **NoCGntMsgDescriptor::getPropertyNames() const
{
    if (!propertynames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
        const char **basenames = basedesc ? basedesc->getPropertyNames() : nullptr;
        propertynames = mergeLists(basenames, names);
    }
    return propertynames;
}

const char *NoCGntMsgDescriptor::getProperty(const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : nullptr;
}

int NoCGntMsgDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 3+basedesc->getFieldCount() : 3;
}

unsigned int NoCGntMsgDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeFlags(field);
        field -= basedesc->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
    };
    return (field>=0 && field<3) ? fieldTypeFlags[field] : 0;
}

const char *NoCGntMsgDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldName(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldNames[] = {
        "outVC",
        "inVC",
        "outPortNum",
    };
    return (field>=0 && field<3) ? fieldNames[field] : nullptr;
}

int NoCGntMsgDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount() : 0;
    if (fieldName[0]=='o' && strcmp(fieldName, "outVC")==0) return base+0;
    if (fieldName[0]=='i' && strcmp(fieldName, "inVC")==0) return base+1;
    if (fieldName[0]=='o' && strcmp(fieldName, "outPortNum")==0) return base+2;
    return basedesc ? basedesc->findField(fieldName) : -1;
}

const char *NoCGntMsgDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeString(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "int",
        "int",
        "int",
    };
    return (field>=0 && field<3) ? fieldTypeStrings[field] : nullptr;
}

const char **NoCGntMsgDescriptor::getFieldPropertyNames(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldPropertyNames(field);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

const char *NoCGntMsgDescriptor::getFieldProperty(int field, const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldProperty(field, propertyname);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

int NoCGntMsgDescriptor::getFieldArraySize(void *object, int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldArraySize(object, field);
        field -= basedesc->getFieldCount();
    }
    NoCGntMsg *pp = (NoCGntMsg *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

const char *NoCGntMsgDescriptor::getFieldDynamicTypeString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldDynamicTypeString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    NoCGntMsg *pp = (NoCGntMsg *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string NoCGntMsgDescriptor::getFieldValueAsString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldValueAsString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    NoCGntMsg *pp = (NoCGntMsg *)object; (void)pp;
    switch (field) {
        case 0: return long2string(pp->getOutVC());
        case 1: return long2string(pp->getInVC());
        case 2: return long2string(pp->getOutPortNum());
        default: return "";
    }
}

bool NoCGntMsgDescriptor::setFieldValueAsString(void *object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->setFieldValueAsString(object,field,i,value);
        field -= basedesc->getFieldCount();
    }
    NoCGntMsg *pp = (NoCGntMsg *)object; (void)pp;
    switch (field) {
        case 0: pp->setOutVC(string2long(value)); return true;
        case 1: pp->setInVC(string2long(value)); return true;
        case 2: pp->setOutPortNum(string2long(value)); return true;
        default: return false;
    }
}

const char *NoCGntMsgDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructName(field);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    };
}

void *NoCGntMsgDescriptor::getFieldStructValuePointer(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructValuePointer(object, field, i);
        field -= basedesc->getFieldCount();
    }
    NoCGntMsg *pp = (NoCGntMsg *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

Register_Class(NoCAckMsg)

NoCAckMsg::NoCAckMsg(const char *name, short kind) : ::omnetpp::cMessage(name,kind)
{
    this->OK = false;
    this->outVC = 0;
    this->inVC = 0;
    this->outPortNum = 0;
}

NoCAckMsg::NoCAckMsg(const NoCAckMsg& other) : ::omnetpp::cMessage(other)
{
    copy(other);
}

NoCAckMsg::~NoCAckMsg()
{
}

NoCAckMsg& NoCAckMsg::operator=(const NoCAckMsg& other)
{
    if (this==&other) return *this;
    ::omnetpp::cMessage::operator=(other);
    copy(other);
    return *this;
}

void NoCAckMsg::copy(const NoCAckMsg& other)
{
    this->OK = other.OK;
    this->outVC = other.outVC;
    this->inVC = other.inVC;
    this->outPortNum = other.outPortNum;
}

void NoCAckMsg::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::omnetpp::cMessage::parsimPack(b);
    doParsimPacking(b,this->OK);
    doParsimPacking(b,this->outVC);
    doParsimPacking(b,this->inVC);
    doParsimPacking(b,this->outPortNum);
}

void NoCAckMsg::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::omnetpp::cMessage::parsimUnpack(b);
    doParsimUnpacking(b,this->OK);
    doParsimUnpacking(b,this->outVC);
    doParsimUnpacking(b,this->inVC);
    doParsimUnpacking(b,this->outPortNum);
}

bool NoCAckMsg::getOK() const
{
    return this->OK;
}

void NoCAckMsg::setOK(bool OK)
{
    this->OK = OK;
}

int NoCAckMsg::getOutVC() const
{
    return this->outVC;
}

void NoCAckMsg::setOutVC(int outVC)
{
    this->outVC = outVC;
}

int NoCAckMsg::getInVC() const
{
    return this->inVC;
}

void NoCAckMsg::setInVC(int inVC)
{
    this->inVC = inVC;
}

int NoCAckMsg::getOutPortNum() const
{
    return this->outPortNum;
}

void NoCAckMsg::setOutPortNum(int outPortNum)
{
    this->outPortNum = outPortNum;
}

class NoCAckMsgDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertynames;
  public:
    NoCAckMsgDescriptor();
    virtual ~NoCAckMsgDescriptor();

    virtual bool doesSupport(omnetpp::cObject *obj) const override;
    virtual const char **getPropertyNames() const override;
    virtual const char *getProperty(const char *propertyname) const override;
    virtual int getFieldCount() const override;
    virtual const char *getFieldName(int field) const override;
    virtual int findField(const char *fieldName) const override;
    virtual unsigned int getFieldTypeFlags(int field) const override;
    virtual const char *getFieldTypeString(int field) const override;
    virtual const char **getFieldPropertyNames(int field) const override;
    virtual const char *getFieldProperty(int field, const char *propertyname) const override;
    virtual int getFieldArraySize(void *object, int field) const override;

    virtual const char *getFieldDynamicTypeString(void *object, int field, int i) const override;
    virtual std::string getFieldValueAsString(void *object, int field, int i) const override;
    virtual bool setFieldValueAsString(void *object, int field, int i, const char *value) const override;

    virtual const char *getFieldStructName(int field) const override;
    virtual void *getFieldStructValuePointer(void *object, int field, int i) const override;
};

Register_ClassDescriptor(NoCAckMsgDescriptor)

NoCAckMsgDescriptor::NoCAckMsgDescriptor() : omnetpp::cClassDescriptor("NoCAckMsg", "omnetpp::cMessage")
{
    propertynames = nullptr;
}

NoCAckMsgDescriptor::~NoCAckMsgDescriptor()
{
    delete[] propertynames;
}

bool NoCAckMsgDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<NoCAckMsg *>(obj)!=nullptr;
}

const char **NoCAckMsgDescriptor::getPropertyNames() const
{
    if (!propertynames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
        const char **basenames = basedesc ? basedesc->getPropertyNames() : nullptr;
        propertynames = mergeLists(basenames, names);
    }
    return propertynames;
}

const char *NoCAckMsgDescriptor::getProperty(const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : nullptr;
}

int NoCAckMsgDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 4+basedesc->getFieldCount() : 4;
}

unsigned int NoCAckMsgDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeFlags(field);
        field -= basedesc->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
    };
    return (field>=0 && field<4) ? fieldTypeFlags[field] : 0;
}

const char *NoCAckMsgDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldName(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldNames[] = {
        "OK",
        "outVC",
        "inVC",
        "outPortNum",
    };
    return (field>=0 && field<4) ? fieldNames[field] : nullptr;
}

int NoCAckMsgDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount() : 0;
    if (fieldName[0]=='O' && strcmp(fieldName, "OK")==0) return base+0;
    if (fieldName[0]=='o' && strcmp(fieldName, "outVC")==0) return base+1;
    if (fieldName[0]=='i' && strcmp(fieldName, "inVC")==0) return base+2;
    if (fieldName[0]=='o' && strcmp(fieldName, "outPortNum")==0) return base+3;
    return basedesc ? basedesc->findField(fieldName) : -1;
}

const char *NoCAckMsgDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeString(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "bool",
        "int",
        "int",
        "int",
    };
    return (field>=0 && field<4) ? fieldTypeStrings[field] : nullptr;
}

const char **NoCAckMsgDescriptor::getFieldPropertyNames(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldPropertyNames(field);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

const char *NoCAckMsgDescriptor::getFieldProperty(int field, const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldProperty(field, propertyname);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

int NoCAckMsgDescriptor::getFieldArraySize(void *object, int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldArraySize(object, field);
        field -= basedesc->getFieldCount();
    }
    NoCAckMsg *pp = (NoCAckMsg *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

const char *NoCAckMsgDescriptor::getFieldDynamicTypeString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldDynamicTypeString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    NoCAckMsg *pp = (NoCAckMsg *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string NoCAckMsgDescriptor::getFieldValueAsString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldValueAsString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    NoCAckMsg *pp = (NoCAckMsg *)object; (void)pp;
    switch (field) {
        case 0: return bool2string(pp->getOK());
        case 1: return long2string(pp->getOutVC());
        case 2: return long2string(pp->getInVC());
        case 3: return long2string(pp->getOutPortNum());
        default: return "";
    }
}

bool NoCAckMsgDescriptor::setFieldValueAsString(void *object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->setFieldValueAsString(object,field,i,value);
        field -= basedesc->getFieldCount();
    }
    NoCAckMsg *pp = (NoCAckMsg *)object; (void)pp;
    switch (field) {
        case 0: pp->setOK(string2bool(value)); return true;
        case 1: pp->setOutVC(string2long(value)); return true;
        case 2: pp->setInVC(string2long(value)); return true;
        case 3: pp->setOutPortNum(string2long(value)); return true;
        default: return false;
    }
}

const char *NoCAckMsgDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructName(field);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    };
}

void *NoCAckMsgDescriptor::getFieldStructValuePointer(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructValuePointer(object, field, i);
        field -= basedesc->getFieldCount();
    }
    NoCAckMsg *pp = (NoCAckMsg *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

Register_Class(NoCPopMsg)

NoCPopMsg::NoCPopMsg(const char *name, short kind) : ::omnetpp::cMessage(name,kind)
{
    this->VC = 0;
    this->outPortNum = 0;
}

NoCPopMsg::NoCPopMsg(const NoCPopMsg& other) : ::omnetpp::cMessage(other)
{
    copy(other);
}

NoCPopMsg::~NoCPopMsg()
{
}

NoCPopMsg& NoCPopMsg::operator=(const NoCPopMsg& other)
{
    if (this==&other) return *this;
    ::omnetpp::cMessage::operator=(other);
    copy(other);
    return *this;
}

void NoCPopMsg::copy(const NoCPopMsg& other)
{
    this->VC = other.VC;
    this->outPortNum = other.outPortNum;
}

void NoCPopMsg::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::omnetpp::cMessage::parsimPack(b);
    doParsimPacking(b,this->VC);
    doParsimPacking(b,this->outPortNum);
}

void NoCPopMsg::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::omnetpp::cMessage::parsimUnpack(b);
    doParsimUnpacking(b,this->VC);
    doParsimUnpacking(b,this->outPortNum);
}

int NoCPopMsg::getVC() const
{
    return this->VC;
}

void NoCPopMsg::setVC(int VC)
{
    this->VC = VC;
}

int NoCPopMsg::getOutPortNum() const
{
    return this->outPortNum;
}

void NoCPopMsg::setOutPortNum(int outPortNum)
{
    this->outPortNum = outPortNum;
}

class NoCPopMsgDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertynames;
  public:
    NoCPopMsgDescriptor();
    virtual ~NoCPopMsgDescriptor();

    virtual bool doesSupport(omnetpp::cObject *obj) const override;
    virtual const char **getPropertyNames() const override;
    virtual const char *getProperty(const char *propertyname) const override;
    virtual int getFieldCount() const override;
    virtual const char *getFieldName(int field) const override;
    virtual int findField(const char *fieldName) const override;
    virtual unsigned int getFieldTypeFlags(int field) const override;
    virtual const char *getFieldTypeString(int field) const override;
    virtual const char **getFieldPropertyNames(int field) const override;
    virtual const char *getFieldProperty(int field, const char *propertyname) const override;
    virtual int getFieldArraySize(void *object, int field) const override;

    virtual const char *getFieldDynamicTypeString(void *object, int field, int i) const override;
    virtual std::string getFieldValueAsString(void *object, int field, int i) const override;
    virtual bool setFieldValueAsString(void *object, int field, int i, const char *value) const override;

    virtual const char *getFieldStructName(int field) const override;
    virtual void *getFieldStructValuePointer(void *object, int field, int i) const override;
};

Register_ClassDescriptor(NoCPopMsgDescriptor)

NoCPopMsgDescriptor::NoCPopMsgDescriptor() : omnetpp::cClassDescriptor("NoCPopMsg", "omnetpp::cMessage")
{
    propertynames = nullptr;
}

NoCPopMsgDescriptor::~NoCPopMsgDescriptor()
{
    delete[] propertynames;
}

bool NoCPopMsgDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<NoCPopMsg *>(obj)!=nullptr;
}

const char **NoCPopMsgDescriptor::getPropertyNames() const
{
    if (!propertynames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
        const char **basenames = basedesc ? basedesc->getPropertyNames() : nullptr;
        propertynames = mergeLists(basenames, names);
    }
    return propertynames;
}

const char *NoCPopMsgDescriptor::getProperty(const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : nullptr;
}

int NoCPopMsgDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 2+basedesc->getFieldCount() : 2;
}

unsigned int NoCPopMsgDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeFlags(field);
        field -= basedesc->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,
        FD_ISEDITABLE,
    };
    return (field>=0 && field<2) ? fieldTypeFlags[field] : 0;
}

const char *NoCPopMsgDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldName(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldNames[] = {
        "VC",
        "outPortNum",
    };
    return (field>=0 && field<2) ? fieldNames[field] : nullptr;
}

int NoCPopMsgDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount() : 0;
    if (fieldName[0]=='V' && strcmp(fieldName, "VC")==0) return base+0;
    if (fieldName[0]=='o' && strcmp(fieldName, "outPortNum")==0) return base+1;
    return basedesc ? basedesc->findField(fieldName) : -1;
}

const char *NoCPopMsgDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeString(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "int",
        "int",
    };
    return (field>=0 && field<2) ? fieldTypeStrings[field] : nullptr;
}

const char **NoCPopMsgDescriptor::getFieldPropertyNames(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldPropertyNames(field);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

const char *NoCPopMsgDescriptor::getFieldProperty(int field, const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldProperty(field, propertyname);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

int NoCPopMsgDescriptor::getFieldArraySize(void *object, int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldArraySize(object, field);
        field -= basedesc->getFieldCount();
    }
    NoCPopMsg *pp = (NoCPopMsg *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

const char *NoCPopMsgDescriptor::getFieldDynamicTypeString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldDynamicTypeString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    NoCPopMsg *pp = (NoCPopMsg *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string NoCPopMsgDescriptor::getFieldValueAsString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldValueAsString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    NoCPopMsg *pp = (NoCPopMsg *)object; (void)pp;
    switch (field) {
        case 0: return long2string(pp->getVC());
        case 1: return long2string(pp->getOutPortNum());
        default: return "";
    }
}

bool NoCPopMsgDescriptor::setFieldValueAsString(void *object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->setFieldValueAsString(object,field,i,value);
        field -= basedesc->getFieldCount();
    }
    NoCPopMsg *pp = (NoCPopMsg *)object; (void)pp;
    switch (field) {
        case 0: pp->setVC(string2long(value)); return true;
        case 1: pp->setOutPortNum(string2long(value)); return true;
        default: return false;
    }
}

const char *NoCPopMsgDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructName(field);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    };
}

void *NoCPopMsgDescriptor::getFieldStructValuePointer(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructValuePointer(object, field, i);
        field -= basedesc->getFieldCount();
    }
    NoCPopMsg *pp = (NoCPopMsg *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}


