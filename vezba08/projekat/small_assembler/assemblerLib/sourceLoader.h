#ifndef __SOURCE_LOADER_H__
#define __SOURCE_LOADER_H__

#include <string>

/**
 * @brief   Loads source code and replaces pseudo instructions
 * 
 *          Loads source line to source list beside line numbers.
 *          Replaces psuedo instructions and register aliases.
 *
 * @param   input_file  input file with assembler source code
 *
 * @return  false if errors found; true otherwise
 */
bool loadSourceRepPseudo(std::string input_file);

#endif  // __SOURCE_LOADER_H__