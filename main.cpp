#include <bits/stdc++.h>

using namespace std;

struct Lib {
    int nBooks;
    int signDays;
    int nBooksPerDay;

    vector<int> booksToScan;
};

void solve(ifstream &in, ofstream &out) {
    int nBooks, nLibs, nDays;
    in >> nBooks >> nLibs >> nDays;

    vector<int> bookScore(nBooks);
    for (int i = 0; i < nBooks; ++i) {
        in >> bookScore[i];
    }

    auto lambda = [&](auto &b1, auto &b2) {
        return bookScore[b1] > bookScore[b2] || (bookScore[b1] == bookScore[b2] && b1 > b2);
    };
    vector<Lib> libs(nLibs);
    vector<set<int, decltype(lambda)>> libToBooks(nLibs, set<int, decltype(lambda)>(lambda));
    for (int j = 0; j < nLibs; ++j) {
        auto &lib = libs[j];
        in >> lib.nBooks >> lib.signDays >> lib.nBooksPerDay;
        for (int i = 0; i < lib.nBooks; ++i) {
            int bookId;
            in >> bookId;
            libToBooks[j].insert(bookId);
        }
    }
    vector<int> intersectionBooks(nBooks);
    for (int l = 0; l < nLibs; ++l) {
        for (auto &bookId : libToBooks[l]) {
            intersectionBooks[bookId]++;
        }
    }

    vector<int> outLibs;

    unordered_set<int> checkLibs;
    for (int k = 0; k < nLibs; ++k) {
        checkLibs.insert(k);
    }
    int curDay = 0;
    while (!checkLibs.empty()) {
        double bestScore = -1;
        int bestLib;
        for (auto &libId : checkLibs) {
            auto &lib = libs[libId];
            double tempScore = 0;

            int points = 0;
            int scanDays = max(nDays - curDay - lib.signDays, 0);
            int scanBooks = min(scanDays * lib.nBooksPerDay, (int) libToBooks[libId].size());
            auto it = libToBooks[libId].begin();
            for (int i = 0; i < scanBooks; ++i) {
                int bookId = *it;
                points += bookScore[bookId];
                ++it;
            }
            //B
//            tempScore = (double) 1 / pow(lib.signDays, 1.);
            // C
//            tempScore = (double) pow(points, 1.) / pow(lib.signDays, 1.);
            //D
//            tempScore = (double) libToBooks[libId].size();
            // E
//            tempScore = (double) pow(points, 1.146) / pow(lib.signDays, 1.);
            // F
            if (scanBooks == 0) {
                tempScore = 0;
            } else {
                tempScore = (double) pow(points, 1.) * pow(1 + ((double)libToBooks[libId].size() - scanBooks)/(double)scanBooks, 0.05) / pow(lib.signDays, 1.);
            }
//            cout << pow(points, 1.146) << " " << pow(lib.signDays, 1.) << " " << pow(scanBooks + 1, 0.1) << " " << tempScore << endl;
            if (tempScore > bestScore) {
                bestScore = tempScore;
                bestLib = libId;
            }
        }
        checkLibs.erase(bestLib);


        int scanDayss = max(nDays - curDay - libs[bestLib].signDays, 0);
        int scanBookss = min(scanDayss * libs[bestLib].nBooksPerDay, (int) libToBooks[bestLib].size());
        if (scanBookss == 0) continue;

        outLibs.push_back(bestLib);
        int scanDays = nDays - curDay - libs[bestLib].signDays;
        int scanBooks = min(scanDays * libs[bestLib].nBooksPerDay, (int) libToBooks[bestLib].size());
        auto it = libToBooks[bestLib].begin();
        for (int i = 0; i < scanBooks; ++i) {
            int bookId = *it;
            libs[bestLib].booksToScan.push_back(bookId);
            for (auto &remainedLibId : checkLibs) {
                libToBooks[remainedLibId].erase(bookId);
            }
            ++it;
        }
        curDay += libs[bestLib].signDays;

        if (checkLibs.size() % 100 == 0) {
            cout << checkLibs.size() << endl;
        }
    }


    out << outLibs.size() << endl;
    for (int n = 0; n < outLibs.size(); ++n) {
        int libId = outLibs[n];

        out << libId << " " << libs[libId].booksToScan.size() << endl;
        for (int i = 0; i < libs[libId].booksToScan.size(); ++i) {
            out << libs[libId].booksToScan[i] << " ";
        }
        out << endl;

    }
}

int main() {
    string fileDirectory = "/home/alex/Workspace/hashcode-2020/";

    vector<string> files;
//    files.emplace_back("a_example.txt");
//    files.emplace_back("b_read_on.txt");
//    files.emplace_back("c_incunabula.txt");
//    files.emplace_back("d_tough_choices.txt");
//    files.emplace_back("e_so_many_books.txt");
    files.emplace_back("f_libraries_of_the_world.txt");

    for (auto &filename : files) {
        ifstream in(fileDirectory + filename);
        ofstream out(fileDirectory + "out_" + filename);
        solve(in, out);
        out.close();
        in.close();
    }

    return 0;
}
