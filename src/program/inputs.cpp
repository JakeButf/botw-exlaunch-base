#include "inputs.h"
#include "diag/assert.hpp"

nn::hid::NpadBaseState inputs::previousControllerState{};
nn::hid::NpadBaseState inputs::currentControllerState{};

ulong inputs::selectedPort = -1;

bool inputs::isReadingInput = true;

Styles inputs::GetStyle(nn::hid::NpadStyleSet style)
{
    if (style.isBitSet(nn::hid::NpadStyleTag::NpadStyleFullKey)) { return Styles::ProController; }
    if (style.isBitSet(nn::hid::NpadStyleTag::NpadStyleHandheld)) { return Styles::JoyConHandheld; }
    if (style.isBitSet(nn::hid::NpadStyleTag::NpadStyleJoyDual)) { return Styles::JoyConDualMode; }
    if (style.isBitSet(nn::hid::NpadStyleTag::NpadStyleJoyLeft)) { return Styles::JoyConLeftSingle; }
    if (style.isBitSet(nn::hid::NpadStyleTag::NpadStyleJoyRight)) { return Styles::JoyConRightSingle; }
    if (style.isBitSet(nn::hid::NpadStyleTag::NpadStyleGc)) { return Styles::GamecubeController; }
    if (style.isBitSet(nn::hid::NpadStyleTag::NpadStylePalma)) { return Styles::PokeBallPlusController; }
    if (style.isBitSet(nn::hid::NpadStyleTag::NpadStyleLark)) { return Styles::NESController; }
    if (style.isBitSet(nn::hid::NpadStyleTag::NpadStyleHandheldLark)) { return Styles::NESControllerHandheld; }
    if (style.isBitSet(nn::hid::NpadStyleTag::NpadStyleLucia)) { return Styles::SNESController; }
    if (style.isBitSet(nn::hid::NpadStyleTag::NpadStyleLagon)) { return Styles::N64Controller;}
    if (style.isBitSet(nn::hid::NpadStyleTag::NpadStyleLager)) { return Styles::SegaGenesisController; }
    if (style.isBitSet(nn::hid::NpadStyleTag::NpadStyleSystemExt)) { return Styles::GenericExternalController; }
    if (style.isBitSet(nn::hid::NpadStyleTag::NpadStyleSystem)) { return Styles::GenericController;}

    return Styles::Unknown;
}

void inputs::UpdateControllerState()
{
    previousControllerState = currentControllerState;
    
    getControllerState(&currentControllerState, selectedPort);
}

bool inputs::getControllerState(nn::hid::NpadBaseState *state, ulong port)
{
    nn::hid::NpadStyleSet styleSet = nn::hid::GetNpadStyleSet(port);
    isReadingInput = true;
    bool controllerState = true; //return value

    if (styleSet.isBitSet(nn::hid::NpadStyleTag::NpadStyleFullKey)) {
        nn::hid::GetNpadState((nn::hid::NpadFullKeyState *) state, port);
    } else if (styleSet.isBitSet(nn::hid::NpadStyleTag::NpadStyleHandheld)) {
        nn::hid::GetNpadState((nn::hid::NpadHandheldState *) state, port);
    } else if (styleSet.isBitSet(nn::hid::NpadStyleTag::NpadStyleJoyDual)) {
        nn::hid::GetNpadState((nn::hid::NpadJoyDualState *) state, port);
    } else if (styleSet.isBitSet(nn::hid::NpadStyleTag::NpadStyleJoyLeft)) {
        nn::hid::GetNpadState((nn::hid::NpadJoyLeftState *) state, port);
    } else if (styleSet.isBitSet(nn::hid::NpadStyleTag::NpadStyleJoyRight)) {
        nn::hid::GetNpadState((nn::hid::NpadJoyRightState *) state, port);
    } else {
        controllerState = false;
    }

    isReadingInput = false;

    return controllerState;
}

bool inputs::isHolding(nn::hid::NpadButton button)
{
    return currentControllerState.mButtons.isBitSet(button);
}

bool inputs::isPress(nn::hid::NpadButton button)
{
    return currentControllerState.mButtons.isBitSet(button) && !previousControllerState.mButtons.isBitSet(button);
}

bool inputs::isRelease(nn::hid::NpadButton button)
{
    return !currentControllerState.mButtons.isBitSet(button) && previousControllerState.mButtons.isBitSet(button);
}