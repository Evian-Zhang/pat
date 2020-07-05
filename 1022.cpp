#include <cstdio>
#include <cstring>
#include <iostream>
#include <string>
#include <set>
#include <unordered_map>
#include <vector>
#include <functional>
using namespace std;

void insertOrCreate(unordered_map<string, set<string> > *container, string key, string id) {
    auto pos = container->find(key);
    if (pos != container->end()) {
        pos->second.emplace(id);
    } else {
        set<string> ids;
        ids.emplace(id);
        container->emplace(key, ids);
    }
}

void findAndDisplay(unordered_map<string, set<string> > *container, string key) {
    auto ids = container->find(key);
    if (ids == container->end()) {
        printf("\nNot Found");
    } else {
        for (auto id : ids->second) {
            printf("\n%s", id.c_str());
        }
    }
}

int main() {
    unordered_map<string, set<string> > titles, authors, words, publishers, years;

    int n;
    scanf("%d", &n);
    getchar();
    for (int i = 0; i < n; i++) {
        char tmpstr[64];
        cin.getline(tmpstr, 64);
        string id(tmpstr);
        cin.getline(tmpstr, 64);
        string title(tmpstr);
        insertOrCreate(&titles, title, id);
        cin.getline(tmpstr, 64);
        string author(tmpstr);
        insertOrCreate(&authors, author, id);
        char keywords[64];
        cin.getline(keywords, 64);
        char *keyword = strtok(keywords, " ");
        while (keyword != NULL) {
            string word(keyword);
            insertOrCreate(&words, word, id);
            keyword = strtok(NULL, " ");
        }
        cin.getline(tmpstr, 64);
        string publisher(tmpstr);
        insertOrCreate(&publishers, publisher, id);
        cin.getline(tmpstr, 64);
        string year(tmpstr);
        insertOrCreate(&years, year, id);
    }

    int m;
    scanf("%d", &m);
    for (int i = 0; i < m; i++) {
        int type;
        scanf("%d", &type);
        getchar();
        getchar();
        char keystr[64];
        cin.getline(keystr, 64);
        string key(keystr);
        if (i != 0) { printf("\n"); }
        cout << type << ": " << key;
        switch (type) {
            case 1: findAndDisplay(&titles, key); break;
            case 2: findAndDisplay(&authors, key); break;
            case 3: findAndDisplay(&words, key); break;
            case 4: findAndDisplay(&publishers, key); break;
            case 5: findAndDisplay(&years, key); break;
        }
    }

    return 0;
}