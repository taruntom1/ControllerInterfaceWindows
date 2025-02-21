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
    protocol.sendData((uint8_t *)&controllerData.controllerProperties, sizeof(ControllerProperties));
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
    protocol.sendData((uint8_t *)(&controllerData.motorData[motorID]), sizeof(MotorData));
    protocol.readCommand(recievedCommand);
    return (recievedCommand == READ_SUCCESS); // Return true if the motor data was set successfully
}

bool ControlInterface::SetMotorControlMode()
{
    uint8_t recievedCommand;
    protocol.sendCommand(SET_MOTOR_CONTROL_MODES);
    for (uint8_t i = 0; i < controllerData.controllerProperties.numMotors; i++)
    {
        protocol.sendData((uint8_t *)&controllerData.motorData[i].controlMode, sizeof(ControlMode));
    }
    protocol.readCommand(recievedCommand);
    return (recievedCommand == READ_SUCCESS);
}

bool ControlInterface::SetControllerData()
{
    bool ctrl_prop_success;
    bool motor_data_success = true;
    ctrl_prop_success = SetControllerProperties();
    if (ctrl_prop_success)
    {
        for (uint8_t i = 0; i < controllerData.controllerProperties.numMotors; i++)
        {
            motor_data_success &= SetMotorData(i);
        }
    }
    return (motor_data_success && ctrl_prop_success);
}

void ControlInterface::SetMotorPWMs()
{
    protocol.sendCommand(SET_MOTOR_PWMS);
    for (uint8_t i = 0; i < controllerData.controllerProperties.numMotors; i++)
    {
        protocol.sendData((uint8_t *)&controllerData.motorData[i].pwmValue, sizeof(uint16_t));
    }
}

bool ControlInterface::SetOdoBroadcastStatus(uint8_t motor_id)
{
    uint8_t receivedCommand;
    uint8_t data[sizeof(OdoBroadcastStatus) + 1];
    data[0] = motor_id;
    memcpy(data + 1, &controllerData.motorData[motor_id].odoBroadcastStatus, sizeof(OdoBroadcastStatus));
    protocol.sendCommand(SET_ODO_BROADCAST_STATUS);
    protocol.sendData(data, sizeof(OdoBroadcastStatus) + 1);
    protocol.readCommand(receivedCommand, 1);
    return receivedCommand == READ_SUCCESS;
}

bool ControlInterface::RecieveOdoAngles()
{
    bool success = true;

    for (uint8_t i = 0; i < controllerData.controllerProperties.numMotors; i++)
    {
        success &= protocol.readData((uint8_t *)&controllerData.motorData[i].odometryData.angle, sizeof(int));
    }
    return success;
}
