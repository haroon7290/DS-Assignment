#include <iostream>
#include <string>

using namespace std;

struct Job {
    int jobId;
    string details;
    int rank;
    Job *next;
};

class JobList {
public:
    JobList() {
        head = nullptr;
    }

    void insertJob(int id, string details, int rank) {
        Job *newJob = new Job;
        newJob->jobId = id;
        newJob->details = details;
        newJob->rank = rank;
        newJob->next = nullptr;

        if (head == nullptr || newJob->rank > head->rank) {
            newJob->next = head;
            head = newJob;
        } else {
            Job *temp = head;
            while (temp->next != nullptr && temp->next->rank >= newJob->rank) {
                temp = temp->next;
            }
            newJob->next = temp->next;
            temp->next = newJob;
        }
    }

    void removeTopPriorityJob() {
        if (head != nullptr) {
            Job *temp = head;
            head = head->next;
            delete temp;
        }
    }

    void deleteJobById(int id) {
        if (head == nullptr) {
            return;
        }

        if (head->jobId == id) {
            Job *temp = head;
            head = head->next;
            delete temp;
            return;
        }

        Job *temp = head;
        while (temp->next != nullptr) {
            if (temp->next->jobId == id) {
                Job *toDelete = temp->next;
                temp->next = temp->next->next;
                delete toDelete;
                return;
            }
            temp = temp->next;
        }
    }

    void displayJobs() {
        Job *temp = head;
        while (temp != nullptr) {
            cout << "Job ID: " << temp->jobId << endl;
            cout << "Details: " << temp->details << endl;
            cout << "Rank: " << temp->rank << endl;
            cout << endl;
            temp = temp->next;
        }
    }

private:
    Job *head;
};

int main() {
    JobList jobList;
    int selection;

    while (true) {
        cout << "1. Add a new job" << endl;
        cout << "2. Display all jobs" << endl;
        cout << "3. Remove the job with the highest rank" << endl;
        cout << "4. Delete a job by ID" << endl;
        cout << "5. Quit" << endl;
        cout << "Choose an option: ";
        cin >> selection;

        switch (selection) {
            case 1: {
                int id, rank;
                string details;
                cout << "Enter job ID: ";
                cin >> id;
                cout << "Enter job details: ";
                cin.ignore();
                getline(cin, details);
                cout << "Enter job rank: ";
                cin >> rank;
                jobList.insertJob(id, details, rank);
                break;
            }
            case 2:
                jobList.displayJobs();
                break;
            case 3:
                jobList.removeTopPriorityJob();
                break;
            case 4: {
                int id;
                cout << "Enter the job ID to delete: ";
                cin >> id;
                jobList.deleteJobById(id);
                break;
            }
            case 5:
                exit(0);
            default:
                cout << "Invalid option. Try again." << endl;
        }
    }

    return 0;
}
