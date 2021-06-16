#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define USERNAME "user"
#define PASSWORD "password"
#define MAX 20

int isProductAvailable(int);
int isCodeAvailable(char);
int get_int(int);
void close_app();
int check_rate();
void addProduct();
void display();
void updateProduct();
void search();
void login();
void deleteRecord();
void options();

typedef struct items
{
    char product_code[MAX];
    char product_name[MAX];
    int rate;
    int quantity;
    float weight;
    char description[30];

} ITEM;

ITEM item;

int isProductAvailable(int quantity)
{
    FILE *file;
    file = fopen("Record.txt", "r");
    while (!feof(file))
    {
        fread(&item, sizeof(item), 1, file);
        if (item.quantity >= quantity)
        {
            fclose(file);
            return 1;
        }
    }
    fclose(file);
    return 0;
}

int isCodeAvailable(char code[])
{
    FILE *file;
    file = fopen("Record.txt", "r");
    while (!feof(file))
    {
        fread(&item, sizeof(item), 1, file);
        if (strcmp(code, item.product_code) == 0)
        {
            fclose(file);
            return 1;
        }
    }
    fclose(file);
    return 0;
}

int get_int(int input)
{
    char ch;
    while (scanf("%d", &input) != 1)
    {
        while ((ch = getchar()) != '\n')
        {
        }
        printf("\033[1;31m");
        printf("\n\v\t\t\t\t\t\tMust be positive integer.\n");
        printf("\033[0m");
        printf("\t\t\t\t\tEnter Positive integer value 1-6: ");
    }
    return input;
}

void close_app()
{
    char choice;
    printf("\n Do you wish to close the applications?(Y/y)");
    scanf("%s", &choice);
    if (choice == 'Y' || choice == 'y')
    {
        exit(0);
    }
}

int check_rate()
{
    int input;
    char ch;
    while (scanf("%d", &input) != 1)
    {
        while ((ch = getchar()) != '\n')
        {
        }
        printf("\033[1;31m");
        printf("\n\v\t\t\t\t\t\tRate must be a positive Integer.\n");
        printf("\033[0m");
        printf("\t\t\t\t\tEnter rate of the product: ");
    }
    return input;
}

void addProduct()
{
    printf("\v\v\t\t\t\t\t\t\tAdd Product\n");
    printf("\t\t\t\t\t\t************************\n");
    FILE *file;
    char code[MAX];
    char x[4] = {0};
    int a;
    file = fopen("Record.txt", "ab");
    printf("\n\t\t\t\t\tEnter the \" end \" to exit for here");
    printf("\n\t\t\t\t\tEnter Product code: ");
    scanf("%s", code);
    if (strcmp(code, "end") == 0)
    {
        system("cls");
        options();
    }
    int available;
    available = isCodeAvailable(code);
    if (available == 1)
    {
        system("cls");
        printf("\033[1;31m");
        printf("\n\v\t\t\t\t\t\t* Product is already there.\n");
        printf("\033[0m");
        options();
    }
    strcpy(item.product_code, code);
    printf("\t\t\t\t\tEnter Product Name: ");
    scanf("%s", item.product_name);
    printf("\t\t\t\t\tEnter Product Rate: ");
    a = check_rate();
    item.rate = a;
    printf("\t\t\t\t\tEnter Quantity: ");
    scanf("%d", &item.quantity);
    printf("\t\t\t\t\tEnter product Weight(in gram): ");
    scanf("%f", &item.weight);
    printf("\t\t\t\t\tEnter product descriptions: ");
    scanf(" %s", item.description);
    fwrite(&item, sizeof(item), 1, file);
    fclose(file);
}

void display()
{
    printf("\v\v\t\t\t\t\t\t\tAvailable Products\n");
    printf("\t\t\t\t\t\t***************************\n");
    FILE *file;
    int count = 0;
    file = fopen("Record.txt", "rb");
    printf("\t\t\t------------------------------------------------------------------------------------------------------\n");
    printf("\t\t\tCODE\t||\tNAME\t||\tRATE\t||\tQUANTITY\t||\tWEIGHT\t||\tDESCRIPTION\n");
    printf("\t\t\t------------------------------------------------------------------------------------------------------\n");
    if (file == NULL)
    {
        printf("\t\t\t\tNo Product is inserted.");
        options();
    }
    while (fread(&item, sizeof(item), 1, file))
    {
        printf("\t\t\t%s\t||\t%s\t||\t%d\t||\t %d\t\t||\t%.2f\t||\t%s \n", item.product_code, item.product_name, item.rate, item.quantity, item.weight, item.description);
        count++;
    }
    printf("\t\t\t------------------------------------------------------------------------------------------------------\n");
    if (count == 0)
    {
        system("cls");
        printf("\033[1;31m");
        printf("\n\v\t\t\t\t\t\t* Product is not available.\n");
        printf("\033[0m");
    }
    fclose(file);
}

void updateProduct()
{
    int a;
    printf("\v\v\t\t\t\t\t\t\tUpdate Product\n");
    printf("\t\t\t\t\t\t************************\n");
    FILE *file1, *file2;
    char code[MAX], product[MAX];
    int available;
    printf("Enter the Product code to update the record:");
    scanf("%s", code);
    available = isCodeAvailable(code);
    if (available == 0)
    {
        system("cls");
        printf("\033[1;31m");
        printf("\n\v\t\t\t\t\t\t* No Product is found for update.\n");
        printf("\033[0m");
    }
    else
    {
        file1 = fopen("Record.txt", "rb");
        file2 = fopen("tempfile.txt", "wb");
        while (fread(&item, sizeof(item), 1, file1))
        {
            strcpy(product, item.product_code);
            if (strcmp(product, code) != 0)
            {
                fwrite(&item, sizeof(item), 1, file2);
            }
            else
            {
                printf("\n Updating data for the product with code %s ..........\n\n", code);
                printf("\t\t\t\t\tEnter Product Name: ");
                scanf("%s", item.product_name);
                printf("\t\t\t\t\tEnter Product Rate: ");
                a = check_rate();
                item.rate = a;
                printf("\t\t\t\t\tEnter Quantity: ");
                scanf("%d", &item.quantity);
                printf("\t\t\t\t\tEnter product Weight(in gram): ");
                scanf("%f", &item.weight);
                printf("\t\t\t\t\tEnter product descriptions: ");
                scanf(" %s", item.description);
                printf("\n\n");
                fwrite(&item, sizeof(item), 1, file2);
            }
        }
        fclose(file1);
        fclose(file2);
        file1 = fopen("Record.txt", "wb");
        file2 = fopen("tempfile.txt", "rb");
        while (fread(&item, sizeof(item), 1, file2))
        {
            fwrite(&item, sizeof(item), 1, file1);
        }
        fclose(file1);
        fclose(file2);
    }
}

void search()
{

    FILE *file;
    char code[MAX], product[MAX];
    int available;
    printf("\v\t\t\t\t\tEnter \"end\" for back to menu.\n");
    printf("\v\t\t\t\t\tEnter the Product code to search: ");
    scanf("%s", code);
    if (strcmp(code, "end") == 0)
    {
        system("cls");
        options();
    }
    system("cls");
    printf("\v\v\t\t\t\t\t\tProduct information\n");
    printf("\t\t\t\t\t\t**********************\n");
    available = isCodeAvailable(code);
    if (available == 0)
    {
        system("cls");
        system("cls");
        printf("\033[1;31m");
        printf("\n\t\t\t\t\t\tProduct code is not found.\n");
        printf("\033[0m");
    }
    else
    {
        file = fopen("Record.txt", "rb");
        while (fread(&item, sizeof(item), 1, file))
        {
            strcpy(product, item.product_code);
            if (strcmp(product, code) == 0)
            {
                printf("\n\t\t\t\t\t\tProduct Code:        %s", item.product_code);
                printf("\n\t\t\t\t\t\tName of Product:     %s", item.product_name);
                printf("\n\t\t\t\t\t\tRate of Product(RS): %d", item.rate);
                printf("\n\t\t\t\t\t\tProduct Weight:      %.2f", item.weight);
                printf("\n\t\t\t\t\t\tProduct Description: %s\n", item.description);
            }
        }
        fclose(file);
    }
}

void login()
{
    printf("\v\v\t\t\t\t\t\t\tLOGIN \n");
    printf("\t\t\t\t\t\t************************\n");
    char username[15], password[10];
    printf("\v\v\t\t\tEnter username: ");
    scanf("%s", username);
    printf("\t\t\tEnter password: ");
    scanf("%s", password);
    while (1)
    {
        if ((strcmp(USERNAME, username)) == 0 && (strcmp(PASSWORD, password)) == 0)
        {
            system("cls");
            printf("\033[1;32m");
            printf("\t\t\t\t\tLogin successfully!!");
            printf("\033[0m");
            options();
        }
        else
        {
            system("cls");
            printf("\033[1;31m");
            printf("\n\t\t\tSorry you enter the wrong information.\n");
            printf("\n\t\t\tPlease try again.\n");
            printf("\033[0m");
            login();
            break;
        }
    }
}

void deleteRecord()
{
    printf("\v\v\t\t\t\t\t\t\tDelete Product\n");
    printf("\t\t\t\t\t\t************************\n");
    FILE *file1, *file2;
    char code[MAX], product[MAX];
    int available;
    file1 = fopen("Record.txt", "rb");
    if (file1 == NULL)
    {
         printf("\t\t\t\tNo Product is inserted.");
         options();
    }
    display();
    printf("\n\t\t\t\t\t\tEnter the Product code to delete: ");
    scanf("%s", code);
    system("cls");
    available = isCodeAvailable(code);
    if (available == 0)
    {
        system("cls");
        printf("\033[1;31m");
        printf("\n\v\t\t\t\t\t\t* Product is not available.\n");
        printf("\033[0m");
    }
    else
    {

        file2 = fopen("tempfile.txt", "wb");
        while (fread(&item, sizeof(item), 1, file1))
        {
            strcpy(product, item.product_code);
            if (strcmp(product, code) != 0)
            {
                fwrite(&item, sizeof(item), 1, file2);
            }
        }
        fclose(file1);
        fclose(file2);
        file1 = fopen("Record.txt", "wb");
        file2 = fopen("tempfile.txt", "rb");
        while (fread(&item, sizeof(item), 1, file2))
        {
            fwrite(&item, sizeof(item), 1, file1);
        }
        printf("\n\v\t\t\t\t\t\tProduct Deleted Sucessfully!!\n\n");
        fclose(file1);
        fclose(file2);
    }

}

void options()
{
    printf("\v\n\v\t\t\t\t\t\t\t\t    --FASHION BOUTIQUE STORE--\n");
    printf("\t\t\t\t\t\t\t\t**********************************\n");
    int num, choice;
    while (1)
    {
        printf("\n\t\t\t\t\t\t\t\t\t1. ADD PRODUCT\n\t\t\t\t\t\t\t\t\t2. LIST PRODUCTS");
        printf("\n\t\t\t\t\t\t\t\t\t3. SEARCH PRODUCT\n\t\t\t\t\t\t\t\t\t4. REMOVE PRODUCT\n\t\t\t\t\t\t\t\t\t5. UPDATE PRODUCT");
        printf("\n\t\t\t\t\t\t\t\t\t6. CLOSE APPLICATION\n\n");
        printf("\t\t\t\t\t\t\t\t\tENTER YOUR CHOICE: ");
        choice = get_int(num);
        switch (choice)
        {
        case 1:
            system("cls");
            addProduct();
            system("cls");
            break;
        case 2:
            system("cls");
            display();
            break;
        case 3:
            system("cls");
            search();
            break;
        case 4:
            system("cls");
            deleteRecord();
            break;
        case 5:
            system("cls");
            updateProduct();
            break;
        case 6:
            system("cls");
            close_app();
            break;
        default:
            system("cls");
            printf("\033[1;31m");
            printf("\t\tINVALID CHOICE!!!\n");
            printf("\033[0m");
            break;
        }
    }
}

int main()
{
    login();
    system("cls");
    return 0;
}
