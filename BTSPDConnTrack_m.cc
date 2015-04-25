//
// Generated file, do not edit! Created by opp_msgc 4.2 from applications/BitTorrentSPD/BTSPDConnTrack.msg.
//

// Disable warnings about unused variables, empty switch stmts, etc:
#ifdef _MSC_VER
#  pragma warning(disable:4101)
#  pragma warning(disable:4065)
#endif

#include <iostream>
#include <sstream>
#include "BTSPDConnTrack_m.h"

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




Register_Class(BTSPDConnTrackNewConnMsg);

BTSPDConnTrackNewConnMsg::BTSPDConnTrackNewConnMsg(const char *name, int kind) : cMessage(name,kind)
{
    this->myName_var = 0;
    this->remoteIP_var = 0;
}

BTSPDConnTrackNewConnMsg::BTSPDConnTrackNewConnMsg(const BTSPDConnTrackNewConnMsg& other) : cMessage(other)
{
    copy(other);
}

BTSPDConnTrackNewConnMsg::~BTSPDConnTrackNewConnMsg()
{
}

BTSPDConnTrackNewConnMsg& BTSPDConnTrackNewConnMsg::operator=(const BTSPDConnTrackNewConnMsg& other)
{
    if (this==&other) return *this;
    cMessage::operator=(other);
    copy(other);
    return *this;
}

void BTSPDConnTrackNewConnMsg::copy(const BTSPDConnTrackNewConnMsg& other)
{
    this->myName_var = other.myName_var;
    this->remoteIP_var = other.remoteIP_var;
}

void BTSPDConnTrackNewConnMsg::parsimPack(cCommBuffer *b)
{
    cMessage::parsimPack(b);
    doPacking(b,this->myName_var);
    doPacking(b,this->remoteIP_var);
}

void BTSPDConnTrackNewConnMsg::parsimUnpack(cCommBuffer *b)
{
    cMessage::parsimUnpack(b);
    doUnpacking(b,this->myName_var);
    doUnpacking(b,this->remoteIP_var);
}

const char * BTSPDConnTrackNewConnMsg::myName() const
{
    return myName_var.c_str();
}

void BTSPDConnTrackNewConnMsg::setMyName(const char * myName)
{
    this->myName_var = myName;
}

const char * BTSPDConnTrackNewConnMsg::remoteIP() const
{
    return remoteIP_var.c_str();
}

void BTSPDConnTrackNewConnMsg::setRemoteIP(const char * remoteIP)
{
    this->remoteIP_var = remoteIP;
}

class BTSPDConnTrackNewConnMsgDescriptor : public cClassDescriptor
{
  public:
    BTSPDConnTrackNewConnMsgDescriptor();
    virtual ~BTSPDConnTrackNewConnMsgDescriptor();

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

Register_ClassDescriptor(BTSPDConnTrackNewConnMsgDescriptor);

BTSPDConnTrackNewConnMsgDescriptor::BTSPDConnTrackNewConnMsgDescriptor() : cClassDescriptor("BTSPDConnTrackNewConnMsg", "cMessage")
{
}

BTSPDConnTrackNewConnMsgDescriptor::~BTSPDConnTrackNewConnMsgDescriptor()
{
}

bool BTSPDConnTrackNewConnMsgDescriptor::doesSupport(cObject *obj) const
{
    return dynamic_cast<BTSPDConnTrackNewConnMsg *>(obj)!=NULL;
}

const char *BTSPDConnTrackNewConnMsgDescriptor::getProperty(const char *propertyname) const
{
    if (!strcmp(propertyname,"omitGetVerb")) return "true";
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : NULL;
}

int BTSPDConnTrackNewConnMsgDescriptor::getFieldCount(void *object) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 2+basedesc->getFieldCount(object) : 2;
}

unsigned int BTSPDConnTrackNewConnMsgDescriptor::getFieldTypeFlags(void *object, int field) const
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

const char *BTSPDConnTrackNewConnMsgDescriptor::getFieldName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldNames[] = {
        "myName",
        "remoteIP",
    };
    return (field>=0 && field<2) ? fieldNames[field] : NULL;
}

int BTSPDConnTrackNewConnMsgDescriptor::findField(void *object, const char *fieldName) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount(object) : 0;
    if (fieldName[0]=='m' && strcmp(fieldName, "myName")==0) return base+0;
    if (fieldName[0]=='r' && strcmp(fieldName, "remoteIP")==0) return base+1;
    return basedesc ? basedesc->findField(object, fieldName) : -1;
}

const char *BTSPDConnTrackNewConnMsgDescriptor::getFieldTypeString(void *object, int field) const
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

const char *BTSPDConnTrackNewConnMsgDescriptor::getFieldProperty(void *object, int field, const char *propertyname) const
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

int BTSPDConnTrackNewConnMsgDescriptor::getArraySize(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getArraySize(object, field);
        field -= basedesc->getFieldCount(object);
    }
    BTSPDConnTrackNewConnMsg *pp = (BTSPDConnTrackNewConnMsg *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

std::string BTSPDConnTrackNewConnMsgDescriptor::getFieldAsString(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldAsString(object,field,i);
        field -= basedesc->getFieldCount(object);
    }
    BTSPDConnTrackNewConnMsg *pp = (BTSPDConnTrackNewConnMsg *)object; (void)pp;
    switch (field) {
        case 0: return oppstring2string(pp->myName());
        case 1: return oppstring2string(pp->remoteIP());
        default: return "";
    }
}

bool BTSPDConnTrackNewConnMsgDescriptor::setFieldAsString(void *object, int field, int i, const char *value) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->setFieldAsString(object,field,i,value);
        field -= basedesc->getFieldCount(object);
    }
    BTSPDConnTrackNewConnMsg *pp = (BTSPDConnTrackNewConnMsg *)object; (void)pp;
    switch (field) {
        case 0: pp->setMyName((value)); return true;
        case 1: pp->setRemoteIP((value)); return true;
        default: return false;
    }
}

const char *BTSPDConnTrackNewConnMsgDescriptor::getFieldStructName(void *object, int field) const
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

void *BTSPDConnTrackNewConnMsgDescriptor::getFieldStructPointer(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructPointer(object, field, i);
        field -= basedesc->getFieldCount(object);
    }
    BTSPDConnTrackNewConnMsg *pp = (BTSPDConnTrackNewConnMsg *)object; (void)pp;
    switch (field) {
        default: return NULL;
    }
}

Register_Class(BTSPDConnTrackConnDropMsg);

BTSPDConnTrackConnDropMsg::BTSPDConnTrackConnDropMsg(const char *name, int kind) : cMessage(name,kind)
{
    this->myName_var = 0;
    this->remoteIP_var = 0;
}

BTSPDConnTrackConnDropMsg::BTSPDConnTrackConnDropMsg(const BTSPDConnTrackConnDropMsg& other) : cMessage(other)
{
    copy(other);
}

BTSPDConnTrackConnDropMsg::~BTSPDConnTrackConnDropMsg()
{
}

BTSPDConnTrackConnDropMsg& BTSPDConnTrackConnDropMsg::operator=(const BTSPDConnTrackConnDropMsg& other)
{
    if (this==&other) return *this;
    cMessage::operator=(other);
    copy(other);
    return *this;
}

void BTSPDConnTrackConnDropMsg::copy(const BTSPDConnTrackConnDropMsg& other)
{
    this->myName_var = other.myName_var;
    this->remoteIP_var = other.remoteIP_var;
}

void BTSPDConnTrackConnDropMsg::parsimPack(cCommBuffer *b)
{
    cMessage::parsimPack(b);
    doPacking(b,this->myName_var);
    doPacking(b,this->remoteIP_var);
}

void BTSPDConnTrackConnDropMsg::parsimUnpack(cCommBuffer *b)
{
    cMessage::parsimUnpack(b);
    doUnpacking(b,this->myName_var);
    doUnpacking(b,this->remoteIP_var);
}

const char * BTSPDConnTrackConnDropMsg::myName() const
{
    return myName_var.c_str();
}

void BTSPDConnTrackConnDropMsg::setMyName(const char * myName)
{
    this->myName_var = myName;
}

const char * BTSPDConnTrackConnDropMsg::remoteIP() const
{
    return remoteIP_var.c_str();
}

void BTSPDConnTrackConnDropMsg::setRemoteIP(const char * remoteIP)
{
    this->remoteIP_var = remoteIP;
}

class BTSPDConnTrackConnDropMsgDescriptor : public cClassDescriptor
{
  public:
    BTSPDConnTrackConnDropMsgDescriptor();
    virtual ~BTSPDConnTrackConnDropMsgDescriptor();

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

Register_ClassDescriptor(BTSPDConnTrackConnDropMsgDescriptor);

BTSPDConnTrackConnDropMsgDescriptor::BTSPDConnTrackConnDropMsgDescriptor() : cClassDescriptor("BTSPDConnTrackConnDropMsg", "cMessage")
{
}

BTSPDConnTrackConnDropMsgDescriptor::~BTSPDConnTrackConnDropMsgDescriptor()
{
}

bool BTSPDConnTrackConnDropMsgDescriptor::doesSupport(cObject *obj) const
{
    return dynamic_cast<BTSPDConnTrackConnDropMsg *>(obj)!=NULL;
}

const char *BTSPDConnTrackConnDropMsgDescriptor::getProperty(const char *propertyname) const
{
    if (!strcmp(propertyname,"omitGetVerb")) return "true";
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : NULL;
}

int BTSPDConnTrackConnDropMsgDescriptor::getFieldCount(void *object) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 2+basedesc->getFieldCount(object) : 2;
}

unsigned int BTSPDConnTrackConnDropMsgDescriptor::getFieldTypeFlags(void *object, int field) const
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

const char *BTSPDConnTrackConnDropMsgDescriptor::getFieldName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldNames[] = {
        "myName",
        "remoteIP",
    };
    return (field>=0 && field<2) ? fieldNames[field] : NULL;
}

int BTSPDConnTrackConnDropMsgDescriptor::findField(void *object, const char *fieldName) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount(object) : 0;
    if (fieldName[0]=='m' && strcmp(fieldName, "myName")==0) return base+0;
    if (fieldName[0]=='r' && strcmp(fieldName, "remoteIP")==0) return base+1;
    return basedesc ? basedesc->findField(object, fieldName) : -1;
}

const char *BTSPDConnTrackConnDropMsgDescriptor::getFieldTypeString(void *object, int field) const
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

const char *BTSPDConnTrackConnDropMsgDescriptor::getFieldProperty(void *object, int field, const char *propertyname) const
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

int BTSPDConnTrackConnDropMsgDescriptor::getArraySize(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getArraySize(object, field);
        field -= basedesc->getFieldCount(object);
    }
    BTSPDConnTrackConnDropMsg *pp = (BTSPDConnTrackConnDropMsg *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

std::string BTSPDConnTrackConnDropMsgDescriptor::getFieldAsString(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldAsString(object,field,i);
        field -= basedesc->getFieldCount(object);
    }
    BTSPDConnTrackConnDropMsg *pp = (BTSPDConnTrackConnDropMsg *)object; (void)pp;
    switch (field) {
        case 0: return oppstring2string(pp->myName());
        case 1: return oppstring2string(pp->remoteIP());
        default: return "";
    }
}

bool BTSPDConnTrackConnDropMsgDescriptor::setFieldAsString(void *object, int field, int i, const char *value) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->setFieldAsString(object,field,i,value);
        field -= basedesc->getFieldCount(object);
    }
    BTSPDConnTrackConnDropMsg *pp = (BTSPDConnTrackConnDropMsg *)object; (void)pp;
    switch (field) {
        case 0: pp->setMyName((value)); return true;
        case 1: pp->setRemoteIP((value)); return true;
        default: return false;
    }
}

const char *BTSPDConnTrackConnDropMsgDescriptor::getFieldStructName(void *object, int field) const
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

void *BTSPDConnTrackConnDropMsgDescriptor::getFieldStructPointer(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructPointer(object, field, i);
        field -= basedesc->getFieldCount(object);
    }
    BTSPDConnTrackConnDropMsg *pp = (BTSPDConnTrackConnDropMsg *)object; (void)pp;
    switch (field) {
        default: return NULL;
    }
}

Register_Class(BTSPDConnTrackNodeCreationMsg);

BTSPDConnTrackNodeCreationMsg::BTSPDConnTrackNodeCreationMsg(const char *name, int kind) : cMessage(name,kind)
{
    this->myName_var = 0;
    this->myIP_var = 0;
    this->creationTime_var = 0;
}

BTSPDConnTrackNodeCreationMsg::BTSPDConnTrackNodeCreationMsg(const BTSPDConnTrackNodeCreationMsg& other) : cMessage(other)
{
    copy(other);
}

BTSPDConnTrackNodeCreationMsg::~BTSPDConnTrackNodeCreationMsg()
{
}

BTSPDConnTrackNodeCreationMsg& BTSPDConnTrackNodeCreationMsg::operator=(const BTSPDConnTrackNodeCreationMsg& other)
{
    if (this==&other) return *this;
    cMessage::operator=(other);
    copy(other);
    return *this;
}

void BTSPDConnTrackNodeCreationMsg::copy(const BTSPDConnTrackNodeCreationMsg& other)
{
    this->myName_var = other.myName_var;
    this->myIP_var = other.myIP_var;
    this->creationTime_var = other.creationTime_var;
}

void BTSPDConnTrackNodeCreationMsg::parsimPack(cCommBuffer *b)
{
    cMessage::parsimPack(b);
    doPacking(b,this->myName_var);
    doPacking(b,this->myIP_var);
    doPacking(b,this->creationTime_var);
}

void BTSPDConnTrackNodeCreationMsg::parsimUnpack(cCommBuffer *b)
{
    cMessage::parsimUnpack(b);
    doUnpacking(b,this->myName_var);
    doUnpacking(b,this->myIP_var);
    doUnpacking(b,this->creationTime_var);
}

const char * BTSPDConnTrackNodeCreationMsg::myName() const
{
    return myName_var.c_str();
}

void BTSPDConnTrackNodeCreationMsg::setMyName(const char * myName)
{
    this->myName_var = myName;
}

const char * BTSPDConnTrackNodeCreationMsg::myIP() const
{
    return myIP_var.c_str();
}

void BTSPDConnTrackNodeCreationMsg::setMyIP(const char * myIP)
{
    this->myIP_var = myIP;
}

double BTSPDConnTrackNodeCreationMsg::creationTime() const
{
    return creationTime_var;
}

void BTSPDConnTrackNodeCreationMsg::setCreationTime(double creationTime)
{
    this->creationTime_var = creationTime;
}

class BTSPDConnTrackNodeCreationMsgDescriptor : public cClassDescriptor
{
  public:
    BTSPDConnTrackNodeCreationMsgDescriptor();
    virtual ~BTSPDConnTrackNodeCreationMsgDescriptor();

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

Register_ClassDescriptor(BTSPDConnTrackNodeCreationMsgDescriptor);

BTSPDConnTrackNodeCreationMsgDescriptor::BTSPDConnTrackNodeCreationMsgDescriptor() : cClassDescriptor("BTSPDConnTrackNodeCreationMsg", "cMessage")
{
}

BTSPDConnTrackNodeCreationMsgDescriptor::~BTSPDConnTrackNodeCreationMsgDescriptor()
{
}

bool BTSPDConnTrackNodeCreationMsgDescriptor::doesSupport(cObject *obj) const
{
    return dynamic_cast<BTSPDConnTrackNodeCreationMsg *>(obj)!=NULL;
}

const char *BTSPDConnTrackNodeCreationMsgDescriptor::getProperty(const char *propertyname) const
{
    if (!strcmp(propertyname,"omitGetVerb")) return "true";
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : NULL;
}

int BTSPDConnTrackNodeCreationMsgDescriptor::getFieldCount(void *object) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 3+basedesc->getFieldCount(object) : 3;
}

unsigned int BTSPDConnTrackNodeCreationMsgDescriptor::getFieldTypeFlags(void *object, int field) const
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
    };
    return (field>=0 && field<3) ? fieldTypeFlags[field] : 0;
}

const char *BTSPDConnTrackNodeCreationMsgDescriptor::getFieldName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldNames[] = {
        "myName",
        "myIP",
        "creationTime",
    };
    return (field>=0 && field<3) ? fieldNames[field] : NULL;
}

int BTSPDConnTrackNodeCreationMsgDescriptor::findField(void *object, const char *fieldName) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount(object) : 0;
    if (fieldName[0]=='m' && strcmp(fieldName, "myName")==0) return base+0;
    if (fieldName[0]=='m' && strcmp(fieldName, "myIP")==0) return base+1;
    if (fieldName[0]=='c' && strcmp(fieldName, "creationTime")==0) return base+2;
    return basedesc ? basedesc->findField(object, fieldName) : -1;
}

const char *BTSPDConnTrackNodeCreationMsgDescriptor::getFieldTypeString(void *object, int field) const
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
        "double",
    };
    return (field>=0 && field<3) ? fieldTypeStrings[field] : NULL;
}

const char *BTSPDConnTrackNodeCreationMsgDescriptor::getFieldProperty(void *object, int field, const char *propertyname) const
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

int BTSPDConnTrackNodeCreationMsgDescriptor::getArraySize(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getArraySize(object, field);
        field -= basedesc->getFieldCount(object);
    }
    BTSPDConnTrackNodeCreationMsg *pp = (BTSPDConnTrackNodeCreationMsg *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

std::string BTSPDConnTrackNodeCreationMsgDescriptor::getFieldAsString(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldAsString(object,field,i);
        field -= basedesc->getFieldCount(object);
    }
    BTSPDConnTrackNodeCreationMsg *pp = (BTSPDConnTrackNodeCreationMsg *)object; (void)pp;
    switch (field) {
        case 0: return oppstring2string(pp->myName());
        case 1: return oppstring2string(pp->myIP());
        case 2: return double2string(pp->creationTime());
        default: return "";
    }
}

bool BTSPDConnTrackNodeCreationMsgDescriptor::setFieldAsString(void *object, int field, int i, const char *value) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->setFieldAsString(object,field,i,value);
        field -= basedesc->getFieldCount(object);
    }
    BTSPDConnTrackNodeCreationMsg *pp = (BTSPDConnTrackNodeCreationMsg *)object; (void)pp;
    switch (field) {
        case 0: pp->setMyName((value)); return true;
        case 1: pp->setMyIP((value)); return true;
        case 2: pp->setCreationTime(string2double(value)); return true;
        default: return false;
    }
}

const char *BTSPDConnTrackNodeCreationMsgDescriptor::getFieldStructName(void *object, int field) const
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
    };
    return (field>=0 && field<3) ? fieldStructNames[field] : NULL;
}

void *BTSPDConnTrackNodeCreationMsgDescriptor::getFieldStructPointer(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructPointer(object, field, i);
        field -= basedesc->getFieldCount(object);
    }
    BTSPDConnTrackNodeCreationMsg *pp = (BTSPDConnTrackNodeCreationMsg *)object; (void)pp;
    switch (field) {
        default: return NULL;
    }
}

Register_Class(BTSPDConnTrackDwlCompeteMsg);

BTSPDConnTrackDwlCompeteMsg::BTSPDConnTrackDwlCompeteMsg(const char *name, int kind) : cMessage(name,kind)
{
    this->myName_var = 0;
    this->completionTime_var = 0;
    this->duration_var = 0;
}

BTSPDConnTrackDwlCompeteMsg::BTSPDConnTrackDwlCompeteMsg(const BTSPDConnTrackDwlCompeteMsg& other) : cMessage(other)
{
    copy(other);
}

BTSPDConnTrackDwlCompeteMsg::~BTSPDConnTrackDwlCompeteMsg()
{
}

BTSPDConnTrackDwlCompeteMsg& BTSPDConnTrackDwlCompeteMsg::operator=(const BTSPDConnTrackDwlCompeteMsg& other)
{
    if (this==&other) return *this;
    cMessage::operator=(other);
    copy(other);
    return *this;
}

void BTSPDConnTrackDwlCompeteMsg::copy(const BTSPDConnTrackDwlCompeteMsg& other)
{
    this->myName_var = other.myName_var;
    this->completionTime_var = other.completionTime_var;
    this->duration_var = other.duration_var;
}

void BTSPDConnTrackDwlCompeteMsg::parsimPack(cCommBuffer *b)
{
    cMessage::parsimPack(b);
    doPacking(b,this->myName_var);
    doPacking(b,this->completionTime_var);
    doPacking(b,this->duration_var);
}

void BTSPDConnTrackDwlCompeteMsg::parsimUnpack(cCommBuffer *b)
{
    cMessage::parsimUnpack(b);
    doUnpacking(b,this->myName_var);
    doUnpacking(b,this->completionTime_var);
    doUnpacking(b,this->duration_var);
}

const char * BTSPDConnTrackDwlCompeteMsg::myName() const
{
    return myName_var.c_str();
}

void BTSPDConnTrackDwlCompeteMsg::setMyName(const char * myName)
{
    this->myName_var = myName;
}

double BTSPDConnTrackDwlCompeteMsg::completionTime() const
{
    return completionTime_var;
}

void BTSPDConnTrackDwlCompeteMsg::setCompletionTime(double completionTime)
{
    this->completionTime_var = completionTime;
}

double BTSPDConnTrackDwlCompeteMsg::duration() const
{
    return duration_var;
}

void BTSPDConnTrackDwlCompeteMsg::setDuration(double duration)
{
    this->duration_var = duration;
}

class BTSPDConnTrackDwlCompeteMsgDescriptor : public cClassDescriptor
{
  public:
    BTSPDConnTrackDwlCompeteMsgDescriptor();
    virtual ~BTSPDConnTrackDwlCompeteMsgDescriptor();

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

Register_ClassDescriptor(BTSPDConnTrackDwlCompeteMsgDescriptor);

BTSPDConnTrackDwlCompeteMsgDescriptor::BTSPDConnTrackDwlCompeteMsgDescriptor() : cClassDescriptor("BTSPDConnTrackDwlCompeteMsg", "cMessage")
{
}

BTSPDConnTrackDwlCompeteMsgDescriptor::~BTSPDConnTrackDwlCompeteMsgDescriptor()
{
}

bool BTSPDConnTrackDwlCompeteMsgDescriptor::doesSupport(cObject *obj) const
{
    return dynamic_cast<BTSPDConnTrackDwlCompeteMsg *>(obj)!=NULL;
}

const char *BTSPDConnTrackDwlCompeteMsgDescriptor::getProperty(const char *propertyname) const
{
    if (!strcmp(propertyname,"omitGetVerb")) return "true";
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : NULL;
}

int BTSPDConnTrackDwlCompeteMsgDescriptor::getFieldCount(void *object) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 3+basedesc->getFieldCount(object) : 3;
}

unsigned int BTSPDConnTrackDwlCompeteMsgDescriptor::getFieldTypeFlags(void *object, int field) const
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
    };
    return (field>=0 && field<3) ? fieldTypeFlags[field] : 0;
}

const char *BTSPDConnTrackDwlCompeteMsgDescriptor::getFieldName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldNames[] = {
        "myName",
        "completionTime",
        "duration",
    };
    return (field>=0 && field<3) ? fieldNames[field] : NULL;
}

int BTSPDConnTrackDwlCompeteMsgDescriptor::findField(void *object, const char *fieldName) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount(object) : 0;
    if (fieldName[0]=='m' && strcmp(fieldName, "myName")==0) return base+0;
    if (fieldName[0]=='c' && strcmp(fieldName, "completionTime")==0) return base+1;
    if (fieldName[0]=='d' && strcmp(fieldName, "duration")==0) return base+2;
    return basedesc ? basedesc->findField(object, fieldName) : -1;
}

const char *BTSPDConnTrackDwlCompeteMsgDescriptor::getFieldTypeString(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeString(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldTypeStrings[] = {
        "string",
        "double",
        "double",
    };
    return (field>=0 && field<3) ? fieldTypeStrings[field] : NULL;
}

const char *BTSPDConnTrackDwlCompeteMsgDescriptor::getFieldProperty(void *object, int field, const char *propertyname) const
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

int BTSPDConnTrackDwlCompeteMsgDescriptor::getArraySize(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getArraySize(object, field);
        field -= basedesc->getFieldCount(object);
    }
    BTSPDConnTrackDwlCompeteMsg *pp = (BTSPDConnTrackDwlCompeteMsg *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

std::string BTSPDConnTrackDwlCompeteMsgDescriptor::getFieldAsString(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldAsString(object,field,i);
        field -= basedesc->getFieldCount(object);
    }
    BTSPDConnTrackDwlCompeteMsg *pp = (BTSPDConnTrackDwlCompeteMsg *)object; (void)pp;
    switch (field) {
        case 0: return oppstring2string(pp->myName());
        case 1: return double2string(pp->completionTime());
        case 2: return double2string(pp->duration());
        default: return "";
    }
}

bool BTSPDConnTrackDwlCompeteMsgDescriptor::setFieldAsString(void *object, int field, int i, const char *value) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->setFieldAsString(object,field,i,value);
        field -= basedesc->getFieldCount(object);
    }
    BTSPDConnTrackDwlCompeteMsg *pp = (BTSPDConnTrackDwlCompeteMsg *)object; (void)pp;
    switch (field) {
        case 0: pp->setMyName((value)); return true;
        case 1: pp->setCompletionTime(string2double(value)); return true;
        case 2: pp->setDuration(string2double(value)); return true;
        default: return false;
    }
}

const char *BTSPDConnTrackDwlCompeteMsgDescriptor::getFieldStructName(void *object, int field) const
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
    };
    return (field>=0 && field<3) ? fieldStructNames[field] : NULL;
}

void *BTSPDConnTrackDwlCompeteMsgDescriptor::getFieldStructPointer(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructPointer(object, field, i);
        field -= basedesc->getFieldCount(object);
    }
    BTSPDConnTrackDwlCompeteMsg *pp = (BTSPDConnTrackDwlCompeteMsg *)object; (void)pp;
    switch (field) {
        default: return NULL;
    }
}

Register_Class(BTSPDConnTrackIPtoNameMapMsg);

BTSPDConnTrackIPtoNameMapMsg::BTSPDConnTrackIPtoNameMapMsg(const char *name, int kind) : cMessage(name,kind)
{
    this->myIP_var = 0;
    this->myName_var = 0;
}

BTSPDConnTrackIPtoNameMapMsg::BTSPDConnTrackIPtoNameMapMsg(const BTSPDConnTrackIPtoNameMapMsg& other) : cMessage(other)
{
    copy(other);
}

BTSPDConnTrackIPtoNameMapMsg::~BTSPDConnTrackIPtoNameMapMsg()
{
}

BTSPDConnTrackIPtoNameMapMsg& BTSPDConnTrackIPtoNameMapMsg::operator=(const BTSPDConnTrackIPtoNameMapMsg& other)
{
    if (this==&other) return *this;
    cMessage::operator=(other);
    copy(other);
    return *this;
}

void BTSPDConnTrackIPtoNameMapMsg::copy(const BTSPDConnTrackIPtoNameMapMsg& other)
{
    this->myIP_var = other.myIP_var;
    this->myName_var = other.myName_var;
}

void BTSPDConnTrackIPtoNameMapMsg::parsimPack(cCommBuffer *b)
{
    cMessage::parsimPack(b);
    doPacking(b,this->myIP_var);
    doPacking(b,this->myName_var);
}

void BTSPDConnTrackIPtoNameMapMsg::parsimUnpack(cCommBuffer *b)
{
    cMessage::parsimUnpack(b);
    doUnpacking(b,this->myIP_var);
    doUnpacking(b,this->myName_var);
}

const char * BTSPDConnTrackIPtoNameMapMsg::myIP() const
{
    return myIP_var.c_str();
}

void BTSPDConnTrackIPtoNameMapMsg::setMyIP(const char * myIP)
{
    this->myIP_var = myIP;
}

const char * BTSPDConnTrackIPtoNameMapMsg::myName() const
{
    return myName_var.c_str();
}

void BTSPDConnTrackIPtoNameMapMsg::setMyName(const char * myName)
{
    this->myName_var = myName;
}

class BTSPDConnTrackIPtoNameMapMsgDescriptor : public cClassDescriptor
{
  public:
    BTSPDConnTrackIPtoNameMapMsgDescriptor();
    virtual ~BTSPDConnTrackIPtoNameMapMsgDescriptor();

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

Register_ClassDescriptor(BTSPDConnTrackIPtoNameMapMsgDescriptor);

BTSPDConnTrackIPtoNameMapMsgDescriptor::BTSPDConnTrackIPtoNameMapMsgDescriptor() : cClassDescriptor("BTSPDConnTrackIPtoNameMapMsg", "cMessage")
{
}

BTSPDConnTrackIPtoNameMapMsgDescriptor::~BTSPDConnTrackIPtoNameMapMsgDescriptor()
{
}

bool BTSPDConnTrackIPtoNameMapMsgDescriptor::doesSupport(cObject *obj) const
{
    return dynamic_cast<BTSPDConnTrackIPtoNameMapMsg *>(obj)!=NULL;
}

const char *BTSPDConnTrackIPtoNameMapMsgDescriptor::getProperty(const char *propertyname) const
{
    if (!strcmp(propertyname,"omitGetVerb")) return "true";
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : NULL;
}

int BTSPDConnTrackIPtoNameMapMsgDescriptor::getFieldCount(void *object) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 2+basedesc->getFieldCount(object) : 2;
}

unsigned int BTSPDConnTrackIPtoNameMapMsgDescriptor::getFieldTypeFlags(void *object, int field) const
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

const char *BTSPDConnTrackIPtoNameMapMsgDescriptor::getFieldName(void *object, int field) const
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

int BTSPDConnTrackIPtoNameMapMsgDescriptor::findField(void *object, const char *fieldName) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount(object) : 0;
    if (fieldName[0]=='m' && strcmp(fieldName, "myIP")==0) return base+0;
    if (fieldName[0]=='m' && strcmp(fieldName, "myName")==0) return base+1;
    return basedesc ? basedesc->findField(object, fieldName) : -1;
}

const char *BTSPDConnTrackIPtoNameMapMsgDescriptor::getFieldTypeString(void *object, int field) const
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

const char *BTSPDConnTrackIPtoNameMapMsgDescriptor::getFieldProperty(void *object, int field, const char *propertyname) const
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

int BTSPDConnTrackIPtoNameMapMsgDescriptor::getArraySize(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getArraySize(object, field);
        field -= basedesc->getFieldCount(object);
    }
    BTSPDConnTrackIPtoNameMapMsg *pp = (BTSPDConnTrackIPtoNameMapMsg *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

std::string BTSPDConnTrackIPtoNameMapMsgDescriptor::getFieldAsString(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldAsString(object,field,i);
        field -= basedesc->getFieldCount(object);
    }
    BTSPDConnTrackIPtoNameMapMsg *pp = (BTSPDConnTrackIPtoNameMapMsg *)object; (void)pp;
    switch (field) {
        case 0: return oppstring2string(pp->myIP());
        case 1: return oppstring2string(pp->myName());
        default: return "";
    }
}

bool BTSPDConnTrackIPtoNameMapMsgDescriptor::setFieldAsString(void *object, int field, int i, const char *value) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->setFieldAsString(object,field,i,value);
        field -= basedesc->getFieldCount(object);
    }
    BTSPDConnTrackIPtoNameMapMsg *pp = (BTSPDConnTrackIPtoNameMapMsg *)object; (void)pp;
    switch (field) {
        case 0: pp->setMyIP((value)); return true;
        case 1: pp->setMyName((value)); return true;
        default: return false;
    }
}

const char *BTSPDConnTrackIPtoNameMapMsgDescriptor::getFieldStructName(void *object, int field) const
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

void *BTSPDConnTrackIPtoNameMapMsgDescriptor::getFieldStructPointer(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructPointer(object, field, i);
        field -= basedesc->getFieldCount(object);
    }
    BTSPDConnTrackIPtoNameMapMsg *pp = (BTSPDConnTrackIPtoNameMapMsg *)object; (void)pp;
    switch (field) {
        default: return NULL;
    }
}


