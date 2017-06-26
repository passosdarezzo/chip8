/* 
* Type: CALL 
* Explanation: Calls RCA 1802 program at address NNN. Not necessary for most ROMs.
*/
void _0NNN();

/* 
* Type: DISPLAY 
* Explanation: Clears the screen.
*/
void _00E0();

/* 
* Type: FLOW 
* Explanation: Returns from a subroutine.
*/
void _00EE();

/* 
* Type: FLOW 
* Explanation: Jumps to address NNN.
*/
void _1NNN();

/* 
* Type: FLOW 
* Explanation: Calls subroutine at NNN.
*/
void _2NNN();

/* 
* Type: Cond 
* Explanation: Skips the next instruction if VX equals NN. (Usually the next instruction is a jump to skip a code block)
*/
void _3XNN();

/* 
* Type: Cond 
* Explanation: Skips the next instruction if VX doesn't equal NN. (Usually the next instruction is a jump to skip a code block)
*/
void _4XNN();

/* 
* Type: Cond 
* Explanation: Skips the next instruction if VX equals VY. (Usually the next instruction is a jump to skip a code block)
*/
void _5XY0();

/* 
* Type: Const 
* Explanation: Sets VX to NN.
*/
void _6XNN();

/* 
* Type: Const 
* Explanation: Adds NN to VX.
*/
void _7XNN();

/* 
* Type: Assign 
* Explanation: 	Sets VX to the value of VY.
*/
void _8XY0();

/* 
* Type: BitOp 
* Explanation: Sets VX to VX or VY. (Bitwise OR operation)
*/
void _8XY1();

/* 
* Type: BitOp 
* Explanation: 	Sets VX to VX and VY. (Bitwise AND operation)
*/
void _8XY2();

/* 
* Type: BitOp 
* Explanation: Sets VX to VX xor VY.
*/
void _8XY3();

/* 
* Type: Math 
* Explanation: Adds VY to VX. VF is set to 1 when there's a carry, and to 0 when there isn't.
*/
void _8XY4();

/* 
* Type: Math 
* Explanation: VY is subtracted from VX. VF is set to 0 when there's a borrow, and 1 when there isn't.
*/
void _8XY5();

/* 
* Type: BitOp 
* Explanation: Shifts VX right by one. VF is set to the value of the least significant bit of VX before the shift.
*/
void _8XY6();

/* 
* Type: Math 
* Explanation: Sets VX to VY minus VX. VF is set to 0 when there's a borrow, and 1 when there isn't.
*/
void _8XY7();

/* 
* Type: BitOp 
* Explanation: Shifts VX left by one. VF is set to the value of the most significant bit of VX before the shift
*/
void _8XYE();

/* 
* Type: Cond 
* Explanation: Skips the next instruction if VX doesn't equal VY. (Usually the next instruction is a jump to skip a code block)
*/
void _9XY0();

/* 
* Type: MEM 
* Explanation: Sets I to the address NNN.
*/
void ANNN();

/* 
* Type: Flow 
* Explanation: Jumps to the address NNN plus V0.
*/
void BNNN();

/* 
* Type: Rand 
* Explanation: Sets VX to the result of a bitwise and operation on a random number (Typically: 0 to 255) and NN.
*/
void CXNN();

/* 
* Type: Disp 
* Explanation: Draws a sprite at coordinate (VX, VY) that has a width of 8 pixels and a height of N pixels. Each row of 8 pixels is read as bit-coded starting from memory location I; I value doesn’t change after the execution of this instruction. As described above, VF is set to 1 if any screen pixels are flipped from set to unset when the sprite is drawn, and to 0 if that doesn’t happen
*/
void DXYN();

/* 
* Type: KeyOp 
* Explanation: Skips the next instruction if the key stored in VX is pressed. (Usually the next instruction is a jump to skip a code block)
*/
void EX9E();

/* 
* Type: KeyOp 
* Explanation: Skips the next instruction if the key stored in VX isn't pressed. (Usually the next instruction is a jump to skip a code block)
*/
void EXA1();

/* 
* Type: Timer 
* Explanation: Sets VX to the value of the delay timer.
*/
void FX07();

/* 
* Type: KeyOp 
* Explanation: A key press is awaited, and then stored in VX. (Blocking Operation. All instruction halted until next key event)
*/
void FX0A();

/* 
* Type: Timer 
* Explanation: Sets the delay timer to VX.
*/
void FX15();

/* 
* Type: Sound 
* Explanation: Sets the sound timer to VX.
*/
void FX18();

/* 
* Type: MEM 
* Explanation: Adds VX to I
*/
void FX1E();

/* 
* Type: MEM 
* Explanation: Sets I to the location of the sprite for the character in VX. Characters 0-F (in hexadecimal) are represented by a 4x5 font.
*/
void FX29();

/* 
* Type: BCD 
* Explanation: Stores the binary-coded decimal representation of VX, with the most significant of three digits at the address in I, the middle digit at I plus 1, and the least significant digit at I plus 2. (In other words, take the decimal representation of VX, place the hundreds digit in memory at location in I, the tens digit at location I+1, and the ones digit at location I+2.)
*/
void FX33();

/* 
* Type: MEM 
* Explanation: Stores V0 to VX (including VX) in memory starting at address I.
*/
void FX55();

/* 
* Type: MEM 
* Explanation: Fills V0 to VX (including VX) with values from memory starting at address I.
*/
void FX65();


