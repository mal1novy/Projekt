#pragma once
#include <string>
#include <iostream>

class Content {   
protected:
    int id;
    std::string title;
    int releaseYear;
    double price;
    bool inSubscriptionPool;

    virtual std::string serializeDetails() const = 0;
    virtual void printDetails(std::ostream& os) const = 0;
public:
    Content(int id, std::string title, int releaseYear, double price, bool inSub);
    virtual ~Content(){};

    int getId() const;
    std::string getTitle() const;
    int getReleaseYear() const;
    double getPrice() const;
    bool isInSubscriptionPool() const;

    virtual std::string getType() const = 0;

    std::string serialize() const;
    void printInfo(std::ostream& os) const;
};

