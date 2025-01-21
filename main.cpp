#include <iostream>
#include <time.h>
#include <windows.h>

void swap(int &, int &);
void shuffle(int[], int);
void board(const int[], const bool[], const bool[], int, bool);
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

void board(const int board[], const bool revealed[], const bool found[],
           int size, bool pause = false) {
  system("cls");

  for (int i = 0; i < size; i++) {
    if (found[i]) {
      color(2);
      std::cout << board[i] << '\t';
    } else if (revealed[i]) {
      color(6);
      std::cout << board[i] << '\t';
    } else {
      color(7);
      std::cout << "X\t";
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

  int firstPick, secondPick;

  while (matchesFound < 10) {
    board(cards, revealed, found, SIZE);
    {
      std::cout << "pick a card, any card (1-20)";
      std::cin >> firstPick;
      firstPick--;
    }
    if (firstPick < 0 || firstPick >= SIZE || revealed[firstPick]) {
      std::cout << "invalid move, try again\n";
      Sleep(500);
      continue;
    }

    revealed[firstPick] = true;

    board(cards, revealed, found, SIZE);

    std::cout << "pick a pair for the first card";
    std::cin >> secondPick;
    secondPick--;

    if (secondPick < 0 || secondPick >= SIZE || revealed[secondPick]) {
      std::cout << "invalid move, try again\n";
      Sleep(500);
      revealed[firstPick] = false;
      continue;
    }

    revealed[secondPick] = true;
    board(cards, revealed, found, SIZE);

    if (cards[firstPick] == cards[secondPick]) {
      std::cout << "nice\n";
      matchesFound++;

      found[firstPick] = true;
      found[secondPick] = true;
      revealed[firstPick] = false;
      revealed[secondPick] = false;
    } else {
      std::cout << "invalid move, try again\n";
      Sleep(2000);
      revealed[firstPick] = false;
      revealed[secondPick] = false;
    }
  }
}