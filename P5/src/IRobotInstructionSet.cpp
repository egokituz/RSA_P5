/*
 * File:   IRobotInstructionSet.h
 * Author: Gorka Montero
 *
 * Created on 2012
 */

#include "IRobotInstructionSet.h"

iRobotInstructionSet::iRobotInstructionSet(void)
{
}

iRobotInstructionSet::~iRobotInstructionSet(void)
{
}

char iRobotInstructionSet::intHightByte( short num )
{
	return((char)(num>>8));
}

char iRobotInstructionSet::intLowByte( short num )
{
	return((  char) num);
}

Instruction iRobotInstructionSet::start()
{
	int miSize = 1;
	Instruction aux;
	aux.instruction = (  char*)malloc(miSize * sizeof(  char));
	aux.instruction[0] = iRobotInstructions::START;
	aux.length = miSize;
	return aux;
}

Instruction iRobotInstructionSet::baud(   char code )
{
	int miSize = 2;
	Instruction aux;
	aux.instruction = (  char*)malloc(miSize * sizeof(  char));
	aux.instruction[0] = iRobotInstructions::BAUD;
	aux.instruction[1] = code;
	aux.length = miSize;
	return aux;
}

Instruction iRobotInstructionSet::control()
{
	int miSize = 1;
	Instruction aux;
	aux.instruction = (  char*)malloc(miSize * sizeof(  char));
	aux.instruction[0] = iRobotInstructions::CONTROL;
	aux.length = miSize;
	return aux;

}

Instruction iRobotInstructionSet::safe()
{
	int miSize = 1;
	Instruction aux;
	aux.instruction = (  char*)malloc(miSize * sizeof(  char));
	aux.instruction[0] = iRobotInstructions::SAFE;
	aux.length = miSize;
	return aux;
}

Instruction iRobotInstructionSet::full()
{
	int miSize = 1;
	Instruction aux;
	aux.instruction = (  char*)malloc(miSize * sizeof(  char));
	aux.instruction[0] = iRobotInstructions::FULL;
	aux.length = miSize;
	return aux;
}

Instruction iRobotInstructionSet::spot()
{
	int miSize = 1;
	Instruction aux;
	aux.instruction = (  char*)malloc(miSize * sizeof(  char));
	aux.instruction[0] = iRobotInstructions::SPOT;
	aux.length = miSize;
	return aux;
}

Instruction iRobotInstructionSet::cover()
{
	int miSize = 1;
	Instruction aux;
	aux.instruction = (  char*)malloc(miSize * sizeof(  char));
	aux.instruction[0] = iRobotInstructions::COVER;
	aux.length = miSize;
	return aux;
}

Instruction iRobotInstructionSet::demo(   char code )
{
	int miSize = 2;
	Instruction aux;
	aux.instruction = (  char*)malloc(miSize * sizeof(  char));
	aux.instruction[0] = iRobotInstructions::DEMO;
	aux.instruction[1] = code;
	aux.length = miSize;
	return aux;
}

Instruction iRobotInstructionSet::drive( int speed, int radius )
{
	int miSize = 5;
	Instruction aux;
	aux.instruction = (  char*)malloc(miSize * sizeof(  char));
	aux.instruction[0] = iRobotInstructions::DRIVE;
	aux.instruction[1] = intHightByte(speed);
	aux.instruction[2] = intLowByte(speed);
	aux.instruction[3] = intHightByte(radius);
	aux.instruction[4] = intLowByte(radius);
	aux.length = miSize;
	return aux;
}

Instruction iRobotInstructionSet::lowSideDrivers(   char outputBit )
{
	int miSize = 2;
	Instruction aux;
	aux.instruction = (  char*)malloc(miSize * sizeof(  char));
	aux.instruction[0] = iRobotInstructions::LOW_SIDE_DRIVERS;
	aux.instruction[1] = outputBit;
	aux.length = miSize;
	return aux;
}

Instruction iRobotInstructionSet::leds( int ledBit, int ledColor, int ledIntensity )
{
	int miSize = 4;
	Instruction aux;
	aux.instruction = (  char*)malloc(miSize * sizeof(  char));
	aux.instruction[0] = iRobotInstructions::LEDS;
	aux.instruction[1] = ledBit;
	aux.instruction[2] = ledColor;
	aux.instruction[3] = ledIntensity;
	aux.length = miSize;
	return aux;
}

Instruction iRobotInstructionSet::song( int songNumber, int songSize,   char *song )
{
	int miSize = songSize+3;
	Instruction aux;
	aux.instruction = (  char*)malloc(miSize * sizeof(  char));
	aux.instruction[0] = iRobotInstructions::SONG;
	aux.instruction[1] = songNumber;
	aux.instruction[2] = (int)songSize/2;
	for (int i = 0; i < songSize; i++)
	{
		aux.instruction[i+3] = song[i];
	}
	aux.length = miSize;

	return aux;
}

Instruction iRobotInstructionSet::playSong(int songNumber)
{
	int miSize = 2;
	Instruction aux;
	aux.instruction = (  char*)malloc(miSize * sizeof(  char));
	aux.instruction[0] = iRobotInstructions::PLAY;
	aux.instruction[1] = songNumber;
	aux.length = miSize;
	return aux;
}

Instruction iRobotInstructionSet::updateSensor(   char sensorId )
{
	int miSize = 2;
	Instruction aux;
	aux.instruction = (  char*)malloc(miSize * sizeof(  char));
	aux.instruction[0] = iRobotInstructions::SENSORS;
	aux.instruction[1] = sensorId;
	aux.response = sensorReturn(sensorId);
	aux.length = miSize;
	return aux;
}

Instruction iRobotInstructionSet::coverAndDock()
{
	int miSize = 1;
	Instruction aux;
	aux.instruction = (  char*)malloc(miSize * sizeof(  char));
	aux.instruction[0] = iRobotInstructions::COVER_AND_DOCK;
	aux.length = miSize;
	return aux;
}

Instruction iRobotInstructionSet::pwmLowSideDrivers( int driver2,int driver1, int driver0 )
{
	int miSize = 4;
	Instruction aux;
	aux.instruction = (  char*)malloc(miSize * sizeof(  char));
	aux.instruction[0] = iRobotInstructions::PWM_LOW_SIDE_DRIVERS;
	aux.instruction[1] = driver2;
	aux.instruction[2] = driver1;
	aux.instruction[3] = driver0;
	aux.length = miSize;
	return aux;
}

Instruction iRobotInstructionSet::driveDirect( int rightVelocity, int leftVelocity )
{
	int miSize = 5;
	Instruction aux;
	aux.instruction = (  char*)malloc(miSize * sizeof(  char));
	aux.instruction[0] = iRobotInstructions::DRIVE_DIRECT;
	aux.instruction[1] = intHightByte(rightVelocity);
	aux.instruction[2] = intLowByte(rightVelocity);
	aux.instruction[3] = intHightByte(leftVelocity);
	aux.instruction[4] = intLowByte(leftVelocity);
	aux.length = miSize;
	return aux;
}

int iRobotInstructionSet::sensorReturn(   char sensor )
{
	if (sensor < 7) return 0;
	if (sensor < 19) return 1;
	if (sensor < 21) return 2;
	if (sensor == 21) return 1;
	if (sensor < 24) return 2;
	if (sensor == 24) return 1;
	if (sensor < 32) return 2;
	if (sensor == 32) return 1;
	if (sensor == 33) return 2;
	if (sensor < 39) return 1;
	if (sensor < 43) return 2;
	return 0;
}

Instruction iRobotInstructionSet::digitalOutputs( int outputBits )
{
	int miSize = 2;
	Instruction aux;
	aux.instruction = (  char*)malloc(miSize * sizeof(  char));
	aux.instruction[0] = iRobotInstructions::DIGITAL_OUTPUTS;
	aux.instruction[1] = (char) outputBits;
	aux.length = miSize;
	return aux;
}

Instruction iRobotInstructionSet::stream( char* sensorIdList, int size )
{
	int miSize = 2+ size;
	Instruction aux;
	aux.instruction = (  char*)malloc(miSize * sizeof(  char));
	aux.instruction[0] = iRobotInstructions::STREAM;
	aux.instruction[1] = size;
	for(int i = 0; i < size; i++) 
	{
		aux.instruction[i+2] = sensorIdList[i];
		aux.response += sensorReturn(sensorIdList[i]);
	}
	aux.length = miSize;
	return aux;
}

Instruction iRobotInstructionSet::queryList( char * sensorIdList, int size )
{
	int miSize = 2+ size;
	Instruction aux;
	aux.instruction = (  char*)malloc(miSize * sizeof(  char));
	aux.instruction[0] = iRobotInstructions::QUERY_LIST;
	aux.instruction[1] = size;
	for(int i = 0; i < size; i++) 
	{
		aux.instruction[i+2] = sensorIdList[i];
		aux.response += sensorReturn(sensorIdList[i]);
	}
	aux.length = miSize;
	return aux;
}

Instruction iRobotInstructionSet::PauseResumeStream( bool bol )
{
	int miSize = 2;
	Instruction aux;
	aux.instruction = (  char*)malloc(miSize * sizeof(  char));
	aux.instruction[0] = iRobotInstructions::PAUSE_RESUME_STREAM;
	aux.instruction[1] = (char) bol;
	aux.length = miSize;
	return aux;
}

Instruction iRobotInstructionSet::sendIr( int data )
{
	int miSize = 2;
	Instruction aux;
	aux.instruction = (  char*)malloc(miSize * sizeof(  char));
	aux.instruction[0] = iRobotInstructions::SEND_IR;
	aux.instruction[1] = (char)data;
	aux.length = miSize;
	return aux;
}

Instruction iRobotInstructionSet::script( int *commandList, int size )
{
	int miSize = 2+ size;
	Instruction aux;
	aux.instruction = (  char*)malloc(miSize * sizeof(  char));
	aux.instruction[0] = iRobotInstructions::SCRIPT;
	aux.instruction[1] = size;
	for(int i = 0; i < size; i++) aux.instruction[i+2] = commandList[i];
	aux.length = miSize;
	return aux;
}

Instruction iRobotInstructionSet::playScript()
{
	int miSize = 1;
	Instruction aux;
	aux.instruction = (  char*)malloc(miSize * sizeof(  char));
	aux.instruction[0] = iRobotInstructions::PLAY_SCRIPT;
	aux.length = miSize;
	return aux;
}

Instruction iRobotInstructionSet::showScript()
{
	int miSize = 1;
	Instruction aux;
	aux.instruction = (  char*)malloc(miSize * sizeof(  char));
	aux.instruction[0] = iRobotInstructions::SHOW_SCRIPT;
	aux.length = miSize;
	return aux;
}

Instruction iRobotInstructionSet::waitTime( int seconds )
{
	int miSize = 2;
	Instruction aux;
	aux.instruction = (  char*)malloc(miSize * sizeof(  char));
	aux.instruction[0] = iRobotInstructions::WAIT_TIME;
	aux.instruction[1] = seconds;
	aux.length = miSize;
	return aux;
}

Instruction iRobotInstructionSet::waitDistance( int mm )
{
	int miSize = 3;
	Instruction aux;
	aux.instruction = (  char*)malloc(miSize * sizeof(  char));
	aux.instruction[0] = iRobotInstructions::WAIT_DISTANCE;
	aux.instruction[1] = intHightByte(mm);
	aux.instruction[2] = intLowByte(mm);
	aux.length = miSize;
	return aux;
}

Instruction iRobotInstructionSet::waitAngle( int degrees )
{
	int miSize = 3;
	Instruction aux;
	aux.instruction = (  char*)malloc(miSize * sizeof(  char));
	aux.instruction[0] = iRobotInstructions::WAIT_ANGLE;
	aux.instruction[1] = intHightByte(degrees);
	aux.instruction[2] = intLowByte(degrees);
	aux.length = miSize;
	return aux;
}

Instruction iRobotInstructionSet::waitEvent( int eventId )
{
	int miSize = 2;
	Instruction aux;
	aux.instruction = (  char*)malloc(miSize * sizeof(  char));
	aux.instruction[0] = iRobotInstructions::WAIT_EVENT;
	aux.instruction[1] = (char) eventId;
	aux.length = miSize;
	return aux;
}





