#include "Instruction.h"
/**
 * @author Theodore Miesel
 * @date 10/21/2025
 * @file MULT.c
 */


void mult_reg_assm(void) {
	if (strcmp(OP_CODE, "MULT") != 0) {
		// If the op code doesnt match, this isnt the correct command
		state = WRONG_COMMAND;
		return;
	}

	

	/*
		Checking the type of parameters
	*/

	/*
		Checking the value of parameters
	*/

	/*
		Putting the binary together
	*/


	// tell the system the encoding is done
	state = COMPLETE_ENCODE;
}

void mult_reg_bin(void) {
	// Check if the op code bits match
	// check_bits(start_bit, bit_string) returns 0 if the bit_string matches
	//  any x will be skipped
	// If the manual shows (0), then the value of that bit doesnt matter
	if (checkBits(31, "000000") != 0 || checkBits(5, "100000") != 0) {
		state = WRONG_COMMAND;
		return;
	}

	// tell the system the decoding is done
	state = COMPLETE_DECODE;
}

