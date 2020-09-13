# HexGame
A command line simulation of the Hex board game (Human vs AI)


## Information about the game

Hex is a strategy board game for two players, B (black) and W (white), played on a hexagonal grid. Players alternate placing their colored pieces, on unoccupied spaces of the board. The goal is to make a continuous chain from their side of the board to the opposite. The first player to do so, wins.

More info on the Hex Game can be found [here](https://en.wikipedia.org/wiki/Hex_(board_game))

## Getting to play

### Compilation

Enter the ``` make ``` command while in the */HexGame/* directory

### Execution 

Type ``` ./hex ``` while in the game's directory

### Command line arguments
You can give the following arguments in the command line:

``` -n <size> ``` : Sets the size of the board (default = 11).

``` -d <difficulty> ``` : Sets the game difficulty (default = 1).

``` -b ``` : Sets human as the black player (default = white).

``` -s ``` : Enables the swap rule (default = disabled).

### Commands during gameplay
You can give the following commands at any point of the game:

• ``` newgame [white|black [swapoff|swapon [size]]] ``` : Starts a new game based on the parameters given.

• ``` play <move> ``` : User performs said \<move\> (format "L#" where L is a Capital Letter and # a Number).

• ``` cont ``` : The AI makes a move.

NOTE: At this stage, the AI is not properly functioning. This will be improved in future commits. 

• ``` suggest ``` : The AI suggests a move.

• ``` undo ``` : Reverts back one move.

• ``` level <difficulty> ``` : Sets the difficulty level to \<difficulty\>.

• ``` swap ``` : If the swap rule is on, performs the swap move for the user.

• ``` save <statefile> ``` : Saves the current state of the game in the file named \<statefile\>.

• ``` load <statefile> ``` : Loads the gamee state saved in the file named \<statefile\>.

• ``` showstate ``` : Prints the current game state.

• ``` quit ``` : Quits the game.


## About
- This is a first semester assignment (fourth and last one), by professor [P.Stamatopoulos](http://cgi.di.uoa.gr/~takis/Welcome.html), for the Department of Informatics and Telecommunications, UoA. It was recommended for 2 people, but I dicided to take it on solo.
