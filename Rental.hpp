#pragma once
class Rental {
private:
    int contentId;
    int daysLeft;

public:
    Rental(int contentId, int daysLeft);

    int getContentId() const;
    int getDaysLeft() const;

    void setDaysLeft(int d);
    void decreaseDay();
};

