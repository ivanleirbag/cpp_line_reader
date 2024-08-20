#include <ncurses.h>
#include <iostream>

#define ESC 27
#define ENTER 10
#define TAB 9
#define SPACE 32
#define PLUS 43
#define AMPERSAND 38
#define HASH 35

int key, words, lines, chars, charsPlus;
int last_three[3];
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

            //Reiniciamos el contador en 0 por cada vez que se vuelva a ingresar al programa
            counter = 0;
            while ((key = getch()) != ENTER){
                //Llena los primeros 3 caracteres ingresados
                move(row, col); //posiciona correctamente el texto ingresado por el usuario
                col++;
                if (counter < 3){
                    last_three[counter] = key;
                    counter++;
                //Si ya están llenos todos los espacios, empieza a desplazarlos
                }else{
                    for (int i = 0; i < 3; i++){
                        if (i!=2){
                            last_three[i] = last_three[i+1];
                        }else{
                            last_three[2] = key;
                        }
                    }
                }

                switch (key){
                case ESC:
                    endwin();
                    running = false;
                    key = ENTER;
                    break;
                case SPACE: 
                    if(last_three[1] != SPACE && last_three[1] != TAB && last_three[1] != ENTER){
                        words++;
                    }
                    break;
                case TAB:
                    if(last_three[1] != SPACE && last_three[1] != TAB && last_three[1] != ENTER){
                        words++;
                    }
                    break;
                default:
                    chars ++;
                    break;
                }
            }

            if(last_three[0] == PLUS && last_three[1] == AMPERSAND && last_three[2] == HASH){
                printw("Termino");
            }
            row++;
            col = 0;
            lines++;
        }
    }
        
        /*
        move(row, col); //posiciona correctamente el texto ingresado por el usuario
        if (counter < 3){
            counter++;
        }else{
            counter = 0;
        }

        col++;
        //----------------Manejo del input----------------//
        key = getch();
        switch (key){
        case ESC:
            endwin();
            running = false;
            break;
        case ENTER:
            row++;
            col = 0;
            charsPlus++;
            lines++;
            words++;
            break;
        case SPACE:
            charsPlus++;
            words++;
            break;
        case TAB:
            col += 3;
            charsPlus++;
            words++;
            break;            
        default:
            chars ++;
            break;
        }

        //----------------Guarda los últimos 3 caracteres----------------//
        switch (counter)
        {
        case 0:
            frst = key;
            break;
        case 1:
            scnd = key;
            break;
        case 2:
            thrd = key;
            break;
        default:
            break;
        }
        move(30,0);
        printw("primer=%d - segundo=%d - tercer=%d", frst, scnd, thrd);
        if(frst==PLUS && scnd == AMPERSAND && thrd == HASH){
            printw("palabras=%d - lineas=%d - caracteres=%d - caracteresPlus=%d", words, lines, chars, charsPlus);
        }
        */
    endwin();
    return 0;
}
