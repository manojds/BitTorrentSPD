//
// Generated file, do not edit! Created by opp_msgc 4.2 from applications/BitTorrentSPD/BTSPDConnMap.msg.
//

// Disable warnings about unused variables, empty switch stmts, etc:
#ifdef _MSC_VER
#  pragma warning(disable:4101)
#  pragma warning(disable:4065)
#endif

#include <iostream>
#include <sstream>
#include "BTSPDConnMap_m.h"

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




Register_Class(BTSPDConnMapMsg);

BTSPDConnMapMsg::BTSPDConnMapMsg(const char *name, int kind) : cMessage(name,kind)
{
    this->myIP_var = 0;
    this->remoteIP_var = 0;
}

BTSPDConnMapMsg::BTSPDConnMapMsg(const BTSPDConnMapMsg& other) : cMessage(other)
{
    copy(other);
}

BTSPDConnMapMsg::~BTSPDConnMapMsg()
{
}

BTSPDConnMapMsg& BTSPDConnMapMsg::operator=(const BTSPDConnMapMsg& other)
{
    if (this==&other) return *this;
    cMessage::operator=(other);
    copy(other);
    return *this;
}

void BTSPDConnMapMsg::copy(const BTSPDConnMapMsg& other)
{
    this->myIP_var = other.myIP_var;
    this->remoteIP_var = other.remoteIP_var;
}

void BTSPDConnMapMsg::parsimPack(cCommBuffer *b)
{
    cMessage::parsimPack(b);
    doPacking(b,this->myIP_var);
    doPacking(b,this->remoteIP_var);
}

void BTSPDConnMapMsg::parsimUnpack(cCommBuffer *b)
{
    cMessage::parsimUnpack(b);
    doUnpacking(b,this->myIP_var);
    doUnpacking(b,this->remoteIP_var);
}

const char * BTSPDConnMapMsg::myIP() const
{
    return myIP_var.c_str();
}

void BTSPDConnMapMsg::setMyIP(const char * myIP)
{
    this->myIP_var = myIP;
}

const char * BTSPDConnMapMsg::remoteIP() const
{
    return remoteIP_var.c_str();
}

void BTSPDConnMapMsg::setRemoteIP(const char * remoteIP)
{
    this->remoteIP_var = remoteIP;
}

class BTSPDConnMapMsgDescriptor : public cClassDescriptor
{
  public:
    BTSPDConnMapMsgDescriptor();
    virtual ~BTSPDConnMapMsgDescriptor();

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

Register_ClassDescriptor(BTSPDConnMapMsgDescriptor);

BTSPDConnMapMsgDescriptor::BTSPDConnMapMsgDescriptor() : cClassDescriptor("BTSPDConnMapMsg", "cMessage")
{
}

BTSPDConnMapMsgDescriptor::~BTSPDConnMapMsgDescriptor()
{
}

bool BTSPDConnMapMsgDescriptor::doesSupport(cObject *obj) const
{
    return dynamic_cast<BTSPDConnMapMsg *>(obj)!=NULL;
}

const char *BTSPDConnMapMsgDescriptor::getProperty(const char *propertyname) const
{
    if (!strcmp(propertyname,"omitGetVerb")) return "true";
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : NULL;
}

int BTSPDConnMapMsgDescriptor::getFieldCount(void *object) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 2+basedesc->getFieldCount(object) : 2;
}

unsigned int BTSPDConnMapMsgDescriptor::getFieldTypeFlags(void *object, int field) const
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

const char *BTSPDConnMapMsgDescriptor::getFieldName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldNames[] = {
        "myIP",
        "remoteIP",
    };
    return (field>=0 && field<2) ? fieldNames[field] : NULL;
}

int BTSPDConnMapMsgDescriptor::findField(void *object, const char *fieldName) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount(object) : 0;
    if (fieldName[0]=='m' && strcmp(fieldName, "myIP")==0) return base+0;
    if (fieldName[0]=='r' && strcmp(fieldName, "remoteIP")==0) return base+1;
    return basedesc ? basedesc->findField(object, fieldName) : -1;
}

const char *BTSPDConnMapMsgDescriptor::getFieldTypeString(void *object, int field) const
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

const char *BTSPDConnMapMsgDescriptor::getFieldProperty(void *object, int field, const char *propertyname) const
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

int BTSPDConnMapMsgDescriptor::getArraySize(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getArraySize(object, field);
        field -= basedesc->getFieldCount(object);
    }
    BTSPDConnMapMsg *pp = (BTSPDConnMapMsg *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

std::string BTSPDConnMapMsgDescriptor::getFieldAsString(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldAsString(object,field,i);
        field -= basedesc->getFieldCount(object);
    }
    BTSPDConnMapMsg *pp = (BTSPDConnMapMsg *)object; (void)pp;
    switch (field) {
        case 0: return oppstring2string(pp->myIP());
        case 1: return oppstring2string(pp->remoteIP());
        default: return "";
    }
}

bool BTSPDConnMapMsgDescriptor::setFieldAsString(void *object, int field, int i, const char *value) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->setFieldAsString(object,field,i,value);
        field -= basedesc->getFieldCount(object);
    }
    BTSPDConnMapMsg *pp = (BTSPDConnMapMsg *)object; (void)pp;
    switch (field) {
        case 0: pp->setMyIP((value)); return true;
        case 1: pp->setRemoteIP((value)); return true;
        default: return false;
    }
}

const char *BTSPDConnMapMsgDescriptor::getFieldStructName(void *object, int field) const
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

void *BTSPDConnMapMsgDescriptor::getFieldStructPointer(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructPointer(object, field, i);
        field -= basedesc->getFieldCount(object);
    }
    BTSPDConnMapMsg *pp = (BTSPDConnMapMsg *)object; (void)pp;
    switch (field) {
        default: return NULL;
    }
}

Register_Class(BTSPDIPtoNameMappingMsg);

BTSPDIPtoNameMappingMsg::BTSPDIPtoNameMappingMsg(const char *name, int kind) : cMessage(name,kind)
{
    this->myIP_var = 0;
    this->myName_var = 0;
}

BTSPDIPtoNameMappingMsg::BTSPDIPtoNameMappingMsg(const BTSPDIPtoNameMappingMsg& other) : cMessage(other)
{
    copy(other);
}

BTSPDIPtoNameMappingMsg::~BTSPDIPtoNameMappingMsg()
{
}

BTSPDIPtoNameMappingMsg& BTSPDIPtoNameMappingMsg::operator=(const BTSPDIPtoNameMappingMsg& other)
{
    if (this==&other) return *this;
    cMessage::operator=(other);
    copy(other);
    return *this;
}

void BTSPDIPtoNameMappingMsg::copy(const BTSPDIPtoNameMappingMsg& other)
{
    this->myIP_var = other.myIP_var;
    this->myName_var = other.myName_var;
}

void BTSPDIPtoNameMappingMsg::parsimPack(cCommBuffer *b)
{
    cMessage::parsimPack(b);
    doPacking(b,this->myIP_var);
    doPacking(b,this->myName_var);
}

void BTSPDIPtoNameMappingMsg::parsimUnpack(cCommBuffer *b)
{
    cMessage::parsimUnpack(b);
    doUnpacking(b,this->myIP_var);
    doUnpacking(b,this->myName_var);
}

const char * BTSPDIPtoNameMappingMsg::myIP() const
{
    return myIP_var.c_str();
}

void BTSPDIPtoNameMappingMsg::setMyIP(const char * myIP)
{
    this->myIP_var = myIP;
}

const char * BTSPDIPtoNameMappingMsg::myName() const
{
    return myName_var.c_str();
}

void BTSPDIPtoNameMappingMsg::setMyName(const char * myName)
{
    this->myName_var = myName;
}

class BTSPDIPtoNameMappingMsgDescriptor : public cClassDescriptor
{
  public:
    BTSPDIPtoNameMappingMsgDescriptor();
    virtual ~BTSPDIPtoNameMappingMsgDescriptor();

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

Register_ClassDescriptor(BTSPDIPtoNameMappingMsgDescriptor);

BTSPDIPtoNameMappingMsgDescriptor::BTSPDIPtoNameMappingMsgDescriptor() : cClassDescriptor("BTSPDIPtoNameMappingMsg", "cMessage")
{
}

BTSPDIPtoNameMappingMsgDescriptor::~BTSPDIPtoNameMappingMsgDescriptor()
{
}

bool BTSPDIPtoNameMappingMsgDescriptor::doesSupport(cObject *obj) const
{
    return dynamic_cast<BTSPDIPtoNameMappingMsg *>(obj)!=NULL;
}

const char *BTSPDIPtoNameMappingMsgDescriptor::getProperty(const char *propertyname) const
{
    if (!strcmp(propertyname,"omitGetVerb")) return "true";
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : NULL;
}

int BTSPDIPtoNameMappingMsgDescriptor::getFieldCount(void *object) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 2+basedesc->getFieldCount(object) : 2;
}

unsigned int BTSPDIPtoNameMappingMsgDescriptor::getFieldTypeFlags(void *object, int field) const
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

const char *BTSPDIPtoNameMappingMsgDescriptor::getFieldName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldNames[] = {
        "myIP",
        "myName",
    };
    return (field>=0 && field<2) ? fieldNames[field] : NULL;
}

int BTSPDIPtoNameMappingMsgDescriptor::findField(void *object, const char *fieldName) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount(object) : 0;
    if (fieldName[0]=='m' && strcmp(fieldName, "myIP")==0) return base+0;
    if (fieldName[0]=='m' && strcmp(fieldName, "myName")==0) return base+1;
    return basedesc ? basedesc->findField(object, fieldName) : -1;
}

const char *BTSPDIPtoNameMappingMsgDescriptor::getFieldTypeString(void *object, int field) const
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

const char *BTSPDIPtoNameMappingMsgDescriptor::getFieldProperty(void *object, int field, const char *propertyname) const
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

int BTSPDIPtoNameMappingMsgDescriptor::getArraySize(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getArraySize(object, field);
        field -= basedesc->getFieldCount(object);
    }
    BTSPDIPtoNameMappingMsg *pp = (BTSPDIPtoNameMappingMsg *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

std::string BTSPDIPtoNameMappingMsgDescriptor::getFieldAsString(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldAsString(object,field,i);
        field -= basedesc->getFieldCount(object);
    }
    BTSPDIPtoNameMappingMsg *pp = (BTSPDIPtoNameMappingMsg *)object; (void)pp;
    switch (field) {
        case 0: return oppstring2string(pp->myIP());
        case 1: return oppstring2string(pp->myName());
        default: return "";
    }
}

bool BTSPDIPtoNameMappingMsgDescriptor::setFieldAsString(void *object, int field, int i, const char *value) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->setFieldAsString(object,field,i,value);
        field -= basedesc->getFieldCount(object);
    }
    BTSPDIPtoNameMappingMsg *pp = (BTSPDIPtoNameMappingMsg *)object; (void)pp;
    switch (field) {
        case 0: pp->setMyIP((value)); return true;
        case 1: pp->setMyName((value)); return true;
        default: return false;
    }
}

const char *BTSPDIPtoNameMappingMsgDescriptor::getFieldStructName(void *object, int field) const
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

void *BTSPDIPtoNameMappingMsgDescriptor::getFieldStructPointer(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructPointer(object, field, i);
        field -= basedesc->getFieldCount(object);
    }
    BTSPDIPtoNameMappingMsg *pp = (BTSPDIPtoNameMappingMsg *)object; (void)pp;
    switch (field) {
        default: return NULL;
    }
}


