#include "l_header.h"
#include "f_header.h"


int minimax( char **board, int size, int x, int y, int difficulty, int maximize, int user ) {

	int finalEval, i, j, eval;
	/* Board Copy */
	char **copy;

	copy = malloc(size * sizeof(char *));

    for( i = 0 ; i < size ; i++ ) {

        *(copy + i) = malloc(size * sizeof(char));

    }

    for( i = 0 ; i < size ; i++ ) {

	    for( j = 0 ; j < size ; j++ ) {

	      	copy[i][j] = board[i][j];	

	    }

	}
	/////
	if(difficulty) {

		if(maximize) {

			finalEval = -99999;
			/* For all possible moves player can make */
			for( i = 0 ; i < size ; i++ ) {

				for( j = 0 ; j < size ; j++ ) {
					
					if( copy[i][j] == 'n' ) {

						if( !user ) //user is white player
							copy[i][j] = 'w';
						else
							copy[i][j] = 'b';

						eval = minimax( copy, size, i, j, difficulty - 1, 0, user );

						copy[i][j] = 'n';

					}
					
					finalEval = max( finalEval, eval );

				}

			}

		} else {//min

			finalEval = 99999;
			/* For all possible moves player can make */
			for( i = 0 ; i < size ; i++ ) {

				for( j = 0 ; j < size ; j++ ) {
					
					if( copy[i][j] == 'n' ) {

						if( !user ) //user is white player
							copy[i][j] = 'w';
						else
							copy[i][j] = 'b';

						eval = minimax( copy, size, i, j, difficulty - 1, 1, user );

						copy[i][j] = 'n';

					}
					
					finalEval = min( finalEval, eval );

				}

			}

		}

		return finalEval;

	} else { 
		
		return eval1( copy, user, size ); 
		
	}

}

int eval1( char **board , int user, int size ) {

	int *score, length1 = 0, length2 = 0;

	score = malloc( sizeof( int ) );

	/* Board Copy */
	char **copy;

	copy = malloc(size * sizeof(char *));

    for( int z = 0 ; z < size ; z++ ) {

        *(copy + z) = malloc(size * sizeof(char));

    }

    for( int z = 0 ; z < size ; z++ ) {

	    for( int k = 0 ; k < size ; k++ ) {

	      	copy[z][k] = board[z][k];	

	    }

	}

	/* 				We will find the bigest path for each player, then we will subtract the two to find the evaluation.
	 		To find a path's length we first cycle through the board until we find a piece of the player we are searching for.
	   Then we empty this cell and add 1 to the length of the path while calling the next function that searches for neighbour cells */

	for( int i = 0 ; i < size ; i++ ) {			//White player biggest path length

	    for( int j = 0 ; j < size ; j++ ) {

	      	if( copy[i][j] == 'w' ) {

	      		copy[i][j] = 'n';
	      		*score = 0;
	      		eval2( copy, score, i, j, 'w', size );
	      		length1 = max( length1, *score );
	      		copy[i][j] = 'w';

	      	}
	    }

	}

	for( int i = 0 ; i < size ; i++ ) {			//Black player biggest path length

	    for( int j = 0 ; j < size ; j++ ) {

	      	if( copy[i][j] == 'b' ) {

	      		copy[i][j] = 'n';
	      		*score = 0;
	      		eval2( copy, score, i, j, 'b', size );
	      		length2 = max( length2, *score );
	      		copy[i][j] = 'b';

	      	}
	    }

	}

	if( user )
		return length2-length1;
	else
		return length1-length2;

}

void eval2( char **board, int *score, int i, int j, char piece, int size ) {

	/* Check "neighbour-cells" */

	if( i - 1 >= 0 ) {

		if ( board[i-1][j] == piece ) {

			board[i-1][j] = 'n';
			(*score)++;
			eval2( board, score, i-1, j, piece, size )	;		

		}
	}
	
	if( i + 1 < size ) {

		if( board[i+1][j] == piece ) {

			board[i+1][j] = 'n';
			(*score)++;
			eval2( board, score, i+1, j, piece, size );			

		}
	}
	
	if( j - 1 >= 0 ) {

		if( board[i][j-1] == piece ) {

			board[i][j-1] = 'n';
			(*score)++;
			eval2( board, score, i, j-1, piece, size );			

		}
	}
	
	if( j + 1 < size ) {

		if( board[i][j+1] == piece ) {

			board[i][j+1] = 'n';
			(*score)++;
			eval2( board, score, i, j+1, piece, size );			
			
		}	
	}
	
	if( ( j + 1 < size ) && ( i - 1 >= 0 )) {

		if( ( board[i-1][j+1] == piece ) ) {

			board[i-1][j+1] = 'n';
			(*score)++;
			eval2( board, score, i-1, j+1, piece, size );			
			
		}
	}

	if( ( j - 1 >= 0 ) && ( i + 1 < size ) ) {

		if( board[i+1][j-1] == piece ) {

			board[i+1][j-1] = 'n';
			(*score)++;
			eval2( board, score, i+1, j-1, piece, size );			
			
		}
			
	}

}
