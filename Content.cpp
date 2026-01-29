#include "Content.hpp"

Content::Content(int id, std::string title, int releaseYear, double price, bool inSub)
    : id(id), title(title), releaseYear(releaseYear), price(price), inSubscriptionPool(inSub) {}

int Content::getId() const { return id; }
std::string Content::getTitle() const { return title; }
int Content::getReleaseYear() const { return releaseYear; }
double Content::getPrice() const { return price; }
bool Content::isInSubscriptionPool() const { return inSubscriptionPool; }


void Content::printInfo(std::ostream& os) const {
    os << "[" << getType() << "] "
       << id << " | " << title
       << " | " << releaseYear
       << " | " << price
       << " | sub=" << (inSubscriptionPool ? "1" : "0");
    printDetails(os);
}

