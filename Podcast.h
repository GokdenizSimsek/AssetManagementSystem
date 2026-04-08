#ifndef PODCAST_H
#define PODCAST_H

#include "Asset.h"

class Podcast : public Asset
{
private:
    string host;
    int episodeCount;
    string topic;

public:
    Podcast(string title, string owner, string host, int episodeCount, string topic, int idParam = -1)
        : Asset(title, owner, idParam)
    {
        this->host = host;
        this->episodeCount = episodeCount;
        this->topic = topic;
    }

    void display() const override
    {
        cout << "PODCAST | "
             << id << " | "
             << title << " | "
             << owner << " | "
             << host << " | "
             << episodeCount << " episodes" << " | "
             << topic
             << endl;
    }

    string getType() const override
    {
        return "PODCAST";
    }

    string getTopic() const
    {
        return topic;
    }

    Asset* clone() const override 
    {
        return new Podcast(*this);
    }

    string serialize() const override 
    {
        return "PODCAST," + to_string(id) + "," + title + "," + owner + "," + host + "," + to_string(episodeCount) + "," + topic;
    }
};

#endif