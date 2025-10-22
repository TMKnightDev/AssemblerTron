/*
* Author: Ol' Jim
* Editor: Luke DeVault
* Date Edited: 10/22/2025
* ByteForge Systems
* MIPS-Translatron 3000
*/

#include "Instruction.h"

void or_reg_assm(void) {
	// Checking that the op code matches
	// strcmp(string1, string2) return 0 if they match
	if (strcmp(OP_CODE, "OR") != 0) {
		// If the op code doesnt match, this isnt the correct command
		state = WRONG_COMMAND;
		return;
	}
	/*
		Checking the type of parameters
	*/
	// Generally the first parameter should always be a register
	if (PARAM1.type != REGISTER) {
		state = MISSING_REG;
		return;
	}
	// This is OR register, so param 2 needs to be a register
	if (PARAM2.type != REGISTER) {
		state = MISSING_REG;
		return;
	}
	// This is OR register, so param 3 needs to be a register
	if (PARAM3.type != REGISTER) {
		state = MISSING_REG;
		return;
	}


	// Rd should be 31 or less
	if (PARAM1.value > 31) {
		state = INVALID_REG;
		return;
	}
	// Rs should be 31 or less
	if (PARAM2.value > 31) {
		state = INVALID_REG;
		return;
	}
	// Rt should be 31 or less
	if (PARAM3.value > 31) {
		state = INVALID_REG;
		return;
	}
	/*
		Putting the binary together
	*/

	// Set the opcode
	setBits_num(31, 0, 6);

	// Set the funct
	setBits_str(5, "100101");

	// Set Rd
	setBits_num(15, PARAM1.value, 5);

	// Set Rs
	setBits_num(25, PARAM2.value, 5);

	// Set Rt
	setBits_num(20, PARAM3.value, 5);

	// Tell the system that the encoding is complete
	state = COMPLETE_ENCODE;
}

void or_reg_bin(void) {
	// Check if the op code bits match
	// check_bits(start_bit, bit_string) returns 0 if the bit_string matches
	//  any x will be skipped
	// If the manual shows (0), then the value of that bit doesnt matter
	if (checkBits(31, "000000") != 0 || checkBits(5, "100101") != 0) {
		state = WRONG_COMMAND;
		return;
	}

	// If the op code bits match, then the rest can be read as correctly

	/*
		Finding values in the binary
	*/
	// getBits(start_bit, width)
	uint32_t Rd = getBits(15, 5);
	uint32_t Rs = getBits(25, 5);
	uint32_t Rt = getBits(20, 5);

	/*
		Setting Instruction values
	*/
	setOp("OR");
	// setCond_num(cond);
	// setParam(param_num, param_type, param_value)
	setParam(1, REGISTER, Rd); // Destination
	setParam(2, REGISTER, Rs); // First source 
	setParam(3, REGISTER, Rt); // Second source

	// Tell the system that decoding is complete
	state = COMPLETE_DECODE;
}


