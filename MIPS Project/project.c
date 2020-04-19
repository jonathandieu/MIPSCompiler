// Jonathan Dieu and Gonzalo Ruiz
// CDA 3103C - MIPS Compiler Project


/* ALU */
/* 10 Points */
void ALU(unsigned A,unsigned B,char ALUControl,unsigned *ALUresult,char *Zero)
{
    switch((int)ALUControl){
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
        *Zero = 1;
    else
        *Zero = 0;
}


/* instruction fetch */
/* 10 Points */
int instruction_fetch(unsigned PC,unsigned *Mem,unsigned *instruction)
{
    // Multiply by 4 in order to get the correct address in memory

   

    // if the PC is not byte addressed (or divisible by 4)

}


/* instruction partition */
/* 10 Points */
void instruction_partition(unsigned instruction, unsigned *op, unsigned *r1,unsigned *r2, unsigned *r3, unsigned *funct, unsigned *offset, unsigned *jsec)
{
    // Shift bits until we have only we want for each instruction field 

    // Bitwise shift by 26 in order to get upper/most significant 6 bits as the op code

    // Bitwise shifts to partition registers 1-3

    *r1 = 
    *r2 = (instruction >> 21) & 0x00

}



/* instruction decode */
/* 15 Points */
int instruction_decode(unsigned op,struct_controls *controls)
{

}

/* Read Register */
/* 5 Points */
void read_register(unsigned r1,unsigned r2,unsigned *Reg,unsigned *data1,unsigned *data2)
{

}


/* Sign Extend */
/* 10 Points */
void sign_extend(unsigned offset,unsigned *extended_value)
{

}

/* ALU operations */
/* 10 Points */
int ALU_operations(unsigned data1,unsigned data2,unsigned extended_value,unsigned funct,char ALUOp,char ALUSrc,unsigned *ALUresult,char *Zero)
{

}

/* Read / Write Memory */
/* 10 Points */
int rw_memory(unsigned ALUresult,unsigned data2,char MemWrite,char MemRead,unsigned *memdata,unsigned *Mem)
{

}


/* Write Register */
/* 10 Points */
void write_register(unsigned r2,unsigned r3,unsigned memdata,unsigned ALUresult,char RegWrite,char RegDst,char MemtoReg,unsigned *Reg)
{

}

/* PC update */
/* 10 Points */
void PC_update(unsigned jsec,unsigned extended_value,char Branch,char Jump,char Zero,unsigned *PC)
{

}
