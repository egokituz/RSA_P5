/*
 * File:   Serial.h
 * Author: @bgamecho
 *
 * Created on October 13, 2015, 6:44 PM
 */

#ifndef SERIAL_H
#define	SERIAL_H

#pragma once
#include <cstdlib>
#include <unistd.h>
#include <iostream>
#include <wiringPi.h>
#include <wiringSerial.h>

class Serial
{
private:
    const char * portName;
    int fd_serial;
    int flag_debug;

public:
    Serial(void);
    Serial(const char * type);
    ~Serial(void);
    int connect();
    int send(char *data, int size);
    int receive(char *buffer, size_t size);
    void disconnect();
    void setVerboseMode(int val);
};


#endif	/* SERIAL_H */
