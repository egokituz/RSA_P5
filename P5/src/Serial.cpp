/*
 * File:   Serial.cpp
 * Author: @bgamecho
 *
 * Created on October 13, 2015, 6:44 PM
 */

#include "Serial.h"

using namespace std;

Serial::Serial(void){
    portName = "/dev/ttyUSB0";
    flag_debug = 0;
}

Serial::Serial(const char * type){
    portName = type;
    flag_debug = 0;
}

Serial::~Serial(void){
}

int Serial::connect(){
    fd_serial = serialOpen(portName, 57600);
    if(fd_serial < 0 ){
        if(flag_debug){
            std::cout << "[V]\tError opening port: " << portName << std::endl;
        }
        return false;
    }
    return true;
}

int Serial::send(char *data, int size){
   int index;

   if(flag_debug){
     std::cout << "[V]\tSend command: " << std::endl;
     std::cout << "[V]\t\tCommand size: " << size << std::endl;
   }

   for (index = 0; index < size; index++){
        serialPutchar(fd_serial,  data[index]);
        if(flag_debug){
          std::cout << "[V]\t\t" << index << " - "  << +data[index] << std::endl;
        }
        delay(10); // wait 10 ms to send the command
    }

   return 0;
}

int Serial::receive(char *buffer, size_t size){
    int index;

    if(flag_debug){
      std::cout << "[V]\tReceive command: " << std::endl;
    }
    delay(10); // wait some time before receiving data

    for (index = 0; index < (int) size; index++){
        if(flag_debug){
          int val =  serialDataAvail(fd_serial) ;
          std::cout << "[V]\t\tBytes available for reading: " << val << std::endl;
        }

        int aux = serialGetchar(fd_serial);
        buffer[index] = (char) aux;

        if(flag_debug){
          std::cout << "[V]\t\t"<< index <<" Read:  " << +aux << std::endl;
        }
    }
    
    return 0;
}

void Serial::disconnect(){
    serialClose(fd_serial);
}

void Serial::setVerboseMode(int val){
  if (val == 0){
    flag_debug = 0;
  }else{
    flag_debug = 1;
  }
}
