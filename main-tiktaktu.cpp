#include <time.h>
#include <conio.h>
#include <stdio.h>
#include <windows.h>
#include <stdlib.h>
#include <string.h>

#include "tiktaktu.h"

#define true 1
#define false 0


int main ()
{
	
	/* KAMUS DATA */
	/* ATRIBUT PERMAINAN */
	int turn = 1;
	int winner = 0;
	
	/*Reset ScoreBoard*/
	for (i = 0; i < 11; i++){
		strcpy(BotHistory[i].name, "-");
		BotHistory[i].win = 0;
		BotHistory[i].lose = 0;
		BotHistory[i].draw = 0;
		strcpy(PlayerHistory[i].name, "-");
		PlayerHistory[i].win = 0;
		PlayerHistory[i].lose = 0;
		PlayerHistory[i].draw = 0;
	}
	
	/* ALGORITMA */
	do {
		mainMenu(&Player1, &Player2);
		
		fflush(stdin);
		
		resetBoard();
		gameplay(&turn, &winner);
		
		header();
		printBoard();
		printf("\n");
		
		header();
		Winner(winner);
		
		//	ScoreBoard
		storeData(Player1, Player2, winner, lawan);
		sortData();
		saveData();
		fflush(stdin);
	} while (!kbhit());
	
	return 0;
}
