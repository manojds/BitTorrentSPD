//
// Generated file, do not edit! Created by opp_msgc 4.2 from applications/BitTorrentSPD/BTSPDPeerBlackListReqMsg.msg.
//

// Disable warnings about unused variables, empty switch stmts, etc:
#ifdef _MSC_VER
#  pragma warning(disable:4101)
#  pragma warning(disable:4065)
#endif

#include <iostream>
#include <sstream>
#include "BTSPDPeerBlackListReqMsg_m.h"

// Template rule which fires if a struct or class doesn't have operator<<
template<typename T>
std::ostream& operator<<(std::ostream& out,const T&) {return out;}

// Another default rule (prevents compiler from choosing base class' doPacking())
template<typename T>
void doPacking(cCommBuffer *, T& t) {
    throw cRuntimeError("Parsim error: no doPacking() function for type %s or its base class (check .msg and _m.cc/h files!)",opp_typename(typeid(t)));
}

template<typename T>
void doUnpacking(cCommBuffer *, T& t) {
    throw cRuntimeError("Parsim error: no doUnpacking() function for type %s or its base class (check .msg and _m.cc/h files!)",opp_typename(typeid(t)));
}




Register_Class(BTSPDPeerBlackListReqMsg);

BTSPDPeerBlackListReqMsg::BTSPDPeerBlackListReqMsg(const char *name, int kind) : cPacket(name,kind)
{
    attackers_arraysize = 0;
    this->attackers_var = 0;
}

BTSPDPeerBlackListReqMsg::BTSPDPeerBlackListReqMsg(const BTSPDPeerBlackListReqMsg& other) : cPacket(other)
{
    attackers_arraysize = 0;
    this->attackers_var = 0;
    copy(other);
}

BTSPDPeerBlackListReqMsg::~BTSPDPeerBlackListReqMsg()
{
    delete [] attackers_var;
}

BTSPDPeerBlackListReqMsg& BTSPDPeerBlackListReqMsg::operator=(const BTSPDPeerBlackListReqMsg& other)
{
    if (this==&other) return *this;
    cPacket::operator=(other);
    copy(other);
    return *this;
}

void BTSPDPeerBlackListReqMsg::copy(const BTSPDPeerBlackListReqMsg& other)
{
    delete [] this->attackers_var;
    this->attackers_var = (other.attackers_arraysize==0) ? NULL : new opp_string[other.attackers_arraysize];
    attackers_arraysize = other.attackers_arraysize;
    for (unsigned int i=0; i<attackers_arraysize; i++)
        this->attackers_var[i] = other.attackers_var[i];
}

void BTSPDPeerBlackListReqMsg::parsimPack(cCommBuffer *b)
{
    cPacket::parsimPack(b);
    b->pack(attackers_arraysize);
    doPacking(b,this->attackers_var,attackers_arraysize);
}

void BTSPDPeerBlackListReqMsg::parsimUnpack(cCommBuffer *b)
{
    cPacket::parsimUnpack(b);
    delete [] this->attackers_var;
    b->unpack(attackers_arraysize);
    if (attackers_arraysize==0) {
        this->attackers_var = 0;
    } else {
        this->attackers_var = new opp_string[attackers_arraysize];
        doUnpacking(b,this->attackers_var,attackers_arraysize);
    }
}

void BTSPDPeerBlackListReqMsg::setAttackersArraySize(unsigned int size)
{
    opp_string *attackers_var2 = (size==0) ? NULL : new opp_string[size];
    unsigned int sz = attackers_arraysize < size ? attackers_arraysize : size;
    for (unsigned int i=0; i<sz; i++)
        attackers_var2[i] = this->attackers_var[i];
    for (unsigned int i=sz; i<size; i++)
        attackers_var2[i] = 0;
    attackers_arraysize = size;
    delete [] this->attackers_var;
    this->attackers_var = attackers_var2;
}

unsigned int BTSPDPeerBlackListReqMsg::getAttackersArraySize() const
{
    return attackers_arraysize;
}

const char * BTSPDPeerBlackListReqMsg::getAttackers(unsigned int k) const
{
    if (k>=attackers_arraysize) throw cRuntimeError("Array of size %d indexed by %d", attackers_arraysize, k);
    return attackers_var[k].c_str();
}

void BTSPDPeerBlackListReqMsg::setAttackers(unsigned int k, const char * attackers)
{
    if (k>=attackers_arraysize) throw cRuntimeError("Array of size %d indexed by %d", attackers_arraysize, k);
    this->attackers_var[k] = attackers;
}

class BTSPDPeerBlackListReqMsgDescriptor : public cClassDescriptor
{
  public:
    BTSPDPeerBlackListReqMsgDescriptor();
    virtual ~BTSPDPeerBlackListReqMsgDescriptor();

    virtual bool doesSupport(cObject *obj) const;
    virtual const char *getProperty(const char *propertyname) const;
    virtual int getFieldCount(void *object) const;
    virtual const char *getFieldName(void *object, int field) const;
    virtual int findField(void *object, const char *fieldName) const;
    virtual unsigned int getFieldTypeFlags(void *object, int field) const;
    virtual const char *getFieldTypeString(void *object, int field) const;
    virtual const char *getFieldProperty(void *object, int field, const char *propertyname) const;
    virtual int getArraySize(void *object, int field) const;

    virtual std::string getFieldAsString(void *object, int field, int i) const;
    virtual bool setFieldAsString(void *object, int field, int i, const char *value) const;

    virtual const char *getFieldStructName(void *object, int field) const;
    virtual void *getFieldStructPointer(void *object, int field, int i) const;
};

Register_ClassDescriptor(BTSPDPeerBlackListReqMsgDescriptor);

BTSPDPeerBlackListReqMsgDescriptor::BTSPDPeerBlackListReqMsgDescriptor() : cClassDescriptor("BTSPDPeerBlackListReqMsg", "cPacket")
{
}

BTSPDPeerBlackListReqMsgDescriptor::~BTSPDPeerBlackListReqMsgDescriptor()
{
}

bool BTSPDPeerBlackListReqMsgDescriptor::doesSupport(cObject *obj) const
{
    return dynamic_cast<BTSPDPeerBlackListReqMsg *>(obj)!=NULL;
}

const char *BTSPDPeerBlackListReqMsgDescriptor::getProperty(const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : NULL;
}

int BTSPDPeerBlackListReqMsgDescriptor::getFieldCount(void *object) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 1+basedesc->getFieldCount(object) : 1;
}

unsigned int BTSPDPeerBlackListReqMsgDescriptor::getFieldTypeFlags(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeFlags(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISARRAY | FD_ISEDITABLE,
    };
    return (field>=0 && field<1) ? fieldTypeFlags[field] : 0;
}

const char *BTSPDPeerBlackListReqMsgDescriptor::getFieldName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldNames[] = {
        "attackers",
    };
    return (field>=0 && field<1) ? fieldNames[field] : NULL;
}

int BTSPDPeerBlackListReqMsgDescriptor::findField(void *object, const char *fieldName) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount(object) : 0;
    if (fieldName[0]=='a' && strcmp(fieldName, "attackers")==0) return base+0;
    return basedesc ? basedesc->findField(object, fieldName) : -1;
}

const char *BTSPDPeerBlackListReqMsgDescriptor::getFieldTypeString(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeString(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldTypeStrings[] = {
        "string",
    };
    return (field>=0 && field<1) ? fieldTypeStrings[field] : NULL;
}

const char *BTSPDPeerBlackListReqMsgDescriptor::getFieldProperty(void *object, int field, const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldProperty(object, field, propertyname);
        field -= basedesc->getFieldCount(object);
    }
    switch (field) {
        default: return NULL;
    }
}

int BTSPDPeerBlackListReqMsgDescriptor::getArraySize(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getArraySize(object, field);
        field -= basedesc->getFieldCount(object);
    }
    BTSPDPeerBlackListReqMsg *pp = (BTSPDPeerBlackListReqMsg *)object; (void)pp;
    switch (field) {
        case 0: return pp->getAttackersArraySize();
        default: return 0;
    }
}

std::string BTSPDPeerBlackListReqMsgDescriptor::getFieldAsString(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldAsString(object,field,i);
        field -= basedesc->getFieldCount(object);
    }
    BTSPDPeerBlackListReqMsg *pp = (BTSPDPeerBlackListReqMsg *)object; (void)pp;
    switch (field) {
        case 0: return oppstring2string(pp->getAttackers(i));
        default: return "";
    }
}

bool BTSPDPeerBlackListReqMsgDescriptor::setFieldAsString(void *object, int field, int i, const char *value) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->setFieldAsString(object,field,i,value);
        field -= basedesc->getFieldCount(object);
    }
    BTSPDPeerBlackListReqMsg *pp = (BTSPDPeerBlackListReqMsg *)object; (void)pp;
    switch (field) {
        case 0: pp->setAttackers(i,(value)); return true;
        default: return false;
    }
}

const char *BTSPDPeerBlackListReqMsgDescriptor::getFieldStructName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldStructNames[] = {
        NULL,
    };
    return (field>=0 && field<1) ? fieldStructNames[field] : NULL;
}

void *BTSPDPeerBlackListReqMsgDescriptor::getFieldStructPointer(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructPointer(object, field, i);
        field -= basedesc->getFieldCount(object);
    }
    BTSPDPeerBlackListReqMsg *pp = (BTSPDPeerBlackListReqMsg *)object; (void)pp;
    switch (field) {
        default: return NULL;
    }
}


