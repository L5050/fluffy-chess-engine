#include <iostream>
#include <string>
#include <vector>

using namespace std;
#define EMPTY 0
#define PAWN 1
#define KNIGHT 2
#define BISHOP 3
#define ROOK 4
#define QUEEN 5
#define KING 6
#define EN_PASSANT 7

int board[64] = {
    ROOK, KNIGHT, BISHOP, QUEEN, KING, BISHOP, KNIGHT, ROOK,
    PAWN, PAWN, PAWN, PAWN, PAWN, PAWN, PAWN, PAWN,
    EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY,
    EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY,
    EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY,
    EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY,
    -PAWN, -PAWN, -PAWN, -PAWN, -PAWN, -PAWN, -PAWN, -PAWN,
    -ROOK, -KNIGHT, -BISHOP, -QUEEN, -KING, -BISHOP, -KNIGHT, -ROOK
};
int posBoard[64] = {
    ROOK, KNIGHT, BISHOP, QUEEN, KING, BISHOP, KNIGHT, ROOK,
    PAWN, PAWN, PAWN, PAWN, PAWN, PAWN, PAWN, PAWN,
    EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY,
    EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY,
    EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY,
    EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY,
    -PAWN, -PAWN, -PAWN, -PAWN, -PAWN, -PAWN, -PAWN, -PAWN,
    -ROOK, -KNIGHT, -BISHOP, -QUEEN, -KING, -BISHOP, -KNIGHT, -ROOK
};
vector<int> pawnMoves;
vector<int> bishopMoves;
vector<int> knightMoves;
vector<int> rookMoves;
vector<int> queenMoves;
vector<int> kingMoves;
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

char* stringToArray(string s) {
  char* array = new char[s.length() + 1];
    array[s.length()] = '\0';
    for (int i = 0; i < s.length(); i++) {
        array[i] = s[i];
    }
    return array;
}

int positionToArrayCoords(string s){
    int file = s[0] - 'a';
    int rank = s[1] - '1';
    return 8 * rank + file;
}


string arrayCoordsToPosition(int coords) {
    string pos;
    pos += 'a' + (coords % 8);
    pos += '8' - (coords / 8);
    return pos;
}

void calcLegalMoves() {
  for(int i=0;i<64;i++)
  {
      if(posBoard[i] == BISHOP)
      {
          for(int j=0;j<64;j++)
          {
              if(abs(i/8 - j/8) == abs(i%8 - j%8) && posBoard[j] <= 0)
              {
                  bishopMoves.push_back(i);
              }
          }
      }
      if(posBoard[i] == KNIGHT)
      {
            int row = i/8, col = i%8;
            int potentialMoves[8][2] = {{-2, -1}, {-2, 1}, {-1, -2}, {-1, 2}, {1, -2}, {1, 2}, {2, -1}, {2, 1}};
            for(int j=0;j<8;j++) {
                int destRow = row + potentialMoves[j][0];
                int destCol = col + potentialMoves[j][1];
                if(destRow >= 0 && destRow < 8 && destCol >= 0 && destCol < 8) {
                    int destIndex = 8*destRow + destCol;
                    if(posBoard[destIndex] <= 0) {
                        knightMoves.push_back(destIndex);
                    }
                }
            }
        }
        if(posBoard[i] == ROOK) {
            int row = i / 8, col = i % 8;
            // Check horizontal directions
            for(int j = col - 1; j >= 0; j--) { // Check left
                int index = 8 * row + j;
                if(posBoard[index] == EMPTY) {
                    rookMoves.push_back(index);
                } else if(posBoard[index] < 0) {
                    rookMoves.push_back(index);
                    break;
                } else {
                    break;
                }
            }
            for(int j = col + 1; j < 8; j++) { // Check right
                int index = 8 * row + j;
                if(posBoard[index] == EMPTY) {
                    rookMoves.push_back(index);
                } else if(posBoard[index] < 0) {
                    rookMoves.push_back(index);
                    break;
                } else {
                    break;
                }
            }
            // Check vertical directions
            for(int j = row - 1; j >= 0; j--) { // Check up
                int index = 8 * j + col;
                if(posBoard[index] == EMPTY) {
                    rookMoves.push_back(index);
                } else if(posBoard[index] < 0) {
                    rookMoves.push_back(index);
                    break;
                } else {
                    break;
                }
            }
            for(int j = row + 1; j < 8; j++) { // Check down
                int index = 8 * j + col;
                if(posBoard[index] == EMPTY) {
                    rookMoves.push_back(index);
                } else if(posBoard[index] < 0) {
                    rookMoves.push_back(index);
                    break;
                } else {
                    break;
                }
            }
        }
        if(posBoard[i] == QUEEN) {
          int row = i / 8, col = i % 8;
    int dx[8] = {-1, -1, -1, 0, 0, 1, 1, 1};
    int dy[8] = {-1, 0, 1, -1, 1, -1, 0, 1};

    for(int d = 0; d < 8; d++) {
        for(int j = 1; j < 8; j++) {
            int x = row + dx[d] * j, y = col + dy[d] * j;
            if(x < 0 || x >= 8 || y < 0 || y >= 8) break;
            int index = 8 * x + y;
            if(posBoard[index] == EMPTY) {
                queenMoves.push_back(index);
            } else if(posBoard[index] < 0) {
                queenMoves.push_back(index);
                break;
            } else {
                break;
            }
        }
  }}
  if(posBoard[i] == KING) {
    int row = i / 8, col = i % 8;
    int dx[8] = {-1, -1, -1, 0, 0, 1, 1, 1};
    int dy[8] = {-1, 0, 1, -1, 1, -1, 0, 1};

    for(int d = 0; d < 8; d++) {
        int x = row + dx[d], y = col + dy[d];
        if(x >= 0 && x < 8 && y >= 0 && y < 8) {
            int index = 8 * x + y;
            if(posBoard[index] <= 0) {
                kingMoves.push_back(index);
            }
        }
    }
  }
  if (posBoard[i] == PAWN) {
            if (posBoard[i] > 0) {
                // Move one square forward
                int move = i + 8;
                if (posBoard[move] == EMPTY) {
                    pawnMoves.push_back(move);
                }
                // Move two squares forward
                if (i < 16 && posBoard[move + 8] == EMPTY) {
                    pawnMoves.push_back(move + 8);
                }
                // Capture to the left
                int leftCapture = i + 7;
                if (leftCapture % 8 != 7 && posBoard[leftCapture] < 0) {
                  pawnMoves.push_back(leftCapture);
                }
                // Capture to the right
                int rightCapture = i + 9;
                if (rightCapture % 8 != 0 && posBoard[rightCapture] < 0) {
                  pawnMoves.push_back(rightCapture);
                }
                //En Passant
                if (i % 8 != 0 && posBoard[i + 7] == PAWN && i + 7 == EN_PASSANT) {
                  pawnMoves.push_back(i + 7);
                }
                if (i % 8 != 7 && posBoard[i + 9] == PAWN && i + 9 == EN_PASSANT) {
                  pawnMoves.push_back(i + 9);
                }
            }
        }
    }
}

//pawns = 100, bishops 300, knights 300, rooks 500, queens 900

float evaluatePosition() {
  int total_material = 0;
for (int i = 0; i < 64; i++) {
    if (posBoard[i] == ROOK) {
        total_material += 500;
    }
    else if (posBoard[i] == KNIGHT) {
        total_material += 300;
    }
    else if (posBoard[i] == BISHOP) {
        total_material += 300;
    }
    else if (posBoard[i] == QUEEN) {
        total_material += 900;
    }
    else if (posBoard[i] == PAWN) {
        total_material += 100;
    }
    else if (posBoard[i] == -ROOK) {
        total_material -= 500;
    }
    else if (posBoard[i] == -KNIGHT) {
        total_material -= 300;
    }
    else if (posBoard[i] == -BISHOP) {
        total_material -= 300;
    }
    else if (posBoard[i] == -QUEEN) {
        total_material -= 900;
    }
    else if (posBoard[i] == -PAWN) {
        total_material -= 100;
    }
    }
    int evaluation = total_material;
  float f = evaluation;
  f = f / 100;
  return f;
}

int main()
{
    revertBoards(0);
    cout<<evaluatePosition();
    cout<<positionToArrayCoords("a3");
    cout<<"\nHello World";

    return 0;
}
