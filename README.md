# HexGame
A command line simulation of the Hex board game (Human vs AI)


### Installation

Download source code by typing:

```
git clone https://github.com/sgourdas/HexGame.git
```


### Compilation

Enter the ``` make ``` command while in the */Hex-Game/* directory


### Execution 

Type:

Type ``` ./hex ``` command while in the game's directory


### Information about the game

Hex is a strategy board game for two players, B (black) and W (white), played on a hexagonal grid, usually the size of 11x11. 

Players alternate placing their colored pieces, on unoccupied spaces of the board, in an attempt to make a 
continuous chain from their side of the board to the opposite. 

The first player to do so, wins.

More info on the Hex Game can be found here: https://en.wikipedia.org/wiki/Hex_(board_game)


## Available arguments and commands

### Command line arguments
You can give the following arguments in the command line:

-n \<size\> : Sets the size of the board (default = 11).

-d \<difficulty\> : Sets the game difficulty (default = 1).

-b : Sets human as the black player (default = white).

-s : Enables the swap rule (default = disabled).



### Commands during gameplay
You can give the following commands at any point of the game:

• newgame  \[white|black\[swapoff|swapon \[\<size>]]]

Starts a new game based on the parameters given.

• play \<move\>

User performs said \<move\>. 
- Note that acceptable moves are of the format "L#" where L is a Capital Letter and # a number.

• cont

The AI makes a move.

• suggest

The AI suggests a move.

• undo

Reverts back one move.

• level \<difficulty\>

Sets the difficulty level to \<difficulty\>.

• swap

If the swap rule is on, performs the swap move for the user.

• save \<statefile\>
  
Saves the current state of the game in the file named \<statefile\>.

• load \<statefile\>
  
Loads the gamee state saved in the file named \<statefile\>.

• showstate

Prints the current game state.

• quit

Quits the game.


NOTE: At the current state, the AI is pretty dumb. This will be improved in futuree commits. 


## About
- This is a first semester assignment, by professor [P.Stamatopoulos](http://cgi.di.uoa.gr/~takis/Welcome.html), for the Department of Informatics and Telecommunications, Uoa.
