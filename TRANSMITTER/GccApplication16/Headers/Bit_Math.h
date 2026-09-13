#ifndef _BIT_MATH_H_
#define _BIT_MATH_H_


#define SET_BIT(Var, BitNo)   ( (Var) = (Var) |( 1 << (BitNo)) )
#define CLR_BIT(Var, BitNo)   ((Var) =(Var) & ~(1 << (BitNo)))
#define Toggle_Bit(Var, BitNo) ((Var) = (Var)^ (1 << (BitNo)))
#define GET_BIT(Var, BitNo)   (((Var) >> (BitNo)) & 0x01)


#endif