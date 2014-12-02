/* 
 * CS:APP Data Lab 
 * 
 * <Omar Ashour - omashour>
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
       //We know that x^y is (x | y) & ~(x & y)
       //Using DeMorgan's Law we can remove the OR expression
       return ~(~x & ~y) & ~(x & y);
}
/* 
 * allOddBits - return 1 if all odd-numbered bits in word set to 1
 *   Examples allOddBits(0xFFFFFFFD) = 0, allOddBits(0xAAAAAAAA) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 2
 */
int allOddBits(int x) {
  int oddByte = 0xAA; 
  //We create a 32 bit mask of odd bits that are into 1 
  int oddBits = (oddByte) | (oddByte << 24) | (oddByte << 16) | (oddByte << 8);
  //Removing all the even bits by (x & oddBits)
  //Checking for similarity by inverting the result of the xor with the 
  //new result
  return !((x & oddBits)^(oddBits)); 
  
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
  //We know that a byte is 8 bits
  //n*8 is the number of bits to right shift to get a byte
  //masking with 0xff extract the byte
  return (x >> (n << 3)) & (0xFF);
}
/* 
 * reverseBytes - reverse the bytes of x
 *   Example: reverseBytes(0x01020304) = 0x04030201
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 25
 *   Rating: 3
 */
int reverseBytes(int x) {
  //Get each byte
  int firstByte = x & 0xFF;
  int secondByte = (x >> 8) & 0xFF; 
  int thirdByte = (x >> 16) & 0xFF; 
  int fourthByte = (x >> 24) & 0xFF;
  //Shifting and Or operations to put each byte accordingly
  return (firstByte << 24) | (secondByte << 16) | (thirdByte << 8) | fourthByte;  
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
  int bits = ~0; 
  int lo = bits << lowbit;
  int lShifts = highbit + 1;
  //Note: we didn't shift by highbit + 1 to avoid shifiting by 
  //32 which is undefined if highbnit = 31 (after testing)
  int hi = (bits << highbit << 1);
  //mask done by getting the difference between lo and hi
  int mask = lo ^ hi;
  //check if lowBit > highbit 
  //by chcking the sign of highbit - lowbit is negative 
  int check = ((~lowbit + lShifts) >> 31) & 1;
  //if true then 0 else 0xffffffff
  int andBits = check + bits; 
  return mask & andBits;
}
/* 
 * bang - Compute !x without using !
 *   Examples: bang(3) = 0, bang(0) = 1
 *   Legal ops: ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 4 
 */
int bang(int x) {
  //checking if x is positive or 0 
  int isPos = ((~x >> 31) & 1);
  //checking if x is equal to 0
  int isZero = ((~x + 1) >> 31) & 1;
  // if x is both 0 and pos (mainly checking if x  = 0 then 0)
  // and with isPos ensures that even if we have a negative result we get 0;
  return (isPos ^ isZero) & isPos;
}
/* 
 * isNegative - return 1 if x < 0, return 0 otherwise 
 *   Example: isNegative(-1) = 1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 6
 *   Rating: 2
 */
int isNegative(int x) {
  //getting the sign bit
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
  //2's complement: -x = ~x + 1
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
  //the only time there is overflow when subtracting is when: 
  // x and y have different signs 
  // and the result is not as expected 
  //this is what is expected when x and y are not the same: (r is result) 
  // |x|y|r|
  // |+|-|+|
  // |-|+|-| otherwise there is an overflow 
  int subtract = x + (~y + 1);
  int isNotSameSign = !!((x ^ y) >> 31);
  int isXNeg = (x >> 31); //checks if x is less than 0;
  int isSubtractNeg = (subtract >> 31) & 1;
  int ans = (isNotSameSign & isXNeg & isSubtractNeg) | (isNotSameSign & !isXNeg & !isSubtractNeg) | !isNotSameSign; 
  return ans; 
}
/* 
 * isLess - if x < y  then return 1, else return 0 
 *   Example: isLess(4,5) = 1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 24
 *   Rating: 3
 */
int isLess(int x, int y) {
  //we check if x and y have the same sign 
  int isNotSameSign = ((x ^ y) >> 31) & 1;
  //x - y
  int subtraction = y + (~x + 1);
  //checking if y is Negative
  int isYNeg = (y >> 31);
  //if they are not the same sign and y is Postive -> 1;
  int ans1 = ((isNotSameSign & !isYNeg) & !!x) ^ 0;
  //if they are the same sign & result is not 0 & sign of result is greater than or eq 0 
  int ans2 = (!isNotSameSign & !!subtraction & !(subtraction >> 31));
  //either first case or second case
  int final = (ans1 | ans2);
  return final;
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
  int multBy5 = (x << 2) + x;
  int isNeg = (multBy5 >> 31) & 1;
  int minus1 = ~0;
  //give -1 if Neg else give 0
  int giveMinus = ~(isNeg + minus1);
  //add 7 only when x is negative 
  int add7 = (giveMinus & 7) + multBy5;
  int divBy8 = (add7) >> 3;
    
  return divBy8;
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
  //Get the 8 bits exponent
  int exponent = (uf >> 23) & 0xff;
  int frac = uf & 0x7fffff;

  //Check for NAN  
  if ((exponent == 0xff) && (frac != 0)) {
    return uf; 
  }
  //Remove the sign bit 
  else {
    return (uf & 0x7FFFFFFF);
  }
  
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
  int sign = !!(uf & 0x80000000);
  int exponent = (uf >> 23) & 0xff; //8 bits only
  int frac = uf & 0x7fffff; //23 bits
  int actualExponent = exponent - 127; 
  //if NAN or infinity 
  if (exponent == 0xff)
    return 0x80000000u;
  //if exponent == -127 -> round to 0
  if (exponent == 0)
    return 0;
  //overflow will occur if 2^x > 2^30
  if (actualExponent > 30)
    return 0x80000000u;
  //here means that the value is between -0.5 and +0.5
  //we round to zero in this case
  if (actualExponent < -1)
    return 0;
  //normalizing the frac
  frac = frac | 0x800000;
  //if we have a value >= 2^23
  if (actualExponent > 22)
    frac = (frac << (actualExponent - 23));
  //if we have a value <= 2^23
  if (actualExponent < 24)
    frac = frac >> (23 - actualExponent);
  //notice that if actualExponent = 23 there will be no shifting
  //checking if we have a negative value 
  if (sign)
    return ~frac + 1;
  //returns our int if we have a positive number
  return frac;
}
