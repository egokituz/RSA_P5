/*
 * File:   Instruction.cpp
 * Author: Gorka Montero
 *
 * Created on 2012
 */

#include "Instruction.h"

Instruction::Instruction()
{
	instruction = nullptr; response = 0;
}

Instruction & Instruction::operator=( const Instruction &aux )
{
	if (instruction != nullptr) free(instruction);
	instruction = new char[aux.length-1];
	for (int i = 0; i < aux.length ; i++)
	{
		instruction[i] = aux.instruction[i];
	}
	length = aux.length;
	response = aux.response;
	return *this;
}

