//
// Generated file, do not edit! Created by opp_msgc 4.2 from applications/BitTorrentSPD/BTHostIntrnlMsgsSPD.msg.
//

// Disable warnings about unused variables, empty switch stmts, etc:
#ifdef _MSC_VER
#  pragma warning(disable:4101)
#  pragma warning(disable:4065)
#endif

#include <iostream>
#include <sstream>
#include "BTHostIntrnlMsgsSPD_m.h"

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




Register_Class(BTRequestTrackerCommSPD);

BTRequestTrackerCommSPD::BTRequestTrackerCommSPD(const char *name, int kind) : cMessage(name,kind)
{
    this->downloader_var = true;
    this->seeder_var = false;
    this->publishInPeerList_var = 0;
}

BTRequestTrackerCommSPD::BTRequestTrackerCommSPD(const BTRequestTrackerCommSPD& other) : cMessage(other)
{
    copy(other);
}

BTRequestTrackerCommSPD::~BTRequestTrackerCommSPD()
{
}

BTRequestTrackerCommSPD& BTRequestTrackerCommSPD::operator=(const BTRequestTrackerCommSPD& other)
{
    if (this==&other) return *this;
    cMessage::operator=(other);
    copy(other);
    return *this;
}

void BTRequestTrackerCommSPD::copy(const BTRequestTrackerCommSPD& other)
{
    this->downloader_var = other.downloader_var;
    this->seeder_var = other.seeder_var;
    this->publishInPeerList_var = other.publishInPeerList_var;
}

void BTRequestTrackerCommSPD::parsimPack(cCommBuffer *b)
{
    cMessage::parsimPack(b);
    doPacking(b,this->downloader_var);
    doPacking(b,this->seeder_var);
    doPacking(b,this->publishInPeerList_var);
}

void BTRequestTrackerCommSPD::parsimUnpack(cCommBuffer *b)
{
    cMessage::parsimUnpack(b);
    doUnpacking(b,this->downloader_var);
    doUnpacking(b,this->seeder_var);
    doUnpacking(b,this->publishInPeerList_var);
}

bool BTRequestTrackerCommSPD::downloader() const
{
    return downloader_var;
}

void BTRequestTrackerCommSPD::setDownloader(bool downloader)
{
    this->downloader_var = downloader;
}

bool BTRequestTrackerCommSPD::seeder() const
{
    return seeder_var;
}

void BTRequestTrackerCommSPD::setSeeder(bool seeder)
{
    this->seeder_var = seeder;
}

bool BTRequestTrackerCommSPD::publishInPeerList() const
{
    return publishInPeerList_var;
}

void BTRequestTrackerCommSPD::setPublishInPeerList(bool publishInPeerList)
{
    this->publishInPeerList_var = publishInPeerList;
}

class BTRequestTrackerCommSPDDescriptor : public cClassDescriptor
{
  public:
    BTRequestTrackerCommSPDDescriptor();
    virtual ~BTRequestTrackerCommSPDDescriptor();

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

Register_ClassDescriptor(BTRequestTrackerCommSPDDescriptor);

BTRequestTrackerCommSPDDescriptor::BTRequestTrackerCommSPDDescriptor() : cClassDescriptor("BTRequestTrackerCommSPD", "cMessage")
{
}

BTRequestTrackerCommSPDDescriptor::~BTRequestTrackerCommSPDDescriptor()
{
}

bool BTRequestTrackerCommSPDDescriptor::doesSupport(cObject *obj) const
{
    return dynamic_cast<BTRequestTrackerCommSPD *>(obj)!=NULL;
}

const char *BTRequestTrackerCommSPDDescriptor::getProperty(const char *propertyname) const
{
    if (!strcmp(propertyname,"omitGetVerb")) return "true";
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : NULL;
}

int BTRequestTrackerCommSPDDescriptor::getFieldCount(void *object) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 3+basedesc->getFieldCount(object) : 3;
}

unsigned int BTRequestTrackerCommSPDDescriptor::getFieldTypeFlags(void *object, int field) const
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

const char *BTRequestTrackerCommSPDDescriptor::getFieldName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldNames[] = {
        "downloader",
        "seeder",
        "publishInPeerList",
    };
    return (field>=0 && field<3) ? fieldNames[field] : NULL;
}

int BTRequestTrackerCommSPDDescriptor::findField(void *object, const char *fieldName) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount(object) : 0;
    if (fieldName[0]=='d' && strcmp(fieldName, "downloader")==0) return base+0;
    if (fieldName[0]=='s' && strcmp(fieldName, "seeder")==0) return base+1;
    if (fieldName[0]=='p' && strcmp(fieldName, "publishInPeerList")==0) return base+2;
    return basedesc ? basedesc->findField(object, fieldName) : -1;
}

const char *BTRequestTrackerCommSPDDescriptor::getFieldTypeString(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeString(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldTypeStrings[] = {
        "bool",
        "bool",
        "bool",
    };
    return (field>=0 && field<3) ? fieldTypeStrings[field] : NULL;
}

const char *BTRequestTrackerCommSPDDescriptor::getFieldProperty(void *object, int field, const char *propertyname) const
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

int BTRequestTrackerCommSPDDescriptor::getArraySize(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getArraySize(object, field);
        field -= basedesc->getFieldCount(object);
    }
    BTRequestTrackerCommSPD *pp = (BTRequestTrackerCommSPD *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

std::string BTRequestTrackerCommSPDDescriptor::getFieldAsString(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldAsString(object,field,i);
        field -= basedesc->getFieldCount(object);
    }
    BTRequestTrackerCommSPD *pp = (BTRequestTrackerCommSPD *)object; (void)pp;
    switch (field) {
        case 0: return bool2string(pp->downloader());
        case 1: return bool2string(pp->seeder());
        case 2: return bool2string(pp->publishInPeerList());
        default: return "";
    }
}

bool BTRequestTrackerCommSPDDescriptor::setFieldAsString(void *object, int field, int i, const char *value) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->setFieldAsString(object,field,i,value);
        field -= basedesc->getFieldCount(object);
    }
    BTRequestTrackerCommSPD *pp = (BTRequestTrackerCommSPD *)object; (void)pp;
    switch (field) {
        case 0: pp->setDownloader(string2bool(value)); return true;
        case 1: pp->setSeeder(string2bool(value)); return true;
        case 2: pp->setPublishInPeerList(string2bool(value)); return true;
        default: return false;
    }
}

const char *BTRequestTrackerCommSPDDescriptor::getFieldStructName(void *object, int field) const
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

void *BTRequestTrackerCommSPDDescriptor::getFieldStructPointer(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructPointer(object, field, i);
        field -= basedesc->getFieldCount(object);
    }
    BTRequestTrackerCommSPD *pp = (BTRequestTrackerCommSPD *)object; (void)pp;
    switch (field) {
        default: return NULL;
    }
}


