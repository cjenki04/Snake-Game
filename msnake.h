#include<iostream>


//msnake.h: contains constants and place_snake definition
// ---------------------------------------
// ----- CONSTANTS  ----------------------
// ---------------------------------------
const int 	ROWS    = 24;		// changed to 24 to include border
const int 	COLS    = 63;		// changed to 63 to include border
const int	EU_INIT = 60;
const char	BUG_SYM = 'X';
const int	BUG_VAL = 25;
const char	EGG_SYM = 'O';
const int	EGG_VAL = 15;
const char	UP = '^' ;
const char	DOWN = 'v';
const char	RIGHT = '>';
const char	LEFT = '<';

//main definitions 

void	place_snack(char, char[ROWS][COLS]);


