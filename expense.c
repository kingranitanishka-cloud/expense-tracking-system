# include <stdio.h>
struct expense{
int ID;
char description[60];
char category[30];
float amount;
};

void add_expense(){
    struct expense e;
    printf("enter expense ID: ");
    scanf("%d", &e.ID);
    printf("enter description (no spaces, use _ instead): ");
    scanf("%s", e.description);
    printf("enter category (no spaces): ");
    scanf("%s", e.category);
    printf("enter amount: ");
    scanf("%f", &e.amount);
    FILE *f = fopen("expenses.dat", "ab");
    fwrite(&e, sizeof(struct expense),1,f);
    fclose(f);
    printf("Expense added successfully!\n");
}

void view_expenses(){
    struct expense e;
    FILE *f = fopen("expenses.dat", "rb");
    printf("ID\tDescription\tCategory\tAmount\n");
    while(fread(&e, sizeof(struct expense),1,f)){
        printf("%d\t%s\t%s\t%.2f\n", e.ID, e.description, e.category, e.amount);
    }
    fclose(f);
}

void search_expense(){
    int id;
    printf("enter expense ID to search: ");
    scanf("%d", &id);
    struct expense e;
    FILE *f = fopen("expenses.dat", "rb");
    int found = 0;
    while(fread(&e, sizeof(struct expense),1,f)){
        if(e.ID == id){
            printf("ID: %d\nDescription: %s\nCategory: %s\nAmount: %.2f\n", e.ID, e.description, e.category, e.amount);
            found = 1;
            break;
        }
    }
    fclose(f);
    if(!found){
        printf("Expense with ID %d not found.\n", id);
    }
}

void delete_expense(){
    int id;
    printf("enter expense ID to delete: ");
    scanf("%d", &id);
    struct expense e;
    FILE *f = fopen("expenses.dat", "rb");
    FILE *temp = fopen("temp.dat", "wb");
    int found = 0;
    while(fread(&e, sizeof(struct expense),1,f)){
        if(e.ID == id){
            found = 1;
            continue; // skip writing this expense to temp file
        }
        fwrite(&e, sizeof(struct expense),1,temp);
    }
    fclose(f);
    fclose(temp);
    remove("expenses.dat");
    rename("temp.dat", "expenses.dat");
    if(found){
        printf("Expense with ID %d deleted successfully.\n", id);
    } else {
        printf("Expense with ID %d not found.\n", id);
    }
}

void total_expense(){
    struct expense e;
    FILE *f = fopen("expenses.dat", "rb");
    float total = 0;
    while(fread(&e, sizeof(struct expense),1,f)){
        total += e.amount;
    }
    fclose(f);
    printf("Total Expense: %.2f\n", total);
}

int main(){
    int choice;
    printf("Expense Tracker\n");
    do{
        printf("1. add expenses\n");
        printf("2. view expenses\n");
        printf("3. search expense\n");
        printf("4. delete an expense\n");
        printf("5. total expense\n");
        printf("6. exit\n");
        printf("enter your choice: ");
        scanf("%d",&choice);
        
        switch(choice){
            case 1:
                add_expense();
                break;
            case 2:
                view_expenses();
                break;
            case 3:
                search_expense();
                break;
            case 4:
                delete_expense();
                break;
            case 5:
                total_expense();
                break;
            case 6:
                printf("Exiting the program. Goodbye!\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }while(choice!=6);

}