#include <iostream>
#include <ctime>
#include <cstdlib>
#include <thread>
#include <windows.h>
#include <cstring>
#include "Ascii art.cpp"            //ascii art for the winning screen code
using namespace std;

bool gameover=false;

char board [15][15];    //2 dimensional array, positions could also be done using a single array since squares are numbered

void initialize_board(){
    cout<<endl<<"please wait while we prepare your game board"<<endl;
    for(int i=0;i<15;i++){
        for(int j=0;j<15;j++){
            board[i][j]=' ';
        }
    }
    for(int k=0;k<5;k++){
        srand(time(0));
        int x= (rand()%14)+1;
        int y= (rand()%14)+1;
        if(board[x][y]!=' '){
            x= (rand()%14)+1;
            y= (rand()%14)+1;
        }
        board[x][y]='+';
         Sleep(1000);
    }
    for(int k=0;k<5;k++){
        srand(time(0));
        int x= (rand()%14)+1;
        int y= (rand()%14)+1;

        if(board[x][y]!=' '){           //condition to make sure no 2 + or - are in the same position
            x= (rand()%14)+1;
            y= (rand()%14)+1;
        }
        board[x][y]='-';
         Sleep(1000);
    }
}

void print_board(){



        system("cls");              //clear screen function to simulate updating the console
    cout<<endl;
    int c=1;
    for(int i=0; i<=14; i++){
        for(int j=0; j<=15; j++){
            if(j%16==0){
                    cout<<" -------------------------------------------------------------"<<endl;

            }
            if(board[j][i]=='+'){
                    cout<<" | ";
                    HANDLE h= GetStdHandle(STD_OUTPUT_HANDLE);
                    SetConsoleTextAttribute(h,10);
                    cout<<board[j][i];

             }else if(board[j][i]=='-'){
                    HANDLE h= GetStdHandle(STD_OUTPUT_HANDLE);
                    SetConsoleTextAttribute(h,7);
                    cout<<" | ";
                    h= GetStdHandle(STD_OUTPUT_HANDLE);
                    SetConsoleTextAttribute(h,12);
                    cout<<board[j][i];
                } else{
                    HANDLE h= GetStdHandle(STD_OUTPUT_HANDLE);
                    SetConsoleTextAttribute(h,7);
                    cout<<" | "<<board[j][i];}
        }
        cout<<endl;
    }
    cout<<" -------------------------------------------------------------"<<endl;




}


class player{
public:
    string name;
    char symbol;
    int health;
    int x,y;                //position variables
public:
    player(string name){
        this->name = name;
        this->symbol=name[0];
        health = 10;
        x=0;                    //starting at (0,0)
        y=0;
    }
};


void nve(player& a);                    //function prototype so we can call it in the move function
void pve(player& a);

void move(player& a, int steps){        //standard move
    board[a.x][a.y]=' ';
    if((a.x==0) && (a.y==0)){           //this condition is to follow the logic that when the game starts both players are off the board so the first "step" in the game gets them to position [0,0]

        for(int i=0; i<steps-1; i++){
        if(a.x!=14){
            a.x++;
        }else{
            a.x=0;
            a.y++;
        }
        }
    }else{
        for(int i=0; i<steps; i++){
        if(a.x!=14){
            a.x++;
        }else if(a.y==14){
            gameover=true;
        }else{
            a.x=0;
            a.y++;
        }
        }
    }

    if(board[a.x][a.y]=='+'){            //postive function call
        board[a.x][a.y]=' ';
        pve(a);
        board[a.x][a.y]=a.symbol;

    }else if(board[a.x][a.y]=='-'){      //negative function call
        board[a.x][a.y]=' ';
        nve(a);
        board[a.x][a.y]=a.symbol;

    } else if(board[a.x][a.y]!=' '){     //if both players are in the same cell
        board[a.x][a.y]='&';
    }else{                              //normal cell call
        board[a.x][a.y]=a.symbol;
    }
}


void up(player& a){            //ladder up cell
   move(a,5);
}
void healthup(player& a){       //health up
    if(a.health>0){
        a.health+=5;
    }
}
void pve(player& x){            //+ve function to randomize between healthup and ladder up
    srand(time(0));
    int which= (rand()%2)+1;
    if(which==1){
       up(x);
    }else{
        healthup(x);
    }
}


void down(player& a){            //ladderdown cell
     board[a.x][a.y]=' ';
    for(int i=0; i<5; i++){     //move 5 steps backward
        if(a.x!=0){
            a.x--;
        }else{
            a.x=14;
            a.y--;
        }
    }
    board[a.x][a.y]=a.symbol;
}
void healthdown(player& a){     //healthdown
    a.health-=5;
    if(a.health<=0){
        gameover=true;
    }
}
void nve(player& x){
    srand(time(0));
    int which= (rand()%2)+1;
    if(which==1){
       down(x);
    }else{
        healthdown(x);
    }
}


int dice(player& x){             //Dice function using random int generator
    srand(time(0));
    int roll = (rand()%6)+1;    //this line sets the range of numbers (1-6)
    cout<<endl<<"the number is "<<roll<<endl;         //unnecessary output just to try the function
    move(x,roll);
    return roll;
}
