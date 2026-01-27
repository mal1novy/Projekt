#pragma once
#include "Content.hpp"
#include <string>

class Series : public Content {
private:
    int seasons;
    int episodes;
    std::string genre;
    std::string quality;

protected:
    std::string serializeDetails() const override;
    void printDetails(std::ostream& os) const override;
    
public:
    Series(int id, std::string title, int releaseYear, double price, bool inSub,
           int seasons, int episodes, std::string genre, std::string quality);

    std::string getType() const override;




};

