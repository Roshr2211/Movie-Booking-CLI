#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>
typedef struct {
    char name[50];
    char email[50];
    char mobile[10];
    char *row;
    int col;
    char movie_selected[50];
    int cancelled;
} Details;

typedef struct {
    char *movie_name;
    char seats[10][15][4];
} Theatre;

Details *dynamic_array = NULL;
int count = 0;

Theatre one, two, three, four, five;


void PrintMenu() {
    printf("\033[1;36m");
    printf("   ╔════════════════════════════════════════════════════════════╗\n");
    printf("   ║                                                            ║\n");
    printf("   ║                         BOOK YOUR SHOW                     ║\n");
    printf("   ║                                                            ║\n");
    printf("   ║  Please select an option from below:                       ║\n");
    printf("   ║                                                            ║\n");
    printf("   ║    (1) Enter Details                                       ║\n");
    printf("   ║    (2) Show Details                                        ║\n");
    printf("   ║    (3) Book Movies                                         ║\n");
    printf("   ║    (4) Generate Bill                                       ║\n");
    printf("   ║    (5) Cancel Booking                                      ║\n");
    printf("   ║    (6) Exit                                                ║\n");
    printf("   ║                                                            ║\n");
    printf("   ╚════════════════════════════════════════════════════════════╝\n");
    printf("   > ");
    printf("\033[0m");
}

// Function to check if the name contains only letters and spaces
int validate_name(const char *name) {
    for (int i = 0; i < strlen(name); i++) {
        if (!isalpha(name[i]) && name[i] != ' ') {
            return 0; // Invalid character
        }
    }
    return 1; // Valid name
}

// Function to validate email with basic checks (can be expanded)
int validate_email(const char *email) {
    const char *at = strchr(email, '@');
    if (at == NULL || strchr(at, '.') == NULL) {
        return 0; // Invalid email (no @ or no domain)
    }
    return 1; // Basic valid email
}

// Function to validate phone number (digits only)
int validate_phone(const char *phone) {
    for (int i = 0; i < strlen(phone); i++) {
        if (!isdigit(phone[i])) {
            return 0; // Invalid character (not a digit)
        }
    }
    return 1; // Valid phone number
}

void InputDetails() {
    Details *temp = realloc(dynamic_array, (count + 1) * sizeof(Details));
    if (temp == NULL) {
        printf("\nMemory allocation failed!\n");
        return;
    }
    dynamic_array = temp;

    char name[100], email[100], phone[20];

    // Input for Name
    printf("   >>> Enter your name: ");
    scanf(" %[^\n]", name);
    if (!validate_name(name)) {
        printf("Invalid name. Please use only letters and spaces.\n");
        return; // Exit function if validation fails
    }
    strcpy(dynamic_array[count].name, name);

    // Input for Email
    printf("   >>> Enter your email address: ");
    scanf("%s", email);
    if (!validate_email(email)) {
        printf("Invalid email.\n");
        return; // Exit function if validation fails
    }
    strcpy(dynamic_array[count].email, email);

    // Input for Phone
    printf("   >>> Enter mobile number: ");
    scanf("%s", phone);
    if (!validate_phone(phone)) {
        printf("Invalid phone number. Please enter only digits.\n");
        return; // Exit function if validation fails
    }
    strcpy(dynamic_array[count].mobile, phone);

    dynamic_array[count].cancelled = 0;
    count++;
    printf("Details successfully added!\n");
}

void ShowDetails() {
    printf("   >>> Enter first or last name: ");
    char search[50];
    scanf("%s", search);
    for (int i = 0; i < count; i++) {
        if (strstr(dynamic_array[i].name, search) != NULL) {
            printf("   Name: %s\n   Mobile: %s\n   Email: %s\n", 
                   dynamic_array[i].name, dynamic_array[i].mobile, dynamic_array[i].email);
            if (dynamic_array[i].row != NULL) {
                printf("   Movie: %s\n   Seat: %c-%d\n", 
                       dynamic_array[i].movie_selected, *(dynamic_array[i].row), dynamic_array[i].col);
                printf("   Status: %s\n", dynamic_array[i].cancelled ? "Cancelled" : "Active");
            } else {
                printf("   No booking made yet.\n");
            }
        }
    }
}

void DisplaySeats(Theatre *theatre) {
    char *empty_seat = "[ ]";
    char *booked_seat = "[X]";

    printf("\t\tRecliner $500\n");
    for (int i = 9; i > 8; i--) {
        printf("\033[38;5;250m");
        printf("\t\t%c ", 'A' + i);
        printf("\033[0m");
        for (int j = 0; j < 15; j++) {
            if (strcmp(theatre->seats[i][j], empty_seat) == 0)
                printf("\033[1;32m");
            else
                printf("\033[1;31m");
            printf("%s ", theatre->seats[i][j]);
        }
        printf("\033[0m");
        printf("\n");
    }
    printf("\t\tPrime $300\n");
    for (int i = 8; i > 5; i--) {
        printf("\033[38;5;250m");
        printf("\t\t%c ", 'A' + i);
        printf("\033[0m");
        for (int j = 0; j < 15; j++) {
            if (strcmp(theatre->seats[i][j], empty_seat) == 0)
                printf("\033[1;32m");
            else
                printf("\033[1;31m");
            printf("%s ", theatre->seats[i][j]);
        }
        printf("\033[0m");
        printf("\n");
    }
    printf("\t\tNormal $200\n");
    for (int i = 5; i >= 0; i--) {
        printf("\033[38;5;250m");
        printf("\t\t%c ", 'A' + i);
        printf("\033[0m");
        for (int j = 0; j < 15; j++) {
            if (strcmp(theatre->seats[i][j], empty_seat) == 0)
                printf("\033[1;32m");
            else
                printf("\033[1;31m");
            printf("%s ", theatre->seats[i][j]);
        }
        printf("\033[0m");
        printf("\n");
    }
    printf("\t\t   1   2   3   4   5   6   7   8   9   10  11  12  13  14  15\n\n");
}

void Book() {
    printf("   >>> Enter your first or last name: ");
    char search[50];
    scanf("%s", search);
    for (int i = 0; i < count; i++) {
        if (strstr(dynamic_array[i].name, search) != NULL) {
            printf("   Which Movie would you like to watch:\n");
            printf("   \t(1) Dune 2\n");
            printf("   \t(2) Transformers One\n");
            printf("   \t(3) Oppenheimer\n");
            printf("   \t(4) Inception\n");
            printf("   \t(5) Tenet\n");
            printf("   >>> ");
            int n;
            scanf("%d", &n);
            
            Theatre *selected_theatre;
            switch(n) {
                case 1:
                    strcpy(dynamic_array[i].movie_selected, "Dune 2");
                    selected_theatre = &one;
                    break;
                case 2:
                    strcpy(dynamic_array[i].movie_selected, "Transformers One");
                    selected_theatre = &two;
                    break;
                case 3:
                    strcpy(dynamic_array[i].movie_selected, "Oppenheimer");
                    selected_theatre = &three;
                    break;
                case 4:
                    strcpy(dynamic_array[i].movie_selected, "Inception");
                    selected_theatre = &four;
                    break;
                case 5:
                    strcpy(dynamic_array[i].movie_selected, "Tenet");
                    selected_theatre = &five;
                    break;
                default:
                    printf("Invalid choice. Booking cancelled.\n");
                    return;
            }
            
            printf("   You have chosen the movie %s\n", dynamic_array[i].movie_selected);
            printf("   Select a Seat!\n");

            DisplaySeats(selected_theatre);

            char s;
            int num;
            while (1) {
                printf("   >>> Enter the row you would like (A-J): ");
                scanf(" %c", &s);
                printf("   >>> Enter the seat number you would like (1-15): ");
                scanf("%d", &num);

                if (s < 'A' || s > 'J' || num < 1 || num > 15) {
                    printf("Invalid seat selection. Please try again.\n");
                    continue;
                }

                int temp = s - 'A';
                if (strcmp(selected_theatre->seats[temp][num - 1], "[X]") == 0) {
                    printf("This seat is already booked. Please choose another seat.\n");
                    continue;
                }
                
                strcpy(selected_theatre->seats[temp][num - 1], "[X]");
                break;
            }

            dynamic_array[i].row = malloc(sizeof(char));
            *(dynamic_array[i].row) = s;
            dynamic_array[i].col = num;
            dynamic_array[i].cancelled = 0;

            printf("Booking successful!\n");
            return;
        }
    }
    printf("User not found. Please enter your details first.\n");
}

void GenerateBill() {
    printf("   >>> Enter first or last name: ");
    char search[50];
    scanf("%s", search);
    printf("\033[0;31m");
    for (int i = 0; i < count; i++) {
        if (strstr(dynamic_array[i].name, search) != NULL && !dynamic_array[i].cancelled) {
            printf("\n\n\t\t   *************************************\n");
            printf("\t\t     * Name : %s\n", dynamic_array[i].name);
            printf("\t\t     * Email id : %s\n", dynamic_array[i].email);
            printf("\t\t     * Mobile No : %s\n", dynamic_array[i].mobile);
            time_t currentTime;
            struct tm *localTime;
            currentTime = time(NULL);
            localTime = localtime(&currentTime);
            printf("\t\t     * %s", asctime(localTime));
            printf("\t\t     * Movie Selected: %s\n", dynamic_array[i].movie_selected);
            printf("\t\t     * Seat : %c-%d\n", *(dynamic_array[i].row), dynamic_array[i].col);
            if ('A' <= *(dynamic_array[i].row) && *(dynamic_array[i].row) <= 'F')
                printf("\t\t     * Price = $200\n");
            else if('G' <= *(dynamic_array[i].row) && *(dynamic_array[i].row) <= 'I')
                printf("\t\t     * Price = $300\n");
            else if (*(dynamic_array[i].row) == 'J')
                printf("\t\t     * Price = $500\n");
            printf("\t\t   *************************************\n\n");
        }
    }
    printf("\033[0m");
}

void CancelBooking() {
    printf("   >>> Enter first or last name: ");
    char search[50];
    scanf("%s", search);
    
    for (int i = 0; i < count; i++) {
        if (strstr(dynamic_array[i].name, search) != NULL && !dynamic_array[i].cancelled && dynamic_array[i].row != NULL) {
            printf("Booking found for %s\n", dynamic_array[i].name);
            printf("Movie: %s, Seat: %c-%d\n", dynamic_array[i].movie_selected, *(dynamic_array[i].row), dynamic_array[i].col);
            printf("Do you want to cancel this booking? (Y/N): ");
            char confirm;
            scanf(" %c", &confirm);
            
            if (confirm == 'Y' || confirm == 'y') {
                dynamic_array[i].cancelled = 1;
                
                Theatre *theatre;
                if (strcmp(dynamic_array[i].movie_selected, "Dune 2") == 0) theatre = &one;
                else if (strcmp(dynamic_array[i].movie_selected, "Transformers One") == 0) theatre = &two;
                else if (strcmp(dynamic_array[i].movie_selected, "Oppenheimer") == 0) theatre = &three;
                else if (strcmp(dynamic_array[i].movie_selected, "Inception") == 0) theatre = &four;
                else if (strcmp(dynamic_array[i].movie_selected, "Tenet") == 0) theatre = &five;
                
                int row = *(dynamic_array[i].row) - 'A';
                int col = dynamic_array[i].col - 1;
                strcpy(theatre->seats[row][col], "[ ]");
                
                printf("Booking cancelled successfully.\n");
                return;
            } else {
                printf("Cancellation aborted.\n");
                return;
            }
        }
    }
    printf("No active booking found for %s\n", search);
}


int main() {
    // Initialize theatres with movie names
    one.movie_name = strdup("Dune 2");
    if (one.movie_name == NULL) { printf("Memory allocation failed!\n"); return 1; }

    two.movie_name = strdup("Transformers One");
    if (two.movie_name == NULL) { printf("Memory allocation failed!\n"); return 1; }

    three.movie_name = strdup("Oppenheimer");
    if (three.movie_name == NULL) { printf("Memory allocation failed!\n"); return 1; }

    four.movie_name = strdup("Inception");
    if (four.movie_name == NULL) { printf("Memory allocation failed!\n"); return 1; }

    five.movie_name = strdup("Tenet");
    if (five.movie_name == NULL) { printf("Memory allocation failed!\n"); return 1; }

    // Initialize seats as empty
    const char *empty_seat = "[ ]";
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 15; j++) {
            strcpy(one.seats[i][j], empty_seat);
            strcpy(two.seats[i][j], empty_seat);
            strcpy(three.seats[i][j], empty_seat);
            strcpy(four.seats[i][j], empty_seat);
            strcpy(five.seats[i][j], empty_seat);
        }
    }

    // Allocate memory for dynamic array
    dynamic_array = calloc(1, sizeof(Details));
    if (dynamic_array == NULL) {
        printf("Memory allocation failed!\n");
        return 1; // Exit on allocation failure
    }

    int flag = 0;
    while (flag != 1) {
        PrintMenu();
        int n;
        scanf("%d", &n);
        switch (n) {
            case 1:
                InputDetails();
                break;
            case 2:
                ShowDetails();
                break;
            case 3:
                Book();
                break;
            case 4:
                GenerateBill();
                break;
            case 5:
                CancelBooking(); // Added this option
                break;
            case 6:
                flag = 1; // Exit option
                break;
            default:
                printf("Invalid entry!!!\n");
                break;
        }
    }

    // Free allocated memory for dynamic array and movie names
    free(dynamic_array);

    free(one.movie_name);
    free(two.movie_name);
    free(three.movie_name);
    free(four.movie_name);
    free(five.movie_name);

    return 0;
}
