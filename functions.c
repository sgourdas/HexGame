#include "l_header.h"
#include "f_header.h"


char *subStr( char *str1, char *str2, int part ) { /*    subStr is a function that copies the part
													     substring of str1 to str2 and returns str2's 
													  address - "parts" are strings seperated by spaces  */
	int i = 0, j = 0;

	while( part > 1 ) {

		while( *(str1 + i) != ' ' ) { /* cycle through parts */

			i++;

		}

		i++;
		part--;

	}

	/* here we have reached the part we want to copy */

	while( *(str1 + i) != ' ' ) {

		*(str2 + j) = *(str1 + i);
		i++;
		j++;

	}

	*(str2 + j) = '\0';

	return str2;

}

int partCount( char *str ) { /* partCount function just counts how many parts str has */

	int parts = 1, i = 0;

	while( *(str + i) != '\0' ) {

		if( *(str + i) == ' ' ) {

			parts++;

		}

		i++;

	}

	return parts;

}

void boardDisp(char **board, int size) { /* Displays the current state of the board */

	int i, j;

	//white

	for(i = 0 ; i < size / 2 ; i++ ) 
		printf("   ");

	printf("    W H I T E\n    ");
	
	//upper letters
	
	for(i = 0 ; i < size ; i++)
		printf("%c   ", i + 65);

	printf("\n    ");

	//_   _   _    _
	
	for(i = 0 ; i < size ; i++)
		printf("_   ");

	printf("\n   /");

	// \_/ \_/
	
	for(i = 0 ; i < size - 1 ; i++)
		printf(" \\_/");

	printf(" \\\n");

	//Looping cells

	for( i = 0 ; i < size ; i++ ) {

		for( j = 0 ; j < i ; j++ )
			printf(" ");

		for( j = 0 ; j < i ; j++ )////////////////
			printf(" ");

		printf("%d", j + 1);
		if(i < 9)
			printf(" ");
		printf("|");

		for( j = 0 ; j < size ; j++ ) {

			printf(" ");
			
			if( board[i][j] != 'n' )//PRINT EMPTY CELLS WHEN == "N"
				printf("%c", board[i][j]);
			else 
				printf(" ");

			printf(" |");

		}

		printf(" %d", i + 1);

		if ( i == ( size / 2 - 1) ) //!
			printf("  B");
		if ( i == ( size / 2 ) ) //!
			printf("  A");
		if ( i == ( size / 2 + 1 ) ) //!
			printf("  K");

		printf("\n");

		////////

		for( j = 0 ; j < i ; j++ )
			printf(" ");
		printf("   ");


		for( j = 0 ; j < i ; j++ )////////////////
			printf(" ");

		for( j = 0 ; j < size ; j++ )
			printf("\\_/ ");

		if( i != size - 1 )
			printf("\\");

		if ( i == ( size / 2 - 1) ) //!
			printf("    L");
		if ( i == ( size / 2 ) ) //!
			printf("    C");

		printf("\n");

	}

	printf("\n");

}

void next(int nextPlayer, int user) { /* Message for next Player */

	if( !nextPlayer ) {
		    	
		printf("White player ");

    } else {

    	printf("Black player ");

    }
		    
    if( nextPlayer == user ) {
		   
	   	printf("(human) ");
		   
    }
		    
    printf("plays now.\n");

}

int win( char **board, int size, int player ) { /* Determines whether someone has won */

	int i, *won;

	*won = 0;

	for( i = 0 ; i < size ; i++ ) {
		
		if( board[i][0] == 'b' ) {
		
			board[i][0] = 'n';
			seq( board, size, i, 0, won, 'b' );				
			board[i][0] = 'b';
			
			if( *won ) {

				printf("\n");
				break;

			}
		
		} else if( board[0][i] == 'w' ) {
			
			board[0][i] = 'n';
			seq( board, size, 0, i, won, 'w' );			
			board[0][i] = 'w';
			
			if( *won ) {

				printf("\n");
				break;

			}

		}

	}

	if( *won ) {

		if( player )
			printf("Black");
		else
			printf("White");

		printf(" player wins!\n");

	return 1;

	} else { return 0; }

}

int seq( char **board, int size, int i, int j, int *won, char player ) {

	if( (( (i == size - 1) && (player == 'w')) || (j == size - 1) && (player == 'b')) ) { /* Win Condition */
		*won = 1;
		printf( "Win with path: %c%d", j+65, i+1 );
		return 0;

	}
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
	
	/* Check "neighbour-cells" */

	if( ( i - 1 >= 0 ) && !(*won) ) {
		if ( board[i-1][j] == player ) {
			
			board[i-1][j] = 'n';
			seq( board, size, i-1, j, won, player );			
			board[i-1][j] = player;
			if( *won )
				printf( " - %c%d", j+65, i+1 );
		}
	}
	
	if( ( i + 1 < size ) && !(*won) ) {
		if( board[i+1][j] == player ) {
			
			board[i+1][j] = 'n';
			seq( board, size, i+1, j, won, player );			
			board[i+1][j] = player;
			if( *won )
				printf( " - %c%d", j+65, i+1 );

		}
	}
	
	if( ( j - 1 >= 0 ) && !(*won) ) {
		if( board[i][j-1] == player ) {
			
			board[i][j-1] = 'n';
			seq( board, size, i, j-1, won, player );			
			board[i][j-1] = player;
			if( *won )
				printf( " - %c%d", j+65, i+1 );

		}
	}
	
	if( ( j < size ) && !(*won) ) {
		if( board[i][j+1] == player ) {
			
			board[i][j+1] = 'n';
			seq( board, size, i, j+1, won, player );			
			board[i][j+1] = player;
			if( *won )
				printf( " - %c%d", j+65, i+1 );


		}	
	}
	
	if( ( j + 1 < size ) && ( i - 1 >= 0 ) && !(*won) ) {
		if( ( board[i-1][j+1] == player ) ) {
			
			board[i-1][j+1] = 'n';
			seq( board, size, i-1, j+1, won, player );			
			board[i-1][j+1] = player;
			if( *won )
				printf( " - %c%d", j+65, i+1 );
			

		}
	}

	if( ( j - 1 >= 0 ) && ( i + 1 < size ) && !(*won) ) {
		if( board[i+1][j-1] == player ) {
			
			board[i+1][j-1] = 'n';
			seq( board, size, i+1, j-1, won, player );			
			board[i+1][j-1] = player;
			if( *won )
				printf( " - %c%d", j+65, i+1 );
		}
			
	}

}

int max( int var1, int var2 ) { /* Returns bigger of the two values */

	if( var1 >= var2 )
		return var1;
	else
		return var2;

}

int min( int var1, int var2 ) { /* Returns smaller of the two values */

	if( var1 <= var2 )
		return var1;
	else
		return var2;

}