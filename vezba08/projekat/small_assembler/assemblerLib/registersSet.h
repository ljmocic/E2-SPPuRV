#ifndef __REGISTERS_SET_H__
#define __REGISTERS_SET_H__

/**
 * The number of defined registers aliases.
 */
#define REGISTERS_NO 32

/**
 * The array of defined registers aliases.
 */
registers_Pair REGISTERS_SET[REGISTERS_NO] = {
    //               alias    name
    registers_Pair( "$zero" , "$0"  ),
    registers_Pair( "$at"   , "$1"  ),
    registers_Pair( "$v0"   , "$2"  ),
    registers_Pair( "$v1"   , "$3"  ),
    registers_Pair( "$a0"   , "$4"  ),
    registers_Pair( "$a1"   , "$5"  ),
    registers_Pair( "$a2"   , "$6"  ),
    registers_Pair( "$a3"   , "$7"  ),
    registers_Pair( "$t0"   , "$8"  ),
    registers_Pair( "$t1"   , "$9"  ),
    registers_Pair( "$t2"   , "$10" ),
    registers_Pair( "$t3"   , "$11" ),
    registers_Pair( "$t4"   , "$12" ),
    registers_Pair( "$t5"   , "$13" ),
    registers_Pair( "$t6"   , "$14" ),
    registers_Pair( "$t7"   , "$15" ),
    registers_Pair( "$s0"   , "$16" ),
    registers_Pair( "$s1"   , "$17" ),
    registers_Pair( "$s2"   , "$18" ),
    registers_Pair( "$s3"   , "$19" ),
    registers_Pair( "$s4"   , "$20" ),
    registers_Pair( "$s5"   , "$21" ),
    registers_Pair( "$s6"   , "$22" ),
    registers_Pair( "$s7"   , "$23" ),
    registers_Pair( "$t8"   , "$24" ),
    registers_Pair( "$t9"   , "$25" ),
    registers_Pair( "$k0"   , "$26" ),
    registers_Pair( "$k1"   , "$27" ),
    registers_Pair( "$gp"   , "$28" ),
    registers_Pair( "$sp"   , "$29" ),
    registers_Pair( "$fp"   , "$30" ),
    registers_Pair( "$ra"   , "$31" )
};

#endif  // __REGISTERS_SET_H__