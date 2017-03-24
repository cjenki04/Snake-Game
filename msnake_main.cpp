#include <iostream>
using namespace std;
#include "termfuncs.h"
#include "snake.h"
 

/*
 * msnake version 1.0
 *  	By : Conor Jenkinson
 * Phase 1 : October 29, 2015	
 * Phase 2 : November 5, 2015
 * Descrip : This game builds on the snake game by adding another snake that
 *	     can be controlled by another player. Instead of structs, this  
 *	     program implements the use of classes for each snake. Controls,
 *	     name, and body of the snake are all decided by the player.
 *	     Game is played until one player dies by either running into 
 *	     its own tail or running out of energy units. In order to win a
 *	     player must both be alive at the end of the game and have more
 *	     points than their opponent. Each move earns one point but 
 *	     but subtracts one energy unit.   
 *  	     Game is played on a board 22 by 61, the egg snack "0" is worth
 *           15 energy_units while the bug snakc "X" is worth 25. 
 *     
 */


// ---------------------------------------
// ----- msnake_main.cpp: MAIN  ----------
// ---------------------------------------
// includes main method and helpers

string	play_game(char[ROWS][COLS]);
void	display(char [ROWS][COLS], Snake, Snake);
string	compute_outcome(Snake, Snake);
void 	report(std::string result);
void	draw_board(char board[][COLS]);
void 	setup_board(char board[][COLS]);
void 	initialize_board(char board[][COLS]);
//    ---- note: DO NOT MODIFY main() AT ALL ----
//main-runs game on 2d array of chars, implements setup_board, play_game,
//and report
//args: none
//rets: void
int main()
{
	char	board[ROWS][COLS];
	string	result;

	setup_board(board);
	result = play_game(board);
	report(result);
}
//setup_board-gets the board ready to play on-initializes, creates border,
//clears screen, and prints the board
//args:2d array of chars
//rets:void
void setup_board(char board[][COLS]){
	initialize_board(board);
	screen_clear();
	char bline = '|' ;
	char bplus = '+' ;
	char bminus = '-';
	for (int i = 1 ; i < (ROWS-1) ; i ++){
		for (int j = 1 ; j < (COLS-1) ; j++ ){
			board[0][j] = bminus;         // creates top  border
			board[i][0] = bline;	      // creates left border
			board[(ROWS-1)][j] = bminus;  // creates bottom bord
			board[i][COLS-1] = bline;     // creates right border
		}
	}
	board[0][0] = bplus;		       // puts "+" in every corner
	board[0][(COLS-1)] = bplus;
	board[(ROWS-1)][0] = bplus;
	board[(ROWS-1)][(COLS-1)] = bplus;
	draw_board(board);
}
//
// play_game -- run a game of multi-snake
//    args: a board ready to use
//    rets: "X wins" or "X died" where X is name of snake
//    note: USE THIS MAIN UNCHANGED FOR PHASE 0
//    note: FOR PHASE 1, move setup_snake into class 
//
string play_game(char b[ROWS][COLS])
{
	Snake	s0, s1;		// the players
	char	input;
	string	outcome = "";

	// set up the snakes and put food on board
	screen_clear();
	s0.setup_snake(0, ROWS/2-1, COLS/2, '^', EU_INIT);
	s1.setup_snake(1, ROWS/2  , COLS/2, 'v', EU_INIT);
	s0.draw_head_on_board(b);
	s1.draw_head_on_board(b);
	place_snack(BUG_SYM, b);
	place_snack(EGG_SYM, b);

	// play the game
	while( s0.is_alive() && s1.is_alive() )
	{
		display(b, s0, s1);
		input = getachar();
		s0.process_key(input, b);
		s1.process_key(input, b);
	}
	display(b, s0,s1);

	outcome = compute_outcome(s0, s1);
	return outcome;
}

// compute_outcome -- determine if someone one
//  args: two snakes
//  rets: "X wins" OR  "X died"
//  note: to win, a snake must be alive AND have a higher score
//
string compute_outcome(Snake a, Snake b)
{
	if ((a.is_alive()) and (a.get_score() > b.get_score())){
			return a.get_name() + " wins.";
		}
	else if (( b.is_alive()) and (b.get_score() > a.get_score())){
		return b.get_name() + " wins.";
	        }
   else if ( b.is_alive() != true) {
			return b.get_name()+ " died."; 
   		}
   else if ( a.is_alive() != true) {
			return a.get_name()+ " died."; 
   		}
   else { 
		return 0 ;
	 }
}

// display - show current state of game including board and snake status
//  args: the board, the snakes
//  rets: nothing
//  does: sends info to cout
//
void display(char brd[ROWS][COLS], Snake a, Snake b)
{	a.draw_head_on_board(brd);
	b.draw_head_on_board(brd);
	draw_board(brd);
	a.print_status();
	b.print_status();
}

//report-couts the result of the game in the proper format
//args- result of game;
//rets- void, couts the results
void report(string result){
	cout << "Game over. " << result << endl;
}
//draw_board-couts the board for the game
//args- 2d array of chars
//rets- void, couts the board
void draw_board(char board[][COLS]){
	screen_clear();
	for (int i = 0 ; i < ROWS ; i ++){
		for (int j = 0 ; j < COLS ; j++){
			cout << board[i][j] ;
		}
		cout << endl ;
	}
}
//initialize_board- sets all elements of the board to a space
//args- 2d array of chars
//rets- void, clears the board of dead squirrels
void initialize_board(char board[][COLS]){
	 for (int i = 0 ; i < ROWS ; i ++){
		for (int j = 0 ; j < COLS ; j++){
			board[i][j] = ' ';
			
		}
	 }
     }
//place_snack: places a snack on the board at a random empty location
//args: the snack char and the 2d board of chars
//rets: void- places snack on the board
void place_snack(char snack, char board[][COLS]){
	int random_row,random_col; 
	do{
	random_row = random_int(1,(ROWS-2));
	random_col = random_int(1,(COLS-2));
	}while (board[random_row][random_col] != ' ' );

		board[random_row][random_col] = snack ;		
			
}	
	
