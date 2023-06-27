#include <iostream>

using namespace std;

template<size_t N>
void PrintNumberArray(int (&numberArray)[N]) 
{
    for (int i = 0; i < N; i++) {
        if (numberArray[i] != 0) {
            cout << i + 1 << ". " << numberArray[i] << endl;
        } else {
            cout << i + 1 << ". " << endl;
        }
    }
}

template<size_t N>
bool IsValidNumberSpot(int(&numberArray)[N], int number, int spot) 
{
    if (numberArray[spot] != 0) {
        return false;
    }

    for (int i = spot + 1; i < N; i++) {
        if (numberArray[i] < number && numberArray[i] != 0) {
            return false;
        }
    }

    for (int i = spot - 1; i >= 0; i--) {
        if (numberArray[i] > number && numberArray[i] != 0) {
            return false;
        }
    }

    return true;
}

template<size_t N>
bool HasValidSpotForNumber(int(&numberArray)[N], int number)
{
    for (int i = 0; i < N; i++) {
        if (IsValidNumberSpot(numberArray, number, i)) {
            return true;
        }
    }
    return false;
}

template<size_t N>
bool Find(int(&numberArray)[N], int number)
{
    for (int i = 0; i < N; i++) {
        if (numberArray[i] == number) {
            return true;
        }
    }
    return false;
}

template<size_t N>
bool WonGame(int(&numberArray)[N])
{
    for (int i = 0; i < N; i++) {
        if (numberArray[i] == 0) {
            return false;
        }
    }
    return true;
}

int main() 
{
    srand(time(nullptr));
    bool genNumber = true;
    int randomNumber = -1;
    int numberArray[20]{};
    while (true) {
        system("cls");

        if (WonGame(numberArray)) {
            cout << "YOU WON!" << endl;
            PrintNumberArray(numberArray);
            return 0;
        }

        if (genNumber) {
            randomNumber = rand() % 1000 + 1;
            while (Find(numberArray, randomNumber)) {
                randomNumber = rand() % 1000 + 1;
            }
        }

        genNumber = true;
        cout << "Where do you want to put this number? " << randomNumber << endl;
        PrintNumberArray(numberArray);
        if (HasValidSpotForNumber(numberArray, randomNumber) == false) {
            cout << "No valid place for number. You lost." << endl;
            return 0;
        }

        int choice = -1;
        cin >> choice;
        if (choice < 1 || choice > 20 || !IsValidNumberSpot(numberArray, randomNumber, choice - 1)) {
            genNumber = false;
            continue;
        }
        numberArray[choice - 1] = randomNumber;
    }
    return 0;
}