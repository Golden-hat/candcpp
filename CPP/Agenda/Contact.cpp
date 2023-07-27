#include <iostream>
#include <string>

class Contact{
    private:
        std::string name;
        std::string surname;
        std::string email;
        long phoneNumber;
    public:
        Contact(std::string na, std::string sur, std::string ema, long n){
            name = na;
            surname = sur;
            email = ema;
            phoneNumber = n;
        }

        void setName(std::string s){
            name = s;
        }
        void setSurname(std::string s){
            surname = s;
        }
        void setEmail(std::string s){
            email = s;
        }
        void setphoneNumber(long s){
            phoneNumber = s;
        }
        std::string getName(){ return name; }
        std::string getSurname(){ return surname; }
        std::string getEmail(){ return email; }
        long getphoneNumber(){ return phoneNumber; }

        std::string toString(){
            return name+" "+surname+", E-mail: "+email+", Telephone: "+std::to_string(phoneNumber);  
        }

        void printContact(){
            std::cout << toString() << std::endl;
        }
};