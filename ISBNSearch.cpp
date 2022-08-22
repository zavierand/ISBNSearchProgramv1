/*
    This program will sort and store data that will be read from a file.
    The user will be able to select what they would like through a menu 
    and display the given information based on what the user picks.
*/

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <iomanip>

using namespace std;

// constant declaration
const int SIZE = 100;

// function prototypes
void printMenu();
void printBookTitles(string [], int);
void printTextbookEdition(string [], long int [], int);
void printASINEdition(string [], string [], int);
int linearSearch(long int [], int , long int);
int linearSearch(string [], int , string);

int main() {

    // variable declaration for data
    string bookName;
    long int isbnPaperback, isbnHardcover, asinNumbers;

    // variable declaration for user input
    int userChoice;
    string userASIN;
    long int userISBN;

    //variable declaration for file stream
    ifstream inputfile;
    inputfile.open("compscibooks.txt");

    // array declaration
    string arr_bookTitles[SIZE];
    long int arr_isbnPaperback[SIZE];
    long int arr_isbnHardcover[SIZE];
    string arr_asinNumbers[SIZE];


    // logic statement for file stream
    if(inputfile) {
        int index = 0;
        int validateInput = 0;

        // fill arrays with data
        while (inputfile) {
            inputfile >> arr_bookTitles[index];
            inputfile >> arr_isbnPaperback[index];
            inputfile >> arr_isbnHardcover[index];
            inputfile >> arr_asinNumbers[index];
            index++;
        }
        
        // variables for linear search
        int userISBNPaperSearch;
        int userISBNHardSearch;
        int userASINSearch;

        do {
            printMenu();
            cout << "Enter the number you would like to access." << endl;
            cin >> userChoice;

            //input validation
            while (userChoice < 0 || userChoice > 6) {
                cout << "This is an invalid operation. Pick another number." << endl;
                cin >> userChoice;
                validateInput++;
            }

            // switch statements for different cases picked
            switch(userChoice) {
                // variable initialization to store linear search value
                case 1:
                    printBookTitles(arr_bookTitles, 13);
                    break;
                case 2:
                    printTextbookEdition(arr_bookTitles, arr_isbnPaperback, 13);
                    break;
                case 3:
                    printTextbookEdition(arr_bookTitles, arr_isbnHardcover, 13);
                    break;
                case 4:
                    printASINEdition(arr_bookTitles, arr_asinNumbers, 13);
                    break;
                case 5: {
                    cout << "Enter the ISBN Number of the textbook: " << endl;
                    cin >> userISBN;
                    userISBNPaperSearch = linearSearch(arr_isbnPaperback, 13, userISBN);
                    userISBNHardSearch = linearSearch(arr_isbnHardcover, 13, userISBN);
                    if (userISBNPaperSearch == -1) {
                        if (userISBNHardSearch == -1) {
                            cout << "This textbook does not exist." << endl;
                        } else {
                            cout << arr_bookTitles[userISBNHardSearch] << endl;
                        }
                    } else {
                        cout << arr_bookTitles[userISBNPaperSearch] << endl;
                    }
                    break;
                }
                case 6: {
                    cout << "Enter the ASIN Number of the textbook: " << endl;
                    cin >> userASIN;
                    userASINSearch = linearSearch(arr_asinNumbers, 13, userASIN);
                    if (userASINSearch == -1) {
                        cout << "This textbook does not exist." << endl;
                    } else {
                        cout << arr_bookTitles[userASINSearch] << endl;
                    }
                    break;
                case 0:
                    cout << "Thank you for using the Textbook Searcher!" << endl;
                    break;
                }
            }
        } while (userChoice > 0);
    } else {
        cout << "This file does not exist." << endl;
    }

    inputfile.close();

    return 0;
}

void printMenu() {
    cout << "Welcome to the Textbook Search!" << endl;
    cout << "\t1. See all book titles." << endl;
    cout << "\t2. See all Paperback books and ISBN." << endl;
    cout << "\t3. See all Hardcover books and ISBN" << endl;
    cout << "\t4. See all Kindle books and ASIN." << endl;
    cout << "\t5. Search for book by ISBN" << endl;
    cout << "\t6. Search for ebook by ASIN" << endl;
    cout << "\t0. Exit." << endl;
}

void printBookTitles(string arr[], int size) {
    for (int i = 0; i < size; i++) {
        cout << arr[i] << endl;
    }
    cout << endl;
}

void printTextbookEdition(string titleArr[], long int numArr[], int size) {
    for (int index = 0; index < size; index++) {
        if (numArr[index] == 0) {
            continue;
        }
        cout << "Title: " << titleArr[index] << " ";
        cout << setw(5) << "ISBN: " << numArr[index];
        cout << endl;
    }
    cout << endl;
}

void printASINEdition(string titleArr[], string asinArr[], int size) {
    for (int index = 0; index < size; index++) {
        if (asinArr[index] == "NoEbook") {
            continue;
        }
        cout << "Title: " << titleArr[index] << " ";
        cout << "ASIN: " << asinArr[index];
        cout << endl;
    }
    cout << endl;
}

int linearSearch(long int arr[], int size, long int searchValue) {
    bool found = false;
    int position = -1;
    int index = 0;
    while (!found && (index < size)) {
        if (arr[index] == searchValue) {
            found = true;
            position = index;
        }
        index++;
    }
    return position;
}

int linearSearch(string arr[], int size, string searchValue) {
    bool found = false;
    int position = -1;
    int index = 0;
    while (!found && (index < size)) {
        if (arr[index] == searchValue) {
            found = true;
            position = index;
        }
        index++;
    }
    return position;
}
