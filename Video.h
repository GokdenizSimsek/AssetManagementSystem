#ifndef VIDEO_H
#define VIDEO_H

#include "Asset.h"

class Video : public Asset
{
private:
    int durationMinutes;
    string resolution;

public:
    Video(string title, string owner, int durationMinutes, string resolution, int idParam = -1)
        : Asset(title, owner, idParam)
    {
        this->durationMinutes = durationMinutes;
        this->resolution = resolution;
    }

    void display() const override
    {
        cout << "VIDEO | "
             << id << " | "
             << title << " | "
             << owner << " | "
             << durationMinutes << " minutes | "
             << resolution
             << endl;
    }

    string getType() const override
    {
        return "VIDEO";
    }

    Asset* clone() const override 
    {
        return new Video(*this);
    }

    string serialize() const override 
    {
        return "VIDEO," + to_string(id) + "," + title + "," + owner + "," + to_string(durationMinutes) + "," + resolution;
    }
};

#endif