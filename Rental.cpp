#include "Rental.hpp"

Rental::Rental(int contentId, int daysLeft)
    : contentId(contentId), daysLeft(daysLeft) {}

int Rental::getContentId() const { return contentId; }
int Rental::getDaysLeft() const { return daysLeft; }

void Rental::setDaysLeft(int d) { daysLeft = d; }

void Rental::decreaseDay() {
    if (daysLeft > 0) daysLeft--;
}
