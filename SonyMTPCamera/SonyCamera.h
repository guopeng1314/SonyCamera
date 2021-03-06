#pragma once
#include "Camera.h"
#include "CameraSupportedProperties.h"
#include <unordered_map>
#include "PropertyInfo.h"

// Sony Commands - Seem to have a handle on these ones
/* Get all properties in one go */
#define COMMAND_READ_SETTINGS               0x9209

/* Get list of properties that the camera supports
   Seems to be broken into two sections... */
#define COMMAND_SONY_GET_PROPERTY_LIST      0x9202

   // Sony Commands - Unsure about these ones
#define COMMAND_SONY_GET_NEXT_HANDLE        0x9201

// Setting Properties:
//   ..._PROPERTY   = Properties where accessibility = READWRITE
//   ..._PROPERTY2  = Properties where accessibility = READONLY but SonySpecial != 0
#define COMMAND_SONY_SET_PROPERTY           0x9205
#define COMMAND_SONY_SET_PROPERTY2          0x9207
// 1: d20d, 0000 - set shutter speed -1 ?
//    ^^^^
//    Property to set
// 2: ffff
//    ^^^^
//    Value to use


// Returns error?
#define COMMAND_SONY3                  0x9208

class SonyCamera : public Camera
{
public:
    SonyCamera(Device* device);
    ~SonyCamera();

    bool Initialize();
    CameraSettings* GetSettings(bool refresh);
    bool SetProperty(Property id, PropertyValue* value);

private:
};

