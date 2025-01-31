#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_TITLE 50
#define MAX_AUTHOR 50
#define MAX_USER 20

typedef struct {
    int id;
    char title[MAX_TITLE];
    char author[MAX_AUTHOR];
    int isAvailable;
} Book;


void adminLogin();
void userLogin();
void addBook();
void deleteBook();
void searchBook();
void viewBooks();
void borrowBook();
void returnBook();
void userViewBooks();
void saveBook(Book book);
void displayBooks();
void writeToFile();
void loadBooks();

Book books[100];
int bookCount = 0;

int main() {
    int choice;

    loadBooks();
    while (1) {
        printf("\n====== Library Management System ======\n");
        printf("1. Admin Login\n");
        printf("2. User Login\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                adminLogin();
                break;
            case 2:
                userLogin();
                break;
            case 3:
                printf("Exiting the program. Goodbye!\n");
                return 0;
            default:
                printf("Invalid choice! Please try again.\n");
        }
    }

    return 0;
}

// Admin login
void adminLogin() {
    char username[MAX_USER], password[MAX_USER];
    printf("\nEnter Admin Username: ");
    scanf("%s", username);
    printf("Enter Admin Password: ");
    scanf("%s", password);

    if (strcmp(username, "nithya") == 0 && strcmp(password, "nithya123") == 0) {
        int choice;
        printf("\nAdmin Login Successful!\n");

        do {
            printf("\n====== Admin Menu ======\n");
            printf("1. Add Book\n");
            printf("2. Delete Book\n");
            printf("3. Search Book\n");
            printf("4. View All Books\n");
            printf("5. Logout\n");
            printf("Enter your choice: ");
            scanf("%d", &choice);

            switch (choice) {
                case 1:
                    addBook();
                    break;
                case 2:
                    deleteBook();
                    break;
                case 3:
                    searchBook();
                    break;
                case 4:
                    viewBooks();
                    break;
                case 5:
                    printf("Logging out...\n");
                    return;
                default:
                    printf("Invalid choice! Try again.\n");
            }
        } while (1);
    } else {
        printf("Invalid credentials! Returning to the main menu.\n");
    }
}

// User login
void userLogin() {
    char username[MAX_USER];
    printf("\nEnter your Username: ");
    scanf("%s", username);

    int choice;
    printf("\nWelcome, %s!\n", username);

    do {
        printf("\n====== User Menu ======\n");
        printf("1. View Books\n");
        printf("2. Borrow Book\n");
        printf("3. Return Book\n");
        printf("4. Logout\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                userViewBooks();
                break;
            case 2:
                borrowBook();
                break;
            case 3:
                returnBook();
                break;
            case 4:
                printf("Logging out...\n");
                return;
            default:
                printf("Invalid choice! Try again.\n");
        }
    } while (1);
}

// Add a book
void addBook() {
    Book book;
    printf("\nEnter Book ID: ");
    scanf("%d", &book.id);
    getchar();
    printf("Enter Book Title: ");
    fgets(book.title, MAX_TITLE, stdin);
    book.title[strcspn(book.title, "\n")] = 0;
    printf("Enter Author Name: ");
    fgets(book.author, MAX_AUTHOR, stdin);
    book.author[strcspn(book.author, "\n")] = 0;
    book.isAvailable = 1;

    books[bookCount++] = book;
    writeToFile();
    printf("Book added successfully!\n");
}

// Delete a book
void deleteBook() {
    int id, found = 0;

    printf("\nEnter Book ID to Delete: ");
    scanf("%d", &id);

    for (int i = 0; i < bookCount; i++) {
        if (books[i].id == id) {
            found = 1;
            for (int j = i; j < bookCount - 1; j++) {
                books[j] = books[j + 1];
            }
            bookCount--;
            writeToFile();
            printf("Book deleted successfully!\n");
            break;
        }
    }

    if (!found) {
        printf("Book not found!\n");
    }
}

// Search for a book
void searchBook() {
    int id, found = 0;

    printf("\nEnter Book ID to Search: ");
    scanf("%d", &id);

    for (int i = 0; i < bookCount; i++) {
        if (books[i].id == id) {
            printf("\nBook Found:\n");
            printf("ID: %d\nTitle: %s\nAuthor: %s\nAvailable: %s\n", books[i].id, books[i].title, books[i].author, books[i].isAvailable ? "Yes" : "No");
            found = 1;
            break;
        }
    }

    if (!found) {
        printf("Book not found!\n");
    }
}

// View all books (admin)
void viewBooks() {
    displayBooks();
}

// Display all books
void displayBooks() {
    printf("\n====== Book List ======\n");
    printf("ID\tTitle\t\tAuthor\t\tAvailable\n");
    printf("-------------------------------------------\n");

    for (int i = 0; i < bookCount; i++) {
        printf("%d\t%s\t\t%s\t\t%s\n", books[i].id, books[i].title, books[i].author, books[i].isAvailable ? "Yes" : "No");
    }
}

// View available books (user)
void userViewBooks() {
    displayBooks();
}

// Borrow a book
void borrowBook() {
    int id, found = 0;

    printf("\nEnter Book ID to Borrow: ");
    scanf("%d", &id);

    for (int i = 0; i < bookCount; i++) {
        if (books[i].id == id && books[i].isAvailable) {
            books[i].isAvailable = 0;
            writeToFile();
            printf("Book borrowed successfully!\n");
            found = 1;
            break;
        }
    }

    if (!found) {
        printf("Book not available or not found!\n");
    }
}

//
void returnBook() {
    int id, found = 0;

    printf("\nEnter Book ID to Return: ");
    scanf("%d", &id);

    for (int i = 0; i < bookCount; i++) {
        if (books[i].id == id && !books[i].isAvailable) {
            books[i].isAvailable = 1;
            writeToFile();
            printf("Book returned successfully!\n");
            found = 1;
            break;
        }
    }

    if (!found) {
        printf("Book not found or already returned!\n");
    }
}

//
void writeToFile() {
    FILE *file = fopen("books.txt", "w");
    if (file == NULL) {
        printf("Error opening file!\n");
        return;
    }

    for (int i = 0; i < bookCount; i++) {
        fprintf(file, "%d,%s,%s,%d\n", books[i].id, books[i].title, books[i].author, books[i].isAvailable);
    }

    fclose(file);
}

// Load books from the file
void loadBooks() {
    FILE *file = fopen("books.txt", "r");
    if (file == NULL) {
        return; // No file exists yet
    }

    while (fscanf(file, "%d,%49[^,],%49[^,],%d\n", &books[bookCount].id, books[bookCount].title, books[bookCount].author, &books[bookCount].isAvailable) != EOF) {
        bookCount++;
    }

    fclose(file);
}
