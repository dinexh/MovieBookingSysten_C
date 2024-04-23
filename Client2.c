#include<stdio.h>
#include<stdlib.h>
#include <unistd.h>

void board(char square[]);
int playGame();
int checkWin(char square[]);
int ComputerMove(char square[]);

int player = 0;
char replace;

//LOGIC OF THE GAME
int playGame() {
    char square[]={'1', '2', '3', '4', '5', '6', '7', '8', '9'};
    char quit,exit;
    int GameStatus=1,opt,fill=0,invalid=0;

    board(square);

    while (GameStatus == 1) {
        player++;

        if (fill == 1) {
            printf("Space Filled! Try again\n");
            fill--;
        }

        if (invalid == 1) {
            printf("Invalid Move! Try again\n");
            invalid--;
        }

        player = (player % 2 != 0) ? 1 : 2;
        replace = (player == 1) ? 'X' : 'O';
		
		if(player==1){
			printf("Player %d [%c] turn: ", player, replace);
        	scanf("%d", &opt);
		}
		else{
			printf("Computer [%c] turn: ",replace);	
			sleep(1);
			opt=ComputerMove(square);
			printf("%d",opt);
			sleep(1);		
		}
        
        if (opt >= 0 && opt <= 9) {
            if (opt == 0) {
                do{
                	printf("Are you sure you want to quit?(y/n): ");
                	scanf(" %c", &quit);
				}while(quit!='y'&&quit!='n');
                if (quit == 'y') {
                    printf("\n-----You quit the game-----\n");
                    break;
                } else {
                    player--;
                }
            } else {
                opt--;
                if (square[opt] != 'X' && square[opt] != 'O') {
                    square[opt] = replace;
                } else {
                    fill = 1;
                    player--;
                }
            }
        }
		else {
            invalid = 1;
            player--;
        }

        board(square);
        GameStatus = checkWin(square);
        if(GameStatus==2)
        	printf("\n------- Player %d[%c] Winner -------\n", player, replace);
        else if(GameStatus==3)
        	printf("\n------- Draw -------\n");
    }
	do{
		printf("Do you want to exit?(y/n): ");
    	scanf(" %c", &exit); 
	}while(exit!= 'y' && exit!= 'n');
    if (exit == 'n') {
        playGame();
    }
}

//DISPLAYING THE BOARD
void board(char square[]) {
    system("cls");
    printf("\n=========== Tic Tac Toe ===========\n");
    printf("\n---------Instructions--------------\n");
    printf("\n 1) Use the numbers to replace symbol ");
    printf("\n 2)Press 0 to quit \n");
    printf("-----------------------\n\n");
    printf("\n\n\t     |     |   \n");
    printf("\t   %c |  %c  |  %c  \n", square[0], square[1], square[2]);
    printf("\t_____|_____|______\n");
    printf("\t     |     |     \n");
    printf("\t   %c |  %c  |  %c  \n", square[3], square[4], square[5]);
    printf("\t_____|_____|______\n");
    printf("\t     |     |     \n");
    printf("\t   %c |  %c  |  %c  \n", square[6], square[7], square[8]);
    printf("\t     |     |   \n\n");
}

//CONDTION TO FINISH THE GAME
int checkWin(char square[]) {
    if ((square[0] == square[1] && square[1] == square[2]) ||
        (square[3] == square[4] && square[4] == square[5]) ||
        (square[6] == square[7] && square[7] == square[8])) {
        return 2;
    } 
	else if ((square[0] == square[4] && square[4] == square[8]) ||
               (square[2] == square[4] && square[4] == square[6])) {
        return 2;
    }
	else if ((square[0] == square[3] && square[3] == square[6]) ||
               (square[1] == square[4] && square[4] == square[7]) ||
               (square[2] == square[5] && square[5] == square[8])) {
        return 2;
    } 
	else if (square[0] != '1' && square[1] != '2' && square[2] != '3' &&
               square[3] != '4' && square[4] != '5' && square[5] != '6' &&
               square[6] != '7' && square[7] != '8' && square[8] != '9') {
        return 3;
    } 
	else {
        return 1;
    }
}

//lOGIC FOR COMPUTER MOVE
int ComputerMove(char square[]){
	char temp;
	int random;
	//	WINNING CONDITION FOR COMPUTER
	for(int i=0;i<9;i++){
		if(square[i]!='X'&&square[i]!='O'){
			temp=square[i];
			square[i]='O';
			if(checkWin(square)==2){
				square[i]=temp;	
				return i+1;
			}
			square[i]=temp;
		}
	}
	// BLOCKING CONDITION FOR OPPONENT
	 for (int i = 0; i < 9; i++) {
        if (square[i] != 'X' && square[i] != 'O') {
            temp = square[i];
            square[i] = 'X';
            if (checkWin(square) == 2) {
                square[i] = temp;
                return i + 1;
            }
            square[i] = temp;
        }
    }
	// TAKING CENTER
	if(square[4]=='5'){
		return 5;
	}
	// RANDOM MOVE
	while(1){
		srand(time(0));
		random = rand()%8;   
		if(square[random]!='X'&&square[random]!='O'){
			return random+1;
		}
	}	
}

int main() {
    playGame();
    printf("\n\t===== Thank You =====");
    return 0;
}