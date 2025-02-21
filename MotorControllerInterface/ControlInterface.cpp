#include "ControlInterface.h"

ControlInterface::ControlInterface(ProtocolConfig protocol_config, ControllerData &controllerData) : protocol(protocol_config), controllerData(controllerData)
{
    if (!protocol.begin())
    {
        std::cerr << "Failed to initialize UART." << std::endl;
    }
}

bool ControlInterface::Ping()
{
    uint8_t recievedCommand;
    protocol.sendCommand(PING);
    protocol.readCommand(recievedCommand);
    return (recievedCommand == PING);
}

bool ControlInterface::SetControllerProperties()
{
    uint8_t recievedCommand;
    protocol.sendCommand(SET_CONTROLLER_PROPERTIES);
    protocol.sendData((byte*)&controllerData.controllerProperties, sizeof(ControllerProperties));
    protocol.readCommand(recievedCommand);
    return (recievedCommand == READ_SUCCESS); // Return true if the controller properties were set successfully
}

bool ControlInterface::SetMotorData(uint8_t motorID)
{
    if (motorID >= controllerData.controllerProperties.numMotors)
    {
        return false;
    }
    uint8_t recievedCommand;
    protocol.sendCommand(SET_MOTOR_DATA);
    protocol.sendData(&motorID, 1);
    protocol.sendData((byte *)(&controllerData.motorData[motorID]), sizeof(MotorData));
    protocol.readCommand(recievedCommand);
    return (recievedCommand == READ_SUCCESS); // Return true if the motor data was set successfully
}