#pragma once

#include "../nn/hid.h"

enum class Styles
{
    Unknown,
    ProController,
    JoyConHandheld,
    JoyConDualMode,
    JoyConLeftSingle,
    JoyConRightSingle,
    GamecubeController,
    PokeBallPlusController,
    NESController,
    NESControllerHandheld,
    SNESController,
    N64Controller,
    SegaGenesisController,
    GenericExternalController,
    GenericController
};

class inputs
{

public:
    static void InitHooks();
    static void UpdateControllerState();
    static void SetPort(ulong port) { selectedPort = port;}

    static bool isHolding(nn::hid::NpadButton button);
    static bool isPress(nn::hid::NpadButton button);
    static bool isRelease(nn::hid::NpadButton button);

    static bool DoInput(bool doingInput) {isReadingInput = doingInput; return isReadingInput;}
    static bool IsDoingInput() {return isReadingInput;}

    static Styles GetStyle(nn::hid::NpadStyleSet style);
private:
    static bool getControllerState(nn::hid::NpadBaseState* state, ulong port);

    static nn::hid::NpadBaseState currentControllerState;
    static nn::hid::NpadBaseState previousControllerState;

    static ulong selectedPort;

    static bool isReadingInput;
};