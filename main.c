#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>
#include <conio.h>

char board[3][3];
const char PLAYER = 'X';
const char COMPUTER = 'O';

void resetBoard();
void printBoard();
int checkFreeSpaces();
void playerMove();
void computerMove();
char checkWinner();
void printWinner(char);

int main(){
  char winner = ' ';
  resetBoard();
  while (winner ==' ' && checkFreeSpaces()!=0)
  {
    printBoard();

    playerMove();
    winner = checkWinner();
    if(winner !=' ' || checkFreeSpaces()==0){
      break;
    }

    computerMove();
    winner = checkWinner();
    if(winner !=' ' || checkFreeSpaces()==0){
      break;
    }
  }

  printBoard();
  printWinner(winner);
  _getch();
  return 0;
}

void resetBoard(){
  for(int i=0; i<3; i++)
  {
    for(int j = 0; j<3; j++)
    {
      board[i][j]= ' ';
    }
  }
}

void printBoard(){
  printf(" %c | %c | %c ",board[0][0], board[0][1], board[0][2]);
  printf("\n---|---|---\n");
  printf(" %c | %c | %c ",board[1][0], board[1][1], board[1][2]);
  printf("\n---|---|---\n");
  printf(" %c | %c | %c ",board[2][0], board[2][1], board[2][2]);
  printf("\n");
}

int checkFreeSpaces(){
  int freeSpaces = 9;

  for(int i=0;i<3; i++){
    for(int j=0;j<3; j++){
      if(board[i][j]!=' '){
        freeSpaces--;
      }
    }
  }
  return freeSpaces;
}

void playerMove(){
  int x;
  int y;
  do{
    printf("Enter row #(1-3): ");
    scanf("%d", &x);
    x--;
    printf("Enter column #(1-3): ");
    scanf("%d", &y); // исправлено

    if(board[x][y-1]!=' ') // учтено смещение индекса
    {
      printf("Invalid move\n");
    }else{
      board[x][y-1] = PLAYER; // учтено смещение индекса
      break;
    }
  }while(board[x][y-1] !=' ');
}

void computerMove(){
  srand(time(0));
  int x;
  int y;

  if(checkFreeSpaces()>0)
  {
    do{
      x = rand()%3;
      y = rand()%3;
    }while(board[x][y]!=' ');

    board[x][y] = COMPUTER;
  }
  else{
    printWinner(' ');
  }
}

char checkWinner(){ // возвращаемый тип изменен на char
  for(int i = 0; i<3; i++){
    if(board[i][0] == board[i][1]&& board[i][0]==board[i][2]){
      return board[i][0];
    }
  }
  for(int i = 0; i<3; i++){
    if(board[0][i] == board[1][i]&& board[0][i]==board[2][i]){
      return board[0][i]; // было board[0][1], исправлено на board[0][i]
    }
  }
  if(board[0][0] == board[1][1]&& board[0][0]==board[2][2]){
    return board[0][0];
  }
  if(board[0][2] == board[1][1]&& board[0][2]==board[2][0]){
    return board[0][2];
  }
  return ' ';
}

void printWinner(char winner){
  if(winner == PLAYER){
    printf("You win!");
  }else if (winner==COMPUTER){
    printf("You lost!");
  }else{
    printf("It's a draw.");
  }
}
