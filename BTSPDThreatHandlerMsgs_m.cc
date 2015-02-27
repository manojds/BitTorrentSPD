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


