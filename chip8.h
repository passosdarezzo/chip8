/*
	+===========================+--0xFFFF(4095) End of Chip RAM
	| 0x200 to 0xFFF			|
	|  PROGRAM / DATA SPACE		|
	+===========================+--0x600(1536) Start of ETI 660 Chip 8 Program
	|							|
	|							|
	+===========================+--0x200 (512) Start of most Chip 8 Programs
	| 0x000 to 0x1FF			|
	| Reserved for Interpreter	|
	+===========================+--0x000(0) Start of chip RAM
	
*/
/*
char 	8 bits
short 	16 bits
int		32 bits
long	64 bits
*/
struct Chip8{
	unsigned char memory[4096];
	unsigned char V[16];
	unsigned short I;
	unsigned short pc;
	unsigned char delay_timer;
	unsigned char sound_timer;
	unsigned short stack[16];
	unsigned short sp;
	unsigned char key[16];
	unsigned char gfx[64 * 32];
	unsigned char draw_flag;
};
