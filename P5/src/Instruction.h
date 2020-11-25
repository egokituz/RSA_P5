/*
 * File:   Instruction.h
 * Author: Gorka Montero
 *
 * Created on 2012
 */

#ifndef INSTRUCTION_H
#define	INSTRUCTION_H

#pragma once
#include <malloc.h>

class Instruction{
public:
	char * instruction; //Instruction bytes
	int length;			//How many bytes compose the instruction
	int response;		//How many bytes will the instruction generate as return by the machine

	Instruction();
	~Instruction(){}
	Instruction & operator=(const Instruction &aux);
};

#endif