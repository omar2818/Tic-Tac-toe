#include <bits/stdc++.h>
using namespace std;
#define COM 1 
#define COMPUTER 1
#define HUMAN 2 
#define SIDE 3
char COMPUTERMOVE='X';
char HUMANMOVE='O';

//  give initial value to the board
void initialBoard(char board[][SIDE]){
    for(int i=0;i<SIDE;i++){
        for(int j=0;j<SIDE;j++){
            board[i][j]=' ';
        }
    }
}

// print the board
void showBoard(char board[][SIDE]){
    for(int i=0;i<SIDE;i++){
        for(int j=0;j<SIDE;j++){
            cout<<" "<<board[i][j]<<" ";
            if(j<2){
                cout<<"|";
            }
        }
        cout<<"\n";
        if(i<2){
            for(int j=0;j<SIDE;j++){
                cout<<"---";
                if(j<2){
                    cout<<"-";
                }
            }
            cout<<"\n";
        }
    }
}

// print game rules
void showrules(){
    cout<<"Choose a cell numbered from 1 to 9 as below and play\n";
    for(int i=0;i<SIDE;i++){
        for(int j=0;j<SIDE;j++){
            cout<<" "<<(i*3)+j+1<<" ";
            if(j<2){
                cout<<"|";
            }
        }
        cout<<"\n";
        if(i<2){
            for(int j=0;j<SIDE;j++){
                cout<<"---";
                if(j<2){
                    cout<<"-";
                }
            }
            cout<<"\n";
        }
    }
}

// print the winner
void printWinner(int turn){
    if(turn==COM){
        cout<<"COMPUTER has won\n";
    }else{
        cout<<"HUMAN has won\n";
    }
}

// check if there win in a rows
bool rowwin(char board[][SIDE]){
    for(int i=0;i<SIDE;i++){
        if(board[i][0]==board[i][1] && board[i][0]==board[i][2] && board[i][0]!=' '){
            return true;
        }
    }
    return false;
}

// check if there win in a columns
bool colwin(char board[][SIDE]){
    for(int i=0;i<SIDE;i++){
        if(board[0][i]==board[1][i] && board[0][i]==board[2][i] && board[0][i]!=' '){
            return true;
        }
    }
    return false;
}

// check if there are diagonal win
bool diagonalwin(char board[][SIDE]){
    if(board[0][0]==board[1][1] && board[0][0]==board[2][2] && board[0][0]!=' '){
        return true;
    }
    if(board[0][2]==board[1][1] && board[0][2]==board[2][0] && board[0][2]!=' '){
        return true;
    }
    return false;
}

// check if there are any win
bool gameOver(char board[][SIDE]){
    return (rowwin(board)||colwin(board)||diagonalwin(board));
}

// check if board is complete
bool leftMoves(char board[][SIDE]){
    for(int i=0;i<SIDE;i++){
        for(int j=0;j<SIDE;j++){
            if(board[i][j]==' '){
                return true;
            }    
        }
    }
    return false;
}

// mini max function to evaluate the moves
int minimax(char board[][SIDE],int depth,int explore,bool isAI){
    int score=0,bestScore=0;
    if(gameOver(board)==true){
        if(isAI==true){
            return -1;
        }else{
            return 1;
        }
    }else{
        if(depth<min(9,explore)){
            if(isAI==true){
                bestScore=-999;
                for(int i=0;i<SIDE;i++){
                    for(int j=0;j<SIDE;j++){
                        if(board[i][j]==' '){
                            board[i][j]=COMPUTERMOVE;
                            score=minimax(board,depth+1,explore,false);
                            board[i][j]=' ';
                            if(score > bestScore){
                                bestScore=score;
                            }
                        }
                    }  
                }
                return bestScore;
            }else{
                bestScore=999;
                for(int i=0;i<SIDE;i++){
                    for(int j=0;j<SIDE;j++){
                        if(board[i][j]==' '){
                            board[i][j]=HUMANMOVE;
                            score=minimax(board,depth+1,explore,true);
                            board[i][j]=' ';
                            if(score < bestScore){
                                bestScore=score;
                            }
                        }
                    }  
                }
                return bestScore;
            }
        }else{
            return 0;
        }
    }
}

// find the best move for the computer 
int bestMove(char board[][SIDE],int moveIndex,int difficulty){
    int x=-1,y=-1,score=0,bestScore=-999;
    for(int i=0;i<SIDE;i++){
        for(int j=0;j<SIDE;j++){
            if(board[i][j]==' '){
                board[i][j]=COMPUTERMOVE;
                score=minimax(board,moveIndex+1,moveIndex+difficulty,false);
                board[i][j]=' ';
                if(score > bestScore){
                    bestScore=score;
                    x=i;
                    y=j;
                }
            }
            
        }  
    }
    return (x*3)+y;
}

// let's start playing
void letsplay(int turn,int difficulty){
    int moveIndex=0,x=0,y=0;
    char board[SIDE][SIDE];
    showrules();
    initialBoard(board);
    while(leftMoves(board)==true && gameOver(board)==false){
        int pos;
        if(turn==HUMAN){
            cout<<"You can choose any of the following cells : ";
            for(int i=0;i<SIDE;i++){
                for(int j=0;j<SIDE;j++){
                    if(board[i][j]==' '){
                        cout<<(i*3)+j+1<<" ";
                    }    
                }
            }
            cout<<"\n Enter the position ";
            cin>>pos;
            pos--;
            x=pos/3; 
            y=pos%3; 
            if(board[x][y]==' ' && pos>=0 && pos<9){
                board[x][y]=HUMANMOVE;
                cout<<"\n you choosed cell number "<<pos+1<<"\n";
                showBoard(board);
                moveIndex++;
                turn=COM;
            }else if(board[x][y]!=' ' && pos>=0 && pos<9){
                cout<<"\nPosition is occupied, select any one position from the available positions\n";
            }else{
                cout<<"\n invalid position \n";
            }
        }else{
            pos=bestMove(board,moveIndex,difficulty);
            x=pos/3;
            y=pos%3;
            board[x][y]=COMPUTERMOVE;
            cout<<"\n computer choosed cell number "<<pos+1<<"\n";
            showBoard(board);
            moveIndex++;
            turn=HUMAN;
        }
        
    }
    if(gameOver(board)==true){
        if(turn==HUMAN){
            turn=COM;
        }else{
            turn=HUMAN;
        }
        printWinner(turn);
    }else{
        cout<<"it is draw \n";
    }
}

int main()
{
    cout<<"Tic-Tac-Toe \n";
    char ch,quit='n',start,difficulty;
    int level;
    while(quit=='n'){
        // taking some info from the user
        cout<<"Do you want to start first ? (y/n)";
        cin>>start;
        if(start=='y' || start=='n'){
            cout<<"Do you want play Hard or Easy? (h/e)";
            cin>>difficulty;
            if(difficulty=='h'){
                level=9;
            }else if(difficulty=='e'){
                level=2;
            }else{
                cout<<"\n invalid choise (try to choose h or e) \n";
                continue;
            }
            cout<<"\n which sympol you want to play with ? (x/o)";
            cin>>ch;
            if(ch=='X' || ch=='x'){
                COMPUTERMOVE='O';
                HUMANMOVE='X';
                if(start=='y'){
                    letsplay(HUMAN,level);
                }else{
                    letsplay(COM,level);
                }
            }else if(ch=='O' || ch=='o'){
                COMPUTERMOVE='X';
                HUMANMOVE='O';
                if(start=='y'){
                    letsplay(HUMAN,level);
                }else{
                    letsplay(COM,level);
                }
            }else {
                cout<<"\n invalid choise (try to choose X or O \n";
                continue;
            }
        }else{
            cout<<"\n invalid choise (try to choose y or n (lower case only)\n";
            continue;
        }
        cout<<" do you want to quit (y/n)\n";
        cin>>quit;
    }
    return 0;
}