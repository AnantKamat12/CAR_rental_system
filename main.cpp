#include <iostream>
#include <vector>
#include <string>
using namespace std;

class Car {
private:
    string carId;
    string brand;
    string model;
    double basePricePerDay;
    bool available;

public:
    Car(string id, string br, string md, double price)
        : carId(id), brand(br), model(md), basePricePerDay(price), available(true) {}

    string getCarId() const { return carId; }
    string getBrand() const { return brand; }
    string getModel() const { return model; }
    bool isAvailable() const { return available; }

    double calculatePrice(int days) const {
        return basePricePerDay * days;
    }

    void rent() { available = false; }
    void returnCar() { available = true; }
};

class Customer {
private:
    string customerId;
    string name;

public:
    Customer(string id, string nm) : customerId(id), name(nm) {}

    string getCustomerId() const { return customerId; }
    string getName() const { return name; }
};

class Rental {
private:
    Car* car;
    Customer* customer;
    int days;

public:
    Rental(Car* c, Customer* cust, int d)
        : car(c), customer(cust), days(d) {}

    Car* getCar() const { return car; }
    Customer* getCustomer() const { return customer; }
    int getDays() const { return days; }
};

class CarRentalSystem {
private:
    vector<Car> cars;
    vector<Customer> customers;
    vector<Rental> rentals;

public:
    void addCar(const Car& car) {
        cars.push_back(car);
    }

    void addCustomer(const Customer& cust) {
        customers.push_back(cust);
    }

    void rentCar(Car* car, Customer* cust, int days) {
        if (car->isAvailable()) {
            car->rent();
            rentals.push_back(Rental(car, cust, days));
        } else {
            cout << "Car not available.\n";
        }
    }

    void returnCar(Car* car) {
        car->returnCar();
        for (auto it = rentals.begin(); it != rentals.end(); ++it) {
            if (it->getCar() == car) {
                rentals.erase(it);
                return;
            }
        }
        cout << "Car was not rented.\n";
    }

    Car* findCarById(const string& id) {
        for (auto& car : cars) {
            if (car.getCarId() == id)
                return &car;
        }
        return nullptr;
    }

    void menu() {
        while (true) {
            cout << "\n===== Car Rental System =====\n";
            cout << "1. Rent a Car\n";
            cout << "2. Return a Car\n";
            cout << "3. Exit\n";
            cout << "Enter your choice: ";
            int choice;
            cin >> choice;

            if (choice == 1) {
                string name, id;
                int days;

                cout << "Enter your name: ";
                cin >> name;

                cout << "\nAvailable Cars:\n";
                for (auto& car : cars) {
                    if (car.isAvailable()) {
                        cout << car.getCarId() << " - " 
                             << car.getBrand() << " " << car.getModel() << "\n";
                    }
                }

                cout << "Enter Car ID: ";
                cin >> id;
                Car* carPtr = findCarById(id);

                cout << "Enter rental days: ";
                cin >> days;

                if (carPtr && carPtr->isAvailable()) {
                    string custId = "CUS" + to_string(customers.size() + 1);
                    customers.emplace_back(custId, name);

                    Customer* custPtr = &customers.back();

                    cout << "Total Price: " << carPtr->calculatePrice(days) << "\n";
                    rentCar(carPtr, custPtr, days);
                    cout << "Car rented successfully.\n";
                } else {
                    cout << "Car unavailable or invalid ID.\n";
                }
            }

            else if (choice == 2) {
                string id;
                cout << "Enter Car ID: ";
                cin >> id;

                Car* carPtr = findCarById(id);
                if (!carPtr || carPtr->isAvailable()) {
                    cout << "Invalid or not rented.\n";
                } else {
                    returnCar(carPtr);
                    cout << "Car returned successfully.\n";
                }
            }

            else if (choice == 3) break;
            else cout << "Invalid option.\n";
        }
    }
};

int main() {
    CarRentalSystem system;
    system.addCar(Car("C001", "Toyota", "Camry", 60));
    system.addCar(Car("C002", "Honda", "Accord", 70));
    system.addCar(Car("C003", "Mahindra", "Thar", 150));

    system.menu();
    return 0;
}
