/*********************************************************
 *  agent.c
 *  Nine-Board Tic-Tac-Toe Random Player
 *  COMP3411/9414/9814 Artificial Intelligence
 *  Alan Blair, CSE, UNSW
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>

#include "common.h"
#include "agent.h"
#include "game.h"

#define MAX_MOVE 81
#define MAX 10000
#define MIN -10000

int board[10][10];
int move[MAX_MOVE+1];
int player;
int m;
int w = 0;
int l = 0;

/*********************************************************//*
   Print usage information and exit
*/
void usage( char argv0[] )
{
  printf("Usage: %s\n",argv0);
  printf("       [-p port]\n"); // tcp port
  printf("       [-h host]\n"); // tcp host
  exit(1);
}

/*********************************************************//*
   Parse command-line arguments
*/
void agent_parse_args( int argc, char *argv[] )
{
  int i=1;
  while( i < argc ) {
    if( strcmp( argv[i], "-p" ) == 0 ) {
      if( i+1 >= argc ) {
        usage( argv[0] );
      }
      port = atoi(argv[i+1]);
      i += 2;
    }
    else if( strcmp( argv[i], "-h" ) == 0 ) {
      if( i+1 >= argc ) {
        usage( argv[0] );
      }
      host = argv[i+1];
      i += 2;
    }
    else {
      usage( argv[0] );
    }
  }
}

/*********************************************************//*
   Called at the beginning of a series of games
*/
void agent_init()
{
  struct timeval tp;

  // generate a new random seed each time
  gettimeofday( &tp, NULL );
  srandom(( unsigned int )( tp.tv_usec ));
}

/*********************************************************//*
   Called at the beginning of each game
*/
void agent_start( int this_player )
{
  reset_board( board );
  m = 0;
  move[m] = 0;
  player = this_player;
}

/*********************************************************//*
   Check if board is empty, return 1 if not empty
*/
int board_empty( int board_num )
{
    int i, f = 0;
    for (i = 1; i <= 9; i++)
    {
        if (board[board_num][i] != EMPTY)
        {
            f = 1;
        }
    }
    return f;
}

/*********************************************************//*
   Check if board is full, return 1 if empty
*/
int board_full( int board_num )
{
    int i, f = 0;
    for (i = 1; i <= 9; i++)
    {
        if (board[board_num][i] == EMPTY)
        {
            f = 1;
        }
    }
    return f;
}

/*********************************************************//*
   Return 1 if player has 3 in a row on a given board
*/
int win() {
    for (int i = 1; i <= 9; i++) {
        // horizontal
    	if((board[i][1] == player) && (board[i][1] == board[i][2]) && (board[i][2] == board[i][3])) return 1;
    	if((board[i][4] == player) && (board[i][4] == board[i][5]) && (board[i][5] == board[i][6])) return 1;
    	if((board[i][7] == player) && (board[i][7] == board[i][8]) && (board[i][8] == board[i][9])) return 1;

    	// vertical
        if((board[i][1] == player) && (board[i][1] == board[i][4]) && (board[i][4] == board[i][7])) return 1;
    	if((board[i][2] == player) && (board[i][2] == board[i][5]) && (board[i][5] == board[i][8])) return 1;
    	if((board[i][3] == player) && (board[i][3] == board[i][6]) && (board[i][6] == board[i][9])) return 1;

    	// diagonal
        if((board[i][1] == player) && (board[i][1] == board[i][5]) && (board[i][5] == board[i][9])) return 1;
    	if((board[i][3] == player) && (board[i][3] == board[i][5]) && (board[i][5] == board[i][7])) return 1;
    }


    return 0;
}

/*********************************************************//*
   Return 1 if !player has 3 in a row on a given board i
*/
int loss() {
    for (int i = 0; i <= 9; i++) {
        // horizontal
    	if((board[i][1] == !player) && (board[i][1] == board[i][2]) && (board[i][2] == board[i][3])) return 1;
    	if((board[i][4] == !player) && (board[i][4] == board[i][5]) && (board[i][5] == board[i][6])) return 1;
    	if((board[i][7] == !player) && (board[i][7] == board[i][8]) && (board[i][8] == board[i][9])) return 1;

    	// vertical
        if((board[i][1] == !player) && (board[i][1] == board[i][4]) && (board[i][4] == board[i][7])) return 1;
    	if((board[i][2] == !player) && (board[i][2] == board[i][5]) && (board[i][5] == board[i][8])) return 1;
    	if((board[i][3] == !player) && (board[i][3] == board[i][6]) && (board[i][6] == board[i][9])) return 1;

    	// diagonal
        if((board[i][1] == !player) && (board[i][1] == board[i][5]) && (board[i][5] == board[i][9])) return 1;
    	if((board[i][3] == !player) && (board[i][3] == board[i][5]) && (board[i][5] == board[i][7])) return 1;
    }


    return 0;
}



/*********************************************************//*
   Return 1 if no one has won and there are no available moves left
*/
int draw( int board_num ) {
    if (board_full(board_num) == 0) return 1;
    return 0;
}

/*********************************************************//*
   Evaluate the board
*/
int eval(){
    int score = 0;
    for (int n = 1; n <= 9; n++) {
        // Advantage me
        if ((board[n][1] == player) && (board[n][1] == board[n][2]) && (board[n][3] == EMPTY)) score = score + 10;
        if ((board[n][2] == player) && (board[n][2] == board[n][3]) && (board[n][1] == EMPTY)) score = score + 10;
        if ((board[n][1] == player) && (board[n][1] == board[n][4]) && (board[n][7] == EMPTY)) score = score + 10;
        if ((board[n][4] == player) && (board[n][4] == board[n][7]) && (board[n][1] == EMPTY)) score = score + 10;
        if ((board[n][7] == player) && (board[n][7] == board[n][8]) && (board[n][9] == EMPTY)) score = score + 10;
        if ((board[n][8] == player) && (board[n][8] == board[n][9]) && (board[n][7] == EMPTY)) score = score + 10;
        if ((board[n][3] == player) && (board[n][3] == board[n][6]) && (board[n][9] == EMPTY)) score = score + 10;
        if ((board[n][6] == player) && (board[n][6] == board[n][9]) && (board[n][3] == EMPTY)) score = score + 10;
        if ((board[n][1] == player) && (board[n][1] == board[n][5]) && (board[n][9] == EMPTY)) score = score + 10;
        if ((board[n][3] == player) && (board[n][3] == board[n][5]) && (board[n][7] == EMPTY)) score = score + 10;
        if ((board[n][7] == player) && (board[n][7] == board[n][5]) && (board[n][3] == EMPTY)) score = score + 10;
        if ((board[n][9] == player) && (board[n][9] == board[n][5]) && (board[n][1] == EMPTY)) score = score + 10;
        if ((board[n][2] == player) && (board[n][2] == board[n][5]) && (board[n][8] == EMPTY)) score = score + 10;
        if ((board[n][4] == player) && (board[n][4] == board[n][5]) && (board[n][6] == EMPTY)) score = score + 10;
        if ((board[n][6] == player) && (board[n][6] == board[n][5]) && (board[n][4] == EMPTY)) score = score + 10;
        if ((board[n][8] == player) && (board[n][8] == board[n][5]) && (board[n][2] == EMPTY)) score = score + 10;
        if ((board[n][1] == player) && (board[n][2] == board[n][3]) && (board[n][3] == EMPTY)) score = score + 5;
        if ((board[n][2] == player) && (board[n][3] == board[n][1]) && (board[n][1] == EMPTY)) score = score + 5;
        if ((board[n][1] == player) && (board[n][7] == board[n][4]) && (board[n][7] == EMPTY)) score = score + 5;
        if ((board[n][4] == player) && (board[n][1] == board[n][7]) && (board[n][1] == EMPTY)) score = score + 5;
        if ((board[n][7] == player) && (board[n][9] == board[n][8]) && (board[n][9] == EMPTY)) score = score + 5;
        if ((board[n][8] == player) && (board[n][7] == board[n][9]) && (board[n][7] == EMPTY)) score = score + 5;
        if ((board[n][3] == player) && (board[n][9] == board[n][6]) && (board[n][9] == EMPTY)) score = score + 5;
        if ((board[n][6] == player) && (board[n][3] == board[n][9]) && (board[n][3] == EMPTY)) score = score + 5;
        if ((board[n][1] == player) && (board[n][9] == board[n][5]) && (board[n][9] == EMPTY)) score = score + 5;
        if ((board[n][3] == player) && (board[n][7] == board[n][5]) && (board[n][7] == EMPTY)) score = score + 5;
        if ((board[n][7] == player) && (board[n][3] == board[n][5]) && (board[n][3] == EMPTY)) score = score + 5;
        if ((board[n][9] == player) && (board[n][1] == board[n][5]) && (board[n][1] == EMPTY)) score = score + 5;
        if ((board[n][2] == player) && (board[n][8] == board[n][5]) && (board[n][8] == EMPTY)) score = score + 5;
        if ((board[n][4] == player) && (board[n][6] == board[n][5]) && (board[n][6] == EMPTY)) score = score + 5;
        if ((board[n][6] == player) && (board[n][4] == board[n][5]) && (board[n][4] == EMPTY)) score = score + 5;
        if ((board[n][8] == player) && (board[n][2] == board[n][5]) && (board[n][2] == EMPTY)) score = score + 5;
        if (board[n][5] == player) score = score + 2;

        // Advantage opponent
        if ((board[n][1] == !player) && (board[n][1] == board[n][2]) && (board[n][3] == EMPTY)) score = score - 10;
        if ((board[n][2] == !player) && (board[n][2] == board[n][3]) && (board[n][1] == EMPTY)) score = score - 10;
        if ((board[n][1] == !player) && (board[n][1] == board[n][4]) && (board[n][7] == EMPTY)) score = score - 10;
        if ((board[n][4] == !player) && (board[n][4] == board[n][7]) && (board[n][1] == EMPTY)) score = score - 10;
        if ((board[n][7] == !player) && (board[n][7] == board[n][8]) && (board[n][9] == EMPTY)) score = score - 10;
        if ((board[n][8] == !player) && (board[n][8] == board[n][9]) && (board[n][7] == EMPTY)) score = score - 10;
        if ((board[n][3] == !player) && (board[n][3] == board[n][6]) && (board[n][9] == EMPTY)) score = score - 10;
        if ((board[n][6] == !player) && (board[n][6] == board[n][9]) && (board[n][3] == EMPTY)) score = score - 10;
        if ((board[n][1] == !player) && (board[n][1] == board[n][5]) && (board[n][9] == EMPTY)) score = score - 10;
        if ((board[n][3] == !player) && (board[n][3] == board[n][5]) && (board[n][7] == EMPTY)) score = score - 10;
        if ((board[n][7] == !player) && (board[n][7] == board[n][5]) && (board[n][3] == EMPTY)) score = score - 10;
        if ((board[n][9] == !player) && (board[n][9] == board[n][5]) && (board[n][1] == EMPTY)) score = score - 10;
        if ((board[n][2] == !player) && (board[n][2] == board[n][5]) && (board[n][8] == EMPTY)) score = score - 10;
        if ((board[n][4] == !player) && (board[n][4] == board[n][5]) && (board[n][6] == EMPTY)) score = score - 10;
        if ((board[n][6] == !player) && (board[n][6] == board[n][5]) && (board[n][4] == EMPTY)) score = score - 10;
        if ((board[n][8] == !player) && (board[n][8] == board[n][5]) && (board[n][2] == EMPTY)) score = score - 10;
        if ((board[n][1] == !player) && (board[n][2] == board[n][3]) && (board[n][3] == EMPTY)) score = score - 5;
        if ((board[n][2] == !player) && (board[n][3] == board[n][1]) && (board[n][1] == EMPTY)) score = score - 5;
        if ((board[n][1] == !player) && (board[n][7] == board[n][4]) && (board[n][7] == EMPTY)) score = score - 5;
        if ((board[n][4] == !player) && (board[n][1] == board[n][7]) && (board[n][1] == EMPTY)) score = score - 5;
        if ((board[n][7] == !player) && (board[n][9] == board[n][8]) && (board[n][9] == EMPTY)) score = score - 5;
        if ((board[n][8] == !player) && (board[n][7] == board[n][9]) && (board[n][7] == EMPTY)) score = score - 5;
        if ((board[n][3] == !player) && (board[n][9] == board[n][6]) && (board[n][9] == EMPTY)) score = score - 5;
        if ((board[n][6] == !player) && (board[n][3] == board[n][9]) && (board[n][3] == EMPTY)) score = score - 5;
        if ((board[n][1] == !player) && (board[n][9] == board[n][5]) && (board[n][9] == EMPTY)) score = score - 5;
        if ((board[n][3] == !player) && (board[n][7] == board[n][5]) && (board[n][7] == EMPTY)) score = score - 5;
        if ((board[n][7] == !player) && (board[n][3] == board[n][5]) && (board[n][3] == EMPTY)) score = score - 5;
        if ((board[n][9] == !player) && (board[n][1] == board[n][5]) && (board[n][1] == EMPTY)) score = score - 5;
        if ((board[n][2] == !player) && (board[n][8] == board[n][5]) && (board[n][8] == EMPTY)) score = score - 5;
        if ((board[n][4] == !player) && (board[n][6] == board[n][5]) && (board[n][6] == EMPTY)) score = score - 5;
        if ((board[n][6] == !player) && (board[n][4] == board[n][5]) && (board[n][4] == EMPTY)) score = score - 5;
        if ((board[n][8] == !player) && (board[n][2] == board[n][5]) && (board[n][2] == EMPTY)) score = score - 5;
        if (board[n][5] == !player) score = score - 2;
    }

    return score;
}

/*********************************************************//*
   Perform alphabeta search to depth d and return best move for current player
*/
int alphabeta(int d, int maxPlayer, int board_num, int alpha, int beta) {

    // Terminating conditions
    if (win()) return 100;
    if (loss()) return -100;
    if (draw(board_num)) return 0;
    if (d == 0) return eval();

    // All legal moves
    int i, c = 0;
    int legal[9];
    for (i = 1; i <= 9; i++) {
        if (board[board_num][i] == EMPTY) {
            legal[c] = i;
            c++;
        }
    }

    // Prune
    int bscore, bmove;
    if (maxPlayer == 1) {
        bscore = MIN;
        // Recur for all legal moves
        for (i = 0; i < c; i++) {
            board[board_num][legal[i]] = player;
            int score = alphabeta(d - 1, 0, legal[i], alpha, beta);
            board[board_num][legal[i]] = EMPTY;
            if (score == 100) {
                bmove = legal[i];
                break;
            }
            if (bscore < score) {
                bscore = score;
            }
            if (alpha < bscore) {
                bmove = legal[i];
                alpha = bscore;
            }
            if (beta <= alpha) break;
        }
    } else {
        bscore = MAX;
        // Recur for all legal moves
        for (i = 0; i < c; i++) {
            board[board_num][legal[i]] = !player;
            int score = alphabeta(d - 1, 1, legal[i], alpha, beta);
            board[board_num][legal[i]] = EMPTY;
            if (bscore > score) {
                bscore = score;
            }
            if (beta > bscore) {
                bmove = legal[i];
                beta = bscore;
            }
            if (beta <= alpha) break;
        }
    }

    if (d != 9) {
        return bscore;
    } else {
        return bmove;
    }
}

/*********************************************************//*
   Choose second move and return it
*/
int agent_second_move( int board_num, int prev_move )
{
  int this_move;
  move[0] = board_num;
  move[1] = prev_move;
  board[board_num][prev_move] = !player;
  m = 2;
   do {
    //my code goes here
        befmove = getBestMove(board,prev_move,DEPTH,player);
        this_move = befmove;
    } while( board[prev_move][this_move] != EMPTY );
  move[m] = this_move;
  board[prev_move][this_move] = player;
  return( this_move );
}

/*********************************************************//*
   Choose third move and return it
*/
int agent_third_move(
                     int board_num,
                     int first_move,
                     int prev_move
                    )
{
    int this_move = 0;
    move[0] = board_num;
    move[1] = first_move;
    move[2] = prev_move;
    board[board_num][first_move] =  player;
    board[first_move][prev_move] = !player;
    m=3;
    do {
        //my code goes here
        befmove = getBestMove(board,prev_move,DEPTH,player);
        this_move = BM;
    } while( board[prev_move][this_move] != EMPTY );
    move[m] = this_move;
    board[move[m-1]][this_move] = player;
    return( this_move );
  /*
  if ((board_num != 5) && (first_move != 5) && (prev_move != 5)) {
      this_move = 5;
  } else {
      int i = 1;
      while ((this_move == 0) && (i < 10)) {
          if ((board_num != i) && (first_move != i)) {
              this_move = i;
          }
          i = i + 2;
      }
      if (i > 10) {
          i = 2;
          while ((this_move == 0) && (i < 10)) {
              if ((board_num != i) && (first_move != i)) {
                  this_move = i;
              }
              i = i + 2;
          }
      }
  }
  move[m] = this_move;
  board[move[m-1]][this_move] = player;
  return( this_move );
  */
}

/*********************************************************//*
   Choose next move and return it
*/
int agent_next_move( int prev_move )
{
    int this_move;
    m++;
    move[m] = prev_move;
    board[move[m-1]][move[m]] = !player;
    m++;
    do {
    //my code goes here
        befmove = alphabeta(9, 1, move[m-1], MIN, MAX);
        this_move = befmove;
    } while( board[prev_move][this_move] != EMPTY );
    //this_move = alphabeta(9, 1, move[m-1], MIN, MAX);
    move[m] = this_move;
    board[move[m-1]][this_move] = player;
    return( this_move );
}

/*********************************************************//*
   Receive last move and mark it on the board
*/
void agent_last_move( int prev_move )
{
  m++;
  move[m] = prev_move;
  if(board[move[m-2]][move[m-1] == player]){
    board[move[m-1]][move[m]] = !player;
  } else {
    board[move[m-1]][move[m]] = player;
  }
}

/*********************************************************//*
   Called after each game
*/
void agent_gameover(
                    int result,// WIN, LOSS or DRAW
                    int cause  // TRIPLE, ILLEGAL_MOVE, TIMEOUT or FULL_BOARD
                   )
{
    if (result == WIN) {
        w++;
    } else {
        l++;
    }
    printf("win: %d\nloss: %d\n", w, l);
  // nothing to do here
}

/*********************************************************//*
   Called after the series of games
*/
void agent_cleanup()
{
  // nothing to do here
}
