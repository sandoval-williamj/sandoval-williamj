//DUE: 12.11.2023, TEAM 10: Jake, William, & Felipe, C-Portfolio

/* DESCRIPTION: This is a script for team 10's C Portfolio project. 
In this project, each team member designs a game utilizing the concepts we have learned
in the course ENGR 0711, taught by Dr. Mena.

William is developing a rendition of Connect4, Jake is creating a version of Tic-Tac-Toe, and Felipe is making hangman.
We are all computer engineering students.
*/

/* Specific Assignment Details: This is a group project for the University of Pittsburgh's course ENGR 0711,
Honors Engineering Analysis and Engineering Computing. For our end-of-semester project, we are tasked with 
creating 3 different games incorporating ideas and techniques learned throughout the semester. 

Some of the topics you may see below include: functions, loops, escape-sequences, recursion, 
variable types, user input, array and matrix operations, & filepointers. 

If you have any specific questions regarding the assignment, please contact us at the emails below:
    William Sandoval Casas - sandoval.williamj@pitt.edu
    Jake Chinchar - jac682@pitt.edu
    Felipe Correa - ffc2@pitt.edu
*/

//Importing libraries
#include <stdlib.h>
#include <stdio.h>

//CONNECT 4 function prototypes - Author: William Sandoval Casas
void connect4(void);
void startGame(void);
void yourTurn(int, char[], char[], char[], char[], char[], char[], int[][7], int[][7]);
void availableRows(int[][7], int[][7], int[]);
int userInputRowChecker(int[], int, int);
int userInputColumnChecker(int, int, int[][7], int[][7], int);
int victoryChecker(int, int[][7], int[][7]);
void dispBoard(char[], char[], char[], char[], char[], char[]);
void podium(int);
int juegaAgain(int);
void jake(void);

//Tic-tac-toe prototypes - Author: Jake Chinchar
void ttt5(void);
int switch_player(int);
char play_again(char);

//Hangman prototypes - Author: Felipe Correa
void hangMan(void);

//Main method
int main(void){
    
    //Variables for main
    char userChoice, runAgain = 'y';
    int attempts = 0;

    //Start program here 
    printf("Welcome to the Team 10 C-Portfolio project created by Jake Chinchar, William Sandoval Casas, Felipe Correa.\n\n");

    //Re-runs entite program
    while (runAgain == 'y' || runAgain == 'Y'){

        //Prompts user for game to play and error checks user input
        do{
        
            if(attempts > 0){

                printf("\nPlease be sure to have an accurate input:\n");

            }

            printf("\nPlease enter the character 'a' to play Hangman or\nenter the character 'b' to play tic-tac-toe or\nthe character 'c' to play Connect4:\n");
            scanf(" %c", &userChoice);
            attempts++;

        } while(userChoice != 'A' && userChoice != 'a' && userChoice != 'B' && userChoice != 'b' && userChoice != 'C' && userChoice != 'c');

        printf("\n");
        //Switch case calls separate games
        switch(userChoice){
            //Calls the game hangman
            case 'a':
            case 'A':
                hangMan();
            break;
            //calls the game tic tac toe
            case 'b':
            case 'B':
                ttt5();
            break;
            //calls the game connect 4
            case 'c':
            case 'C':
                connect4();
            break;
        }

        //Prompts user to run program again and error checks user input
        attempts = 0;
        do{

            if(attempts > 0){

                printf("\nPlease check the accuracy of your input.\n");

            }

            printf("\nWould you like to run this program again? Please enter y for yes and n for no:\n");
            scanf(" %c", &runAgain);
            attempts++;

        } while(runAgain != 'Y' && runAgain != 'y' && runAgain != 'N' && runAgain != 'n');

    }
}
//END OF MAIN METHOD________________________________________________________________________
/*                                                                                          */
//FUNCTIONS---------------------------- ● ○ ------------------------------------------------


//Calls the game connect4
void connect4(void){    //Connect4 is a game on a 6 by 7 board where players try to match 4 pieces to win. Whoever matches 4 first, wins!

    //Variable for repetition
    int playAgain = 1;

    //Forces program into while loop, which repeats at user discretion
    while (playAgain == 1){

        //Variables
        char row1[8] = "       ", row2[8] = "       ", row3[8] = "       ", row4[8] = "       ", row5[8] = "       ", row6[8] = "       "; //might have to place spaces in when printing!!!! -William
        int locPlayer1[6][7] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}, locPlayer2[6][7] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}, gameOver = 0, playerTurn = 0;

        //Calls function startGame:
        startGame();

        //Displays board for user experience
        dispBoard(row1, row2, row3, row4, row5, row6);

        //While loop keeps calling the same functions until a player wins or a tie is reached, essentially where int gameOver is no longer Null - simulates boolean false
        while (gameOver == 0){

            //Calls the function that allows user to play (Player 1 -> 0 mod, Player 2 --> 1 mod)
            yourTurn(playerTurn, row1, row2, row3, row4, row5, row6, locPlayer1, locPlayer2);

            //Counter adds one which switches which player plays
            playerTurn ++;

            //Calls the function dispBoard to display the board for user experience
            dispBoard(row1, row2, row3, row4, row5, row6);

            //Calls function which checks if a user has won, !! returns !! gameOver as 0 or 1. If == 1, game over is thought of as true and the game proceeds to end.
            gameOver = victoryChecker(gameOver, locPlayer1, locPlayer2);  

        }

        //printf("\n\nGame Won.\n");
        //Function to declare result of game, maybe include how many rounds it took w/ playerTurn (Note to self: maybe call dispBoard again?)
        podium(gameOver);

        //Calls a function asking user whether to repeat program or not
        playAgain = juegaAgain(playAgain); // Function to play again

    }

}
 
//Calls the game tic tac toe
void ttt5(void){    //Tic tac toe is a game on a 3 by 3 board, where players fight to match 3 pieces in a row. 
    //Variables
	char ttt[5][5] = {{' ','|',' ','|',' '},{'-','-','-','-','-'},{' ','|',' ','|',' '},{'-','-','-','-','-'},{' ','|',' ','|',' '}}, shape, again[10] = {'y'};
	int example[3][3] = {{1,2,3},{4,5,6},{7,8,9}}, position, player = 1, newPosition, i, j, wins1 = 0, wins2 = 0;
	
	//Rules of the game
	printf("This is tic-tac-toe. To win, you must have three X's or O's in a row. \nYou can do this by entering the position you would like to place an X or an O.\nThe positions are indicated below: \n");
	
	while(again[0] == 'Y' || again[0] == 'y')
	{
		//Shows positions to enter
		printf("\n%d   %d   %d\n\n%d   %d   %d\n\n%d   %d   %d\n\n", example[0][0],example[0][1],example[0][2],example[1][0],example[1][1],example[1][2],example[2][0],example[2][1],example[2][2]);
	
	
	while(555)
	{
		newPosition = 1;
		do{
			do{
                //Changes shape entered after player is switched at the end of this do-while
				if(player == 1)
				{
					shape = 'X';
				}
				else
				{
					shape = 'O';
				}
                //Asks where to enter shape (1-9) (positions indicated in diagram above game)
			printf("Player %d select a position to place your %c : ", player, shape);
			scanf("%d",&position); 
		//Error check position is between 1-9
			}while(position<1 || position>9); 

			//FILL IN 3by3
			if(position == 1 && ttt[0][0] != 'X' && ttt[0][0] != 'O')
			{
				if(player == 1)
				{
					ttt[0][0] = 'X';
				}	
				if(player == 2)
				{
					ttt[0][0] = 'O';
				}
				newPosition = 1;
			}
			else if(position == 2 && ttt[0][2] != 'X' && ttt[0][2] != 'O')
			{
				if(player == 1)
				{
					ttt[0][2] = 'X';
				}
				if(player == 2)
				{
					ttt[0][2] = 'O';
				}
				newPosition = 1;
			}
			else if(position == 3 && ttt[0][4] != 'X' && ttt[0][4] != 'O')
				{
					if(player == 1)
					{
					ttt[0][4] = 'X';
				}
				if(player == 2)
				{
					ttt[0][4] = 'O';
				}
				newPosition = 1;
			}			
			else if(position == 4 && ttt[2][0] != 'X' && ttt[2][0] != 'O')
			{
				if(player == 1)
				{
					ttt[2][0] = 'X';
				}
				if(player == 2)
				{
					ttt[2][0] = 'O';
				}
				newPosition = 1;
			}		
			else if(position == 5 && ttt[2][2] != 'X' && ttt[2][2] != 'O')
			{
				if(player == 1)
				{
					ttt[2][2] = 'X';
				}
				if(player == 2)
				{
					ttt[2][2] = 'O';
				}
				newPosition = 1;
			}	
			else if(position == 6 && ttt[2][4] != 'X' && ttt[2][4] != 'O')
			{
				if(player == 1)
				{
					ttt[2][4] = 'X';
				}
				if(player == 2)
				{
					ttt[2][4] = 'O';
				}
				newPosition = 1;			
			}	
			else if(position == 7 && ttt[4][0] != 'X' && ttt[4][0] != 'O')
			{
				if(player == 1)
				{
					ttt[4][0] = 'X';
				}
				if(player == 2)
				{
					ttt[4][0] = 'O';
				}
				newPosition = 1;
			}
			else if(position == 8 && ttt[4][2] != 'X' && ttt[4][2] != 'O')
			{
				if(player == 1)
				{
					ttt[4][2] = 'X';
				}
				if(player == 2)
				{
					ttt[4][2] = 'O';
				}	
				newPosition = 1;		
			}
			else if(position == 9 && ttt[4][4] != 'X' && ttt[4][4] != 'O')
			{
				if(player == 1)
				{
					ttt[4][4] = 'X';
				}
				if(player == 2)
				{
					ttt[4][4] = 'O';
				}		
				newPosition = 1;
			}	
			else
			{
                //This means that the position they selected already has an x or an o
				newPosition = 2;

			}

		}while(newPosition == 2);
			
		//Prints board with new X or O	
		printf("%c %c %c %c %c\n%c %c %c %c %c\n%c %c %c %c %c\n%c %c %c %c %c\n%c %c %c %c %c\n",ttt[0][0],ttt[0][1],ttt[0][2],ttt[0][3],ttt[0][4],ttt[1][0],ttt[1][1],ttt[1][2],ttt[1][3],ttt[1][4],ttt[2][0],ttt[2][1],ttt[2][2],ttt[2][3],ttt[2][4],ttt[3][0],ttt[3][1],ttt[3][2],ttt[3][3],ttt[3][4],ttt[4][0],ttt[4][1],ttt[4][2],ttt[4][3],ttt[4][4]);
		
		//Below are the ways to win, if there is a winner, the while loop is exited
		
		//X Across 
		if((ttt[0][0]=='X' && ttt[0][2]=='X' && ttt[0][4]=='X') || (ttt[2][0]=='X' && ttt[2][2]=='X' && ttt[2][4]=='X') || (ttt[4][0]=='X' && ttt[4][2]=='X' && ttt[4][4]=='X')) 
		{
			//Winner message and reset board
			wins1 = wins1 + 1;
			printf("Congrats player 1, YOU WIN!!!\n");
			printf("Player 1 wins: %d, Player 2 wins: %d\n\n", wins1, wins2);
			
			for(i=0;i<5;i++)
			{
				for(j=0;j<5;j++)
				{
					if(ttt[i][j] == 'X' || ttt[i][j] == 'O')
					{
					ttt[i][j] = ' ';
					}
				}
			}					
			//Function switch_player
			player = switch_player(player);			
			break;
		}
	
		//O across
		if((ttt[0][0]=='O' && ttt[0][2]=='O' && ttt[0][4]=='O') || (ttt[2][0]=='O' && ttt[2][2]=='O' && ttt[2][4]=='O') || (ttt[4][0]=='O' && ttt[4][2]=='O' && ttt[4][4]=='O')) 
		{
			//Winner message and reset board		
			wins2 = wins2 + 1;
			printf("Congrats player 2, YOU WIN!!!\n");
			printf("Player 1 wins: %d, Player 2 wins: %d\n\n", wins1, wins2);			
			
			for(i=0;i<5;i++)
			{
				for(j=0;j<5;j++)
				{
					if(ttt[i][j] == 'X' || ttt[i][j] == 'O')
					{
					ttt[i][j] = ' ';
					}				
				}
			}			
			//Function switch_player
			player = switch_player(player);
			break;
		}
	
		//X down
		if((ttt[0][0]=='X' && ttt[2][0]=='X' && ttt[4][0]=='X') || (ttt[0][2]=='X' && ttt[2][2]=='X' && ttt[4][2]=='X') || (ttt[0][4]=='X' && ttt[2][4]=='X' && ttt[4][4]=='X')) 
		{
			//Winner message and reset board
			wins1 = wins1 + 1;
			printf("Congrats player 1, YOU WIN!!!\n");
			printf("Player 1 wins: %d, Player 2 wins: %d\n\n", wins1, wins2);	
			
			for(i=0;i<5;i++)
			{
				for(j=0;j<5;j++)
				{
					if(ttt[i][j] == 'X' || ttt[i][j] == 'O')
					{
					ttt[i][j] = ' ';
					}
				}
			}		
			//Function switch_player
			player = switch_player(player);		
			break;
		}
	
		//O down
		if((ttt[0][0]=='O' && ttt[2][0]=='O' && ttt[4][0]=='O') || (ttt[0][2]=='O' && ttt[2][2]=='O' && ttt[4][2]=='O') || (ttt[0][4]=='O' && ttt[2][4]=='O' && ttt[4][4]=='O'))
		{
			//Winner message and reset board
			wins2 = wins2 + 1;
			printf("Congrats player 2, YOU WIN!!!\n");
			printf("Player 1 wins: %d, Player 2 wins: %d\n\n", wins1, wins2);	
			
			for(i=0;i<5;i++)
			{
				for(j=0;j<5;j++)
				{
					if(ttt[i][j] == 'X' || ttt[i][j] == 'O')
					{
					ttt[i][j] = ' ';
					}
				}
			}		
			//Function switch_player
			player = switch_player(player);				
			break;
		}
	
		//X diagnol
		if((ttt[0][0]=='X' && ttt[2][2]=='X' && ttt[4][4]=='X') || (ttt[4][0]=='X' && ttt[2][2]=='X' && ttt[0][4]=='X')) 
		{
			//Winner message and reset board		
			wins1 = wins1 + 1;
			printf("Congrats player 1, YOU WIN!!!\n");
			printf("Player 1 wins: %d, Player 2 wins: %d\n\n", wins1, wins2);	

			for(i=0;i<5;i++)
			{
				for(j=0;j<5;j++)
				{
					if(ttt[i][j] == 'X' || ttt[i][j] == 'O')
					{
					ttt[i][j] = ' ';
					}
				}
			}		
			//Function switch_player
			player = switch_player(player);		
			break;
		}
	
		//O diagnol
		if((ttt[0][0]=='O' && ttt[2][2]=='O' && ttt[4][4]=='O') || (ttt[4][0]=='O' && ttt[2][2]=='O' && ttt[0][4]=='O')) 
		{
			//Winner message and reset board
			wins2 = wins2 + 1;
			printf("Congrats player 2, YOU WIN!!!\n");
			printf("Player 1 wins: %d, Player 2 wins: %d\n\n", wins1, wins2);	

			for(i=0;i<5;i++)
			{
				for(j=0;j<5;j++)
				{
					if(ttt[i][j] == 'X' || ttt[i][j] == 'O')
					{
					ttt[i][j] = ' ';
					}
				}
			}				
			//Function switch_player
			player = switch_player(player);	
			break;
		}
	
		//Checks if tie
		if(ttt[0][0]!=' ' && ttt[0][2]!=' ' && ttt[0][4]!=' ' && ttt[2][0]!=' ' && ttt[2][2]!=' ' && ttt[2][4]!=' ' && ttt[4][0]!=' ' && ttt[4][2]!=' ' && ttt[4][4]!=' ')
		{
			printf("It\'s a tie. \n");
			printf("Player 1 wins: %d, Player 2 wins: %d\n\n", wins1, wins2);		
			
			for(i=0;i<5;i++)
			{
				for(j=0;j<5;j++)
				{
					if(ttt[i][j] == 'X' || ttt[i][j] == 'O')
					{
					ttt[i][j] = ' ';
					}
				}
			}					
			//Function switch_player
			player = switch_player(player);	
			break;
		}

		//Function switch_player
		player = switch_player(player);
	
	}
	
	//Function play_again
	again[0] = play_again(again[0]);
	}
	
}

//Calls the game hangman
void hangMan(void){     //Hangman is a game where one player pics a word another player guesses. The player guessing the word has 6 attempts to do so by only guessing letters.
    int again;
    do{
    printf("Welcome to Hangman! \nThis is a two player experience where one player will input a word, and the other will try to guess it, so grab a friend and get ready!\n");
	
	//Declare vars
	char letter, guessedLetters[100];
	int g=0, len = 0, total=0, passes=0, ch=0;
	
	char a1[6]="|--  ", a2[6]="| |  ", a3[6]="| |  ", a4[6]="|    ", a5[6]="|    ", a6[6]="|    ", a7[6]="|    ", a8[6]="|    ", a9[6]="|    ", a10[6]="|____";
	printf("%s \n%s \n%s \n%s \n%s \n%s \n%s \n%s \n%s \n%s \n\n\n\n", a1, a2, a3, a4, a5, a6, a7, a8, a9, a10);	
	//Ask user for length of word and create vars
	printf("\nFirst player, Enter the length of the word you are going to use: \n");
	scanf("%d", &len);
	char word[len], printWord[len];
	
	//Make the progress shown as "____" when printed to user
	for (int k=0;k<(len);k++){
		printWord[k]='_';
	}
	
	//Ask user for word
	printf("First player, enter your word of choice now: \n");
	scanf("%s", word);
	printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\nWord confirmed!\n\n");
	printf("It is a %d letter word.", len);

	//Allow user to guess letters in word, as well as make them lose if they run out of guesses
	
	do{
		//Ask user for letter and error check to make sure they haven't already guessed it
		int count = 0;

		do{
			printf("\n\nSecond player, enter your letter, don't repeat an old one!\n");
			scanf(" %c", &letter);
			for (int u=0; u<passes; u++){
				if (letter == guessedLetters[u]){
					ch=1;
					break;
				}
				else{
					ch=0;
				}
			}
		}while (ch==1);
		
	
		printf("\n\nYou guessed the letter %c.\n\n", letter);
		
		
		for (int i=0;i<len;i++){
			//Loops through the word, and checks if the guessed letter appears counting the number of times it appears and inputting
			//the letter into the word that gets printed to show the user what they have guessed so far
			if (letter == word[i]){
				printWord[i] = letter;
				count++;
				
			}
		}
			if (count>0){
				//Checks to see if the user guessed any letters correctly, then prints out what they have guessed so far
				printf("\n\nYou guessed %d letter(s) correctly!\n", count);
				printf("So far you have:\n");
				for (int j=0;j<len;j++){
					printf("%c", printWord[j]);
				}
			}
			else{
				//Increases number associated with incorrect guesses if the user did not guess any letters correctly
				g++;
				
				//Change the drawing of the hangman accordingly and print
				switch(g){
					case 1:
						a4[2] = 'O';
						printf("%s \n%s \n%s \n%s \n%s \n%s \n%s \n%s \n%s \n%s \n", a1, a2, a3, a4, a5, a6, a7, a8, a9, a10);
						printf("You now have a head. Be careful.\n\n\n");
						break;
					
					case 2:
						a5[2]='|';
						a6[2]='|';
						printf("%s \n%s \n%s \n%s \n%s \n%s \n%s \n%s \n%s \n%s \n", a1, a2, a3, a4, a5, a6, a7, a8, a9, a10);
						printf("Things are getting serious. You have a body.\n\n\n");
						break;
						
					case 3:
						a5[1]='\\';
						printf("%s \n%s \n%s \n%s \n%s \n%s \n%s \n%s \n%s \n%s \n", a1, a2, a3, a4, a5, a6, a7, a8, a9, a10);
						printf("There's one arm!\n\n\n");
						break;
						
					case 4:
						a5[3]='/';
						printf("%s \n%s \n%s \n%s \n%s \n%s \n%s \n%s \n%s \n%s \n", a1, a2, a3, a4, a5, a6, a7, a8, a9, a10);
						printf("There's the other!\n\n\n");
						break;
						
					case 5:
						a7[1]='/';
						printf("%s \n%s \n%s \n%s \n%s \n%s \n%s \n%s \n%s \n%s \n", a1, a2, a3, a4, a5, a6, a7, a8, a9, a10);
						printf("One leg! Be careful, one more and you're done!\n\n\n");
						break;
						
					case 6:
						a7[3]='\\';
						printf("%s \n%s \n%s \n%s \n%s \n%s \n%s \n%s \n%s \n%s \n", a1, a2, a3, a4, a5, a6, a7, a8, a9, a10);
						printf("Uh Oh!\n\n\n");
						break;
				
				}
				
				printf("That letter is not in the word.");
				printf("\n\nYou have had %d incorrect guesses so far. You have 6 total. Use them wisely!", g);
				printf("So far you have:\n");
				for (int j=0;j<len;j++){
					printf("%c", printWord[j]);
				}
			}

	//Prints letters used so far
	guessedLetters[passes] = letter;
	printf("\nThe letters you have guessed so far are: \n");
	for (int m=0;m<passes+1;m++){
		printf("%c\t", guessedLetters[m]);
	}

	//Checks if either the user has guessed the word or they ran out of guesses
	total = total+count;
	
	//Increment the number of passes through have gone by
	passes++;
	}while (total!=(len) && g<6);
	
	//Checks how the user exited the while loop by either winning or losing and displays the appropriate message
	if (total == (len)){
		printf("\n\nCongratulations! You guessed the whole word correctly without getting hung!\n");
	}
	else{
		printf("\n\nSorry! You ran out of guesses. Better luck next time!\n\n");
	}
	
	//Print out the word just to show the user what it was
	printf("The word was %s\n\n", word);

    printf("Enter a 1 if you would like to play again: ");
    scanf("%d", &again);
    }while(again==1);
}

/////////////////////Switch Player//////////////////////////////
int switch_player(int player)
{
	if(player == 1)
	{
		player = 2;
	}
	else if(player == 2)
	{
		player = 1;
	}
	return(player);
}



/////////////////////TO PLAY AGAIN//////////////////////////////
char play_again(char again)
{
	//Ask to play again
	do{
	printf("Would you like to play again? (y or n) ");
	scanf("%s", &again);
	}while(again!='y' && again!='Y' && again !='n' && again != 'N'); 
	return(again);
}

//Paste functions

//Displays user friendly information
void startGame(void){

    //Variable declaration
    char start = 'x';

    //Welcomes user into the game & prompts for user input
    printf("Welcome to Connect4!\n\nThe aim on this game is to match 4 pieces in any direction in order to win!\nTwo players fight to win, blocking each other's moves, and eventually connecting 4!\n\nPlayer 1 begins first and plays with the \"x\" symbol.\nPlayer 2 plays after, with the \"o\" symbol.\n\nPress x to start:\n");
    scanf(" %c", &start);

    //error checks user input
    while( start != 'x' ){

    //Prompts user for input again
    printf("\nWhenever you are ready to start, enter x:\n");
    scanf(" %c", &start);

}

}

//Allows user to play
void yourTurn(int playerTurn, char row1[], char row2[], char row3[], char row4[], char row5[], char row6[], int locPlayer1[][7], int locPlayer2[][7]){

    //Variables
    int row = 10, column = 10, rowWorks = 0, columnWorks = 0, rowsAvailable[6] = {0,0,0,0,0,0};

    //Calculating which player plays
    playerTurn = playerTurn % 2;

    //Determines which user plays (may work when the user prompted for value before if statement, NOTE TO SELF!!
    if (playerTurn == 0){

        //Prompts player one for input
        printf("\nPlayer One:\nPlease decide where to place your piece.\nFirst, enter the row, noting that the topmost row is 1 and bottommost row is 6.\n");

    } else {

        //Prompts  player two for input
        printf("\nPlayer Two:\nPlease decide where to place your piece.\nFirst, enter the row, noting that the topmost row is 1 and bottommost row is 6.\n");

    }

    //Collects the row from player 1 or 2 and converts it to a format that eases the use of matrixes (since index value = 0)
    scanf("%d", &row);
    row = row - 1;

    //Calls function to determine available rows
    availableRows(locPlayer1, locPlayer2, rowsAvailable);

    //Loop runs again if user input is invalid
    while(rowWorks == 0){

        //Determines if user input matches available row to place connect 4 chip.
        rowWorks = userInputRowChecker(rowsAvailable, row, rowWorks);

        //displays if rowWorks returns back as 0, false/not working.
            if (rowWorks == 0){

                //Prompts user 1 to play, asks for a row to enter
                printf("\nChoose an empty & possible row for your piece.\nRemember that the topmost row is 1 and bottommost row is 6.\n");
                scanf("%d", &row);
                row = row - 1;

            }

        }

        //Asks the user for column and error checks
        printf("\nNow enter the column. \nPlease note that the leftmost column is 1, and rightmost is 7.\n");
        scanf("%d", &column);
        column = column - 1;
        
        //Acts as boolean, where if columnWorks returns false, then the user must re-select an accurate column
        while(columnWorks == 0){

        //Calls the function below which determines if user is able to choose desired column to place play piece (error checks user input)
        columnWorks = userInputColumnChecker(row, column, locPlayer1, locPlayer2, columnWorks);

        //displays if rowWorks returns back as 0, false/not working.
            if (columnWorks == 0){

                //Prompts user 1 to play, asks for a row to enter
                printf("\nPlease enter an available column. \nPlease note that the leftmost column is 1, and rightmost is 7.\n");
                scanf("%d", &column);
                column = column - 1;

            }

        }
    
    //Plugs row and column into player 1's location
    if(playerTurn == 0){

        //Establishes that player 1 played on said spot
        locPlayer1[row][column] = 1;

        //Places an x on the desires row and column  (for future iteration, make the board a matrix as opposed to individual arrays per board)
        if (row == 0){

            row1[column] = 'x';

        } else if (row == 1){

            row2[column] = 'x'; 

        } else if (row == 2){

            row3[column] = 'x';

        } else if (row == 3){

            row4[column] = 'x';

        } else if (row == 4){
        
            row5[column] = 'x';

        } else {

            row6[column] = 'x';

        }

    //Plugs row and column into player 2's Location
    } else if (playerTurn == 1){

        //Establishes that player 1 played on said spot
        locPlayer2[row][column] = 1;

        //Places an o on the desires row and column  (for future iteration, make the board a matrix as opposed to individual arrays per board)
        if (row == 0){

            row1[column] = 'o';

        } else if (row == 1){

            row2[column] = 'o';

        } else if (row == 2){

            row3[column] = 'o';

        } else if (row == 3){

         row4[column] = 'o';

        } else if (row == 4){
        
            row5[column] = 'o';

        } else{

            row6[column] = 'o';

        }

    }

}

//Determines the availableRows, where the user may play. An array of rowsAvailable is returned
void availableRows(int locPlayer1[][7], int locPlayer2[][7], int rowsAvailable[]){

    //Variable declaration
    int rowAvailability5 = 0, rowAvailability4 = 0, rowAvailability3 = 0, rowAvailability2 = 0, rowAvailability1 = 0, rowAvailability0 = 0;

    //Determines if the user's row option is available. In connect 4, you need to place your piece on one of 7 spots per row. Once that row is filled up, it may no longer be played on, similarly, rows that are too far up (meaning no pieces connect to them directly horizontally), are unavailable for play
    if((locPlayer1[5][0] == 0) && (locPlayer1[5][1] == 0) && (locPlayer1[5][2] == 0) && (locPlayer1[5][3] == 0) && (locPlayer1[5][4] == 0) && (locPlayer1[5][5] == 0) && (locPlayer1[5][6] == 0) && (locPlayer2[5][0] == 0) && (locPlayer2[5][1] == 0) && (locPlayer2[5][2] == 0) && (locPlayer2[5][3] == 0) && (locPlayer2[5][4] == 0) && (locPlayer2[5][5] == 0) && (locPlayer2[5][6] == 0)){ 

        //States row 6 is available for play (from top to bottom, 6 being the bottomost row)
        rowsAvailable[5] = 1;

    } else if ((locPlayer1[4][0] == 0) && (locPlayer1[4][1] == 0) && (locPlayer1[4][2] == 0) && (locPlayer1[4][3] == 0) && (locPlayer1[4][4] == 0) && (locPlayer1[4][5] == 0) && (locPlayer1[4][6] == 0) && (locPlayer2[4][0] == 0) && (locPlayer2[4][1] == 0) && (locPlayer2[4][2] == 0) && (locPlayer2[4][3] == 0) && (locPlayer2[4][4] == 0) && (locPlayer2[4][5] == 0) && (locPlayer2[4][6] == 0)){

        //States that row 5 is available for play
        rowsAvailable[4] = 1;

        //Calculates whether an entire row is full 
        rowAvailability5 = locPlayer1[5][0] + locPlayer1[5][1] + locPlayer1[5][2] + locPlayer1[5][3] + locPlayer1[5][4] + locPlayer1[5][5] + locPlayer1[5][6] + locPlayer2[5][0] + locPlayer2[5][1] + locPlayer2[5][2] + locPlayer2[5][3] + locPlayer2[5][4] + locPlayer2[5][5] + locPlayer2[5][6];
        
        //If there is a value occupying each place in the row, rowAvaiability would be == 7.
        if (rowAvailability5 < 7){

            //States that row 6 is available for play
            rowsAvailable[5] = 1;
            
        }

    } else if ((locPlayer1[3][0] == 0) && (locPlayer1[3][1] == 0) && (locPlayer1[3][2] == 0) && (locPlayer1[3][3] == 0) && (locPlayer1[3][4] == 0) && (locPlayer1[3][5] == 0) && (locPlayer1[3][6] == 0) && (locPlayer2[3][0] == 0) && (locPlayer2[3][1] == 0) && (locPlayer2[3][2] == 0) && (locPlayer2[3][3] == 0) && (locPlayer2[3][4] == 0) && (locPlayer2[3][5] == 0) && (locPlayer2[3][6] == 0)){

        //States that row 4 is available for play
        rowsAvailable[3] = 1;

        //Calculates if an entire row is full 
        rowAvailability5 = locPlayer1[5][0] + locPlayer1[5][1] + locPlayer1[5][2] + locPlayer1[5][3] + locPlayer1[5][4] + locPlayer1[5][5] + locPlayer1[5][6] + locPlayer2[5][0] + locPlayer2[5][1] + locPlayer2[5][2] + locPlayer2[5][3] + locPlayer2[5][4] + locPlayer2[5][5] + locPlayer2[5][6];
        rowAvailability4 = locPlayer1[4][0] + locPlayer1[4][1] + locPlayer1[4][2] + locPlayer1[4][3] + locPlayer1[4][4] + locPlayer1[4][5] + locPlayer1[4][6] + locPlayer2[4][0] + locPlayer2[4][1] + locPlayer2[4][2] + locPlayer2[4][3] + locPlayer2[4][4] + locPlayer2[4][5] + locPlayer2[4][6];

        //If there is a value occupying each place in the row, rowAvaiability would be == 7.
        if (rowAvailability5 < 7){

            //States that row 6 is available for play
            rowsAvailable[5] = 1;
            
        }

        //If there is a value occupying each place in the row, rowAvaiability would be == 7.
        if (rowAvailability4 < 7){

            //Checks that the row below has a game piece, this allows the player to place a piece on 
            if(((locPlayer1[5][0] + locPlayer2[5][0]) != (locPlayer1[4][0] + locPlayer2[4][0])) || ((locPlayer1[5][1] + locPlayer2[5][1]) != (locPlayer1[4][1] + locPlayer2[4][1])) || ((locPlayer1[5][2] + locPlayer2[5][2]) != (locPlayer1[4][2] + locPlayer2[4][2])) || ((locPlayer1[5][3] + locPlayer2[5][3]) != (locPlayer1[4][3] + locPlayer2[4][3])) || ((locPlayer1[5][4] + locPlayer2[5][4]) != (locPlayer1[4][4] + locPlayer2[4][4])) || ((locPlayer1[5][5] + locPlayer2[5][5]) != (locPlayer1[4][5] + locPlayer2[4][5])) || ((locPlayer1[5][6] + locPlayer2[5][6]) != (locPlayer1[4][6] + locPlayer2[4][6]))){
                
                //States that row 6 is available for play
                rowsAvailable[4] = 1;
            }
        }


    } else if ((locPlayer1[2][0] == 0) && (locPlayer1[2][1] == 0) && (locPlayer1[2][2] == 0) && (locPlayer1[2][3] == 0) && (locPlayer1[2][4] == 0) && (locPlayer1[2][5] == 0) && (locPlayer1[2][6] == 0) && (locPlayer2[2][0] == 0) && (locPlayer2[2][1] == 0) && (locPlayer2[2][2] == 0) && (locPlayer2[2][3] == 0) && (locPlayer2[2][4] == 0) && (locPlayer2[2][5] == 0) && (locPlayer2[2][6] == 0)){

        //States that row 3 is available for play
        rowsAvailable[2] = 1;

        //Calculates if an entire row is full 
        rowAvailability5 = locPlayer1[5][0] + locPlayer1[5][1] + locPlayer1[5][2] + locPlayer1[5][3] + locPlayer1[5][4] + locPlayer1[5][5] + locPlayer1[5][6] + locPlayer2[5][0] + locPlayer2[5][1] + locPlayer2[5][2] + locPlayer2[5][3] + locPlayer2[5][4] + locPlayer2[5][5] + locPlayer2[5][6];
        rowAvailability4 = locPlayer1[4][0] + locPlayer1[4][1] + locPlayer1[4][2] + locPlayer1[4][3] + locPlayer1[4][4] + locPlayer1[4][5] + locPlayer1[4][6] + locPlayer2[4][0] + locPlayer2[4][1] + locPlayer2[4][2] + locPlayer2[4][3] + locPlayer2[4][4] + locPlayer2[4][5] + locPlayer2[4][6];
        rowAvailability3 = locPlayer1[3][0] + locPlayer1[3][1] + locPlayer1[3][2] + locPlayer1[3][3] + locPlayer1[3][4] + locPlayer1[3][5] + locPlayer1[3][6] + locPlayer2[3][0] + locPlayer2[3][1] + locPlayer2[3][2] + locPlayer2[3][3] + locPlayer2[3][4] + locPlayer2[3][5] + locPlayer2[3][6];


        //If there is a value occupying each place in the row, rowAvaiability would be == 7.
        if (rowAvailability5 < 7){

            //States that row 6 is available for play
            rowsAvailable[5] = 1;
            
        }

        //If there is a value occupying each place in the row, rowAvaiability would be == 7.
        if (rowAvailability4 < 7){

            if(((locPlayer1[5][0] + locPlayer2[5][0]) != (locPlayer1[4][0] + locPlayer2[4][0])) || ((locPlayer1[5][1] + locPlayer2[5][1]) != (locPlayer1[4][1] + locPlayer2[4][1])) || ((locPlayer1[5][2] + locPlayer2[5][2]) != (locPlayer1[4][2] + locPlayer2[4][2])) || ((locPlayer1[5][3] + locPlayer2[5][3]) != (locPlayer1[4][3] + locPlayer2[4][3])) || ((locPlayer1[5][4] + locPlayer2[5][4]) != (locPlayer1[4][4] + locPlayer2[4][4])) || ((locPlayer1[5][5] + locPlayer2[5][5]) != (locPlayer1[4][5] + locPlayer2[4][5])) || ((locPlayer1[5][6] + locPlayer2[5][6]) != (locPlayer1[4][6] + locPlayer2[4][6]))){
                
                //States that row 6 is available for play
                rowsAvailable[4] = 1;
            }
        }

        //If there is a value occupying each place in the row, rowAvaiability would be == 7.
        if (rowAvailability3 < 7){

            if(((locPlayer1[3][0] + locPlayer2[3][0]) != (locPlayer1[4][0] + locPlayer2[4][0])) || ((locPlayer1[3][1] + locPlayer2[3][1]) != (locPlayer1[4][1] + locPlayer2[4][1])) || ((locPlayer1[3][2] + locPlayer2[3][2]) != (locPlayer1[4][2] + locPlayer2[4][2])) || ((locPlayer1[3][3] + locPlayer2[3][3]) != (locPlayer1[4][3] + locPlayer2[4][3])) || ((locPlayer1[3][4] + locPlayer2[3][4]) != (locPlayer1[4][4] + locPlayer2[4][4])) || ((locPlayer1[3][5] + locPlayer2[3][5]) != (locPlayer1[4][5] + locPlayer2[4][5])) || ((locPlayer1[3][6] + locPlayer2[3][6]) != (locPlayer1[4][6] + locPlayer2[4][6]))){
                
                //States that row 6 is available for play
                rowsAvailable[3] = 1;
            }
        }

    } else if ((locPlayer1[1][0] == 0) && (locPlayer1[1][1] == 0) && (locPlayer1[1][2] == 0) && (locPlayer1[1][3] == 0) && (locPlayer1[1][4] == 0) && (locPlayer1[1][5] == 0) && (locPlayer1[1][6] == 0) && (locPlayer2[1][0] == 0) && (locPlayer2[1][1] == 0) && (locPlayer2[1][2] == 0) && (locPlayer2[1][3] == 0) && (locPlayer2[1][4] == 0) && (locPlayer2[1][5] == 0) && (locPlayer2[1][6] == 0)){

        //States that row 2 is available for play
        rowsAvailable[1] = 1;

        //Calculates if an entire row is full 
        rowAvailability5 = locPlayer1[5][0] + locPlayer1[5][1] + locPlayer1[5][2] + locPlayer1[5][3] + locPlayer1[5][4] + locPlayer1[5][5] + locPlayer1[5][6] + locPlayer2[5][0] + locPlayer2[5][1] + locPlayer2[5][2] + locPlayer2[5][3] + locPlayer2[5][4] + locPlayer2[5][5] + locPlayer2[5][6];
        rowAvailability4 = locPlayer1[4][0] + locPlayer1[4][1] + locPlayer1[4][2] + locPlayer1[4][3] + locPlayer1[4][4] + locPlayer1[4][5] + locPlayer1[4][6] + locPlayer2[4][0] + locPlayer2[4][1] + locPlayer2[4][2] + locPlayer2[4][3] + locPlayer2[4][4] + locPlayer2[4][5] + locPlayer2[4][6];
        rowAvailability3 = locPlayer1[3][0] + locPlayer1[3][1] + locPlayer1[3][2] + locPlayer1[3][3] + locPlayer1[3][4] + locPlayer1[3][5] + locPlayer1[3][6] + locPlayer2[3][0] + locPlayer2[3][1] + locPlayer2[3][2] + locPlayer2[3][3] + locPlayer2[3][4] + locPlayer2[3][5] + locPlayer2[3][6];
        rowAvailability2 = locPlayer1[2][0] + locPlayer1[2][1] + locPlayer1[2][2] + locPlayer1[2][3] + locPlayer1[2][4] + locPlayer1[2][5] + locPlayer1[2][6] + locPlayer2[2][0] + locPlayer2[2][1] + locPlayer2[2][2] + locPlayer2[2][3] + locPlayer2[2][4] + locPlayer2[2][5] + locPlayer2[2][6];


        //If there is a value occupying each place in the row, rowAvaiability would be == 7.
        if (rowAvailability5 < 7){

            //States that row 6 is available for play
            rowsAvailable[5] = 1;
            
        }

        //If there is a value occupying each place in the row, rowAvaiability would be == 7.
        if (rowAvailability4 < 7){

            if(((locPlayer1[5][0] + locPlayer2[5][0]) != (locPlayer1[4][0] + locPlayer2[4][0])) || ((locPlayer1[5][1] + locPlayer2[5][1]) != (locPlayer1[4][1] + locPlayer2[4][1])) || ((locPlayer1[5][2] + locPlayer2[5][2]) != (locPlayer1[4][2] + locPlayer2[4][2])) || ((locPlayer1[5][3] + locPlayer2[5][3]) != (locPlayer1[4][3] + locPlayer2[4][3])) || ((locPlayer1[5][4] + locPlayer2[5][4]) != (locPlayer1[4][4] + locPlayer2[4][4])) || ((locPlayer1[5][5] + locPlayer2[5][5]) != (locPlayer1[4][5] + locPlayer2[4][5])) || ((locPlayer1[5][6] + locPlayer2[5][6]) != (locPlayer1[4][6] + locPlayer2[4][6]))){
                
                //States that row 6 is available for play
                rowsAvailable[4] = 1;
            }
        }

        //If there is a value occupying each place in the row, rowAvaiability would be == 7.
        if (rowAvailability3 < 7){

            if(((locPlayer1[3][0] + locPlayer2[3][0]) != (locPlayer1[4][0] + locPlayer2[4][0])) || ((locPlayer1[3][1] + locPlayer2[3][1]) != (locPlayer1[4][1] + locPlayer2[4][1])) || ((locPlayer1[3][2] + locPlayer2[3][2]) != (locPlayer1[4][2] + locPlayer2[4][2])) || ((locPlayer1[3][3] + locPlayer2[3][3]) != (locPlayer1[4][3] + locPlayer2[4][3])) || ((locPlayer1[3][4] + locPlayer2[3][4]) != (locPlayer1[4][4] + locPlayer2[4][4])) || ((locPlayer1[3][5] + locPlayer2[3][5]) != (locPlayer1[4][5] + locPlayer2[4][5])) || ((locPlayer1[3][6] + locPlayer2[3][6]) != (locPlayer1[4][6] + locPlayer2[4][6]))){
                
                //States that row 6 is available for play
                rowsAvailable[3] = 1;
            }
        }

        if (rowAvailability2 < 7){

            if(((locPlayer1[3][0] + locPlayer2[3][0]) != (locPlayer1[2][0] + locPlayer2[2][0])) || ((locPlayer1[3][1] + locPlayer2[3][1]) != (locPlayer1[2][1] + locPlayer2[2][1])) || ((locPlayer1[3][2] + locPlayer2[3][2]) != (locPlayer1[2][2] + locPlayer2[2][2])) || ((locPlayer1[3][3] + locPlayer2[3][3]) != (locPlayer1[2][3] + locPlayer2[2][3])) || ((locPlayer1[3][4] + locPlayer2[3][4]) != (locPlayer1[2][4] + locPlayer2[2][4])) || ((locPlayer1[3][5] + locPlayer2[3][5]) != (locPlayer1[2][5] + locPlayer2[2][5])) || ((locPlayer1[3][6] + locPlayer2[3][6]) != (locPlayer1[2][6] + locPlayer2[2][6]))){
                
                //States that row 6 is available for play
                rowsAvailable[2] = 1;
            }
        }

    } else if ((locPlayer1[0][0] == 0) && (locPlayer1[0][1] == 0) && (locPlayer1[0][2] == 0) && (locPlayer1[0][3] == 0) && (locPlayer1[0][4] == 0) && (locPlayer1[0][5] == 0) && (locPlayer1[0][6] == 0) && (locPlayer2[0][0] == 0) && (locPlayer2[0][1] == 0) && (locPlayer2[0][2] == 0) && (locPlayer2[0][3] == 0) && (locPlayer2[0][4] == 0) && (locPlayer2[0][5] == 0) && (locPlayer2[0][6] == 0)){

        //States that row 1 is available for play
        rowsAvailable[0] = 1;

        //Calculates if an entire row is full 
        rowAvailability5 = locPlayer1[5][0] + locPlayer1[5][1] + locPlayer1[5][2] + locPlayer1[5][3] + locPlayer1[5][4] + locPlayer1[5][5] + locPlayer1[5][6] + locPlayer2[5][0] + locPlayer2[5][1] + locPlayer2[5][2] + locPlayer2[5][3] + locPlayer2[5][4] + locPlayer2[5][5] + locPlayer2[5][6];
        rowAvailability4 = locPlayer1[4][0] + locPlayer1[4][1] + locPlayer1[4][2] + locPlayer1[4][3] + locPlayer1[4][4] + locPlayer1[4][5] + locPlayer1[4][6] + locPlayer2[4][0] + locPlayer2[4][1] + locPlayer2[4][2] + locPlayer2[4][3] + locPlayer2[4][4] + locPlayer2[4][5] + locPlayer2[4][6];
        rowAvailability3 = locPlayer1[3][0] + locPlayer1[3][1] + locPlayer1[3][2] + locPlayer1[3][3] + locPlayer1[3][4] + locPlayer1[3][5] + locPlayer1[3][6] + locPlayer2[3][0] + locPlayer2[3][1] + locPlayer2[3][2] + locPlayer2[3][3] + locPlayer2[3][4] + locPlayer2[3][5] + locPlayer2[3][6];
        rowAvailability2 = locPlayer1[2][0] + locPlayer1[2][1] + locPlayer1[2][2] + locPlayer1[2][3] + locPlayer1[2][4] + locPlayer1[2][5] + locPlayer1[2][6] + locPlayer2[2][0] + locPlayer2[2][1] + locPlayer2[2][2] + locPlayer2[2][3] + locPlayer2[2][4] + locPlayer2[2][5] + locPlayer2[2][6];
        rowAvailability1 = locPlayer1[1][0] + locPlayer1[1][1] + locPlayer1[1][2] + locPlayer1[1][3] + locPlayer1[1][4] + locPlayer1[1][5] + locPlayer1[1][6] + locPlayer2[1][0] + locPlayer2[1][1] + locPlayer2[1][2] + locPlayer2[1][3] + locPlayer2[1][4] + locPlayer2[1][5] + locPlayer2[1][6];


        //If there is a value occupying each place in the row, rowAvaiability would be == 7.
        if (rowAvailability5 < 7){

            //States that row 6 is available for play
            rowsAvailable[5] = 1;
            
        }

        //If there is a value occupying each place in the row, rowAvaiability would be == 7.
        if (rowAvailability4 < 7){

            if(((locPlayer1[5][0] + locPlayer2[5][0]) != (locPlayer1[4][0] + locPlayer2[4][0])) || ((locPlayer1[5][1] + locPlayer2[5][1]) != (locPlayer1[4][1] + locPlayer2[4][1])) || ((locPlayer1[5][2] + locPlayer2[5][2]) != (locPlayer1[4][2] + locPlayer2[4][2])) || ((locPlayer1[5][3] + locPlayer2[5][3]) != (locPlayer1[4][3] + locPlayer2[4][3])) || ((locPlayer1[5][4] + locPlayer2[5][4]) != (locPlayer1[4][4] + locPlayer2[4][4])) || ((locPlayer1[5][5] + locPlayer2[5][5]) != (locPlayer1[4][5] + locPlayer2[4][5])) || ((locPlayer1[5][6] + locPlayer2[5][6]) != (locPlayer1[4][6] + locPlayer2[4][6]))){
                
                //States that row 6 is available for play
                rowsAvailable[4] = 1;
            }
        }

        //If there is a value occupying each place in the row, rowAvaiability would be == 7.
        if (rowAvailability3 < 7){

            if(((locPlayer1[3][0] + locPlayer2[3][0]) != (locPlayer1[4][0] + locPlayer2[4][0])) || ((locPlayer1[3][1] + locPlayer2[3][1]) != (locPlayer1[4][1] + locPlayer2[4][1])) || ((locPlayer1[3][2] + locPlayer2[3][2]) != (locPlayer1[4][2] + locPlayer2[4][2])) || ((locPlayer1[3][3] + locPlayer2[3][3]) != (locPlayer1[4][3] + locPlayer2[4][3])) || ((locPlayer1[3][4] + locPlayer2[3][4]) != (locPlayer1[4][4] + locPlayer2[4][4])) || ((locPlayer1[3][5] + locPlayer2[3][5]) != (locPlayer1[4][5] + locPlayer2[4][5])) || ((locPlayer1[3][6] + locPlayer2[3][6]) != (locPlayer1[4][6] + locPlayer2[4][6]))){
                
                //States that row 6 is available for play
                rowsAvailable[3] = 1;
            }
        }

        if (rowAvailability2 < 7){

            if(((locPlayer1[3][0] + locPlayer2[3][0]) != (locPlayer1[2][0] + locPlayer2[2][0])) || ((locPlayer1[3][1] + locPlayer2[3][1]) != (locPlayer1[2][1] + locPlayer2[2][1])) || ((locPlayer1[3][2] + locPlayer2[3][2]) != (locPlayer1[2][2] + locPlayer2[2][2])) || ((locPlayer1[3][3] + locPlayer2[3][3]) != (locPlayer1[2][3] + locPlayer2[2][3])) || ((locPlayer1[3][4] + locPlayer2[3][4]) != (locPlayer1[2][4] + locPlayer2[2][4])) || ((locPlayer1[3][5] + locPlayer2[3][5]) != (locPlayer1[2][5] + locPlayer2[2][5])) || ((locPlayer1[3][6] + locPlayer2[3][6]) != (locPlayer1[2][6] + locPlayer2[2][6]))){
                
                //States that row 6 is available for play
                rowsAvailable[2] = 1;
            }
        }

        if (rowAvailability1 < 7){

            if(((locPlayer1[1][0] + locPlayer2[1][0]) != (locPlayer1[2][0] + locPlayer2[2][0])) || ((locPlayer1[1][1] + locPlayer2[1][1]) != (locPlayer1[2][1] + locPlayer2[2][1])) || ((locPlayer1[1][2] + locPlayer2[1][2]) != (locPlayer1[2][2] + locPlayer2[2][2])) || ((locPlayer1[1][3] + locPlayer2[1][3]) != (locPlayer1[2][3] + locPlayer2[2][3])) || ((locPlayer1[1][4] + locPlayer2[1][4]) != (locPlayer1[2][4] + locPlayer2[2][4])) || ((locPlayer1[1][5] + locPlayer2[1][5]) != (locPlayer1[2][5] + locPlayer2[2][5])) || ((locPlayer1[1][6] + locPlayer2[1][6]) != (locPlayer1[2][6] + locPlayer2[2][6]))){
                
                //States that row 6 is available for play
                rowsAvailable[1] = 1;
            }
        }

    } else {

        //States that row 1 is available for play -- Since no row can be guaranteed free, this condition does not apply for this possibility
        //rowsAvailable[0] = 1;

        //Calculates if an entire row is full 
        rowAvailability5 = locPlayer1[5][0] + locPlayer1[5][1] + locPlayer1[5][2] + locPlayer1[5][3] + locPlayer1[5][4] + locPlayer1[5][5] + locPlayer1[5][6] + locPlayer2[5][0] + locPlayer2[5][1] + locPlayer2[5][2] + locPlayer2[5][3] + locPlayer2[5][4] + locPlayer2[5][5] + locPlayer2[5][6];
        rowAvailability4 = locPlayer1[4][0] + locPlayer1[4][1] + locPlayer1[4][2] + locPlayer1[4][3] + locPlayer1[4][4] + locPlayer1[4][5] + locPlayer1[4][6] + locPlayer2[4][0] + locPlayer2[4][1] + locPlayer2[4][2] + locPlayer2[4][3] + locPlayer2[4][4] + locPlayer2[4][5] + locPlayer2[4][6];
        rowAvailability3 = locPlayer1[3][0] + locPlayer1[3][1] + locPlayer1[3][2] + locPlayer1[3][3] + locPlayer1[3][4] + locPlayer1[3][5] + locPlayer1[3][6] + locPlayer2[3][0] + locPlayer2[3][1] + locPlayer2[3][2] + locPlayer2[3][3] + locPlayer2[3][4] + locPlayer2[3][5] + locPlayer2[3][6];
        rowAvailability2 = locPlayer1[2][0] + locPlayer1[2][1] + locPlayer1[2][2] + locPlayer1[2][3] + locPlayer1[2][4] + locPlayer1[2][5] + locPlayer1[2][6] + locPlayer2[2][0] + locPlayer2[2][1] + locPlayer2[2][2] + locPlayer2[2][3] + locPlayer2[2][4] + locPlayer2[2][5] + locPlayer2[2][6];
        rowAvailability1 = locPlayer1[1][0] + locPlayer1[1][1] + locPlayer1[1][2] + locPlayer1[1][3] + locPlayer1[1][4] + locPlayer1[1][5] + locPlayer1[1][6] + locPlayer2[1][0] + locPlayer2[1][1] + locPlayer2[1][2] + locPlayer2[1][3] + locPlayer2[1][4] + locPlayer2[1][5] + locPlayer2[1][6];
        rowAvailability0 = locPlayer1[0][0] + locPlayer1[0][1] + locPlayer1[0][2] + locPlayer1[0][3] + locPlayer1[0][4] + locPlayer1[0][5] + locPlayer1[0][6] + locPlayer2[0][0] + locPlayer2[0][1] + locPlayer2[0][2] + locPlayer2[0][3] + locPlayer2[0][4] + locPlayer2[0][5] + locPlayer2[0][6];


        //If there is a value occupying each place in the row, rowAvaiability would be == 7.
        if (rowAvailability5 < 7){

            //States that row 6 is available for play
            rowsAvailable[5] = 1;
            
        }

        //If there is a value occupying each place in the row, rowAvaiability would be == 7.
        if (rowAvailability4 < 7){

            if(((locPlayer1[5][0] + locPlayer2[5][0]) != (locPlayer1[4][0] + locPlayer2[4][0])) || ((locPlayer1[5][1] + locPlayer2[5][1]) != (locPlayer1[4][1] + locPlayer2[4][1])) || ((locPlayer1[5][2] + locPlayer2[5][2]) != (locPlayer1[4][2] + locPlayer2[4][2])) || ((locPlayer1[5][3] + locPlayer2[5][3]) != (locPlayer1[4][3] + locPlayer2[4][3])) || ((locPlayer1[5][4] + locPlayer2[5][4]) != (locPlayer1[4][4] + locPlayer2[4][4])) || ((locPlayer1[5][5] + locPlayer2[5][5]) != (locPlayer1[4][5] + locPlayer2[4][5])) || ((locPlayer1[5][6] + locPlayer2[5][6]) != (locPlayer1[4][6] + locPlayer2[4][6]))){
                
                //States that row 6 is available for play
                rowsAvailable[4] = 1;
            }
        }

        //If there is a value occupying each place in the row, rowAvaiability would be == 7.
        if (rowAvailability3 < 7){

            if(((locPlayer1[3][0] + locPlayer2[3][0]) != (locPlayer1[4][0] + locPlayer2[4][0])) || ((locPlayer1[3][1] + locPlayer2[3][1]) != (locPlayer1[4][1] + locPlayer2[4][1])) || ((locPlayer1[3][2] + locPlayer2[3][2]) != (locPlayer1[4][2] + locPlayer2[4][2])) || ((locPlayer1[3][3] + locPlayer2[3][3]) != (locPlayer1[4][3] + locPlayer2[4][3])) || ((locPlayer1[3][4] + locPlayer2[3][4]) != (locPlayer1[4][4] + locPlayer2[4][4])) || ((locPlayer1[3][5] + locPlayer2[3][5]) != (locPlayer1[4][5] + locPlayer2[4][5])) || ((locPlayer1[3][6] + locPlayer2[3][6]) != (locPlayer1[4][6] + locPlayer2[4][6]))){
                
                //States that row 6 is available for play
                rowsAvailable[3] = 1;
            }
        }

        if (rowAvailability2 < 7){

            if(((locPlayer1[3][0] + locPlayer2[3][0]) != (locPlayer1[2][0] + locPlayer2[2][0])) || ((locPlayer1[3][1] + locPlayer2[3][1]) != (locPlayer1[2][1] + locPlayer2[2][1])) || ((locPlayer1[3][2] + locPlayer2[3][2]) != (locPlayer1[2][2] + locPlayer2[2][2])) || ((locPlayer1[3][3] + locPlayer2[3][3]) != (locPlayer1[2][3] + locPlayer2[2][3])) || ((locPlayer1[3][4] + locPlayer2[3][4]) != (locPlayer1[2][4] + locPlayer2[2][4])) || ((locPlayer1[3][5] + locPlayer2[3][5]) != (locPlayer1[2][5] + locPlayer2[2][5])) || ((locPlayer1[3][6] + locPlayer2[3][6]) != (locPlayer1[2][6] + locPlayer2[2][6]))){
                
                //States that row 6 is available for play
                rowsAvailable[2] = 1;
            }
        }

        if (rowAvailability1 < 7){

            if(((locPlayer1[1][0] + locPlayer2[1][0]) != (locPlayer1[2][0] + locPlayer2[2][0])) || ((locPlayer1[1][1] + locPlayer2[1][1]) != (locPlayer1[2][1] + locPlayer2[2][1])) || ((locPlayer1[1][2] + locPlayer2[1][2]) != (locPlayer1[2][2] + locPlayer2[2][2])) || ((locPlayer1[1][3] + locPlayer2[1][3]) != (locPlayer1[2][3] + locPlayer2[2][3])) || ((locPlayer1[1][4] + locPlayer2[1][4]) != (locPlayer1[2][4] + locPlayer2[2][4])) || ((locPlayer1[1][5] + locPlayer2[1][5]) != (locPlayer1[2][5] + locPlayer2[2][5])) || ((locPlayer1[1][6] + locPlayer2[1][6]) != (locPlayer1[2][6] + locPlayer2[2][6]))){
                
                //States that row 6 is available for play
                rowsAvailable[1] = 1;
            }
        }

        if (rowAvailability0 < 7){

            if(((locPlayer1[1][0] + locPlayer2[1][0]) != (locPlayer1[0][0] + locPlayer2[0][0])) || ((locPlayer1[1][1] + locPlayer2[1][1]) != (locPlayer1[0][1] + locPlayer2[0][1])) || ((locPlayer1[1][2] + locPlayer2[1][2]) != (locPlayer1[0][2] + locPlayer2[0][2])) || ((locPlayer1[1][3] + locPlayer2[1][3]) != (locPlayer1[0][3] + locPlayer2[0][3])) || ((locPlayer1[1][4] + locPlayer2[1][4]) != (locPlayer1[0][4] + locPlayer2[0][4])) || ((locPlayer1[1][5] + locPlayer2[1][5]) != (locPlayer1[0][5] + locPlayer2[0][5])) || ((locPlayer1[1][6] + locPlayer2[1][6]) != (locPlayer1[0][6] + locPlayer2[0][6]))){
                
                //States that row 6 is available for play
                rowsAvailable[0] = 1;
            }
        }

    }


}

//Gets variables related to rows and determines if user's row input is eligible
int userInputRowChecker(int rowsAvailable[], int row, int rowWorks){

    //Determines if player may place a piece on the 5th row
    if (row == 5){
            
            //If row avaiable, rowWorks set to true (1), if unavailable, set to flase (0)
            if (rowsAvailable[5] == 1){
                
                rowWorks = 1;

            } else {

                rowWorks = 0;

            }

    //Determines if player may place a piece on the 4th row
    } else if (row == 4){

            //If row avaiable, rowWorks set to true (1), if unavailable, set to flase (0)
            if (rowsAvailable[4] == 1){
                
                rowWorks = 1;

            } else {

                rowWorks = 0;

            }

    //Determines if player may place a piece on the 3rd row
    } else if (row == 3){

            //If row avaiable, rowWorks set to true (1), if unavailable, set to flase (0)
            if (rowsAvailable[3] == 1){
                
                rowWorks = 1;

            } else {

                rowWorks = 0;

            }

    //Determines if player may place a piece on the 2nd row
    } else if (row == 2){

            //If row avaiable, rowWorks set to true (1), if unavailable, set to flase (0)
            if (rowsAvailable[2] == 1){
                
                rowWorks = 1;

            } else {

                rowWorks = 0;

            }

    //Determines if player may place a piece on the 1st row
    } else if (row == 1){

            //If row avaiable, rowWorks set to true (1), if unavailable, set to flase (0)
            if (rowsAvailable[1] == 1){
            
                rowWorks = 1;

            } else {

                rowWorks = 0;

            }

    //Determines if player may place a piece on the 0th row (top most)
    } else if (row == 0){

            //If row avaiable, rowWorks set to true (1), if unavailable, set to flase (0)
            if (rowsAvailable[0] == 1){
                
                rowWorks = 1;

            } else {

                rowWorks = 0;

            }

    }

    //return rowWorks, informing user whether their desired row works or not
    return rowWorks;

}

//Gets the user given row and determines what the 
int userInputColumnChecker(int row, int column, int locPlayer1[][7], int locPlayer2[][7], int columnWorks){

    //This condition checks the spot and if filled, prevents user from playing there
    if(locPlayer1[row][column] == 1 || locPlayer2[row][column] == 1){

        columnWorks = 0;

    //If spot is empty, other conditions must be met first
    } else if (locPlayer1[row][column] == 0 && locPlayer2[row][column] == 0){

        //Ensures that spot is playable
        if (locPlayer1[(row+1)][column] == 1 || locPlayer2[(row+1)][column] == 1){

            //Allows user to place game piece on that spot
            columnWorks = 1;
            
        //Special rules for row 5 (the bottom most row). At start of game, user is able to place a piece there as long as there are no pieces there (as confirmed by row & column Works)
        } else if ((row == 5 && column == 0) || (row == 5 && column == 1) || (row == 5 && column == 2) || (row == 5 && column == 3) || (row == 5 && column == 4) || (row == 5 && column == 5) || (row == 5 && column == 6)){

            //Allows user to place game piece on that spot
            columnWorks = 1;

        } else {

            /*If for whatever reason the above conditions are not satisfied, an error is printed.
                User should then select an eligible column. ()*/ 
            printf("\nERROR: Please enter a column on the selected row, that is available.\n");
            columnWorks = 0;

        }

    } 

    //Don't forget to include return statement for non-array value
    return columnWorks;
}

//Function returns the status of the game: not yet victorious, a player has won, a tie has occured.
int victoryChecker(int gameOver, int locPlayer1[][7], int locPlayer2[][7]){

    //Note to self: Use switch case to determine outcomes in main, (not yet victory == 0, victory player1 == 1, victory player2 == 2, draw[(locPlayer1 + 2) == 42] == 3).

    //Variables
    int sumAll = 0;



    //Adding up all numbers in both "Player" boards to determine if they are filled up
    for(int i = 0; i < 6; i++){
        for(int j = 0; j < 7; j++){

            /*If sumAll == 42, then the board is full, and game is a draw. 
            Before reaching that conclusion, however, it must be determined 
            if the player won on the last piece "drop". */
            sumAll = sumAll + locPlayer1[i][j] + locPlayer2[i][j];

        }
    }

    //If-statement + for loops determine if a column win is present
    for(int i = 0; i < 7; i++){
        for(int j = 0; j < 3; j++){

            //If gameOver changes declaration to 1, playerOne wins
            if((locPlayer1[(0+j)][i] + locPlayer1[(1+j)][i] + locPlayer1[(2+j)][i] + locPlayer1[(3+j)][i]) == 4){
                gameOver = 1;
                //printf("\nF\n");

            }

            ///If gameOver changes declaration to 2, playerTwo wins
            if((locPlayer2[(0+j)][i] + locPlayer2[(1+j)][i] + locPlayer2[(2+j)][i] + locPlayer2[(3+j)][i]) == 4){
                gameOver = 2;
                //printf("\nFi\n");

            }
        }
    }

    //If statement + for loops determine if a row win is present
    for(int i = 0; i < 6; i++){
        for(int j = 0; j < 4; j++){

            //If gameOver changes declaration to 1, playerOne wins
            if((locPlayer1[i][(0+j)] + locPlayer1[i][(1+j)] + locPlayer1[i][(2+j)] + locPlayer1[i][(3+j)]) == 4){
                gameOver = 1;
                //printf("\nFir\n");
            }

            //If gameOver changes declaration to 2, playerTwo wins
            if((locPlayer2[i][(0+j)] + locPlayer2[i][(1+j)] + locPlayer2[i][(2+j)] + locPlayer2[i][(3+j)]) == 4){
                gameOver = 2;
                //printf("\nFirs\n");

            }

        }
    }

    //If statement + for loops determine if an downwards-diagonal win is present
    for(int i = 0; i < 4; i++){
        for(int j = 0; j < 3; j++){

            //If gameOver changes declaration to 1, playerOne wins
            if((locPlayer1[j][i] + locPlayer1[(j+1)][(i+1)] + locPlayer1[(j+2)][(i+2)] + locPlayer1[(j+3)][(i+3)]) == 4){
                gameOver = 1;
            //printf("\nFirst\n");
            }

            //If gameOver changes declaration to 1, playerOne wins
            if((locPlayer2[j][i] + locPlayer2[(j+1)][(i+1)] + locPlayer2[(j+2)][(i+2)] + locPlayer2[(j+3)][(i+3)]) == 4){
                gameOver = 2;
            //printf("\nFist lr\n");

            }
        }
    }

    //If statement + for loops determine if an upwards-diagonal win is present
    for(int i = 0; i < 4; i++){
        for(int j = 0; j < 3; j++){

            //If gameOver changes declaration to 1, playerOne wins
            if((locPlayer1[(5-j)][i] + locPlayer1[(4-j)][(i+1)] + locPlayer1[(3-j)][(i+2)] + locPlayer1[(2-j)][(i+3)]) == 4){
                gameOver = 1;
            //printf("\nFist lrer\n");

             }

                //If gameOver changes declaration to 1, playerOne wins
            if((locPlayer2[(5-j)][i] + locPlayer2[(4-j)][(i+1)] + locPlayer2[(3-j)][(i+2)] + locPlayer2[(2-j)][(i+3)]) == 4){
                gameOver = 2;
            //printf("\nFist lrww\n");

            }

        }
    }

    /*
    
        Determined the for loop "formulas" for victory for the trickier diagonal 
        rows by drawing all the winning possiblities in a notebook and observing 
        for patterns, which there were.
    
    */

    //If the entire board is full and no one won in the last round, a draw is called
    if (sumAll == 42 && gameOver == 0){

        gameOver = 3;
                //printf("\nFist lrwwwwwwwww\n");

    } 

    //Returns an int value indicating the status of the game
    return gameOver;
}

//Displays the standing of the game to the terminal/screen
void dispBoard(char row1[], char row2[], char row3[], char row4[], char row5[], char row6[]){

    //Displays the board to enhance user experience (might have to remove one space at end) - done
    //Top row (1)
    printf("\n\n1 |");
    for(int i = 0; i < 6; i++){
    printf("%c ", row1[i]);
    }
    printf("%c", row1[6]);
    printf("|\n");

    //row (2)
    printf("2 |");
    for(int i = 0; i < 6; i++){
    printf("%c ", row2[i]);
    }
    printf("%c", row2[6]);
    printf("|\n");

    //row (3)
    printf("3 |");
    for(int i = 0; i < 6; i++){
    printf("%c ", row3[i]);
    }
    printf("%c", row3[6]);
    printf("|\n");

    //row (4)
    printf("4 |");
    for(int i = 0; i < 6; i++){
    printf("%c ", row4[i]);
    }
    printf("%c", row4[6]);
    printf("|\n");

    //row (5)
    printf("5 |");
    for(int i = 0; i < 6; i++){
    printf("%c ", row5[i]);
    }
    printf("%c", row5[6]);
    printf("|\n");

    //Bottom row (6)
    printf("6 |");
    for(int i = 0; i < 6; i++){
    printf("%c", row6[i]);
    printf(" ");
    }
    printf("%c", row6[6]);
    printf("|\n");

    printf("  ⁻⁻⁻⁻⁻⁻⁻⁻⁻⁻⁻⁻⁻⁻⁻\n");
    printf("   1 2 3 4 5 6 7\n");
    /*
       1 |● ○ ○ ● ○ ● ○|
       2 |● ○ ○ ● ○ ● ○|
       3 |● ○ ○ ● ○ ● ○|
       4 |● ○ ○ ● ○ ● ○|
       5 |● ○ ○ ● ○ ● ○|
       6 |● ○ ○ ● ○ ● ○|  <- Format to Follow (include numbers?) - yes
         ⁻⁻⁻⁻⁻⁻⁻⁻⁻⁻⁻⁻⁻⁻⁻
          1 2 3 4 5 6 7
    */

    }

//Function displays print statements associated with the final status of the Connect4 game6
void podium(int gameOver){

    //Switch case displays result of game
    switch(gameOver){

        //Uses int gameOver, altered in victoryChecker function, to display status of game.
        //Player 1 wins
        case 1:

            printf("\nPlayer One has won. Congratulations!!!\n\n");
            break;

        //Player 2 wins
        case 2:
            printf("\nPlayer Two has won. Congratulations!!!\n\n");
            break;

        //Player 3 wins
        case 3:
            printf("\nGame is a tie.\n\n");

            //no break required here
    }

}

//Function grants user the option to play again if the user wishes. There is also an easter egg our group created for fun.
int juegaAgain(int playAgain){

    //Variable declaration
    char userInput;
    char guessOne;
    char guessTwo;
    char guessThree;
    char guessFour;
    int attempt = 0;

    //As long as user input does not match y, Y, n, or N, this do-while loop repeats
    //Error checks user input
    do{

        if(attempt > 0){

            printf("\nPlease be sure your input is accurate.");

        }

        //Obtains user input
        printf("\nWould you like to play again? Enter the character y or n for yes or no respectively.\n");
        scanf(" %c", &userInput);

        //Jake Easter Egg, must store a 'j', 'a', 'k', and 'e' in the corresponding guesses to call the function jake
        if(attempt == 0){

            guessOne = userInput;

        } else if (attempt == 1){

            guessTwo = userInput;

        } else if (attempt == 2){

            guessThree = userInput;

        } else if (attempt == 3){

            guessFour = userInput;

        }

        //if the user guesses 'j', 'a', 'k', & 'e' in order, then the easter egg jake is called, which proceed to exit the program
        if(guessOne == 'j' && guessTwo == 'a' && guessThree == 'k' && guessFour == 'e'){

            //Calls function jake
            jake();

        }

        //counter
        attempt++;

    } while(userInput != 'N' && userInput != 'n' && userInput != 'Y' && userInput != 'y');

    //Determines the value of playAgain, according to user input
    if(userInput == 'y' || userInput == 'Y'){

        playAgain = 1;

    } else if (userInput == 'N' || userInput == 'n'){

        playAgain = 0;

    }

    printf("\n");

    /* For a future iteration, I would modify the program, where the only input
    by either user would be the row they wish to drop their game piece. It would
    potentially simplify the code and enhance the user experience*/

    //returns user desire to repeat this specific game
    return playAgain;
}

//Jake Easter Egg
void jake(void){

    //variables
    int run = 0;

        //Loop prints "jake jake jake jake jake" a total of 70 times. Writing jake 350 times
        while(1){
            printf("\njake jake jake jake jake\n");
            run++;

            if(run == 70)
                break;
        }

    //Exits program, meaning that to play this, or other games, the program must be debugged again.
    exit(9999);

}

//Thank you for viewing our program.
/*

    We would also like to thank Dr. Mena for an astounding semester. We learned an immesurable amount of knowledge thanks
    to her efforts. She built our foundation for the programs C and MATLAB and for that, we are eternally grateful. As future
    computer engineers, we found this course alligned with our passion, and gave us a better understanding of the software
    side of computer engineering. We appreciate it!

*/