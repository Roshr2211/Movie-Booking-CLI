#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include<ctype.h>
typedef struct {
    char name[50];
    char email[50];
    char mobile[10];
    char *row;
    int col;
    char movie_selected[50];
} Details;

typedef struct{
    char *movie_name;
    char seats[10][15][4];
} Theatre;

Theatre *list = NULL;

Details *dynamic_array = NULL;
int count = 0;

Theatre one, two, three, four, five;


void PrintMenu()
{
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
    printf("   ║    (5) Exit                                                ║\n");
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

    // dynamic_array[count].cancelled = 0;
    count++;
    printf("Details successfully added!\n");
}


void ShowDetails()
{
    printf("   >>> Enter first or last name: ");
    char search[50];
    scanf("%s", search);
    for (int i = 0; i < count; i++) {
        if (strstr(dynamic_array[i].name, search) != NULL) {
            printf("   Name: %s\n   Mobile: %s\n   Email: %s\n", dynamic_array[i].name, dynamic_array[i].mobile, dynamic_array[i].email);
        }
    }
}
void ReadCSVAndUpdateSeats(const char *filename, Theatre *theatre, char *moviename) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        printf("Could not open file %s for reading.\n", filename);
        return;
    }

    char line[256];
    while (fgets(line, sizeof(line), file)) {
        char *token;
        char movie[50], row;
        int col;
        token = strtok(line,",");
        token = strtok(NULL,",");
        token = strtok(NULL,",");
        token = strtok(NULL, ",");
        if (token) strcpy(movie, token);
        token = strtok(NULL, ",");
        if (token) row = token[0];
        token = strtok(NULL, ",");
        if (token) col = atoi(token);
        if (strcmp(movie,moviename) == 0) {
            int row_index = row - 'A';
            if (row_index >= 0 && row_index < 10 && col >= 1 && col <= 15) {
                strcpy(theatre->seats[row_index][col - 1], "[X]");
            }
        }

    }
    fclose(file);
}
void Book()
{
    printf("   >>> Enter your first or last name: ");
    char search[50];
    scanf("%s", search);
    for (int i = 0; i < count; i++)
    {
        if (strstr(dynamic_array[i].name, search) != NULL)
        {
            printf("   Which Movie would you like to watch:\n");
            printf("   \t(1) Dune 2\n");
            printf("   \t(2) Transformers One\n");
            printf("   \t(3) Oppenheimer\n");
            printf("   \t(4) Inception\n");
            printf("   \t(5) Tenet\n");
            printf("   >>>");
            int n;
            scanf("%d", &n);
            char movie_chosen[50];
            int movie_num;
            switch(n)
            {
                case 1:
                    strcpy(movie_chosen,"Dune 2");
                    movie_num = 1;
                    break;
                case 2:
                    strcpy(movie_chosen,"Transformers One");
                    movie_num = 2;
                    break;
                case 3:
                    strcpy(movie_chosen,"Oppenheimer");
                    movie_num = 3;
                    break;
                case 4:
                    strcpy(movie_chosen,"Inception");
                    movie_num = 4;
                    break;
                case 5:
                    strcpy(movie_chosen,"Tenet");
                    movie_num = 5;
                    break;
                default:
                    printf("Invalid");
                    break;
            }
            switch (movie_num){
                case 1:
                    ReadCSVAndUpdateSeats("data.csv",&one,movie_chosen);
                    break;
                case 2:
                    ReadCSVAndUpdateSeats("data.csv",&two,movie_chosen);
                    break;
                case 3:
                    ReadCSVAndUpdateSeats("data.csv",&three,movie_chosen);
                    break;
                case 4:
                    ReadCSVAndUpdateSeats("data.csv",&four,movie_chosen);
                    break;
                case 5:
                    ReadCSVAndUpdateSeats("data.csv",&five,movie_chosen);
                    break;
                default:
                    break;
            }
            char s;
            char *empty_seat = "[ ]";
            char *booked_seat = "[X]";
            if (n == 1)
                {
                    strcpy(dynamic_array[i].movie_selected, "Dune 2");
                    printf("   You have chosen the movie Dune 2\n");
                    printf("   Select a Seat!\n");

                    printf("\t\tRecliner $500\n");
                    for (int i = 9; i > 8; i--)
                    {
                        printf("\033[38;5;250m");
                        printf("\t\t%c ",'A'+i);
                        printf("\033[0m");
                        for (int j = 0; j < 15; j++)
                        {
                            if (strcmp(one.seats[i][j], empty_seat) == 0)
                                printf("\033[1;32m");
                            else
                                printf("\033[1;31m");
                            printf("%s ", one.seats[i][j]);
                        }
                        printf("\033[0m");
                        printf("\n");
                    }
                    printf("\t\tPrime $300\n");
                    for (int i = 8; i > 5; i--)
                    {
                        printf("\033[38;5;250m");
                        printf("\t\t%c ",'A'+i);
                        printf("\033[0m");
                        for (int j = 0; j < 15; j++)
                        {
                            if (strcmp(one.seats[i][j], empty_seat) == 0)
                                printf("\033[1;32m");
                            else
                                printf("\033[1;31m");
                            printf("%s ", one.seats[i][j]);
                        }
                        printf("\033[0m");
                        printf("\n");
                    }
                    printf("\t\tNomral $200\n");
                    for (int i = 5; i >= 0; i--)
                    {
                        printf("\033[38;5;250m");
                        printf("\t\t%c ",'A'+i);
                        printf("\033[0m");
                        for (int j = 0; j < 15; j++)
                        {
                            if (strcmp(one.seats[i][j], empty_seat) == 0)
                                printf("\033[1;32m");
                            else
                                printf("\033[1;31m");
                            printf("%s ", one.seats[i][j]);
                        }
                        printf("\033[0m");
                        printf("\n");
                    }
                    printf("\t\t   1   2   3   4   5   6   7   8   9   10  11  12  13  14  15\n\n");
                    printf("   >>> Enter the row you would like: ");
                    scanf(" %c", &s);
                    printf("   >>> Enter the seat number you would like (1-15)");
                    int num;
                    scanf("%d", &num);

                    int temp = s - 'A';
                    strcpy(one.seats[temp][num - 1], booked_seat);

                    dynamic_array[i].row = malloc(sizeof(char));
                    *(dynamic_array[i].row) = s;
                    dynamic_array[i].col = num;
                }
            if (n == 2)
                {
                    strcpy(dynamic_array[i].movie_selected, "Transformers One");
                    printf("   You have chosen the movie Transformers One\n");
                    printf("   Select a Seat!\n");

                    printf("\t\tRecliner $500\n");
                    for (int i = 9; i > 8; i--)
                    {
                        printf("\033[38;5;250m");
                        printf("\t\t%c ",'A'+i);
                        printf("\033[0m");
                        for (int j = 0; j < 15; j++)
                        {
                            if (strcmp(two.seats[i][j], empty_seat) == 0)
                                printf("\033[1;32m");
                            else
                                printf("\033[1;31m");
                            printf("%s ", two.seats[i][j]);
                        }
                        printf("\033[0m");
                        printf("\n");
                    }
                    printf("\t\tPrime $300\n");
                    for (int i = 8; i > 5; i--)
                    {
                        printf("\033[38;5;250m");
                        printf("\t\t%c ",'A'+i);
                        printf("\033[0m");
                        for (int j = 0; j < 15; j++)
                        {
                            if (strcmp(two.seats[i][j], empty_seat) == 0)
                                printf("\033[1;32m");
                            else
                                printf("\033[1;31m");
                            printf("%s ", two.seats[i][j]);
                        }
                        printf("\033[0m");
                        printf("\n");
                    }
                    printf("\t\tNomral $200\n");
                    for (int i = 5; i >= 0; i--)
                    {
                        printf("\033[38;5;250m");
                        printf("\t\t%c ",'A'+i);
                        printf("\033[0m");
                        for (int j = 0; j < 15; j++)
                        {
                            if (strcmp(two.seats[i][j], empty_seat) == 0)
                                printf("\033[1;32m");
                            else
                                printf("\033[1;31m");
                            printf("%s ", two.seats[i][j]);
                        }
                        printf("\033[0m");
                        printf("\n");
                    }
                    printf("\t\t   1   2   3   4   5   6   7   8   9   10  11  12  13  14  15\n\n");

                    printf("   >>> Enter the row you would like: ");
                    scanf(" %c", &s);
                    printf("   >>> Enter the seat number you would like (1-15)");
                    int num;
                    scanf("%d", &num);

                    int temp = s - 'A';
                    strcpy(two.seats[temp][num - 1], booked_seat);

                    dynamic_array[i].row = malloc(sizeof(char));
                    *(dynamic_array[i].row) = s;
                    dynamic_array[i].col = num;
                }
            if (n == 3)
                {
                    strcpy(dynamic_array[i].movie_selected, "Oppenheimer");
                    printf("   You have chosen the movie Oppenheimer\n");
                    printf("   Select a Seat!\n");

                    printf("\t\tRecliner $500\n");
                    for (int i = 9; i > 8; i--)
                    {
                        printf("\033[38;5;250m");
                        printf("\t\t%c ",'A'+i);
                        printf("\033[0m");
                        for (int j = 0; j < 15; j++)
                        {
                            if (strcmp(three.seats[i][j], empty_seat) == 0)
                                printf("\033[1;32m");
                            else
                                printf("\033[1;31m");
                            printf("%s ", three.seats[i][j]);
                        }
                        printf("\033[0m");
                        printf("\n");
                    }
                    printf("\t\tPrime $300\n");
                    for (int i = 8; i > 5; i--)
                    {
                        printf("\033[38;5;250m");
                        printf("\t\t%c ",'A'+i);
                        printf("\033[0m");
                        for (int j = 0; j < 15; j++)
                        {
                            if (strcmp(three.seats[i][j], empty_seat) == 0)
                                printf("\033[1;32m");
                            else
                                printf("\033[1;31m");
                            printf("%s ", three.seats[i][j]);
                        }
                        printf("\033[0m");
                        printf("\n");
                    }
                    printf("\t\tNomral $200\n");
                    for (int i = 5; i >= 0; i--)
                    {
                        printf("\033[38;5;250m");
                        printf("\t\t%c ",'A'+i);
                        printf("\033[0m");
                        for (int j = 0; j < 15; j++)
                        {
                            if (strcmp(three.seats[i][j], empty_seat) == 0)
                                printf("\033[1;32m");
                            else
                                printf("\033[1;31m");
                            printf("%s ", three.seats[i][j]);
                        }
                        printf("\033[0m");
                        printf("\n");
                    }
                    printf("\t\t   1   2   3   4   5   6   7   8   9   10  11  12  13  14  15\n\n");

                    printf("   >>> Enter the row you would like: ");
                    scanf(" %c", &s);
                    printf("   >>> Enter the seat number you would like (1-15)");
                    int num;
                    scanf("%d", &num);

                    int temp = s - 'A';
                    strcpy(three.seats[temp][num - 1], booked_seat);

                    dynamic_array[i].row = malloc(sizeof(char));
                    *(dynamic_array[i].row) = s;
                    dynamic_array[i].col = num;
                }
            if (n == 4)
                {
                    strcpy(dynamic_array[i].movie_selected, "Inception");
                    printf("   You have chosen the movie Inception\n");
                    printf("   Select a Seat!\n");

                    printf("\t\tRecliner $500\n");
                    for (int i = 9; i > 8; i--)
                    {
                        printf("\033[38;5;250m");
                        printf("\t\t%c ",'A'+i);
                        printf("\033[0m");
                        for (int j = 0; j < 15; j++)
                        {
                            if (strcmp(four.seats[i][j], empty_seat) == 0)
                                printf("\033[1;32m");
                            else
                                printf("\033[1;31m");
                            printf("%s ", four.seats[i][j]);
                        }
                        printf("\033[0m");
                        printf("\n");
                    }
                    printf("\t\tPrime $300\n");
                    for (int i = 8; i > 5; i--)
                    {
                        printf("\033[38;5;250m");
                        printf("\t\t%c ",'A'+i);
                        printf("\033[0m");
                        for (int j = 0; j < 15; j++)
                        {
                            if (strcmp(four.seats[i][j], empty_seat) == 0)
                                printf("\033[1;32m");
                            else
                                printf("\033[1;31m");
                            printf("%s ", four.seats[i][j]);
                        }
                        printf("\033[0m");
                        printf("\n");
                    }
                    printf("\t\tNomral $200\n");
                    for (int i = 5; i >= 0; i--)
                    {
                        printf("\033[38;5;250m");
                        printf("\t\t%c ",'A'+i);
                        printf("\033[0m");
                        for (int j = 0; j < 15; j++)
                        {
                            if (strcmp(four.seats[i][j], empty_seat) == 0)
                                printf("\033[1;32m");
                            else
                                printf("\033[1;31m");
                            printf("%s ", four.seats[i][j]);
                        }
                        printf("\033[0m");
                        printf("\n");
                    }
                    printf("\t\t   1   2   3   4   5   6   7   8   9   10  11  12  13  14  15\n\n");

                    printf("   >>> Enter the row you would like: ");
                    scanf(" %c", &s);
                    printf("   >>> Enter the seat number you would like (1-15)");
                    int num;
                    scanf("%d", &num);

                    int temp = s - 'A';
                    strcpy(four.seats[temp][num - 1], booked_seat);

                    dynamic_array[i].row = malloc(sizeof(char));
                    *(dynamic_array[i].row) = s;
                    dynamic_array[i].col = num;
                }
            if (n == 5)
                {
                    strcpy(dynamic_array[i].movie_selected, "Tenet");
                    printf("   You have chosen the movie Tenet\n");
                    printf("   Select a Seat!\n");

                    printf("\t\tRecliner $500\n");
                    for (int i = 9; i > 8; i--)
                    {
                        printf("\033[38;5;250m");
                        printf("\t\t%c ",'A'+i);
                        printf("\033[0m");
                        for (int j = 0; j < 15; j++)
                        {
                            if (strcmp(five.seats[i][j], empty_seat) == 0)
                                printf("\033[1;32m");
                            else
                                printf("\033[1;31m");
                            printf("%s ", five.seats[i][j]);
                        }
                        printf("\033[0m");
                        printf("\n");
                    }
                    printf("\t\tPrime $300\n");
                    for (int i = 8; i > 5; i--)
                    {
                        printf("\033[38;5;250m");
                        printf("\t\t%c ",'A'+i);
                        printf("\033[0m");
                        for (int j = 0; j < 15; j++)
                        {
                            if (strcmp(five.seats[i][j], empty_seat) == 0)
                                printf("\033[1;32m");
                            else
                                printf("\033[1;31m");
                            printf("%s ", five.seats[i][j]);
                        }
                        printf("\033[0m");
                        printf("\n");
                    }
                    printf("\t\tNomral $200\n");
                    for (int i = 5; i >= 0; i--)
                    {
                        printf("\033[38;5;250m");
                        printf("\t\t%c ",'A'+i);
                        printf("\033[0m");
                        for (int j = 0; j < 15; j++)
                        {
                            if (strcmp(five.seats[i][j], empty_seat) == 0)
                                printf("\033[1;32m");
                            else
                                printf("\033[1;31m");
                            printf("%s ", five.seats[i][j]);
                        }
                        printf("\033[0m");
                        printf("\n");
                    }
                    printf("\t\t   1   2   3   4   5   6   7   8   9   10  11  12  13  14  15\n\n");

                    printf("   >>> Enter the row you would like: ");
                    scanf(" %c", &s);
                    printf("   >>> Enter the seat number you would like (1-15)");
                    int num;
                    scanf("%d", &num);

                    int temp = s - 'A';
                    strcpy(five.seats[temp][num - 1], booked_seat);

                    dynamic_array[i].row = malloc(sizeof(char));
                    *(dynamic_array[i].row) = s;
                    dynamic_array[i].col = num;
                }
        }
    }
}

void GenerateBill()
{
    printf("   >>> Enter first or last name: ");
    char search[50];
    scanf("%s", search);
    printf("\033[0;31m");
    for (int i = 0; i < count; i++) {
        if (strstr(dynamic_array[i].name, search) != NULL)
        {
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
            if ('A'<=*(dynamic_array[i].row) && *(dynamic_array[i].row)<='F')
                printf("\t\t     * Price = $200\n");
            else if('G'<=*(dynamic_array[i].row) && *(dynamic_array[i].row)<='I')
                printf("\t\t     * Price = $300\n");
            else if (*(dynamic_array[i].row) == 'J')
                printf("\t\t     * Price = $500\n");
            printf("\t\t   *************************************\n\n");
        }
    }
    printf("\033[0m");
}

int main()
{
    one.movie_name = malloc(strlen("Dune 2") + 1);
    strcpy(one.movie_name, "Dune 2");
    two.movie_name = malloc(strlen("Transformers One") + 1);
    strcpy(two.movie_name, "Transformers One");
    three.movie_name = malloc(strlen("Oppenheimer") + 1);
    strcpy(three.movie_name, "Oppenheimer");
    four.movie_name = malloc(strlen("Inception") + 1);
    strcpy(four.movie_name, "Inception");
    five.movie_name = malloc(strlen("Tenet") + 1);
    strcpy(five.movie_name, "Tenet");

    char *empty_seat = "[ ]";
    char *booked_seat = "[X]";

    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 15; j++)
        {
            strcpy(one.seats[i][j], empty_seat);
            strcpy(two.seats[i][j], empty_seat);
            strcpy(three.seats[i][j], empty_seat);
            strcpy(four.seats[i][j], empty_seat);
            strcpy(five.seats[i][j], empty_seat);
        }
    }

    dynamic_array = malloc(sizeof(Details));
       if (dynamic_array == NULL)
       {
           printf("Memory allocation failed!\n");
       }

       int flag = 0;
       while (flag != 1)
       {
           PrintMenu();
           int n;
           scanf("%d", &n);
           switch (n)
           {
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
               flag = 1;
               break;
           default:
               printf("Invalid entry!!!\n");
               break;
           }
       }

       free(dynamic_array);
       return 0;

}
