#include "chip8.h"

/* 
* Type: CALL 
* Explanation: Calls RCA 1802 program at address NNN. Not necessary for most ROMs.
*/
void _0NNN(struct Chip8 * chip, const unsigned short _opcode){
    //printf("\nExecutado _0NNN");
}

/* 
* Type: DISPLAY 
* Explanation: Clears the screen.
*/
void _00E0(struct Chip8 * chip, const unsigned short _opcode){
    //printf("\nExecutado _00E0");
}

/* 
* Type: FLOW 
* Explanation: Returns from a subroutine.
*/
void _00EE(struct Chip8 * chip, const unsigned short _opcode){
//printf("\nExecutado _00EE");
}

/* 
* Type: FLOW 
* Explanation: Jumps to address NNN.
*/
void _1NNN(struct Chip8 chip, const unsigned short _opcode){
    //printf("\nExecutado _1NNN");
    chip.pc = 0x0FFF & _opcode;
    
    printf("\nPointer PC: 0x%X", chip.pc);
}

/* 
* Type: FLOW 
* Explanation: Calls subroutine at NNN.
*/
void _2NNN(struct Chip8 chip, const unsigned short _opcode){
    //printf("\nExecutado _2NNN");
    chip.stack[chip.sp] = chip.pc;
    chip.sp++;
    chip.pc = _opcode & 0x0FFF;
}

/* 
* Type: Cond 
* Explanation: Skips the next instruction if VX equals NN. (Usually the next instruction is a jump to skip a code block)
*/
void _3XNN(struct Chip8 chip, const unsigned short _opcode){
    int vIndex = (_opcode & 0x0F00) >> 8;
    
    if(chip.V[vIndex] == (_opcode & 0x00FF)){  
        chip.pc += 4;   
    } else {
        chip.pc += 2;
    }
    
    //printf("\nExecutado _3XNN");
}

/* 
* Type: Cond 
* Explanation: Skips the next instruction if VX doesn't equal NN. (Usually the next instruction is a jump to skip a code block)
*/
void _4XNN(struct Chip8 chip, const unsigned short _opcode){
    int vIndex = (_opcode & 0x0F00) >> 8;
    
    if(chip.V[vIndex] != (_opcode & 0x00FF)){
        chip.pc += 4;
    } else {
        chip.pc += 2;
    }
    
    //printf("\nExecutado _4XNN");
}

/* 
* Type: Cond 
* Explanation: Skips the next instruction if VX equals VY. 
* (Usually the next instruction is a jump to skip a code block)
*/
void _5XY0(struct Chip8 chip, const unsigned short _opcode){
    unsigned short xIndex = (_opcode & 0x0F00) >> 8;
    unsigned short yIndex = (_opcode & 0x00F0) >> 4;
    
    if(chip.V[xIndex] == chip.V[yIndex]){
        chip.pc += 4;
    } else {
        chip.pc += 2;
    }
    
    //printf("\nExecutado _5XY0");
}

/* 
* Type: Const 
* Explanation: Sets VX to NN.
*/
void _6XNN(struct Chip8 chip, const unsigned short _opcode){
    unsigned short xIndex = (_opcode & 0x0F00) >> 8;
    
    chip.V[xIndex] = (_opcode & 0x00FF);
    chip.pc += 2;
    //printf("\nExecutado _6XNN");
}

/* 
* Type: Const 
* Explanation: Adds NN to VX.
*/
void _7XNN(struct Chip8 chip, const unsigned short _opcode){
    unsigned short xIndex = (_opcode & 0x0F00) >> 8;
    
    chip.V[xIndex] += (_opcode & 0x00FF);
    chip.pc += 2;
    //printf("\nExecutado _7XNN");
}

/* 
* Type: Assign 
* Explanation:  Sets VX to the value of VY.
*/
void _8XY0(struct Chip8 chip, const unsigned short _opcode){
    unsigned short xIndex = (_opcode & 0x0F00) >> 8;
    unsigned short yIndex = (_opcode & 0x00F0) >> 4;
    
    chip.V[xIndex] = chip.V[yIndex];
    chip.pc += 2;
    //printf("\nExecutado _8XY0");
}

/* 
* Type: BitOp 
* Explanation: Sets VX to VX or VY. (Bitwise OR operation)
*/
void _8XY1(struct Chip8 chip, const unsigned short _opcode){
    unsigned short xIndex = (_opcode & 0x0F00) >> 8;
    unsigned short yIndex = (_opcode & 0x00F0) >> 4;
    
    chip.V[xIndex] |= chip.V[yIndex];
    chip.pc += 2;
    //printf("\nExecutado _8XY1");
}

/* 
* Type: BitOp 
* Explanation:  Sets VX to VX and VY. (Bitwise AND operation)
*/
void _8XY2(struct Chip8 chip, const unsigned short _opcode){
    unsigned short xIndex = (_opcode & 0x0F00) >> 8;
    unsigned short yIndex = (_opcode & 0x00F0) >> 4;
    
    chip.V[xIndex] &= chip.V[yIndex];
    chip.pc += 2;
    //printf("\nExecutado _8XY2");
}

/* 
* Type: BitOp 
* Explanation: Sets VX to VX xor VY.
*/
void _8XY3(struct Chip8 chip, const unsigned short _opcode){
    unsigned short xIndex = (_opcode & 0x0F00) >> 8;
    unsigned short yIndex = (_opcode & 0x00F0) >> 4;
    
    chip.V[xIndex] ^= chip.V[yIndex];
    chip.pc += 2;
    //printf("\nExecutado _8XY3");
}

/* 
* Type: Math 
* Explanation: Adds VY to VX. VF is set to 1 when there's a carry, and to 0 when there isn't.
*/
void _8XY4(struct Chip8 chip, const unsigned short _opcode){
    unsigned short xIndex = (_opcode & 0x0F00) >> 8;
    unsigned short yIndex = (_opcode & 0x00F0) >> 4;
    
    if(chip.V[xIndex] > (0xFF - chip.V[yIndex])){
        chip.V[0xF] = 1;    
    } else {
        chip.V[0xF] = 0;
    }
    
    chip.V[xIndex] += chip.V[yIndex];
    
    chip.pc += 2;
    //printf("\nExecutado _8XY4");
}

/* 
* Type: Math 
* Explanation: VY is subtracted from VX. VF is set to 0 when there's a borrow, 
* and 1 when there isn't.
*/
void _8XY5(struct Chip8 chip, const unsigned short _opcode){
    unsigned short xIndex = (_opcode & 0x0F00) >> 8;
    unsigned short yIndex = (_opcode & 0x00F0) >> 4;
    
    if(chip.V[yIndex] > chip.V[xIndex]){
        chip.V[0xF] = 1; // BORROW
    } else {
        chip.V[0xF] = 0; // BORROW
    }
    
    chip.V[xIndex] -= chip.V[yIndex];
    
    chip.pc += 2;
    //printf("\nExecutado _8XY5");
}

/* 
* Type: BitOp 
* Explanation: Shifts VX right by one. VF is set to the value of the least significant bit of 
* VX before the shift.
*/
void _8XY6(struct Chip8 chip, const unsigned short _opcode){
    unsigned short xIndex = (_opcode & 0x0F00) >> 8;
    
    chip.V[xIndex] >>= 1;
    chip.pc += 2;
    //printf("\nExecutado _8XY6");
}

/* 
* Type: Math 
* Explanation: Sets VX to VY minus VX. VF is set to 0 when there's a borrow, and 1 when there isn't.
*/
void _8XY7(struct Chip8 chip, const unsigned short _opcode){
    unsigned short xIndex = (_opcode & 0x0F00) >> 8;
    unsigned short yIndex = (_opcode & 0x00F0) >> 4;
    
    // borrow
    if(chip.V[xIndex] > chip.V[yIndex]){
        chip.V[0xF] = 1;
    } else {
        chip.V[0xF] = 0;
    }
    
    chip.V[xIndex] = chip.V[yIndex] - chip.V[xIndex];
    chip.pc += 2;
    //printf("\nExecutado _8XY7");
}

/* 
* Type: BitOp 
* Explanation: Shifts VX left by one. VF is set to the value of the most significant 
* bit of VX before the shift
*/
void _8XYE(struct Chip8 chip, const unsigned short _opcode){
    unsigned short xIndex = (_opcode & 0x0F00) >> 8;
    
    chip.V[0xF] = chip.V[xIndex] >> 7;
    
    chip.V[xIndex] <<= 1;
    chip.pc += 2;
    //printf("\nExecutado _8XYE");
}

/* 
* Type: Cond 
* Explanation: Skips the next instruction if VX doesn't equal VY. 
* (Usually the next instruction is a jump to skip a code block)
*/
void _9XY0(struct Chip8 chip, const unsigned short _opcode){
    unsigned short xIndex = (_opcode & 0x0F00) >> 8;
    unsigned short yIndex = (_opcode & 0x00F0) >> 4;
    
    if(chip.V[xIndex] != chip.V[yIndex]){
        chip.pc += 4;
    } else {
        chip.pc += 2;
    }
    //printf("\nExecutado _9XY0");
}

/* 
* Type: MEM 
* Explanation: Sets I to the address NNN.
*/
void ANNN(struct Chip8 chip, const unsigned short _opcode){
    chip.I = (_opcode & 0x0FFF);
    chip.pc += 2;
    //printf("\nExecutado ANNN");
}

/* 
* Type: Flow 
* Explanation: Jumps to the address NNN plus V0.
*/
void BNNN(struct Chip8 chip, const unsigned short _opcode){
    chip.pc = (_opcode * 0x0FFF) + chip.V[0];
    //printf("\nExecutado BNNN");
}

/* 
* Type: Rand 
* Explanation: Sets VX to the result of a bitwise AND operation on a random number 
* (Typically: 0 to 255) and NN.
*/
void CXNN(struct Chip8 chip, const unsigned short _opcode){
    unsigned short xIndex = (_opcode & 0x0F00) >> 8;
    
    chip.V[xIndex] = (rand() % 0xFF) & (_opcode & 0x00FF);
    chip.pc += 2;
    //printf("\nExecutado CXNN");
}

/* 
* Type: Disp 
* Explanation: Draws a sprite at coordinate (VX, VY) that has a width of 8 pixels and 
* a height of N pixels. Each row of 8 pixels is read as bit-coded starting from memory 
* location I; I value doesn’t change after the execution of this instruction. As 
* described above, VF is set to 1 if any screen pixels are flipped from set to unset 
* when the sprite is drawn, and to 0 if that doesn’t happen
*/
void DXYN(struct Chip8 chip, const unsigned short _opcode){
    unsigned short xIndex = (_opcode & 0x0F00) >> 8;
    unsigned short yIndex = (_opcode & 0x00F0) >> 4;
    unsigned short height = (_opcode & 0x000F);
    unsigned short pixels;
    
    // reset the collision detect
    chip.V[0xF] = 0;
    
    int yLine = 0;
    for(0; yLine < height; yLine++){
    	pixels = chip.memory[chip.I + yLine];
    	
    	
	}
	//printf("\nExecutado DXYN");
	
	chip.draw_flag = 1;
	chip.pc += 2;
}

/* 
* Type: KeyOp 
* Explanation: Skips the next instruction if the key stored in VX is pressed. (Usually the next instruction is a jump to skip a code block)
*/
void EX9E(struct Chip8 chip, const unsigned short _opcode){
    //printf("\nExecutado EX9E");
}

/* 
* Type: KeyOp 
* Explanation: Skips the next instruction if the key stored in VX isn't pressed. (Usually the next instruction is a jump to skip a code block)
*/
void EXA1(struct Chip8 chip, const unsigned short _opcode){
    //printf("\nExecutado EXA1");
}

/* 
* Type: Timer 
* Explanation: Sets VX to the value of the delay timer.
*/
void FX07(struct Chip8 chip, const unsigned short _opcode){
    //printf("\nExecutado FX07");
}

/* 
* Type: KeyOp 
* Explanation: A key press is awaited, and then stored in VX. (Blocking Operation. All instruction halted until next key event)
*/
void FX0A(struct Chip8 chip, const unsigned short _opcode){
    //printf("\nExecutado FX0A");
}

/* 
* Type: Timer 
* Explanation: Sets the delay timer to VX.
*/
void FX15(struct Chip8 chip, const unsigned short _opcode){
    //printf("\nExecutado FX15");
}

/* 
* Type: Sound 
* Explanation: Sets the sound timer to VX.
*/
void FX18(struct Chip8 chip, const unsigned short _opcode){
    //printf("\nExecutado FX18");
}

/* 
* Type: MEM 
* Explanation: Adds VX to I
*/
void FX1E(struct Chip8 chip, const unsigned short _opcode){
    //printf("\nExecutado FX1E");
}

/* 
* Type: MEM 
* Explanation: Sets I to the location of the sprite for the character in VX. Characters 0-F (in hexadecimal) are represented by a 4x5 font.
*/
void FX29(struct Chip8 chip, const unsigned short _opcode){
    //printf("\nExecutado FX29");
}

/* 
* Type: BCD 
* Explanation: Stores the binary-coded decimal representation of VX, with the most significant of three digits at the address in I, the middle digit at I plus 1, and the least significant digit at I plus 2. (In other words, take the decimal representation of VX, place the hundreds digit in memory at location in I, the tens digit at location I+1, and the ones digit at location I+2.)
*/
void FX33(struct Chip8 chip, const unsigned short _opcode){
    //printf("\nExecutado FX33");
}

/* 
* Type: MEM 
* Explanation: Stores V0 to VX (including VX) in memory starting at address I.
*/
void FX55(struct Chip8 chip, const unsigned short _opcode){
    //printf("\nExecutado FX55");
}

/* 
* Type: MEM 
* Explanation: Fills V0 to VX (including VX) with values from memory starting at address I.
*/
void FX65(struct Chip8 chip, const unsigned short _opcode){
    //printf("\nExecutado FX65");
}
