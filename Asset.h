#ifndef ASSET_H
#define ASSET_H

#include <string>
#include <iostream>

using namespace std;

class Asset
{
protected:
    int id;
    string title;
    string owner;

public:
    static int nextId;
    
    Asset(string title, string owner, int idParam = -1) 
    {
        this->title = title;
        this->owner = owner;

        if (idParam == -1) {
            this->id = nextId++; // Manual
        } else {
            this->id = idParam;  // From fie
        }
    }

    virtual ~Asset() {}

    int getId() const
    {
        return id;
    }

    string getTitle() const
    {
        return title;
    }

    string getOwner() const
    {
        return owner;
    }

    void setId(int newId) 
    { 
        this->id = newId; 
    }

    virtual void display() const = 0;
    virtual string getType() const = 0;
    virtual Asset* clone() const = 0;
    virtual string serialize() const = 0;
};

#endif