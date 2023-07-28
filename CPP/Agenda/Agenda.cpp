#include <iostream>
#include "ContactList.cpp"
#include <string>

bool run = true;
ContactList list;

void mainMenu(){
    system("clear");
    int input;
    std::cout << "Welcome to your agenda!" << std::endl;
    std::cout << "1. Add contact." << std::endl;
    std::cout << "2. Remove contact." << std::endl;
    std::cout << "3. View contact list." << std::endl;
    std::cout << "4. Look for contact." << std::endl;
    std::cout << "5. Exit application.\n" << std::endl;

    std::cin >> input;

    switch(input){
        case 1:
            system("clear");
            list.addToList(); break;
        case 2:
            system("clear");
            list.removeFromList();
            std::cin.get();
            break;
        case 3:
            system("clear");
            list.printList();
            std::cin.ignore();
            std::cin.get();
            break;
        case 4:
        {
            system("clear");
            std::cout << "Insert the name and the surname of the new contact to find:" << std::endl;
            std::cout << "Name: ";

            std::string name;
            std::cin >> name;

            std::cout << "Surname: ";
            std::string surname;
            std::cin.ignore();
            std::getline(std::cin, surname);

            if(list.findContact(name, surname) == NULL){std::cout << "\nContact not found." << std::endl; }
            else{ list.findContact(name, surname)->data->printContact(); }

            std::cin.get();
            break;
        }
        case 5:
            run = false; break;
        default:
            system("clear");
            std::cin.clear();
            std::cin.ignore();
            break;
    }
}

int main(){
    list.loadFromFile();
    while(run)
        mainMenu();
    list.writeToFile();
    return 0;
}