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


void Series::printDetails(std::ostream& os) const {
    os << " | seasons=" << seasons
       << " | episodes=" << episodes
       << " | " << genre
       << " | " << quality;
}


