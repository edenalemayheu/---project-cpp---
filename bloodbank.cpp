#include <iostream>
#include <iomanip>
#include <fstream>   // for file management
using namespace std;

int main() {
    int choice1, choice2, choice3, i;
    const int MAX = 100;

    // Donor data
    string name_donor[MAX], blood_type[MAX], phone_donor[MAX];
    int age_donor[MAX], id_donor[MAX];
    int donors = 0;

    // Admin password
    int pass;

    // Volunteer data
    string name_volunteer[MAX], phone_volunteer[MAX];
    int volunteer = 0;
    int id_volunteer[MAX];

    // For Compatibility
    int compatible = 0;
    string recipent;

    bool running = true;   // control program loop

    while (running) {
        system("cls");
        cout << "\n========== BLOOD BANK MANAGEMENT SYSTEM ==========\n";
        cout << "1) User" << endl;
        cout << "2) Admin" << endl;
        cout << "3) Exit" << endl;
        cout << "Choice: ";
        cin >> choice1;

        switch (choice1) {
        case 1: {
            cout << "\n===== USER MENU =====\n";
            cout << " Register as:\n 1) Donor \n 2) Volunteer \n";
            cin >> choice2;

            if (choice2 == 1) {
                if (donors >= MAX) {
                    cout << "Donor limit reached.\n";
                    break;
                }
                cout << "\nDonor page!!\n";
                cout << "Enter your name: ";
                cin >> name_donor[donors];
                cout << "Enter your age: ";
                cin >> age_donor[donors];

                int valid;
                do {
                    valid = 0;
                    cout << "Enter blood group (A+, A-, B+, B-, O+, O-, AB+, AB-): ";
                    cin >> blood_type[donors];
                    for (char &c : blood_type[donors]) c = toupper(c);
                    if (blood_type[donors] == "A+" || blood_type[donors] == "A-" ||
                        blood_type[donors] == "B+" || blood_type[donors] == "B-" ||
                        blood_type[donors] == "O+" || blood_type[donors] == "O-" ||
                        blood_type[donors] == "AB+" || blood_type[donors] == "AB-") {
                        valid = 1;
                    } else cout << "Invalid blood group! Try again.\n";
                } while (valid == 0);

phone:
                cout << "Enter your phone:+251 ";
                cin >> phone_donor[donors];
                if (phone_donor[donors].length() != 9) {
                    cout << "Invalid phone number! Try again\n";
                    goto phone;
                }

                if (age_donor[donors] > 18 && age_donor[donors] < 60) {
                    id_donor[donors] = 1000 + donors + 1;
                    cout << "Id: " << id_donor[donors];
                    donors++;
                    cout << "\nRegistered successfully!\n";

                    // Save donor to file
                    ofstream fout("bloodbank.txt", ios::app);
                    fout << "DONOR | ID:" << id_donor[donors-1]
                         << " | Name:" << name_donor[donors-1]
                         << " | Age:" << age_donor[donors-1]
                         << " | Blood:" << blood_type[donors-1]
                         << " | Phone:+251" << phone_donor[donors-1]
                         << endl;
                    fout.close();

                } else if (age_donor[donors] <= 18) {
                    cout << "Not eligible to donate yet. Consider volunteering.\n";
                } else {
                    cout << "Not eligible for donating, thank you for approaching us.\n";
                }
            }
            else if (choice2 == 2) {
                cout << "Enter your name: ";
                cin >> name_volunteer[volunteer];
phone2:
                cout << "Enter your phone:+251 9";
                cin >> phone_volunteer[volunteer];
                if (phone_volunteer[volunteer].length() != 8) {
                    cout << "Invalid phone number! Try again\n";
                    goto phone2;
                }
                cout << "Successfully registered!!\n";
                id_volunteer[volunteer] = 15000 + volunteer + 1;
                cout << "Your volunteer ID is: " << id_volunteer[volunteer] << endl;
                volunteer++;

                // Save volunteer to file
                ofstream fout("bloodbank.txt", ios::app);
                fout << "VOLUNTEER | ID:" << id_volunteer[volunteer-1]
                     << " | Name:" << name_volunteer[volunteer-1]
                     << " | Phone:+2519" << phone_volunteer[volunteer-1]
                     << endl;
                fout.close();
            }
            else {
                cout << "Invalid input!\n";
            }
            break;
        }
        case 2: {
            cout << "Enter Admin password: ";
            cin >> pass;
            if (pass == 1234) {
                cout << "Access granted\n";
                cout << "======= ADMIN MENU =======";
                cout << "\n 1) Emergency (blood request)";
                cout << "\n 2) View all donors";
                cout << "\n 3) View all volunteers \n";
                cout << "Enter choice: ";
                cin >> choice3;

                switch (choice3) {
                case 1: {
                    int valid;
                    do {
                        valid = 0;
                        cout << "Enter recipient blood group: ";
                        cin >> recipent;
                        for (char &c : recipent) c = toupper(c);
                        if (recipent == "A+" || recipent == "A-" ||
                            recipent == "B+" || recipent == "B-" ||
                            recipent == "O+" || recipent == "O-" ||
                            recipent == "AB+" || recipent == "AB-") {
                            valid = 1;
                        } else cout << "Invalid blood group! Try again.\n";
                    } while (valid == 0);

                    for (int i = 0; i < donors; i++) {
                        if (blood_type[i] == recipent) compatible = 1;
                        else if (blood_type[i] == "O-") compatible = 1;
                        else if (recipent == "AB+") compatible = 1;

                        if (compatible == 1) {
                            cout << "Compatible donor found\n";
                            cout << i << "." << id_donor[i] << ":" << name_donor[i]
                                 << "(" << blood_type[i] << ")"
                                 << " -phone:+251" << phone_donor[i] << endl;
                            compatible = 1;
                        }
                    }
                    if (compatible == 0)
                        cout << "\nNo compatible donor found.\n";
                    break;
                }
                case 2: {
                    cout << "\nID" << setw(13) << "Name" << setw(13) << "Age"
                         << setw(13) << "Blood type" << setw(13) << "Phone\n";
                    for (int i = 0; i < donors; i++) {
                        cout << id_donor[i] << setw(13) << name_donor[i]
                             << setw(13) << age_donor[i] << setw(13) << blood_type[i]
                             << setw(13) << "+251" << phone_donor[i] << endl;
                    }
                    break;
                }
                case 3: {
                    cout << "Name" << setw(13) << "Phone\n";
                    for (i = 0; i < volunteer; i++) {
                        cout << name_volunteer[i] << setw(13) << "09" << phone_volunteer[i] << endl;
                    }
                    break;
                }
                default:
                    cout << "Invalid input!!\n";
                }
            } else cout << "Wrong password!!\n";
            break;
        }
        case 3: {
            cout << "Thank you for using the system.\n";
            running = false;   // exit loop
            break;
        }
        default:
            cout << "Invalid choice!!\n";
        }
        if (running) system("pause");
    }

    return 0;
}
