#include <stdio.h>
#include <string.h>
#define MAX_SEATS 40
typedef struct 
{
    int seatNumber;
    char passengerName[100];
    int isBooked;
} Seat;
Seat bus[MAX_SEATS];
// Function to initialize the bus seats
//Tanjimul Hassan
void initializeBus() 
{
    FILE *file = fopen("bus.txt", "r");
    if (file == NULL) 
    {
        for (int i = 0; i < MAX_SEATS; i++) 
        {
            bus[i].seatNumber = i + 1;
            bus[i].isBooked = 0;
            strcpy(bus[i].passengerName, "");
        }
    } 
    else 
    {
        for (int i = 0; i < MAX_SEATS; i++) 
        {
            {
                fscanf(file,"%d %d %[^\n]", &bus[i].seatNumber, &bus[i].isBooked, bus[i].passengerName);
                bus[i].seatNumber = i + 1;
                bus[i].isBooked = 0;
                strcpy(bus[i].passengerName, "");
            }
        }
        fclose(file);
    }
}
//Labib(part-1)
void saveBus() 
{
    FILE *file = fopen("write.txt", "w");
    for (int i = 0; i < MAX_SEATS; i++)
    {
        fprintf(file,"%d %d %s\n", bus[i].seatNumber, bus[i].isBooked, bus[i].passengerName);
    }
    fclose(file);
}
void viewAvailableSeats() 
{
    printf("Available Seats:\n");
    for (int i = 0; i < MAX_SEATS; i++) 
    {
        if (!bus[i].isBooked) 
        {
            printf("Seat %d\n", bus[i].seatNumber);
        }
    }
}
//Rafiz
void bookTicket() 
{
    int seatNumber;
    char name[100];
    printf("Enter seat number to book: ");
    scanf("%d", &seatNumber);
    getchar();
    if (seatNumber < 1 || seatNumber > MAX_SEATS) 
    {
        printf("Invalid seat number!\n");
        return;
    }
    if (bus[seatNumber - 1].isBooked) 
    {
        printf("Seat already booked!\n");
        return;
    }
    printf("Enter passenger name: ");
    fgets(name, sizeof(name), stdin);  // Use fgets instead of scanf for strings
    // Remove the newline character at the end of the name 
    name[strcspn(name, "\n")] = '\0';
    bus[seatNumber - 1].isBooked = 1;
    strcpy(bus[seatNumber - 1].passengerName, name);
    printf("Ticket booked for %s at seat %d\n", name, seatNumber);
    // Save the updated seat information to the file
    saveBus();
}
//Yafid
void cancelTicket() 
{
    int seatNumber;
    printf("Enter seat number to cancel: ");
    scanf("%d", &seatNumber);
    if (seatNumber < 1 || seatNumber > MAX_SEATS) 
    {
        printf("Invalid seat number!\n");
        return;
    }
    if (!bus[seatNumber - 1].isBooked) 
    {
        printf("Seat is not booked!\n");
        return;
    }
    bus[seatNumber - 1].isBooked = 0;
    strcpy(bus[seatNumber - 1].passengerName, "");
    printf("Ticket for seat %d canceled\n", seatNumber);
    // Save the updated seat information to the file
    saveBus();
}
//Labib(part-2)
void viewBookedTickets() {
    printf("Booked Tickets:\n");
    for (int i = 0; i < MAX_SEATS; i++) 
    {
        if (bus[i].isBooked) {
            printf("Seat %d: %s\n", bus[i].seatNumber, bus[i].passengerName);
        }
    }
}
//Sayed
int main() 
{
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
