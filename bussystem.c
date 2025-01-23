#include <stdio.h>
#include <string.h>
#define MAX_SEATS 40
//#define FILENAME "bus.txt"
typedef struct {
    int seatNumber;
    char passengerName[100];
    int isBooked;
} Seat;
Seat bus[MAX_SEATS];
// Function to initialize the bus seats
void initializeBus() {
    FILE *file = fopen("bus.txt", "r");
    if (file == NULL) {
        // If the file doesn't exist, initialize all seats as empty
        for (int i = 0; i < MAX_SEATS; i++) {
            bus[i].seatNumber = i + 1;
            bus[i].isBooked = 0;
            strcpy(bus[i].passengerName, "");
        }
    } else {
        // If the file exists, read the seat information from the file
        for (int i = 0; i < MAX_SEATS; i++) {
            //if (fscanf(file, "%d %d %[^\n]", &bus[i].seatNumber, &bus[i].isBooked, bus[i].passengerName) != 3)
            {
                fscanf(file,"%d %d %%[^\n]", &bus[i].seatNumber, &bus[i].isBooked, bus[i].passengerName);
                // Handle case where fscanf does not read expected values
                bus[i].seatNumber = i + 1;
                bus[i].isBooked = 0;
                strcpy(bus[i].passengerName, "");
            }
        }
        fclose(file);
    }
}


// Function to save the current seat information to the file
void saveBus() {
    FILE *file = fopen("write.txt", "w");
    for (int i = 0; i < MAX_SEATS; i++)
    {
        fprintf(file,"%d %d %s\n", bus[i].seatNumber, bus[i].isBooked, bus[i].passengerName);
    }
    fclose(file);
}

// Function to view available seats
void viewAvailableSeats() {
    printf("Available Seats:\n");
    for (int i = 0; i < MAX_SEATS; i++) {
        if (!bus[i].isBooked) {
            printf("Seat %d\n", bus[i].seatNumber);
        }
    }
}

// Function to book a ticket
void bookTicket() {
    int seatNumber;
    char name[100];

    printf("Enter seat number to book: ");
    scanf("%d", &seatNumber);
    if (seatNumber < 1 || seatNumber > MAX_SEATS) {
        printf("Invalid seat number!\n");
        return;
    }

    if (bus[seatNumber - 1].isBooked) {
        printf("Seat already booked!\n");
        return;
    }

    printf("Enter passenger name: ");
    scanf("%s", name);
    bus[seatNumber - 1].isBooked = 1;
    strcpy(bus[seatNumber - 1].passengerName, name);
    printf("Ticket booked for %s at seat %d\n", name, seatNumber);

    // Save the updated seat information to the file
    saveBus();
}

// Function to cancel a ticket
void cancelTicket() {
    int seatNumber;
    printf("Enter seat number to cancel: ");
    scanf("%d", &seatNumber);

    if (seatNumber < 1 || seatNumber > MAX_SEATS) {
        printf("Invalid seat number!\n");
        return;
    }

    if (!bus[seatNumber - 1].isBooked) {
        printf("Seat is not booked!\n");
        return;
    }

    bus[seatNumber - 1].isBooked = 0;
    strcpy(bus[seatNumber - 1].passengerName, "");
    printf("Ticket for seat %d canceled\n", seatNumber);

    // Save the updated seat information to the file
    saveBus();
}

// Function to view booked tickets
void viewBookedTickets() {
    printf("Booked Tickets:\n");
    for (int i = 0; i < MAX_SEATS; i++) {
        if (bus[i].isBooked) {
            printf("Seat %d: %s\n", bus[i].seatNumber, bus[i].passengerName);
        }
    }
}

int main() {
    int choice;
    initializeBus();

    while (1) {
        printf("\nBus Ticket Reservation System\n");
        printf("1. View Available Seats\n");
        printf("2. Book a Ticket\n");
        printf("3. Cancel a Ticket\n");
        printf("4. View Booked Tickets\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                viewAvailableSeats();
                break;
            case 2:
                bookTicket();
                break;
            case 3:
                cancelTicket();
                break;
            case 4:
                viewBookedTickets();
                break;
            case 5:
                return 0;
            default:
                printf("Invalid choice! Please try again.\n");
        }
    }
}

