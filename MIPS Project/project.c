// Jonathan Dieu and Gonzalo Ruiz
// CDA 3103C - MIPS Compiler Project

#include "spimcore.h"

/* ALU */
/* 10 Points */
void ALU(unsigned A,unsigned B,char ALUControl,unsigned *ALUresult,char *Zero)
{
    switch((int)ALUControl)
  {
      //Z = A+B
      case 0:
          *ALUresult = A + B;
          break;
      //Z = A-B
      case 1:
          *ALUresult = A - B;
          break;
      //If A<B, Z = 1, otherwise Z = 0
      case 2:
          if((signed) A < (signed) B)
              *ALUresult = 1;
          else
              *ALUresult = 0;
          break;
      //If A<B, Z = 1, otherwise Z = 0 UNSIGNED
      case 3:
          if(A < B)
              *ALUresult = 1;
          else
              *ALUresult = 0;
          break;
      //Z = A AND B
      case 4:
          *ALUresult = A & B;
          break;
      //Z = A OR B
      case 5:
          *ALUresult = A | B;
          break;
      //Shift left B by 16 bits
      case 6:
          *ALUresult = B << 16;   
          break;
      //Z = NOT A
      case 7:
          *ALUresult = ~A;
          break;
  }

  //Now check to see if the result is zero, and set the zero bit
  if(*ALUresult == 0)
  {
    *Zero = 1;
  }
  else
  {
    *Zero = 0;
  }
}


/* instruction fetch */
/* 10 Points */
int instruction_fetch(unsigned PC,unsigned *Mem,unsigned *instruction)
{		
    // If the PC is not byte addressed (or divisible by 4) it is an invalid instruction and cannot be fetched
  	if(PC % 4 != 0)
    {
      return 1;
    }
  
    // Multiply by 4 (shift by 2 bits) in order to get the correct address in memory
	*instruction = Mem[PC >> 2];
  		return 0;
}


/* instruction partition */
/* 10 Points */
void instruction_partition(unsigned instruction, unsigned *op, unsigned *r1,unsigned *r2, unsigned *r3, unsigned *funct, unsigned *offset, unsigned *jsec)
{
  // If the bits are not at the end of the string then shift right to place the bits at the end,
 
  // Bitmask to isolate

  *op = (instruction >> 26)  & 0b00000000000000000000000000111111; // Instruction[31-26]
  
  *r1 = (instruction >> 21)  & 0b00000000000000000000000000011111; // Instruction[25-21]
  
  *r2 = (instruction >> 16)  & 0b00000000000000000000000000011111; // Instruction[20-16]
  
  *r3 = (instruction >> 11)  & 0b00000000000000000000000000011111; // Instruction[15-11]
  
  *funct = instruction       & 0b00000000000000000000000000111111; // Instruction[5-0]
  
  *offset = instruction      & 0b00000000000000001111111111111111; // Instruction[15-0]
  
  *jsec = instruction        & 0b00000011111111111111111111111111; // Instruction[25-0]
}


/* instruction decode */
/* 15 Points */
int instruction_decode(unsigned op,struct_controls *controls)
{
	switch(op) {
        // R-Type
        case 0x0:
            controls->RegDst = 1;
      		controls->RegWrite = 1;
            controls->Jump = 0;
            controls->Branch = 0;
            controls->MemRead = 0;
            controls->MemtoReg = 0;
            controls->ALUOp = 7;
            controls->MemWrite = 0;
            controls->ALUSrc = 0;
            break;
        // Jump
        case 0x2:
            controls->RegDst = 0;
      		controls->RegWrite = 0;
            controls->Jump = 1;
            controls->Branch = 0;
            controls->MemRead = 0;
            controls->MemtoReg = 0;
            controls->ALUOp = 0;
            controls->MemWrite = 0;
            controls->ALUSrc = 0;
            break;
        // Branch Equal --> beq
        case 0x4:
            controls->RegDst = 2;
            controls->RegWrite = 0;
            controls->Jump = 0;
            controls->Branch = 1;
            controls->MemRead = 0;
            controls->MemtoReg = 2;
            controls->ALUOp = 1;
            controls->MemWrite = 0;
            controls->ALUSrc = 0;

            break;
        // Load Upper Immediate --> lui
        case 0xF:
            controls->RegDst = 0;
            controls->RegWrite = 1;
            controls->Jump = 0;
            controls->Branch = 0;
            controls->MemRead = 0;
            controls->MemtoReg = 0;
            controls->ALUOp = 6;
            controls->MemWrite = 0;
            controls->ALUSrc = 1;
            break;
        // Load Word --> lw
        case 0x23:
            controls->RegDst = 0;
            controls->RegWrite = 1;
            controls->Jump = 0;
            controls->Branch = 0;
            controls->MemRead = 1;
            controls->MemtoReg = 1;
            controls->ALUOp = 0;
            controls->MemWrite = 0;
            controls->ALUSrc = 1;
            break;
        // Store Word --> sw
        case 0x2B:
            controls->RegDst = 2;
            controls->RegWrite = 0;
            controls->Jump = 0;
            controls->Branch = 0;
            controls->MemRead = 0;
            controls->MemtoReg = 2;
            controls->ALUOp = 0;
            controls->MemWrite = 1;
            controls->ALUSrc = 1;
            break;
        // Add Immediate --> addi
        case 0x8:
            controls->RegDst = 0;
       			controls->RegWrite = 1;
            controls->Jump = 0;
            controls->Branch = 0;
            controls->MemRead = 0;
            controls->MemtoReg = 0;
            controls->ALUOp = 0;
            controls->MemWrite = 0;
            controls->ALUSrc = 1;
            break;
        // Set to 1 if Less Than Immediate --> slti
        case 0xA:
            controls->RegDst = 0;
            controls->RegWrite = 1;
            controls->Jump = 0;
            controls->Branch = 0;
            controls->MemRead = 0;
            controls->MemtoReg = 0;
            controls->ALUOp = 2;
            controls->MemWrite = 0;
            controls->ALUSrc = 1;
            break;
        // Set to 1 if Less Than Unsigned Immediate --> sltu
        case 0xB:
            controls->RegDst = 0;
            controls->RegWrite = 1;
            controls->Jump = 0;
            controls->Branch = 0;
            controls->MemRead = 0;
            controls->MemtoReg = 0;
            controls->ALUOp = 3;
            controls->MemWrite = 0;
            controls->ALUSrc = 1;
            break;
           // Bitwise OR Immediate
        case 0xD:
            controls->RegDst = 0;
            controls->RegWrite = 1;
            controls->Jump = 0;
            controls->Branch = 0;
            controls->MemRead = 0;
            controls->MemtoReg = 0;
            controls->ALUOp = 5;
            controls->MemWrite = 0;
            controls->ALUSrc = 1;
            break;
        // Bitwise AND Immediate
        case 0xC:
            controls->RegDst = 0;
            controls->RegWrite = 1;
            controls->Jump = 0;
            controls->Branch = 0;
            controls->MemRead = 0;
            controls->MemtoReg = 0;
            controls->ALUOp = 4;
            controls->MemWrite = 0;
            controls->ALUSrc = 1;
            break;

        // If it's not any of the previous cases, stop
        default:
            return 1;
    }
    // In case of no errors
    return 0;
}


/* Read Register */
/* 5 Points */
void read_register(unsigned r1,unsigned r2,unsigned *Reg,unsigned *data1,unsigned *data2)
{
	// Read from registers for the addresses of r1 and r2 and set data to the data stored in registers
    *data1 = Reg[r1];
    *data2 = Reg[r2];
}


/* Sign Extend */
/* 10 Points */
void sign_extend(unsigned offset,unsigned *extended_value)
{
  
  // Takes the offset and checks if the 16th bit is = 1 in order to determine whether or not the value is negative and should have an extended sign
  if(offset >> 15 == 1)
  {
    // Mask signficant bits to 1
    *extended_value = offset | 0xffff0000;
  }
  else
  {
    // Put 16 bits onto the front
    *extended_value = offset & 0x0000ffff;;
  }
  

}

/* ALU operations */
/* 10 Points */
int ALU_operations(unsigned data1,unsigned data2,unsigned extended_value,unsigned funct,char ALUOp,char ALUSrc,unsigned *ALUresult,char *Zero)
{
  // In the case that the ALUSrc is 1, data2 will be set to extended_value;
  if(ALUSrc == 1)
  {
    data2 = extended_value;
  }
  
  // 7 is an ALUop that represents R-Type instructions
  if(ALUOp == 7)
  {
    switch(funct)
    {
        // Subtraction
      case 32: 
        ALUOp = 0;
        break;
      case 34:
        ALUOp = 1;
        break;
      case 42:
        ALUOp = 2;
        break;
      case 43:
        ALUOp = 3;
        break;
      case 36:
        ALUOp = 4;
        break;
      case 37:
        ALUOp = 5;
        break;
      case 4:
        ALUOp = 6;
        break;
      case 39:
        ALUOp = 7;
        break;
      default:
        	return 1;
    }
    // Call the ALU function
    ALU(data1, data2, ALUOp, ALUresult, Zero);
  }
  else
  {
    // Call the ALU for non-functions
    ALU(data1, data2, ALUOp, ALUresult, Zero);
  }
  	return 0;
  
  
  // Set the correct ALUop for each R-Type instruction
  
  
  

}

/* Read / Write Memory */
/* 10 Points */
int rw_memory(unsigned ALUresult,unsigned data2,char MemWrite,char MemRead,unsigned *memdata,unsigned *Mem)
{
	// This if statement checks if ALUresult has a word aligned address
    if ((MemWrite || MemRead) && ALUresult % 4 != 0)
        return 1;

    if (MemWrite == 1)
    { 
        Mem[ALUresult >> 2] = data2; // Write data in memory
    } 
    else if (MemRead == 1) 
    { 
        *memdata = Mem[ALUresult >> 2]; // Read data from memory
    }

    // If there are no errors
    return 0;
}


/* Write Register */
/* 10 Points */
void write_register(unsigned r2,unsigned r3,unsigned memdata,unsigned ALUresult,char RegWrite,char RegDst,char MemtoReg,unsigned *Reg)
{
	// Only allowed to continue if RegWrite is asserted
    if( RegWrite != 1 )
        return;

  	// Make sure to combine the correct source to write in the correct register
  	// RegDst 0 is for itype instructions
    // RegDst 1 is for rtype instructions
    if ( MemtoReg == 1 ) 
    { // Memory is source of write
        if ( RegDst == 1)
            Reg[r3] = memdata;
        else
            Reg[r2] = memdata;
    } 
    else 
    { // ALU Result is the source
        if ( RegDst == 1 )
            Reg[r3] = ALUresult;
        else
            Reg[r2] = ALUresult;
    }
}

/* PC update */
/* 10 Points */
void PC_update(unsigned jsec,unsigned extended_value,char Branch,char Jump,char Zero,unsigned *PC)
{
	// Increase the PC in order to get to the next instruction
	*PC += 4;
  
  	// When zero & branch are asserted, use the extended value to increment the PC
    if (Zero && Branch)
        *PC += extended_value <<  2;

  	//Modify PC to jump addresses on Jump
  	if (Jump)
    {
        // Since jsec is 26 bits, we need to check if PC has bits in 31-27
        // so we can then merge that with the shift adjusted jsec
        *PC = (*PC & 0xf0000000) | jsec << 2;
    }
}

