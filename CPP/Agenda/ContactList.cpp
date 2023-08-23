#include <iostream>
#include <fstream>
#include "Contact.cpp"
#include "LinkedList.cpp"
#include "string"
#include <bits/stdc++.h>

class ContactList{
    private:
        LinkedList<Contact*>* contactList;
    public:
        ContactList(){
            contactList = new LinkedList<Contact*>();
        }

        void addToList(){
            std::cout << "Insert the data of the new contact:" << std::endl;
            std::cout << "Name: ";
            
            std::string name;
            std::cin >> name;

            std::cout << "Surname: ";
            std::string surname;
            std::cin.ignore();
            std::getline(std::cin, surname);

            std::cout << "E-mail: ";
            std::string email;
            std::cin >> email;

            std::cout << "Telephone: ";
            long telephone = 2;
            std::cin >> telephone;

            Contact* contact = new Contact(name, surname, email, telephone);
            if(findContact(contact) == NULL)
                contactList->add(contact);
        }

        void removeFromList(){
            std::cout << "Insert the name and the surname of the new contact to remove:" << std::endl;
            std::cout << "Name: ";

            std::string name;
            std::cin >> name;

            std::cout << "Surname: ";
            std::string surname;
            std::cin.ignore();
            std::getline(std::cin, surname);

            if(findContact(name, surname) != NULL){
                contactList->remove(findContact(name, surname)->data);
                std::cout << "\nContact removed successfully." << std::endl;
            }
            else{std::cout << "\nSuch Contact does not exist." << std::endl;}
        }

        void printList(){
            contactList->printListObjects();
        }

        void writeToFile(){
            std::ofstream MyFile("contactFile.txt");
            for(int i = 0; i < contactList->getSize(); i++){
                Node<Contact*>* node = contactList->findIndex(i);
                MyFile << node->data->getName()+","+node->data->getSurname()+","+
                    node->data->getEmail()+","+std::to_string(node->data->getphoneNumber()) 
                    << std::endl;
            }
            MyFile.close();
        }

        void loadFromFile(){
            std::string text;
            std::string wordsReturn[4];
            std::ifstream MyFile("contactFile.txt");
            while(std::getline(MyFile, text)){
                adv_tokenizer(text, ",", wordsReturn);
                Contact* contact = new Contact(wordsReturn[0], wordsReturn[1], wordsReturn[2], stoul(wordsReturn[3]));
                contactList->add(contact);
            }
            MyFile.close();
        }

        void adv_tokenizer(std::string s, const char* del, std::string t[])
        {
            std::stringstream ss(s);
            std::string word;
            int i = 0;
            while (!ss.eof()) {
                std::getline(ss, word, *del);
                t[i++] = word;
            }
        }

        Node<Contact*>* findContact(Contact* contact){
            for(int i = 0; i < contactList->getSize(); i++){
                Node<Contact*>* node = contactList->findIndex(i);
                if(node->data->getName() == contact->getName() &&
                node->data->getEmail() == contact->getEmail() && 
                node->data->getphoneNumber() == contact->getphoneNumber() && 
                node->data->getSurname() == contact->getSurname()){
                    return node;
                }
            }
            return NULL;
        }

        Node<Contact*>* findContact(std::string name, std::string surname){
            for(int i = 0; i < contactList->getSize(); i++){
                Node<Contact*>* node = contactList->findIndex(i);
                if(node->data->getName() == name &&
                node->data->getSurname() == surname ){
                    return node;
                }
            }
            return NULL;
        }
};