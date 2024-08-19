#include <ncurses.h>
#include <iostream>

int key;
bool menu = true;


int main(){
    initscr();
    keypad(stdscr, TRUE);

    //---------------- Bucle menú de inicio----------------//
    while (menu){
        //---------------- INPUT menú de inicio----------------//
        key = getch();
        switch (key){
        case 27:
            endwin();
            menu = false;
            break;
        default:
            break;
        }
    }

    return 0;
}
