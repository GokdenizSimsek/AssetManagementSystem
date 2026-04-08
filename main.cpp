#include <iostream>
#include <fstream>
#include "AssetManager.h"
#include "Book.h"
#include "Video.h"
#include "Podcast.h"

using namespace std;

int main()
{
    AssetManager manager;
    int choice;

    while (true)
    {
        cout << "\n===== ASSET MANAGEMENT SYSTEM =====\n"
        << "1 Add Book\n"
        << "2 Add Video\n"
        << "3 Add Podcast\n"
        << "4 List All Assets\n"
        << "5 List Books\n"
        << "6 List Videos\n"
        << "7 List Podcasts\n"
        << "8 Search Assets by ID\n"
        << "9 Search Assets by Title\n"
        << "10 Search Books by Genre\n"
        << "11 Search Podcasts by Topic\n"
        << "12 Count Assets\n"
        << "13 Remove Asset\n"
        << "14 Load from File\n"
        << "15 Save to File\n"
        << "0 Exit\n";

        cout << "Choice: ";
        if (!(cin >> choice)) 
        {
            cout << "Please enter a valid number!" << endl;
            cin.clear();
            cin.ignore(1000, '\n');
            continue;
        }
        cin.ignore();

        cout << endl;
        switch (choice)
        {
        case 1:     // Add Book
        {
            int pages;
            string title, owner, author, genre;

            cout << "Title: ";
            getline(cin, title);

            cout << "Owner: ";
            getline(cin, owner);

            cout << "Author: ";
            getline(cin, author);

            cout << "Page Count: ";
            while (!(cin >> pages)) {
                cout << "Invalid input! Please enter a numeric value for Page Count: ";
                cin.clear();
                cin.ignore(1000, '\n');
            }
            cin.ignore();

            cout << "Genre: ";
            getline(cin, genre);

            manager.addAsset(new Book(title, owner, author, pages, genre));
            break;
        }

        case 2:     // Add Video
        {
            int duration;
            string title, owner, resolution;

            cout << "Title: ";
            getline(cin, title);

            cout << "Owner: ";
            getline(cin, owner);

            cout << "Duration (minutes): ";
            while (!(cin >> duration)) {
                cout << "Invalid input! Please enter a numeric value for Duration: ";
                cin.clear();
                cin.ignore(1000, '\n');
            }
            cin.ignore();

            cout << "Resolution: ";
            getline(cin, resolution);

            manager.addAsset(new Video(title, owner, duration, resolution));
            break;
        }

        case 3:     // Add Podcast
        {
            int episodes;
            string title, owner, host, topic;

            cout << "Title: ";
            getline(cin, title);

            cout << "Owner: ";
            getline(cin, owner);

            cout << "Host: ";
            getline(cin, host);

            cout << "Episode Count: ";
            while (!(cin >> episodes)) {
                cout << "Invalid input! Please enter a numeric value for Episode Count: ";
                cin.clear();
                cin.ignore(1000, '\n');
            }
            cin.ignore();

            cout << "Topic: ";
            getline(cin, topic);

            manager.addAsset(new Podcast(title, owner, host, episodes, topic));
            break;
        }

        case 4:     // List Assets
        {
            manager.listAssets();
            break;
        }

        case 5:     // List Books
        {
            manager.listAssetsByType("BOOK");
            break;
        }

        case 6:     // List Videos
        {
            manager.listAssetsByType("VIDEO");
            break;
        }

        case 7:     // List Podcasts
        {
            manager.listAssetsByType("PODCAST");
            break;
        }

        case 8:     // Search Asset by ID
        {
            int id;
            cout << "Enter ID: ";
            while (!(cin >> id)) {
                cout << "Invalid ID format! Please enter a numeric ID: ";
                cin.clear();
                cin.ignore(1000, '\n');
            }
            cin.ignore();

            Asset* asset = manager.searchById(id);

            if (asset)
                asset->display();
            else
                cout << "Asset not found.\n";
            break;
        }

        case 9:     // Search Asset by Title
        {
            string title;

            cout << "Enter title keyword: ";
            getline(cin, title);

            manager.searchByTitle(title);
            break;
        }

        case 10:     // Search Books by Genre
        {
            string genre;

            cout << "Enter genre: ";
            getline(cin, genre);

            manager.searchBooksByGenre(genre);
            break;
        }

        case 11:     // Search Podcasts by Topic
        {
            string topic;

            cout << "Enter topic: ";
            getline(cin, topic);

            manager.searchPodcastsByTopic(topic);
            break;
        }

        case 12:     // Asset Counts
        {
            cout << "Total Assets: " << manager.countBooks() + manager.countVideos() + manager.countPodcasts() << endl;
            cout << "Books: " << manager.countBooks() << endl;
            cout << "Videos: " << manager.countVideos() << endl;
            cout << "Podcasts: " << manager.countPodcasts() << endl;
            break;
        }

        case 13:    // Remove Asset
        {
            int id;
            cout << "Enter ID to remove: ";
            while (!(cin >> id)) {
                cout << "Invalid ID format! Please enter a numeric ID: ";
                cin.clear();
                cin.ignore(1000, '\n');
            }
            cin.ignore();

            manager.removeAsset(id);
            break;
        }

        case 14:    // Load from File
        {
            string filename;
            bool success = false;

            while (!success) 
            {
                cout << "Enter filename to load (or '0' to cancel): ";
                cin >> filename;
                cin.ignore();

                if (filename == "0") break;

                ifstream checkFile(filename);
                if (checkFile.is_open()) 
                {
                    checkFile.close();
                    manager.loadFromFile(filename);
                    success = true;
                } else {
                    cout << "Error: File '" << filename << "' not found. Please try again." << endl;
                }
            }
            break;
        }

        case 15:    // Save to File
        {
            manager.saveToFile("assets.txt");
            break;
        }

        case 0:     // Exit
        {
            cout << "Exiting...\n";
            return 0;
        }

        case 99:
        {
            AssetManager originalManager;

            originalManager.addAsset(new Book("Test Book", "Owner", "Author", 100, "Genre"));
            originalManager.addAsset(new Video("Test Video", "Owner", 100, "4K"));
            originalManager.addAsset(new Podcast("Test Podcast", "Owner", "Host", 100, "Topic"));

            cout << "--- Original List (Before Deletion) ---" << endl;
            originalManager.listAssets();

            cout << "\nCopied: originalManager -> copiedManager..." << endl;
            AssetManager copiedManager = originalManager;

            cout << "Original Manager Deleting..." << endl;
            originalManager.removeAsset(1);

            cout << "\n--- Original Manager (After Deletion First Asset) ---" << endl;
            originalManager.listAssets();

            cout << "\n--- Copied Manager (Still Being Stored?) ---" << endl;
            copiedManager.listAssets();

            originalManager.removeAsset(2); originalManager.removeAsset(3);
            cout << "\n--- Original Manager (After Deletion All) ---" << endl;
            originalManager.listAssets();

            cout << "\n--- Copied Manager (Still Being Stored?) ---" << endl;
            copiedManager.listAssets();
        }

        default:
        {
            cout << "Invalid choice.\n";
        }
        }
    }

    return 0;
}