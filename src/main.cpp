#include <iostream>
#include <vector>
#include <fstream>
#include <stdio.h>
#include <unistd.h>


#if defined(__unix__)  
    #include <termios.h>
#endif
#if defined(_WIN32) || defined(WIN32) 
    #include <conio.h>
#endif

using namespace std;

#include "todo.h"
#include "menu.h"

#ifdef __unix__
 char getch() {
        char buf = 0;
        struct termios old = {0};
        if (tcgetattr(0, &old) < 0)
                perror("tcsetattr()");
        old.c_lflag &= ~ICANON;
        old.c_lflag &= ~ECHO;
        old.c_cc[VMIN] = 1;
        old.c_cc[VTIME] = 0;
        if (tcsetattr(0, TCSANOW, &old) < 0)
                perror("tcsetattr ICANON");
        if (read(0, &buf, 1) < 0)
                perror ("read()");
        old.c_lflag |= ICANON;
        old.c_lflag |= ECHO;
        if (tcsetattr(0, TCSADRAIN, &old) < 0)
                perror ("tcsetattr ~ICANON");
        return (buf);
}
#endif 



int main(){
    ToDoList tdl;
    tdl.load(); //load the data from 'data.td'
    char menuChoice = 'c';

    #ifdef __unix__
        system("clear");
    #else
        system("cls");
    #endif

    while(menuChoice != 'q'){
        Menu::displayTitle(); //display the toDoList
        tdl.display();
        Menu::displayMenu();

        //get the user's input
        #ifdef __unix__
            menuChoice = getch();
        #else
            menuChoice = _getch();
        #endif

        if(menuChoice == 'e')
            tdl.addTD(Menu::createTD());
        if(menuChoice == 'd')
            tdl.removeTD();
        if(menuChoice == 'z')
            tdl.addSelector(-1);
        if(menuChoice == 's')
            tdl.addSelector(+1);

        #ifdef __unix__
            system("clear");
        #else
            system("cls");
        #endif
    }
    tdl.save(); //the data are save automatically at the end of the program
    return 0;
}