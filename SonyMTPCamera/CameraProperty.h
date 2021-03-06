#pragma once
#include "pch.h"
#include <stdint.h>
#include <list>
#include <unordered_map>
#include "Property.h"
#include "PropertyInfo.h"
#include "PropertyValue.h"

#include "resource.h"

class CameraProperty
{
public:
    CameraProperty();
    CameraProperty(const CameraProperty& rhs);
    ~CameraProperty();

    void SetId(Property id);
    Property GetId();
    std::wstring GetName();
    virtual std::wstring AsString();
    std::wstring ToString();
    DWORD Slurp(BYTE* data, DWORD dataLen);
    bool equals(const CameraProperty& rhs);
    PropertyInfo* GetInfo();
    PropertyValue* GetCurrentValue();

protected:
    BYTE GetBYTE(BYTE* data, DWORD offset);
    WORD GetWORD(BYTE* data, DWORD offset);
    DWORD GetDWORD(BYTE* data, DWORD offset);
    PropertyValue* ReadData(BYTE* data, DWORD &offset, DataType type);

    PropertyInfo* m_info = nullptr;
    PropertyValue* m_current = nullptr;
};

class ISOProperty : public CameraProperty
{
public:
    ISOProperty();

    std::wstring AsString();
};

class ShutterTimingProperty : public CameraProperty
{
public:
    ShutterTimingProperty();

    std::wstring AsString();
};

class Div10Property : public CameraProperty
{
public:
    Div10Property();

    std::wstring AsString();
};

class Div100Property : public CameraProperty
{
public:
    Div100Property();

    std::wstring AsString();
};

class Div1000Property : public CameraProperty
{
public:
    Div1000Property();

    std::wstring AsString();
};

class PercentageProperty : public CameraProperty
{
public:
    PercentageProperty();

    std::wstring AsString();
};

class StringLookupProperty : public CameraProperty
{
public:
    StringLookupProperty();

    std::wstring AsString();

protected:
    void AddResource(Property property, WORD value, WORD resid);

    static std::unordered_map<DWORD, WORD> _resourceMap;
};

template< typename T > CameraProperty* pCreate()
{
    return new T();
}

typedef CameraProperty* (*pConstructor)();

class CameraPropertyFactory
{
public:
    CameraPropertyFactory();

    CameraProperty* Create(Property id);

private:
    void AddCreator(Property id, pConstructor c);

    std::unordered_map<Property, pConstructor> m_creators;
};