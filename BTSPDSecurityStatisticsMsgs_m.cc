//
// Generated file, do not edit! Created by opp_msgc 4.2 from applications/BitTorrentSPD/BTSPDSecurityStatisticsMsgs.msg.
//

// Disable warnings about unused variables, empty switch stmts, etc:
#ifdef _MSC_VER
#  pragma warning(disable:4101)
#  pragma warning(disable:4065)
#endif

#include <iostream>
#include <sstream>
#include "BTSPDSecurityStatisticsMsgs_m.h"

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




Register_Class(BTSPDSecurityStatus);

BTSPDSecurityStatus::BTSPDSecurityStatus(const char *name, int kind) : cMessage(name,kind)
{
    this->moduleType_var = 0;
}

BTSPDSecurityStatus::BTSPDSecurityStatus(const BTSPDSecurityStatus& other) : cMessage(other)
{
    copy(other);
}

BTSPDSecurityStatus::~BTSPDSecurityStatus()
{
}

BTSPDSecurityStatus& BTSPDSecurityStatus::operator=(const BTSPDSecurityStatus& other)
{
    if (this==&other) return *this;
    cMessage::operator=(other);
    copy(other);
    return *this;
}

void BTSPDSecurityStatus::copy(const BTSPDSecurityStatus& other)
{
    this->moduleType_var = other.moduleType_var;
}

void BTSPDSecurityStatus::parsimPack(cCommBuffer *b)
{
    cMessage::parsimPack(b);
    doPacking(b,this->moduleType_var);
}

void BTSPDSecurityStatus::parsimUnpack(cCommBuffer *b)
{
    cMessage::parsimUnpack(b);
    doUnpacking(b,this->moduleType_var);
}

const char * BTSPDSecurityStatus::moduleType() const
{
    return moduleType_var.c_str();
}

void BTSPDSecurityStatus::setModuleType(const char * moduleType)
{
    this->moduleType_var = moduleType;
}

class BTSPDSecurityStatusDescriptor : public cClassDescriptor
{
  public:
    BTSPDSecurityStatusDescriptor();
    virtual ~BTSPDSecurityStatusDescriptor();

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

Register_ClassDescriptor(BTSPDSecurityStatusDescriptor);

BTSPDSecurityStatusDescriptor::BTSPDSecurityStatusDescriptor() : cClassDescriptor("BTSPDSecurityStatus", "cMessage")
{
}

BTSPDSecurityStatusDescriptor::~BTSPDSecurityStatusDescriptor()
{
}

bool BTSPDSecurityStatusDescriptor::doesSupport(cObject *obj) const
{
    return dynamic_cast<BTSPDSecurityStatus *>(obj)!=NULL;
}

const char *BTSPDSecurityStatusDescriptor::getProperty(const char *propertyname) const
{
    if (!strcmp(propertyname,"omitGetVerb")) return "true";
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : NULL;
}

int BTSPDSecurityStatusDescriptor::getFieldCount(void *object) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 1+basedesc->getFieldCount(object) : 1;
}

unsigned int BTSPDSecurityStatusDescriptor::getFieldTypeFlags(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeFlags(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,
    };
    return (field>=0 && field<1) ? fieldTypeFlags[field] : 0;
}

const char *BTSPDSecurityStatusDescriptor::getFieldName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldNames[] = {
        "moduleType",
    };
    return (field>=0 && field<1) ? fieldNames[field] : NULL;
}

int BTSPDSecurityStatusDescriptor::findField(void *object, const char *fieldName) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount(object) : 0;
    if (fieldName[0]=='m' && strcmp(fieldName, "moduleType")==0) return base+0;
    return basedesc ? basedesc->findField(object, fieldName) : -1;
}

const char *BTSPDSecurityStatusDescriptor::getFieldTypeString(void *object, int field) const
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

const char *BTSPDSecurityStatusDescriptor::getFieldProperty(void *object, int field, const char *propertyname) const
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

int BTSPDSecurityStatusDescriptor::getArraySize(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getArraySize(object, field);
        field -= basedesc->getFieldCount(object);
    }
    BTSPDSecurityStatus *pp = (BTSPDSecurityStatus *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

std::string BTSPDSecurityStatusDescriptor::getFieldAsString(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldAsString(object,field,i);
        field -= basedesc->getFieldCount(object);
    }
    BTSPDSecurityStatus *pp = (BTSPDSecurityStatus *)object; (void)pp;
    switch (field) {
        case 0: return oppstring2string(pp->moduleType());
        default: return "";
    }
}

bool BTSPDSecurityStatusDescriptor::setFieldAsString(void *object, int field, int i, const char *value) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->setFieldAsString(object,field,i,value);
        field -= basedesc->getFieldCount(object);
    }
    BTSPDSecurityStatus *pp = (BTSPDSecurityStatus *)object; (void)pp;
    switch (field) {
        case 0: pp->setModuleType((value)); return true;
        default: return false;
    }
}

const char *BTSPDSecurityStatusDescriptor::getFieldStructName(void *object, int field) const
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

void *BTSPDSecurityStatusDescriptor::getFieldStructPointer(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructPointer(object, field, i);
        field -= basedesc->getFieldCount(object);
    }
    BTSPDSecurityStatus *pp = (BTSPDSecurityStatus *)object; (void)pp;
    switch (field) {
        default: return NULL;
    }
}

Register_Class(BTSPDVulnerabilityStatus);

BTSPDVulnerabilityStatus::BTSPDVulnerabilityStatus(const char *name, int kind) : cMessage(name,kind)
{
    this->vulnerabilityFixed_var = 0;
}

BTSPDVulnerabilityStatus::BTSPDVulnerabilityStatus(const BTSPDVulnerabilityStatus& other) : cMessage(other)
{
    copy(other);
}

BTSPDVulnerabilityStatus::~BTSPDVulnerabilityStatus()
{
}

BTSPDVulnerabilityStatus& BTSPDVulnerabilityStatus::operator=(const BTSPDVulnerabilityStatus& other)
{
    if (this==&other) return *this;
    cMessage::operator=(other);
    copy(other);
    return *this;
}

void BTSPDVulnerabilityStatus::copy(const BTSPDVulnerabilityStatus& other)
{
    this->vulnerabilityFixed_var = other.vulnerabilityFixed_var;
}

void BTSPDVulnerabilityStatus::parsimPack(cCommBuffer *b)
{
    cMessage::parsimPack(b);
    doPacking(b,this->vulnerabilityFixed_var);
}

void BTSPDVulnerabilityStatus::parsimUnpack(cCommBuffer *b)
{
    cMessage::parsimUnpack(b);
    doUnpacking(b,this->vulnerabilityFixed_var);
}

bool BTSPDVulnerabilityStatus::vulnerabilityFixed() const
{
    return vulnerabilityFixed_var;
}

void BTSPDVulnerabilityStatus::setVulnerabilityFixed(bool vulnerabilityFixed)
{
    this->vulnerabilityFixed_var = vulnerabilityFixed;
}

class BTSPDVulnerabilityStatusDescriptor : public cClassDescriptor
{
  public:
    BTSPDVulnerabilityStatusDescriptor();
    virtual ~BTSPDVulnerabilityStatusDescriptor();

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

Register_ClassDescriptor(BTSPDVulnerabilityStatusDescriptor);

BTSPDVulnerabilityStatusDescriptor::BTSPDVulnerabilityStatusDescriptor() : cClassDescriptor("BTSPDVulnerabilityStatus", "cMessage")
{
}

BTSPDVulnerabilityStatusDescriptor::~BTSPDVulnerabilityStatusDescriptor()
{
}

bool BTSPDVulnerabilityStatusDescriptor::doesSupport(cObject *obj) const
{
    return dynamic_cast<BTSPDVulnerabilityStatus *>(obj)!=NULL;
}

const char *BTSPDVulnerabilityStatusDescriptor::getProperty(const char *propertyname) const
{
    if (!strcmp(propertyname,"omitGetVerb")) return "true";
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : NULL;
}

int BTSPDVulnerabilityStatusDescriptor::getFieldCount(void *object) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 1+basedesc->getFieldCount(object) : 1;
}

unsigned int BTSPDVulnerabilityStatusDescriptor::getFieldTypeFlags(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeFlags(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,
    };
    return (field>=0 && field<1) ? fieldTypeFlags[field] : 0;
}

const char *BTSPDVulnerabilityStatusDescriptor::getFieldName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldNames[] = {
        "vulnerabilityFixed",
    };
    return (field>=0 && field<1) ? fieldNames[field] : NULL;
}

int BTSPDVulnerabilityStatusDescriptor::findField(void *object, const char *fieldName) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount(object) : 0;
    if (fieldName[0]=='v' && strcmp(fieldName, "vulnerabilityFixed")==0) return base+0;
    return basedesc ? basedesc->findField(object, fieldName) : -1;
}

const char *BTSPDVulnerabilityStatusDescriptor::getFieldTypeString(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeString(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldTypeStrings[] = {
        "bool",
    };
    return (field>=0 && field<1) ? fieldTypeStrings[field] : NULL;
}

const char *BTSPDVulnerabilityStatusDescriptor::getFieldProperty(void *object, int field, const char *propertyname) const
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

int BTSPDVulnerabilityStatusDescriptor::getArraySize(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getArraySize(object, field);
        field -= basedesc->getFieldCount(object);
    }
    BTSPDVulnerabilityStatus *pp = (BTSPDVulnerabilityStatus *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

std::string BTSPDVulnerabilityStatusDescriptor::getFieldAsString(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldAsString(object,field,i);
        field -= basedesc->getFieldCount(object);
    }
    BTSPDVulnerabilityStatus *pp = (BTSPDVulnerabilityStatus *)object; (void)pp;
    switch (field) {
        case 0: return bool2string(pp->vulnerabilityFixed());
        default: return "";
    }
}

bool BTSPDVulnerabilityStatusDescriptor::setFieldAsString(void *object, int field, int i, const char *value) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->setFieldAsString(object,field,i,value);
        field -= basedesc->getFieldCount(object);
    }
    BTSPDVulnerabilityStatus *pp = (BTSPDVulnerabilityStatus *)object; (void)pp;
    switch (field) {
        case 0: pp->setVulnerabilityFixed(string2bool(value)); return true;
        default: return false;
    }
}

const char *BTSPDVulnerabilityStatusDescriptor::getFieldStructName(void *object, int field) const
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

void *BTSPDVulnerabilityStatusDescriptor::getFieldStructPointer(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructPointer(object, field, i);
        field -= basedesc->getFieldCount(object);
    }
    BTSPDVulnerabilityStatus *pp = (BTSPDVulnerabilityStatus *)object; (void)pp;
    switch (field) {
        default: return NULL;
    }
}

Register_Class(BTSPDThreatStatus);

BTSPDThreatStatus::BTSPDThreatStatus(const char *name, int kind) : cMessage(name,kind)
{
    this->infected_var = 0;
}

BTSPDThreatStatus::BTSPDThreatStatus(const BTSPDThreatStatus& other) : cMessage(other)
{
    copy(other);
}

BTSPDThreatStatus::~BTSPDThreatStatus()
{
}

BTSPDThreatStatus& BTSPDThreatStatus::operator=(const BTSPDThreatStatus& other)
{
    if (this==&other) return *this;
    cMessage::operator=(other);
    copy(other);
    return *this;
}

void BTSPDThreatStatus::copy(const BTSPDThreatStatus& other)
{
    this->infected_var = other.infected_var;
}

void BTSPDThreatStatus::parsimPack(cCommBuffer *b)
{
    cMessage::parsimPack(b);
    doPacking(b,this->infected_var);
}

void BTSPDThreatStatus::parsimUnpack(cCommBuffer *b)
{
    cMessage::parsimUnpack(b);
    doUnpacking(b,this->infected_var);
}

bool BTSPDThreatStatus::infected() const
{
    return infected_var;
}

void BTSPDThreatStatus::setInfected(bool infected)
{
    this->infected_var = infected;
}

class BTSPDThreatStatusDescriptor : public cClassDescriptor
{
  public:
    BTSPDThreatStatusDescriptor();
    virtual ~BTSPDThreatStatusDescriptor();

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

Register_ClassDescriptor(BTSPDThreatStatusDescriptor);

BTSPDThreatStatusDescriptor::BTSPDThreatStatusDescriptor() : cClassDescriptor("BTSPDThreatStatus", "cMessage")
{
}

BTSPDThreatStatusDescriptor::~BTSPDThreatStatusDescriptor()
{
}

bool BTSPDThreatStatusDescriptor::doesSupport(cObject *obj) const
{
    return dynamic_cast<BTSPDThreatStatus *>(obj)!=NULL;
}

const char *BTSPDThreatStatusDescriptor::getProperty(const char *propertyname) const
{
    if (!strcmp(propertyname,"omitGetVerb")) return "true";
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : NULL;
}

int BTSPDThreatStatusDescriptor::getFieldCount(void *object) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 1+basedesc->getFieldCount(object) : 1;
}

unsigned int BTSPDThreatStatusDescriptor::getFieldTypeFlags(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeFlags(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,
    };
    return (field>=0 && field<1) ? fieldTypeFlags[field] : 0;
}

const char *BTSPDThreatStatusDescriptor::getFieldName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldNames[] = {
        "infected",
    };
    return (field>=0 && field<1) ? fieldNames[field] : NULL;
}

int BTSPDThreatStatusDescriptor::findField(void *object, const char *fieldName) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount(object) : 0;
    if (fieldName[0]=='i' && strcmp(fieldName, "infected")==0) return base+0;
    return basedesc ? basedesc->findField(object, fieldName) : -1;
}

const char *BTSPDThreatStatusDescriptor::getFieldTypeString(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeString(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldTypeStrings[] = {
        "bool",
    };
    return (field>=0 && field<1) ? fieldTypeStrings[field] : NULL;
}

const char *BTSPDThreatStatusDescriptor::getFieldProperty(void *object, int field, const char *propertyname) const
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

int BTSPDThreatStatusDescriptor::getArraySize(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getArraySize(object, field);
        field -= basedesc->getFieldCount(object);
    }
    BTSPDThreatStatus *pp = (BTSPDThreatStatus *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

std::string BTSPDThreatStatusDescriptor::getFieldAsString(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldAsString(object,field,i);
        field -= basedesc->getFieldCount(object);
    }
    BTSPDThreatStatus *pp = (BTSPDThreatStatus *)object; (void)pp;
    switch (field) {
        case 0: return bool2string(pp->infected());
        default: return "";
    }
}

bool BTSPDThreatStatusDescriptor::setFieldAsString(void *object, int field, int i, const char *value) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->setFieldAsString(object,field,i,value);
        field -= basedesc->getFieldCount(object);
    }
    BTSPDThreatStatus *pp = (BTSPDThreatStatus *)object; (void)pp;
    switch (field) {
        case 0: pp->setInfected(string2bool(value)); return true;
        default: return false;
    }
}

const char *BTSPDThreatStatusDescriptor::getFieldStructName(void *object, int field) const
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

void *BTSPDThreatStatusDescriptor::getFieldStructPointer(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructPointer(object, field, i);
        field -= basedesc->getFieldCount(object);
    }
    BTSPDThreatStatus *pp = (BTSPDThreatStatus *)object; (void)pp;
    switch (field) {
        default: return NULL;
    }
}


