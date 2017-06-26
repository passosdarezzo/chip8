#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "opcode.h"
#include "chip8.h"

#define true 1
#define false 0

// Display size
#define SCREEN_WIDTH 64
#define SCREEN_HEIGHT 32

unsigned short opcode;

struct Chip8 myChip;

void setupGraphics(){
	
}

void setupInput(){
	
}

void drawFlag(){
}

void drawGraphics(){
}

void setKeys(){
}

void printInitialOpcodes(){
	int i = 512;
	for(i; i < 805; i++){
		/*
		printf("%x", memory[i++]);
		printf("%x \n", memory[i]);
		*/
		unsigned short opcodeFetched = myChip.memory[i] << 8 | myChip.memory[i + 1];
		printf ("Opcode [0x0000]: 0x%X\n", opcodeFetched);
	} 
}

void dumpMemoryToFile(){
	FILE *f = fopen("MemoryDump.txt", "w");
	if (f == NULL){
	    printf("Error opening file!\n");
	    exit(1);
	}
	
	int i = 0;
	for(i; i < 4096; i++){
		//unsigned short opcode = memory[i] << 8 | memory[i + 1];
		//fprintf(f, i + ": %c\n", opcode);
		//fwrite(&opcode, sizeof(opcode), 1, f);
		fprintf(f, i + "%04x", myChip.memory[i]);
	}
	
	
	/*
	//print some text
	const char *text = "Write this to the file";
	fprintf(f, "Some text: %s\n", text);
	
	//print integers and floats
	int i = 1;
	float py = 3.1415927;
	fprintf(f, "Integer: %d, float: %f\n", i, py);
	
	// printing single chatacters
	char c = 'A';
	fprintf(f, "A character: %c\n", c);
	*/
	fclose(f);
}

/**
* Carrega o programa para a memoria do CHIP 8
*/
int loadApplication(const char * filename){ 
	//init();
	printf("Loading: %s\n", filename);
		
	// Open file
	FILE * pFile = fopen(filename, "rb");
	if (pFile == NULL){
		fputs ("File error", stderr); 
		return false;
	}

	// Check file size
	fseek(pFile , 0 , SEEK_END);
	long lSize = ftell(pFile);
	rewind(pFile);
	printf("Filesize: %d\n", (int)lSize);
	
	// Allocate memory to contain the whole file
	char * buffer = (char*)malloc(sizeof(char) * lSize);
	if (buffer == NULL) {
		fputs ("Memory error", stderr); 
		return false;
	}

	// Copy the file into the buffer
	size_t result = fread (buffer, 1, lSize, pFile);
	if (result != lSize) {
		fputs("Reading error",stderr); 
		return false;
	}

	// Copy buffer to Chip8 memory
	if((4096-512) > lSize){
		int i = 0;
		for(i; i < lSize; ++i){
			myChip.memory[i + 512] = buffer[i];
		}
	} else {
		printf("Erro: ROM too big for memory");
	}

	// Close file, free buffer
	fclose(pFile);
	free(buffer);

	return true;
}

/**
* Inicializa os registradores
*/
void initialize(){
	myChip.pc	= 0x200;// Program counter starts at 0x200 (Start adress program)
	opcode		= 0;	// Reset current opcode	
	myChip.I	= 0;	// Reset index register
	myChip.sp	= 0;	// Reset stack pointer
}

void decodeAndExecuteOpcode(unsigned short _opcode){
	
	switch(_opcode & 0xF000){ 
		case 0x0000:
			switch((_opcode & 0x000F)){
				case 0x0000:
					_00E0(myChip, opcode);
					break;
					
				case 0x000E:
					_00EE(myChip, opcode);
					break;
					
				default:
					_0NNN(myChip, opcode);	
			}
			break;
			
		case 0x1000:
			printf("\nOpcode: 0x%X - Reconhecido como 0x1NNN", _opcode);
			_1NNN(myChip, opcode);
			break;
			
		case 0x2000:
			printf("\nOpcode: 0x%X - Reconhecido como 0x2NNN", _opcode);
			_2NNN(myChip, opcode);
			break;
			
		case 0x3000:
			printf("\nOpcode: 0x%X - Reconhecido como 0x3XNN", _opcode);
			_3XNN(myChip, opcode);
			break;
			
		case 0x4000:
			printf("\nOpcode: 0x%X - Reconhecido como 0x4XNN", _opcode);
			_4XNN(myChip, opcode);
			break;
			
		case 0x5000:
			printf("\nOpcode: 0x%X - Reconhecido como 0x5XY0", _opcode);
			_5XY0(myChip, opcode);
			break;
			
		case 0x6000:
			printf("\nOpcode: 0x%X - Reconhecido como 0x6XNN", _opcode);
			_6XNN(myChip, opcode);
			break;
			
		case 0x7000:
			printf("\nOpcode: 0x%X - Reconhecido como 0x7XNN", _opcode);
			_7XNN(myChip, opcode);
			break;
			
		case 0x8000:
			switch((_opcode * 0x000F)){
				case 0x0000:
					printf("\nOpcode: 0x%X - Reconhecido como 0x8XY0", _opcode);
					_8XY0(myChip, opcode);		
					break;
				
				case 0x0001:
					printf("\nOpcode: 0x%X - Reconhecido como 0x8XY0", _opcode);
					_8XY1(myChip, opcode);		
					break;
				
				case 0x0002:
					printf("\nOpcode: 0x%X - Reconhecido como 0x8XY0", _opcode);
					_8XY2(myChip, opcode);		
					break;
					
				case 0x0003:
					printf("\nOpcode: 0x%X - Reconhecido como 0x8XY0", _opcode);
					_8XY3(myChip, opcode);		
					break;
					
				case 0x0004:
					printf("\nOpcode: 0x%X - Reconhecido como 0x8XY0", _opcode);
					_8XY4(myChip, opcode);		
					break;
					
				case 0x0005:
					printf("\nOpcode: 0x%X - Reconhecido como 0x8XY0", _opcode);
					_8XY5(myChip, opcode);		
					break;
					
				case 0x0006:
					printf("\nOpcode: 0x%X - Reconhecido como 0x8XY0", _opcode);
					_8XY6(myChip, opcode);		
					break;
					
				case 0x0007:
					printf("\nOpcode: 0x%X - Reconhecido como 0x8XY0", _opcode);
					_8XY7(myChip, opcode);		
					break;
					
				case 0x000E:
					printf("\nOpcode: 0x%X - Reconhecido como 0x8XY0", _opcode);
					_8XYE(myChip, opcode);		
					break;
					
				default:
					printf("\nOpcode: 0x%X - NAO RECONHECIDO!", _opcode);
			}
			break;
			
		case 0x9000:
			printf("\nOpcode: 0x%X - Reconhecido como 0x9XY0", _opcode);
			_9XY0(myChip, opcode);
			break;
			
		case 0xA000:
			printf("\nOpcode: 0x%X - Reconhecido como 0xANNN", _opcode);
			ANNN(myChip, opcode);
			break;
			
		case 0xB000:
			printf("\nOpcode: 0x%X - Reconhecido como 0xBNNN", _opcode);
			BNNN(myChip, opcode);
			break;
			
		case 0xC000:
			printf("\nOpcode: 0x%X - Reconhecido como 0xCXNN", _opcode);
			CXNN(myChip, opcode);
			break;
			
		case 0xD000:
			printf("\nOpcode: 0x%X - Reconhecido como 0xDXYN", _opcode);
			DXYN(myChip, opcode);
			break;
			
		case 0xE000:
			switch((_opcode & 0x00FF)){
				case 0x009E:
					printf("\nOpcode: 0x%X - Reconhecido como 0xENNN", _opcode);
					//ENNN();
					break;
				case 0x00A1:
					printf("\nOpcode: 0x%X - Reconhecido como 0xENNN", _opcode);
					//ENNN();
					break;
				default:
					printf("\nOpcode: 0x%X - NAO RECONHECIDO!", _opcode);
			}
			break;
			
		case 0xF000:
			switch((_opcode & 0x00FF)){
				case 0x0007:
					printf("\nOpcode: 0x%X - Reconhecido como 0xFNNN", _opcode);
					FX07(myChip, opcode);
					break;
				case 0x000A:
					printf("\nOpcode: 0x%X - Reconhecido como 0xFNNN", _opcode);
					//FNNN();
					break;
				case 0x0015:
					printf("\nOpcode: 0x%X - Reconhecido como 0xFNNN", _opcode);
					//FNNN();
					break;
				case 0x0018:
					printf("\nOpcode: 0x%X - Reconhecido como 0xFNNN", _opcode);
					//FNNN();
					break;
				case 0x001E:
					printf("\nOpcode: 0x%X - Reconhecido como 0xFNNN", _opcode);
					//FNNN();
					break;
				case 0x0029:
					printf("\nOpcode: 0x%X - Reconhecido como 0xFNNN", _opcode);
					//FNNN();
					break;
				case 0x0033:
					printf("\nOpcode: 0x%X - Reconhecido como 0xFNNN", _opcode);
					//FNNN();
					break;
				case 0x0055:
					printf("\nOpcode: 0x%X - Reconhecido como 0xFNNN", _opcode);
					//FNNN();
					break;
				case 0x0065:
					printf("\nOpcode: 0x%X - Reconhecido como 0xFNNN", _opcode);
					//FNNN();
					break;
				default:
					printf("\nOpcode: 0x%X - NAO RECONHECIDO!", _opcode);
					
			}
			
		default:
			printf("\nOpcode: 0x%X - NAO RECONHECIDO!", _opcode);
	}
}

/**
* Emula um ciclo de maquina do CHIP 8
*/
void emulateCycle(){
	// Fetch Opcode
	opcode = myChip.memory[myChip.pc] << 8 | myChip.memory[myChip.pc + 1];
	//printf ("\nOpcode [0x0000]: 0x%X", opcode);
			
	// Decode and Execute Opcode
	decodeAndExecuteOpcode(opcode);
	
	// Update timers
	if(myChip.sound_timer > 0){
		if(myChip.sound_timer == 1){
			printf("BEEP\n");
		}
		myChip.sound_timer--;
	}
	
	if(myChip.delay_timer > 0){
		myChip.delay_timer--;
	}
}


int main(int argc, char **argv) {
	printf("Chip 8 Emulator\n");
	
	// Set up render system and register input callbacks
	//setupGraphics();
  	//setupInput();
  	
	initialize();
  	
	loadApplication("ROMS/pong2.c8");

	// Emulation Loop
	for(;;){
		emulateCycle();
		
		// If the draw flag is set, update the screen
    	//if(drawFlag)
      		//drawGraphics();
 
    	// Store key press state (Press and Release)
    	//myChip.setKeys();	
	}
	
	return 0;
}
