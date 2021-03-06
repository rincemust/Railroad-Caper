#include <iostream>
#include <stdlib.h>


//custom headers
#include "Player.h"
#include "File.h"
#include "Room.h"
#include "Functions.h"
#include "Mobs.h"


//so that the '\' and '/' demarkation for folders will not conflict between windows and unix based systems

#ifdef _WIN32
  File menu("data\\Menu.dat");
  File Index("data\\Index.ind");

#elif __unix__
  File menu("data/Menu.dat");
  File Index("data/Index.ind");

#endif

int main()
{
  //declarations
  char choice;
  Player X;
  File room;

  //menu screen shown to player
 //MENU:
  menu.disp();

  do{
    std::cin >> choice;

    //Actions dependent on the player's choice
    switch(choice){
    case '1':
      //This means that the player wants to start a new game
      //Following functions will take in the player's name
      {
	      std::string input;
	      //char c;
	      std::cout << "What is your name?" << std::endl;
	      std::cin.ignore();
	      getline(std::cin, input);

	      while(Index.chk_line(input)){
	        std::cout << "Your name already exists. Pick another one." << std::endl;
	        getline(std::cin, input);
	      }

	      Index.append(input);

	      X = Player(input);
	      std::cout << "Alright, ";
	      X.disp_name();
	      std::cout << ", get ready!" << std::endl << std::endl << std::endl;
	      std::cout << "\t\t\tPress Enter" << std::endl;
	      std::cin.get();
	      goto NEWGAME;
      }
      break;

    case '2':
      //This will be to load a pre-existing game
      //Will start once the basic game's algorithm is complete
      break;

    case '3':
      //This is when the player wants an introduction as to the general syntax expected as input
      break;

    default:
      //Player should be told to re enter the input
      break;
    }
  }while(1);

 NEWGAME:
  //Here begins the algorithm of the game

//Outside world
  Room Start("start", 0);
  Room *R = new Room[8];
  for(int i = 0; i < 8; i++){
    std::string name = "room";
    name = name + std::to_string(i + 1);
    R[i] = Room(name, i + 1);
  }

  //Generates the map
  make_map(R);
  Mobs *enemy = new Mobs[1];
  enemy[0] = Mobs("spider", 25, 10);

  for(int i = 0; i < 1; i++){
    enemy[i].set_occupied(2, R);
  }

  //Player first starts at R[0] inside the cave
  X.occupied = R[0];

  Start.display();
  std::cout << "\t\t\tPress Enter" << std::endl;
  std::cin.get();

  /*
  General Algorithm for the game:-
  1. Show the player the room he/she is in (except in battles)
  2. get the player's command
  3. Perform an action based on the entered command, which will also show the result
  4. Mark a separation point for the player to know that it is the beginning of a new loop
  */
  do{
    X.occupied.display();
    std::string command;
    getline(std::cin, command);
    X.action(command, R, enemy, 1);
    std::cout << std:: endl << std::endl;
    for(int k = 0; k < console_width(); k++){
      std::cout << "-";
    }

    std::cout << std::endl << "\t\t\t\tPress Enter" << std::endl;
    std::cin.get();

    clrscreen();
  }while(X.isalive());

  std::cout << "You died" << std::endl;

  return 0;
}
