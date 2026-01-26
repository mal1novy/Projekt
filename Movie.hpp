#include "Content.hpp"
#include <string>

class Movie : public Content {
private:
    int durationMinutes;
    std::string genre;
    std::string quality;

protected:
    std::string serializeDetails() const override;
    void printDetails(std::ostream& os) const override;

public:
    Movie(int id, std::string title, int releaseYear, double price, bool inSub,
          int durationMinutes, std::string genre, std::string quality);

    std::string getType() const override;
};
