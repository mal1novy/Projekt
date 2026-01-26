class Subscription {
private:
    int daysLeft;
    
public:
    Subscription();

    void start(int days);          // uruchamia subskrypcję na x dni
    bool isActive() const;         // czy jest aktywna
    int getDaysLeft() const;       // ile dni zostało
    void decreaseDay();            // symulacja upływu 1 dnia
    void setDaysLeft(int days);



};
