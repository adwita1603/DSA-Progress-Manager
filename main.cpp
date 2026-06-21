#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <map>

using namespace std;

class Problem {
public:
    string title;
    string topic;
    string difficulty;
    string platform;
    bool solved;

    Problem() {}

    Problem(string t, string tp, string d,
            string p, bool s) {
        title = t;
        topic = tp;
        difficulty = d;
        platform = p;
        solved = s;
    }
};

class ProgressManager {
private:
    vector<Problem> problems;

public:

    void addProblem() {
        cin.ignore();

        string title, topic, difficulty, platform;
        bool solved;

        cout << "\nProblem Title: ";
        getline(cin, title);

        cout << "Topic: ";
        getline(cin, topic);

        cout << "Difficulty (Easy/Medium/Hard): ";
        getline(cin, difficulty);

        cout << "Platform: ";
        getline(cin, platform);

        cout << "Solved? (1 = Yes, 0 = No): ";
        cin >> solved;

        problems.push_back(
            Problem(title, topic,
                    difficulty, platform,
                    solved)
        );

        cout << "\nProblem Added Successfully!\n";
    }

    void viewProblems() {

        if(problems.empty()) {
            cout << "\nNo Problems Available!\n";
            return;
        }

        cout << "\n===== Problem List =====\n";

        for(int i = 0; i < problems.size(); i++) {

            cout << "\nProblem #" << i + 1 << endl;
            cout << "Title      : " << problems[i].title << endl;
            cout << "Topic      : " << problems[i].topic << endl;
            cout << "Difficulty : " << problems[i].difficulty << endl;
            cout << "Platform   : " << problems[i].platform << endl;
            cout << "Solved     : "
                 << (problems[i].solved ? "Yes" : "No")
                 << endl;
        }
    }

    void searchProblem() {

        cin.ignore();

        string target;

        cout << "\nEnter Problem Title: ";
        getline(cin, target);

        bool found = false;

        for(auto &p : problems) {

            if(p.title == target) {

                found = true;

                cout << "\nProblem Found!\n";
                cout << "Title      : " << p.title << endl;
                cout << "Topic      : " << p.topic << endl;
                cout << "Difficulty : " << p.difficulty << endl;
                cout << "Platform   : " << p.platform << endl;
                cout << "Solved     : "
                     << (p.solved ? "Yes" : "No")
                     << endl;
            }
        }

        if(!found)
            cout << "\nProblem Not Found!\n";
    }

    void deleteProblem() {

        cin.ignore();

        string target;

        cout << "\nEnter Problem Title To Delete: ";
        getline(cin, target);

        for(auto it = problems.begin();
            it != problems.end();
            it++) {

            if(it->title == target) {

                problems.erase(it);

                cout << "\nProblem Deleted!\n";
                return;
            }
        }

        cout << "\nProblem Not Found!\n";
    }

    void filterByTopic() {

        cin.ignore();

        string topic;

        cout << "\nEnter Topic: ";
        getline(cin, topic);

        bool found = false;

        for(auto &p : problems) {

            if(p.topic == topic) {

                found = true;

                cout << "\n" << p.title
                     << " | "
                     << p.difficulty
                     << " | "
                     << p.platform
                     << endl;
            }
        }

        if(!found)
            cout << "\nNo Problems Found!\n";
    }

    void showStatistics() {

        int solvedCount = 0;

        int easy = 0;
        int medium = 0;
        int hard = 0;

        map<string,int> topicCount;

        for(auto &p : problems) {

            if(p.solved)
                solvedCount++;

            topicCount[p.topic]++;

            if(p.difficulty == "Easy")
                easy++;

            else if(p.difficulty == "Medium")
                medium++;

            else if(p.difficulty == "Hard")
                hard++;
        }

        cout << "\n===== Statistics =====\n";

        cout << "Total Problems  : "
             << problems.size() << endl;

        cout << "Solved Problems : "
             << solvedCount << endl;

        cout << "\nDifficulty Distribution\n";

        cout << "Easy   : " << easy << endl;
        cout << "Medium : " << medium << endl;
        cout << "Hard   : " << hard << endl;

        cout << "\nTopic Wise Count\n";

        for(auto x : topicCount) {

            cout << x.first
                 << " : "
                 << x.second
                 << endl;
        }
    }

    void saveToFile() {

        ofstream fout("problems.txt");

        for(auto &p : problems) {

            fout << p.title << "|"
                 << p.topic << "|"
                 << p.difficulty << "|"
                 << p.platform << "|"
                 << p.solved
                 << endl;
        }

        fout.close();
    }

    void loadFromFile() {

        ifstream fin("problems.txt");

        string line;

        while(getline(fin, line)) {

            stringstream ss(line);

            string title;
            string topic;
            string difficulty;
            string platform;
            string solvedStr;

            getline(ss, title, '|');
            getline(ss, topic, '|');
            getline(ss, difficulty, '|');
            getline(ss, platform, '|');
            getline(ss, solvedStr, '|');

            bool solved = (solvedStr == "1");

            problems.push_back(
                Problem(
                    title,
                    topic,
                    difficulty,
                    platform,
                    solved
                )
            );
        }

        fin.close();
    }
};

int main() {

    ProgressManager pm;

    pm.loadFromFile();

    int choice;

    do {

        cout << "\n\n===== DSA Progress Manager =====\n";
        cout << "1. Add Problem\n";
        cout << "2. View Problems\n";
        cout << "3. Search Problem\n";
        cout << "4. Delete Problem\n";
        cout << "5. Filter By Topic\n";
        cout << "6. Show Statistics\n";
        cout << "7. Save & Exit\n";

        cout << "\nEnter Choice: ";
        cin >> choice;

        switch(choice) {

            case 1:
                pm.addProblem();
                break;

            case 2:
                pm.viewProblems();
                break;

            case 3:
                pm.searchProblem();
                break;

            case 4:
                pm.deleteProblem();
                break;

            case 5:
                pm.filterByTopic();
                break;

            case 6:
                pm.showStatistics();
                break;

            case 7:
                pm.saveToFile();
                cout << "\nData Saved Successfully!\n";
                break;

            default:
                cout << "\nInvalid Choice!\n";
        }

    } while(choice != 7);

    return 0;
}