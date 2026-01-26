#include "Series.hpp"

Series::Series(int id, std::string title, int releaseYear, double price, bool inSub,
               int seasons, int episodes, std::string genre, std::string quality)
    : Content(id, title, releaseYear, price, inSub),
      seasons(seasons),
      episodes(episodes),
      genre(genre),
      quality(quality) {}

std::string Series::getType() const {
    return "SERIES";
}

std::string Series::serializeDetails() const {
    return std::to_string(seasons) + ";" +
           std::to_string(episodes) + ";" +
           genre + ";" +
           quality;
}

void Series::printDetails(std::ostream& os) const {
    os << " | sezony=" << seasons
       << " | odcinki=" << episodes
       << " | " << genre
       << " | " << quality;
}
