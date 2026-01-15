#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Student {
    int studentID;
    char fullName[100];
    char batch[20];
    char membershipType[10];
    char registrationDate[11];
    char dateOfBirth[11];
    char interest[10];
};

struct Database {
    struct Student* students;
    int count;
    int capacity;
};

void startDatabase(struct Database* db) {
    db->count = 0;
    db->capacity = 10;
    db->students = malloc(db->capacity * sizeof(struct Student));
}

void makeBigger(struct Database* db) {
    if (db->count >= db->capacity) {
        db->capacity *= 2;
        db->students = realloc(db->students, db->capacity * sizeof(struct Student));
    }
}

int findStudent(struct Database* db, int id) {
    for (int i = 0; i < db->count; i++) {
        if (db->students[i].studentID == id) {
            return i;
        }
    }
    return -1;
}

void getFromFile(struct Database* db, char* filename) {
    FILE* file = fopen(filename, "rb");
    
    if (!file) {
        printf("Starting new database...\n");
        return;
    }
    
    struct Student temp;
    while (fread(&temp, sizeof(struct Student), 1, file)) {
        makeBigger(db);
        db->students[db->count] = temp;
        db->count++;
    }
    
    fclose(file);
    printf("Loaded %d students from file.\n", db->count);
}

void putToFile(struct Database* db, char* filename) {
    FILE* file = fopen(filename, "wb");
    
    if (!file) {
        printf("Cannot open file for saving.\n");
        return;
    }
    
    fwrite(db->students, sizeof(struct Student), db->count, file);
    fclose(file);
    printf("Saved %d students to file.\n", db->count);
}

void addStudentToFile(struct Database* db, struct Student newStudent, char* filename) {
    makeBigger(db);
    db->students[db->count] = newStudent;
    db->count++;
    
    putToFile(db, filename);
}

void clearInputBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void registerNewStudent(struct Database* db, char* filename) {
    struct Student newStudent;
    printf("\n--- Register New Student ---\n");
    printf("Student ID: ");
    scanf("%d", &newStudent.studentID);
    clearInputBuffer();
    if (findStudent(db, newStudent.studentID) != -1) {
        printf("Student ID already exists!\n");
        return;
    }
    printf("Full Name: ");
    fgets(newStudent.fullName, sizeof(newStudent.fullName), stdin);
    newStudent.fullName[strcspn(newStudent.fullName, "\n")] = '\0';
    
    printf("Batch (CS, SE, Cyber Security, AI): ");
    fgets(newStudent.batch, sizeof(newStudent.batch), stdin);
    newStudent.batch[strcspn(newStudent.batch, "\n")] = '\0';
    
    printf("Membership Type (IEEE/ACM): ");
    fgets(newStudent.membershipType, sizeof(newStudent.membershipType), stdin);
    newStudent.membershipType[strcspn(newStudent.membershipType, "\n")] = '\0';
    
    printf("Registration Date (YYYY-MM-DD): ");
    fgets(newStudent.registrationDate, sizeof(newStudent.registrationDate), stdin);
    newStudent.registrationDate[strcspn(newStudent.registrationDate, "\n")] = '\0';
    
    printf("Date of Birth (YYYY-MM-DD): ");
    fgets(newStudent.dateOfBirth, sizeof(newStudent.dateOfBirth), stdin);
    newStudent.dateOfBirth[strcspn(newStudent.dateOfBirth, "\n")] = '\0';
    
    printf("Interest (IEEE/ACM/Both): ");
    fgets(newStudent.interest, sizeof(newStudent.interest), stdin);
    newStudent.interest[strcspn(newStudent.interest, "\n")] = '\0';
    
    addStudentToFile(db, newStudent, filename);
    printf("Student registered successfully!\n");
}

void showAllStudents(struct Database* db) {
    if (db->count == 0) {
        printf("\nNo students registered yet.\n");
        return;
    }
    printf("\n--- All Registered Students (%d) ---\n", db->count);
    printf("ID\tName\t\tBatch\t\tMembership\tReg Date\tDOB\t\tInterest\n");
    printf("--------------------------------------------------------------------------------\n");
    
    for (int i = 0; i < db->count; i++) {
        printf("%d\t%.15s\t%.10s\t%.5s\t\t%s\t%s\t%s\n", 
               db->students[i].studentID,
               db->students[i].fullName,
               db->students[i].batch,
               db->students[i].membershipType,
               db->students[i].registrationDate,
               db->students[i].dateOfBirth,
               db->students[i].interest);
    }
}

void changeStudentInfo(struct Database* db, char* filename) {
    int id;
    printf("Enter Student ID to update: ");
    scanf("%d", &id);
    clearInputBuffer();
    
    int index = findStudent(db, id);
    if (index == -1) {
        printf("Student not found!\n");
        return;
    }
    
    printf("\nCurrent Information:\n");
    printf("Name: %s\n", db->students[index].fullName);
    printf("Batch: %s\n", db->students[index].batch);
    printf("Membership: %s\n", db->students[index].membershipType);
    printf("Interest: %s\n\n", db->students[index].interest);
    
    printf("Enter new Batch (CS, SE, Cyber Security, AI): ");
    fgets(db->students[index].batch, sizeof(db->students[index].batch), stdin);
    db->students[index].batch[strcspn(db->students[index].batch, "\n")] = '\0';

    printf("Enter new Membership Type (IEEE/ACM): ");
    fgets(db->students[index].membershipType, sizeof(db->students[index].membershipType), stdin);
    db->students[index].membershipType[strcspn(db->students[index].membershipType, "\n")] = '\0';
    printf("Enter new Interest (IEEE/ACM/Both): ");
    fgets(db->students[index].interest, sizeof(db->students[index].interest), stdin);
    db->students[index].interest[strcspn(db->students[index].interest, "\n")] = '\0';
    putToFile(db, filename);
    printf("Student information updated!\n");
}

void removeStudent(struct Database* db, char* filename) {
    int id;
    printf("Enter Student ID to delete: ");
    scanf("%d", &id);
    clearInputBuffer();
    int index = findStudent(db, id);
    if (index == -1) {
        printf("Student not found!\n");
        return;
    }
    
    printf("Are you sure you want to delete %s (ID: %d)? (y/n): ", 
           db->students[index].fullName, id);
    char confirm;
    scanf("%c", &confirm);
    clearInputBuffer();
    
    if (confirm == 'y' || confirm == 'Y') {
        for (int i = index; i < db->count - 1; i++) {
            db->students[i] = db->students[i + 1];
        }
        db->count--;
        putToFile(db, filename);
        printf("Student deleted successfully!\n");
    } else {
        printf("Deletion cancelled.\n");
    }
}

void showBatchReport(struct Database* db) {
    if (db->count == 0) {
        printf("\nNo students registered yet.\n");
        return;
    }
    char batchChoice[20];
    char membershipChoice[10];
    printf("\n--- Batch Report ---\n");
    printf("Enter Batch (CS, SE, Cyber Security, AI): ");
    fgets(batchChoice, sizeof(batchChoice), stdin);
    batchChoice[strcspn(batchChoice, "\n")] = '\0';
    printf("Enter Membership Type (IEEE/ACM/Both/All): ");
    fgets(membershipChoice, sizeof(membershipChoice), stdin);
    membershipChoice[strcspn(membershipChoice, "\n")] = '\0';
    printf("\nStudents in %s batch with %s membership:\n", batchChoice, membershipChoice);
    printf("ID\tName\t\tMembership\tInterest\n");
    printf("----------------------------------------\n");
    
    int found = 0;
    for (int i = 0; i < db->count; i++) {
        int batchMatch = strcmp(db->students[i].batch, batchChoice) == 0;
        int membershipMatch = (strcmp(membershipChoice, "All") == 0) || 
                              (strcmp(db->students[i].membershipType, membershipChoice) == 0) ||
                              (strcmp(membershipChoice, "Both") == 0);
        if (batchMatch && membershipMatch) {
            printf("%d\t%.15s\t%.5s\t\t%s\n", 
                   db->students[i].studentID,
                   db->students[i].fullName,
                   db->students[i].membershipType,
                   db->students[i].interest);
            found = 1;
        }
    }
    if (!found) {
        printf("No students found.\n");
    }
}

void addTestData(struct Database* db, char* filename) {
    struct Student testStudents[] = {
        {101, "Ali Ahmed", "CS", "IEEE", "2024-01-15", "2003-05-20", "IEEE"},
        {102, "Sara Khan", "SE", "ACM", "2024-01-16", "2002-08-14", "ACM"},
        {103, "Ahmed Raza", "AI", "IEEE", "2024-01-17", "2003-02-28", "Both"},
        {104, "Fatima Noor", "Cyber Security", "ACM", "2024-01-18", "2002-11-30", "ACM"},
        {105, "Bilal Hassan", "CS", "IEEE", "2024-01-19", "2003-07-22", "IEEE"},
        {106, "Zainab Malik", "SE", "IEEE", "2024-01-20", "2002-09-10", "IEEE"},
        {107, "Omar Farooq", "AI", "ACM", "2024-01-21", "2003-01-15", "Both"},
        {108, "Ayesha Siddiqui", "Cyber Security", "IEEE", "2024-01-22", "2002-12-05", "IEEE"},
        {109, "Usman Ali", "CS", "ACM", "2024-01-23", "2003-04-18", "ACM"},
        {110, "Hina Shah", "SE", "IEEE", "2024-01-24", "2002-10-25", "Both"},
        {111, "Kamran Butt", "AI", "IEEE", "2024-01-25", "2003-03-12", "IEEE"},
        {112, "Sana Javed", "Cyber Security", "ACM", "2024-01-26", "2002-07-19", "ACM"},
        {113, "Fahad Mahmood", "CS", "IEEE", "2024-01-27", "2003-06-08", "Both"},
        {114, "Nadia Aslam", "SE", "ACM", "2024-01-28", "2002-04-22", "ACM"},
        {115, "Tariq Mehmood", "AI", "IEEE", "2024-01-29", "2003-08-30", "IEEE"},
        {116, "Rabia Akhtar", "Cyber Security", "ACM", "2024-01-30", "2002-01-14", "ACM"},
        {117, "Imran Ashraf", "CS", "IEEE", "2024-01-31", "2003-09-05", "Both"},
        {118, "Saima Iqbal", "SE", "ACM", "2024-02-01", "2002-03-18", "ACM"},
        {119, "Nasir Hussain", "AI", "IEEE", "2024-02-02", "2003-10-11", "IEEE"},
        {120, "Maria Khan", "Cyber Security", "ACM", "2024-02-03", "2002-12-25", "ACM"}
    };
    int testCount = 20;
    int added = 0;
    for (int i = 0; i < testCount; i++) {
        if (findStudent(db, testStudents[i].studentID) == -1) {
            makeBigger(db);
            db->students[db->count] = testStudents[i];
            db->count++;
            added++;
        }
    }
    putToFile(db, filename);
    printf("Added %d test students. Total students: %d\n", added, db->count);
}

void cleanUp(struct Database* db) {
    free(db->students);
}

void showMenu() {
    printf("\n=== IEEE/ACM Membership System ===\n");
    printf("1. Register New Student\n");
    printf("2. Update Student Information\n");
    printf("3. Delete Student\n");
    printf("4. View All Students\n");
    printf("5. Generate Batch Report\n");
    printf("6. Add Test Data (20 students)\n");
    printf("7. Exit\n");
    printf("Choice: ");
}

int main() {
    struct Database studentDB;
    startDatabase(&studentDB);
    char* filename = "members.dat";
    getFromFile(&studentDB, filename);
    
    int choice;
    do {
        showMenu();
        scanf("%d", &choice);
        clearInputBuffer();
        
        switch (choice) {
            case 1:
                registerNewStudent(&studentDB, filename);
                break;
            case 2:
                changeStudentInfo(&studentDB, filename);
                break;
            case 3:
                removeStudent(&studentDB, filename);
                break;
            case 4:
                showAllStudents(&studentDB);
                break;
            case 5:
                showBatchReport(&studentDB);
                break;
            case 6:
                addTestData(&studentDB, filename);
                break;
            case 7:
                putToFile(&studentDB, filename);
                printf("\nGoodbye! Database saved to file.\n");
                break;
            default:
                printf("Invalid choice! Please try again.\n");
        }
        
    } while (choice != 7);
    
    cleanUp(&studentDB);
    
    return 0;
}