/*
===============================================================================

 ██▓███   ██▀███   ▒█████    ▄████  ██▀███  ▓█████   ██████   ██████     ▄▄▄▄    ▄▄▄       ██▀███
▓██░  ██▒▓██ ▒ ██▒▒██▒  ██▒ ██▒ ▀█▒▓██ ▒ ██▒▓█   ▀ ▒██    ▒ ▒██    ▒    ▓█████▄ ▒████▄    ▓██ ▒ ██▒
▓██░ ██▓▒▓██ ░▄█ ▒▒██░  ██▒▒██░▄▄▄░▓██ ░▄█ ▒▒███   ░ ▓██▄   ░ ▓██▄      ▒██▒ ▄██▒██  ▀█▄  ▓██ ░▄█ ▒
▒██▄█▓▒ ▒▒██▀▀█▄  ▒██   ██░░▓█  ██▓▒██▀▀█▄  ▒▓█  ▄   ▒   ██▒  ▒   ██▒   ▒██░█▀  ░██▄▄▄▄██ ▒██▀▀█▄
▒██▒ ░  ░░██▓ ▒██▒░ ████▓▒░░▒▓███▀▒░██▓ ▒██▒░▒████▒▒██████▒▒▒██████▒▒   ░▓█  ▀█▓ ▓█   ▓██▒░██▓ ▒██▒
▒▓▒░ ░  ░░ ▒▓ ░▒▓░░ ▒░▒░▒░  ░▒   ▒ ░ ▒▓ ░▒▓░░░ ▒░ ░▒ ▒▓▒ ▒ ░▒ ▒▓▒ ▒ ░   ░▒▓███▀▒ ▒▒   ▓▒█░░ ▒▓ ░▒▓░
░▒ ░       ░▒ ░ ▒░  ░ ▒ ▒░   ░   ░   ░▒ ░ ▒░ ░ ░  ░░ ░▒  ░ ░░ ░▒  ░ ░   ▒░▒   ░   ▒   ▒▒ ░  ░▒ ░ ▒░
░░         ░░   ░ ░ ░ ░ ▒  ░ ░   ░   ░░   ░    ░   ░  ░  ░  ░  ░  ░      ░    ░   ░   ▒     ░░   ░
            ░         ░ ░        ░    ░        ░  ░      ░        ░      ░            ░  ░   ░
                                                                              ░

Created on		: Mar 17, 2018
Author			: clbrz (coolbreeze413@yahoo.co.in)
Version     	: v1.0

This is free and unencumbered software released into the public domain.

Anyone is free to copy, modify, publish, use, compile, sell, or
distribute this software, either in source code form or as a compiled
binary, for any purpose, commercial or non-commercial, and by any
means.

In jurisdictions that recognize copyright laws, the author or authors
of this software dedicate any and all copyright interest in the
software to the public domain. We make this dedication for the benefit
of the public at large and to the detriment of our heirs and
successors. We intend this dedication to be an overt act of
relinquishment in perpetuity of all present and future rights to this
software under copyright law.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
IN NO EVENT SHALL THE AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR
OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
OTHER DEALINGS IN THE SOFTWARE.

For more information, please refer to <http://unlicense.org/>


credits
	http://patorjk.com/software/taag/#p=display&f=Bloody&t=progress%20bar

references
	https://stackoverflow.com/questions/14539867/how-to-display-a-progress-indicator-in-pure-c-c-cout-printf
	https://stackoverflow.com/questions/5977326/call-printf-using-va-list
===============================================================================
*/


#ifndef CLBRZ_PBAR_H_
#define CLBRZ_PBAR_H_

#ifdef __cplusplus
extern "C" {
#endif // #ifdef __cplusplus


#include <stdint.h>


// remove this define when using as a "library" - demo purpose code only.
#define CLBRZPBAR_ENABLE_TEST_FUNCTION


// some useful drawing characters for styling the pbar
#define CLBRZ_PBARCHAR_BLOCK					219		// █

#define CLBRZ_PBARCHAR_BLOCK_TOPHALF			223		// ▀

#define CLBRZ_PBARCHAR_BLOCK_BOTTOMHALF			220		// ▄

#define CLBRZ_PBARCHAR_BLOCK_HIDENSITY			178		// ▓

#define CLBRZ_PBARCHAR_BLOCK_MEDDENSITY			177		// ▒

#define CLBRZ_PBARCHAR_BLOCK_LOWDENSITY			176		// ░

#define CLBRZ_PBARCHAR_ANGLEQUOTES_RIGHT		175		// »

#define CLBRZ_PBARCHAR_ANGLEQUOTES_LEFT			174		// «

#define CLBRZ_PBARCHAR_GREATERTHAN				62		// >

#define CLBRZ_PBARCHAR_LESSERTHAN				60		// <

#define CLBRZ_PBARCHAR_EQUALS					61		// =

#define CLBRZ_PBARCHAR_VBAR						124		// |


void clbrzpbar_set_pbarchar(const uint8_t bar_char);
void clbrzpbar_set_printf_marker(char* printf_marker);

void clbrzpbar_init_pbar();
void clbrzpbar_remove_pbar();

void clbrzpbar_print_progress_abs (uint8_t abs_progress); 	// 0 - 100
void clbrzpbar_print_progress_rel (int8_t rel_progress); 	// 0 - 100, can be negative
void clbrzpbar_printf(const char *fmt, ...);				// printf wrapper that plays catch with pbar

#ifdef CLBRZPBAR_ENABLE_TEST_FUNCTION
void clbrzpbar_test();
#endif // #ifdef CLBRZPBAR_ENABLE_TEST_FUNCTION


#ifdef __cplusplus
}
#endif // #ifdef __cplusplus

#endif /* CLBRZ_PBAR_H_ */
