#include "User.hpp"
#include <iostream>
#include <fstream>
#include <sstream>


User::User(std::string name, double balance)
    : name(name), balance(balance) {}

std::string User::getName() const { return name; }
double User::getBalance() const { return balance; }

void User::addMoney(double amount) {
    if (amount > 0) balance += amount;
}

//jeśli użytkownik ma wystarczająco środków, żeby kupić to zmniejsza środki
bool User::pay(double amount) {
    if (amount <= 0) return true;
    if (balance >= amount) {
        balance -= amount;
        return true;
    }
    return false;
}

// Zakupy
// jak nie ma to dodaje do wektora (brak duplikatów)
void User::addOwned(int contentId) {
    if (!owns(contentId)) ownedIds.push_back(contentId);
}

//sprzawdza czy użytkownik ma treść o danym ID (przechodzi po vectorze)
bool User::owns(int contentId) const {
    for (int id : ownedIds) {
        if (id == contentId) return true;
    }
    return false;
}

// Wypożyczenia
void User::addRental(int contentId, int daysLeft) {
    // jeśli już jest wypożyczenie tej treści, to nadpisuje czas
    for (int i = 0; i < (int)rentals.size(); i++) {
        if (rentals[i].getContentId() == contentId) {
            rentals[i].setDaysLeft(daysLeft);
            return;
        }
    }
    rentals.push_back(Rental(contentId, daysLeft));
}

//sprawdza czy wypożyczenie danej treści jest aktywne
bool User::hasActiveRental(int contentId) const {
    for (const Rental& r : rentals) {
        if (r.getContentId() == contentId && r.getDaysLeft() > 0) return true;
    }
    return false;
}

//Printuje zakupione
void User::printOwned() const {
    std::cout << "Zakupione ID: ";
    if (ownedIds.empty()) {
        std::cout << "(brak)\n";
        return;
    }
    for (int id : ownedIds) std::cout << id << " ";
    std::cout << "\n";
}

//Printuje wypożyczenia
void User::printRentals() const {
    std::cout << "Wypozyczenia:\n";
    if (rentals.empty()) {
        std::cout << "(brak)\n";
        return;
    }
    for (const Rental& r : rentals) {
        std::cout << "- ID=" << r.getContentId()<< " | dni=" << r.getDaysLeft() << "\n";
    }
}

void User::startSubscription(int days) {
    subscription.start(days);
}

bool User::hasActiveSubscription() const {
    return subscription.isActive();
}

int User::subscriptionDaysLeft() const {
    return subscription.getDaysLeft();
}

//Printuje czy subskrypcja jest aktywna i ile dni jej pozostało
void User::printSubscription() const {
    if (subscription.isActive()) {
        std::cout << "Subskrypcja aktywna, dni pozostale: " << subscription.getDaysLeft() << "\n";
    } else {
        std::cout << "Subskrypcja nieaktywna.\n";
    }
}

//Zapisuje dane użytkownia do pliku
bool User::saveToFile(const std::string& filename) const {
    std::ofstream file(filename);
    if (!file.is_open()) return false;

    file << name << "\n";

    file << balance << "\n";

    file << subscription.getDaysLeft() << "\n";

    file << "OWNED";
    for (int id : ownedIds) file << ";" << id;
    file << "\n";

    file << "RENTALS";
    for (const Rental& r : rentals) {
        file << ";" << r.getContentId() << "," << r.getDaysLeft();
    }
    file << "\n";

    file.close();
    return true;
}

//wczytuje dane użytkownika z pliku
bool User::loadFromFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) return false;

    std::string line;

    if (!std::getline(file, line)) return false;
    name = line;

    if (!std::getline(file, line)) return false;
    try {
        balance = std::stod(line);
    } catch (...) {
        return false;
    }

    if (!std::getline(file, line)) return false;
    int subDays = 0;
    try {
        subDays = std::stoi(line);
    } catch (...) {
        subDays = 0;
    }
    subscription.setDaysLeft(subDays);

    // czyści dane z pamięci, żeby po wczytaniu nie mieszać starego stanu z nowym
    ownedIds.clear();
    rentals.clear();

    if (std::getline(file, line)) {
        std::istringstream iss(line);
        std::string token;

        if (std::getline(iss, token, ';')) {
            if (token == "OWNED") {
                while (std::getline(iss, token, ';')) {
                    try {
                        int id = std::stoi(token);
                        ownedIds.push_back(id);
                    } catch (...) {
                    }
                }
            }
        }
    }

    if (std::getline(file, line)) {
        std::istringstream iss(line);
        std::string token;

        if (std::getline(iss, token, ';')) {
            if (token == "RENTALS") {
                while (std::getline(iss, token, ';')) {
                    // token ma postać id,days
                    size_t comma = token.find(',');
                    if (comma == std::string::npos) continue;

                    //wycina stringa od początku do przecinka
                    std::string left = token.substr(0, comma);
                    //od przecinka do końca
                    std::string right = token.substr(comma + 1);

                    try {
                        int id = std::stoi(left);
                        int days = std::stoi(right);
                        rentals.push_back(Rental(id, days));
                    } catch (...) {
                    }
                }
            }
        }
    }

    return true;
}

// symuluje upływ dni
void User::nextDays(int days) {
    if (days <= 0) return;

    // subskrypcja
    for (int i = 0; i < days; i++) {
        subscription.decreaseDay();
    }

    // wypożyczenia
    for (int i = 0; i < (int)rentals.size(); i++) {
        for (int d = 0; d < days; d++) {
            rentals[i].decreaseDay();
        }
    }

    // usuwa wygasłe wypożyczenia
    for (int i = 0; i < (int)rentals.size(); ) {
        if (rentals[i].getDaysLeft() <= 0) {
            rentals.erase(rentals.begin() + i);
        } else {
            i++;
        }
    }
}
