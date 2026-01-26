#include <iostream>
#include <string>
#include <limits>

#include "Platform.hpp"
#include "User.hpp"


//zabezpieczenia przed wpisaniem złej opcji
int readInt(const std::string& prompt) {
    int x;
    while (true) {
        std::cout << prompt;
        if (std::cin >> x) {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return x;
        }
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Blad: wpisz liczbe.\n";
    }
}

double readDouble(const std::string& prompt) {
    double x;
    while (true) {
        std::cout << prompt;
        if (std::cin >> x) {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return x;
        }
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Blad: wpisz liczbe (np. 10 lub 10.5).\n";
    }
}

std::string readLine(const std::string& prompt) {
    std::string s;
    std::cout << prompt;
    std::getline(std::cin, s);
    return s;
}

int main() {
    Platform platform;
    User user("User1", 100.0);

    std::string filename = "data.txt";
    platform.loadFromFile(filename);

    int choice = -1;

    while (choice != 0) {
        std::cout << "\n===== PLATFORM MENU =====\n";
        std::cout << "Uzytkownik: " << user.getName() << " | Saldo: " << user.getBalance() << "\n";
        std::cout << "1. Pokaz katalog\n";
        std::cout << "2. Pokaz wg kategorii (Movie/Game/Series)\n";
        std::cout << "3. Wyszukaj po tytule\n";
        std::cout << "4. Kup tresc (ID)\n";
        std::cout << "5. Wypozycz tresc (ID + dni)\n";
        std::cout << "6. Kup subskrypcje (dni)\n";
        std::cout << "7. Odtworz/Uruchom (ID)\n";
        std::cout << "8. Moje konto (zakupy/wypozyczenia/sub)\n";
        std::cout << "9. Doladuj konto\n";
        std::cout << "10. Zapisz dane uzytkownika\n";
        std::cout << "11. Wczytaj dane uzytkownika\n";
        std::cout << "12. Symuluj uplyw czasu (dni)\n";
        std::cout << "0. Wyjscie\n";

        choice = readInt("Wybor: ");

        switch (choice) {
            case 1: {
                platform.listAll();
                break;
            }
            case 2: {
                std::cout << "\nWybierz kategorie:\n";
                std::cout << "1. Movie\n";
                std::cout << "2. Game\n";
                std::cout << "3. Series\n";

                int cat = readInt("Wybor: ");

                if (cat == 1) {
                    platform.listByType("MOVIE");
                } else if (cat == 2) {
                    platform.listByType("GAME");
                } else if (cat == 3) {
                    platform.listByType("SERIES");
                } else {
                    std::cout << "Nieznana kategoria.\n";
                }
                break;
            }
            case 3: {
                std::string frag = readLine("Podaj fragment tytulu: ");
                platform.searchByTitle(frag);
                break;
            }
            case 4: {
                int id = readInt("Podaj ID: ");
                platform.buy(user, id);
                break;
            }
            case 5: {
                int id = readInt("Podaj ID: ");
                int days = readInt("Podaj liczbe dni: ");
                platform.rent(user, id, days);
                break;
            }
            case 6: {
                int days = readInt("Podaj liczbe dni subskrypcji: ");
                platform.subscribe(user, days);
                break;
            }
            case 7: {
                int id = readInt("Podaj ID: ");
                platform.playOrWatch(user, id);
                break;
            }
            case 8: {
                std::cout << "\n=== KONTO ===\n";
                std::cout << "Saldo: " << user.getBalance() << "\n";
                user.printSubscription();
                user.printOwned();
                user.printRentals();
                break;
            }
            case 9: {
                double amount = readDouble("Kwota doladowania: ");
                user.addMoney(amount);
                std::cout << "Doladowano. Nowe saldo: " << user.getBalance() << "\n";
                break;
            }
            case 10: {
                if (user.saveToFile("user.txt")) {
                    std::cout << "Zapisano dane uzytkownika do user.txt\n";
                } else {
                    std::cout << "Nie udalo sie zapisac user.txt\n";
                }
                break;
            }
            case 11: {
                if (user.loadFromFile("user.txt")) {
                    std::cout << "Wczytano dane uzytkownika z user.txt\n";
                } else {
                    std::cout << "Nie udalo sie wczytac user.txt\n";
                }
                break;
            }
            case 12: {
                int days = readInt("Podaj liczbe dni do symulacji: ");
                user.nextDays(days);
                std::cout << "Minelo " << days << " dni.\n";
                user.printSubscription();
                break;
            }

            case 0: {
                std::cout << "Zakonczono program.\n";
                break;
            }

            default: {
                std::cout << "Nieznana opcja.\n";
                break;
            }
        }
    }

    return 0;
}
