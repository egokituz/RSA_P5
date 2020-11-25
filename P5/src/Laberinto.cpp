//Laberinto

#include "Laberinto.h"
#include<iostream>

using namespace std;

/**
*	Constructora sin par�metros
*/
Laberinto::Laberinto(void)
{
	cargarLaberinto("xml/Rejilla.xml");
	situarRobot(0,0,SUR);

	path =  (struct camino *) malloc (sizeof(camino));
	first =  (struct camino *) malloc (sizeof(camino));
	path->nodo_actual=iCreate.nodo_actual;
	path->anterior=NULL;
	path->siguiente=NULL;
	first = path;
}

/**
*	Constructora a partir de un fiichero XML 
*		Const char* pFilename: Fichero XML con un laberinto codificado
*/
Laberinto::Laberinto(const char* pFilename)
{
	cargarLaberinto(pFilename);
	situarRobot(0,0,SUR);

	path =  (struct camino *) malloc (sizeof(camino));
	first =  (struct camino *) malloc (sizeof(camino));
	path->nodo_actual=iCreate.nodo_actual;
	path->anterior=NULL;
	path->siguiente=NULL;
	first = path;
}

/**
*	Constructora 
* 		Const char* pFilename: Fichero XML con un laberinto codificado
*		int x: posici�n del robot en el eje horizontal
*		int y: posici�n del robot en el eje vertical  
*		char orientaci�n: {NORTE, SUR, ESTE, OESTE}
*/
Laberinto::Laberinto(const char* pFilename, int x, int y, char orientacion){
	cargarLaberinto(pFilename);
	situarRobot(x,y,orientacion);

	path =  (struct camino *) malloc (sizeof(camino));
	first =  (struct camino *) malloc (sizeof(camino));
	path->nodo_actual=iCreate.nodo_actual;
	path->anterior=NULL;
	path->siguiente=NULL;
	first = path;
}

/**
*	Destructora clase Mapa
*/
Laberinto::~Laberinto(void)
{

}

/**
*	Parsea el fichero XML del laberinto en memoria e inicializa la estructura Matriz
*		const char* pFilename: el path al fichero que deseamos cargar
*/
void Laberinto::cargarLaberinto(const char* pFilename){

	TiXmlDocument doc(pFilename);
	bool loadOkay = doc.LoadFile();

	if (loadOkay)
	{
		cout << "Cargado fichero: " << pFilename <<"\r"<< endl;

		TiXmlHandle hDoc(&doc);
		TiXmlHandle aux =hDoc.FirstChildElement();

		const char *str_nombre = aux.Element()->Value();
		if(strcmp(str_nombre,"Laberinto")!=0){
			cout << "Error en el fichero XML, etiqueta [Laberinto] esperada, etiqueta [";
			cout << str_nombre << "] encontrada" <<"\r"<<endl;
			exit(-1);
		}

		const char *str_attr_nombre = aux.Element()->Attribute("nombre");
		const char *str_attr_dim_x = aux.Element()->Attribute("dim_x");
		const char *str_attr_dim_y = aux.Element()->Attribute("dim_y");

		nombre = str_attr_nombre;
		dim_x = atoi(str_attr_dim_x);
		dim_y = atoi(str_attr_dim_y);
		//cout << dim_x << " " << dim_y << endl;

		matriz = new nodo *[dim_x];
	    for(int i = 0; i<dim_x;i++) {
	      matriz[i] = new nodo[dim_y];
			for(int j = 0; j<dim_y; j++){
				matriz[i][j].x = i;
				matriz[i][j].y = j;
				matriz[i][j].Norte=NULL;
				matriz[i][j].Sur=NULL;
				matriz[i][j].Este=NULL;
				matriz[i][j].Oeste=NULL;
			}
	    }

		//	cout << str_nombre << "Nombre: " << str_attr_nombre << " " << str_attr_dim_x << " " << str_attr_dim_y << endl;

		procesarNodos(&aux);

	}else{
		cout << "Fallo al cargar el fichero: " << pFilename <<"\r"<< endl;
	}
}

/**
*	Recorre todos los nodos del fichero XML y actualiza los valores x e y de la estructura Matriz
*		TiXmlHandle * hParent: Puntero a un elemento "Laberinto" del fichero XML
*/
void Laberinto::procesarNodos( TiXmlHandle * hParent){

    TiXmlNode * pChild;

    //int i =0 ;

    for ( pChild = hParent->FirstChild().Node(); pChild != 0; pChild = pChild->NextSibling())
    {
    	TiXmlHandle aux(pChild);

   	    const char *str_nombre = aux.Element()->Value();
		if(strcmp(str_nombre,"Nodo")!=0){
			cout << "Error en el fichero XML, etiqueta [Nodo] esperada, etiqueta [";
			cout << str_nombre << "] encontrada" <<"\r"<<endl;
			exit(-1);
		}


   	    const char *str_attrX = aux.Element()->Attribute("x");
   	    const char *str_attrY = aux.Element()->Attribute("y");

   	  //  cout << " " << ++i << "- " << str_nombre << "- Atributos {" << str_attrX << "," << str_attrY << "}" << endl;
        procesarCaminos(&aux, atoi(str_attrX), atoi(str_attrY));

    }

}

/**
*	Recorre todos los caminos de un nodo en el fichero XML  y actualiza los valores arriba, abajo, izquierda, derecha de Matriz
*		TiXmlHandle * hNodo: Puntero a un elemento "Nodo" del fichero XML
*		int pos_x:	Posici�n en el eje horizontal del nodo
*		int pos_y:	Posici�n en el eje vertical del nodo
*/
void Laberinto::procesarCaminos( TiXmlHandle *hNodo, int pos_x, int pos_y){

    TiXmlNode * pChild;

    //int i =0 ;

    for ( pChild = hNodo->FirstChild().Node(); pChild != 0; pChild = pChild->NextSibling())
    {
    	TiXmlHandle aux(pChild);

   	    const char *str_nombre = aux.Element()->Value();
		if(strcmp(str_nombre,"Camino")!=0){
			cout << "Error en el fichero XML, etiqueta [Camino] esperada, etiqueta [";
			cout << str_nombre << "] encontrada" <<"\r"<<endl;
			exit(-1);
		}
   	    const char *str_attrDir = aux.Element()->Attribute("dir");

   	    if(strcmp(str_attrDir, "arriba")==0){
   	    	matriz[pos_x][pos_y].Norte = &matriz[pos_x][pos_y-1];
   	    }else  if(strcmp(str_attrDir, "abajo")==0){
   	    	matriz[pos_x][pos_y].Sur = &matriz[pos_x][pos_y+1];
   	    }else if(strcmp(str_attrDir, "derecha")==0){
   	    	matriz[pos_x][pos_y].Este = &matriz[pos_x+1][pos_y];
   	    }else if(strcmp(str_attrDir, "izquierda")==0){
   	    	matriz[pos_x][pos_y].Oeste = &matriz[pos_x-1][pos_y];
   	    }

   	    // cout << "\t " << ++i << "- " << str_nombre << " Atributos {" << str_attrDir << "}" << endl;
    }

}

/**
*	Asocia un nodo del laberinto/matriz al Robot
*		int pos_x:	Posici�n en el eje horizontal del nodo
*		int pos_y:	Posici�n en el eje vertical del nodo
*		char orientacion: Orientaci�n en la que parte el robot
*/
void Laberinto::situarRobot(int pos_x, int pos_y, char orientacion){
	iCreate.nodo_actual = &matriz[pos_x][pos_y];
	iCreate.orientacion = orientacion;
}

/**
*	Devuelve la posici�n del robot en el laberinto
*		int* pos_x:	Guarda el valor del eje horizontal
*		int* pos_y:	Guarda el valor del eje vertical
*		char* orientacion: Guarda la orientaci�n del robot
*/
void Laberinto::getPosRobot(int *pos_x, int *pos_y, char * orientacion){
	*pos_x = iCreate.nodo_actual->x;
	*pos_y = iCreate.nodo_actual->y;
	*orientacion = iCreate.orientacion;
}

/**
*	Consulta si el robot tiene la siguiente posici�n al sur disponible
*		return bool: true si hay un nodo al Sur
*/
bool Laberinto::esSurLibre(){
	return (iCreate.nodo_actual->Sur!=NULL);
}

/**
*	Consulta si el robot tiene la siguiente posici�n al norte disponible
*		return bool: true si hay un nodo al Norte
*/
bool Laberinto::esNorteLibre(){
	return (iCreate.nodo_actual->Norte!=NULL);
}

/**
*	Consulta si el robot tiene la siguiente posici�n al este disponible
*		return bool: true si hay un nodo al Este
*/
bool Laberinto::esEsteLibre(){
	return (iCreate.nodo_actual->Este!=NULL);
}

/**
*	Consulta si el robot tiene la siguiente posici�n al oeste disponible
*		return bool: true si hay un nodo al Oeste
*/
bool Laberinto::esOesteLibre(){
	return (iCreate.nodo_actual->Oeste!=NULL);
}

/**
*	Orienta el robot hacia la direcci�n Norte en el mapa
*/
void Laberinto::orientarRobotNorte(){
	iCreate.orientacion=NORTE;
}

/**
*	Orienta el robot hacia la direcci�n Sur en el mapa
*/
void Laberinto::orientarRobotSur(){
	iCreate.orientacion=SUR;
}

/**
*	Orienta el robot hacia la direcci�n Este en el mapa
*/
void Laberinto::orientarRobotEste(){
	iCreate.orientacion=ESTE;
}

/**
*	Orienta el robot hacia la direcci�n Oeste en el mapa
*/
void Laberinto::orientarRobotOeste(){
	iCreate.orientacion=OESTE;
}

/**
*	A�ade un nodo visitado en el camino del robot
*		robot *aux: la estructura con la informaci�n de la posici�n del robot
*/
void Laberinto::modificarCamino(robot *aux){
	
	struct camino * siguiente = (struct camino *) malloc (sizeof(camino));

	siguiente->nodo_actual = aux->nodo_actual;
	siguiente->anterior = path;
	siguiente->siguiente = NULL;
	path->siguiente = siguiente;

	path = siguiente;
}

/**
*	Muestra por pantalla el camino que ha seguido el robot 
*/
void Laberinto::imprimirCaminoRobot(){

	struct camino * aux; // = (struct camino *) malloc (sizeof(camino));
	aux = first;

	cout << "imprimiendo el camino: "<<"\r"<<endl;
	cout << "[" << aux->nodo_actual->x << "," << aux->nodo_actual->y <<"] ";
	while(aux->siguiente!=NULL){
		aux = aux->siguiente;
		cout << "[" << aux->nodo_actual->x << "," << aux->nodo_actual->y <<"] ";
	}
	cout<<"\r"<< endl;

}

/**
*	Avanza al nodo situado al Norte del robot
*		return int: -1 en caso de que no exista nodo al que avanzar
*/
int Laberinto::avanzaNorte(){
	if(esNorteLibre()){
		orientarRobotNorte();
		iCreate.nodo_actual= iCreate.nodo_actual->Norte;

		modificarCamino(&iCreate);

		return 0;
	}else{
		return -1;
	}
}

/**
*	Avanza al nodo situado al Sur del robot
*		return int: -1 en caso de que no exista nodo al que avanzar
*/
int Laberinto::avanzaSur(){
	if(esSurLibre()){
		orientarRobotSur();
		iCreate.nodo_actual= iCreate.nodo_actual->Sur;

		modificarCamino(&iCreate);

		return 0;
	}else{
		return -1;
	}
}

/**
*	Avanza al nodo situado al Este del robot
*		return int: -1 en caso de que no exista nodo al que avanzar
*/
int Laberinto::avanzaEste(){
	if(esEsteLibre()){
		orientarRobotEste();
		iCreate.nodo_actual= iCreate.nodo_actual->Este;

		modificarCamino(&iCreate);

		return 0;
	}else{
		return -1;
	}
}

/**
*	Avanza al nodo situado al Oeste del robot
*		return int: -1 en caso de que no exista nodo al que avanzar
*/
int Laberinto::avanzaOeste(){
	if(esOesteLibre()){
		orientarRobotOeste();
		iCreate.nodo_actual= iCreate.nodo_actual->Oeste;

		modificarCamino(&iCreate);

		return 0;
	}else{
		return -1;
	}
}

/**
*	Muestra por pantalla el laberinto y la posici�n del robot
*/
void Laberinto::imprimirLaberinto(){
	cout<<"Imprimiendo: "<< nombre << " Dimensiones x: "<< dim_x << " y: " << dim_y <<"\r" << endl;

	int x_robot;
	int y_robot;
	char orientacion_robot;
	string str;
	this->getPosRobot(&x_robot,&y_robot,&orientacion_robot);
	switch(orientacion_robot){
		case NORTE:
			str = "Norte";
			break;
		case SUR:
			str = "SUR";
			break;
		case ESTE:
			str = "ESTE";
			break;
		case OESTE:
			str = "OESTE";
			break;
		default:
			break;
	}

	cout<<"Robot en posicion: (" << x_robot << "," << y_robot <<") orientacion: "<<str<<"\n\r";


	for(int j=0;j<dim_y; j++){
		// Primer for para la dirección Norte
		for(int i=0; i<dim_x; i++){
			if(matriz[i][j].Norte!=NULL){
				if(iCreate.nodo_actual->x == i & iCreate.nodo_actual->y == j & iCreate.orientacion == NORTE){
					cout << "  ^  ";
				}else{
					cout << "  |  ";  	// Si hay conexión hacia el NORTE
				}
			}else{
				cout << "     ";
			}
		}
		cout <<"\r"<< endl;
		// Segundo for para las direcciones Este y Oeste
		for(int i=0; i<dim_x; i++){
			if(matriz[i][j].Oeste!=NULL){
				if(iCreate.nodo_actual->x == i & iCreate.nodo_actual->y == j & iCreate.orientacion == OESTE){
					cout << "<<";
				}else{
					cout << "--";	// Si hay conexión hacia el OESTE
				}
			}else{
				cout << "  ";
			}

			if(iCreate.nodo_actual->x == i & iCreate.nodo_actual->y == j ){
				switch(iCreate.orientacion){
				case NORTE:
					cout << "^";
					break;
				case SUR:
					cout << "v";
					break;
				case ESTE:
					cout << ">";
					break;
				case OESTE:
					cout << "<";
					break;
				default:
					break;
				}
			}else{
				cout << "+";
			}

		//	cout << "(" << matriz[i][j].x << "," << matriz[i][j].y << ") " << endl;
			if(matriz[i][j].Este!=NULL){
				if(iCreate.nodo_actual->x == i & iCreate.nodo_actual->y == j & iCreate.orientacion == ESTE){
					cout << ">>";
				}else{
					cout << "--";	// Si hay conexión hacia el ESTE
				}
			}else{
				cout << "  ";
			}
		}
		cout <<"\r"<< endl;

		// Tercer for para la direccion Sur
		for(int i=0; i<dim_x; i++){
			if(matriz[i][j].Sur!=NULL){
				if(iCreate.nodo_actual->x == i & iCreate.nodo_actual->y == j & iCreate.orientacion == SUR){
					cout << "  v  ";
				}else{
					cout << "  |  ";  	// Si hay conexión hacia el SUR
				}
			}else{
				cout << "     ";
			}
		}
		cout <<"\r"<< endl;
	}

}

/**
*	M�todo que obtiene el camino entre un nodo de entrada [x_orig, y_orig] y un nodo de 
*	salida [x_dest, y_dest].  
*		int x_orig: Posici�n origen del robot en la Matriz del laberinto
*		int y_orig: Posici�n origen del robot en la Matriz del laberinto
*		int x_dest: Posici�n destino del robot en la Matriz del laberinto
*		int y_dest: Posici�n destino del robot en la Matriz del laberinto
*		return camino*: Apuntador a una estructura tipo camino con la solucion
*/
camino*  Laberinto::encontrarCamino(int x_orig, int y_orig, int x_dest, int y_dest){
	struct camino* solucion  = (struct camino *) malloc (sizeof(camino));
	
	// ... A COMPLETAR EN LA PR�CTICA
	
	return solucion;
}

/**
*	Funci�n que a�ade un nodo nuevo a un camino 
*		camino **cam: Puntero doble a la estructura camino que se va a modificar
*		nodo **aux: Puntero doble al nodo que se quiere a�adir en el camino
*/
void Laberinto::modificarCamino(camino** cam, nodo **aux){
	
	struct camino * siguiente = (struct camino *) malloc (sizeof(camino));

	siguiente->nodo_actual = *aux;
	siguiente->anterior = *cam;
	siguiente->siguiente = NULL;
	
	(*cam)->siguiente = siguiente;
	*cam = siguiente;
}

/**
*	Muestra por pantalla el camino que se pasa por par�metro
*		camino *first_element: Primer elemento de una lista del tipo camino
*/
void Laberinto::imprimirCamino(camino *first_element){
		
	// Recorre la solucion encontrada
	struct camino * aux; // = (struct camino *) malloc (sizeof(camino));
	aux = first_element;

	cout << "[" << aux->nodo_actual->x << "," << aux->nodo_actual->y <<"] ";
	while(aux->siguiente!=NULL){
		aux = aux->siguiente;
		cout << "[" << aux->nodo_actual->x << "," << aux->nodo_actual->y <<"] ";
	}
	cout <<"\r"<< endl; 
} 
	 


