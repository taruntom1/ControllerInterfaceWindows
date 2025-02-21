#pragma once
#include "UARTProtocol.h"
#include "MyStructs.h"
#include "Commands.h"

class ControlInterface
{
private:
	ProtocolConfig protocol_config;
	UARTProtocol protocol;
	ControllerData& controllerData;
public:
	ControlInterface(ProtocolConfig protocol_config, ControllerData& controllerData);


    bool Ping();
    bool Start();
    bool Stop();

    bool SetControllerData();
    bool SetMotorData(uint8_t motorID);
    bool GetMotorData(uint8_t motorID);
    bool SetControllerProperties();
    bool GetControllerProperties();
    bool SetMotorControlMode();

    bool SetPIDConstants(uint8_t motorID, uint8_t PIDtype);

    void SetMotorSpeedSetpoints();
    void SetMotorAngleSetpoints();
    void SetMotorPWMs();

    bool SetOdoBroadcastStatus(uint8_t motor_id);
    bool RecieveOdoSpeeds();
    bool RecieveOdoAngles();

    void Run();
};

