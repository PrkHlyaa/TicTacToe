#include <time.h>
#include <conio.h>
#include <stdio.h>
#include <windows.h>
#include <stdlib.h>
#include <string.h>



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

void header(){
	system("cls");
	int x,y;

	gotoxy(13, 1); printf("%c", 201);
    for (int i=1;i<=94;i++){
        printf("%c", 205);
    }
    printf ("%c \n", 187);

	gotoxy(18, 2); printf(" ______   __     ______     ______   ______     ______     ______   ______     ______    	    \n");
	gotoxy(18, 3); printf("/\\__  _\\ /\\ \\   /\\  ___\\   /\\__  _\\ /\\  __ \\   /\\  ___\\   /\\__  _\\ /\\  __ \\   /\\  ___\\    \n");
	gotoxy(18, 4); printf("\\/_/\\ \\/ \\ \\ \\  \\ \\ \\____  \\/_/\\ \\/ \\ \\  __ \\  \\ \\ \\____  \\/_/\\ \\/ \\ \\ \\/\\ \\  \\ \\  __\\     \n");
	gotoxy(18, 5); printf("   \\ \\_\\  \\ \\_\\  \\ \\_____\\    \\ \\_\\  \\ \\_\\ \\_\\  \\ \\_____\\    \\ \\_\\  \\ \\_____\\  \\ \\_____\\   \n");
	gotoxy(18, 6); printf("    \\/_/   \\/_/   \\/_____/     \\/_/   \\/_/\\/_/   \\/_____/     \\/_/   \\/_____/   \\/_____/     \n");
	
	gotoxy(13,8);printf("%c", 200);
    for (int i=1;i<=94;i++){
        printf("%c", 205);
	}
    printf("%c \n", 188);
}

void loading(){
	header();
	
	// loading 
	int x = 42;  
	gotoxy(x,13); printf("               Loading");
	gotoxy(x,14); printf("     ===========================");
	gotoxy(x,15);printf("    %c                           %c", 186,186);
	gotoxy(x,16); printf("     ===========================");
	for(int i=47; i<=73; i++){
		gotoxy(i,15);printf("\xdb");
		speed(0.05);
	}
}

int main () {
//	int n = 4; // Lebar setiap kotak
//    int j, i, k;
//
//    // Membuat baris horizontal
//    for (i = 0; i <= 10; i++) {
//        for (j = 0; j <= 10; j++) {
//            gotoxy(n * j, 2 * i);
//            if (i == 0 && j == 0) {
//                printf("%c", 218); // Kiri atas
//            } else if (i == 0 && j == 10) {
//                printf("%c", 191); // Kanan atas
//            } else if (i == 10 && j == 0) {
//                printf("%c", 192); // Kiri bawah
//            } else if (i == 10 && j == 10) {
//                printf("%c", 217); // Kanan bawah
//            } else if (i == 0) {
//                printf("%c", 194); // T atas
//            } else if (i == 10) {
//                printf("%c", 193); // T bawah
//            } else if (j == 0) {
//                printf("%c", 195); // T kiri
//            } else if (j == 10) {
//                printf("%c", 180); // T kanan
//            } else {
//                printf("%c", 197); // Persilangan
//            }
//            if (j < 10) {
//                for (k = 1; k < n; k++) {
//                    printf("%c", 196); // Garis horizontal
//                }
//            }
//        }
//    }
//
//    // Membuat baris vertikal
//    for (i = 0; i <= 10; i++) {
//        for (j = 0; j < 10; j++) {
//            gotoxy(n * j + n, 2 * i);
//            printf("%c", 179); // Garis vertikal
//            for (k = 1; k < 2; k++) {
//                gotoxy(n * j + n, 2 * i + k);
//                printf("%c", 179); // Garis vertikal
//            }
//        }
//    }
//
//    return 0;
//


	int n = 4;
	int j;
	for (j = 0; j < 10; j++){
		gotoxy(n*j, 1);
		printf("%c", 194);
		for (int i = 0; i < 3; i++){
			printf("%c", 196);
		}
		gotoxy(n*j, 2);
		printf("%c", 179);
		printf(" A ");
	}
}
