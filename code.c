#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ROWS 10
#define MAX_COLS 6

typedef struct Passenger {
    int id;
    char name[50];
    char contact[15];
    int seatRow;
    int seatCol;
    char source[50];
    char destination[50];
    struct Passenger* next;
} Passenger;

typedef struct Flight {
    int flightNo;
    char flightName[50];
    char source[50];
    char destination[50];
    int totalSeats;
    int availableSeats;
    char seats[MAX_ROWS][MAX_COLS];
    Passenger* passengerList;
    struct Flight* left, * right;
} Flight;

Flight* addFlight(Flight* root, int flightNo, char* flightName, char* source, char* destination, int totalSeats);
Flight* removeFlight(Flight* root, int flightNo);
Flight* modifyFlight(Flight* root, int flightNo);
Flight* searchFlight(Flight* root, int flightNo);
Flight* searchFlightsBySourceAndDestination(Flight* root, char* source, char* destination);
void addPassenger(Flight* flight, int id, char* name, char* contact, char* source, char* destination, char seatType);
void cancelPassenger(Flight* flight, int id);
void initializeSeats(char seats[MAX_ROWS][MAX_COLS]);
void displaySeats(Flight* flight);
void displayFlights(Flight* root);
void displayPassengers(Flight* flight);
int generatePassengerID();
void displayPassengerTicket(Passenger* passenger);

Flight* findMin(Flight* root);

int main() {
    Flight* root = NULL;
    int choice, userType, flightNo, totalSeats, id;
    char flightName[50], source[50], destination[50], name[50], contact[15], seatType;

    while (1) {
        printf("\n--- Airline Management System ---\n");
        printf("1. Admin Login\n");
        printf("2. Passenger Login\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &userType);

        if (userType == 1) {
            printf("\n--- Admin Menu ---\n");
            printf("1. Add Flight\n");
            printf("2. Remove Flight\n");
            printf("3. Modify Flight\n");
            printf("4. Back to Main Menu\n");
            printf("Enter your choice: ");
            scanf("%d", &choice);

            switch (choice) {
                case 1:
                    printf("Enter Flight Number: ");
                    scanf("%d", &flightNo);
                    printf("Enter Flight Name: ");
                    scanf("%s", flightName);
                    printf("Enter Source: ");
                    scanf("%s", source);
                    printf("Enter Destination: ");
                    scanf("%s", destination);
                    printf("Enter Total Seats (Max %d): ", MAX_ROWS * MAX_COLS);
                    scanf("%d", &totalSeats);
                    root = addFlight(root, flightNo, flightName, source, destination, totalSeats);
                    break;

                case 2:
                    printf("Enter Flight Number to Remove: ");
                    scanf("%d", &flightNo);
                    root = removeFlight(root, flightNo);
                    break;

                case 3:
                    printf("Enter Flight Number to Modify: ");
                    scanf("%d", &flightNo);
                    root = modifyFlight(root, flightNo);
                    break;

                case 4:
                    continue;

                default:
                    printf("Invalid choice. Try again.\n");
            }
        } else if (userType == 2) {
            printf("\n--- Passenger Menu ---\n");
            printf("1. Search Flight by Source and Destination\n");
            printf("2. Book Ticket\n");
            printf("3. Cancel Ticket\n");
            printf("4. View All Flights\n");
            printf("5. View My Ticket\n");
            printf("6. Back to Main Menu\n");
            printf("Enter your choice: ");
            scanf("%d", &choice);

            switch (choice) {
                case 1:
                    printf("Enter Source: ");
                    scanf("%s", source);
                    printf("Enter Destination: ");
                    scanf("%s", destination);
                    printf("Enter Flight Number: ");
                    scanf("%d", &flightNo);
                    Flight* flight = searchFlight(root, flightNo);
                    if (flight) {
                        printf("\nSeat Availability for Flight %d (%s):\n", flightNo, flight->flightName);
                        displaySeats(flight);
                    }
                    break;

                case 2:
                    printf("Enter Source: ");
                    scanf("%s", source);
                    printf("Enter Destination: ");
                    scanf("%s", destination);
                    printf("Enter Flight Number for Booking: ");
                    scanf("%d", &flightNo);
                    flight = searchFlight(root, flightNo);
                    if (flight) {
                        printf("Enter Passenger Name: ");
                        scanf("%s", name);
                        printf("Enter Contact Number: ");
                        scanf("%s", contact);
                        printf("Choose Seat Type (W for Window, N for Non-window): ");
                        scanf(" %c", &seatType);
                        addPassenger(flight, generatePassengerID(), name, contact, source, destination, seatType);
                    } else {
                        printf("Flight not found.\n");
                    }
                    break;

                case 3:
                    printf("Enter Flight Number for Cancellation: ");
                    scanf("%d", &flightNo);
                    flight = searchFlight(root, flightNo);
                    if (flight) {
                        printf("Enter Passenger ID for Cancellation: ");
                        scanf("%d", &id);
                        cancelPassenger(flight, id);
                    } else {
                        printf("Flight not found.\n");
                    }
                    break;

                case 4:
                    displayFlights(root);
                    break;

                case 5:
                    printf("Enter your Passenger ID to view your ticket: ");
                    scanf("%d", &id);
                    Passenger* passenger = NULL;
                    for (Flight* f = root; f != NULL; f = (f->left != NULL) ? f->left : f->right) {
                        passenger = f->passengerList;
                        while (passenger) {
                            if (passenger->id == id) {
                                displayPassengerTicket(passenger);
                                break;
                            }
                            passenger = passenger->next;
                        }
                    }
                    break;

                case 6:
                    continue;

                default:
                    printf("Invalid choice. Try again.\n");
            }
        } else if (userType == 3) {
            printf("Exiting...\n");
            break;
        } else {
            printf("Invalid choice. Try again.\n");
        }
    }
    return 0;
}

void initializeSeats(char seats[MAX_ROWS][MAX_COLS]) {
    for (int i = 0; i < MAX_ROWS; i++) {
        for (int j = 0; j < MAX_COLS; j++) {
            if (j == 0 || j == MAX_COLS - 1) {
                seats[i][j] = 'W';
            } else {
                seats[i][j] = 'N';
            }
        }
    }
}

Flight* addFlight(Flight* root, int flightNo, char* flightName, char* source, char* destination, int totalSeats) {
    if (root == NULL) {
        Flight* newFlight = (Flight*)malloc(sizeof(Flight));
        newFlight->flightNo = flightNo;
        strcpy(newFlight->flightName, flightName);
        strcpy(newFlight->source, source);
        strcpy(newFlight->destination, destination);
        newFlight->totalSeats = totalSeats;
        newFlight->availableSeats = totalSeats;
        initializeSeats(newFlight->seats);
        newFlight->passengerList = NULL;
        newFlight->left = newFlight->right = NULL;
        printf("Flight %d (%s) from %s to %s added successfully.\n", flightNo, flightName, source, destination);
        return newFlight;
    }
    if (flightNo < root->flightNo) {
        root->left = addFlight(root->left, flightNo, flightName, source, destination, totalSeats);
    } else if (flightNo > root->flightNo) {
        root->right = addFlight(root->right, flightNo, flightName, source, destination, totalSeats);
    } else {
        printf("Flight with this number already exists.\n");
    }
    return root;
}

Flight* removeFlight(Flight* root, int flightNo) {
    if (root == NULL) {
        printf("Flight not found.\n");
        return root;
    }

    if (flightNo < root->flightNo) {
        root->left = removeFlight(root->left, flightNo);
    } else if (flightNo > root->flightNo) {
        root->right = removeFlight(root->right, flightNo);
    } else {
        if (root->left == NULL) {
            Flight* temp = root->right;
            free(root);
            return temp;
        } else if (root->right == NULL) {
            Flight* temp = root->left;
            free(root);
            return temp;
        }

        Flight* temp = findMin(root->right);
        root->flightNo = temp->flightNo;
        root->right = removeFlight(root->right, temp->flightNo);
    }
    return root;
}

Flight* modifyFlight(Flight* root, int flightNo) {
    Flight* flight = searchFlight(root, flightNo);
    if (flight != NULL) {
        printf("Modify flight details for Flight %d (%s)\n", flightNo, flight->flightName);
        printf("Enter new Flight Name: ");
        scanf("%s", flight->flightName);
        printf("Enter new Source: ");
        scanf("%s", flight->source);
        printf("Enter new Destination: ");
        scanf("%s", flight->destination);
        return flight;
    }
    printf("Flight not found.\n");
    return NULL;
}

Flight* searchFlight(Flight* root, int flightNo) {
    if (root == NULL || root->flightNo == flightNo) {
        return root;
    }
    if (flightNo < root->flightNo) {
        return searchFlight(root->left, flightNo);
    } else {
        return searchFlight(root->right, flightNo);
    }
}

void displaySeats(Flight* flight) {
    for (int i = 0; i < MAX_ROWS; i++) {
        for (int j = 0; j < MAX_COLS; j++) {
            printf("[%c] ", flight->seats[i][j]);
        }
        printf("\n");
    }
}

void displayFlights(Flight* root) {
    if (root == NULL) {
        return;
    }
    displayFlights(root->left);
    printf("Flight %d (%s) from %s to %s, Available Seats: %d\n", root->flightNo, root->flightName, root->source, root->destination, root->availableSeats);
    displayFlights(root->right);
}

void addPassenger(Flight* flight, int id, char* name, char* contact, char* source, char* destination, char seatType) {
    if (flight->availableSeats > 0) {
        Passenger* newPassenger = (Passenger*)malloc(sizeof(Passenger));
        newPassenger->id = id;
        strcpy(newPassenger->name, name);
        strcpy(newPassenger->contact, contact);
        strcpy(newPassenger->source, source);
        strcpy(newPassenger->destination, destination);

        int seatFound = 0;
        for (int i = 0; i < MAX_ROWS && !seatFound; i++) {
            for (int j = 0; j < MAX_COLS && !seatFound; j++) {
                if ((seatType == 'W' && flight->seats[i][j] == 'W') || 
                    (seatType == 'N' && flight->seats[i][j] == 'N')) {
                    newPassenger->seatRow = i;
                    newPassenger->seatCol = j;
                    flight->seats[i][j] = 'B';  // B for Booked
                    flight->availableSeats--;
                    seatFound = 1;
                }
            }
        }

        if (seatFound) {
            newPassenger->next = flight->passengerList;
            flight->passengerList = newPassenger;
            printf("Passenger %s with ID %d booked successfully!\n", name, id);
        } else {
            printf("No available seats for the selected type.\n");
        }
    } else {
        printf("No available seats.\n");
    }
}

void cancelPassenger(Flight* flight, int id) {
    Passenger* prev = NULL;
    Passenger* current = flight->passengerList;
    
    while (current != NULL) {
        if (current->id == id) {
            if (prev == NULL) {
                flight->passengerList = current->next;
            } else {
                prev->next = current->next;
            }
            
            flight->seats[current->seatRow][current->seatCol] = (current->seatCol == 0 || current->seatCol == MAX_COLS - 1) ? 'W' : 'N';
            flight->availableSeats++;
            free(current);
            printf("Passenger ID %d's ticket cancelled.\n", id);
            return;
        }
        prev = current;
        current = current->next;
    }

    printf("Passenger with ID %d not found.\n", id);
}

void displayPassengerTicket(Passenger* passenger) {
    printf("\n--- Passenger Ticket ---\n");
    printf("Passenger ID: %d\n", passenger->id);
    printf("Name: %s\n", passenger->name);
    printf("Contact: %s\n", passenger->contact);
    printf("Source: %s\n", passenger->source);
    printf("Destination: %s\n", passenger->destination);
    printf("Seat: Row %d, Column %d\n", passenger->seatRow + 1, passenger->seatCol + 1);
}

int generatePassengerID() {
    static int id = 1000;
    return id++;
}

Flight* findMin(Flight* root) {
    while (root->left != NULL) {
        root = root->left;
    }
    return root;
}