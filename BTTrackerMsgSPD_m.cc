//
// Generated file, do not edit! Created by opp_msgc 4.2 from applications/BitTorrentSPD/BTTrackerMsgSPD.msg.
//

// Disable warnings about unused variables, empty switch stmts, etc:
#ifdef _MSC_VER
#  pragma warning(disable:4101)
#  pragma warning(disable:4065)
#endif

#include <iostream>
#include <sstream>
#include "BTTrackerMsgSPD_m.h"

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




Register_Class(BTTrackerMsgAnnounceSPD);

BTTrackerMsgAnnounceSPD::BTTrackerMsgAnnounceSPD(const char *name, int kind) : BTTrackerMsgAnnounce(name,kind)
{
    this->relayPeerRatio_var = 0;
}

BTTrackerMsgAnnounceSPD::BTTrackerMsgAnnounceSPD(const BTTrackerMsgAnnounceSPD& other) : BTTrackerMsgAnnounce(other)
{
    copy(other);
}

BTTrackerMsgAnnounceSPD::~BTTrackerMsgAnnounceSPD()
{
}

BTTrackerMsgAnnounceSPD& BTTrackerMsgAnnounceSPD::operator=(const BTTrackerMsgAnnounceSPD& other)
{
    if (this==&other) return *this;
    BTTrackerMsgAnnounce::operator=(other);
    copy(other);
    return *this;
}

void BTTrackerMsgAnnounceSPD::copy(const BTTrackerMsgAnnounceSPD& other)
{
    this->relayPeerRatio_var = other.relayPeerRatio_var;
}

void BTTrackerMsgAnnounceSPD::parsimPack(cCommBuffer *b)
{
    BTTrackerMsgAnnounce::parsimPack(b);
    doPacking(b,this->relayPeerRatio_var);
}

void BTTrackerMsgAnnounceSPD::parsimUnpack(cCommBuffer *b)
{
    BTTrackerMsgAnnounce::parsimUnpack(b);
    doUnpacking(b,this->relayPeerRatio_var);
}

double BTTrackerMsgAnnounceSPD::relayPeerRatio() const
{
    return relayPeerRatio_var;
}

void BTTrackerMsgAnnounceSPD::setRelayPeerRatio(double relayPeerRatio)
{
    this->relayPeerRatio_var = relayPeerRatio;
}

class BTTrackerMsgAnnounceSPDDescriptor : public cClassDescriptor
{
  public:
    BTTrackerMsgAnnounceSPDDescriptor();
    virtual ~BTTrackerMsgAnnounceSPDDescriptor();

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

Register_ClassDescriptor(BTTrackerMsgAnnounceSPDDescriptor);

BTTrackerMsgAnnounceSPDDescriptor::BTTrackerMsgAnnounceSPDDescriptor() : cClassDescriptor("BTTrackerMsgAnnounceSPD", "BTTrackerMsgAnnounce")
{
}

BTTrackerMsgAnnounceSPDDescriptor::~BTTrackerMsgAnnounceSPDDescriptor()
{
}

bool BTTrackerMsgAnnounceSPDDescriptor::doesSupport(cObject *obj) const
{
    return dynamic_cast<BTTrackerMsgAnnounceSPD *>(obj)!=NULL;
}

const char *BTTrackerMsgAnnounceSPDDescriptor::getProperty(const char *propertyname) const
{
    if (!strcmp(propertyname,"omitGetVerb")) return "true";
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : NULL;
}

int BTTrackerMsgAnnounceSPDDescriptor::getFieldCount(void *object) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 1+basedesc->getFieldCount(object) : 1;
}

unsigned int BTTrackerMsgAnnounceSPDDescriptor::getFieldTypeFlags(void *object, int field) const
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

const char *BTTrackerMsgAnnounceSPDDescriptor::getFieldName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldNames[] = {
        "relayPeerRatio",
    };
    return (field>=0 && field<1) ? fieldNames[field] : NULL;
}

int BTTrackerMsgAnnounceSPDDescriptor::findField(void *object, const char *fieldName) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount(object) : 0;
    if (fieldName[0]=='r' && strcmp(fieldName, "relayPeerRatio")==0) return base+0;
    return basedesc ? basedesc->findField(object, fieldName) : -1;
}

const char *BTTrackerMsgAnnounceSPDDescriptor::getFieldTypeString(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeString(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldTypeStrings[] = {
        "double",
    };
    return (field>=0 && field<1) ? fieldTypeStrings[field] : NULL;
}

const char *BTTrackerMsgAnnounceSPDDescriptor::getFieldProperty(void *object, int field, const char *propertyname) const
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

int BTTrackerMsgAnnounceSPDDescriptor::getArraySize(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getArraySize(object, field);
        field -= basedesc->getFieldCount(object);
    }
    BTTrackerMsgAnnounceSPD *pp = (BTTrackerMsgAnnounceSPD *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

std::string BTTrackerMsgAnnounceSPDDescriptor::getFieldAsString(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldAsString(object,field,i);
        field -= basedesc->getFieldCount(object);
    }
    BTTrackerMsgAnnounceSPD *pp = (BTTrackerMsgAnnounceSPD *)object; (void)pp;
    switch (field) {
        case 0: return double2string(pp->relayPeerRatio());
        default: return "";
    }
}

bool BTTrackerMsgAnnounceSPDDescriptor::setFieldAsString(void *object, int field, int i, const char *value) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->setFieldAsString(object,field,i,value);
        field -= basedesc->getFieldCount(object);
    }
    BTTrackerMsgAnnounceSPD *pp = (BTTrackerMsgAnnounceSPD *)object; (void)pp;
    switch (field) {
        case 0: pp->setRelayPeerRatio(string2double(value)); return true;
        default: return false;
    }
}

const char *BTTrackerMsgAnnounceSPDDescriptor::getFieldStructName(void *object, int field) const
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

void *BTTrackerMsgAnnounceSPDDescriptor::getFieldStructPointer(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructPointer(object, field, i);
        field -= basedesc->getFieldCount(object);
    }
    BTTrackerMsgAnnounceSPD *pp = (BTTrackerMsgAnnounceSPD *)object; (void)pp;
    switch (field) {
        default: return NULL;
    }
}


