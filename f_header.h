char *subStr( char *, char *, int );
int partCount( char * );
void next( int, int );
void boardDisp(char **, int );
int win( char **, int, int );
int seq( char **, int, int, int, int *, char );
int eval1( char ** , int, int );
void eval2( char **, int *, int, int, char, int );
int max( int, int );
int min( int, int );
int minimax( char **, int, int, int, int, int, int );