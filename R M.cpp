#include <stdio.h>
#include <stdlib.h>

/* ===== FUNCTION DECLARATIONS ===== */
void menu();
void viewTrains();
void bookTicket();
void viewTickets();
void cancelTicket();
int generateTicket();

/* ===== TICKET NUMBER FUNCTION ===== */
int generateTicket()
{
    static int ticket = 1000;   // ticket starts from 1000
    return ticket++;
}

/* ===== MAIN FUNCTION ===== */
int main()
{
    int choice;

    do
    {
        menu();
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            viewTrains();
            break;

        case 2:
            bookTicket();
            break;

        case 3:
            viewTickets();
            break;

        case 4:
            cancelTicket();
            break;

        case 5:
            printf("Thank you! Program exited.\n");
            break;

        default:
            printf("Invalid choice! Try again.\n");
        }

    } while (choice != 5);

    return 0;
}

/* ===== MENU ===== */
void menu()
{
    printf("\n===== RAILWAY MANAGEMENT SYSTEM =====\n");
    printf("1. View Trains\n");
    printf("2. Book Ticket\n");
    printf("3. View Booked Tickets\n");
    printf("4. Cancel Ticket\n");
    printf("5. Exit\n");
}

/* ===== VIEW TRAINS ===== */
void viewTrains()
{
    printf("\n--- AVAILABLE TRAINS ---\n");
    printf("101  Green Line   Karachi -> Islamabad\n");
    printf("102  Pak Express  Lahore  -> Karachi\n");
    printf("103  Jinnah Exp   Rawalpindi -> Karachi\n");
}

/* ===== BOOK TICKET ===== */
void bookTicket()
{
    FILE *fp;
    char name[30];
    int trainNo;
    int ticketNo;

    fp = fopen("tickets.txt", "a");

    if (fp == NULL)
    {
        printf("File error!\n");
        return;
    }

    ticketNo = generateTicket();

    printf("Enter passenger name: ");
    scanf("%s", name);

    printf("Enter train number: ");
    scanf("%d", &trainNo);

    fprintf(fp, "%d %s %d\n", ticketNo, name, trainNo);
    fclose(fp);

    printf("\nTicket Booked Successfully!\n");
    printf("Ticket No: %d\n", ticketNo);
}

/* ===== VIEW BOOKED TICKETS ===== */
void viewTickets()
{
    FILE *fp;
    int ticketNo, trainNo;
    char name[30];

    fp = fopen("tickets.txt", "r");

    if (fp == NULL)
    {
        printf("No tickets found.\n");
        return;
    }

    printf("\n--- BOOKED TICKETS ---\n");

    while (fscanf(fp, "%d %s %d", &ticketNo, name, &trainNo) != EOF)
    {
        printf("Ticket No: %d | Name: %s | Train No: %d\n",
               ticketNo, name, trainNo);
    }

    fclose(fp);
}

/* ===== CANCEL TICKET ===== */
void cancelTicket()
{
    FILE *fp, *temp;
    int search, ticketNo, trainNo;
    char name[30];
    int found = 0;

    fp = fopen("tickets.txt", "r");
    temp = fopen("temp.txt", "w");

    if (fp == NULL)
    {
        printf("No tickets to cancel.\n");
        return;
    }

    printf("Enter ticket number to cancel: ");
    scanf("%d", &search);

    while (fscanf(fp, "%d %s %d", &ticketNo, name, &trainNo) != EOF)
    {
        if (ticketNo == search)
        {
            found = 1;
            printf("Ticket cancelled successfully.\n");
        }
        else
        {
            fprintf(temp, "%d %s %d\n", ticketNo, name, trainNo);
        }
    }

    fclose(fp);
    fclose(temp);

    remove("tickets.txt");
    rename("temp.txt", "tickets.txt");

    if (!found)
        printf("Ticket not found.\n");
}

