//
// Generated file, do not edit! Created by opp_msgc 4.2 from applications/BitTorrentSPD/BTSPDThreatHandlerMsgs.msg.
//

// Disable warnings about unused variables, empty switch stmts, etc:
#ifdef _MSC_VER
#  pragma warning(disable:4101)
#  pragma warning(disable:4065)
#endif

#include <iostream>
#include <sstream>
#include "BTSPDThreatHandlerMsgs_m.h"

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




EXECUTE_ON_STARTUP(
    cEnum *e = cEnum::find("ATTACK_TYPE");
    if (!e) enums.getInstance()->add(e = new cEnum("ATTACK_TYPE"));
    e->insert(ADDR_FOUND_ACTIVE_CONN, "ADDR_FOUND_ACTIVE_CONN");
    e->insert(ADDR_FOUND_PASSIVE_CONN, "ADDR_FOUND_PASSIVE_CONN");
);

Register_Class(BTSPD_NewAddrFound);

BTSPD_NewAddrFound::BTSPD_NewAddrFound(const char *name, int kind) : cMessage(name,kind)
{
    this->addr_var = 0;
    this->port_var = 0;
}

BTSPD_NewAddrFound::BTSPD_NewAddrFound(const BTSPD_NewAddrFound& other) : cMessage(other)
{
    copy(other);
}

BTSPD_NewAddrFound::~BTSPD_NewAddrFound()
{
}

BTSPD_NewAddrFound& BTSPD_NewAddrFound::operator=(const BTSPD_NewAddrFound& other)
{
    if (this==&other) return *this;
    cMessage::operator=(other);
    copy(other);
    return *this;
}

void BTSPD_NewAddrFound::copy(const BTSPD_NewAddrFound& other)
{
    this->addr_var = other.addr_var;
    this->port_var = other.port_var;
}

void BTSPD_NewAddrFound::parsimPack(cCommBuffer *b)
{
    cMessage::parsimPack(b);
    doPacking(b,this->addr_var);
    doPacking(b,this->port_var);
}

void BTSPD_NewAddrFound::parsimUnpack(cCommBuffer *b)
{
    cMessage::parsimUnpack(b);
    doUnpacking(b,this->addr_var);
    doUnpacking(b,this->port_var);
}

const char * BTSPD_NewAddrFound::addr() const
{
    return addr_var.c_str();
}

void BTSPD_NewAddrFound::setAddr(const char * addr)
{
    this->addr_var = addr;
}

const char * BTSPD_NewAddrFound::port() const
{
    return port_var.c_str();
}

void BTSPD_NewAddrFound::setPort(const char * port)
{
    this->port_var = port;
}

class BTSPD_NewAddrFoundDescriptor : public cClassDescriptor
{
  public:
    BTSPD_NewAddrFoundDescriptor();
    virtual ~BTSPD_NewAddrFoundDescriptor();

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

Register_ClassDescriptor(BTSPD_NewAddrFoundDescriptor);

BTSPD_NewAddrFoundDescriptor::BTSPD_NewAddrFoundDescriptor() : cClassDescriptor("BTSPD_NewAddrFound", "cMessage")
{
}

BTSPD_NewAddrFoundDescriptor::~BTSPD_NewAddrFoundDescriptor()
{
}

bool BTSPD_NewAddrFoundDescriptor::doesSupport(cObject *obj) const
{
    return dynamic_cast<BTSPD_NewAddrFound *>(obj)!=NULL;
}

const char *BTSPD_NewAddrFoundDescriptor::getProperty(const char *propertyname) const
{
    if (!strcmp(propertyname,"omitGetVerb")) return "true";
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : NULL;
}

int BTSPD_NewAddrFoundDescriptor::getFieldCount(void *object) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 2+basedesc->getFieldCount(object) : 2;
}

unsigned int BTSPD_NewAddrFoundDescriptor::getFieldTypeFlags(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeFlags(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,
        FD_ISEDITABLE,
    };
    return (field>=0 && field<2) ? fieldTypeFlags[field] : 0;
}

const char *BTSPD_NewAddrFoundDescriptor::getFieldName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldNames[] = {
        "addr",
        "port",
    };
    return (field>=0 && field<2) ? fieldNames[field] : NULL;
}

int BTSPD_NewAddrFoundDescriptor::findField(void *object, const char *fieldName) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount(object) : 0;
    if (fieldName[0]=='a' && strcmp(fieldName, "addr")==0) return base+0;
    if (fieldName[0]=='p' && strcmp(fieldName, "port")==0) return base+1;
    return basedesc ? basedesc->findField(object, fieldName) : -1;
}

const char *BTSPD_NewAddrFoundDescriptor::getFieldTypeString(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeString(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldTypeStrings[] = {
        "string",
        "string",
    };
    return (field>=0 && field<2) ? fieldTypeStrings[field] : NULL;
}

const char *BTSPD_NewAddrFoundDescriptor::getFieldProperty(void *object, int field, const char *propertyname) const
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

int BTSPD_NewAddrFoundDescriptor::getArraySize(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getArraySize(object, field);
        field -= basedesc->getFieldCount(object);
    }
    BTSPD_NewAddrFound *pp = (BTSPD_NewAddrFound *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

std::string BTSPD_NewAddrFoundDescriptor::getFieldAsString(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldAsString(object,field,i);
        field -= basedesc->getFieldCount(object);
    }
    BTSPD_NewAddrFound *pp = (BTSPD_NewAddrFound *)object; (void)pp;
    switch (field) {
        case 0: return oppstring2string(pp->addr());
        case 1: return oppstring2string(pp->port());
        default: return "";
    }
}

bool BTSPD_NewAddrFoundDescriptor::setFieldAsString(void *object, int field, int i, const char *value) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->setFieldAsString(object,field,i,value);
        field -= basedesc->getFieldCount(object);
    }
    BTSPD_NewAddrFound *pp = (BTSPD_NewAddrFound *)object; (void)pp;
    switch (field) {
        case 0: pp->setAddr((value)); return true;
        case 1: pp->setPort((value)); return true;
        default: return false;
    }
}

const char *BTSPD_NewAddrFoundDescriptor::getFieldStructName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldStructNames[] = {
        NULL,
        NULL,
    };
    return (field>=0 && field<2) ? fieldStructNames[field] : NULL;
}

void *BTSPD_NewAddrFoundDescriptor::getFieldStructPointer(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructPointer(object, field, i);
        field -= basedesc->getFieldCount(object);
    }
    BTSPD_NewAddrFound *pp = (BTSPD_NewAddrFound *)object; (void)pp;
    switch (field) {
        default: return NULL;
    }
}

Register_Class(BTSPDAttackMessage);

BTSPDAttackMessage::BTSPDAttackMessage(const char *name, int kind) : cPacket(name,kind)
{
    this->attacker_var = 0;
    this->victim_var = 0;
    this->attackerAddr_var = 0;
    this->attackType_var = 0;
}

BTSPDAttackMessage::BTSPDAttackMessage(const BTSPDAttackMessage& other) : cPacket(other)
{
    copy(other);
}

BTSPDAttackMessage::~BTSPDAttackMessage()
{
}

BTSPDAttackMessage& BTSPDAttackMessage::operator=(const BTSPDAttackMessage& other)
{
    if (this==&other) return *this;
    cPacket::operator=(other);
    copy(other);
    return *this;
}

void BTSPDAttackMessage::copy(const BTSPDAttackMessage& other)
{
    this->attacker_var = other.attacker_var;
    this->victim_var = other.victim_var;
    this->attackerAddr_var = other.attackerAddr_var;
    this->attackType_var = other.attackType_var;
}

void BTSPDAttackMessage::parsimPack(cCommBuffer *b)
{
    cPacket::parsimPack(b);
    doPacking(b,this->attacker_var);
    doPacking(b,this->victim_var);
    doPacking(b,this->attackerAddr_var);
    doPacking(b,this->attackType_var);
}

void BTSPDAttackMessage::parsimUnpack(cCommBuffer *b)
{
    cPacket::parsimUnpack(b);
    doUnpacking(b,this->attacker_var);
    doUnpacking(b,this->victim_var);
    doUnpacking(b,this->attackerAddr_var);
    doUnpacking(b,this->attackType_var);
}

const char * BTSPDAttackMessage::attacker() const
{
    return attacker_var.c_str();
}

void BTSPDAttackMessage::setAttacker(const char * attacker)
{
    this->attacker_var = attacker;
}

const char * BTSPDAttackMessage::victim() const
{
    return victim_var.c_str();
}

void BTSPDAttackMessage::setVictim(const char * victim)
{
    this->victim_var = victim;
}

const char * BTSPDAttackMessage::attackerAddr() const
{
    return attackerAddr_var.c_str();
}

void BTSPDAttackMessage::setAttackerAddr(const char * attackerAddr)
{
    this->attackerAddr_var = attackerAddr;
}

unsigned int BTSPDAttackMessage::attackType() const
{
    return attackType_var;
}

void BTSPDAttackMessage::setAttackType(unsigned int attackType)
{
    this->attackType_var = attackType;
}

class BTSPDAttackMessageDescriptor : public cClassDescriptor
{
  public:
    BTSPDAttackMessageDescriptor();
    virtual ~BTSPDAttackMessageDescriptor();

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

Register_ClassDescriptor(BTSPDAttackMessageDescriptor);

BTSPDAttackMessageDescriptor::BTSPDAttackMessageDescriptor() : cClassDescriptor("BTSPDAttackMessage", "cPacket")
{
}

BTSPDAttackMessageDescriptor::~BTSPDAttackMessageDescriptor()
{
}

bool BTSPDAttackMessageDescriptor::doesSupport(cObject *obj) const
{
    return dynamic_cast<BTSPDAttackMessage *>(obj)!=NULL;
}

const char *BTSPDAttackMessageDescriptor::getProperty(const char *propertyname) const
{
    if (!strcmp(propertyname,"omitGetVerb")) return "true";
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : NULL;
}

int BTSPDAttackMessageDescriptor::getFieldCount(void *object) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 4+basedesc->getFieldCount(object) : 4;
}

unsigned int BTSPDAttackMessageDescriptor::getFieldTypeFlags(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeFlags(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
    };
    return (field>=0 && field<4) ? fieldTypeFlags[field] : 0;
}

const char *BTSPDAttackMessageDescriptor::getFieldName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldNames[] = {
        "attacker",
        "victim",
        "attackerAddr",
        "attackType",
    };
    return (field>=0 && field<4) ? fieldNames[field] : NULL;
}

int BTSPDAttackMessageDescriptor::findField(void *object, const char *fieldName) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount(object) : 0;
    if (fieldName[0]=='a' && strcmp(fieldName, "attacker")==0) return base+0;
    if (fieldName[0]=='v' && strcmp(fieldName, "victim")==0) return base+1;
    if (fieldName[0]=='a' && strcmp(fieldName, "attackerAddr")==0) return base+2;
    if (fieldName[0]=='a' && strcmp(fieldName, "attackType")==0) return base+3;
    return basedesc ? basedesc->findField(object, fieldName) : -1;
}

const char *BTSPDAttackMessageDescriptor::getFieldTypeString(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeString(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldTypeStrings[] = {
        "string",
        "string",
        "string",
        "unsigned int",
    };
    return (field>=0 && field<4) ? fieldTypeStrings[field] : NULL;
}

const char *BTSPDAttackMessageDescriptor::getFieldProperty(void *object, int field, const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldProperty(object, field, propertyname);
        field -= basedesc->getFieldCount(object);
    }
    switch (field) {
        case 3:
            if (!strcmp(propertyname,"enum")) return "ATTACK_TYPE";
            return NULL;
        default: return NULL;
    }
}

int BTSPDAttackMessageDescriptor::getArraySize(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getArraySize(object, field);
        field -= basedesc->getFieldCount(object);
    }
    BTSPDAttackMessage *pp = (BTSPDAttackMessage *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

std::string BTSPDAttackMessageDescriptor::getFieldAsString(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldAsString(object,field,i);
        field -= basedesc->getFieldCount(object);
    }
    BTSPDAttackMessage *pp = (BTSPDAttackMessage *)object; (void)pp;
    switch (field) {
        case 0: return oppstring2string(pp->attacker());
        case 1: return oppstring2string(pp->victim());
        case 2: return oppstring2string(pp->attackerAddr());
        case 3: return ulong2string(pp->attackType());
        default: return "";
    }
}

bool BTSPDAttackMessageDescriptor::setFieldAsString(void *object, int field, int i, const char *value) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->setFieldAsString(object,field,i,value);
        field -= basedesc->getFieldCount(object);
    }
    BTSPDAttackMessage *pp = (BTSPDAttackMessage *)object; (void)pp;
    switch (field) {
        case 0: pp->setAttacker((value)); return true;
        case 1: pp->setVictim((value)); return true;
        case 2: pp->setAttackerAddr((value)); return true;
        case 3: pp->setAttackType(string2ulong(value)); return true;
        default: return false;
    }
}

const char *BTSPDAttackMessageDescriptor::getFieldStructName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldStructNames[] = {
        NULL,
        NULL,
        NULL,
        NULL,
    };
    return (field>=0 && field<4) ? fieldStructNames[field] : NULL;
}

void *BTSPDAttackMessageDescriptor::getFieldStructPointer(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructPointer(object, field, i);
        field -= basedesc->getFieldCount(object);
    }
    BTSPDAttackMessage *pp = (BTSPDAttackMessage *)object; (void)pp;
    switch (field) {
        default: return NULL;
    }
}


