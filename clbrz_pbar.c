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

Created on: Mar 17, 2018
Author: clbrz (coolbreeze413@yahoo.co.in)

credits: http://patorjk.com/software/taag/#p=display&f=Bloody&t=progress%20bar
ref: https://stackoverflow.com/questions/14539867/how-to-display-a-progress-indicator-in-pure-c-c-cout-printf
ref: https://stackoverflow.com/questions/5977326/call-printf-using-va-list
===============================================================================
*/


#include "clbrz_pbar.h"

#include <stdio.h>
#include <stdarg.h>



#define CLBRZPBAR_PBWIDTH 					60
#define CLBRZPBAR_PBCHAR_DEFAULT			CLBRZ_PBARCHAR_VBAR
#define CLBRZPBAR_PRINTFMARKER_DEFAULT		""

uint8_t CLBRZPBAR_PBSTR[CLBRZPBAR_PBWIDTH] = {0};


static uint8_t clbrzpbar_visible = 0;
static uint8_t clbrzpbar_curr_progress = 0;
static uint8_t clbrzpbar_pbchar = CLBRZPBAR_PBCHAR_DEFAULT;
static char* clbrzpbar_printf_marker = CLBRZPBAR_PRINTFMARKER_DEFAULT;


void clbrzpbar_set_pbarchar(const uint8_t bar_char)
{
	clbrzpbar_pbchar = bar_char;
}


void clbrzpbar_init_pbar()
{
	int i = 0;
	for(i = 0; i < CLBRZPBAR_PBWIDTH; i++)
	{
		CLBRZPBAR_PBSTR[i] = clbrzpbar_pbchar;
	}
	clbrzpbar_curr_progress = 0;
	clbrzpbar_visible = 1;
}


void clbrzpbar_remove_pbar()
{
	printf("\r%-80s\r","");
	clbrzpbar_visible = 0;
}


void clbrzpbar_print_progress_abs (uint8_t abs_progress)
{
	if(!clbrzpbar_visible) return;

	clbrzpbar_curr_progress = abs_progress;
	if (clbrzpbar_curr_progress > 100) clbrzpbar_curr_progress = 100;

    int val = (int) (clbrzpbar_curr_progress);
    int lpad = (int) (((double)clbrzpbar_curr_progress/100) * CLBRZPBAR_PBWIDTH);
    int rpad = CLBRZPBAR_PBWIDTH - lpad;
    printf ("\r%3d%% [ %.*s%*s ]", val, lpad, CLBRZPBAR_PBSTR, rpad, "");
    fflush(stdout);
}


void clbrzpbar_print_progress_rel (int8_t rel_progress)
{
	clbrzpbar_print_progress_abs(clbrzpbar_curr_progress + rel_progress);
}


void clbrzpbar_set_printf_marker(char* printf_marker)
{
	clbrzpbar_printf_marker = printf_marker;
}


void clbrzpbar_printf(const char *fmt, ...)
{
	va_list arg;
	// create str, then call print_progress_rel with add_pc = 0.0

	// delete current line where the progress bar lives - '\r', %-80s with ""
	// again, go back to the beginning '\r'
	// put the message marker
	printf("\r%-80s\r%s","",clbrzpbar_printf_marker);

	// invoke printf for the fmt and varargs
	// prints after the message marker
	va_start(arg, fmt);
	vprintf(fmt, arg);
	va_end(arg);

	// put a blank line after the message
	printf("\n\n");

	// re-display the progress bar on the next line after the print with no changes
	clbrzpbar_print_progress_rel(0);
}


#ifdef CLBRZPBAR_ENABLE_TEST_FUNCTION
// a really bad function - but for testing purposes only.
static void clbrzpbar_util_sleep(int sleep_ms)
{
	// TODO: actual sleep to be implemented. dummy does for now.
	// portable sleep is a problem. posix sleep looks likely candidate (mingw or tdm gcc on windoze)
	{volatile int i = 10*sleep_ms;	while(i--){volatile int k = 50000;	while(k--);}}
}


void clbrzpbar_test()
{
	int count = 0;

	// 1
	clbrzpbar_set_pbarchar(CLBRZ_PBARCHAR_BLOCK);
	clbrzpbar_init_pbar();
	clbrzpbar_set_printf_marker(" >>> ");

	clbrzpbar_printf("normal pbar relative");
	for(count = 0; count <= 100; count++)
	{
		clbrzpbar_util_sleep(100);

		if(count == 100)		{clbrzpbar_printf("full");}
		if(count == 75)			{clbrzpbar_printf("threefourth");}
		if(count == 50)			{clbrzpbar_printf("half");}
		if(count == 25)			{clbrzpbar_printf("quarter");}
		if(count == 0)			{clbrzpbar_printf("zero");}
		//printf("normal...\n"); // causes UI problems...
		// use clbrzpbar_printf() if you are using a pbar.

		clbrzpbar_print_progress_rel(1);
	}

	clbrzpbar_printf("remove pbar");
	clbrzpbar_util_sleep(1000);
	clbrzpbar_remove_pbar();


	// 2
	clbrzpbar_set_pbarchar(CLBRZ_PBARCHAR_BLOCK);
	clbrzpbar_init_pbar();
	clbrzpbar_set_printf_marker(" <<< ");

	clbrzpbar_printf("reducing pbar relative");

	for(count = 100; count >= 0; count--)
	{
		clbrzpbar_util_sleep(100);

		if(count == 100)		{clbrzpbar_printf("full");}
		if(count == 75)			{clbrzpbar_printf("threefourth");}
		if(count == 50)			{clbrzpbar_printf("half");}
		if(count == 25)			{clbrzpbar_printf("quarter");}
		if(count == 0)			{clbrzpbar_printf("zero");}
		//printf("normal...\n"); // causes UI problems...
		// use clbrzpbar_printf() if you are using a pbar.

		clbrzpbar_print_progress_rel(-1);
	}

	clbrzpbar_printf("remove pbar");
	clbrzpbar_util_sleep(1000);
	clbrzpbar_remove_pbar();


	// 3
	clbrzpbar_set_pbarchar(CLBRZ_PBARCHAR_GREATERTHAN);
	clbrzpbar_init_pbar();
	clbrzpbar_set_printf_marker(" ABSOLUTE : ");

	clbrzpbar_printf("normal pbar absolute");

	for(count = 0; count <= 100; count++)
	{
		clbrzpbar_util_sleep(100);

		if(count == 100)		{clbrzpbar_printf("full");}
		if(count == 75)			{clbrzpbar_printf("threefourth");}
		if(count == 50)			{clbrzpbar_printf("half");}
		if(count == 25)			{clbrzpbar_printf("quarter");}
		if(count == 0)			{clbrzpbar_printf("zero");}
		//printf("normal...\n"); // causes UI problems...
		// use clbrzpbar_printf() if you are using a pbar.

		clbrzpbar_print_progress_abs(count);
	}

	clbrzpbar_printf("remove pbar");
	clbrzpbar_util_sleep(1000);
	clbrzpbar_remove_pbar();


	// 4
	clbrzpbar_set_pbarchar(CLBRZ_PBARCHAR_LESSERTHAN);
	clbrzpbar_init_pbar();
	clbrzpbar_set_printf_marker("");

	clbrzpbar_printf("reducing pbar absolute");

	for(count = 100; count >= 0; count--)
	{
		clbrzpbar_util_sleep(100);

		if(count == 100)		{clbrzpbar_printf("full");}
		if(count == 75)			{clbrzpbar_printf("threefourth");}
		if(count == 50)			{clbrzpbar_printf("half");}
		if(count == 25)			{clbrzpbar_printf("quarter");}
		if(count == 0)			{clbrzpbar_printf("zero");}
		//printf("normal...\n"); // causes UI problems...
		// use clbrzpbar_printf() if you are using a pbar.

		clbrzpbar_print_progress_abs(count);
	}

	clbrzpbar_printf("remove pbar");
	clbrzpbar_util_sleep(1000);
	clbrzpbar_remove_pbar();
}


int main()
{
	clbrzpbar_test();

	return 0;
}
#endif // #ifdef CLBRZPBAR_ENABLE_TEST_FUNCTION
