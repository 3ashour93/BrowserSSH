/* 
 * CS:APP Data Lab 
 * 
 * Eisa Alkhulaifi : ekhulaif
 * 
 * bits.c - Source file with your solutions to the Lab.
 *          This is the file you will hand in to your instructor.
 *
 * WARNING: Do not include the <stdio.h> header; it confuses the dlc
 * compiler. You can still use printf for debugging without including
 * <stdio.h>, although you might get a compiler warning. In general,
 * it's not good practice to ignore compiler warnings, but in this
 * case it's OK.  
 */

#if 0
/*
 * Instructions to Students:
 *
 * STEP 1: Read the following instructions carefully.
 */

You will provide your solution to the Data Lab by
editing the collection of functions in this source file.

INTEGER CODING RULES:
 
  Replace the "return" statement in each function with one
  or more lines of C code that implements the function. Your code 
  must conform to the following style:
 
  int Funct(arg1, arg2, ...) {
      /* brief description of how your implementation works */
      int var1 = Expr1;
      ...
      int varM = ExprM;

      varJ = ExprJ;
      ...
      varN = ExprN;
      return ExprR;
  }

  Each "Expr" is an expression using ONLY the following:
  1. Integer constants 0 through 255 (0xFF), inclusive. You are
      not allowed to use big constants such as 0xffffffff.
  2. Function arguments and local variables (no global variables).
  3. Unary integer operations ! ~
  4. Binary integer operations & ^ | + << >>
    
  Some of the problems restrict the set of allowed operators even further.
  Each "Expr" may consist of multiple operators. You are not restricted to
  one operator per line.

  You are expressly forbidden to:
  1. Use any control constructs such as if, do, while, for, switch, etc.
  2. Define or use any macros.
  3. Define any additional functions in this file.
  4. Call any functions.
  5. Use any other operations, such as &&, ||, -, or ?:
  6. Use any form of casting.
  7. Use any data type other than int.  This implies that you
     cannot use arrays, structs, or unions.

 
  You may assume that your machine:
  1. Uses 2s complement, 32-bit representations of integers.
  2. Performs right shifts arithmetically.
  3. Has unpredictable behavior when shifting an integer by more
     than the word size.

EXAMPLES OF ACCEPTABLE CODING STYLE:
  /*
   * pow2plus1 - returns 2^x + 1, where 0 <= x <= 31
   */
  int pow2plus1(int x) {
     /* exploit ability of shifts to compute powers of 2 */
     return (1 << x) + 1;
  }

  /*
   * pow2plus4 - returns 2^x + 4, where 0 <= x <= 31
   */
  int pow2plus4(int x) {
     /* exploit ability of shifts to compute powers of 2 */
     int result = (1 << x);
     result += 4;
     return result;
  }

FLOATING POINT CODING RULES

For the problems that require you to implent floating-point operations,
the coding rules are less strict.  You are allowed to use looping and
conditional control.  You are allowed to use both ints and unsigneds.
You can use arbitrary integer and unsigned constants.

You are expressly forbidden to:
  1. Define or use any macros.
  2. Define any additional functions in this file.
  3. Call any functions.
  4. Use any form of casting.
  5. Use any data type other than int or unsigned.  This means that you
     cannot use arrays, structs, or unions.
  6. Use any floating point data types, operations, or constants.


NOTES:
  1. Use the dlc (data lab checker) compiler (described in the handout) to 
     check the legality of your solutions.
  2. Each function has a maximum number of operators (! ~ & ^ | + << >>)
     that you are allowed to use for your implementation of the function. 
     The max operator count is checked by dlc. Note that '=' is not 
     counted; you may use as many of these as you want without penalty.
  3. Use the btest test harness to check your functions for correctness.
  4. Use the BDD checker to formally verify your functions
  5. The maximum number of ops for each function is given in the
     header comment for each function. If there are any inconsistencies 
     between the maximum ops in the writeup and in this file, consider
     this file the authoritative source.

/*
 * STEP 2: Modify the following functions according the coding rules.
 * 
 *   IMPORTANT. TO AVOID GRADING SURPRISES:
 *   1. Use the dlc compiler to check that your solutions conform
 *      to the coding rules.
 *   2. Use the BDD checker to formally verify that your solutions produce 
 *      the correct answers.
 */


#endif
/* 
 * bitXor - x^y using only ~ and & 
 *   Example: bitXor(4, 5) = 1
 *   Legal ops: ~ &
 *   Max ops: 14
 *   Rating: 1
 */
int bitXor(int x, int y) {
       /* bitXor is basically everything from the | 
	  but nothing from the &, so x^y = x|y & ~(x&y).
	* however, since we can only use & and ~, we have 
	  to make an OR without using |. */
       int z = ~(~x & ~y); /* | */
       return z & ~(x&y);
}
/* 
 * allOddBits - return 1 if all odd-numbered bits in word set to 1
 *   Examples allOddBits(0xFFFFFFFD) = 0, allOddBits(0xAAAAAAAA) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 2
 */
int allOddBits(int x) {
  /* making an int with only odd numbered bits as 1 */
  int halfOdds = (0xAA << 8) | 0xAA;
  int odds = (halfOdds << 16) | halfOdds;

  /* making all even numbered bits 0 since we dont need them.
   * then Ex-oring that with all odd numbered bits as 1, 
   * so if any odd numbered bit is a 0 then the resulting bit 
   * will be a 1. 
   * if all odd bits were 1, a ! will return 1 and 0 otherwise.*/
  return !((x & odds) ^ odds);
}
/* 
 * getByte - Extract byte n from word x
 *   Bytes numbered from 0 (LSB) to 3 (MSB)
 *   Examples: getByte(0x12345678,1) = 0x56
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 6
 *   Rating: 2
 */
int getByte(int x, int n) {
  /* moving the nth byte to the right, 
     and zeroing everything else */
  int shifted = x >> (n << 3);
  return shifted & 0xFF;
}
/* 
 * reverseBytes - reverse the bytes of x
 *   Example: reverseBytes(0x01020304) = 0x04030201
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 25
 *   Rating: 3
 */
int reverseBytes(int x) {
  int byte1 = (x & 0xFF) << 24;
  int byte2 = (x & (0xFF << 8)) << 8;
  int byte3 = (x & (0xFF << 16)) >> 8;
  int byte4 = ((x & (0xFF << 24)) >> 24) & 0xFF;
  return (byte1 | byte2 | byte3 | byte4); 
}
/* 
 * bitMask - Generate a mask consisting of all 1's 
 *   lowbit and highbit
 *   Examples: bitMask(5,3) = 0x38
 *   Assume 0 <= lowbit <= 31, and 0 <= highbit <= 31
 *   If lowbit > highbit, then mask should be all 0's
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 16
 *   Rating: 3
 */
int bitMask(int highbit, int lowbit) {
  int Ones = ~0;

  int low = Ones << lowbit;
  int high = (Ones << highbit) << 1;

  return (low ^ high) & low;
}
/* 
 * bang - Compute !x without using !
 *   Examples: bang(3) = 0, bang(0) = 1
 *   Legal ops: ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 4 
 */
int bang(int x) {
  /* we combine all the bits using |, so even if
     there is only one bit set to 1, we would
     end up with a 1 as the least significant bit.
  */
  x = x | (x >> 16);
  x = x | (x >> 8);
  x = x | (x >> 4);
  x = x | (x >> 2);
  x = x | (x >> 1);

  /* now we remove all bits except for the least
     significant bit.
  */
  return ~x & 1;
}
/* 
 * isNegative - return 1 if x < 0, return 0 otherwise 
 *   Example: isNegative(-1) = 1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 6
 *   Rating: 2
 */
int isNegative(int x) {
  return (x >> 31) & 1;
}
/* 
 * negate - return -x 
 *   Example: negate(1) = -1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 5
 *   Rating: 2
 */
int negate(int x) {
  return ~x + 1;
}
/* 
 * subOK - Determine if can compute x-y without overflow
 *   Example: subOK(0x80000000,0x80000000) = 1,
 *            subOK(0x80000000,0x70000000) = 0, 
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Rating: 3
 */
int subOK(int x, int y) {  
  /* there are two conditions that cause overflow:-
   * x and y will have different signs,
   * and y and the diff will have the same sign.
   */

  // checking if x and y have different signs
  int check = (y ^ x) >> 31;

  // calculating the difference
  int s = x + (~y + 1);

  // checking if y and the difference have the same sign.
  int check2 = !((y ^ s) >> 31);

  return !(check & check2);
}
/* 
 * isLess - if x < y  then return 1, else return 0 
 *   Example: isLess(4,5) = 1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 24
 *   Rating: 3
 */
int isLess(int x, int y) {
  int xSign = (x >> 31) & 1;

  int ySign = (y >> 31) & 1;

  int check = xSign ^ ySign;

  int z = x + (~y + 1);

  int zSign = (z >> 31) & 1;

  return (check & (!ySign)) | ((!check) & zSign);
}
/*
 * multFiveEighths - multiplies by 5/8 rounding toward 0.
 *   Should exactly duplicate effect of C expression (x*5/8),
 *   including overflow behavior.
 *   Examples: multFiveEighths(77) = 48
 *             multFiveEighths(-22) = -13
 *             multFiveEighths(1073741824) = 13421728 (overflow)
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 3
 */
int multFiveEighths(int x) {
  // multiplying by 5.
  int top  = (x << 2) + x;

  /* this is to check if the top part is negative 
   * (if it is we apply the bias), otherwise we dont.
   */
  int sign = (top >> 31);
  int a1 = 1 & sign;
  int added = (a1 << 3) + (~a1 + 1);

  // dividing by 8 and adding bias.
  return (top + added) >> 3;
}
/* 
 * float_abs - Return bit-level equivalent of absolute value of f for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representations of
 *   single-precision floating point values.
 *   When argument is NaN, return argument..
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 10
 *   Rating: 2
 */
unsigned float_abs(unsigned uf) {
  int eCheck = (uf & 0x7f800000) == 0x7f800000;
  int fCheck = (uf & 0x007fffff) != 0;

  if (eCheck && fCheck ) {
    return  uf;
  }
  else {return uf & 0x7fffffff;;}
}
/* 
 * float_f2i - Return bit-level equivalent of expression (int) f
 *   for floating point argument f.
 *   Argument is passed as unsigned int, but
 *   it is to be interpreted as the bit-level representation of a
 *   single-precision floating point value.
 *   Anything out of range (including NaN and infinity) should return
 *   0x80000000u.
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 30
 *   Rating: 4
 */
int float_f2i(unsigned uf) {
  int sign = (uf >> 31) & 1;
  int exp  = uf & 0x7f800000;
  int frac = (uf & 0x007fffff) | 0x800000;
 
  // eCheck1 is infinity check.
  int eCheck1 = exp == 0x7f800000;

  // eCheck2 is denormalized.
  int eCheck2 = exp == 0;
  
  if (eCheck1) {
    // out of range
    return 0x80000000u;
  }
  else if (eCheck2){
    return 0;
  }
  else { 
    //getting e by getting it in the left and minusing bias.
    int E = (exp >> 23) - 127;

    // if E < 0 means a fraction so not integer so 0.
    if (E < 0) {
      return 0;
    }

    // if over 30 then out of range.
    else if (E > 30){
      return 0x80000000u;
    }
    else {
      /* if E < 23 then we want the E first bits of the frac
       * so we remove the last (23 - E) bits.
       */
      if (E < 23) {
	int N = frac >> (23 - E);
	if (sign) {
	  return -N;
	}
	else {
	  return N;
	}
      }
      /* if E >= 23 then we want to add zeros from the right
       * but we dont want to lose the frac so we shift it 
       * left by (E - 23) bits
       */
      else {
	int N = frac << (E - 23);
	if (sign) {
	  return -N;
	}
	else {
	  return N;
	}	
      }
    } 
  }
}
