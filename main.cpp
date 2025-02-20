#include <iostream>
#include <time.h>
#include <windows.h>

void swap(int &, int &);
void shuffle(int[], int);
void board(const int[], const bool[], const bool[], int, int);
void color(unsigned int);

void swap(int &a, int &b) {
  int temp = a;
  a = b;
  b = temp;
}

void shuffle(int arr[], const int size) {
  for (int i = 0; i < size; ++i) {
    int j = rand() % size;
    swap(arr[i], arr[j]);
  }
}

void board(const int board[], const bool revealed[], const bool found[], int size, int cursor) {
  system("cls");
  for (int i = 0; i < size; i++) {
      if (found[i]) {
          color(2);
          std::cout << board[i] << "\t";
      } else if (revealed[i]) {
          color(6);
          std::cout << board[i] << "\t";
      } else {
          if (i == cursor) {
              color(14);
              std::cout << "[X]\t";
          } else {
              color(7);
              std::cout << "X\t";
          }
      }
      color(7);

      if ((i + 1) % 5 == 0) {
          std::cout << '\n';
      }
  }
}

void color(unsigned int id) {
  SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), id);
}

int main() {
  srand((unsigned int)time(0));

  const int SIZE = 20;
  int cards[SIZE] = {};
  bool revealed[SIZE] = {};
  bool found[SIZE] = {};
  int matchesFound = 0;

  for (int i = 0; i < 10; i++) {
    cards[i] = i + 1;
    cards[i + 10] = i + 1;
  }

  shuffle(cards, SIZE);

  int cursor = 0;
  int firstPick = -1, secondPick = -1;

  while (matchesFound < 10) {
    board(cards, revealed, found, SIZE, cursor);

    while(true){
      if(GetAsyncKeyState(VK_UP) & 0x8000){
        if(cursor >= 5){
          cursor = cursor - 5;
          Sleep(150);
        }
      }
      
      if(GetAsyncKeyState(VK_DOWN) & 0x8000){
        if(cursor < SIZE - 5){
          cursor += 5;
          Sleep(150);
        }
      }
      
      if(GetAsyncKeyState(VK_LEFT) & 0x8000){
        if(cursor > 0){
          cursor--;
          Sleep(150);
        }
      }

      if(GetAsyncKeyState(VK_RIGHT) & 0x8000){
        if(cursor < SIZE - 1){
          cursor++;
          Sleep(150);
        }
      }
      
      if(GetAsyncKeyState(VK_CONTROL) & 0x8000){
        if(firstPick == -1) {
          firstPick = cursor;
          revealed[firstPick] = true;
        }
        else if(secondPick == -1) {
          secondPick = cursor;
          if(firstPick == secondPick) {
            continue;
          }
          revealed[secondPick] = true;
          break;
        }
        Sleep(150);
      }
      board(cards, revealed, found, SIZE, cursor);
    }

    board(cards, revealed, found, SIZE, cursor);
    Sleep(500);

    if(cards[firstPick] == cards[secondPick]) {
      found[firstPick] = true;
      found[secondPick] = true;
      matchesFound++;
    }
    else {
      revealed[firstPick] = false;
      revealed[secondPick] = false;
    }

    firstPick = -1;
    secondPick = -1;
  }

  return 0;
}