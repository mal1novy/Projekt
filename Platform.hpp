#pragma once
#include <vector>
#include <string>
#include "Content.hpp"
#include "User.hpp"

class Platform {
private:
    std::vector<Content*> contents;

    static std::vector<std::string> split(const std::string& s, char delim);

public:
    Platform();
    ~Platform();

    void loadFromFile(const std::string& filename);
    void saveToFile(const std::string& filename) const;

    void listAll() const;
    Content* findById(int id) const;
    void searchByTitle(const std::string& fragment) const;

    bool buy(User& user, int contentId);
    bool rent(User& user, int contentId, int days);
    bool subscribe(User& user, int days);
    bool canAccess(const User& user, int contentId) const;
    void playOrWatch(const User& user, int contentId) const;

    void listByType(const std::string& type) const;
};

