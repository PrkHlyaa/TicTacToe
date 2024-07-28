#include <stdio.h>
#include <conio.h>
#include <windows.h>

// Fungsi untuk menggerakkan cursor ke posisi tertentu di konsol
void gotoxy(int x, int y) {
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

// Fungsi untuk mendapatkan ukuran konsol
void getConsoleSize(int *width, int *height) {
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    int columns, rows;

    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    columns = csbi.srWindow.Right - csbi.srWindow.Left + 1;
    rows = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;

    *width = columns;
    *height = rows;
}

int main() {
    int consoleWidth, consoleHeight;
    getConsoleSize(&consoleWidth, &consoleHeight);

    int boxWidth = 4; // Lebar setiap kotak (termasuk garis vertikal)
    int boxHeight = 2; // Tinggi setiap kotak (termasuk garis horizontal)
    int size = 10; // Ukuran papan 10x10

    // Hitung offset untuk menempatkan papan di tengah konsol
    int offsetX = (consoleWidth - (size * boxWidth)) / 2;
    int offsetY = (consoleHeight - (size * boxHeight)) / 2;

    int i, j, k;

    // Membuat papan dengan kotak 10x10
    for (i = 0; i < size; i++) {
        for (j = 0; j < size; j++) {
            gotoxy(offsetX + boxWidth * j, offsetY + boxHeight * i);
            if (i < size) {
                // Garis horizontal
                printf("%c", 197); // Titik persilangan
                for (k = 1; k < boxWidth; k++) {
                    gotoxy(offsetX + boxWidth * j + k, offsetY + boxHeight * i);
                    printf("%c", 196); // Garis horizontal
                }
            }

            if (j < size) {
                // Garis vertikal
                for (k = 1; k < boxHeight; k++) {
                    gotoxy(offsetX + boxWidth * j, offsetY + boxHeight * i + k);
                    printf("%c", 179); // Garis vertikal
                }
            }

            if (i < size && j < size) {
                // Huruf di dalam kotak
                gotoxy(offsetX + boxWidth * j + 1, offsetY + boxHeight * i + 1); // Menyesuaikan posisi huruf di dalam kotak
                printf(" A"); // Ganti dengan huruf yang diinginkan
            }
        }
    }

    // Membuat garis tepi kanan dan bawah papan
    for (i = 0; i <= size * boxHeight; i++) {
        gotoxy(offsetX + size * boxWidth, offsetY + i);
        printf("%c", 186); // Garis vertikal tepi kanan
    }
    for (i = 0; i <= size * boxWidth; i++) {
        gotoxy(offsetX + i, offsetY + size * boxHeight);
        printf("%c", 205); // Garis horizontal tepi bawah
    }

    // Membuat garis tepi kiri dan atas papan
    for (i = 0; i <= size * boxHeight; i++) {
        gotoxy(offsetX, offsetY + i);
        printf("%c", 186); // Garis vertikal tepi kiri
    }
    for (i = 0; i <= size * boxWidth; i++) {
        gotoxy(offsetX + i, offsetY);
        printf("%c", 205); // Garis horizontal tepi atas
    }

    // Membuat sudut-sudut papan
    gotoxy(offsetX, offsetY);
    printf("%c", 201); // Sudut kiri atas
    gotoxy(offsetX + size * boxWidth, offsetY);
    printf("%c", 187); // Sudut kanan atas
    gotoxy(offsetX, offsetY + size * boxHeight);
    printf("%c", 200); // Sudut kiri bawah
    gotoxy(offsetX + size * boxWidth, offsetY + size * boxHeight);
    printf("%c", 188); // Sudut kanan bawah

    return 0;
}

