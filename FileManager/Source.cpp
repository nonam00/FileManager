//работает только на версии c++ 2017 года
//также как и предыдущее схожее дз, реализовано на основе библиотеки, которой не было в курсе

#include <iostream>
#include <fstream>
#include <string>
#include <filesystem>

using namespace std;
namespace fs = std::filesystem;

void showFilesInDirectory(fs::path directory) {
    cout << "Files in directory " << directory << ":\n";
    for (const auto& entry : fs::directory_iterator(directory)) {
        cout << "  " << entry.path().filename() << "\n";
    }
    cout << endl;
}

void createFile(fs::path directory) {
    string filename;
    cout << "Enter the name of the new file: ";
    cin >> filename;
    fs::path filepath = directory / filename;
    ofstream file(filepath);
    if (file.is_open()) {
        cout << "File created successfully.\n";
    }
    else {
        cout << "Error creating file.\n";
    }
}

void deleteFile(fs::path directory) {
    string filename;
    cout << "Enter the name of the file to delete: ";
    cin >> filename;
    fs::path filepath = directory / filename;
    if (fs::exists(filepath)) {
        fs::remove(filepath);
        cout << "File deleted successfully.\n";
    }
    else {
        cout << "File not found.\n";
    }
}

void renameFile(fs::path directory) {
    string filename;
    cout << "Enter the name of the file to rename: ";
    cin >> filename;
    fs::path oldFilePath = directory / filename;
    if (!fs::exists(oldFilePath)) {
        cout << "File not found.\n";
        return;
    }
    string newFilename;
    cout << "Enter the new name of the file: ";
    cin >> newFilename;
    fs::path newFilePath = directory / newFilename;
    try {
        fs::rename(oldFilePath, newFilePath);
        cout << "File renamed successfully.\n";
    }
    catch (const fs::filesystem_error& e) {
        cout << "Error renaming file: " << e.what() << "\n";
    }
}

void moveFile(fs::path directory) {
    string filename;
    cout << "Enter the name of the file to move: ";
    cin >> filename;
    fs::path oldFilePath = directory / filename;
    if (!fs::exists(oldFilePath)) {
        cout << "File not found.\n";
        return;
    }
    fs::path destinationDirectory;
    cout << "Enter the destination directory: ";
    cin >> destinationDirectory;
    fs::path destinationPath = destinationDirectory / filename;
    try {
        fs::rename(oldFilePath, destinationPath);
        cout << "File moved successfully.\n";
    }
    catch (const fs::filesystem_error& e) {
        cout << "Error moving file: " << e.what() << "\n";
    }
}

void displayFileContents(fs::path directory) {
    string filename;
    cout << "Enter the name of the file to display: ";
    cin >> filename;
    fs::path filepath = directory / filename;
    if (fs::exists(filepath)) {
        ifstream file(filepath);
        if (file.is_open()) {
            cout << "Contents of file " << filename << ":\n";
            cout << file.rdbuf() << endl;
        }
        else {
            cout << "Error opening file.\n";
        }
    }
    else {
        cout << "File not found.\n";
    }
}

int main()
{
    fs::path directory = fs::current_path();
    int choice;
    while (true) {
        cout << "Current directory: " << directory << endl;
        cout << "What would you like to do?\n";
        cout << "  1. Show files in directory\n";
        cout << "  2. Create a new file\n";
        cout << "  3. Delete a file\n";
        cout << "  4. Rename a file\n";
        cout << "  5. Move a file\n";
        cout << "  6. Display the contents of a file\n";
        cout << "  7. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;
        switch (choice) {
        case 1:
            showFilesInDirectory(directory);
            break;
        case 2:
            createFile(directory);
            break;
        case 3:
            deleteFile(directory);
            break;
        case 4:
            renameFile(directory);
            break;
        case 5:
            moveFile(directory);
            break;
        case 6:
            displayFileContents(directory);
            break;
        case 7:
            return 0;
        default:
            cout << "Invalid choice. Please try again.\n";
        }
    }
    return 0;
}