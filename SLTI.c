/*
* Author: Josiah Fout
* Date: 10/31/25
* ByteForge Systems
* MIPS-Translatron 3000
*/

// Happy Halloween!
//JF: Added SLTI instruction assembly and binary decoding

#include "Instruction.h"

void slti_immd_assm(void) {
	// Checking that the op code matches
	// strcmp(string1, string2) return 0 if they match
	if(strcmp(OP_CODE, "SLTI") != 0) {
	
		state = WRONG_COMMAND;
		return;
	}

	/*
		Checking the type of parameters
	*/

	// Generally the first parameter should always be a register
	if (PARAM1.type != REGISTER) { // Rt
		state = MISSING_REG;
		return;
	}
	// This is SLTI, so param 2 needs to be a register
	if (PARAM2.type != REGISTER) { // Rs
		state = MISSING_REG;
		return;
	}
	// This is SLTI, so param 3 needs to be immediate
	if (PARAM3.type != IMMEDIATE) { // immediate value
		state = INVALID_PARAM;
		return;
	}

	/*
		Checking the value of parameters
	*/

	// Rs should be 31 or less
	if (PARAM1.value > 31) { // Rt
		state = INVALID_REG;
		return;
	}

	// Rs should be 31 or less
	if (PARAM2.value > 31) { // Rs
		state = INVALID_REG;
		return;
	}
	// The immediate value is limited to 16 bits, this is 0xFFFF
	if (PARAM3.value > 0xFFFF) { // immediate
		state = INVALID_IMMED;
		return;
	}
	/*
		Putting the binary together
	*/
	// Set the opcode
	setBits_str(31, "001010");
	
	// set Rt
	setBits_num(20, PARAM1.value, 5);
	
	// set Rs
	setBits_num(25, PARAM2.value, 5);
	
	// set immediate
	setBits_num(15, PARAM3.value, 16);

	// Tell the system that the encoding is complete
	state = COMPLETE_ENCODE;
}

void slti_immd_bin(void) {
	//checking that the op code matches
	if (checkBits(31, "001010") != 0) {
		state = WRONG_COMMAND;
		return;
	}
	/*
		Finding the binary values
	*/

	//get binary

	// Rt
	uint32_t Rt = getBits(20, 5);

	// Rs
	uint32_t Rs = getBits(25, 5);

	// immediate
	uint32_t imm16 = getBits(15, 16);

	/*
		Setting Instruction values
	
	*/

	setOp("SLTI");
	//setCond_num(cond);
	//setParam(param_number, Param_Type, value);

	setParam(1, REGISTER, Rt); // destination
	setParam(2, REGISTER, Rs); // source
	setParam(3, IMMEDIATE, imm16); // immediate value

	// Indicate that decoding is complete

	state = COMPLETE_DECODE;
}




