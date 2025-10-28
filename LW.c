/*
* Author: Muhammad Zuhair Qureshi
* Date: 10/27/2025
* ByteForge Systems
* MIPS-Translatron 3000
*/
#include "Instruction.h"

void lw_immd_assm(void) {
	// Checks to see if Opcode matches using strcmp
	// strcmp(string1, string2) return 0 if they match
	if (strcmp(OP_CODE, "LW") != 0) {
		// Produces an error if they do not match, LW is not the correct command
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
	// In LW command, the third parameter is also a register
	if (PARAM3.type != REGISTER) {
		state = MISSING_REG;
		return;
	}

	// The second parameter is the immediate value
	if (PARAM2.type != IMMEDIATE) {
		state = INVALID_PARAM;
		return;
	}

	// Check if register 1 and 2 have a value greater than 31
	// Rt should have a value less than 31
	if (PARAM1.value > 31) {
		state = INVALID_REG;
		return;
	}

	// Rs should have a value less than 31
	if (PARAM3.value > 31) {
		state = INVALID_REG;
		return;
	}

	// The offset value is limited to 16 bits, this is 0xFFFF
	// Offset should be less than 0xFFFF
	if (PARAM2.value > 0xFFFF) {
		state = INVALID_IMMED;
		return;
	}
	
	//encode instruction

	/*
		Putting the binary together
	*/

	// Set the opcode
	setBits_str(31, "100011");

	// set Rt
	setBits_num(20, PARAM1.value, 5);

	// set Rs
	setBits_num(25, PARAM3.value, 5);

	// set offset
	setBits_num(15, PARAM2.value, 16);

	// tell the system the encoding is done
	state = COMPLETE_ENCODE;
}


void lw_immd_bin(void) {

	// Check if the op code bits match
			// check_bits(start_bit, bit_string) returns 0 if the bit_string matches
			//  any x will be skipped
			// If the manual shows (0), then the value of that bit doesnt matter
	if (checkBits(31, "100011") != 0) {
		state = WRONG_COMMAND;
		return;
	}
	// If there the Opcode mathces, then the rest of parameters are correct and can be read off correctly
	/*
		Finding values in the binary
	*/
	// getBits(start_bit, width)
	uint32_t Rs = getBits(25, 5);
	uint32_t Rt = getBits(20, 5);
	uint32_t offset = getBits(15, 16);

	setOp("LW");
	// setCond_num(cond);
	// setParam(param_num, param_type, param_value)
	setParam(1, REGISTER, Rt); // destination
	setParam(3, REGISTER, Rs); // source register (contains value)
	setParam(2, IMMEDIATE, offset); // immediate operand
	state = COMPLETE_DECODE;

}
