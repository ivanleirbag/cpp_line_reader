#include <ncurses.h>
#include <iostream>
#include <array>

//Alumno: Peceto, Iván Gabriel      Legajo: 7197
//Comando para compilar en linux:  g++ -Wall -g ./line_reader.cpp -o liner -lncurses

using namespace std;

#define ESC 27
#define ENTER 10
#define TAB 9
#define SPACE 32
#define PLUS 43
#define AMPERSAND 38
#define HASH 35

int buffer_clean, words, chars, charsPlus;
int lines = 0;
int counter = 0;
array<int, 5> last_five = {ENTER,ENTER,ENTER,ENTER,ENTER};
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
        lines = 0;
        charsPlus = 0;
        counter = 0;
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
        //------------------Bucle principal------------------//
        while(running){
            
            
            curs_set(1);
            move(row, col); //posiciona correctamente el texto ingresado por el usuario
            //------------------Bucle de inputs por linea------------------//
            while (true){
                int key = getch();
                flushinp(); //Limpia el buffer (por prevención)
                col++; //Avanza un caracter
                move(row, col); //posiciona correctamente el texto ingresado por el usuario

                if(key == ESC){        //La tecla ESC cierra el bucle principal
                    running = false;
                    break;
                }

                counter ++; //Toma registro de cuantos caracteres se han ingresado
                for (int i = 0; i < 4; i++){        //Ordena los elementos del array cada vez que se ingresa un caracter nuevo
                    last_five[i] = last_five[i+1]; 
                }
                last_five[4] = key;

                if(key == SPACE || key == TAB || key == ENTER){       
                    if(last_five[3] != SPACE && last_five[3] != TAB  && last_five[3] != ENTER){ //Evita contar espacios como palabras
                        words++;
                    }
                    charsPlus++;
                }
                if(key == ENTER){
                    lines++;
                    break;
                }else if(key != SPACE && key != TAB){
                    chars++;
                    charsPlus++;
                }
                //------------DEBUGGING------------//
                /*clear();
                move(0, 30);
                printw("%d %d %d %d", words,lines,chars,charsPlus);
                move(1, 30);
                printw("%d %d %d %d", last_five[0],last_five[1],last_five[2],last_five[3]);
                move(row, col);*/
            }

            //----------------COMANDO DE ESCAPE Y PROCESAMIENTO DE NUEVAS LINEAS----------------//
            if(last_five[1] == PLUS && last_five[2] == AMPERSAND && last_five[3] == HASH){ 
                if (counter < 5){ //si solo se ingresó el comando, no se cuenta la linea
                    lines--;
                }
                chars -=3;
                charsPlus -=4;
                switch (last_five[0]) //Chequea si hace falta descontar +&# o espacios como palabra
                {
                case TAB: case SPACE: 
                    words -=1;
                    break;
                case ENTER:
                    words -=1;
                    if(lines > 0){
                        lines -=1;
                    }
                default:
                    break;
                }
                curs_set(0);
                move(row+1, 0);
                printw("palabras=%d - lineas=%d - caracteres=%d - caracteresPlus=%d", words, lines, chars, charsPlus);
                move(row+3, 0);
                refresh();
                //-------Bucle de comandos de reinicio-------//
                printw("Presione [ENTER] para continuar o [ESC] para salir.");
                do{
                    key = getch();
                    if(key == ENTER){
                        words = 0;
                        lines = 0;
                        chars = 0;
                        charsPlus = 0;
                        counter = 0;
                        key = 0;
                        row = 0;
                        col = 0;
                        clear();
                        move(row,col);
                    }else if (key == ESC){
                        running = false;
                        break;
                    }}while(key != ENTER && key != ESC);   
            }else{
                row++;
                col = 0;
            }

            //------------DEBUGGING------------//
            /*move(0, 30);
            printw("%d %d %d %d", words,lines,chars,charsPlus);
            move(1, 30);
            printw("%d %d %d %d", last_five[0],last_five[1],last_five[2],last_five[3]);
            move(row, col);*/
            
        }
    }
    endwin();
    return 0;
}
