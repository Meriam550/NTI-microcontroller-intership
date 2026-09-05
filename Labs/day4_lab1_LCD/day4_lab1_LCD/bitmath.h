#ifndef _BITMATH_H
#define _BITMATH_H




#define SET_BIT(REG, BIT)        ((REG) |= (1U << (BIT)))
#define CLEAR_BIT(REG, BIT)      ((REG) &= ~(1U << (BIT)))
#define TOGGLE_BIT(REG, BIT)     ((REG) ^= (1U << (BIT)))
#define READ_BIT(REG, BIT)       (((REG) >> (BIT)) & 1U)
#define WRITE_BIT(REG, BIT, VAL) ((VAL) ? SET_BIT(REG, BIT) : CLEAR_BIT(REG, BIT))

#define IS_BIT_SET(REG, BIT)     (((REG) & (1U << (BIT))) != 0)
#define IS_BIT_CLEAR(REG, BIT)   (((REG) & (1U << (BIT))) == 0)


#endif