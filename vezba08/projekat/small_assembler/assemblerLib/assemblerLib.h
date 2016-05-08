#ifndef __ASSEMBLERLIB_H__
#define __ASSEMBLERLIB_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string>
#include <map>
#include <list>
#include <stack>
#include "writeElf.h"

#define D_COMMENT       "#;"
#define D_LABEL         ":"
#define D_WHITESPACE    " \t\r\n"
#define D_DIRECTIVE     '.'
#define D_OPSEP         "\t ,"
#define D_DIRECTIVE_SEP "\t ,"
#define D_COMMAND_SEP   " \t\r\n"
#define D_PSEUDO_SEP    '\n'

/**
 * @brief TEXT area section start address
 */
#define SECTION_TEXT_AREA 0x0
/**
 * @brief DATA area section start address
 */
#define SECTION_DATA_AREA 0x0

/**
 * @brief DATA area indentificator
 */
#define SECTION_DATA "data"
/**
 * @brief TEXT area indentificator
 */
#define SECTION_TEXT "text"

/**
 * @enum SECTION
 * 
 * @brief available sections type
 */
typedef enum SECTION {
    S_DATA,
    S_TEXT,
    S_NONE
} SECTION_T;

/**
 * @enum OPTYPE
 * 
 * @brief operation codes type
 */
typedef enum DIRECTIVE {
    D_NONE,
    D_EXTERN,
    D_GLOBL,
    D_ORG,
    D_SPACE,
    D_WORD
} DIRECTIVE_T;

/**
 * @enum OPTYPE
 * 
 * @brief operation codes type
 */
typedef enum OPTYPE {
    MACHINE,
    PSEUDO,
    MACRO,
    NONE
} OPTYPE_T;

/**
 * @enum IFORMAT
 *
 * @brief instruction formats type
 */
typedef enum IFORMAT {
    R,
    I,
    J,
    B,
    BZ,
    JR,
    LUI,
    MD,
    MF,
    N,
    S,
    SC,
    SV,
    I_NONE
} IFORMAT_T;

/**
 * @struct OPCODE
 *
 * @brief structure for operation code table element
 */
struct OPCODE {
    char*     symbol;   /**< operation code symbol in source code */
    OPTYPE_T  optype;   /**< operation type @see OPTYPE           */
    IFORMAT_T iformat;  /**< operation format @see IFORMAT        */
    char      code;     /**< operation code                       */
    char      funct;    /**< operation function                   */
    char      paramNum; /**< number of parameters required        */
    
    /**
     * OPCODE constructor
     * initialize each element of the structure
     */
    OPCODE (char* sSymbol, OPTYPE_T oOptype, IFORMAT_T iIformat, char cCode, char fFunct, char pParamNum) {
        symbol   = sSymbol;
        optype   = oOptype;
        iformat  = iIformat;
        code     = cCode;
        funct    = fFunct;
        paramNum = pParamNum;
    };
};

/**
 * @struct REL_INFO
 *
 * @brief Relocation info
 */
struct REL_INFO {
    long byteUsed;  /**< bytes in text segment where the symbol is used */
    char relType;   /**< relocation type                                */

    /**
     * REL_INFO constructor
     * initialize each element of the structure
     */
    REL_INFO (long bByteUsed, char rRelType) {
        byteUsed = bByteUsed;
        relType  = rRelType;
    }
};

/**
 * @struct SYMBOL
 *
 * @brief structure for symbol table element
 */
struct SYMBOL {
    long      value;      /**< symbol's value                   */
    SECTION_T section;    /**< section where the symbol belongs */
    std::list<REL_INFO>* relList;   /**< relocation info list                           */

    /**
     * SYMBOL constructor
     * initialize each element of the structure
     */
    SYMBOL (long vValue, SECTION_T sSection) {
        value   = vValue;
        section = sSection;
        relList = new std::list<REL_INFO>;
    }
};

/**
 * @struct EXTERN_SYMBOL
 *
 * @brief structure for extern symbol table element
 */
struct EXTERN_SYMBOL {
    long            value;      /**< symbol's value                                 */
    std::list<REL_INFO>* relList;   /**< relocation info list                           */

    /**
     * EXTERN_SYMBOL constructor
     * initialize each element of the structure
     */
    EXTERN_SYMBOL (long vValue) {
        value = vValue;
        relList = new std::list<REL_INFO>;
    }
};

/**
 * @struct LITERAL
 *
 * @brief structure for literals' table element
 */
struct LITERAL {
    long            value;      /**< literal's value                                */

    /**
     * LITERAL constructor
     * initialize each element of the structure
     */
    LITERAL (long vValue) {
        value = vValue;
    }
};

/**
 * @struct SOURCE_LINE
 *
 * @brief structure for source list element (source line and source line number)
 */
struct SOURCE_LINE {
    long  lineNumber;
	std::string sourceLine;

	SOURCE_LINE (std::string sSourceLine, long lLineNumber) {
        sourceLine = sSourceLine;
        lineNumber = lLineNumber;
    }
};

/**
 * @struct cmp_str
 *
 * @brief compare functor for map with string key
 *
 */
struct cmp_str;

/**
 * registers map type
 */
typedef std::map<std::string, std::string> REGISTERS;
/**
 * registers pair
 */
typedef std::pair<std::string, std::string> registers_Pair;

/**
 * map type for operation codes table
 */
typedef std::map<std::string, OPCODE> TABLE_OPCODE;
/**
 * operation codes table pair
 */
typedef std::pair<std::string, OPCODE> tableOpCode_Pair;

/**
 * error list type
 */
typedef std::list<char*> ERROR_LIST;

/**
 * param stack type
 */
typedef std::stack<std::string> PARAM_STACK;

/**
 * source list type
 */
typedef std::list<SOURCE_LINE> SOURCE_LIST;

/**
 * line numbers list type
 */
typedef std::list<long> LINE_NUMBERS;

/**
 * table of symbols map type
 */
typedef std::map<std::string, SYMBOL> TABLE_SYMBOL;
/**
 * table of symbols pair
 */
typedef std::pair<std::string, SYMBOL> symbol_Pair;

/**
 * table of extern symbols map type
 */
typedef std::map<std::string, EXTERN_SYMBOL> TABLE_EXTERN_SYMBOL;
/**
 * table of extern symbols pair
 */
typedef std::pair<std::string, EXTERN_SYMBOL> externSymbol_Pair;

/**
 * table of literals map type
 */
typedef std::map<long, LITERAL> TABLE_LITERAL;
/**
 * table of literals pair
 */
typedef std::pair<long, LITERAL> tableLiteral_Pair;

/**
 * generated operation codes list type
 */
typedef std::list<long> MACHINE_CODE_LIST;

/**
 * addresses (locations) of instructions list type
 */
typedef std::list<long> INST_LOCATION_LIST;

/**
 * instructions list type
 */
typedef std::list<char*> INSTRUCTION_LIST;

/**
 * @brief Trims trailing characters from a string.
 *
 * @param[in]  string          string to be trimmed
 * @param[in]  tc              character to be trimmed from string
 *
 * @return pointer to the first character in the string to be trimmed
 */
char*         strrspn(const char* string, const char* tc);

/**
 * @brief Replaces given string (find) in string (source) with new string (replace).
 *
 * @param[out] dest       destination for processed string
 * @param[in] source     string being processed
 * @param[in] find       string to replace
 * @param[in] replace    string to replace with
 * @param[in] replaceAll true  - replace all occurences of find
 *                   false - replace only first occ. of find
 *		
 * @return true if replace successful (stringFind found and replaced);
 *         false otherwise
 */
bool          replaceString(char* &dest, const char* source, const char* find, const char* replace, bool replaceAll);

/**
 * @brief Returns integer value of int or hex string
 * 
 * @param[in] string    string to convert
 * @param[out] isNum     true if string is hex or dec number; false otherwise
 * 
 * @return converted value
 */
long          toint(const char* string, bool &isNum);

/**
 * @brief Returns integer value of int or hex string
 * 
 * @param[in] string    string to convert
 * 
 * @return converted value
 */
long          toint(const char* string);

/**
 * @brief   Converts constant from int or hex string to integer value
 *
 * @param[in]   constant string that should be converted to value
 * @param[out]   isNum    true if string is hex or dec number; false otherwise
 *
 * @return  converted value of constant
 */
long          constConv(std::string constant, bool &isNum);

/**
 * @brief   Converts constant from int or hex string to integer value
 *
 * @param[in]   constant string that should be converted to value
 *
 * @return  converted value of constant
 */
long          constConv(std::string constant);

/**
 * @brief Gets executable part of the line
 *
 * @param[out]   executable     will hold executable part of the line, if exacutable is found
 * @param[in]   line           the current line to examine
 * @param[in]   lineNumber     the current line number
 * @param[in]   addErrorToList if true - check if symbolic instruction
 *                         exists in operation codes table and adds
 *                         error if it doesn't exist
 *                         (case of unrecognized instruction)
 *
 * @return  true if an executable line;
 *          false if not an executable line
 */
bool          getExecutable(std::string &executable, std::string line, long lineNumber, bool addErrorToList=false);

/**
 * @brief   Returns the part of passed line that represents the command
 *
 * @param[out]   cmd   pointer to pointer to buffer with returned command if found
 * @param[in]   line  the current line to examine
 *		
 * @return  true if command found; false otherwise
 *
 */
bool          getCommand(std::string &cmd, std::string line);

/**
 * @brief   Returns found directive;
 *          Adds an error to error list if directive is found, but not recognized
 *
 * @param[in]   line        the current line to examine
 * @param[in]   lineNumber  the current line number
 *		
 * @return  D_NONE      - when no directive is found
 *          D_EXTERN    - when .extern is found
 *          D_GLOBL     - when .globl is found
 *          D_ORG       - when .org is found
 *          D_SPACE     - when .space is found
 *          D_WORD      - when .word is found
 */
DIRECTIVE_T   getDirective(std::string line, long lineNumber);

/**
 * @brief   Returns the part of current line that represents symbol, if found
 *
 * @param[out]   symbol  will contain the symbol if one is found in the line
 * @param[in]   line    the current line to examine
 *		
 * @return  true if symbol found; false otherwise
 */
bool          getSymbol(std::string &symbol, std::string line);

/**
 * @brief   Extracts all parameters from current line (after command).
 *
 * @param[out]   params      PARAM_STACK valiable that will hold parameters if they are found
 * @param[in]   line        the current line to examine
 * @param[in]   lineNumber  the number of current line
 * @param[in]   chopDollar  set if you want to chop dollar sign; default value is false
 * @param[in]   unWind      set if you want to unwind parameters; default value is false
 * @param[in]   location    current instruction's location; default value is 0
 *		
 * @return  true if param found; false otherwise
 */
bool          getParams(PARAM_STACK &params, std::string line, long lineNumber, bool chopDollar=false, bool unWind=false, long location=0);

/**
 * @brief   Calculates the value of passed expression
 *
 * @param   expr        expression to calculate
 * @param[in]   lineNumber  current line number
 * @param[in]   line        current line
 * @param[in]   location    current instruction's location
 */
void          exprCalc(char* &expr, long lineNumber, const char* line, long location=0);

/**
 * @brief   Converts an assembler instruction to machine code.
 *
 * @param[in]   line        the current line to examine
 * @param[in]   lineNumber  the current line number
 * @param[in]   location    the current program location
 *
 * @return 32-bit machine code
 */
unsigned long makeMachineCode(const char* line, long lineNumber, long location);

/**
 * @brief Initialises all diynamic members of lib (lists, maps...)
 *
 * @param[in]   machineInstructions     array of machine instructions
 * @param[in]   machineInstructionsNo   number of machine instructions in given set
 * @param[in]   pseudoInstructions      array of pseudo instructions              
 * @param[in]   pseudoInstructionsNo    number of pseudo instructions in given set
 *		
 * @return  True if initialization of all tables was successfull
 *          False otherwise
 */
void          init(const tableOpCode_Pair* machineInstructions, unsigned machineInstructionsNo, const tableOpCode_Pair* pseudoInstructions, unsigned pseudoInstructionsNo);

/**
 * @brief   Cleans all dynamic elements
 */
void          clean();

/**
 * @brief   Gets instruction (full machineCode) from instruction symbol
 *
 * @param[in]   instrSymbol symbol of instruction to find
 * @param[out]   getInstr    opcode of instruction if found
 *		
 * @return  code of intruction; NONE if instruction not found
 */
OPTYPE_T      getInstr(const char* instrSymbol, const OPCODE* &getInstr);

/**
 * @brief   Adds instruction to operation code table
 *
 * @param[in]   instrSymbol operation code symbol in source code
 * @param[in]   optype      operation type @see OPTYPE          
 * @param[in]   iFormat     operation format @see IFORMAT       
 * @param[in]   code        operation code                      
 * @param[in]   funct       operation function                  
 * @param[in]   paramNum    number of parameters required       
 *		
 * @return  true if successful; false otherwise (case the instruction already exists)
 */
bool          pushInstr(const char* instrSymbol, OPTYPE_T optype, IFORMAT_T iFormat, char code, char funct, char paramNum);

/**
 * @brief   Adds source line to source list
 *
 * @param[in]   sourceLine source line to add
 * @param[in]   lineNumber line number of source line to add
 */
void          sourceListPushBack(const char* sourceLine, long lineNumber);

/**
 * @brief   Gets pointer to the list with source lines
 *
 * @return  pointer to sourceList (global variable)
 */
SOURCE_LIST*  getSourceList();

/**
 * @brief   Adds operation code to list
 *
 * @param[in]   machineCode operation code to add
 */
void          pushMachineCode(long machineCode);

/**
 * @brief   Adds instruction location to list
 *
 * @param[in]   instLocation location to add
 */
void          pushInstLocation(long instLocation);

/**
 * @brief   Reads operation code from list
 *
 * @return  operation code
 */
long          readMachineCode();

/**
 * @brief   Gets size of operation code list
 *
 * @return  size of machineCodeList
 */
long          sizeMachineCode();

/**
 * @brief   Adds instruction to instruction list
 *
 * @param[in]   instruction instruction to add
 */
void          pushInstruciton(const char* instruction);

/**
 * @brief   Reads instruction from instruction list and pop
 *
 * @param[out]   instruction instruction to add
 *
 * @return  true if successful (instruction list not empty);
 *          false otherwise
 */
bool          readInstruction(char* &instruction);

/**
 * @brief   Gets size of instruction list
 *
 * @return  size of instructionList
 */
long          sizeInstruction();

/**
 * @brief   add line number to the end of line numbers list
 *
 * @param[in]   lineNumber  line number to add
 */
void          lineNumbersPushBack(long lineNumber);

/**
 * @brief   Pops line number from line numbers list (read and delete)
 *
 * @return  line number
 */
long          lineNumbersPopFront();

/**
 * @brief   Adds a symbol to symbols list
 *
 * @param[in]   symbol      symbol to add (used as key)
 * @param[in]   location    symbol's location
 * @param[in]   section     section in witch the symbol is defined
 */
void          pushSymbol(std::string symbol, long location, SECTION_T section);

/**
 * @brief   Reads symbol and its postion from symbols list
 *
 * @param[in]   symbol  symbol to read, used as key
 * @param[out]   val     location for storing and passing symbol
 *
 * @return  true if symbol found; false otherwise
 */
bool          readSymbol(std::string symbol, long &val);

/**
 * @brief   Verifies if symbol already exists in symbols list
 *
 * @param[in]   symbol  symbol to verifie, used as key
 *
 * @return  true if symbol found; false otherwise
 */
bool          symbolExists(std::string symbol);

/**
 * @brief   Adds a symbol to global symbols list
 *
 * @param[in]   symbol      symbol to add (used as key)
 * @param[in]   location    symbol's location
 */
void          pushGlobalSymbol(std::string symbol, long location);

/**
 * @brief   Updates symbol's location in global symbols list
 *
 * @param[in]   symbol      symbol to update (used as key)
 * @param[in]   location    new symbol's location
 */
void          updateGlobalSymbol(std::string symbol, long location);

/**
 * @brief   Reads symbol and its postion from global symbols list
 *
 * @param[in]   symbol  symbol to read, used as key
 * @param[out]   val     pointer to location for storing and passing symbol
 *
 * @return  true if symbol found; false otherwise
 */
bool          readGlobalSymbol(std::string symbol, long &val);

/**
 * @brief   Verifies if symbol already exists in global symbols list
 *
 * @param[in]   symbol  symbol to verifie, used as key
 *
 * @returns true if symbol found; false otherwise
 */
bool          globalSymbolExists(std::string symbol);

/**
 * @brief   Adds a symbol to extern symbols list
 *
 * @param[in]   symbol      symbol to add (used as key)
 * @param[in]   location    symbol's location
 */
void          pushExternSymbol(std::string symbol, long location);

/**
 * @brief   Reads symbol and its postion from extern symbols list
 *
 * @param[in]   symbol  symbol to read, used as key
 * @param[out]   val     pointer to location for storing and passing symbol
 *
 * @return  true if symbol found; false otherwise
 */
bool          readExternSymbol(std::string symbol, long &val);

/**
 * @brief   Verifies if symbol already exists in extern symbols list
 *
 * @param[in]   symbol  symbol to verifie, used as key
 *
 * @return  true if symbol found; false otherwise
 */
bool          externSymbolExists(std::string symbol);

/**
 * @brief   Adds a value to location in const data list
 *
 * @param[in]   location    data location (used as a key)
 * @param[in]   value       data value
 */
void          pushLiteral(long location, long value);

/**
 * @brief   Reads a value from location in table of literals
 *
 * @param   location    data location (used as a key)
 * @param   value       read data value
 *
 * @return  true if successfull (data found); false otherwise
 */
void          readLiteral(long &location, long &value);

/**
 * @brief   Gets the size of table of literals
 *
 * @return  The size (number of elements) of table of literals
 */
long          sizeTableLiteral();

/**
 * @brief   Adds error to error list if actual number of parameters differs from
 *          expected.
 *
 * @param[in]   lineNumber  current line number
 * @param[in]   line        current line
 * @param[in]   params      pointer to parameters list
 * @param[in]   nExpected   expected number of parameters
 *
 * @return  true if right number; false otherwise
 */
bool          checkEnoughParams(long lineNumber, std::string line, PARAM_STACK params, int nExpected);

/**
 * @brief   Adds errors to errors list
 *
 * @param[in]   lineNumber  current line number
 * @param[in]   line        current line
 * @param[in]   errorText   error text
 */
void          addError(long lineNumber, std::string line, std::string errorText);

/**
 * @brief   If errors were found, print them and exit.
 *
 * @return  true if errors found; false otherwise
 */
bool          errorsFound();

/**
 * @brief   Writes binary data to binary file if defined
 *          Writes text data to textual file if defined, to stream output otherwise
 *
 * @param[in]   outFileNameBin  binary file name
 * @param[in]   outFileNameTxt  textual file name
 */
void          writeDataToFile(std::string outFileNameBin, std::string outFileNameTxt);

/**
 * @brief   Reports an error if output file could not be opened for writing
 *
 * @param[in]   filename  file name that couldn't be opened
 */
void outFileOpenError(std::string filename);

/**
 * @brief   Reports an error if input file could not be opened for reading
 *
 * @param[in]   filename  file name that couldn't be opened
 */
void inFileOpenError(std::string filename);

/**
 * @brief   Writes machine code and all data in relocatable ELF object file
 *
 * @param[in]   outFileName  file name of destination ELF file
 *
 * @return ???
 */
int writeElf(std::string outFileName);

/**
 * @brief   Updates current section and location
 *
 * @param[in]   sectionID   new section identificator (string)
 *                          valid identificators - S (extracted from ".org S" directive):
 *                              text
 *                              data
 * @param[out]   section     identificator of the previously active section
 * @param[out]   location    counter of memory locations for the new section
 *
 * @return  true  - if section identificator is recognized
 *          false - otherwise
 */
bool changeSectionAndLocation(std::string sectionID, SECTION_T &section, long &location);

#endif  // __ASSEMBLERLIB_H__
