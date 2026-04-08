#include "AssetManager.h"
#include "Book.h"
#include "Video.h"
#include "Podcast.h"

#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

AssetManager::AssetManager()
{
}

AssetManager::AssetManager(const AssetManager& other)
{
    for (auto asset : other.assets)
    {
        if (asset != nullptr) {
            this->assets.push_back(asset->clone()); // Adres kopyalamayıp yeni nesne yaratır
        }
    }
}

AssetManager& AssetManager::operator=(const AssetManager& other) 
{
    if (this != &other) {
        for (auto asset : assets) {
            delete asset;
        }
        assets.clear();

        for (auto asset : other.assets) {
            assets.push_back(asset->clone());
        }
    }
    return *this;
}

AssetManager::~AssetManager()
{
    for (auto asset : assets)
    {
        delete asset;
    }
    assets.clear();
}

void AssetManager::addAsset(Asset* asset)
{
    assets.push_back(asset);
}

void AssetManager::removeAsset(int id)
{
    for (auto it = assets.begin(); it != assets.end(); ++it)
    {
        if ((*it)->getId() == id)
        {
            delete *it;
            assets.erase(it);
            cout << "Asset removed." << endl;
            if (id == Asset::nextId - 1) 
            {
                Asset::nextId = id;
            }
            return;
        }
    }

    cout << "Asset not found." << endl;
}

void AssetManager::listAssets() const
{
    if (assets.empty())
    {
        cout << "No assets available." << endl;
        return;
    }

    for (auto asset : assets)
    {
        asset->display();
    }
}

void AssetManager::listAssetsByType(string type) const
{
    bool found = false;
    for (auto asset : assets)
    {
        if (asset->getType() == type)
        {
            asset->display();
            found = true;
        }
    }

    if (!found)
    {
        cout << "No " << type << "s available in the system." << endl;
    }
}

Asset* AssetManager::searchById(int id) const
{
    for (auto asset : assets)
    {
        if (asset->getId() == id)
        {
            return asset;
        }
    }

    return nullptr;
}

void AssetManager::searchByTitle(string title) const
{
    for (auto asset : assets)
    {
        if (asset->getTitle().find(title) != string::npos)
        {
            asset->display();
        }
    }
}

void AssetManager::searchBooksByGenre(string genre) const
{
    for (auto asset : assets)
    {
        if (asset->getType() == "BOOK")
        {
            Book* book = dynamic_cast<Book*>(asset);

            if (book && book->getGenre() == genre)
            {
                book->display();
            }
        }
    }
}

void AssetManager::searchPodcastsByTopic(string topic) const
{
    for (auto asset : assets)
    {
        if (asset->getType() == "PODCAST")
        {
            Podcast* podcast = dynamic_cast<Podcast*>(asset);

            if (podcast && podcast->getTopic() == topic)
            {
                podcast->display();
            }
        }
    }
}

int AssetManager::countBooks() const
{
    int count = 0;

    for (auto asset : assets)
    {
        if (asset->getType() == "BOOK")
        {
            count++;
        }
    }

    return count;
}

int AssetManager::countVideos() const
{
    int count = 0;

    for (auto asset : assets)
    {
        if (asset->getType() == "VIDEO")
        {
            count++;
        }
    }

    return count;
}

int AssetManager::countPodcasts() const
{
    int count = 0;

    for (auto asset : assets)
    {
        if (asset->getType() == "PODCAST")
        {
            count++;
        }
    }

    return count;
}

void AssetManager::saveToFile(string filename) const 
{
    ofstream file(filename);
    for (auto asset : assets) 
    {
        file << asset->serialize() << endl;
    }
    file.close();
    cout << "Assets saved successfully." << endl;
}

void AssetManager::loadFromFile(string filename) 
{
    ifstream file(filename);
    if (!file.is_open()) return;

    string line;
    while (getline(file, line)) {
        if (line.empty()) continue;

        stringstream ss(line);
        string type, idStr, title, owner, extra1, extra2, extra3;

        //Type, ID, Title, Owner
        if (!getline(ss, type, ',') || !getline(ss, idStr, ',') || 
            !getline(ss, title, ',') || !getline(ss, owner, ',')) continue;

        try {
            int fileId = stoi(idStr);
            Asset* newAsset = nullptr;

            if (type == "BOOK") {
                // BOOK: Author, PageCount, Genre
                if (getline(ss, extra1, ',') && getline(ss, extra2, ',') && getline(ss, extra3)) {
                    newAsset = new Book(title, owner, extra1, stoi(extra2), extra3, fileId);
                }
            } 
            else if (type == "VIDEO") {
                // VIDEO: Duration, Resolution
                if (getline(ss, extra1, ',') && getline(ss, extra2)) {
                    newAsset = new Video(title, owner, stoi(extra1), extra2, fileId);
                }
            }
            else if (type == "PODCAST") {
                // PODCAST: Host, EpisodeCount, Topic
                if (getline(ss, extra1, ',') && getline(ss, extra2, ',') && getline(ss, extra3)) {
                    newAsset = new Podcast(title, owner, extra1, stoi(extra2), extra3, fileId);
                }
            }

            if (newAsset) {
                if (searchById(fileId) == nullptr) {
                    newAsset->setId(fileId);
                } else {
                    cout << "Collision! ID " << fileId << " used. Assigned: " << newAsset->nextId << endl;
                    newAsset->setId(newAsset->nextId++);
                }
                assets.push_back(newAsset);
            }
        } catch (...) { continue; }
    }
    
    int maxId = 0;
    for (auto a : assets) if (a->getId() > maxId) maxId = a->getId();
    Asset::nextId = maxId + 1;

    file.close();
    cout << "Sync complete. Next ID will be: " << Asset::nextId << endl;
}