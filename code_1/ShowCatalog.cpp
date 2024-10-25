#include "ShowCatalog.hpp"
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

using namespace std;

ShowCatalog::ShowCatalog() {
    root=nullptr;
}

ShowCatalog::~ShowCatalog() {
    deleteNode(root);
}

void ShowCatalog::deleteNode(ShowItem* node) {
    if (node!=nullptr) {
        deleteNode(node->left);
        deleteNode(node->right);
        delete node;
    }
}

void ShowCatalog::printShowCatalog() {
    if (root==nullptr) {
        cout << "Tree is Empty. Cannot print" << endl;
    }
    printNodes(root);
}

void ShowCatalog::printNodes(ShowItem* node) {
    if (node==nullptr) {
        return;
    }
    cout << "Show: " << node->title << " " << node->userRating << endl;
    printNodes(node->left);
    printNodes(node->right);
    return;
}

void ShowCatalog::getShow(string title) {
    ShowItem* node = recurSearchbyTitle(root, title);
    if (node==nullptr) {
        cout << "Show not found." << endl;
        return;
    }
    cout << "Show Info:" << endl;
    cout << "==================" << endl;
    cout << "Title :" << node->title << endl;
    cout << "Year :" << node->year << endl;
    cout << "Show Rating :" << node->showRating << endl;
    cout << "User Rating :" << node->userRating << endl;
    return;
}

ShowItem* ShowCatalog::recurSearchbyTitle(ShowItem* node, string title) {
    while (node != NULL) {
        if (node->title == title) {
            return node;
        }
        if (title < node->title) {
            node = node->left;
        }
        else 
            node = node->right;
    }
    return nullptr;
}

void ShowCatalog::addShowItem(string title, int year, string showRating, float userRating) {
    preInsertHelper(root, title, year, showRating, userRating);
}

void ShowCatalog::preInsertHelper(ShowItem*& node, std::string title, int year, string showRating, float userRating) {
    if (root==nullptr) {
        root = new ShowItem(title, year, showRating, userRating);
    } else {
        insertHelper(node, title, year, showRating, userRating);
    }
}

void ShowCatalog::insertHelper(ShowItem*& node, std::string title, int year, string showRating, float userRating) {
    if (title < node->title) {
        if (node->left!=nullptr) {
            insertHelper(node->left, title, year, showRating, userRating);
        } else {
            node->left = new ShowItem(title, year, showRating, userRating);
        }
    } else if (title > node->title) {
        if (node->right!=nullptr) {
            insertHelper(node->right, title, year, showRating, userRating);
        } else {
            node->right = new ShowItem(title, year, showRating, userRating);
        }
    }
}

void ShowCatalog::printLeafNodes() {
    leafNodeHelper(root);
}

void ShowCatalog::leafNodeHelper(ShowItem* node) {
    if (node==nullptr) {
        return;
    }
    if ((node->left==nullptr) && (node->right==nullptr)) {
        cout << node->title << endl;
        return;
    }
    leafNodeHelper(node->left);
    leafNodeHelper(node->right);
    return;
}

void ShowCatalog::searchShows(char titleChar) {
    cout << "Shows that starts with " << titleChar << ":" << endl;
    if (root==nullptr) {
        cout << "Tree is Empty. Cannot search Shows." << endl;
        return;
    }
    rootTitleSearch(root, titleChar);
}

void ShowCatalog::rootTitleSearch(ShowItem* node, char firstChar) {
    if (node==nullptr) {
        return;
    }
    if (node->title[0]==firstChar) {
        cout << node->title << "(" << node->year << ") " << node->userRating << endl;
    }
    rootTitleSearch(node->left, firstChar);
    rootTitleSearch(node->right, firstChar);
    return;
}

void ShowCatalog::displayNumShowRating(int &count, string showRating) {
    showRatingHelper(root, count, showRating);
}

void ShowCatalog::showRatingHelper(ShowItem* node, int& num, std::string rating) {
    if (node==nullptr) {
        return;
    }
    showRatingHelper(node->left, num, rating);
    showRatingHelper(node->right, num, rating);
    if (node->showRating==rating) {
        num++;
    }
    return;
}
