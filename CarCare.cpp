#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#pragma warning(disable: 4996)

const int kMax = 100;

//doubly linked list

typedef struct Vehicle {
	char License_plate[10];
	char Brand[20];
	int Vehicle_Year;
	double Mileage;
	int Year;
	int Month;
	int Day;
	struct Vehicle* PreviousVehicle;
	struct Vehicle* NextVehicle;
} Vehicle;

typedef struct Stack {
	struct Stacknode* top;
}Stack;

typedef struct StackNode {
	//wwhatevver
}StackNode;

typedef struct Queue {
	struct QueueNode* front;
	struct QueueNode* rear;
}Queue;

typedef struct QueueNode {
	//more wwhatevver
}QueueNode;

typedef struct Reminder {
	struct Reminder* next;
	char* name;
	int MonthsUntilReminder;
	int YearsUntilReminder;
	struct Reminder* prev;
}Reminder;

typedef struct Profile {
	char* LicensePlate;
	char* Brand;
	int VehicleYear;
	int VehicleMileage;
	int VehicleDate;
	int currentYear;
	int currentMonth;
	int currentDay;
}Profile;

//doubly linked list
struct Vehicle* CreateNewVehicle(const char license[], const char brand[], int vehicleYear, double mileage, int year, int month, int day);
struct Vehicle* InsertNewVehicleHead(struct Vehicle* head, struct Vehicle** tail, const char license[], const char brand[], int vehicleYear, double mileage, int year, int month, int day);
struct Vehicle* InsertNewVehicleTail(struct Vehicle* head, struct Vehicle* tail, const char license[], const char brand[], int vehicleYear, double mileage, int year, int month, int day);
void DeleteHead(struct Vehicle** head, struct Vehicle** tail);
void DeleteTail(struct Vehicle** head, struct Vehicle** tail);
void FreeList(struct Vehicle* head);
void PrintList(struct Vehicle* head);
void inputVehicleDetails(struct Vehicle** head, struct Vehicle** tail);

struct Vehicle* CreateNewVehicle(const char license[], const char brand[], int vehicleYear, double mileage, int year, int month, int day) {
	struct Vehicle* newVehicle = (struct Vehicle*)malloc(sizeof(struct Vehicle));

	if (newVehicle == NULL) {
		printf("There is no memory to allocate a new vehicle!");
		exit(1);
	}

	// Initialize the members of the new Vehicle node
	strncpy(newVehicle->License_plate, license, sizeof(newVehicle->License_plate) - 1);
	newVehicle->License_plate[sizeof(newVehicle->License_plate) - 1] = '\0'; // Ensure null termination

	strncpy(newVehicle->Brand, brand, sizeof(newVehicle->Brand) - 1);
	newVehicle->Brand[sizeof(newVehicle->Brand) - 1] = '\0'; // Ensure null termination

	newVehicle->Vehicle_Year = vehicleYear;
	newVehicle->Mileage = mileage;
	newVehicle->Year = year;
	newVehicle->Month = month;
	newVehicle->Day = day;

	newVehicle->NextVehicle = NULL;
	newVehicle->PreviousVehicle = NULL;

	return newVehicle;

}


struct Vehicle* InsertNewVehicleHead(struct Vehicle* head, struct Vehicle** tail, const char license[], const char brand[], int vehicleYear, double mileage, int year, int month, int day) {
	struct Vehicle* newVehicle = CreateNewVehicle(license, brand, vehicleYear, mileage, year, month, day);

	if (head == NULL) {
		*tail = newVehicle;
		return newVehicle;
	}

	head->PreviousVehicle = newVehicle;
	newVehicle->NextVehicle = head;
	return newVehicle;
}

struct Vehicle* InsertNewVehicleTail(struct Vehicle* head, struct Vehicle* tail, const char license[], const char brand[], int vehicleYear, double mileage, int year, int month, int day) {
	struct Vehicle* newVehicle = CreateNewVehicle(license, brand, vehicleYear, mileage, year, month, day);

	if (tail == NULL) {
		tail = newVehicle;
		return newVehicle;
	}

	tail->NextVehicle = newVehicle;
	newVehicle->PreviousVehicle = tail;
	return tail;
}

void DeleteHead(struct Vehicle** head, struct Vehicle** tail) {
	if (*head == NULL) {
		printf("List is Empty!");
		return;
	}
	struct Vehicle* temp = *head;
	*head = (*head)->NextVehicle;

	if (*head != NULL) {
		(*head)->PreviousVehicle = NULL;
	}
	else {
		*tail = NULL;
	}
	free(temp);
}

void DeleteTail(struct Vehicle** head, struct Vehicle** tail) {
	if (*head == NULL) {
		printf("List is Empty!");
		return;
	}
	struct Vehicle* temp = *tail;
	*tail = (*tail)->PreviousVehicle;

	if (*tail != NULL) {
		(*tail)->NextVehicle = NULL;
	}
	else {
		*head = NULL;
	}
	free(temp);
}

void FreeList(struct Vehicle* head) {

	struct Vehicle* current = head;
	struct Vehicle* tempNode;

	while (current != NULL) {
		tempNode = current->NextVehicle;
		free(current);
		current = tempNode;
	}
}

void PrintList(struct Vehicle* head) {
	struct Vehicle* current = head;
	while (current != NULL) {
		printf("License: %s\n", current->License_plate);
		printf("Brand: %s\n", current->Brand);
		printf("Year: %d\n", current->Vehicle_Year);
		printf("Mileage: %.f\n", current->Mileage);
		printf("Date: %d-%d-%d\n", current->Year, current->Month, current->Day);
		printf("-----------------\n");
		current = current->NextVehicle;
	}
}


void inputVehicleDetails(struct Vehicle** head, struct Vehicle** tail) {
	while (1) {
		char license_plate[8];
		char brand[12];
		int vehicleYear;
		double mileage;
		int year, month, day;
		char input[200];

		// Prompt user for vehicle details
		printf("\n-> What is your car's licence plate? : ");
		fgets(input, sizeof(input), stdin);
		sscanf(input, "%s", license_plate);
		if (strlen(license_plate) < 2 || strlen(license_plate) > 8) {
			printf("\n\tLicense plates must be between two and eight characters long\n\n");
			continue; // Restart loop for this iteration
		}

		printf("-----------------------------------------------\n");
		printf("-> What is your car's brand? : ");
		fgets(input, sizeof(input), stdin);
		sscanf(input, "%s", brand);
		if (!(strcmp(brand, "FORD") == 0 ||
			strcmp(brand, "TOYOTA") == 0 ||
			strcmp(brand, "CHEVROLET") == 0 ||
			strcmp(brand, "HYUNDAI") == 0 ||
			strcmp(brand, "HONDA") == 0 ||
			strcmp(brand, "GMC") == 0 ||
			strcmp(brand, "NISSAN") == 0 ||
			strcmp(brand, "RAM") == 0 ||
			strcmp(brand, "KIA") == 0 ||
			strcmp(brand, "VOLKSWAGEN") == 0 ||
			strcmp(brand, "JEEP") == 0 ||
			strcmp(brand, "MAZDA") == 0)) {
			printf("\n\tInvalid brand name. Please enter a valid brand.\n\n");
			continue; // Restart loop for this iteration
		}

		printf("-----------------------------------------------\n");
		printf("-> What year is your car? : ");
		fgets(input, sizeof(input), stdin);
		if (sscanf(input, "%d", &vehicleYear) != 1 || vehicleYear < 2000 || vehicleYear > 2024) {
			printf("\n\tInvalid input. Please enter a valid year between 2000 and 2024.\n\n");
			continue; // Restart loop for this iteration
		}

		printf("-----------------------------------------------\n");
		printf("-> What is the mileage on your car? (km): ");
		fgets(input, sizeof(input), stdin);
		if (sscanf(input, "%lf", &mileage) != 1 || mileage < 8000 || mileage > 500000) {
			printf("\n\tInvalid input. Please enter a mileage between 8000 km and 500,000 km.\n\n");
			continue; // Restart loop for this iteration
		}

		printf("-----------------------------------------------\n");
		printf("-> Today's date (yyyy-mm-dd): ");
		fgets(input, sizeof(input), stdin);
		if (sscanf(input, "%d-%d-%d", &year, &month, &day) != 3) {
			printf("Invalid date format. Please use yyyy-mm-dd.\n");
			continue; // Restart loop for this iteration
		}

		printf("-----------------------------------------------\n");

		// Insert new vehicle into the doubly linked list
		*head = InsertNewVehicleHead(*head, tail, license_plate, brand, vehicleYear, mileage, year, month, day);

		// Print the list of vehicles
		printf("\nList of Vehicles:\n\n");
		PrintList(*head);
	}
}


struct Reminder* createReminder(char* newName, int months, int years);
struct Reminder* sortReminder(struct Reminder* head, char* newName, int months, int years);
int getYear(char* date);
int getMonth(char* date);
int getDay(char* date);


struct Reminder* createReminder(char* newName, int months, int years) {
	Reminder* newReminder = (struct Reminder*)malloc(sizeof(struct Reminder));

	if (newReminder == NULL) {
		printf("\nERROR OUT OF MEMORY\n");
		free(newReminder);
		exit(EXIT_FAILURE);
	}

	strcpy(newReminder->name, newName);
	newReminder->MonthsUntilReminder = months;
	newReminder->YearsUntilReminder = years;
}

//struct Reminder* sortReminder(struct Reminder* head, char* newName, int months, int years) {
//	Reminder* newReminder = createReminder(newName, months, years);
//
//	if (head == NULL) {
//		newReminder->next = newReminder;
//		newReminder->prev = newReminder;
//	}
//}


int main(void) {

	struct Vehicle* head = NULL;
	struct Vehicle* tail = NULL;

	char userInput[3];
	do {
		printf("\n\tWELCOME TO CAR CARE\n");
		printf("\nDoes your car have a Car Care profile? (Y/N) : ");
		fgets(userInput, sizeof(userInput), stdin);
		userInput[strcspn(userInput, "\n")] = '\0'; // Remove newline character
		system("cls");
		if (strcmp(userInput, "Y") == 0) {
			printf("In process of implementation!Create a new maintenance.\n");
			printf("maintenance\n");
			printf("Reminder\n");
			printf("History\n");
			// Implement code for creating new maintenance here
		}
		else if (strcmp(userInput, "N") == 0) {
			inputVehicleDetails(&head, &tail);
		}
		else {
			printf("Invalid input. Please enter 'Y' or 'N'.\n");
			continue; // Exit program with error
		}

	} while (strcmp(userInput, "X") != 0); // Loop until user enters 'X'


	// Free memory allocated for the doubly linked list
	FreeList(head);

	return 0;
}