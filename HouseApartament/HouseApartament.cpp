#include <iostream>
#include <cstring>
using namespace std;
class Person {
private:
    char* name; // The name of the occupant of the apartment
public:
    Person(const char* _name) {
        size_t len = strlen(_name) + 1;
        name = new char[len];//Allocating memory for a name and copying the value
        strcpy_s(name, len, _name);
    }

    
    Person(const Person& other) {
        size_t len = strlen(other.name) + 1;
        name = new char[len];// Allocating memory for a name and copying the value from another object
        strcpy_s(name, len, other.name);
    }


    ~Person() {
        delete[] name; // Freeing memory allocated for a name
    }

    const char* getName() const {
        return name; //Returns the name of the resident
    }
};

class Apartment {
private:
    Person** residents; // An array of pointers to objects of the Person class - residents of the apartment
    int numResidents; //Number of people in the apartment
public:
    Apartment(int _numResidents) : numResidents(_numResidents) {
        residents = new Person * [_numResidents]; // Memory allocation for an array of pointers to residents
        for (int i = 0; i < _numResidents; i++) {
            residents[i] = nullptr; //Initializing each pointer in an array to nullptr
        }
    }

    Apartment(const Apartment& other) : numResidents(other.numResidents) {
        residents = new Person * [numResidents]; // Allocating memory for an array of pointers to inhabitants and copying the value of the number of inhabitants
        for (int i = 0; i < numResidents; i++) {
            if (other.residents[i] != nullptr) {
                residents[i] = new Person(*other.residents[i]); //  Creating a new Person objectand copying the value from another object if the pointer is not nullptr
            }
            else {
                residents[i] = nullptr; // If the pointer is equal to nullptr, then in the new object we set the value to nullptr
            }
        }
    }

    ~Apartment() {
        for (int i = 0; i < numResidents; i++) {
            delete residents[i]; // Freeing the memory allocated for each Person object
        }
        delete[] residents; // Freeing the memory allocated for an array of pointers to residents
    }

    void addResident(const char* name, int index) {
        if (index >= 0 && index < numResidents) {
            delete residents[index]; // Deleting an existing Person object if it exists at the given index
            residents[index] = new Person(name); // Creating a new Person object and assigning to a pointer in an array
        }
    }

    void removeResident(int index) {
        if (index >= 0 && index < numResidents) {
            delete residents[index]; // Deleting an existing Person object if it exists at the given index
            residents[index] = nullptr; // Setting nullptr to a pointer in an array
        }
    }

    const Person* getResident(int index) const {
        if (index >= 0 && index < numResidents) {
            return residents[index]; // Returns a pointer to the Person object at the specified index
        }
        return nullptr; // Returns nullptr if the index is out of range
    }

    int getNumResidents() const {
        return numResidents; // Returns the number of inhabitants in the apartment
    }
};

class House {
private:
    Apartment** apartments; //An array of pointers to objects of the Apartment class - apartments in a house
    int numApartments; // Number of apartments in the building
public:
    House(int _numApartments) : numApartments(_numApartments) {
        apartments = new Apartment * [_numApartments]; //  Memory allocation for an array of pointers to apartments
        for (int i = 0; i < _numApartments; i++) {
            apartments[i] = nullptr; // Initializing each pointer in an array to nullptr
        }
    }

    House(const House& other) : numApartments(other.numApartments) {
        apartments = new Apartment * [numApartments]; // Allocate memory for an array of pointers to apartmentsand copy the value of the number of apartments
        for (int i = 0; i < numApartments; i++) {
            if (other.apartments[i] != nullptr) {
                apartments[i] = new Apartment(*other.apartments[i]); // Creating a new Apartment object and copying the value from another object if the pointer is not nullptr
            }
            else {
                apartments[i] = nullptr; // If the pointer is equal to nullptr, then in the new object we set the value to nullptr
            }
        }
    }

    ~House() {
        for (int i = 0; i < numApartments; i++) {
            delete apartments[i]; // Freeing the memory allocated for each Apartment object
        }
        delete[] apartments; // Freeing the memory allocated for an array of pointers to apartments
    }

    void addApartment(int index, int numResidents) {
        if (index >= 0 && index < numApartments) {
            delete apartments[index]; // Deleting an existing Apartment object if it exists at the given index
            apartments[index] = new Apartment(numResidents); // Creating a new Apartment object and assigning to a pointer in an array
        }
    }

    void removeApartment(int index) {
        if (index >= 0 && index < numApartments) {
            delete apartments[index]; // Deleting an existing Apartment object if it exists at the given index
            apartments[index] = nullptr; //Setting nullptr to a pointer in an array
        }
    }

    Apartment* getApartment(int index) const {
        if (index >= 0 && index < numApartments) {
            return apartments[index]; //  Returns a pointer to the Apartment object at the specified index
        }
        return nullptr; // Returns nullptr if the index is out of range
    }
};

int main() {
    House house(2);

    house.addApartment(0, 2);
    house.getApartment(0)->addResident("John Doe", 0);
    house.getApartment(0)->addResident("Jane Smith", 1);

    house.addApartment(1, 1);
    house.getApartment(1)->addResident("Alice Johnson", 0);

    for (int i = 0; i < 2; i++) {
        Apartment* apartment = house.getApartment(i);
        if (apartment != nullptr) {
            cout << "Apartment " << i << ":" <<endl;
            for (int j = 0; j < apartment->getNumResidents(); j++) {
                const Person* resident = apartment->getResident(j);
                if (resident != nullptr) {
                    cout << "  Resident " << j << ": " << resident->getName()<<endl;
                }
            }
        }
    }
    system("pause");
    return 0;
}
