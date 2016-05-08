#ifndef __WINELF_H__
#define __WINELF_H__

#include <stdarg.h>
#include <io.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <wtypes.h>
#include <fcntl.h>
#include <libelf.h> 
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <sysexits.h>
#include <vis.h>
#include <sys\elf_common.h>

// Definition of the default string table section ".shstrtab"

	const char defaultStrTable[] = 
	{
		/* offset 00 */ '\0',  // The NULL section
		/* offset 01 */ '.', 's', 'h', 's', 't', 'r', 't', 'a', 'b', '\0',
		/* offset 11 */ '.', 's', 't', 'r', 't', 'a', 'b', '\0',
		/* offset 19 */ '.', 's', 'y', 'm', 't', 'a', 'b', '\0',
		/* offset 27 */ '.', 't', 'e', 'x', 't', '\0',
		/* offset 33 */ '.', 'b', 's', 's', '\0',
		/* offset 38 */ '.', 'd', 'a', 't', 'a', '\0',
		/* offset 44 */ '.', 'r', 'e', 'l', '.', 't', 'e', 'x', 't', '\0',
		/* offset 54 */ '.', 'c', 'o', 'm', 'm', 'e', 'n', 't', '\0'
	};

	const char defaultStrTableLen = sizeof(defaultStrTable); // Length of the "defaultStrTable" string
	const int iSectionsNumber = 9;  // The number of sections in the ELF object file

// End of "Definition of the default string table section"

// Sections offset
	const char _shstrtab_offset = 1;
	const char _strtab_offset = 11;
	const char _symtab_offset = 19;
	const char _text_offset = 27;
	const char _bss_offset = 33;
	const char _data_offset = 38;
	const char _rel_text_offset = 44;

// Index of sections within the object file
	const char _shstrtab = 1;
	const char _strtab = 2;
	const char _symtab = 3;
	const char _text = 4;
	const char _data = 5;

//----------------------------------------------------------------------------


#endif /*__WINWLF_H__*/
