#include <iostream>
#include <windows.h>
#include <fstream>
#include "player.h"
#include "items.h"
#include "functions.h"

using namespace std;

struct Inventory
{
	Items i[10];
}inv_player;

void help(int x)
{
    switch(x)
    {
    case 1:                                                             //General syntax
        cout << "_________________ is an interactive text based adventure game." << endl;
        cout << "In this game, the user is expected to enter two words in the form of <verb> <noun>" << endl;
        cout << "For example, if you want to brush your teeth, input \"Brush teeth\"." << endl << endl;
        cout << "Grammar is not an important aspect in this game, so do not enter unnecessary prepositions." << endl;
        cout << "In the case of \"Brush teeth\", it will be assumed that you will brush your own teeth, and not anyone else's." << endl << endl;
        cout << "However, it will be useful for other scenarios like in the following example-" << endl;
        cout << "If the player enters \"Look Bed\" the game will describe what is on the bed at the moment." << endl;
        cout << "However, if the player enters \"Look under bed\" the game will describe what is lying under the bed." << endl << endl;
        break;
    case 2:                                                             //list of accepted words
        {
            ifstream iFile;
            iFile.open("data\\dictionary\\verbs.dat");
            cout<< "Here is a list of accepted verbs-" << endl;
            while(iFile){
                string word;
                getline(iFile, word);
                cout << word << endl;
            }
            iFile.close();
            cout << "Note:- \"Look\" will inspect the room you are in. \"Inspect\", on the other hand can be used" << endl;
            cout << "with an object to see details related to that object." << endl;
            cout << "So, \"Look <object>\" isn't accepted, but \"Inspect <object>\" is." << endl << endl;
            cout << "Note:- the verbs \"f\", \"l\", \"b\", \"r\" are movement verbs." << endl;
            cout << "f - forward\nb - behind\nl - left\nr - right\n";
        }
        break;
    }
}

int main()
{
    Player X;                                                           //object of the player
    cout << "Welcome to _________________, a text-based adventure game." << endl << endl << endl;
    cout << "Do you wish to-" << endl;
    cout << "1) Start a new game?" << endl;
    cout << "2) Load an existing game?" << endl;
    cout << "3) Get help?" << endl;
    cout << "\t\t\t\t\t\t\t\tInteger input expected" << endl;

    int choice;

    cin >> choice;

    switch(choice)
    {
    case 1:                                                             //Start a new game
        {
            char c;
            system("CLS");
            cout << "What will be your adventurer's name?" << endl;
            cin.ignore();
            X.set_name();                                               //Get the player's name
            do{
                system("CLS");
                cout << "Alright, ";
                X.show_name();
                cout << ". Get ready for your Adventure!" << endl << endl << endl;
                cout << "\t\t\t\t\tPress Enter" << endl;
                cin.get(c);
            }while(c != '\n');
            goto Newgame;                                               //goes to the code where functions of the new game are written
        }
        break;
    case 2:                                                             //loads an existing game
        system("CLS");
        cout << "Which file do you want to load?" << endl;
        break;
    case 3:                                                             //help
        system("CLS");
        {
            Start:
            cout << "What do you want help with?" << endl;
            cout << "1) Syntax of inputs ingame?" << endl;
            cout << "2) Words preferably used?" << endl;
            int help_no, count_fail = 0;
            cin >> help_no;
            if(help_no != 1 && help_no != 2)
            {
                cout << "I do not understand what you are saying." << endl;
                Sleep(2500);
                goto Start;
            }
            system("CLS");
            help(help_no);
            char x;
            cin >> x;
        }
        break;
    }

Newgame:
    system("CLS");
    ifstream iFile;
    iFile.open("data\\rooms\\start.dat");
    while(iFile)
    {
        string disp;
        getline(iFile, disp);
        cout << disp << endl;
    }
    iFile.close();

    int x;
    x = action();
}
