#include <cstdlib>
#include <ctime>
#include <thread>
#include <iostream>
#include <windows.h>
#include <cstring>
#include "assets.cpp"
using namespace std;

int main(){
    HANDLE h= GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(h,3);               //text colour change
    cout <<endl<<endl<< "\t\t\tLADIES & GENTLEMEN, WELCOME TO OUR GAME!!!"<<endl<<endl;

    SetConsoleTextAttribute(h,7);
    cout<<"GAME DESCRIPTION:" <<endl<<endl<< "Our game is simple and easy: players press enter every turn to roll a die"<<endl;
    cout<< "& navigate the board. Landing on a positive cell accelerates the player"<<endl;
    cout<< "by 5 steps OR increases the health by 5 points, while landing on a negative"<<endl;
    cout<<"cell decreases the health by 5 points OR decelerates the player by 5 steps."<<endl;
    cout<< "The aim of the game is to reach the final square. The game is a race"<<endl;
    cout<< "that's based on sheer luck if both players are in the same position the"<<endl;
    cout<<"game displays an '&' sign."<<endl;
    cout<<     "Wishing you the best of luck during the game!";

    cout<<endl<<endl<<"please enter player 1's name"<<endl;
    string x;
    cin>>x;
    player a(x);            //call to the player constructor

    cout<<"please enter player 2's name"<<endl;
    string y;
    cin>>y;
    player b(y);

    initialize_board();
    print_board();

    while(!gameover){                           //run game loop
        cout<<endl<<"player 1, press enter to roll dice"<<endl<<endl;
        system("pause");            //pause to wait for player's input to roll dice
        dice(a);
        print_board();
        cout<<a.name<<": "<<a.health<<endl<<b.name<<": "<<b.health<<endl;

        if(gameover){
            break;
        }

        cout<<endl<<"player 2, press enter to roll dice"<<endl<<endl;
        system("pause");
        dice(b);
        print_board();
        cout<<a.name<<": "<<a.health<<endl<<b.name<<": "<<b.health<<endl;
    }
                HANDLE n= GetStdHandle(STD_OUTPUT_HANDLE);
                SetConsoleTextAttribute(n,13);

    if((a.x>b.x)  || b.health==0){              //win screen conditions

                ascii_art(a.name);              //outputs the name in ascii art
                _getch();
                cout<<endl;
                ascii_art("you've won");
                _getch();

    }else if(b.x>a.x  || a.health==0){
                ascii_art(b.name);
                _getch();
                cout<<endl;
                ascii_art("you've won");
                _getch();

    }
    SetConsoleTextAttribute(n,7);
return 0;
}

///made by:    Team no. 22
///    -Mustafa ayman-7015915
///    -Ganna Aser Mansour-7003883
///    -Aisha Ashraf Aly-7002549
///    -Yasmine Hany Ahmed-7005638
///    -Yousef Ahmed Ebrahim-703671
