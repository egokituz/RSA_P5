/*
 * File:   IRobotConnection.h
 * Author: Gorka Montero
 *
 * Created on 2012
 */

#ifndef IROBOTCONNECTION_H
#define	IROBOTCONNECTION_H

#pragma once
#include <iostream>
#include "IRobotInstructionSet.h"
#include "Serial.h"

class IRobotConnection
{
private:

  			// bool simulated;
				// bool useArduino;

        Serial connection;

        iRobotInstructionSet iRobotInstructionGenerator;

        //If we want to implement some instruction with the Arduino board pins we must use this instruction set
				//ArduinoInstructionSet ArduinoInstructionGenerator;

        char * buffer;

	//************************************
	// Method:    createInt
	// Returns:   int				[out]	integer that we want to create
	// Parameter: char * aux			[in]	Buffer where the hight byte and low byte of the integer are
	// Parameter: int hight				[in]	Position of the hight byte in the buffer
	// Parameter: int low				[in]	Position of the low byte in the buffer
	//************************************
	int createInt(char* aux, int hight = 0, int low = 1);

	int lastScriptSize;						//	Stores the last script size sent to the robot
public:


	//************************************
	// Method:    IRobotConnection
	// Description:												Starts the connection using the simulator
	//************************************
	IRobotConnection(void);
	//************************************
	// Method:    IRobotConnection
	// Parameter: char * connectionType					[in]	"sim" if we want to use the simulator, COMx if we want to use the serial communication
	//************************************
	IRobotConnection(const char * connectionType);
	~IRobotConnection(void);

	//************************************
	// Method:    connect
	// Parameter: bool useArduino						[in]	True -> if serial comunication is going on it will choose Arduino config
	// Description:										Starts the connection
	//************************************
	int connect();
	void disconnect();
	void start();
	void baud(  char code);
	void control();
	void safe();
	void full();
	void spot();
	void cover();
	void demo(  char code);
	void drive(int speed, int radius);
	void lowSideDrivers(  char outputBit);
	void leds(int ledBit, int ledColor, int ledIntensity);
	void song (int songNumber, int songSize,   char *song);
	void playSong(int songNumber);
	int updateSensor(  char sensorId);
	void coverAndDock();
	void pwmLowSideDrivers(int driver2,int driver1, int driver0);
	void driveDirect(int rightVelocity, int leftVelocity);
	void digitalOutputs(int outputBits);
	void stream(char* sensorIdList, int size);
	int queryList(char * sensorIdList, int size);
	void PauseResumeStream(bool bol);
	void sendIr(int data);
	void script(int *commandList, int size);
	void playScript();
	void showScript();
	void waitTime(int seconds);
	void waitDistance(int mm);
	void waitAngle(int degrees);
	void waitEvent(int eventId);

  void setVerboseMode(int flag_debug);
};

#endif