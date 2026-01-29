#include "Platform.hpp"
#include "Movie.hpp"
#include "Game.hpp"
#include "Series.hpp"
#include <fstream>
#include <sstream>
#include <iostream>

Platform::Platform() {}
// destruktor zwalnia pamięć
Platform::~Platform() {
    for (Content* c : contents) {
        delete c;
    }
}
// pomocnicza funkcja do dzielenia stringa (separator) 
std::vector<std::string> Platform::split(const std::string& s, char delim) {
    std::vector<std::string> parts;
    std::string part;
    std::istringstream iss(s);
    while (std::getline(iss, part, delim)) {
        parts.push_back(part);
    }
    return parts;
}
//użytkownik wybiera kategorię, a następnie wyświetlane są tylko treści z tej kategorii
void Platform::listByType(const std::string& type) const {
    bool found = false;

    for (Content* c : contents) {
        if (c->getType() == type) {
            c->printInfo(std::cout);
            std::cout << "\n";
            found = true;
        }
    }

    if (!found) {
        std::cout << "Brak tresci w kategorii: " << type << "\n";
    }
}

//wczytuje dane z pliku
void Platform::loadFromFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cout << "Nie udalo sie otworzyc pliku: " << filename << "\n";
        return;
    }

    // czyści katalog i zwalnia pamięć
    for (Content* c : contents) delete c;
    contents.clear();

    std::string line;
    while (std::getline(file, line)) {
        if (line.empty()) continue;

        std::vector<std::string> t = split(line, ';');
        if (t.size() < 6) continue;

        std::string type = t[0];

        int id = 0;
        int year = 0;
        double price = 0.0;

        // zabezpieczenie, próbuje odczytać liczby jak konwersja się nie uda to pomija linie
        try {
            id = std::stoi(t[1]); //stoi konwertuje string na int
            year = std::stoi(t[3]);
            price = std::stod(t[4]); //stod konwertuje string na double
        } catch (...) {
            continue;
        }

        std::string title = t[2];
        //1=subskrypcja, 0=brak
        bool inSub = (t[5] == "1");

        if (type == "MOVIE") {
            // jeśli linia ma za dużo lub za mało pól, to pomija
            if (t.size() != 9) continue;

            int duration = 0; 
            try {
                duration = std::stoi(t[6]);
            } catch (...) {
                continue;
            }

            std::string genre = t[7];
            std::string quality = t[8];
            //dodaje nowy obiekt Movie do wektora contents
            contents.push_back(new Movie(id, title, year, price, inSub, duration, genre, quality));
        }
        else if (type == "GAME") {
            if (t.size() != 10) continue;

            std::string genre = t[6];

            int playtime = 0;
            try {
                playtime = std::stoi(t[7]);
            } catch (...) {
                continue;
            }

            std::string difficulty = t[8];
            std::string ageRating = t[9];

            contents.push_back(new Game(id, title, year, price, inSub, genre, playtime, difficulty, ageRating));
        }
        else if (type == "SERIES") {
            if (t.size() != 10) continue;

            int seasons = 0;
            int episodes = 0;

            try {
                seasons = std::stoi(t[6]);
                episodes = std::stoi(t[7]);
            } catch (...) {
                continue;
            }
            std::string genre = t[8];
            std::string quality = t[9];

    contents.push_back(new Series(id, title, year, price, inSub, seasons, episodes, genre, quality));
}

    }

    file.close();
}

//Printuje katalog
void Platform::listAll() const {
    if (contents.empty()) {
        std::cout << "Katalog jest pusty.\n";
        return;
    }

    for (Content* c : contents) {
        c->printInfo(std::cout);
        std::cout << "\n";
    }
}

Content* Platform::findById(int id) const {
    for (Content* c : contents) {
        if (c->getId() == id) return c;
    }
    return nullptr;
}

//szuka treści z katalogu po wpisaniu kilku pierwszych liter nazwy
void Platform::searchByTitle(const std::string& fragment) const {
    bool found = false;

    for (Content* c : contents) {
        std::string title = c->getTitle();
        if (title.find(fragment) != std::string::npos) {
            c->printInfo(std::cout);
                std::cout << "\n";
                found = true;
        }
    }
    

    if (!found) {
        std::cout << "Brak wynikow dla: " << fragment << "\n";
    }

}

//kupuje(przypisuje treść do użytkownika na stałe)
bool Platform::buy(User& user, int contentId) {
    Content* c = findById(contentId);
    if (c == nullptr) {
        std::cout << "Nie ma tresci o ID: " << contentId << "\n";
        return false;
    }

    if (user.owns(contentId)) {
        std::cout << "Masz juz zakupiona te tresc.\n";
        return false;
    }

    double price = c->getPrice();
    if (!user.pay(price)) {
        std::cout << "Brak srodkow. Cena: " << price << ", saldo: " << user.getBalance() << "\n";
        return false;
    }

    user.addOwned(contentId);
    std::cout << "Zakupiono: " << c->getTitle() << " (ID=" << contentId << ")\n";
    return true;
}

//przypisuje wypożyczoną treść do użytkownika na określony czas wypożyczenia
bool Platform::rent(User& user, int contentId, int days) {
    Content* c = findById(contentId);
    if (c == nullptr) {
        std::cout << "Nie ma tresci o ID: " << contentId << "\n";
        return false;
    }

    if (days <= 0) {
        std::cout << "Niepoprawna liczba dni.\n";
        return false;
    }

    double rentPrice = c->getPrice() * 0.30;

    if (!user.pay(rentPrice)) {
        std::cout << "Brak srodkow. Cena wypozyczenia: " << rentPrice
                  << ", saldo: " << user.getBalance() << "\n";
        return false;
    }

    user.addRental(contentId, days);
    std::cout << "Wypozyczono: " << c->getTitle()
              << " (ID=" << contentId << ") na " << days << " dni.\n";
    return true;
}

//przypisuje użytkownikowi subskrypcję na określoną ilość dni
bool Platform::subscribe(User& user, int days) {
    if (days <= 0) {
        std::cout << "Niepoprawna liczba dni.\n";
        return false;
    }

    double price = (days / 30.0) * 10.0;

    if (!user.pay(price)) {
        std::cout << "Brak srodkow. Cena subskrypcji: " << price
                  << ", saldo: " << user.getBalance() << "\n";
        return false;
    }

    user.startSubscription(days);
    std::cout << "Aktywowano subskrypcje na " << days << " dni.\n";
    return true;
}

//sprawdza czy użytkownik ma dostęp do danej treści
bool Platform::canAccess(const User& user, int contentId) const {
    Content* c = findById(contentId);
    if (c == nullptr) return false;

    // kupione na zawsze
    if (user.owns(contentId)) return true;

    // wypożyczone i jeszcze ważne
    if (user.hasActiveRental(contentId)) return true;

    // subskrypcja aktywna i treść w puli subskrypcji
    if (user.hasActiveSubscription() && c->isInSubscriptionPool()) return true;

    return false;
}

//jeśli użytokwnik ma dostęp do treści to wtedy ją "uruchamia"
void Platform::playOrWatch(const User& user, int contentId) const {
    Content* c = findById(contentId);
    if (c == nullptr) {
        std::cout << "Nie ma tresci o ID: " << contentId << "\n";
        return;
    }

    if (canAccess(user, contentId)) {
        std::cout << "Uruchamianie: " << c->getTitle() << " (" << c->getType() << ")\n";
    } else {
        std::cout << "Brak dostepu do: " << c->getTitle() << "\n";
        std::cout << "Opcje: kup / wypozycz / subskrypcja (jesli tresc jest w sub).\n";
    }

}
