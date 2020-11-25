// ControlRobot .cpp

#include "ControlRobot.h"
#include<iostream>

using namespace std;

// Estados de la lógica
#define INICIAL 5
#define SIGUE 1
#define BUSCA 0

// Estados para los motores
#define GIRAR_DERECHA 		0
#define GIRAR_IZQUIERDA		1
#define RECTO				2
#define PARADO				3

#define DUCT_TAPE(value) (value < 500)

/**
*	Constructora objeto ControlRobot
*/
ControlRobot::ControlRobot(void)
{
	
}

/**
*	Destructora objeto ControlRobot
*/
ControlRobot::~ControlRobot(void)
{
	
}

/**
* 	Prepara la conexión IRobotConnection e inicializa todas
*	las variables que necesitemos en el programa
*/
void ControlRobot::inicializacion(void)
{
	
	int COM_port;
	char puerto[30];
	
	// Solicitamos el puerto COM por entrada estándar
	//cout << "Puerto COM: ";
	//cin >> COM_port;
	//sprintf(puerto, "COM%d",COM_port);
	
	sprintf(puerto,"/dev/ttyUSB0");


	robot = new IRobotConnection(puerto);
	
	// Iniciamos la conexión
	cout << "Connecting... ";
	robot->connect();
	cout << "Done!!\n\r" << endl;
	
	// Comando 128 start
	robot->start();
	delay(500); // Esperamos medio segundo a que cambie de modo

	// Comando 132 modo full
	robot->full();
	delay(500); // Esperamos medio segundo a que cambie de modo
	
	estado_actual = INICIAL;
	estado_anterior = INICIAL;
	motores = PARADO;
		
}

/**
* 	Calcula si se han dado las condiciones necesarias para terminar el programa
*	return bool: 
*		- true para terminar
*		- false para continuar al menos un ciclo más
*/
bool ControlRobot::condicionSalida()
{
	return false; // nos mantenemos siempre dentro del bucle
}

/**
*	Obtiene y trata la información de los sensores relevantes al programa, 
*	para ello usa la struct Sensores_iCreate sensores;
*/
void ControlRobot::leerSensores()
{
	sensores.front_left = robot->updateSensor(iRobotSensors::CLIFFFRONTLEFTSIGNAL );
	// Ajustamos el valor al máximo permitido por la especificación OI
	if(sensores.front_left>4095) sensores.front_left=4095;
	
	sensores.fl = DUCT_TAPE(sensores.front_left);
}

/**
*	Contiene la lógica del programa
*/
void ControlRobot::logicaEstados()
{		
	// Actualizamos los estados: 
	estado_anterior = estado_actual;		
	
	if(sensores.fl){
		estado_actual = SIGUE;
	}else{
		estado_actual = BUSCA;
	}
	
	// Se decide que hacer con los parametros del robot
	switch(estado_actual){	
		case SIGUE:
			motores = RECTO;
			break;		
		case BUSCA:
			motores = GIRAR_DERECHA;
			break;
		default:
			break;
	}
	
}

/**
*  	Activa los actuadores correspondientes en función de lo decidido 
*	en la lógica del programa 
*/
void ControlRobot::moverActuadores()
{
	switch(motores){
		case PARADO:
			actuadores.vel_der = 0;
			actuadores.vel_izq = 0;
			break;
		case RECTO:
			actuadores.vel_der = 170;
			actuadores.vel_izq = 170;
			robot->leds( 3, 90,200 );
			break;
		case GIRAR_DERECHA:
			actuadores.vel_der = -50;
			actuadores.vel_izq = 50;
			robot->leds( 3, 0,0 );
			break;
		default:
			break;
	}
	
	robot->driveDirect(actuadores.vel_der, actuadores.vel_izq);
	
}

/**
*	Muestra información relevante al usuario
*/
void ControlRobot::imprimirInfo(void)
{
	char estado[20];
	switch(estado_actual){
		case INICIAL : 	sprintf(estado,"INICIAL");	break;
		case SIGUE : 	sprintf(estado,"SIGUE");	break;
		case BUSCA : 	sprintf(estado,"BUSCA");	break;
	}
	
	printf("Estado: %s ",estado);
	printf(": %s ", sensores.fl ? "true" : "false");
	printf(" Valor: %d",	sensores.front_left);
	printf("\n\r");
}

/**
*	Cierra conexiones abiertas
*/
void ControlRobot::finalizacion(void)
{
	robot->disconnect();
	delete robot;
}

