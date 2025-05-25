#include <iostream>
#include <string>
#include <iomanip>

using namespace std;

string room[100][6];
int total_room_admin = 5;
int customer_number;
string room_booked_by[100];
int room_days[100];
string Customer_username[100];
string Customer_password[100];
string admin_username = "Admin", admin_password = "Admin";
string current_user = "";

// Initialize rooms
void Room_initialize() {
    room[0][0] = "Serial";
    room[0][1] = "Room Type";
    room[0][2] = "Floor No.";
    room[0][3] = "Room No.";
    room[0][4] = "Charges";
    room[0][5] = "Status";

    room[1][0] = "1001"; room[1][1] = "Single"; room[1][2] = "1"; room[1][3] = "101"; room[1][4] = "2000"; room[1][5] = "";
    room[2][0] = "1002"; room[2][1] = "Double"; room[2][2] = "2"; room[2][3] = "207"; room[2][4] = "3500"; room[2][5] = "";
    room[3][0] = "1003"; room[3][1] = "Deluxe"; room[3][2] = "3"; room[3][3] = "312"; room[3][4] = "5000"; room[3][5] = "";
    room[4][0] = "1004"; room[4][1] = "Suite"; room[4][2] = "4"; room[4][3] = "409"; room[4][4] = "7000"; room[4][5] = "";
}

// Initialize customer credentials
void Customer_initialize() {
    Customer_username[0] = "customer";
    Customer_password[0] = "customer";
    Customer_username[1] = "customer1";
    Customer_password[1] = "customer1";
    customer_number = 2;
}

// Display available rooms
void Available() {
    cout << "\nAVAILABLE ROOMS\n";
    cout << "-------------------------------------------------------------\n";
    for (int j = 0; j < 6; j++) cout << "|" << setw(12) << room[0][j];
    cout << endl << "-------------------------------------------------------------\n";
    for (int i = 1; i < total_room_admin; i++) {
        for (int j = 0; j < 6; j++) cout << "|" << setw(12) << room[i][j];
        cout << endl;
    }
    cout << "-------------------------------------------------------------\n";
}

// Admin panel
void Admin() {
    int choice;
    char repeat;
    string remove_serial;
    do {
        cout << "1. Add Room  2. Remove Room  3. Show Available\n";
        cin >> choice;
        if (choice == 1) {
            cout << "Enter room details (Serial, Type, Floor, Room No, Charges):\n";
            cin >> room[total_room_admin][0] >> room[total_room_admin][1] >> room[total_room_admin][2]
                >> room[total_room_admin][3] >> room[total_room_admin][4];
            room[total_room_admin][5] = "";
            total_room_admin++;
            Available();
        }
        else if (choice == 2) {
            cout << "Enter Serial to remove: ";
            cin >> remove_serial;
            bool found = false;
            for (int i = 0; i < total_room_admin; i++) {
                if (room[i][0] == remove_serial) {
                    found = true;
                    if (room_booked_by[i] == "") {
                        room[i][1] = "Romoved";
                        room[i][2] = "Romoved";
                        room[i][3] = "Romoved";
                        room[i][4] = "Romoved";
                        room[i][5] = "Romoved";
                        cout << "Room removed.\n";
                        break;
                    }
                    else {
                        cout << "Room is already Booked.\n";
                    }
                }
            }
            if (!found) cout << "Room not found.\n";
        }
        else if (choice == 3) {
            Available();
        }
        cout << "Repeat? (Y/N): ";
        cin >> repeat;
    } while (repeat == 'y' || repeat == 'Y');
}

// Customer login
void CustomerLogin() {
    string username, password;
    cout << "Enter Username: ";
    cin >> username;
    cout << "Enter Password: ";
    cin >> password;

    for (int i = 0; i < customer_number; i++) {
        if (Customer_username[i] == username && Customer_password[i] == password) {
            current_user = username;
            cout << "\nAccess Granted\n";
            return;
        }
    }
    current_user = "";
    cout << "\nAccess Denied\n";
}

// Book a room
void BookRoom() {
    Available();
    string serial;
    cout << "Enter Serial to Book: ";
    cin >> serial;

    for (int i = 1; i < total_room_admin; i++) {
        if (room[i][0] == serial && room_booked_by[i] == "") {
            int days;
            cout << "How many days?: ";
            cin >> days;
            room_booked_by[i] = current_user;
            room_days[i] = days;
            room[i][5] = "Booked";
            cout << "Room booked for " << days << " days.\n";
            return;
        }
        else if (room[i][0] == serial) {
            cout << "Room already booked.\n";
            return;
        }
    }
    cout << "Room not found.\n";
}

// Generate bill
void GenerateBill() {
    for (int i = 1; i < total_room_admin; i++) {
        if (room_booked_by[i] == current_user) {
            int rate = stoi(room[i][4]);
            int total = rate * room_days[i];
            cout << "\nBILL SUMMARY:\n";
            cout << "Room No: " << room[i][3] << "\nType: " << room[i][1]
                << "\nDays: " << room_days[i] << "\nTotal: " << total << endl;
            return;
        }
    }
    cout << "No booking found.\n";
}

// Cancel booking
void CancelBooking() {
    string serial;
    cout << "Enter Serial to cancel: ";
    cin >> serial;
    for (int i = 1; i < total_room_admin; i++) {
        if (room[i][0] == serial && room_booked_by[i] == current_user) {
            room_booked_by[i] = "";
            room_days[i] = 0;
            room[i][5] = "";
            cout << "Booking cancelled.\n";
            return;
        }
    }
    cout << "No such booking under your name.\n";
}

void Menu() {
    char again;
    do {
        int option;
        cout << "\n1. Available Rooms\n2. Book Room\n3. Cancel Booking\n4. Generate Bill\n";
        cin >> option;
        if (option == 1) Available();
        else if (option == 2) BookRoom();
        else if (option == 3) CancelBooking();
        else if (option == 4) GenerateBill();
        else cout << "Invalid\n";
        cout << "Continue? (Y/N): ";
        cin >> again;
    } while (again == 'y' || again == 'Y');
}

// Main driver
int main() {
    Room_initialize();
    Customer_initialize();
    char choice;
    do {
        int type;
        cout << "\n1. Customer Login  2. Admin Login\n";
        cin >> type;

        if (type == 1) {
            CustomerLogin();
            if (!current_user.empty())
            {
                Menu();
            }
        }
        else if (type == 2) {
            string user, pass;
            cout << "Admin Username: "; cin >> user;
            cout << "Admin Password: "; cin >> pass;
            if (user == admin_username && pass == admin_password)
            {
                Admin();
            }
            else {
                cout << "Invalid admin credentials.\n";
            }
        }
        else {
            cout << "Invalid option\n";
        }

        cout << "\nDo you want to return to main menu? (Y/N): ";
        cin >> choice;
    } while (choice == 'y' || choice == 'Y');

    return 0;
}
