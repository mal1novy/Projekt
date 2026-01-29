#include "Movie.hpp"

Movie::Movie(int id, std::string title, int releaseYear, double price, bool inSub,
             int durationMinutes, std::string genre, std::string quality)
    : Content(id, title, releaseYear, price, inSub),
      durationMinutes(durationMinutes),
      genre(genre),
      quality(quality) {}

std::string Movie::getType() const {
    return "MOVIE";
}


void Movie::printDetails(std::ostream& os) const {
    os << " | " << durationMinutes << "min"
       << " | " << genre
       << " | " << quality;
}

