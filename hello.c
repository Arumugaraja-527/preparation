#include <stdio.h>
#include <string.h>

#define MAX_USERS 10
#define MAX_FRIENDS 5
#define MAX_STATUSES 3
#define NAME_LEN 30
#define STATUS_LEN 100

// Structure to hold user profile
struct User {
    char name[NAME_LEN];
    int friendCount;
    int statusCount;
    struct User *friends[MAX_FRIENDS];
    char statuses[MAX_STATUSES][STATUS_LEN];
};

// Array to hold registered users
struct User users[MAX_USERS];
int userCount = 0;

// Function to create a new user profile
void createProfile() {
    if (userCount >= MAX_USERS) {
        printf("Maximum user limit reached.\n");
        return;
    }
    
    struct User newUser;
    printf("Enter your name: ");
    scanf("%s", newUser.name);
    newUser.friendCount = 0;
    newUser.statusCount = 0;
    
    users[userCount++] = newUser;
    printf("Profile created for %s.\n", newUser.name);
}

// Function to find user by name
struct User* findUserByName(char *name) {
    for (int i = 0; i < userCount; i++) {
        if (strcmp(users[i].name, name) == 0) {
            return &users[i];
        }
    }
    return NULL;
}

// Function to add a friend
void addFriend() {
    char userName[NAME_LEN], friendName[NAME_LEN];
    printf("Enter your name: ");
    scanf("%s", userName);
    struct User *user = findUserByName(userName);
    
    if (user == NULL) {
        printf("User not found.\n");
        return;
    }
    
    if (user->friendCount >= MAX_FRIENDS) {
        printf("You have reached the maximum number of friends.\n");
        return;
    }
    
    printf("Enter friend's name: ");
    scanf("%s", friendName);
    struct User *friend = findUserByName(friendName);
    
    if (friend == NULL) {
        printf("Friend not found.\n");
        return;
    }
    
    user->friends[user->friendCount++] = friend;
    printf("%s and %s are now friends!\n", userName, friendName);
}

// Function to post a status update
void postStatus() {
    char userName[NAME_LEN], status[STATUS_LEN];
    printf("Enter your name: ");
    scanf("%s", userName);
    struct User *user = findUserByName(userName);
    
    if (user == NULL) {
        printf("User not found.\n");
        return;
    }
    
    if (user->statusCount >= MAX_STATUSES) {
        printf("You have reached the maximum number of status updates.\n");
        return;
    }
    
    printf("Enter your status: ");
    getchar(); // To clear the newline character
    fgets(status, STATUS_LEN, stdin);
    status[strlen(status) - 1] = '\0'; // Remove trailing newline
    
    strcpy(user->statuses[user->statusCount++], status);
    printf("Status posted: %s\n", status);
}

// Function to view a user's profile
void viewProfile() {
    char userName[NAME_LEN];
    printf("Enter the name of the user: ");
    scanf("%s", userName);
    struct User *user = findUserByName(userName);
    
    if (user == NULL) {
        printf("User not found.\n");
        return;
    }
    
    printf("User: %s\n", user->name);
    printf("Friends:\n");
    for (int i = 0; i < user->friendCount; i++) {
        printf(" - %s\n", user->friends[i]->name);
    }
    
    printf("Statuses:\n");
    for (int i = 0; i < user->statusCount; i++) {
        printf(" - %s\n", user->statuses[i]);
    }
}

// Main function to handle menu options
int main() {
    int choice;
    
    do {
        printf("\n--- Social Network Menu ---\n");
        printf("1. Create Profile\n");
        printf("2. Add Friend\n");
        printf("3. Post Status\n");
        printf("4. View Profile\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        
        switch (choice) {
            case 1:
                createProfile();
                break;
            case 2:
                addFriend();
                break;
            case 3:
                postStatus();
                break;
            case 4:
                viewProfile();
                break;
            case 5:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice, please try again.\n");
        }
    } while (choice != 5);
    
    return 0;
}
