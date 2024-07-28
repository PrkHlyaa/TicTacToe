#ifndef TIKTAKTU_H
#define TIKTAKTU_H

/* DEKLARASI MODUL */
/* MODUL UI */
void header(); // PROSEDUR >> Menampilkan header pada layar
void gotoxy(int x, int y); // PROSEDUR >> Memindahkan kursor pada layar
void speed(float seconds); // PROSEDUR >> Memberi jeda ketika menampilkan sesuatu pada layar
void Winner(int winner); // PROSEDUR >> Menampilkan pemenang pada layar ketika permainan berkakhir
void loading(); // PROSEDUR >> Menampilkan tampilan UI pada saat loading
/* MODUL MAIN MENU */
int selectMenu(); // FUNGSI >> Menampilkan Pilihan Main Menu dan Meminta input Menu >> RETURN INTEGER.
void mainMenu(char (*Player1)[50], char (*Player2)[50]);// PROSEDUR >> Menampilkan menu sesuai input dari selectMenu()
void help(); // PROSEDUR >> Menampilkan fitur bantuan
void selectBoard(); // PROSEDUR >> Tampilan untuk memilih board yang akan digunakan dalam permainan
void selectMode(char (*Player1)[50], char (*Player2)[50]); // PROSEDUR >> Tampilan untuk memilih mode/lawan yang akan digunakan dalam permainan
void inputName(char Player1[50], char Player2[50]); // PROSEDUR >> Meminta input nama pemain
bool isAlpha(const char* str);
/* MODUL board */
void resetBoard(); // PROSEDUR >> Menginisialisasi board permainan dengan nilai ' ' (kosong).
void printBoard(); // PROSEDUR >> Menampilkan board pada layar.
/* MODUL GAMEPLAY */
int moveExist(); // FUNGSI >> Memeriksa apakah ada sel yang masih bisa diisi pada board >> RETURN BOOLEAN.
int checkWinner(); // FUNGSI >> Memeriksa apakah ada pemain yang telah memenuhi goal permainan >> RETURN CHAR ('X'/'O'/' ')
void timer(); // PROSEDUR >> Menghitung mundur waktu.
/* MODUL INPUT MOVE */
int isValid(int row, int column); // FUNGSI >> Memeriksa apakah input move yang diberikan sesuai >> RETURN BOOLEAN.
void drawSymbol(int playerTurn); // PROSEDUR >> Menginput baris dan kolom papan yang akan diisi.
/* MODUL BOT */
void bot(); // PROSEDUR >> Menentukan angka random untuk mengisi papan.
void gameplay(int *turn, int *winner);
/*MODUL StoreData*/
void displayScoreBoard();
void storeData(char player1[25], char player2[25], int result, int mode);
void saveData();
void sortData();

/* KAMUS DATA GLOBAL */
const char PLAYER1 = 'X';
const char PLAYER2 = 'O';

typedef struct{
	char name[50];
	int win;
	int lose;
	int draw;
} Data;

extern Data BotHistory[11];
extern Data PlayerHistory[11];

/* ATRIBUT PERMAINAN */
extern char board[7][7];
extern int boardSize;
extern int lawan, i;
extern char Player1[50];
extern char Player2[50];

#endif
