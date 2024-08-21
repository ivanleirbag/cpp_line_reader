#include <ncurses.h>
#include <iostream>

#define ESC 27
#define ENTER 10
#define TAB 9
#define SPACE 32
#define PLUS 43
#define AMPERSAND 38
#define HASH 35

int key, words, chars, charsPlus;
int lines = 1;
int last_four[4] = {0,0,0,0};
int counter;
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
        counter = 0;
        curs_set(0);
        clear();
        printw("> Presiona [ENTER] para comenzar.\n\n");
        printw("> Presiona [ESC] para cerrar el programa.");

        key = getch();
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

            while ((key = getch()) != ENTER){
                col++;
                move(row, col); //posiciona correctamente el texto ingresado por el usuario

                if(key == ESC){
                    endwin();
                    running = false;
                    break;
                }else if(key == SPACE || key == TAB){
                    if(counter > 0){
                        if(last_four[counter-1] != SPACE && last_four[counter-1] != TAB && last_four[counter-1] != ENTER){
                            words++;
                        }
                        charsPlus++;
                    }
                }else{
                    chars++;
                }
                
                //Llena los primeros 3 caracteres ingresados
                if (counter < 4){
                    last_four[counter] = key;
                    counter++;
                //Si ya están llenos todos los espacios, empieza a desplazarlos
                }else{
                    for (int i = 0; i < 4; i++){
                        if (i!=3){
                            last_four[i] = last_four[i+1];
                        }else{
                            last_four[3] = key;
                        }
                    }
                }
            }

            if(last_four[1] == PLUS && last_four[2] == AMPERSAND && last_four[3] == HASH){
                if(last_four[1] != SPACE && last_four[2] != TAB && last_four[2] != ENTER){
                            words++;
                }
                chars -=3;
                move(row+1, 0);
                printw("palabras=%d - líneas=%d - caracteres=%d - caracteresPlus=%d", words, lines, chars, charsPlus);
            }
            row++;
            col = 0;
            charsPlus++;
            lines++;
        }
    }
    endwin();
    return 0;
}
