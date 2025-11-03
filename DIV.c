/*
* Author: Ol' Jim
* Editor: Josiah Fout
* Date: 10/31/25
* ByteForge Systems
* MIPS-Translatron 3000
*/

// 10.23.25 JF: Fixed several issues with the DIV instruction assembly and binary decoding
// 10.31.25 JF: Also added comments for clarity

#include "Instruction.h"

void div_reg_assm(void) {
	// check opcode
	// strcmp(string1, string2) return 0 if they match
	if (strcmp(OP_CODE, "DIV") != 0) {
	// If the op code doesnt match, this isnt the correct command	
		state = WRONG_COMMAND;
		return;
	}

	// check par
	// Generally the first parameter should always be a register
	if (PARAM1.type != REGISTER) {
		state = MISSING_REG;
		return;
	}
	// check par
	//should be register
	if (PARAM2.type != REGISTER) {
		state = MISSING_REG;
		return;
	}
	
	/*
		Checking the value of parameters

	*/

	// Rs should be 31 or less
	if (PARAM1.value > 31) {
		state = INVALID_REG;
		return;
	}
	// Rt should be 31 or less
	if (PARAM2.value > 31) {
		state = INVALID_REG;
		return;
	}
	
	//Set the opcode
	setBits_num(31, 0, 6); // opcode was incorrect and wrong position, fixed
	// create binary
	setBits_str(31, "000000");
	// set Rs
	setBits_num(25, PARAM1.value, 5); //param2 was Rs, fixed
	// set Rt
	setBits_num(20, PARAM2.value, 5); //param1 was Rt, fixed
	
	setBits_str(5, "011010");

	
	state = COMPLETE_ENCODE; 
}
// decode
void div_reg_bin(void) {
	if (checkBits(31, "000000") != 0 || checkBits(5, "011010") != 0) {
		state = WRONG_COMMAND;
		return;
	}

	// find binary
	uint32_t Rs = getBits(25, 5);
	uint32_t Rt = getBits(20, 5);
	// set parameters
	
	setOp("DIV");
	
	setParam(1, REGISTER, Rs); //was PARAM2, fixed
	
	setParam(2, REGISTER, Rt); //was PARAM1, fixed

	state = COMPLETE_DECODE;
}


