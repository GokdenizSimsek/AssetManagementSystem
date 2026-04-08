#ifndef BOOK_H
#define BOOK_H

#include "Asset.h"

class Book : public Asset
{
private:
    string author;
    int pageCount;
    string genre;

public:
    Book(string title, string owner, string author, int pages, string genre, int idParam = -1)
        : Asset(title, owner, idParam)
    {
        this->author = author;
        this->pageCount = pages;
        this->genre = genre;
    }

    void display() const override
    {
        cout << "BOOK | "
             << id << " | "
             << title << " | "
             << owner << " | "
             << author << " | "
             << pageCount << " pages" << " | "
             << genre
             << endl;
    }

    string getType() const override
    {
        return "BOOK";
    }

    string getGenre() const
    {
        return genre;
    }

    Asset* clone() const override 
    {
        return new Book(*this);
    }

    string serialize() const override 
    {
        return "BOOK," + to_string(id) + "," + title + "," + owner + "," + author + "," + to_string(pageCount) + "," + genre;
    }
};

#endif