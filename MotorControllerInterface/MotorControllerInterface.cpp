
#include <iostream>
#include "ControlInterface.h"

int main()
{
    ProtocolConfig config;
    ControllerData controllerData;
    ControlInterface controlInterface(config, controllerData);

    controllerData.motorData = new MotorData[2];

    controllerData.motorData[0].motorID = 0;
    controllerData.motorData[0].motorConnections.dirPin = 19;
    controllerData.motorData[0].motorConnections.pwmPin = 20;
    controllerData.motorData[0].motorConnections.encPinA = 9;
    controllerData.motorData[0].motorConnections.encPinB = 10;
    controllerData.motorData[0].controlMode = PWM_DIRECT_CONTROL;

    controllerData.motorData[1].motorID = 1;
    controllerData.motorData[1].motorConnections.dirPin = 36;
    controllerData.motorData[1].motorConnections.pwmPin = 37;
    controllerData.motorData[1].motorConnections.encPinA = 21;
    controllerData.motorData[1].motorConnections.encPinB = 47;
    controllerData.motorData[1].controlMode = PWM_DIRECT_CONTROL;

    while (true)
    {
        int dummy;
        if (controlInterface.Ping())
            std::cout << "Ping send and recieved successfully";
        else
            std::cout << "Ping failed";

        std::cin >> dummy;

        if (controlInterface.SetControllerProperties())
            std::cout << "Controller properties set successfully";
        else
            std::cout << "set failed failed";

        std::cin >> dummy;
        if (controlInterface.SetMotorData(0))
            std::cout << "Motor data set successfully for motor 0";
        else
            std::cout << "Set failed for motor 0";
        std::cin >> dummy;
        if (controlInterface.SetMotorData(1))
            std::cout << "Motor data set successfully for motor 1";
        else
            std::cout << "Set failed for motor 1";
        std::cin >> dummy;
        }
}
