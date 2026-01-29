#pragma once
#include "Content.hpp"
#include <string>

class Game : public Content {
protected:
    void printDetails(std::ostream& os) const override;

private:
    std::string genre;
    int playtimeHours;
    std::string difficulty;
    std::string ageRating;

public:
    Game(int id, std::string title, int releaseYear, double price, bool inSub,
         std::string genre, int playtimeHours, std::string difficulty,
         std::string ageRating);

    std::string getType() const override;
};


