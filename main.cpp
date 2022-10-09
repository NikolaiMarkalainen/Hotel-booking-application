#include <iostream>
#include <limits>
#include <string>
#include <vector>
#include <algorithm>
#include <unistd.h>
#include <cstdlib>
#include <random>
#define SMALL_ROOM 100
#define BIG_ROOM 150

std::vector<int>createSingles(int singleRooms,std::vector<int> singles){
// allocating room numbers to vector
    for(int i = 0; i <= singleRooms; i++){
        singles.push_back(i);
    }
    return singles;

};
// same as previous function but for double bedded rooms.
std::vector<int>createDoubles(int singleRooms,std::vector<int> doubles){
    for(int i = singleRooms + 1; i <= singleRooms*2; i++){
        doubles.push_back(i);
    }
    return doubles;

};

std::string nameAdd(){
    //getline to get full name of the register
    std::string name;
    std::cout<<std::endl;
    std::cout << "Please enter your full name: ";
    std::cin.ignore();
    getline(std::cin,name);
    return name;

};


int chooseRoom(){
    //checking user decision and lettong him only use 1 or 2 as an option
    int input;
    std::cout << "Do you wish to book a single bed or double bed room?" << std::endl;
    std::cout << "1: Single room" << std::endl;
    std::cout << "2: Double room" << std::endl;
    std::cin >> input;
    if (input > 3 || input < 1) {
        while (!(std::cin >> input)) {
            std::cin >> input;
            std::cout << "\tInvalid input enter 1 or 2 " << std::endl;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }
    else{
        return input;
    }




};

int chooseLength(){
    // length only valid entry is int.
    int nights;
    std::cout << "How many nights would you like to spend: ";
    while (!(std::cin >> nights)) {
        std::cout << "Invalid input enter a number " << std::endl;
        std::cin >> nights;
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    return nights;
};
int chooseRoomNumber(int decision, int singleRooms){
    // letting user decide their room and setting specific ruleset for them to follow for the condition to work.
    int input = 0;
    switch(decision) {
        case 1:
            std::cout << "Choose a room number from 1 - " << singleRooms << std::endl;
            std::cin >> input;
            if (input > singleRooms || input < 0) {
                std::cin >> input;
                while (input > singleRooms || input <= 0) {
                    std::cout << "Input between the range of 1 - " << singleRooms << std::endl;
                    std::cin >> input;
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                }
            }
            else {
                break;
            }
        case 2:
            std::cout << "Choose a room number from " << singleRooms << " To " <<singleRooms*2 << std::endl;
            std::cin >> input;
            if (input < singleRooms || input > singleRooms*2) {
                while (input < singleRooms || input > singleRooms*2) {
                    std::cout << "Input number between " << singleRooms << " To " <<singleRooms*2 << std::endl;
                    std::cin >> input;
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                }
            }
            else {
                break;
            }
        }
    return input;

};

std::vector<int> checkIfBooked(int decision, int roomNumber ,std::vector<int>values){
    // checking for conditions of which room is reserved then removing from the specific vector
    // the room that user chooses to rent for the stay.
    switch(decision) {
        case 1:
            if (std::count(values.begin(), values.end(), roomNumber)) {
                std::cout << "Room is free and is reserved for you!" << std::endl;
                values.erase(values.begin() + roomNumber);
                sleep(1);
                return values;
            } else {
                std::cout << "Room is reserved choose a new room." << std::endl;

            }
            sleep(1);
            break;
        case 2:
            if (std::count(values.begin(), values.end(), roomNumber)) {
                std::cout << "Room is free and is reserved for you!" << std::endl;
                values.erase(values.begin()+roomNumber);
                return values;
            } else {
                std::cout << "Room is already booked choose a new room." << std::endl;
            }
    }
};


int calculateStay(int decision,int nights){
    // price depending on the room chosen 1 is single and 2 is dual room.

    int bill = 0;
    switch(decision){
        case 1:
            bill = 100 * nights;
            break;
        case 2:
            bill = 150 * nights;
            break;
    }
    sleep(1);
    return bill;
};

double calculateDiscount(int bill){
          double low = 0.1;
          double high = 0.3;
         std::uniform_real_distribution<double> unif(low,high);
         std::default_random_engine re;
         double randomDiscount = unif(re);
         randomDiscount = bill - (bill * randomDiscount);
         return randomDiscount;
};

int main() {
    int rooms, bill, decision, nights, roomNumber;
    std::string name;
    double fullPrice;
    srand(time(NULL));
    rooms = 40 + (rand() % 261);
    // random seeding the value and setting the value to be 40 - 300;
    int singleRooms = rooms / 2;
    //Creating vectors to hold values for rooms and invalidating them depending on if they are rented already
    // or not
    std::vector<int> singles;
    std::vector<int> doubles;
    //function to handle seeding for vectors
    singles = createSingles(singleRooms,singles);
    doubles = createDoubles(singleRooms,doubles);
    std::cout<<std::endl;
    // switch case to let user decide what they do:
    int operation;
    while(true) {
        std::cout << "\tHello welcome to the hotel booking system" << std::endl;
        std::cout << "\t1: Register into hotel" << std::endl;
        std::cout << "\t2: Check available rooms" << std::endl;
        std::cout << "\t3: Check current prices for rooms" << std::endl;
        std::cout << "\t4: Check your input data" << std::endl;
        std::cout << "\t5: Quit the runtime" << std::endl;
        std::cin>> operation;
        std::cout<<std::endl;
        std::cout<<std::endl;

        switch(operation){
            //function case where all the data input is handled
            case 1:
                name = nameAdd();
                decision = chooseRoom();
                nights = chooseLength();
                roomNumber = chooseRoomNumber(decision, singleRooms);
                //checking whether the user is in a single room or two person room to handle data removal
                switch (decision) {
                    case 1:
                        singles = checkIfBooked(decision, roomNumber, singles);
                        break;
                    case 2:
                        doubles = checkIfBooked(decision, roomNumber, doubles);
                        break;
                }
                bill = calculateStay(decision, nights);
                fullPrice  = calculateDiscount(bill);
                std::cout << "Your bill is: " << fullPrice << std::endl;
                sleep(1);
                std::cout << std::endl;
                std::cout << std::endl;
                sleep(0.5);
                break;
            case 2:
                std::cout<< "The single rooms that are available currently are: " << std::endl;
                for(int i: singles){
                    std::cout << i << ' ';
                    if(i % 10 == 1){
                        std::cout << std::endl;
                    }
                }
                std::cout << std::endl;
                std::cout << "The double rooms that are available currently are: " << std::endl;
                for(int i: doubles){
                    std::cout << i << ' ';
                    if(i % 10 == 1){
                        std::cout << std::endl;
                    }
                }

                std::cout << std::endl;
                std::cout << std::endl;
                std::cout << std::endl;
                sleep(1);
                break;
            case 3:
                std::cout<< "Current prices for single person room is: " << SMALL_ROOM <<std::endl;
                std::cout << "Current prices for two person room is: " << BIG_ROOM << std::endl;
                std::cout <<std::endl;
                std::cout << "Price does not include possible discount" << std::endl;
                std::cout << std::endl;
                sleep(1);
                break;

            case 4:
                // printing all data that has saved thus far from user once user changes the data does not exist.
                      std::cout << name << std::endl;
                      switch(decision) {
                          case 1:
                              std::cout << "Single bed room" << std::endl;
                              break;
                          case 2:
                              std::cout << "Double bed room" << std::endl;
                              break;
                      }
                      std::cout <<"Length of stay: " << nights << std::endl;
                      std::cout << "Room number: " << roomNumber << std::endl;
                      std::cout << "Priced at: " << fullPrice << std::endl;
                      sleep(4);
                break;
            case 5:
                // function returns false thus finishing the program.
                return false;
        }
    }
}
