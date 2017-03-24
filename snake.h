#include <iostream>
using namespace std;
#include "msnake.h"

// -------------------------------------------------------------
// -----snake.h : SNAKE DEFINITION ----------------------------
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
