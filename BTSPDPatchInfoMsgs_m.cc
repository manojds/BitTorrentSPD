//
// Generated file, do not edit! Created by opp_msgc 4.2 from applications/BitTorrentSPD/BTSPDPatchInfoMsgs.msg.
//

// Disable warnings about unused variables, empty switch stmts, etc:
#ifdef _MSC_VER
#  pragma warning(disable:4101)
#  pragma warning(disable:4065)
#endif

#include <iostream>
#include <sstream>
#include "BTSPDPatchInfoMsgs_m.h"

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




Register_Class(BTSPDPatchInfoMsg);

BTSPDPatchInfoMsg::BTSPDPatchInfoMsg(const char *name, int kind) : cPacket(name,kind)
{
    this->platform_var = 0;
}

BTSPDPatchInfoMsg::BTSPDPatchInfoMsg(const BTSPDPatchInfoMsg& other) : cPacket(other)
{
    copy(other);
}

BTSPDPatchInfoMsg::~BTSPDPatchInfoMsg()
{
}

BTSPDPatchInfoMsg& BTSPDPatchInfoMsg::operator=(const BTSPDPatchInfoMsg& other)
{
    if (this==&other) return *this;
    cPacket::operator=(other);
    copy(other);
    return *this;
}

void BTSPDPatchInfoMsg::copy(const BTSPDPatchInfoMsg& other)
{
    this->platform_var = other.platform_var;
}

void BTSPDPatchInfoMsg::parsimPack(cCommBuffer *b)
{
    cPacket::parsimPack(b);
    doPacking(b,this->platform_var);
}

void BTSPDPatchInfoMsg::parsimUnpack(cCommBuffer *b)
{
    cPacket::parsimUnpack(b);
    doUnpacking(b,this->platform_var);
}

const char * BTSPDPatchInfoMsg::platform() const
{
    return platform_var.c_str();
}

void BTSPDPatchInfoMsg::setPlatform(const char * platform)
{
    this->platform_var = platform;
}

class BTSPDPatchInfoMsgDescriptor : public cClassDescriptor
{
  public:
    BTSPDPatchInfoMsgDescriptor();
    virtual ~BTSPDPatchInfoMsgDescriptor();

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

Register_ClassDescriptor(BTSPDPatchInfoMsgDescriptor);

BTSPDPatchInfoMsgDescriptor::BTSPDPatchInfoMsgDescriptor() : cClassDescriptor("BTSPDPatchInfoMsg", "cPacket")
{
}

BTSPDPatchInfoMsgDescriptor::~BTSPDPatchInfoMsgDescriptor()
{
}

bool BTSPDPatchInfoMsgDescriptor::doesSupport(cObject *obj) const
{
    return dynamic_cast<BTSPDPatchInfoMsg *>(obj)!=NULL;
}

const char *BTSPDPatchInfoMsgDescriptor::getProperty(const char *propertyname) const
{
    if (!strcmp(propertyname,"omitGetVerb")) return "true";
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : NULL;
}

int BTSPDPatchInfoMsgDescriptor::getFieldCount(void *object) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 1+basedesc->getFieldCount(object) : 1;
}

unsigned int BTSPDPatchInfoMsgDescriptor::getFieldTypeFlags(void *object, int field) const
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

const char *BTSPDPatchInfoMsgDescriptor::getFieldName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldNames[] = {
        "platform",
    };
    return (field>=0 && field<1) ? fieldNames[field] : NULL;
}

int BTSPDPatchInfoMsgDescriptor::findField(void *object, const char *fieldName) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount(object) : 0;
    if (fieldName[0]=='p' && strcmp(fieldName, "platform")==0) return base+0;
    return basedesc ? basedesc->findField(object, fieldName) : -1;
}

const char *BTSPDPatchInfoMsgDescriptor::getFieldTypeString(void *object, int field) const
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

const char *BTSPDPatchInfoMsgDescriptor::getFieldProperty(void *object, int field, const char *propertyname) const
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

int BTSPDPatchInfoMsgDescriptor::getArraySize(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getArraySize(object, field);
        field -= basedesc->getFieldCount(object);
    }
    BTSPDPatchInfoMsg *pp = (BTSPDPatchInfoMsg *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

std::string BTSPDPatchInfoMsgDescriptor::getFieldAsString(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldAsString(object,field,i);
        field -= basedesc->getFieldCount(object);
    }
    BTSPDPatchInfoMsg *pp = (BTSPDPatchInfoMsg *)object; (void)pp;
    switch (field) {
        case 0: return oppstring2string(pp->platform());
        default: return "";
    }
}

bool BTSPDPatchInfoMsgDescriptor::setFieldAsString(void *object, int field, int i, const char *value) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->setFieldAsString(object,field,i,value);
        field -= basedesc->getFieldCount(object);
    }
    BTSPDPatchInfoMsg *pp = (BTSPDPatchInfoMsg *)object; (void)pp;
    switch (field) {
        case 0: pp->setPlatform((value)); return true;
        default: return false;
    }
}

const char *BTSPDPatchInfoMsgDescriptor::getFieldStructName(void *object, int field) const
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

void *BTSPDPatchInfoMsgDescriptor::getFieldStructPointer(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructPointer(object, field, i);
        field -= basedesc->getFieldCount(object);
    }
    BTSPDPatchInfoMsg *pp = (BTSPDPatchInfoMsg *)object; (void)pp;
    switch (field) {
        default: return NULL;
    }
}


