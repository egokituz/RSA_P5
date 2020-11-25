/*
 * File:   IRobotConnection.cpp
 * Author: Gorka Montero
 *
 * Created on 2012
 */

#include "IRobotConnection.h"

using namespace std;

IRobotConnection::IRobotConnection(void)
{
    buffer = (char *) malloc(512*sizeof (char));

    connection = Serial();

  // useArduino = false;
	// simulated = true;
}


IRobotConnection::IRobotConnection(const char * connectionType )
{
	buffer = (char *) malloc(512*sizeof (char));

  connection = Serial(connectionType);
	//useArduino  = false;
	//simulated = (connectionType == "sim");
}


IRobotConnection::~IRobotConnection(void)
{

}


int IRobotConnection::createInt( char* aux, int hight /*= 0*/, int low /*= 1*/ )
{
	return (aux [low]+ (aux[hight]<<8));
}


int IRobotConnection::connect()
{
//       if(!simulated)	this->useArduino = useArduino;
	return connection.connect();
}

void IRobotConnection::disconnect()
{
	connection.disconnect();
}

void IRobotConnection::start()
{
	Instruction aux = iRobotInstructionGenerator.start();
	connection.send(aux.instruction, aux.length);
        
}

void IRobotConnection::baud( char code )
{
	Instruction aux = iRobotInstructionGenerator.baud(code);
	connection.send(aux.instruction, aux.length);
}

void IRobotConnection::control()
{
	Instruction aux = iRobotInstructionGenerator.control();
	connection.send(aux.instruction, aux.length);
}

void IRobotConnection::safe()
{
	Instruction aux = iRobotInstructionGenerator.safe();
	connection.send(aux.instruction, aux.length);
        
}

void IRobotConnection::full()
{
	Instruction aux = iRobotInstructionGenerator.full();
	connection.send(aux.instruction, aux.length);
        delay(200); 
}

void IRobotConnection::spot()
{
	Instruction aux = iRobotInstructionGenerator.spot();
	connection.send(aux.instruction, aux.length);
}

void IRobotConnection::cover()
{
	Instruction aux = iRobotInstructionGenerator.cover();
	connection.send(aux.instruction, aux.length);
}

void IRobotConnection::demo( char code )
{
	Instruction aux = iRobotInstructionGenerator.demo(code);
	connection.send(aux.instruction, aux.length);
}

void IRobotConnection::drive( int speed, int radius )
{
	Instruction aux = iRobotInstructionGenerator.drive(speed,radius);
	connection.send(aux.instruction, aux.length);
}

void IRobotConnection::lowSideDrivers( char outputBit )
{
	Instruction aux = iRobotInstructionGenerator.lowSideDrivers(outputBit);
	connection.send(aux.instruction, aux.length);
}

void IRobotConnection::leds( int ledBit, int ledColor, int ledIntensity )
{
	Instruction aux = iRobotInstructionGenerator.leds(ledBit,ledColor,ledIntensity);
	connection.send(aux.instruction, aux.length);
}

void IRobotConnection::song( int songNumber, int songSize, char *song )
{
	Instruction aux = iRobotInstructionGenerator.song(songNumber,songSize,song);
	connection.send(aux.instruction, aux.length);
}

void IRobotConnection::playSong(int songNumber)
{
	Instruction aux = iRobotInstructionGenerator.playSong(songNumber);
	connection.send(aux.instruction, aux.length);
}

int IRobotConnection::updateSensor( char sensorId )
{
	Instruction aux = iRobotInstructionGenerator.updateSensor(sensorId);
	connection.send(aux.instruction, aux.length);
	connection.receive(buffer,aux.response);
	if (aux.response == 2) return(createInt(buffer));
	return buffer[0];
}

void IRobotConnection::coverAndDock()
{
	Instruction aux = iRobotInstructionGenerator.coverAndDock();
	connection.send(aux.instruction, aux.length);
}

void IRobotConnection::pwmLowSideDrivers( int driver2,int driver1, int driver0 )
{
	Instruction aux = iRobotInstructionGenerator.pwmLowSideDrivers(driver2,driver1,driver0);
	connection.send(aux.instruction, aux.length);
}

void IRobotConnection::driveDirect( int rightVelocity, int leftVelocity )
{
	Instruction aux = iRobotInstructionGenerator.driveDirect(rightVelocity,leftVelocity);
	connection.send(aux.instruction, aux.length);
}

void IRobotConnection::digitalOutputs( int outputBits )
{
	Instruction aux = iRobotInstructionGenerator.digitalOutputs(outputBits);
	connection.send(aux.instruction, aux.length);
}

void IRobotConnection::stream( char* sensorIdList, int size )
{
	Instruction aux = iRobotInstructionGenerator.stream(sensorIdList,size);
	connection.send(aux.instruction, aux.length);
}

int IRobotConnection::queryList( char * sensorIdList, int size )
{
	Instruction aux = iRobotInstructionGenerator.queryList(sensorIdList,size);
	connection.send(aux.instruction, aux.length);
	connection.receive(buffer,aux.response);
	return aux.response;
}

void IRobotConnection::PauseResumeStream( bool bol )
{
	Instruction aux = iRobotInstructionGenerator.PauseResumeStream(bol);
	connection.send(aux.instruction, aux.length);
}

void IRobotConnection::sendIr( int data )
{
	Instruction aux = iRobotInstructionGenerator.sendIr(data);
	connection.send(aux.instruction, aux.length);
}

void IRobotConnection::script( int *commandList, int size )
{
	Instruction aux = iRobotInstructionGenerator.script(commandList,size);
	connection.send(aux.instruction, aux.length);
	lastScriptSize = size;
}

void IRobotConnection::playScript()
{
	Instruction aux = iRobotInstructionGenerator.playScript();
	connection.send(aux.instruction, aux.length);
}

void IRobotConnection::showScript()
{
	Instruction aux = iRobotInstructionGenerator.showScript();
	connection.send(aux.instruction, aux.length);
	connection.receive(buffer,lastScriptSize);
}

void IRobotConnection::waitTime( int seconds )
{
	Instruction aux = iRobotInstructionGenerator.waitTime(seconds);
	connection.send(aux.instruction, aux.length);
}

void IRobotConnection::waitDistance( int mm )
{
	Instruction aux = iRobotInstructionGenerator.waitDistance(mm);
	connection.send(aux.instruction, aux.length);
}

void IRobotConnection::waitAngle( int degrees )
{
	Instruction aux = iRobotInstructionGenerator.waitAngle(degrees);
	connection.send(aux.instruction, aux.length);
}

void IRobotConnection::waitEvent( int eventId )
{
	Instruction aux = iRobotInstructionGenerator.waitEvent(eventId);
	connection.send(aux.instruction, aux.length);
}

void IRobotConnection::setVerboseMode(int flag_debug){
	if(flag_debug==1){
		connection.setVerboseMode(1);
	}else{
		connection.setVerboseMode(0);			
	}
}
