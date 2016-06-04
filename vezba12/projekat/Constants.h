#ifndef __CONSTANTS__
#define __CONSTANTS__

/**
 * Use this when instruction is move with no interference to other instruction. 
 * int 0x32 = char 2
 */
#define __MOVE_NO_INTERFERENCE__        0x32
/**
 * Use this when instruction interference to other instruction. 
 * int 0x31 = char 1
 */
#define __INTERFERENCE__                '1'
/**
 * Use this when instruction is no interference to other instruction. 
 * int 0x30 = char 0
 */
#define __EMPTY__                       '0'

/** 
 * Undefine value
 */
#define __UNDEFINE__                    -1

/**
 * Number of regs in processor.
 */
#define __REG_NUMBER__                  3

/**
 * Debug mode
 */
#define __DEBUG__                       1

#endif
