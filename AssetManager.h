#ifndef ASSETMANAGER_H
#define ASSETMANAGER_H

#include <vector>
#include "Asset.h"

class AssetManager
{
private:
    vector<Asset*> assets;

public:
    AssetManager();
    AssetManager(const AssetManager& other);
    AssetManager& operator=(const AssetManager& other);
    ~AssetManager();

    void addAsset(Asset* asset);
    void removeAsset(int id);
    void listAssets() const;
    void listAssetsByType(string type) const;

    Asset* searchById(int id) const;
    void searchByTitle(string title) const;

    void searchBooksByGenre(string genre) const;
    void searchPodcastsByTopic(string topic) const;

    int countBooks() const;
    int countVideos() const;
    int countPodcasts() const;

    void saveToFile(string filename) const;
    void loadFromFile(string filename);
};

#endif