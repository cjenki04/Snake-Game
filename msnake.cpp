#include <iostream>
using namespace std;
#include "termfuncs.h"

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
// -------------------------------------------------------------
// ----- SNAKE DEFINITION --------------------------------------
// -------------------------------------------------------------

class Snake
{
    public:
	void	init();
	void	set_name(string);
	void	set_pos(int r, int c, char dir);
	void	set_controls(int l, int r, int f);
	void	set_body(char);
	void	set_EU(int);
	void	set_color(string fg, string bg);	// not required
	void 	draw_body(char b[][COLS]);
	char	get_direction();	
	string	get_name();
	int	get_score();
	int     get_eu();
	bool	check_col_pos();
	bool	check_row_pos();
	void    get_food(char b[][COLS]);
	bool	process_key(char, char [ROWS][COLS]);
	bool	is_alive();
	void	print_status();
	void	draw_head_on_board(char [ROWS][COLS]);
	void	setup_snake(int num, int row, int col, char dir, int EU);

    private:
	int score;
	int energy_units;
	string name;
	bool alive;
	char body;
	char direction ;  
	string color;
	int rpos;
	int cpos;
	int lrpos;
	int lcpos;
	char clockwise_turn_key;
	char counterclockwise_turn_key;
	char move_key;
	char bodies[ROWS][COLS];
	void    counterclockwise_turn();
	void	clockwise_turn();
	void 	move(char b[][COLS]);


};

// -------------------------------------------------------------
// ----- Main Game that uses a Snake ---------------------------
// -------------------------------------------------------------

void	place_snack(char, char[ROWS][COLS]);
string	play_game(char[ROWS][COLS]);
void	display(char [ROWS][COLS], Snake, Snake);
string	compute_outcome(Snake, Snake);
void 	report(string result);
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
	


// -------------------------------------------------------------------------
//  SNAKE IMPLEMENTATION
//    The following section contains the member functions for a Snake
//---------------------------------------------------------------------------

//
// init -- set initial default values for a Snake 
//   args: none
//   rets: nothing
//   mods: modifies the snake by setting its member variables
//
void Snake::init()
{
	score    = 0;
	alive    = true;
	for (int i = 0 ; i < ROWS ; i++){
		for (int j = 0; j < COLS ; j++){
			bodies[i][j] = ' ';
		}
	}
}
//is_alive-checks to see if snake has died
//args:none
//rets: boolean 
//note: will always return alive for phase 0
bool Snake::is_alive(){
	if (energy_units == 0){
		alive = false;
	}
	if (bodies[rpos][cpos] == body){
		alive = false;
	}
	return alive;
}
//set_controls-used in set_up_snake to use user input to set custom controls
//args: int left turn key, int right turn key, int forward key
//rets: void, stores controls
void Snake::set_controls(int l, int r, int f){
	clockwise_turn_key = r;
	counterclockwise_turn_key = l;
       	move_key = f;
}
//draw_head_on_board-puts the snake head in the board at its current location
//args: 2d array of chars
//rets: void
void Snake::draw_head_on_board(char b[][COLS]){
	b[rpos][cpos] = direction ;
}
//set_body-sets the snake's body equal to the user input in set_up_snake
//args:char body
//rets:void
void Snake::set_body(char b){
	body = b ;
}
char Snake::get_direction(){
	return direction;
}
//set_name-sets the snake's name to the user input in set_up_snake
//args:string name
//rets: void
void Snake::set_name(string n){
	name = n;
}
//set_pos-sets the initial position and direction of the snake
//args:int row, int col, char direction
//rets: void
void Snake::set_pos(int r,int c, char d){
	rpos = r;
	cpos = c;
	direction = d;
}
//set_EU-sets the energy_units value of the snake to the argument
//args:int energy units
//rets:void
void Snake::set_EU(int eu){
	energy_units = eu ;
}
//get_name-returns the name of the snake
//args:none
//return: string name
string Snake::get_name(){
	return name;
}
//get_score-returns the score of the snake
//args:none
//rets:int score
int Snake::get_score(){
        return score;
}
//get_eu-returns the snake's current energy_units value
//args:none
//rets:int energy_units
int Snake::get_eu(){
	return energy_units;
}
//print_status-prints the current stats of the snake including its
//energy units, score, and the keys that control it
//args:none
//rets:void, couts status
void Snake::print_status(){
	cout << name << " EU: " << energy_units
	     << "  Score: " << score
	     << "  Keys: " <<  counterclockwise_turn_key
	     << clockwise_turn_key << move_key
	     << endl ;
}
//process_key-calls a method based on the getachar() input
//either turns or moves the snake
//args:char input, 2d array of chars
//rets:boolean, is always true once it finishes 
bool Snake::process_key(char input, char b[][COLS]){
	bool is_key_used = false;	
	if (input == move_key){
		is_key_used = true;
		move(b);
	}
	if (input == clockwise_turn_key){
		is_key_used = true;
		clockwise_turn();
	}
	if (input == counterclockwise_turn_key){
		counterclockwise_turn();
		is_key_used = true;
	}

	return is_key_used ;
}
//move-moves the snake one space, checks to see if it needs to be wraped,
//draws the tail after it has moved
//args: 2d array of chars
//rets:void 
void Snake::move(char b [][COLS]){
	lrpos = rpos;
	lcpos = cpos;
    	if ((check_col_pos()) and (check_row_pos())){
		if (direction == UP){
			rpos--;
		}
		if (direction == DOWN){
			rpos++;
		}
		if (direction == LEFT){
			cpos--;
		}
		if (direction == RIGHT){
			cpos++;
		}
	}
	score++;
	energy_units--;
	get_food(b);
	draw_body(b);
	bodies[lrpos][lcpos] = body ;
}
//clock_turn-turns the snake head clockwise
//args:none
//rets:void
void Snake::clockwise_turn(){
	if (direction == UP){
		direction = RIGHT;
	}
	else if (direction == RIGHT){
		direction = DOWN;
	}
	else if (direction == DOWN){
		direction = LEFT;
	}
	else if (direction == LEFT){
		direction = UP;
	}
}
//counter_turn-turns the snake head counterclockwise
//args:none
//rets:void
void Snake::counterclockwise_turn(){
      	if (direction == UP){
		direction = LEFT;
	}
	else if (direction == RIGHT){
		direction = UP;
	}
	else if (direction == DOWN){
		direction = RIGHT;
	}
	else if (direction == LEFT){
		direction = DOWN;
	}
}
//draw_body- draws the snakes body using the last pos of the snake head
//implemented in move
//args:2d array of chars
//rets:void
void Snake::draw_body(char b[][COLS]){
	b[lrpos][lcpos] = body;
}
//check_row_pos-checks to see if the snake's row position is ok, returns
//true if it does not need to wrap, wraps the snake and returns false if it 
//needs to
//args:none
//rets: boolean
bool Snake::check_row_pos(){
	bool okpos = true;
	if (rpos == 1){
		if (direction == UP){
			rpos = (ROWS-2);
			okpos = false;
		}
	}
	if (rpos == (ROWS-2)){
		if (direction == DOWN){
			rpos = 1;
			okpos = false;
		}
	}
	return okpos;
}
//check_col_pos-checks to see if the snake's col position is ok, returns
//true if it does not need to wrap, wraps the snake and returns false if it
//needs to
//args:none
//rets:boolean
bool Snake::check_col_pos(){
	bool okpos = true;
	if(cpos == 1){
		if (direction == LEFT){
			cpos = (COLS-2);
			okpos = false;
		}
	}
	if(cpos == (COLS-2)){
		if (direction == RIGHT){
			cpos = 1;
			okpos = false;
		}
	}
	return okpos;
}
// get_food: checks to see if the snake has landed on a snack and if it has
//	     the snake receives points and a new snack is made
// args: 2d array of chars
// rets: void-searches for food
void Snake::get_food(char b[][COLS]){
       	if (b[rpos][cpos] == EGG_SYM){	
       		energy_units += EGG_VAL;
	       	place_snack(EGG_SYM, b);
       	}
	if (b[rpos][cpos] == BUG_SYM){
	        energy_units += BUG_VAL;
		place_snack(BUG_SYM, b);
		}
}
//
// setup_snake -- initialize a snake for the game
// args: the snake number, its row, col, dir, and initial EU
// rets: void-sets up the snake 
void Snake:: setup_snake(int num, int r, int c, char d, int eu )
{
	string	n;
	char	lkey,rkey,fkey, body;

	init();			// set any initial default values
	set_EU(eu);			// set initial energy
	set_pos(r, c, d);		// set pos and direction

	// now customize for the player
	cout << "Welcome, player " << num << endl;
	cout << "Name? ";
	cin  >> n;
	set_name(n);

	cout << "Body character? ";
	cin  >> body;
	set_body(body);

	cout << "Keys for left, right, fwd? ";
	cin  >> lkey >> rkey >> fkey ;
	set_controls(lkey, rkey, fkey);

}
