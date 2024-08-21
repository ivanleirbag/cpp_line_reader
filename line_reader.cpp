#include <ncurses.h>
#include <iostream>
#include <array>

using namespace std;

#define ESC 27
#define ENTER 10
#define TAB 9
#define SPACE 32
#define PLUS 43
#define AMPERSAND 38
#define HASH 35

int buffer_clean, words, chars, charsPlus;
int lines = 1;
array<int, 4> last_four = {ENTER};
bool running = false;
bool menu = true;
int row, col;


int main(){
    initscr();
    keypad(stdscr, TRUE);


    //---------------- Bucle del programa----------------//
    while(menu){

        row = 0;
        col = 0;
        words = 0;
        chars = 0;
        charsPlus = 0;
        curs_set(0);
        clear();
        printw("> Presiona [ENTER] para comenzar.\n\n");
        printw("> Presiona [ESC] para cerrar el programa.");

        int key = getch();
        switch (key)
        {
        case ENTER:
            running = true;
            clear();
            break;
        case ESC:
            endwin();
            menu = false;
            break;
        default:
            break;
        }

        while(running){
            curs_set(1);
            move(row, col); //posiciona correctamente el texto ingresado por el usuario

            while (true){
                int key = getch();
                flushinp();
                col++;
                move(row, col); //posiciona correctamente el texto ingresado por el usuario

                if(key == ESC){        
                    running = false;
                    break;
                }

                for (int i = 0; i < 3; i++){        //Ordena los elementos del array cada vez que se ingresa un caracter nuevo
                    last_four[i] = last_four[i+1]; 
                }
                last_four[3] = key;

                if(key == SPACE || key == TAB || key == ENTER){         //Evita contar palabras de más cuando se presiona espacio/tab/enter mas de una vez
                    if(last_four[2] != SPACE && last_four[2] != TAB  && last_four[2] != ENTER){
                        words++;
                    }
                    charsPlus++;
                }

                if(key == ENTER){
                    break;
                }else{
                    chars++;
                }
                //------------DEBUGGING------------//
                /*move(0, 30);
                printw("%d %d %d %d", words,lines,chars,charsPlus);
                move(1, 30);
                printw("%d %d %d %d", last_four[0],last_four[1],last_four[2],last_four[3]);
                move(row, col);*/
            }


            if(last_four[0] == PLUS && last_four[1] == AMPERSAND && last_four[2] == HASH){
                chars -=3;
                curs_set(0);
                move(row+1, 0);
                printw("palabras=%d - lineas=%d - caracteres=%d - caracteresPlus=%d", words, lines, chars, charsPlus);
                move(row+2, 0);
            }

            //------------DEBUGGING------------//
            /*move(0, 30);
            printw("%d %d %d %d", words,lines,chars,charsPlus);
            move(1, 30);
            printw("%d %d %d %d", last_four[0],last_four[1],last_four[2],last_four[3]);
            move(row, col);*/
            row++;
            col = 0;
            charsPlus++;
            lines++;
        }
    }
    endwin();
    return 0;
}
