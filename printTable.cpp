#include <stdio.h>
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

// Fungsi untuk menggambar tabel di tengah konsol
void table() {
    system("cls");

    int tableWidth = 65; // Lebar tabel
    int tableHeight = 15; // Tinggi tabel pertama
    int consoleWidth, consoleHeight;

    getConsoleSize(&consoleWidth, &consoleHeight);

    // Hitung offset untuk menempatkan tabel di tengah konsol
    int offsetX = (consoleWidth - tableWidth) / 2;
    int offsetY = (consoleHeight - 2 * tableHeight) / 2;

    // Membuat kotak pertama (atas)
    // Garis atas
    gotoxy(offsetX, offsetY); printf("%c", 201);
    for (int i = 1; i < tableWidth - 1; i++) {
        printf("%c", 205);
    }
    printf("%c\n", 187);

    // Garis samping dan isi kotak pertama
    for (int i = 1; i < tableHeight; i++) {
        gotoxy(offsetX, offsetY + i); printf("%c", 186);
        gotoxy(offsetX + tableWidth - 1, offsetY + i); printf("%c", 186);
    }

    // Garis bawah kotak pertama (bagian atas kotak kedua)
    gotoxy(offsetX, offsetY + tableHeight); printf("%c", 204);
    for (int i = 1; i < tableWidth - 1; i++) {
        printf("%c", 205);
    }
    printf("%c\n", 185);

    // Membuat kotak kedua (bawah)
    // Garis samping kotak kedua
    tableHeight = 12;
    for (int i = 1; i < tableHeight; i++) {
        gotoxy(offsetX, offsetY + tableHeight + i); printf("%c", 186);
        gotoxy(offsetX + tableWidth - 1, offsetY + tableHeight + i); printf("%c", 186);
    }

    // Garis bawah kotak kedua
    gotoxy(offsetX, offsetY + 2 * tableHeight); printf("%c", 200);
    for (int i = 1; i < tableWidth - 1; i++) {
        printf("%c", 205);
    }
    printf("%c\n", 188);
}

int main() {
    table();
    return 0;
}

