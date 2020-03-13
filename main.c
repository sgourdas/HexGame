#include "l_header.h"
#include "f_header.h"


int main(int argc, char **argv) {
	
	int size = 11, difficulty = 1, user = 0, swap = 0, nextPlayer, canSwap, winCond, contMove, conti, contj, i, j; /* 0 is white */

	/*
		Command Line Parameter Choices -- Executes if we have parameters (argc > 1) 
	*/

	if(argc > 1) {

		char *n,*d,*b,*s;

		/*
			argv choices:
				-n	size
				-d	difficulty
				-b	user is black player
				-s  swap rule
		*/

		for (i = 1 ; i < argc ; ) {

			if(!strcmp("-n",argv[i])) { /* if we have -n */

				size = atoi(argv[i+1]);
				i+=2;

			} else if(!strcmp("-d",argv[i])) { /* if we have -d */

				difficulty = atoi(argv[i+1]);
				i+=2;

			} else if(!strcmp("-b",argv[i])) { /* if we have -b */

				user = 1;
				i++;

			} else if(!strcmp("-s",argv[i])) { /* if we have -s */

				swap = 1;
				i++;

			}

		}

	}

	/*
		In-Game Commands
	*/

	char cmd[9999], temp[999999], **board;

	FILE *filePath;

	do {

		fflush(stdout); //This is not essential, but is added for the Hex Cup.
		
		/* Read the Command */
		printf("Hex Game> ");
		gets(cmd);

		/* Decide what the Command is and act accordingly 
			-- every single one of these outside ifs 
			correspond to a different in-game command     */

		subStr(cmd, temp, 1);

		if(!strcmp(temp, "newgame")) {

			winCond = 0, canSwap = 2;

			if(partCount(cmd) >= 2) { /* Here User is selected */

				char tempUsr[30];

				subStr(cmd, tempUsr, 2);

				if(!strcmp(tempUsr, "black")) 
					user = 1;

				if(partCount(cmd) >= 3) { /* Here swap option is defined */

					char tempSwp[30];

					subStr(cmd, tempSwp, 3);

					if(!strcmp(tempSwp, "swapon")) 
						swap = 1;

					if(partCount(cmd) >= 4) { /* Here size option is defined */

						char tempSz[30];
						
						subStr(cmd, tempSz, 4);

						size = atoi(tempSz);

					}

				}

			}

			/* Board Making */

			board = malloc(size * sizeof(char *));

		    for(i = 0 ; i < size ; i++)
		        *(board + i) = malloc(size * sizeof(char));

		    for(i = 0 ; i < size ; i++)
		        for(j = 0 ; j < size ; j++)
		        	board[i][j] = 'n';

		    boardDisp(board, size);

		    nextPlayer = 0;

		    next(nextPlayer, user);

		    filePath = fopen("moves.hex", "w+");
 
		} else if(!strcmp(temp, "play")) {

			if(!winCond && (nextPlayer == user)) { // (!winCond) for local 1v1 

				char move[10];

				canSwap--;
				
				subStr(cmd, move, 2);

				/* Translate move to numbers */

				int y = *move - 64, x = *(move + 1) - 48;

				if(strcmp(move + 2, "\0")) {

					x *= 10;
					x += *(move + 2) - 48;

				}

				/* Make the move -- if possible */

				if(board[x-1][y-1] != 'n') {

					boardDisp(board, size);
					printf("Move can't be played! Position is occupied\n");

				} else {

					if(!nextPlayer)
						board[x-1][y-1] = 'w';
					else
						board[x-1][y-1] = 'b';

					/* Log the move */

					fputs(move, filePath);
					fflush(filePath);

					boardDisp(board, size);

					printf("Move played: %s\n", move);

					winCond = win(board, size, nextPlayer);

					nextPlayer = !nextPlayer;

				}

				if(!winCond)
					next(nextPlayer, user);

			} else if(winCond) {

				printf("Game has ended!\n");

			} else if(!(nextPlayer == user)) {

				printf("You must wait for your turn to play.\n");

			}

		} else if(!strcmp(temp, "cont")) {

			if(nextPlayer != user) {

				canSwap--;

				contMove = -99999, conti = size / 2, contj = size / 2;
				int temp = -99999;
				/* Find the best evaluated move from all the possible ones */
				for(i = 0 ; i < size ; i++) {
					
					for (j = 0 ; j < size ; j++) {

						if(board[i][j] == 'n') {

							if(!user)
								board[i][j] = 'w';
							else 
								board[i][j] = 'b';

							temp = minimax(board, size, i, j, difficulty-1, 1, user);

							board[i][j] = 'n';

							contMove = max(contMove, temp);

							if(contMove != temp) {

								conti = i;
								contj = j;

							}

						}

					}
				
				}

				/* Make the best evaluated move */

				if(!user) 
					board[conti][contj] = 'b';
				 else
					board[conti][contj] = 'w';

				boardDisp(board, size);

				printf("Move played: %c%d\n", contj+65, conti+1);

				/* Log the move */

				int tempi, tempCond = 0; //Condition for the case where j is double digit so we have to write it digit by digit
				
				conti++;

				if(conti > 9) {

					tempCond = 1;
					tempi = (conti) % 10;
					conti /= 10;


				}

				fputc(contj + 65, filePath);
				fputc(conti + 48, filePath);
				if(tempCond)
					fputc(tempi + 48, filePath);

				fflush(filePath);

				winCond = win(board, size, nextPlayer);

				nextPlayer = !nextPlayer;	

				if(!winCond)
					next(nextPlayer, user);			

			} else {

				printf("Cannnot use cont right now, it is user's turn.\n");

			}

		} else if(!strcmp(temp, "undo")) {

			/* To make undos possible, we log each move played to a temporary moves.hex file */

			if(!winCond) {

				int extraCh = 0;

				nextPlayer = !nextPlayer;

				/* Find numbers of characters of last move */

				/*  We have to remember that fgetc() gets our 
				   pointer 1 position to the right so we must 
				     always fix the position after using it    */

				fseek(filePath, -2 , SEEK_CUR); //-2 pointerseats

				if (fgetc(filePath) < 58) { /* this if means we have 3 characters since this char is a number(<58) */
												//+1 pointerseats
					fseek(filePath, -1, SEEK_CUR); //-1 pointerseats

					extraCh = 1;

				}

				fseek(filePath, -1 , SEEK_CUR);//-1 pointerseats -- -2 total for 2 chars / -3 for 3 chars (ready for x)

				/* Identify and undo last move */

				int y = fgetc(filePath) - 64;
				int x = fgetc(filePath) - 48;

				if(extraCh) {

					x *= 10;
					x += fgetc(filePath) - 48;


				}

				board[x-1][y-1] = 'n';

				fseek(filePath, -(2 + extraCh) , SEEK_CUR); /* 	File Pointer will stay in a place where undos are 
																 to its right, so as future undos will not be impacted */
				boardDisp(board, size);

				next(nextPlayer, user);

			} else {

				printf("Game not in progress!\n");

			}

		} else if(!strcmp(temp, "suggest")) {

			contMove = -99999;
			int temp = -99999;
			/* Find the best evaluated move from all the possible ones */
			for(i = 0 ; i < size ; i++) {
					
				for (j = 0 ; j < size ; j++) {

					if(board[i][j] == 'n') {

						if(!user)
							board[i][j] = 'b';
						else 
							board[i][j] = 'w';

						temp = minimax(board, size, i, j, difficulty-1, 0, user);

						board[i][j] = 'n';

						contMove = min(contMove, temp);

						if(contMove != temp) {

							conti = i;
							contj = j;

						}

					}

				}
				
			}

			printf("Suggested move: %c%d\n", contj+65, conti+1);

		} else if(!strcmp(temp, "level")) {

			if(partCount(cmd) == 2) {

				char tempLvl[5];
				
				subStr(cmd, tempLvl, 2);

				difficulty = atoi(tempLvl);

			} else {

				printf("Current game level is: %d\n", difficulty);

			}

		} else if(!strcmp(temp, "swap")) {
			
			if(canSwap == 1) {
				
				if(nextPlayer == user) {

					//user = !user; This can be uncommented to make local 1v1 possible with some other adjustments
					/* Following part is sane thing from the undo command */
					int extraCh = 0;


					fseek(filePath, -2 , SEEK_CUR);

					if (fgetc(filePath
						) < 58) {

						fseek(filePath, -1, SEEK_CUR);

						extraCh = 1;

					}

					fseek(filePath, -1 , SEEK_CUR);

					int y = fgetc(filePath) - 64;
					int x = fgetc(filePath) - 48;

					if(extraCh) {

						x *= 10;
						x += fgetc(filePath) - 48;

					}

					board[x-1][y-1] = 'n';
					board[y-1][x-1] = 'b';

					nextPlayer = !nextPlayer;

					boardDisp(board, size);

					printf("Move played: swap\n");

					next(nextPlayer, user);

				} else {

					printf("You must wait for your turn to swap\n");

				}

			} else {

				printf("Only black player can swap on his first move.\n");

			}

		} else if(!strcmp(temp, "save")) {

			char fileName[100];

			subStr(cmd, fileName, 2);

			FILE *fp;

			fp = fopen(fileName, "wb");

			fwrite(&size, 1, 1, fp);

			if(nextPlayer) {
			
				fwrite("b", 1, 1, fp);
			
			} else {

				fwrite("w", 1, 1, fp);

			}

			for(i = 0 ; i < size ; i++) {

				fwrite(*(board+ i), sizeof(char), size, fp);

			}

			printf("State of game saved at: %s\n", fileName);

			fclose(fp);

		} else if(!strcmp(temp, "load")) {

			char fileName[100], nextP[5];

			subStr(cmd, fileName, 2);

			FILE *fp;

			fp = fopen(fileName, "rb");

			fread(&size, 1, 1, fp);
			fread(nextP, 1, 1, fp);

			if (!(strcmp(nextP, "w"))) {
			
				nextPlayer = 0;
			
			} else {

				nextPlayer = 1;
			
			}

			board = malloc(size * sizeof(char *));

		    for(i = 0 ; i < size ; i++)
		        *(board + i) = malloc(size * sizeof(char));

		    for(i = 0 ; i < size ; i++)
		        fread(*(board + i), sizeof(char), size, fp);

		    fclose(fp);

		    filePath = fopen(fileName, "r+");

		    fseek(filePath, 0, SEEK_END);

		    boardDisp(board, size);

		    next(nextPlayer, user);

		    winCond = 0;

		} else if(!strcmp(temp, "showstate")) {

			boardDisp(board, size);

			next(nextPlayer, user);

		} else if(!strcmp(temp, "quit")) {

			fclose(filePath);
			remove("moves.hex");
			return 0;

		} else { printf("Uknown Command!\n"); } //Maybe add help command here

	} while(1);

}