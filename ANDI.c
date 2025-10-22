/*
* Author: Ol' Jim
* Date: 10/22/2025
* Editor: Ted
* ByteForge Systems
* MIPS-Translatron 3000
*/

#include "Instruction.h"

void andi_immd_assm(void) {
	// Checking that the op code matches
	// strcmp(string1, string2) return 0 if they match
	if (strcmp(OP_CODE, "ANDI") != 0) {
		state = WRONG_COMMAND; // Don't match
		return;
	}

	/*
		Checking the type of parameters
	*/

	// Generally the first parameter should always be a register
	if (PARAM1.type != REGISTER) { // rt
		state = MISSING_REG;
		return;
	}
	// Needs to be register
	if (PARAM2.type != REGISTER) { // rs
		state = MISSING_REG;
		return;
	}
	// Needs to be immediate
	if (PARAM3.type != IMMEDIATE) { // imm
		state = INVALID_PARAM;
		return;
	}


	/*
		Checking the value of parameters
	*/

	// Rt should be 31 or less
	if (PARAM1.value > 31) { // rt
		state = INVALID_REG;
		return;
	}
	// Rs should be 31 or less
	if (PARAM2.value > 31) { // rs
		state = INVALID_REG;
		return;
	}
	// Must be in 16 bit range
	if (PARAM3.value > 0xFFFF) { // immediate 16 bits
		state = INVALID_IMMED;
		return;
	}

	// combine binary
	setBits_str(31, "001100");
	setBits_num(20, PARAM1.value, 5); // Set rt
	setBits_num(25, PARAM2.value, 5); // Set rs
	setBits_num(15, PARAM3.value, 16); // Set immediate

	state = COMPLETE_ENCODE;
}

void andi_immd_bin(void) {
	// Check if the op code bits match
	// check_bits(start_bit, bit_string) returns 0 if the bit_string matches
	//  any x will be skipped
	// If the manual shows (0), then the value of that bit doesnt matter
	if (checkBits(31, "001100") != 0 ) {
		state = WRONG_COMMAND;
		return;
	}

	// If the op code bits match, then the rest can be read as correctly

	/*
		Finding values in the binary
	*/
	// get binary values
	uint32_t Rt = getBits(20, 5);
	uint32_t Rs = getBits(25, 5);
	uint32_t imm16 = getBits(15, 16);


	/*
		Setting Instruction values
	*/

	// set op
	setOp("ANDI");
	setParam(1, REGISTER, Rt); // Destination
	setParam(2, REGISTER, Rs);  // Source register 1
	setParam(3, IMMEDIATE, imm16); // Immediate value
	
	// Tell OS the decoding is complete
	state = COMPLETE_DECODE;
}



