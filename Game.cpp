#include "Game.hpp"

Game::Game(int id, std::string title, int releaseYear, double price, bool inSub,
           std::string genre, int playtimeHours, std::string difficulty,
           std::string ageRating)
    : Content(id, title, releaseYear, price, inSub),
      genre(genre),
      playtimeHours(playtimeHours),
      difficulty(difficulty),
      ageRating(ageRating){}

std::string Game::getType() const {
    return "GAME";
}

std::string Game::serializeDetails() const {
    return genre + ";" +
           std::to_string(playtimeHours) + ";" +
           difficulty + ";" +
           ageRating;
}

void Game::printDetails(std::ostream& os) const {
    os << " | " << genre
       << " | " << playtimeHours << "h"
       << " | " << difficulty
       << " | " << ageRating << std::endl;
}
