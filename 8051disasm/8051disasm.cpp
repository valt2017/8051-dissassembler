// 8051disasm.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <vector>
#include <cstdio>
#include <fstream>

struct Instruction {
	int Bytes;
	std::string Mnemonic;
	std::string Operands;
};

std::vector<Instruction> Instructions = {
	{/* 00	*/ 1,"NOP",""},
	{/* 01	*/ 2,"AJMP","%02XH" },
	{/* 02	*/ 3,"LJMP","%02X%02XH" },
	{/* 03	*/ 1,"RR","A" },
	{/* 04	*/ 1,"INC","A" },
	{/* 05	*/ 2,"INC","%02XH" },
	{/* 06	*/ 1,"INC","@R0" },
	{/* 07	*/ 1,"INC","@R1" },
	{/* 08	*/ 1,"INC","R0" },
	{/* 09	*/ 1,"INC","R1" },
	{/* 0A	*/ 1,"INC","R2" },
	{/* 0B	*/ 1,"INC","R3" },
	{/* 0C	*/ 1,"INC","R4" },
	{/* 0D	*/ 1,"INC","R5" },
	{/* 0E	*/ 1,"INC","R6" },
	{/* 0F	*/ 1,"INC","R7" },
	{/* 10	*/ 3,"JBC","%02X%02XH" },
	{/* 11	*/ 2,"ACALL","%02XH" },
	{/* 12	*/ 3,"LCALL","%02X%02XH" },
	{/* 13	*/ 1,"RRC","A" },
	{/* 14	*/ 1,"DEC","A" },
	{/* 15	*/ 2,"DEC","%02XH" },
	{/* 16	*/ 1,"DEC","@R0" },
	{/*	17	*/ 1,"DEC","@R1" },
	{/*	18	*/ 1,"DEC","R0" },
	{/*	19	*/ 1,"DEC","R1" },
	{/* 1A	*/ 1,"DEC","R2" },
	{/* 1B	*/ 1,"DEC","R3" },
	{/* 1C	*/ 1,"DEC","R4" },
	{/* 1D	*/ 1,"DEC","R5" },
	{/* 1E	*/ 1,"DEC","R6" },
	{/* 1F	*/ 1,"DEC","R7" },
	{/* 20	*/ 3,"JB","%02X%02XH" },
	{/* 21	*/ 2,"AJMP","%02XH" },
	{/* 22	*/ 1,"RET","" },
	{/* 23	*/ 1,"RL","A" },
	{/* 24	*/ 2,"ADD","A, #%02XH" },
	{/* 25	*/ 2,"ADD","A, %02XH" },
	{/* 26	*/ 1,"ADD","A, @R0" },
	{/* 27	*/ 1,"ADD","A, @R1" },
	{/* 28	*/ 1,"ADD","A, R0" },
	{/* 29	*/ 1,"ADD","A, R1" },
	{/* 2A	*/ 1,"ADD","A, R2" },
	{/* 2B	*/ 1,"ADD","A, R3" },
	{/* 2C	*/ 1,"ADD","A, R4" },
	{/* 2D	*/ 1,"ADD","A, R5" },
	{/* 2E	*/ 1,"ADD","A, R6" },
	{/* 2F	*/ 1,"ADD","A, R7" },
	{/* 30	*/ 3,"JNB","%02X%02XH" },
	{/* 31	*/ 2,"ACALL","%02XH" },
	{/* 32	*/ 1,"RETI","" },
	{/* 33	*/ 1,"RLC","A" },
	{/* 34	*/ 2,"ADDC","A, #%02XH" },
	{/* 35	*/ 2,"ADDC","A, %02XH" },
	{/* 36	*/ 1,"ADDC","A, @R0" },
	{/* 37	*/ 1,"ADDC","A, @R1" },
	{/* 38	*/ 1,"ADDC","A, R0" },
	{/* 39	*/ 1,"ADDC","A, R1" },
	{/* 3A	*/ 1,"ADDC","A, R2" },
	{/* 3B	*/ 1,"ADDC","A, R3" },
	{/* 3C	*/ 1,"ADDC","A, R4" },
	{/* 3D	*/ 1,"ADDC","A, R5" },
	{/* 3E	*/ 1,"ADDC","A, R6" },
	{/* 3F	*/ 1,"ADDC","A, R7" },
	{/* 40	*/ 2,"JC","%02XH" },
	{/* 41	*/ 2,"AJMP","%02XH" },
	{/* 42	*/ 2,"ORL","%02XH, A" },
	{/* 43	*/ 3,"ORL","%02XH, #%02XH" },
	{/* 44	*/ 2,"ORL","A, #%02XH" },
	{/* 45	*/ 2,"ORL","A, %02XH" },
	{/* 46	*/ 1,"ORL","A, @R0" },
	{/* 47	*/ 1,"ORL","A, @R1" },
	{/* 48	*/ 1,"ORL","A, R0" },
	{/* 49	*/ 1,"ORL","A, R1" },
	{/* 4A	*/ 1,"ORL","A, R2" },
	{/* 4B	*/ 1,"ORL","A, R3" },
	{/* 4C	*/ 1,"ORL","A, R4" },
	{/* 4D	*/ 1,"ORL","A, R5" },
	{/* 4E	*/ 1,"ORL","A, R6" },
	{/* 4F	*/ 1,"ORL","A, R7" },
	{/* 50	*/ 2,"JNC","%02XH" },
	{/* 51	*/ 2,"ACALL","%02XH" },
	{/* 52	*/ 2,"ANL","%02XH, A" },
	{/* 53	*/ 3,"ANL","%02XH, #%02XH" },
	{/* 54	*/ 2,"ANL","A, #%02XH" },
	{/* 55	*/ 2,"ANL","A, %02XH" },
	{/* 56	*/ 1,"ANL","A, @R0" },
	{/* 57	*/ 1,"ANL","A, @R1" },
	{/* 58	*/ 1,"ANL","A, R0" },
	{/* 59	*/ 1,"ANL","A, R1" },
	{/* 5A	*/ 1,"ANL","A, R2" },
	{/* 5B	*/ 1,"ANL","A, R3" },
	{/* 5C	*/ 1,"ANL","A, R4" },
	{/* 5D	*/ 1,"ANL","A, R5" },
	{/* 5E	*/ 1,"ANL","A, R6" },
	{/* 5F	*/ 1,"ANL","A, R7" },
	{/* 60	*/ 2,"JZ","%02XH" },
	{/* 61	*/ 2,"AJMP","%02XH" },
	{/* 62	*/ 2,"XRL","%02XH, A" },
	{/* 63	*/ 3,"XRL","%02XH, #%02XH" },
	{/* 64	*/ 2,"XRL", "A, #%02XH" },
	{/* 65	*/ 2,"XRL", "A, %02XH" },
	{/* 66	*/ 1,"XRL", "A, @R0" },
	{/* 67	*/ 1,"XRL", "A, @R1" },
	{/* 68	*/ 1,"XRL", "A, R0" },
	{/* 69	*/ 1,"XRL", "A, R1" },
	{/* 6A	*/ 1,"XRL", "A, R2" },
	{/* 6B	*/ 1,"XRL", "A, R3" },
	{/* 6C	*/ 1, "XRL", "A, R4" },
	{/* 6D	*/ 1, "XRL", "A, R5" },
	{/* 6E	*/ 1, "XRL", "A, R6" },
	{/* 6F	*/ 1, "XRL", "A, R7" },
	{/* 70	*/ 2, "JNZ", "%02XH" },
	{/* 71	*/ 2, "ACALL", "%02XH" },
	{/* 72	*/ 2, "ORL", "C, %02XH" },
	{/* 73	*/ 1, "JMP", "@A+DPTR" },
	{/* 74	*/ 2, "MOV", "A, #%02XH" },
	{/* 75	*/ 3, "MOV", "%02XH, #%02XH" },
	{/* 76	*/ 2, "MOV", "@R0, #%02XH" },
	{/* 77	*/ 2, "MOV", "@R1, #%02XH" },
	{/* 78	*/ 2, "MOV", "R0, #%02XH" },
	{/* 79	*/ 2, "MOV", "R1, #%02XH" },
	{/* 7A	*/ 2, "MOV", "R2, #%02XH" },
	{/* 7B	*/ 2, "MOV", "R3, #%02XH" },
	{/* 7C	*/ 2, "MOV", "R4, #%02XH" },
	{/* 7D	*/ 2, "MOV", "R5, #%02XH" },
	{/* 7E	*/ 2, "MOV", "R6, #%02XH" },
	{/* 7F	*/ 2, "MOV", "R7, #%02XH" },
	{/* 80	*/ 2, "SJMP", "%02XH" },
	{/* 81	*/ 2, "AJMP", "%02XH" },
	{/* 82	*/ 2, "ANL", "C, %02XH" },
	{/* 83	*/ 1, "MOVC", "A, @A+PC" },
	{/* 84	*/ 1, "DIV", "AB" },
	{/* 85	*/ 3, "MOV", "%02XH, %02XH" },
	{/* 86	*/ 2, "MOV", "%02XH, @R0" },
	{/* 87	*/ 2, "MOV", "%02XH, @R1" },
	{/* 88	*/ 2, "MOV", "%02XH, R0" },
	{/* 89	*/ 2, "MOV", "%02XH, R1" },
	{/* 8A	*/ 2, "MOV", "%02XH, R2" },
	{/* 8B	*/ 2, "MOV", "%02XH, R3" },
	{/* 8C	*/ 2, "MOV", "%02XH, R4" },
	{/* 8D	*/ 2, "MOV", "%02XH, R5" },
	{/* 8E	*/ 2, "MOV", "%02XH, R6" },
	{/* 8F	*/ 2, "MOV", "%02XH, R7" },
	{/* 90	*/ 3, "MOV", "DPTR, #%02X%02XH" },
	{/* 91	*/ 2, "ACALL", "%02XH" },
	{/* 92	*/ 2, "MOV", "%02XH, C" },
	{/* 93	*/ 1, "MOVC", "A, @A+DPTR" },
	{/* 94	*/ 2, "SUBB", "A, #%02XH" },
	{/* 95	*/ 2, "SUBB", "A, %02XH" },
	{/* 96	*/ 1, "SUBB", "A, @R0" },
	{/* 97	*/ 1, "SUBB", "A, @R1" },
	{/* 98	*/ 1, "SUBB", "A, R0" },
	{/* 99	*/ 1, "SUBB", "A, R1" },
	{/* 9A	*/ 1, "SUBB", "A, R2" },
	{/* 9B	*/ 1, "SUBB", "A, R3" },
	{/* 9C	*/ 1, "SUBB", "A, R4" },
	{/* 9D	*/ 1, "SUBB", "A, R5" },
	{/* 9E	*/ 1, "SUBB", "A, R6" },
	{/* 9F	*/ 1, "SUBB", "A, R7" },
	{/* A0	*/ 2, "ORL", "C, / %02XH" },
	{/* A1	*/ 2, "AJMP", "%02XH" },
	{/* A2	*/ 2, "MOV", "C, %02XH" },
	{/* A3	*/ 1, "INC", "DPTR" },
	{/* A4	*/ 1, "MUL", "AB" },
	{/* A5	*/ 1, "reserved", "" },
	{/* A6	*/ 2, "MOV", "@R0, %02XH" },
	{/* A7	*/ 2, "MOV", "@R1, %02XH" },
	{/* A8	*/ 2, "MOV", "R0, %02XH" },
	{/* A9	*/ 2, "MOV", "R1, %02XH" },
	{/* AA	*/ 2, "MOV", "R2, %02XH" },
	{/* AB	*/ 2, "MOV", "R3, %02XH" },
	{/* AC	*/ 2, "MOV", "R4, %02XH" },
	{/* AD	*/ 2, "MOV", "R5, %02XH" },
	{/* AE	*/ 2, "MOV", "R6, %02XH" },
	{/* AF	*/ 2, "MOV", "R7, %02XH" },
	{/* B0	*/ 2, "ANL", "C, / %02XH" },
	{/* B1	*/ 2, "ACALL", "%02XH" },
	{/* B2	*/ 2, "CPL", "%02XH" },
	{/* B3	*/ 1, "CPL", "C" },
	{/* B4	*/ 3, "CJNE", "A, #%02XH, %02XH" },
	{/* B5	*/ 3, "CJNE", "A, %02XH, %02XH" },
	{/* B6	*/ 3, "CJNE", "@R0, #%02XH, %02XH" },
	{/* B7	*/ 3, "CJNE", "@R1, #%02XH, %02XH" },
	{/* B8	*/ 3, "CJNE", "R0, #%02XH, %02XH" },
	{/* B9	*/ 3, "CJNE", "R1, #%02XH, %02XH" },
	{/* BA	*/ 3, "CJNE", "R2, #%02XH, %02XH" },
	{/* BB	*/ 3, "CJNE", "R3, #%02XH, %02XH" },
	{/* BC	*/ 3, "CJNE", "R4, #%02XH, %02XH" },
	{/* BD	*/ 3, "CJNE", "R5, #%02XH, %02XH" },
	{/* BE	*/ 3, "CJNE", "R6, #%02XH, %02XH" },
	{/* BF	*/ 3, "CJNE", "R7, #%02XH, %02XH" },
	{/* C0	*/ 2, "PUSH", "%02XH" },
	{/* C1	*/ 2, "AJMP", "%02XH" },
	{/* C2	*/ 2, "CLR", "%02XH" },
	{/* C3	*/ 1, "CLR", "C" },
	{/* C4	*/ 1, "SWAP", "A" },
	{/* C5	*/ 2, "XCH", "A, %02XH" },
	{/* C6	*/ 1, "XCH", "A, @R0" },
	{/* C7	*/ 1, "XCH", "A, @R1" },
	{/* C8	*/ 1, "XCH", "A, R0" },
	{/* C9	*/ 1, "XCH", "A, R1" },
	{/* CA	*/ 1, "XCH", "A, R2" },
	{/* CB	*/ 1, "XCH", "A, R3" },
	{/* CC	*/ 1, "XCH", "A, R4" },
	{/* CD	*/ 1, "XCH", "A, R5" },
	{/* CE	*/ 1, "XCH", "A, R6" },
	{/* CF	*/ 1, "XCH", "A, R7" },
	{/* D0	*/ 2, "POP", "%02XH" },
	{/* D1	*/ 2, "ACALL", "%02XH" },
	{/* D2	*/ 2, "SETB", "%02XH" },
	{/* D3	*/ 1, "SETB", "C" },
	{/* D4	*/ 1, "DA", "A" },
	{/* D5	*/ 3, "DJNZ", "%02XH, %02XH" },
	{/* D6	*/ 1, "XCHD", "A, @R0" },
	{/* D7	*/ 1, "XCHD", "A, @R1" },
	{/* D8	*/ 2, "DJNZ", "R0, %02XH" },
	{/* D9	*/ 2, "DJNZ", "R1, %02XH" },
	{/* DA	*/ 2, "DJNZ", "R2, %02XH" },
	{/* DB	*/ 2, "DJNZ", "R3, %02XH" },
	{/* DC	*/ 2, "DJNZ", "R4, %02XH" },
	{/* DD	*/ 2, "DJNZ", "R5, %02XH" },
	{/* DE	*/ 2, "DJNZ", "R6, %02XH" },
	{/* DF	*/ 2, "DJNZ", "R7, %02XH" },
	{/* E0	*/ 1, "MOVX", "A, @DPTR" },
	{/* E1	*/ 2, "AJMP", "%02XH" },
	{/* E2	*/ 1, "MOVX", "A, @R0" },
	{/* E3	*/ 1, "MOVX", "A, @R1" },
	{/* E4	*/ 1, "CLR", "A" },
	{/* E5	*/ 2, "MOV", "A, %02XH" },
	{/* E6	*/ 1, "MOV", "A, @R0" },
	{/* E7	*/ 1, "MOV", "A, @R1" },
	{/* E8	*/ 1, "MOV", "A, R0" },
	{/* E9	*/ 1, "MOV", "A, R1" },
	{/* EA	*/ 1, "MOV", "A, R2" },
	{/* EB	*/ 1, "MOV", "A, R3" },
	{/* EC	*/ 1, "MOV", "A, R4" },
	{/* ED	*/ 1, "MOV", "A, R5" },
	{/* EE	*/ 1, "MOV", "A, R6" },
	{/* EF	*/ 1, "MOV", "A, R7" },
	{/* F0	*/ 1, "MOVX", "@DPTR, A" },
	{/* F1	*/ 2, "ACALL", "%02XH" },
	{/* F2	*/ 1, "MOVX", "@R0, A" },
	{/* F3	*/ 1, "MOVX", "@R1, A" },
	{/* F4  */ 1, "CPL", "A" },
	{/* F5	*/ 2, "MOV", "%02XH, A" },
	{/* F6	*/ 1, "MOV", "@R0, A" },
	{/* F7	*/ 1, "MOV", "@R1, A" },
	{/* F8  */ 1, "MOV", "R0, A" },
	{/* F9	*/ 1, "MOV", "R1, A" },
	{/* FA	*/ 1, "MOV", "R2, A" },
	{/* FB	*/ 1, "MOV", "R3, A" },
	{/* FC	*/ 1, "MOV", "R4, A" },
	{/* FD	*/ 1, "MOV", "R5, A" },
	{/* FE	*/ 1, "MOV", "R6, A" },
	{/* FF	*/ 1, "MOV", "R7, A" },
};

int main(int argc, char ** argv)
{
	if (argc != 2)
	{
		printf("usage: 8051disasm.exe file.bin\n");
		exit(EXIT_FAILURE);
	}
	std::ifstream pFin(argv[1], std::ios::in | std::ios::binary | std::ios::ate);
	if (!pFin.is_open())
	{
		printf("%s opening error\n",argv[1]);
		exit(EXIT_FAILURE);
	}
	unsigned long FileSize;
	unsigned long FilePos = 0;
	// obtain file size, ios::ate -> EOF
	FileSize = pFin.tellg();
	char * memblock = new char[FileSize];
	pFin.seekg(0, std::ios::beg);
	//File complete to memory
	pFin.read(memblock, FileSize);
	pFin.close();
	
	while(FilePos < FileSize)
	{
		// Address in bin file
		printf("%06X\t", FilePos);
		// Get instruction ID
		unsigned char InstrID = memblock[FilePos];
		// Write instruction ID and operands
		for (int j = 0; j < Instructions[InstrID].Bytes; j++)
			printf("%02X", (unsigned char)memblock[FilePos + j]);
		// Mnemonic of instruction
		printf("\t%s", (Instructions[InstrID].Mnemonic).c_str());
		// Operands of instuction
		switch (Instructions[InstrID].Bytes)
		{	// ID + 2 operands
			case 3:
				printf("\t");
				printf((Instructions[InstrID].Operands).c_str(), (unsigned char)memblock[FilePos + 1], (unsigned char)memblock[FilePos + 2]);
				printf("\n");
				break;
			// ID + 1 operand
			case 2:
				printf("\t");
				printf((Instructions[InstrID].Operands).c_str(), (unsigned char)memblock[FilePos + 1]);
				printf("\n");
				break;
			// ID only, no operands
			case 1:
			default:
				printf("\t%s\n", (Instructions[InstrID].Operands).c_str());
		}
		FilePos += Instructions[InstrID].Bytes;
	}
	delete[] memblock;
	return 0;
}

