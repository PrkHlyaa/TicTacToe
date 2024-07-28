#include <time.h>
#include <conio.h>
#include <stdio.h>
#include <windows.h>
#include <stdlib.h>
#include <string.h>

#include "tiktaktu.h"

#define true 1
#define false 0

Data BotHistory[11];
Data PlayerHistory[11];

char board[7][7];
int boardSize = 3;
int lawan, i;
char Player1[50];
char Player2[50];
char player1[50];
char player2[50];

void gameplay(int *turn, int *winner)
{
	resetBoard();
	*turn = 1;
	*winner = 0;
	while (moveExist() && *winner == 0)
	{
		if (moveExist() && *winner == 0)
		{
			header();
			printBoard();
			drawSymbol(*turn);
			*turn = 2;
			*winner = checkWinner();
			
			system("cls");
		}
		if (moveExist() && *winner == 0)
		{
			header();
			printBoard();
			if (lawan == 2)
			{
				drawSymbol(*turn);
			}
			else if (lawan == 3)
			{
				bot();
			}
			*turn = 1;
			*winner = checkWinner();
			
			system("cls");	
		}	
	}
}

void displayScoreBoard(){
	int lawan; 
	while (true){
		printf("(1) vsBOT\t\t\t (2) vsPlayer\n");
		printf("\tInput: \t");
		scanf("%d", &lawan);
		
		if((lawan == 1)||(lawan == 2)){
			break;
		}
		printf("\nMasukkan angka yang sesuai\n");
		printf("Tekan enter untuk melanjutkan!\n");
		while (!kbhit()){}
		
		system ("cls");
	}
	
	if (lawan == 1){ // vsBOT
		FILE *bot = fopen("scoreBoard_bot.txt","r");
		if (!bot){
			printf("Data kosong, mainkan setidaknya 1 permainan!\n");
			printf("Tekan enter untuk melanjutkan!\n");
			while(!kbhit()){}
			return;
		} else {
  		    fread(BotHistory, sizeof (Data), 11, bot);
			system("cls");
			printf("TOP 10 VS BOT SCOREBOARD\n\n");
			printf("NO\tNAME\t\t\t\t\tWIN\t\tLOSE\t\tDRAW");
			for (i=0;i<10;i++){
				printf("\n%d\t%-15s\t\t\t\t%d\t\t%d\t\t%d",i+1,BotHistory[i].name,BotHistory[i].win,BotHistory[i].lose,BotHistory[i].draw);
			}
		}
		fclose(bot);
				
	} else if (lawan == 2){
		FILE *player = fopen("scoreBoard_player.txt","r");
		if (!player){
			printf("Data kosong, mainkan setidaknya 1 permainan!\n");
			printf("Tekan enter untuk melanjutkan!\n");
			while(!kbhit()){}
			return;
		} else {
  		    fread(PlayerHistory, sizeof (Data), 11, player);
			system("cls");
			printf("TOP 10 VS PLAYER SCOREBOARD\n\n");
			printf("NO\tNAME\t\t\t\t\tWIN\t\tLOSE\t\tDRAW");
			for (i=0;i<10;i++){
				printf("\n%d\t%-15s\t\t\t\t%d\t\t%d\t\t%d",i+1,PlayerHistory[i].name,PlayerHistory[i].win,PlayerHistory[i].lose,PlayerHistory[i].draw);
			}
		}
		fclose(player);
	}
	
	printf("\n\nTekan enter untuk kembali ke menu utama!\n");
	while(!kbhit()){}
}


void storeData(char player1[50], char player2[50], int result, int mode){
	if (mode == 3){ //vsBot
		FILE *bot = fopen("scoreBoard_bot.txt", "r");
		fread (BotHistory, sizeof(Data), 11, bot);
		if (result == 1){ //player1 win
			int slot1 = 1;
			int slot2 = 1;
			for (i = 0; i < 11; i++){
				if (strcmp(player1, BotHistory[i].name)==0){
					BotHistory[i].win++;
					slot1 = 0;
					break;
				} else if(strcmp(BotHistory[i].name, "-")==0){
					strcpy(BotHistory[i].name, player1);
					BotHistory[i].win++;
					slot1 = 0;
					break;
				}
			}
			for (i = 0; i < 11; i++){
				if (strcmp(player2, BotHistory[i].name)==0){
					BotHistory[i].lose++;
					slot2 = 0;
					break;
				} else if (strcmp(BotHistory[i].name, "-")==0){
					strcpy(BotHistory[i].name, player2);
					BotHistory[i].lose++;
					slot2 = 0;
					break;
				}
			}
			if (slot1 == 1){
				strcpy(BotHistory[10].name, player1);
				BotHistory[i].win = 1;
				BotHistory[i].lose = 0;
				BotHistory[i].draw= 0;
			} else if (slot2 == 1){
				strcpy(BotHistory[10].name, player2);
				BotHistory[i].win = 0;
				BotHistory[i].lose = 1;
				BotHistory[i].draw= 0;
			}
		} else if (result == 2){ //Bot win
			int slot1 = 1;
			int slot2 = 1;
			for (i = 0; i < 11; i++){
				if (strcmp(player1, BotHistory[i].name)==0){
					BotHistory[i].lose++;
					slot1 = 0;
					break;
				} else if(strcmp(BotHistory[i].name, "-")==0){
					strcpy(BotHistory[i].name, player1);
					BotHistory[i].lose++;
					slot1 = 0;
					break;
				}
			}
			for (i = 0; i < 11; i++){
				if (strcmp(player2, BotHistory[i].name)==0){
					BotHistory[i].win++;
					slot2 = 0;
					break;
				} else if (strcmp(BotHistory[i].name, "-")==0){
					strcpy(BotHistory[i].name, player2);
					BotHistory[i].win++;
					slot2 = 0;
					break;
					
				}
			}
			if (slot1 == 1){
				strcpy(BotHistory[10].name, player1);
				BotHistory[i].win = 0;
				BotHistory[i].lose = 1;
				BotHistory[i].draw= 0;
			} else if (slot2 == 1){
				strcpy(BotHistory[10].name, player2);
				BotHistory[i].win = 1;
				BotHistory[i].lose = 0;
				BotHistory[i].draw= 0;
			}
		} else if (result == 0){ //Draw
  		    int slot1 = 1;
			int slot2 = 1;
			for (i=0;i<11;i++){
				if (strcmp(player1,BotHistory[i].name)==0){
					BotHistory[i].draw++;
					slot1 = 0;
					break;
				}
				else if (strcmp(BotHistory[i].name,"-")==0){
					strcpy(BotHistory[i].name,player1);
					BotHistory[i].draw++;
					slot1 = 0;
					break;
				}
			}
			for (i=0;i<11;i++){
				if (strcmp(player2,BotHistory[i].name)==0){
					BotHistory[i].draw++;
					slot2 = 0;
					break;
				}
				else if (strcmp(BotHistory[i].name,"-")==0){
					strcpy(BotHistory[i].name,player2);
					BotHistory[i].draw++;
					slot2 = 0;
					break;
				}
			}
			if (slot1 == 1){
				strcpy(BotHistory[11].name,player1);
				BotHistory[10].win = 0;
				BotHistory[10].lose = 0;
				BotHistory[10].draw = 1;
			}
			else if(slot2 == 1){
				strcpy(BotHistory[10].name,player2);
				BotHistory[10].win = 0;
				BotHistory[10].lose = 0;
				BotHistory[10].draw = 1;
			}
		}
	}
	else if (mode == 2){ //player vs player
		FILE *player = fopen("scoreBoard_player.txt","r");
		fread(PlayerHistory, sizeof(Data), 11, player);
		if (result == 1){  //player1 wins
		   int slot1 = 1;
		   int slot2 = 1;
		   for (i = 0; i < 11; i++){
     	   	    if (strcmp(player1, PlayerHistory[i].name)==0){
				   PlayerHistory[i].win++;
				   slot1 = 0;
				   break;
			    } else if (strcmp(PlayerHistory[i].name, "-")==0){
			    	strcpy(PlayerHistory[i].name, player1);
			    	PlayerHistory[i].win++;
			    	slot1 = 0;
			    	break;
				}
		    }
		    for (i = 0; i < 11; i++){
		    	if (strcmp(player2, PlayerHistory[i].name)==0){
		    		PlayerHistory[i].lose++;
		    		slot2 = 0;
		    		break;
				} else if (strcmp(PlayerHistory[i].name, "-")==0){
					strcpy(PlayerHistory[i].name, player2);
					PlayerHistory[i].lose++;
					slot2 = 0;
					break;
				}
			}
			if (slot1 == 1){
				strcpy(PlayerHistory[10].name, player1);
				PlayerHistory[10].win = 1;
				PlayerHistory[10].lose = 0;
				PlayerHistory[10].draw = 0;
			}
			else if(slot2 == 1){
				strcpy(PlayerHistory[10].name, player2);
				PlayerHistory[10].win = 0;
				PlayerHistory[10].lose = 1;
				PlayerHistory[10].draw = 0;
			}
		}
		else if (result == 2){ //Player2 wins
			int slot1 = 1;
			int slot2 = 1;
			for (i = 0; i < 11; i++){
				if (strcmp(player1, PlayerHistory[i].name)==0){
					PlayerHistory[i].lose++;
					slot1 = 0;
					break;
				} else if(strcmp(PlayerHistory[i].name, "-")==0){
					strcpy(PlayerHistory[i].name, player1);
					PlayerHistory[i].lose++;
					slot1 = 0;
					break;
				}
			}
			for (i = 0; i < 11; i++){
				if (strcmp(player2, PlayerHistory[i].name)==0){
					PlayerHistory[i].win++;
					slot2 = 0;
					break;
				} else if (strcmp(PlayerHistory[i].name, "-")==0){
					strcpy(PlayerHistory[i].name, player2);
					PlayerHistory[i].win++;
					slot2 = 0;
					break;
					
				}
			}
			if (slot1 == 1){
				strcpy(PlayerHistory[10].name, player1);
				PlayerHistory[i].win = 0;
				PlayerHistory[i].lose = 1;
				PlayerHistory[i].draw= 0;
			} else if (slot2 == 1){
				strcpy(BotHistory[10].name, player2);
				PlayerHistory[i].win = 1;
				PlayerHistory[i].lose = 0;
				PlayerHistory[i].draw= 0;
			}
		}
		else if (result == 0){ //draw
			int slot1 = 1;
			int slot2 = 1;
			for (i=0;i<11;i++){
				if (strcmp(player1,PlayerHistory[i].name)==0){
					PlayerHistory[i].draw++;
					slot1 = 0;
					break;
				}
				else if (strcmp(PlayerHistory[i].name,"-")==0){
					strcpy(PlayerHistory[i].name,player1);
					BotHistory[i].draw++;
					slot1 = 0;
					break;
				}
			}
			for (i=0;i<11;i++){
				if (strcmp(player2,PlayerHistory[i].name)==0){
					PlayerHistory[i].draw++;
					slot2 = 0;
					break;
				}
				else if (strcmp(PlayerHistory[i].name,"-")==0){
					strcpy(PlayerHistory[i].name,player2);
					PlayerHistory[i].draw++;
					slot2 = 0;
					break;
				}
			}
			if (slot1 == 1){
				strcpy(PlayerHistory[11].name,player1);
				PlayerHistory[10].win = 0;
				PlayerHistory[10].lose = 0;
				PlayerHistory[10].draw = 1;
			}
			else if(slot2 == 1){
				strcpy(PlayerHistory[10].name,player2);
				PlayerHistory[10].win = 0;
				PlayerHistory[10].lose = 0;
				PlayerHistory[10].draw = 1;
			}
		}
		fclose(player);
	}
}

void sortData(){
	Data temp;
	int j;
	for (i=0;i<10;i++){
		for (j=i;j<11;j++){
			if (BotHistory[j].win > BotHistory[i].win){
				strcpy(temp.name,BotHistory[i].name);
				temp.win = BotHistory[i].win;
				temp.lose = BotHistory[i].lose;
				temp.draw = BotHistory[i].draw;
				strcpy(BotHistory[i].name,BotHistory[j].name);
				BotHistory[i].win = BotHistory[j].win;
				BotHistory[i].lose = BotHistory[j].lose;
				BotHistory[i].draw = BotHistory[j].draw;
				strcpy(BotHistory[j].name,temp.name);
				BotHistory[j].win = temp.win;
				BotHistory[j].lose = temp.lose;
				BotHistory[j].draw = temp.draw;
			} 
			if (PlayerHistory[j].win > PlayerHistory[i].win){
				strcpy(temp.name,PlayerHistory[i].name);
				temp.win = PlayerHistory[i].win;
				temp.lose = PlayerHistory[i].lose;
				temp.draw = PlayerHistory[i].draw;
				strcpy(PlayerHistory[i].name,PlayerHistory[j].name);
				PlayerHistory[i].win = PlayerHistory[j].win;
				PlayerHistory[i].lose = PlayerHistory[j].lose;
				PlayerHistory[i].draw = PlayerHistory[j].draw;
				strcpy(PlayerHistory[j].name,temp.name);
				PlayerHistory[j].win = temp.win;
				PlayerHistory[j].lose = temp.lose;
				PlayerHistory[j].draw = temp.draw;
			}
		}
	}
}

void saveData(){
	FILE *bot = fopen("scoreboard_bot.txt","w");
	fwrite(BotHistory, sizeof (Data), 11, bot);
	fclose(bot);
	FILE *player = fopen("scoreboard_player.txt","w");
	fwrite(PlayerHistory, sizeof (Data), 11 , player);
	fclose(player);
}


void header(){
	system("cls");
	int x,y;

	gotoxy(13, 1); printf("%c", 201);
    for (i=1;i<=94;i++){
        printf("%c", 205);
    }
    printf ("%c \n", 187);

	gotoxy(18, 2); printf(" ______   __     ______     ______   ______     ______     ______   ______     ______    	    \n");
	gotoxy(18, 3); printf("/\\__  _\\ /\\ \\   /\\  ___\\   /\\__  _\\ /\\  __ \\   /\\  ___\\   /\\__  _\\ /\\  __ \\   /\\  ___\\    \n");
	gotoxy(18, 4); printf("\\/_/\\ \\/ \\ \\ \\  \\ \\ \\____  \\/_/\\ \\/ \\ \\  __ \\  \\ \\ \\____  \\/_/\\ \\/ \\ \\ \\/\\ \\  \\ \\  __\\     \n");
	gotoxy(18, 5); printf("   \\ \\_\\  \\ \\_\\  \\ \\_____\\    \\ \\_\\  \\ \\_\\ \\_\\  \\ \\_____\\    \\ \\_\\  \\ \\_____\\  \\ \\_____\\   \n");
	gotoxy(18, 6); printf("    \\/_/   \\/_/   \\/_____/     \\/_/   \\/_/\\/_/   \\/_____/     \\/_/   \\/_____/   \\/_____/     \n");
	
	gotoxy(13,8);printf("%c", 200);
    for (i=1;i<=94;i++){
        printf("%c", 205);
	}
    printf("%c \n", 188);
}

void gotoxy(int x, int y) {
    COORD coord;
     
    coord.X = x;
    coord.Y = y;
     
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void speed(float seconds){
	 clock_t endwait;
	 endwait=clock()+seconds*CLOCKS_PER_SEC;
	 while(clock()<endwait){};
}

void loading(){
	int x = 42;  
	header();
	
	// loading 
	gotoxy(x,13); printf("               Loading");
	gotoxy(x,14); printf("     ===========================");
	gotoxy(x,15);printf("    %c                           %c", 186,186);
	gotoxy(x,16); printf("     ===========================");
	for(i=47; i<=73; i++){
		gotoxy(i,15);printf("\xdb");
		speed(0.05);
	}
}

void Winner(int winner){
	header();
	printf("\n\n");
	printf("\t\t\t\t\t     _________________________ \n");
	printf("\t\t\t\t\t    |     |     ___     |     |\n");
	printf("\t\t\t\t\t    |_____|    /_  |    |_____|\n");
	printf("\t\t\t\t\t          |      | |    |      \n");
	printf("\t\t\t\t\t          |      | |    |      \n");
	printf("\t\t\t\t\t          |      |_|    |      \n");
	printf("\t\t\t\t\t          |_____________|      \n");
	printf("\t\t\t\t\t                |  |           \n");
	printf("\t\t\t\t\t                |  |           \n");
	printf("\t\t\t\t\t                |  |           \n");
	printf("\t\t\t\t\t              __|  |__         \n");
	printf("\t\t\t\t\t             |________|        \n");
	printf("\t\t\t\t\t          ________________     \n");
	printf("\t\t\t\t\t        ____________________   \n");

	if (winner == 0)
	{
		printf("DRAW.");
	}
	else if (winner == 1)
	{
		printf("%s's WIN.", Player1);
	}
	else
	{
		printf("%s's WIN.", Player2);
	}

	system("pause");
}

int selectMenu(){
	system("color 1F");
	loading();
	int menu=1;

	do {
		header();
		gotoxy(44, 10); printf(" ________________________________   \n");	
		gotoxy(44, 11); printf("|                                |  \n");	
		gotoxy(44, 12); printf("|           MENU UTAMA           |  \n");
		gotoxy(44, 13); printf("|________________________________|  \n");
		gotoxy(44, 14); printf("|                                |  \n");
		gotoxy(44, 15); printf("|                                |  \n");	
		gotoxy(44, 16); printf("|            1. Mulai            |  \n");
		gotoxy(44, 17); printf("|           2. Bantuan           |  \n");
		gotoxy(44, 18); printf("|          3. Papan Skor         |  \n");
		gotoxy(44, 19); printf("|            4. Keluar           |  \n");
		gotoxy(44, 20); printf("|                                |  \n");
		gotoxy(44, 21); printf("|________________________________|  \n\n\n");
	
		while (menu != 1 && menu != 2 && menu != 3 && menu != 4 ){
			printf("                                         TOLONG MASUKKAN INPUT YANG VALID (1-4)             \n\n");
			break;
		}
			
		printf("                                 Ketik 1, 2, 3 atau 4 sesuai dengan pilihan opsi di atas \n");
		printf("                                                      Masukkan Input                \n");
		printf("                                                             ");
		scanf("%d", &menu);	
	} while (menu != 1 && menu != 2 && menu != 3 && menu != 4 );
	
	return menu;
}

void mainMenu(char (*Player1)[50], char (*Player2)[50]){
	int menu=0;
		
	while(menu==0){
		menu=selectMenu();
		
		if(menu == 1){
			menu=0;
			selectBoard();
			break;
		} else if (menu == 2){
			loading();
			help();
			menu=0;
			continue;
		} else if (menu == 3){
			loading();
			header();
			displayScoreBoard();
			menu=0;
			continue;
		} else if (menu == 4){
			loading();
			header();
			gotoxy(50,13); printf("See U Next Time^^\n\n\n\n");
			exit(0);
		} else {
			menu=0;
			continue;
		}	
	}	
}

void help(){
	int menu;
	
	do{
		header();
		
		gotoxy(47, 11); printf("CARA DAN ATURAN BERMAIN\n\n");
		printf("   1. Pada menu utama, ketik '1', '2', '3' atau '4' untuk menampilkan menu yang ingin anda lihat\n");
		printf("   2. Pilih papan bermain yang anda akan gunakan. Ada 3 pilihan papan yang bisa dimainkan. \n");
		printf("      Ketik '3','5' atau '7' untuk memilih papan\n");
		printf("   3. Pilih lawan yang anda ingin lawan. Ketik '1' jika akan bermain bersama pemain lain, \n");
		printf("      ketik '2' jika anda akan memainkan permainan ini sendiri melawan bot\n");
		printf("   4. Ketik nama pemain yang akan bermain\n");
		printf("   5. Untuk melakukan sebuah gerakan, kamu perlu mengetik lokasi kotak yang kamu mau. Contoh '1 1', '2 5', '7 4'\n");

		printf("\n   Selamat bermain!!\n\n");
		
		printf("   Ketik 0 untuk kembali ke menu utama: ");
		scanf("%d", &menu);
		
	} while (menu!=0);
}


void selectBoard(){
	loading();
	boardSize = 1;
	do {
		header();
		system("color CF");
		gotoxy(44, 10); printf(" ________________________________  ");	
		gotoxy(44, 11); printf("|                                |  ");	
		gotoxy(44, 12); printf("|           SELECT BOARD         |  ");
		gotoxy(44, 13); printf("|________________________________|  ");
		gotoxy(44, 14); printf("|                                |  ");
		gotoxy(44, 15); printf("|                                |  ");	
		gotoxy(44, 16); printf("|          1. Board 3x3          |  ");
		gotoxy(44, 17); printf("|          2. Board 5x5          |  ");
		gotoxy(44, 18); printf("|          3. Board 7x7          |  ");
		gotoxy(44, 19); printf("|          4. Kembali            |  ");
		gotoxy(44, 20); printf("|                                |  ");
		gotoxy(44, 21); printf("|________________________________|  \n\n\n");
		
		while (boardSize != 1 && boardSize != 2 && boardSize !=3 && boardSize !=4){
			printf("                                         TOLONG MASUKKAN INPUT YANG VALID (1-4)             \n\n");
			break;
		}
			
		printf("                        Ketik 1, 2, 3, atau 4 sesuai pilihan di atas untuk memilih papan yang ingin digunakan \n");
		printf("                                                      Masukkan Input                \n");
		printf("                                                             ");
		scanf("%d", &boardSize);
			
	} while (boardSize != 1 && boardSize != 2 && boardSize != 3 && boardSize !=4);

	if(boardSize == 1){
		boardSize = 3;
		selectMode(&Player1, &Player2);
	} else if (boardSize == 2){
		boardSize = 5;
		selectMode(&Player1, &Player2);
	} else if (boardSize == 3){
		boardSize = 7;
		selectMode(&Player1, &Player2);
	} else if (boardSize == 4){
		mainMenu(&Player1, &Player2);
	} 
}		


void selectMode(char (*Player1)[50], char (*Player2)[50]){
	loading();
	lawan=1;
	
	do {
		system("color 5F");
		header();
		gotoxy(44, 10); printf(" ________________________________  \n");	
		gotoxy(44, 11); printf("|                                |  \n");	
		gotoxy(44, 12); printf("|           SELECT MODE          |  \n");
		gotoxy(44, 13); printf("|________________________________|  \n");
		gotoxy(44, 14); printf("|                                |  \n");
		gotoxy(44, 15); printf("|                                |  \n");	
		gotoxy(44, 16); printf("|            1. Player           |  \n");
		gotoxy(44, 17); printf("|            2. Bot              |  \n");
		gotoxy(44, 18); printf("|            3. Kembali          |  \n");
		gotoxy(44, 19); printf("|                                |  \n");
		gotoxy(44, 20); printf("|________________________________|  \n\n\n");
		if (lawan != 1 && lawan != 2 && lawan != 3){
			printf("                                         TOLONG MASUKKAN INPUT YANG VALID (1-3)             \n\n");
		}	
		printf("                        Ketik 1 atau 2 sesuai pilihan di atas untuk memilih lawan dalam permainan \n");
		printf("                                                      Masukkan Input                \n");
		printf("                                                             ");
		scanf("%d", &lawan);
			
	} while (lawan != 1 && lawan != 2 && lawan != 3);
	
	switch(lawan){
		case 1:
			lawan=2;
			inputName((*Player1), (*Player2));
			break;
		case 2:
			lawan=3;
			inputName((*Player1), (*Player2));
			break;
		case 3:
			selectBoard();
	}
	
}

void inputName(char Player1[50], char Player2[50]){
	system("color 4F");
	loading();
	char *nameBot[25];
	char BOT[] = "BOT ";
	
	if (lawan == 2){
		do{
			header();
			gotoxy(44, 12); printf("Masukkan Nama Player 1 : ");
			fflush(stdin);
			scanf("%[^\n]s", Player1);
			if (!isAlpha(Player1)){
				printf("\n                                TOLONG MASUKKAN INPUT YANG VALID (hanya berupa alphabet)  \n\n");
				system("pause");
			}
		} while (!isAlpha(Player1));
		
		do{
			header();
			gotoxy(44, 12); printf("Masukkan Nama Player 2 : ");
			fflush(stdin);
			scanf("%[^\n]s", Player2);
			if (!isAlpha(Player2)){
				printf("\n                                TOLONG MASUKKAN INPUT YANG VALID (hanya berupa alphabet)  \n\n");
				system("pause");
			}
		} while (!isAlpha(Player2));
	}
	
	else if (lawan == 3){
		do{
			header();
			gotoxy(44, 12); printf("Masukkan Nama Player : ");
			fflush(stdin);
			scanf("%[^\n]s", Player1);
			if (!isAlpha(Player1)){
				printf("\n                               TOLONG MASUKKAN INPUT YANG VALID (hanya berupa alphabet)  \n\n");
				system("pause");
			}
		} while (!isAlpha(Player1));
		
		*nameBot = strcat(BOT, Player1);
		strcpy(Player2, (*nameBot));
	}
	
}


bool isAlpha(const char* str) {
    for(int i = 0; i < strlen(str); i++) {
        if(!isalpha(str[i])) {
            return false;
        }
    }
    return true;
}

void resetBoard()
{
	int j;
	for(i = 0; i < 7; i++)
		for(j = 0; j < 7; j++)
			board[i][j] = ' ';
}

void printBoard()
{
	if (boardSize == 3) {
		gotoxy(44, 11); printf ("         1       2       3     ");
		gotoxy(44, 12); printf ("      _______________________\n");
		gotoxy(44, 13); printf ("     |       |       |       |\n");
		gotoxy(44, 14); printf (" 1   |   %c   |   %c   |   %c   |\n", board[0][0], board[0][1], board[0][2]);
		gotoxy(44, 15); printf ("     |_______|_______|_______|\n");
		gotoxy(44, 16); printf ("     |       |       |       |\n");
		gotoxy(44, 17); printf (" 2   |   %c   |   %c   |   %c   |\n", board[1][0], board[1][1], board[1][2]);
		gotoxy(44, 18); printf ("     |_______|_______|_______|\n");
		gotoxy(44, 19); printf ("     |       |       |       |\n");
		gotoxy(44, 20); printf (" 3   |   %c   |   %c   |   %c   |\n", board[2][0], board[2][1], board[2][2]);
		gotoxy(44, 21); printf ("     |_______|_______|_______|\n");		
	}
	else if (boardSize == 5)
	{
		gotoxy(37, 11); printf ("         1       2       3       4       5 \n");
		gotoxy(37, 12); printf ("      _______________________________________\n");
		gotoxy(37, 13); printf ("     |       |       |       |       |       |\n");
		gotoxy(37, 14); printf (" 1   |   %c   |   %c   |   %c   |   %c   |   %c   |\n", board[0][0], board[0][1], board[0][2], board[0][3], board[0][4]);
		gotoxy(37, 15); printf ("     |_______|_______|_______|_______|_______|\n");
		gotoxy(37, 16); printf ("     |       |       |       |       |       |\n");
		gotoxy(37, 17); printf (" 2   |   %c   |   %c   |   %c   |   %c   |   %c   |\n", board[1][0], board[1][1], board[1][2], board[1][3], board[1][4]);
		gotoxy(37, 18); printf ("     |_______|_______|_______|_______|_______|\n");
		gotoxy(37, 19); printf ("     |       |       |       |       |       |\n");
		gotoxy(37, 20); printf (" 3   |   %c   |   %c   |   %c   |   %c   |   %c   |\n", board[2][0], board[2][1], board[2][2], board[2][3], board[2][4]);
		gotoxy(37, 21); printf ("     |_______|_______|_______|_______|_______|\n");
		gotoxy(37, 22); printf ("     |       |       |       |       |       |\n");
		gotoxy(37, 23); printf (" 4   |   %c   |   %c   |   %c   |   %c   |   %c   |\n", board[3][0], board[3][1], board[3][2], board[3][3], board[3][4]);
		gotoxy(37, 24); printf ("     |_______|_______|_______|_______|_______|\n");
		gotoxy(37, 25); printf ("     |       |       |       |       |       |\n");
		gotoxy(37, 26); printf (" 5   |   %c   |   %c   |   %c   |   %c   |   %c   |\n", board[4][0], board[4][1], board[4][2], board[4][3], board[4][4]);
		gotoxy(37, 27); printf ("     |_______|_______|_______|_______|_______|\n");
	}
	else if (boardSize == 7)
	{
		gotoxy(30, 11); printf ("         1       2       3       4       5       6       7  \n");
		gotoxy(30, 12); printf ("      _______________________________________________________\n");
		gotoxy(30, 13); printf ("     |       |       |       |       |       |       |       |\n");
		gotoxy(30, 14); printf (" 1   |   %c   |   %c   |   %c   |   %c   |   %c   |   %c   |   %c   |\n", board[0][0], board[0][1], board[0][2], board[0][3], board[0][4], board[0][5], board[0][6]);
		gotoxy(30, 15); printf ("     |_______|_______|_______|_______|_______|_______|_______|\n");
		gotoxy(30, 16); printf ("     |       |       |       |       |       |       |       |\n");
		gotoxy(30, 17); printf (" 2   |   %c   |   %c   |   %c   |   %c   |   %c   |   %c   |   %c   |\n", board[1][0], board[1][1], board[1][2], board[1][3], board[1][4], board[1][5], board[1][6]);
		gotoxy(30, 18); printf ("     |_______|_______|_______|_______|_______|_______|_______|\n");
		gotoxy(30, 19); printf ("     |       |       |       |       |       |       |       |\n");
		gotoxy(30, 20); printf (" 3   |   %c   |   %c   |   %c   |   %c   |   %c   |   %c   |   %c   |\n", board[2][0], board[2][1], board[2][2], board[2][3], board[2][4], board[2][5], board[2][6]);
		gotoxy(30, 21); printf ("     |_______|_______|_______|_______|_______|_______|_______|\n");
		gotoxy(30, 22); printf ("     |       |       |       |       |       |       |       |\n");
		gotoxy(30, 23); printf (" 4   |   %c   |   %c   |   %c   |   %c   |   %c   |   %c   |   %c   |\n", board[3][0], board[3][1], board[3][2], board[3][3], board[3][4], board[3][5], board[3][6]);
		gotoxy(30, 24); printf ("     |_______|_______|_______|_______|_______|_______|_______|\n");
		gotoxy(30, 25); printf ("     |       |       |       |       |       |       |       |\n");
		gotoxy(30, 26); printf (" 5   |   %c   |   %c   |   %c   |   %c   |   %c   |   %c   |   %c   |\n", board[4][0], board[4][1], board[4][2], board[4][3], board[4][4], board[4][5], board[4][6]);
		gotoxy(30, 27); printf ("     |_______|_______|_______|_______|_______|_______|_______|\n");
		gotoxy(30, 28); printf ("     |       |       |       |       |       |       |       |\n");
		gotoxy(30, 29); printf (" 6   |   %c   |   %c   |   %c   |   %c   |   %c   |   %c   |   %c   |\n", board[5][0], board[5][1], board[5][2], board[5][3], board[5][4], board[5][5], board[5][6]);
		gotoxy(30, 30); printf ("     |_______|_______|_______|_______|_______|_______|_______|\n");
		gotoxy(30, 31); printf ("     |       |       |       |       |       |       |       |\n");
		gotoxy(30, 32); printf (" 7   |   %c   |   %c   |   %c   |   %c   |   %c   |   %c   |   %c   |\n", board[6][0], board[6][1], board[6][2], board[6][3], board[6][4], board[6][5], board[6][6]);
		gotoxy(30, 33); printf ("     |_______|_______|_______|_______|_______|_______|_______|\n");
	}
}

int moveExist()
{
	int j, move = false;
	for (i = 0; i < boardSize; i++)
		for (j = 0; j < boardSize; j++)
		{
			if (board[i][j] == ' ')
			{
				move = true;
				break;
			}
		}	
	return move;
}

int isValid(int row, int column)
{
	if(row >= 0 && row < boardSize && column >= 0 && column < boardSize && board[row][column] == ' ')
		return true;
	else 
		return false;
}

void drawSymbol(int playerTurn)
{
	int row, column;
	
	for(;;)
	{
		printf("\nENTER ROW & COLUMN (#ROW #COLUMN): ");
		scanf("%d %d", &row, &column);
		row--;
		column--;
		
		if (isValid(row, column))
		{
			if (playerTurn == 1)
			{
				board[row][column] = PLAYER1;
			}
			else if (playerTurn == 2)
			{
				board[row][column] = PLAYER2;
			}
			break;
		}
		else
		{
			//system("cls");
			header();
			printBoard();
			printf("\nENTER A VALID INPUT.\n");
		}
	}
}

int checkWinner()
{
	int j;
	if (boardSize == 3)
	{
		for (i = 0; i < 3; i++)
		{
			/* WIN BY HORIZONTAL */
			if (board[i][0] == 'X' && board[i][1] == 'X' && board[i][2] == 'X')
			{ 
				return 1; 
				break;
			}
			else if (board[i][0] == 'O' && board[i][1] == 'O' && board[i][2] == 'O')
			{ 
				return 2; 
				break;
			}
			/* WIN BY VERTICALS */
			else if (board[0][i] == 'X' && board[1][i] == 'X' && board[2][i] == 'X')
			{ 
				return 1; 
				break;
			}
			else if (board[0][i] == 'O' && board[1][i] == 'O' && board[2][i] == 'O')
			{ 
				return 2; 
				break;
			}
			/* WIN BY DIAGONALS */
			else if(board[0][0] == 'X' && board[1][1] == 'X' && board[2][2] == 'X' || board[0][2] == 'X' && board[1][1] == 'X' && board[2][0] == 'X')
			{
				return 1; 
				break;
			}
			else if(board[0][0] == 'O' && board[1][1] == 'O' && board[2][2] == 'O' || board[0][2] == 'O' && board[1][1] == 'O' && board[2][0] == 'O')
			{
				return 2; 
				break;
			}
		}
		return 0;
	}
	else if (boardSize == 5)
	{
		for (i = 0; i < 5; i++)
		{
			for (j = 0; j < 2; j++)
			{
				/* WIN BY HORIZONTAL */
				if (board[i][j] == 'X' && board[i][j+1] == 'X' && board[i][j+2] == 'X' && board[i][j+3] == 'X') 
				{
					return 1; 
					break;
				}
				else if (board[i][j] == 'O' && board[i][j+1] == 'O' && board[i][j+2] == 'O' && board[i][j+3] == 'O') 
				{
					return 2; 
					break;
				}
				/* WIN BY VERTICAL */
				else if (board[j][i] == 'X' && board[j+1][i] == 'X' && board[j+2][i] == 'X' && board[j+3][i] == 'X') 
				{
					return 1; 
					break;
				}
				else if (board[j][i] == 'O' && board[j+1][i] == 'O' && board[j+2][i] == 'O' && board[j+3][i] == 'O') 
				{
					return 2; 
					break;
				}
				/* WIN BY DIAGONAL */
				else if (board[0+i][0+j] == 'X' && board[1+i][1+j] == 'X' && board[2+i][2+j] == 'X' && board[3+i][3+j] == 'X') 
				{
					return 1; 
					break;
				}
				else if (board[0+i][0+j] == 'O' && board[1+i][1+j] == 'O' && board[2+i][2+j] == 'O' && board[3+i][3+j] == 'O') 
				{
					return 2; 
					break;
				}
				else if (board[0+i][3+j] == 'X' && board[1+i][2+j] == 'X' && board[2+i][1+j] == 'X' && board[3+i][0+j] == 'X') 
				{
					return 1; 
					break;
				}
				else if (board[0+i][3+j] == 'O' && board[1+i][2+j] == 'O' && board[2+i][1+j] == 'O' && board[3+i][0+j] == 'O') 
				{
					return 2; 
					break;
				}
			}
		}
		return 0;
	}
	else if (boardSize == 7)
	{
		for (i = 0; i < 7; i++)
		{
			for (j = 0; j < 3; j++)
			{
				/* WIN BY HORIZONTAL */
				if (board[i][j] == 'X' && board[i][j+1] == 'X' && board[i][j+2] == 'X' && board[i][j+3] == 'X' && board[i][j+4] == 'X') 
				{
					return 1; 
					break;
				}
				else if (board[i][j] == 'O' && board[i][j+1] == 'O' && board[i][j+2] == 'O' && board[i][j+3] == 'O' && board[i][j+4] == 'O') 
				{
					return 2; 
					break;
				}
				/* WIN BY VERTICAL */
				else if (board[j][i] == 'X' && board[j+1][i] == 'X' && board[j+2][i] == 'X' && board[j+3][i] == 'X' && board[j+4][i] == 'X') 
				{
					return 1; 
					break;
				}
				else if (board[j][i] == 'O' && board[j+1][i] == 'O' && board[j+2][i] == 'O' && board[j+3][i] == 'O' && board[j+4][i] == 'O') 
				{
					return 2; 
					break;
				}
				/* WIN BY DIAGONALS */
				else if (board[0+i][2-j] == 'X' && board[1+i][3-j] == 'X' && board[2+i][4-j] == 'X' && board[3+i][5-j] == 'X' && board[4+i][6-j] == 'X') 
				{
					return 1; 
					break;
				}
				else if (board[0+i][2-j] == 'O' && board[1+i][3-j] == 'O' && board[2+i][4-j] == 'O' && board[3+i][5-j] == 'O' && board[4+i][6-j] == 'O')
				{
					return 2; 
					break;
				}
				else if (board[0+i][4+j] == 'X' && board[1+i][3+j] == 'X' && board[2+i][2+j] == 'X' && board[3+i][1+j] == 'X' && board[4+i][0+j] == 'X') 
				{
					return 1; 
					break;
				}
				else if (board[0+i][4+j] == 'O' && board[1+i][3+j] == 'O' && board[2+i][2+j] == 'O' && board[3+i][1+j] == 'O' && board[4+i][0+j] == 'O') 
				{
					return 2; 
					break;
				}				
			}
		}
		return 0;
	}
}


void bot()
{
	/* KAMUS DATA */
	int row, column;
	time_t t1;
	
	/* ALGORIMTA */
	srand((unsigned) time(&t1));
	while (!isValid(row, column))
	{
		row = rand()%boardSize;
		column = rand()%boardSize;
	}
	
	board[row][column] = PLAYER2;
}

void timer()
{
	int seconds = 15;
	
	while (seconds > 0)
	{
		printf("\r%02d", seconds);
		fflush(stdout);
		
		clock_t stop = clock() + CLOCKS_PER_SEC;
		while (clock() < stop) { }
		
		seconds--;
	}
	
	printf("TIME'S UP...");
}

