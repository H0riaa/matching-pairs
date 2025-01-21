#include <iostream>
#include <time.h>
#include <windows.h>


void swap(int &a, int &b)
{
    int temp = a;
    a = b;
    b = temp;

}


void shuffle(int arr[], int size)
{
    for(int i = size - 1; i > 0; i--)
    {
        int j = rand() % (i + 1);
        swap(arr[i], arr[j]);
    }

}

void board(const int board[], const bool revealed[], int size, bool pause = false)
{
    system("cls"); 

    for(int i = 0; i < size; i++)
    {
        if(revealed[i])
        {
            std::cout << board[i] << '\t';
        }
        else
        {
            std::cout << "X\t";
        }
    
        if((i + 1) % 5 == 0)
        {
            std::cout << '\n';
        }
    }

}




int main()
{
    srand((unsigned int)time(0));

    const int SIZE = 20;
    int cards[SIZE] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    bool revealed[SIZE] = {false};
    int matchesFound = 0;
    

    shuffle(cards, SIZE);

    int firstPick, secondPick;

    while(matchesFound < 10)
    {
        board(cards, revealed, SIZE);
        {
            std::cout << "pick a card, any card";
            std::cin >> firstPick;
            firstPick--;
        }
        if(firstPick < 0 || firstPick >= SIZE || revealed[firstPick])
        {
            std::cout << "invalid move, try again\n";
            continue;
        }
    

        revealed[firstPick] = true;
        
        board(cards, revealed, SIZE);
        
        std::cout << "pick a pair for the first card";
        std::cin >> secondPick;
        secondPick--;

    if(secondPick < 0 || secondPick >= SIZE || revealed[secondPick])
        {
                std::cout << "invalid move, try again\n";
                revealed[firstPick] = false;
                continue;
        }

        revealed[secondPick] = true;
        board(cards, revealed, SIZE);

        if(cards[firstPick] == cards[secondPick])
        {
            std::cout << "nice\n";
            matchesFound++;
        }
        else
        {
            std::cout << "invalid move, try again\n";
            revealed[firstPick] = false;
            revealed[secondPick] = false;
        }

    }

    



}