#include <string>
#include <vector>
#include "Rental.hpp"
#include "Subscription.hpp"

class User {
private:
    std::string name;
    double balance;

    std::vector<int> ownedIds;
    std::vector<Rental> rentals;

    Subscription subscription;

public:
    User(std::string name, double balance);

    std::string getName() const;
    double getBalance() const;

    void addMoney(double amount);
    bool pay(double amount);

    // Zakupy
    void addOwned(int contentId);
    bool owns(int contentId) const;

    // Wypożyczenia
    void addRental(int contentId, int daysLeft);
    bool hasActiveRental(int contentId) const;

    // Subskrypcja
    void startSubscription(int days);
    bool hasActiveSubscription() const;
    int subscriptionDaysLeft() const;

    // pomocnicze
    void printOwned() const;
    void printRentals() const;
    void printSubscription() const;

    bool saveToFile(const std::string& filename) const;
    bool loadFromFile(const std::string& filename);

    void nextDays(int days);
};
