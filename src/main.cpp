#include <iostream>
#include <string>

int board[64] =
    {-1,-2,-3,-4,-5,-3,-2,-1,
     -6,-6,-6,-6,-6,-6,-6,-6,
      0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0,
      6, 6, 6, 6, 6, 6, 6, 6,
      1, 2, 3, 4, 5, 3, 2, 1};
int posBoard[64] =
    {-1,-2,-3,-4,-5,-3,-2,-1,
     -6,-6,-6,-6,-6,-6,-6,-6,
      0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0,
      6, 6, 6, 6, 6, 6, 6, 6,
      1, 2, 3, 4, 5, 3, 2, 1};

void revertBoards(bool way){
if (way == 0){
for (int i = 0; i < 64; i++) {
board[i] = posBoard[i];
}}
if (way == 1){
for (int i = 0; i < 64; i++) {
posBoard[i] = board[i];
}}
}

//pawns = 100, bishops 300, knights 300, rooks 500, queens 900

float evaluatePosition() {
  int evaluation = 0;
    for (int i = 0; i < 64; i++) {
      switch (posBoard[i]) {
        case 1:
        evaluation += 500;
        break;
        case 2:
        evaluation += 300;
        break;
        case 3:
        evaluation += 300;
        break;
        case 4:
        evaluation += 900;
        break;
        case 6:
        evaluation += 100;
        break;
        case -1:
        evaluation -= 500;
        break;
        case -2:
        evaluation -= 300;
        break;
        case -3:
        evaluation -= 300;
        break;
        case -4:
        evaluation -= 900;
        break;
        case -6:
        evaluation -= 100;
        break;
      }
    }
  float f = evaluation;
  f = f / 100;
  return f;
}

int main()
{
    revertBoards(0);
    cout<<evaluatePosition();
    cout<<"\nHello World";

    return 0;
}
