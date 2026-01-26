#include "Subscription.hpp"

Subscription::Subscription() : daysLeft(0) {}

void Subscription::start(int days) {
    if (days > 0) daysLeft = days;
}

bool Subscription::isActive() const {
    return daysLeft > 0;
}

int Subscription::getDaysLeft() const {
    return daysLeft;
}

void Subscription::decreaseDay() {
    if (daysLeft > 0) daysLeft--;
}

void Subscription::setDaysLeft(int days) {
    if (days < 0) days = 0;
    daysLeft = days;
}

