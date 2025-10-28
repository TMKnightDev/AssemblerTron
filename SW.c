/*
 * Author: Ol' Jim
 * Editor: Josiah Fout
 * Date: 06/13/2012
 * ByteForge Systems
 * MIPS-Translatron 3000
 */

#include "Instruction.h"

void sw_immd_assm(void) {
    if (strcmp(OP_CODE, "SW") != 0) {
        // If the op code doesnt match, this isnt the correct command
        state = WRONG_COMMAND;
        return;
    }
    /*

            Checking the type of parameters

    */

    // Rt should be a register
    if (PARAM1.type != REGISTER) {
        state = MISSING_REG;
        return;
    }

    // Rs should be a register
    if (PARAM3.type != REGISTER) {
        state = MISSING_REG;
        return;
    }
    // The offset/immediate should be an immediate
    if (PARAM2.type != IMMEDIATE) {
        state = INVALID_PARAM;
        return;
    }

    /*

        Checking the value of parameters

    */
    // Rt should be 31 or less
    if (PARAM1.value > 31) {
        state = INVALID_REG;
        return;
    }
    // Rs should be 31 or less
    if (PARAM3.value > 31) {  // was PARAM3, fixed
        state = INVALID_REG;
        return;
    }
    if (PARAM2.value > 0xFFFF) {  // immediate should be 16 bits
        state = INVALID_IMMED;
        return;
    }

    /*
            Putting the binary together
    */

    // Set the opcode
    setBits_str(31, "101011");
    // set Rt
    setBits_num(20, PARAM1.value, 5);
    // set Rs
    setBits_num(25, PARAM3.value, 5);
    // set immediate/offset
    setBits_num(15, PARAM2.value, 16);

    // Tell the system that the encoding is complete
    state = COMPLETE_ENCODE;
}

void sw_immd_bin(void) {
    // check opcode
    if (checkBits(31, "101011") != 0) {
        state = WRONG_COMMAND;
        return;
    }

    /*
            finding the binary values
    */

    uint32_t Rs = getBits(25, 5);
    uint32_t Rt = getBits(20, 5);
    uint32_t offset = getBits(15, 16);

    /*
            Setting Instruction values

    */

    setOp("SW");
    setParam(1, REGISTER, Rt);  // destination
    setParam(3, REGISTER, Rs);
    setParam(2, IMMEDIATE, offset);

    // tell the system that the decoding is complete
    state = COMPLETE_DECODE;
}