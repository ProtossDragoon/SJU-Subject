#include<stdio.h>
#include<string.h>
#include<stdlib.h>


/*
 * Basic ADT
 */
typedef struct unsigned_binary US_BIN;
typedef struct signed_binary S_BIN;
typedef union union_binary BIN;
typedef unsigned char uchar;
typedef unsigned int uint32;

struct unsigned_binary {
	int maxlength;
	uchar bit[32];
};
struct signed_binary {
	int maxlength;
	uchar bit[32];
};
union union_binary {
	US_BIN us_bin;
	S_BIN s_bin;
};

#define	SIGNED 1
#define UNSIGNED 0

uint32	binaryUnsigned_print(US_BIN binary) {

	int startbit = binary.maxlength - 1;
	uint32 data = 0;
	uint32 pow = 1;

	for (int i = 0; i <= startbit; i++) {
		if (i != 0) pow = pow * 2;

		data = data + pow * (binary.bit[i] == '1' ? 1 : 0);
	}
	printf("dec : %u\n", data);
	return data;
}
int		binarySigned_print(S_BIN binary) {
	
	int startbit = binary.maxlength - 1;
	int data = 0;
	int pow = 1;

	for (int i = 0; i <= startbit; i++) {
		if (i != 0) pow = pow * 2;

		if (i != startbit) 
			data = data + pow * (binary.bit[i] == '1' ? 1 : 0);
		else
			data = data + (-1 * pow) * (binary.bit[i] == '1' ? 1 : 0);
	}
	printf("dec : %d\n", data);
	return data;
}
BIN		binaryFromDec(int signed_or_unsigned, int length, int dec) {

	BIN newbinary;
	int startbit = length - 1;

	if (length > 32) {
		printf("init_binary error!, length upper than 32\n");
		return;
	}
	for (int i = 0; i < 32; i++) {
		newbinary.s_bin.bit[i] = '#';
		newbinary.us_bin.bit[i] = '#';
	}


	if (signed_or_unsigned == SIGNED) {
		newbinary.s_bin.maxlength = length;
		for (int i = 0; i <= startbit; i++) {
			newbinary.s_bin.bit[i] = '0';
		}

		int tmpdec;
		if (dec < 0) tmpdec = (dec * -1);
		else tmpdec = dec;

		int position = 0;
		while (1)
		{
			newbinary.s_bin.bit[position] = (tmpdec % 2) + '0';
			tmpdec = tmpdec / 2;
			position++;
			if (tmpdec == 0)
				break;

			if (position >= length) {
				printf("overflow!\n");
			}
		}

		if (dec < 0) {
			for (int i = 0; i <= startbit; i++) {
				newbinary.s_bin.bit[i] = !(newbinary.s_bin.bit[i] - '0') + '0';
			}
			for (int i = 0, cnt = 1; i <= startbit && cnt != 0; i++) {
				cnt = 0;
				if (newbinary.s_bin.bit[i] == '1') {
					newbinary.s_bin.bit[i] = '0';
					cnt = 1;
				}
				else {
					newbinary.s_bin.bit[i] = '1';
				}
			}
		}
		return newbinary;
	}

	if (signed_or_unsigned == UNSIGNED) {
		if (dec < 0) {
			printf("init_binary error!, you have to init SIGNED mode if you throw negative number\n");
			return;
		}
		newbinary.us_bin.maxlength = length;
		for (int i = 0; i <= startbit; i++) {
			newbinary.us_bin.bit[i] = '#';
		}
		
		int position = 0;
		while (1)
		{
			newbinary.us_bin.bit[position] = (dec % 2) + '0';
			dec = dec / 2;
			position++;
			if (dec == 0)
				break;

			if (position >= length) {
				printf("overflow!\n");
			}
		}

		return newbinary;
	}

	printf("init_binary error!\n");
	return;
}
BIN		binaryFromUSINT(uint32 unsignedint) {

	BIN signed_or_unsigned_binary;
	int startbit = 31;
	signed_or_unsigned_binary.us_bin.maxlength = 32;
	for (int i = 0; i <= startbit; i++) {
		signed_or_unsigned_binary.us_bin.bit[i] = '0';
	}

	int position = 0;
	while (1)
	{
		signed_or_unsigned_binary.us_bin.bit[position] = (unsignedint % 2) + '0';
		unsignedint = unsignedint / 2;
		position++;
		if (unsignedint == 0)
			break;
	}

	return signed_or_unsigned_binary;
}
void	example_code1() {
	BIN binary;
	
	// bit = [index 0, index 1, index 2 ....]
	// index 0 = 2^0 bit, so index k = 2^k bit

	binary = binaryFromDec(SIGNED, 11, -15);
	binarySigned_print(binary.s_bin);
	binaryUnsigned_print(binary.us_bin);

	binary = binaryFromDec(UNSIGNED, 19, 12345);
	binarySigned_print(binary.s_bin);
	binaryUnsigned_print(binary.us_bin);

	binary = binaryFromUSINT(23);
	binarySigned_print(binary.s_bin);
	binaryUnsigned_print(binary.us_bin);
}




/**************************************/
/*			type define			      */
/**************************************/
#define DONTCARE 0
struct Control
{
	uchar RegDst;
	uchar Jump;
	uchar Branch;
	uchar MemRead;
	uchar MemtoReg;
	uchar ALUOp;
	uchar MemWrite;
	uchar ALUSrc;
	uchar RegWrite;
};

struct Reg_Read
{
	uint32 Read_data_1;
	uint32 Read_data_2;
};
struct ALU
{
	uchar zero; // 1: enable, 0: disable
	uint32 ALU_result;
};

struct Control control;
struct Reg_Read reg_read;
struct ALU alu;
uint32 mem[64] = { 0 };
uint32 reg[32] = { 0 };


/**************************************/
/*      function original form        */
/**************************************/
uint32	Inst_Fetch(uint32 read_addr);
void	Register_Read(uint32 read_reg_1, uint32 read_reg_2);
void	Control_Signal(uint32 opcode);
uchar	ALU_Control_Signal(uchar signal);
void	ALU_func(uchar ALU_control, uint32 a, uint32 b);
uint32	Memory_Access(uchar MemWrite, uchar MemRead, uint32 addr, uint32 write_data);
void	Register_Write(uchar RegWrite, uint32 Write_reg, uint32 Write_data);
uint32	Sign_Extend(uint32 inst_16);
uint32	Shift_Left_2(uint32 inst);
uint32	Add(uint32 a, uint32 b);
uint32	Mux(char signal, uint32 a_0, uint32 b_1);
void	print_reg_mem(void);


/**************************************/
/*       function implementation      */
/**************************************/
uint32 Inst_Fetch(uint32 read_addr) {
	return mem[read_addr];
}
void Register_Read(uint32 read_reg_1, uint32 read_reg_2) {
	reg_read.Read_data_1 = reg[read_reg_1];
	reg_read.Read_data_2 = reg[read_reg_2];
}
void Control_Signal(uint32 opcode) {
	if (opcode == 0) {
		// r type
		// add 000000 ~ 100000
		printf(">> ADD\n");
		control.RegDst = 1;
		control.Jump = 0;
		control.Branch = 0;

		control.MemRead = 0;
		control.ALUOp = 2;
		control.MemtoReg = 0;
		control.MemWrite = 0;
		control.ALUSrc = 0;
		control.RegWrite = 1;
	}
	else {
		// jump 000010
		if (opcode == 2) {
			printf(">> JUMP\n");
			control.RegDst = 0;
			control.Jump = 1;
			control.Branch = 0;

			control.MemRead = DONTCARE;
			control.ALUOp = DONTCARE;
			control.MemtoReg = DONTCARE;
			control.MemWrite = DONTCARE;
			control.ALUSrc = DONTCARE;
			control.RegWrite = DONTCARE;
		}
		// lw	100011
		if (opcode == 32 + 3) {
			printf(">> LW\n");
			control.RegDst = 0;
			control.Jump = 0;
			control.Branch = 0;

			control.MemRead = 1;
			control.ALUOp = 0;
			control.MemtoReg = 1;
			control.MemWrite = 0;
			control.ALUSrc = 1;
			control.RegWrite = 1;
		}
		// sw	101011
		if (opcode == 32 + 8 + 3) {
			printf(">> SW\n");
			control.RegDst = DONTCARE;
			control.Jump = 0;
			control.Branch = 0;

			control.MemRead = 0;
			control.ALUOp = 0;
			control.MemtoReg = DONTCARE;
			control.MemWrite = 1;
			control.ALUSrc = 1;
			control.RegWrite = 0;
		}
		// beq	000100
		if (opcode == 4) {
			printf(">> BEQ\n");
			control.RegDst = DONTCARE;
			control.Jump = 0;
			control.Branch = 1;

			control.MemRead = 0;
			control.ALUOp = 1;
			control.MemtoReg = DONTCARE;
			control.MemWrite = 0;
			control.ALUSrc = 0;
			control.RegWrite = 0;
		}
	}
}
uchar ALU_Control_Signal(uchar signal) {

	if (signal == 0) {
		return 2;
	}
	else if (signal == 1) {
		return 6;
	}
	else if (signal == 2) {
		return 2;
	}
	else {
		printf("-alu control signal param error-\n");
		return;
	}
}
void ALU_func(uchar ALU_control, uint32 a, uint32 b) {

	if (ALU_control == 2) {
		alu.ALU_result = a + b;
	}
	else if (ALU_control == 6) {
		alu.ALU_result = a - b;
	}
	else if (ALU_control == 0) {
		alu.ALU_result = a & b;
	}
	else if (ALU_control == 1) {
		alu.ALU_result = a | b;
	}
	else if (ALU_control == 7) {
		// set on less than
	}
	else {
		// not defined
	}

	if (alu.ALU_result == 0) {
		alu.zero = 1;
	}
}
uint32	Memory_Access(uchar MemWrite, uchar MemRead, uint32 addr, uint32 write_data) {

	if (MemWrite == 1) {

		mem[addr] = write_data;
		return DONTCARE;
	}

	if (MemRead == 1) {

		return mem[addr];
	}
}
void	Register_Write(uchar RegWrite, uint32 Write_reg, uint32 Write_data) {
	if (RegWrite == 1) {

		reg[Write_reg] = Write_data;
	}
}
uint32 Add(uint32 a, uint32 b) {
	return a + b;
}
uint32 Mux(char signal, uint32 a_0, uint32 b_1) {

	if (signal == 1) {
		return b_1;
	}
	else {
		return a_0;
	}
}

uint32 Sign_Extend(uint32 inst_16)
{
	uint32 inst_32 = 0;
	if ((inst_16 & 0x00008000)) // minus
	{
		inst_32 = inst_16 | 0xffff0000;
	}
	else // plus
	{
		inst_32 = inst_16;
	}

	return inst_32;
}
uint32 Shift_Left_2(uint32 inst)
{
	return inst << 2;
}
void print_reg_mem(void)
{
	int reg_index = 0;
	int mem_index = 0;

	printf("\n===================== REGISTER =====================\n");

	for (reg_index = 0; reg_index < 8; reg_index++)
	{
		printf("reg[%02d] = %08d        reg[%02d] = %08d        reg[%02d] = %08d        reg[%02d] = %08d \n",
			reg_index, reg[reg_index], reg_index + 8, reg[reg_index + 8], reg_index + 16, reg[reg_index + 16], reg_index + 24, reg[reg_index + 24]);
	}

	printf("===================== REGISTER =====================\n");

	printf("\n===================== MEMORY =====================\n");

	for (mem_index = 0; mem_index < 32; mem_index = mem_index + 4)
	{
		printf("mem[%02d] = %012d        mem[%02d] = %012d \n",
			mem_index, mem[mem_index], mem_index + 32, mem[mem_index + 32]);
	}
	printf("===================== MEMORY =====================\n");
}

void score_5() {

	uint32 pc = 0;
	FILE* fp;
	uint32 inst = 0;
	uint32 inst_31_26 = 0;
	uint32 inst_25_21 = 0;
	uint32 inst_20_16 = 0;
	uint32 inst_15_11 = 0;
	uint32 inst_15_0 = 0;
	uint32 inst_ext_32 = 0;
	uint32 inst_ext_shift = 0;
	uint32 pc_add_4 = 0;
	uint32 pc_add_inst = 0;
	uint32 mux_result = 0;
	uchar ALU_control = 0;
	uint32 inst_25_0 = 0;
	uint32 jump_addr = 0;
	uint32 mem_result = 0;

	uint32 add_result = 0;
	uint32 sign_extend_result = 0;

	int total_cycle = 0;

	/**************************************/
	/*      register initialization       */
	/**************************************/
	reg[8] = 41621;
	reg[9] = 41621;
	reg[16] = 40;
	
	/**************************************/
	/*        memory initialization       */
	/**************************************/
	mem[40] = 3578;



	if ( !(fp = fopen("5.txt", "r")) )
	{
		printf("error: file open fail !!\n");
		exit(1);
	}
		
//	fscanf(fp, "%x", &inst);
	while (!feof(fp))
	{		
		fscanf(fp, "%x", &inst);
		mem[pc] = inst;
		pc = pc + 4;
	}


	/**************************************/
	/*      control initialization        */
	/**************************************/
	control.RegDst = 0;
	control.Jump = 0;
	control.Branch = 0;
	control.MemRead = 0;
	control.ALUOp = 0;
	control.MemWrite = 0;
	control.ALUSrc = 0;
	control.RegWrite = 0;


	print_reg_mem();
	printf("\n ***** Processor START !!! ***** \n");
	pc = 0;
	while (pc < 64)
	{
		// pc +4
		pc_add_4 = Add(pc, 4);

		// instruction fetch
		inst = Inst_Fetch(pc);
		printf("Instruction = %08x \n", inst);

		// instruction decode
		inst_31_26 = inst >> 26;
		inst_25_21 = (inst & 0x03e00000) >> 21; // 0011 1110 0000 0000 0000 0000 0000‬
		inst_20_16 = (inst & 0x001f0000) >> 16;
		inst_15_11 = (inst & 0x0000f800) >> 11;
		inst_15_0 = inst & 0x0000ffff;
		inst_25_0 = inst & 0x03ffffff;

		//printf("%x, %x, %x, %x, %x, %x\n", inst_31_26, inst_25_21, inst_20_16, inst_15_11, inst_15_0, inst_25_0);
		
		// type check
		
		// set control signal and read register value
		Control_Signal(inst_31_26);
		Register_Read(inst_25_21, inst_20_16);


		// jump


		// alu_control_signal = ALU_Control_Signal(control.ALUOp)
		sign_extend_result = Sign_Extend(inst_15_0);
		ALU_func(ALU_Control_Signal(control.ALUOp), reg_read.Read_data_1, Mux(control.ALUSrc, reg_read.Read_data_2, sign_extend_result));
		add_result = Add(pc_add_4, Shift_Left_2(sign_extend_result));




		// data memory
		uint32 toregval;
		toregval = Memory_Access(control.MemWrite, control.MemRead, alu.ALU_result, reg_read.Read_data_2);

		uchar tmp = (control.Branch & alu.zero);
		uint32 tmp2 = pc_add_4 & 0xf0000000;
		

		pc = Mux(
			control.Jump, 
			Mux(control.Branch & alu.zero, pc_add_4, add_result), 
			Add(pc_add_4 & 0xf0000000, Shift_Left_2(inst_25_0))
		);

		
		// save data to register
		Register_Write(control.RegWrite, 
			Mux(control.RegDst, inst_20_16, inst_15_11), 
			Mux(control.MemtoReg, alu.ALU_result, toregval));



		/********************************/
		/*       implementation         */
		/********************************/
		total_cycle++;

		/********************************/
		/*            result            */
		/********************************/
		printf("PC : %d \n", pc);
		printf("Total cycle : %d \n", total_cycle);
		print_reg_mem();

		//system("pause");
	}

	printf("\n ***** Processor END !!! ***** \n");
	return 0;
}
void score_7() {
	example_code1();

	uint32 pc = 0;
	FILE* fp;
	uint32 inst = 0;
	uint32 inst_31_26 = 0;
	uint32 inst_25_21 = 0;
	uint32 inst_20_16 = 0;
	uint32 inst_15_11 = 0;
	uint32 inst_15_0 = 0;
	uint32 inst_ext_32 = 0;
	uint32 inst_ext_shift = 0;
	uint32 pc_add_4 = 0;
	uint32 pc_add_inst = 0;
	uint32 mux_result = 0;
	unsigned char ALU_control = 0;
	uint32 inst_25_0 = 0;
	uint32 jump_addr = 0;
	uint32 mem_result = 0;
	int total_cycle = 0;

	// register initialization
	/**************************************/
	reg[8] = 41621;
	reg[9] = 41621;
	reg[16] = 40;
	/**************************************/

	// memory initialization
	/**************************************/
	mem[40] = 3578;


	/*
	if ( !(fp = fopen("input.txt", "r")) )
	{
		printf("error: file open fail !!\n");
		exit(1);
	}

	while (feof(fp) == false)
	{
		fscanf(fp, "%x", &inst);
		mem[pc] = inst;
		pc = pc + 4;
	}
	*/


	while (1)
	{
		scanf("%x", &inst);
		if (inst == 0)
			break;
		mem[pc] = inst;
		pc = pc + 4;
	}


	/**************************************/
	// control initialization
	/**************************************/
	control.RegDst = 0;
	control.Jump = 0;
	control.Branch = 0;
	control.MemRead = 0;
	control.ALUOp = 0;
	control.MemWrite = 0;
	control.ALUSrc = 0;
	control.RegWrite = 0;
	/**************************************/

	print_reg_mem();

	printf("\n ***** Processor START !!! ***** \n");

	pc = 0;

	while (pc < 64)
	{
		// pc +4
		pc_add_4 = Add(pc, 4);

		// instruction fetch
		inst = Inst_Fetch(pc);
		printf("Instruction = %08x \n", inst);


		// instruction decode
		inst_31_26 = inst >> 26;
		inst_25_21 = (inst & 0x03e00000) >> 21;
		inst_20_16 = (inst & 0x001f0000) >> 16;
		inst_15_11 = (inst & 0x0000f800) >> 11;
		inst_15_0 = inst & 0x0000ffff;
		inst_25_0 = inst & 0x03ffffff;

		//printf("%x, %x, %x, %x, %x, %x", inst_31_26, inst_25_21, inst_20_16, inst_15_11, inst_15_0, inst_25_0);


		// register read


		// create control signal


		// create ALU control signal


		// ALU


		// memory access


		// register write


		total_cycle++;

		// result
		/********************************/
		printf("PC : %d \n", pc);
		printf("Total cycle : %d \n", total_cycle);
		print_reg_mem();
		/********************************/

		system("pause");
	}

	printf("\n ***** Processor END !!! ***** \n");


}

int main() {

	score_5();

	return 0;
}