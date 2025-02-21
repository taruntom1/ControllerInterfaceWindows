
#include <iostream>
#include "ControlInterface.h"

int main()
{
	ProtocolConfig config;
	ControllerData controllerData;
	ControlInterface controlInterface(config, controllerData);

	controllerData.motorData = new MotorData[2];


	while (true)
	{
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


		int dummy;
		std::cin >> dummy;
		if (controlInterface.Ping())
			std::cout << "Ping send and recieved successfully" << std::endl;
		else
			std::cout << "Ping failed" << std::endl;

		//std::cin >> dummy;
		//if (controlInterface.SetControllerData())
		//	std::cout << "Controller data set successfully" << std::endl;
		//else
		//	std::cout << "Set failed for controller data" << std::endl;

		std::cin >> dummy;
		if (controlInterface.SetControllerProperties())
			std::cout << "Controller properties set successfully" << std::endl;
		else
			std::cout << "set failed failed" << std::endl;

		std::cin >> dummy;
		if (controlInterface.SetMotorData(0))
			std::cout << "Motor data set successfully for motor 0" << std::endl;
		else
			std::cout << "Set failed for motor 0" << std::endl;
		if (controlInterface.SetMotorData(1))
			std::cout << "Motor data set successfully for motor 1" << std::endl;
		else
			std::cout << "Set failed for motor 1" << std::endl;

		std::cin >> dummy;
		if (controlInterface.SetMotorControlMode())
			std::cout << "Motor control mode set successfully" << std::endl;
		else
			std::cout << "Set failed for motor control mode" << std::endl;

		std::cin >> dummy;
		controllerData.motorData[0].pwmValue = 555;
		controllerData.motorData[1].pwmValue = 556;
		controlInterface.SetMotorPWMs();
		std::cout << "PWMs set" << std::endl;

		std::cin >> dummy;
		controllerData.motorData[0].odoBroadcastStatus.angleBroadcast = true;
		controllerData.motorData[0].odoBroadcastStatus.speedBroadcast = false;
		controllerData.motorData[0].odoBroadcastStatus.pwmBroadcast = true;
		controllerData.motorData[1].odoBroadcastStatus.angleBroadcast = false;
		controllerData.motorData[1].odoBroadcastStatus.speedBroadcast = true;
		controllerData.motorData[1].odoBroadcastStatus.pwmBroadcast = true;

		if (controlInterface.SetOdoBroadcastStatus(0))
			std::cout << "Odometer broadcast status set successfully for motor 0" << std::endl;
		else
			std::cout << "Set failed for motor 0" << std::endl;
		if (controlInterface.SetOdoBroadcastStatus(1))
			std::cout << "Odometer broadcast status set successfully for motor 1" << std::endl;
		else
			std::cout << "Set failed for motor 1" << std::endl;
		std::cin >> dummy;







		


	}



}
