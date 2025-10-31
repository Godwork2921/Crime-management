#include <iostream>

using namespace std;

struct CriminalCase {
    int caseId;
    string name;
    string crimeType;
    int age;
    string date;
    string sex;
    string crimeHistory;
    CriminalCase* next;
};

CriminalCase* start_ptr = NULL;  // Head of the linked list
bool isAdminLoggedIn = false;

// Helper to ensure positive numbers
int getPositiveInt(string prompt, int min = 1) {
    int value;

    while (true) {
        cout << prompt;
        cin >> value;
        if (cin.fail() || value < min) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Please enter a number >= " << min << ".\n";
        } else {
            cin.ignore(); // clear newline character after valid input
            return value;
        }
    }
}





//bool isValidDate(const string& date)
  //  if (date.length() != 10) return false;
    //if (date[2] != '/' || date[5] != '/') return false;
//
  //  int day = stoi(date.substr(0, 2));
    //int month = stoi(date.substr(3, 2));
    //int year = stoi(date.substr(6, 4));

    //if (day < 1 || day > 30) return false;
    //if (month < 1 || month > 12) return false;
    //if (year < 1000 || year > 9999) return false;

    //return true;}











// Validate dd/mm/yyyy format (days 01�30, months 01�12, 4-digit year)




// Check if a case ID already exists
bool isDuplicateId(int id) {
    CriminalCase* temp = start_ptr;
    while (temp != NULL) {
        if (temp->caseId == id) return true;
        temp = temp->next;
    }
    return false;
}

void addCase(int id, string name, string type, int age, string date, string sex, string history) {
    if (!isAdminLoggedIn) {
        cout << "You must be logged in as admin to add cases.\n";
        return;
    }
    if (isDuplicateId(id)) {
        cout << "Case ID already exists. Cannot add duplicate.\n";
        return;
    }
    CriminalCase* newCase = new CriminalCase{id, name, type, age, date, sex, history, start_ptr};
    start_ptr = newCase;
    cout << "Case added successfully!\n";
}

void displayCases() {
    if (start_ptr == NULL) {
        cout << "No cases available.\n";
        return;
    }
    CriminalCase* temp = start_ptr;
    while (temp != NULL) {
        cout << "Case ID: " << temp->caseId << "\n Name: " << temp->name << "\n Crime: " << temp->crimeType
             << "\n Age: " << temp->age << "\n Date: " << temp->date << "\n Sex: " << temp->sex
             << "\n History: " << temp->crimeHistory << "\n\n";
        temp = temp->next;
    }
}

void deleteCase(int id) {
    if (!isAdminLoggedIn) {
        cout << "You must be logged in as admin to delete cases.\n";
        return;
    }
    CriminalCase* temp = start_ptr;
    CriminalCase* prev = NULL;
    while (temp != NULL&& temp->caseId != id) {
        prev = temp;
        temp = temp->next;
    }
    if (temp == NULL) {
        cout << "Case ID not found.\n";
        return;
    }
    if (prev == NULL) start_ptr = temp->next;
    else prev->next = temp->next;
    delete temp;
    cout << "Case deleted successfully!\n";
}

void updateCase(int id) {
    if (!isAdminLoggedIn) {
        cout << "You must be logged in as admin to update cases.\n";
        return;
    }
    CriminalCase* temp = start_ptr;
    while (temp != NULL) {
        if (temp->caseId == id) {
            cout << "Enter new Full Name (First Middle Last): ";
            getline(cin, temp->name);
            cout << "Enter new crime type: ";
            getline(cin, temp->crimeType);
            temp->age = getPositiveInt("Enter new age (>18): ", 19);
           // temp->date = getValidDate();
            cout << "Enter new sex: ";
            cin >> temp->sex;
            cin.ignore();
            cout << "Enter new crime history: ";
            getline(cin, temp->crimeHistory);
            cout << "Case updated successfully!\n";
            return;
        }
        temp = temp->next;
    }
    cout << "Case ID not found.\n";
}

void searchCase() {
    int searchChoice;
    cout << "Search by:\n1. Case ID\n2. Name\nEnter choice: ";
    cin >> searchChoice;

    if (searchChoice == 1) {
        int id;
        cout << "Enter ID to search: ";
        cin >> id;
        CriminalCase* temp = start_ptr;
        while (temp != NULL) {
            if (temp->caseId == id) {
                cout << "Case found:\n";
                cout << "Case ID: " << temp->caseId << "\n Name: " << temp->name << "\n Crime: " << temp->crimeType
                     << "\n Age: " << temp->age << "\n Date: " << temp->date << "\n Sex: " << temp->sex
                     << "\n History: " << temp->crimeHistory << "\n";
                return;
            }
            temp = temp->next;
        }
        cout << "Case ID not found!\n";
    } else if (searchChoice == 2) {
        string name;
        cin.ignore();
        cout << "Enter full name to search: ";
        getline(cin, name);
        CriminalCase* temp = start_ptr;
        while (temp != NULL) {
            if (temp->name == name) {
                cout << "Case found:\n";
                cout << "Case ID: " << temp->caseId << "\n Name: " << temp->name << "\n Crime: " << temp->crimeType
                     << "\n Age: " << temp->age << "\n Date: " << temp->date << "\n Sex: " << temp->sex
                     << "\n History: " << temp->crimeHistory << "\n";
                return;
            }
            temp = temp->next;
        }
        cout << "Name not found!\n";
    } else {
        cout << "Invalid search choice!\n";
    }
}

void adminLogin() {
    const string ADMIN_USERNAME = "crime";
    const string ADMIN_PASSWORD = "pass123";

    string username, password;
    cout << "Enter admin username: ";
    cin >> username;
    cout << "Enter admin password: ";
    cin >> password;

if (username == ADMIN_USERNAME && password == ADMIN_PASSWORD) {
        isAdminLoggedIn = true;
        cout << "Admin login successful!\n";
    } else {
        cout << "Invalid username or password.\n";
    }
}

void adminLogout() {
    if (isAdminLoggedIn) {
        isAdminLoggedIn = false;
        cout << "Admin logged out.\n";
    } else {
        cout << "No admin currently logged in.\n";
    }
}

int main() {
    int choice, id, age;
    string fullName, crime, sex, date, history;

    do{
        cout << "\nCrime Management System\n";
        cout << "Admin status: " << (isAdminLoggedIn ? "Logged in" : "Not logged in") << "\n";
        cout << "1. Admin Login\n";
        cout << "2. Admin Logout\n";
        cout << "3. Add Case (Admin Only)\n";
        cout << "4. Display Cases\n";
        cout << "5. Delete Case (Admin Only)\n";
        cout << "6. Update Case (Admin Only)\n";
        cout << "7. Search Case\n";
        cout << "8. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                adminLogin();
                break;
            case 2:
                adminLogout();
                break;
            case 3:
                if (!isAdminLoggedIn) {
                    cout << "You must login as admin first.\n";
                    break;
                }
                id = getPositiveInt("Enter Case ID: ");
                cout << "Enter Full Name (First Middle Last): ";
                cin.ignore();
                getline(cin, fullName);
                cout << "Enter Crime: ";
                getline(cin, crime);
                age = getPositiveInt("Enter Age (>18): ", 19);
               // date = getValidDate();
                cout << "Enter Sex: ";
                cin >> sex;
                cin.ignore();
                cout << "Enter History: ";
                getline(cin, history);
                addCase(id, fullName, crime, age, date, sex, history);
                break;
            case 4:
                displayCases();
                break;
            case 5:
                if (!isAdminLoggedIn) {
                    cout << "You must login as admin first.\n";
                    break;
                }
                id = getPositiveInt("Enter ID to delete: ");
                deleteCase(id);
                break;
            case 6:
                if (!isAdminLoggedIn) {
                    cout << "You must login as admin first.\n";
                    break;
                }
                id = getPositiveInt("Enter ID to update: ");
                cin.ignore();
                updateCase(id);
                break;
            case 7:
                searchCase();
                break;
            case 8:
                cout << "Exiting...\n";
                break;
            default:
                cout << "Invalid choice. Try again.\n";
        }
    }while(choice!=8);
    return 0;
}
