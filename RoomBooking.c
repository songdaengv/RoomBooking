// Standard C library header files (#include ....)
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#pragma pack(1)

// Symbolic constants (#define ...)
#define POUND_SIGN 156			// Pound Sign
#define MAX_NUM_RECORDS 999			// Maximum number of records that can be stored
#define MAX_NUM_ROOMS 9			// Maximum number of rooms that can be stored
#define MIN_LEN_ID 001			// Minimum length of ID
#define MAX_NAME 16			// Maximum length a name can be
#define MIN_NAME 1			// Minimum length a name can be
#define MAX_STREET 31			// Maximum length of street name
#define MAX_POST 8			// Maximum length of postcode
#define MAX_EMAIL 31		// Maximum length of email
#define MAX_TELEPHONE 11			// Maximum length of telephone
#define MAX_NUM_FACILITY 19			// Maximum number of facilities that can be stored
#define MAX_NUM_BOOKING 998			// Maximum number of bookings that can be made
#define GREETING "\n		              Room Booking System\n                              -------------------\n\n" // Welcome message

// User-defined data types (struct ...)

// Struct for customers
struct CUSTRECORDS
{
	int CustomerID;
	char CustFirstName[MAX_NAME];
	char CustLastName[MAX_NAME];
	int CustHouseNum;
	char CustStreet[MAX_STREET];
	char CustPostCode[MAX_POST];
	int CustTelephone;
	char CustEmail[MAX_EMAIL];
	char CustMember;
};

// Struct for Rooms
struct ROOM
{
	int RoomID;
	char RoomName[MAX_NAME];
	float RoomPrice;
};

//Struct for Facility
struct FACILITY
{
	int FacID;
	char FacName[MAX_NAME];
};

// Struct for Booking
struct BOOKING
{   
	int BookingID; 
	int CustomerID;
	int RoomID;
	float BookingPrice;
	char BookingDate[9];
	int BookingStartTime;
	int BookingEndTime;
	char FacilityBooked[(MAX_NAME * 3)];
};

// Function Prototypes (a.k.a. Declarations)
// None

// FUNCTION DEFINITIONS:-

void ShowMainMenu();
void BookRoom(struct CUSTRECORDS Customers[], int *CustRecords, struct ROOM Rooms[], int *RoomRecords, struct BOOKING Bookings[], int *BookingRecords, struct FACILITY Facility[], int *FacRecords);
int FileManagement(struct CUSTRECORDS *Customers[], struct ROOM *Rooms[], struct FACILITY *Facility[], struct BOOKING *Bookings[], int *CustRecords, int *RoomRecords, int *FacRecords, int *BookingRecords);
void WriteToFile(struct CUSTRECORDS Customers[], struct ROOM Rooms[], struct FACILITY Facility[], struct BOOKING Bookings[], int *RoomRecords, int *CustRecords, int *FacRecords, int *BookingRecords);

void DisplayPastBookings(struct BOOKING Bookings[], int *BookingRecords, struct ROOM Rooms[], int *RoomRecords);

void AddCustomer(struct CUSTRECORDS Customers[], int *CustRecords, int MaxRecords);
void EditCustomer(struct CUSTRECORDS Customers[], int CustRecords);
void CustUpdateMenu();
void DisplayAllCustomer(struct CUSTRECORDS Customers[], int *CustRecords);
void DisplaySelectedCustomer(struct CUSTRECORDS Customers[], int *CustRecords);

void AddRoom(struct ROOM Rooms[], int *RoomRecords);
void EditRoom(struct ROOM Rooms[], int RoomRecords);
void ShowRoomEditMenu();
void DisplayAllRooms(struct ROOM Rooms[], int *RoomRecords);
void DisplaySelectedRoom(struct ROOM Rooms[], int *RoomRecords);

void AddFacility(struct FACILITY Facility[], int *FacRecords);
void EditFacility(struct FACILITY Facility[], int *FacRecords);
void AddEditFacilitiesMenu();
void AddEditFacilities(struct FACILITY Facility[], int *FacRecords);
char GetFacilityBooked(struct FACILITY Facility[], int *FacRecords, char BookedFacility[]);

void GetValidatedName(char ValidatedString[], int MinLength, int MaxLength);
char GetValidatedString(char ValidatedString[], int MinLength, int MaxLength);
char GetValidatedYesOrNo();
int GetValidatedInteger(int Min, int Max);
void ClearStruct(struct CUSTRECORDS Customers[], struct ROOM Rooms[], struct FACILITY Facility[], struct BOOKING Bookings[]);
void GetValidatedDate(char ValidatedString[]);
void Pause();


int main()
{
	struct CUSTRECORDS Customers[MAX_NUM_RECORDS];
	struct ROOM Rooms[MAX_NUM_ROOMS];
	struct FACILITY Facility[MAX_NUM_FACILITY];
	struct BOOKING Bookings[MAX_NUM_BOOKING];

	// Local Constants: 
	int RoomRecords = 0, BookingRecords = 0;  // ACTUAL Number of Records    
	int CustRecords = 0, FacRecords = 0; // ACTUAL Number of Records

	// Input Variables:
	int MenuChoice = 0;

	// Intermediate Variables:
	// None

	// Output Variables:
	// None

	ClearStruct(Customers, Rooms, Facility, Bookings);
	FileManagement(Customers, Rooms, Facility, Bookings, &CustRecords, &RoomRecords, &FacRecords, &BookingRecords);

	do
	{
		//Clear screen, display menu and get user-selected menu item   
		ShowMainMenu();
		MenuChoice = GetValidatedInteger(1, 12); // Minimum choice 1, max choice 12


		//Action user-selected menu item   
		switch (MenuChoice)
		{
		case 1:
			BookRoom(Customers, &CustRecords, Rooms, &RoomRecords, Bookings, &BookingRecords, Facility, &FacRecords);	//Open function BookRoom
			break;
		case 2:
			AddCustomer(Customers, &CustRecords, MAX_NUM_RECORDS);	//Open function AddCustomer
			break;
		case 3:
			EditCustomer(Customers, CustRecords);			//Open function EditCustomer
			break;
		case 4:
			AddRoom(Rooms, &RoomRecords);			//Open function AddRoom
			break;
		case 5:
			EditRoom(Rooms, RoomRecords);			//Open function EditRoom
			break;
		case 6:
			DisplayAllCustomer(Customers, &CustRecords);						//Open function DisplayAllCustomer
			break;
		case 7:
			DisplaySelectedCustomer(Customers, &CustRecords);						//Open function DisplaySelectedCustomer
			break;
		case 8:
			DisplayAllRooms(Rooms, &RoomRecords);						//Open function DisplayAllRooms
			break;
		case 9:
			DisplaySelectedRoom(Rooms, &RoomRecords);						//Open function DisplaySelectedRoom
			break;
		case 10:
			AddEditFacilities(Facility, &FacRecords);						//Open function AddEditFacilities
			break;
		case 11:
			DisplayPastBookings(Bookings, &BookingRecords, Rooms, &RoomRecords);						//Open function DisplayPastBookings

			break;
		case 12:
			WriteToFile(Customers, Rooms, Facility, Bookings, &RoomRecords, &CustRecords, &FacRecords, &BookingRecords);
			printf("\nQuitting Program");							//Quit the program
			printf("\n\n");
			break;
		}
	} while (MenuChoice != 12);


	Pause();

}


void ShowMainMenu()
{
	system("cls");  // NB Not ANSCII-C compliant (Windows-specific)  
	printf("%s", GREETING);
	printf("\n MAIN MENU\n ---------");
	printf("\n  1. Book Room");
	printf("\n  2. Add Customer");
	printf("\n  3. Edit Customer");
	printf("\n  4. Add Room");
	printf("\n  5. Edit Room");
	printf("\n  6. Display All Customer");
	printf("\n  7. Display Selected Customer");
	printf("\n  8. Display All Rooms");
	printf("\n  9. Display Selected Room");
	printf("\n  10. Add/Edit Facilities");
	printf("\n  11. Display Past Bookings");
	printf("\n  12. Quit");
	printf("\n\n  Enter your choice: ");
}

/**********************************************************************************************
* Function Name: int FileManagement()
*
* Function Description:
*  -Reading from file, or creating new file, if file doesn't existing
*
* User-interface variables:-
*		*OUT (Return values):
*			- N/A
*		*IN (Value Parameters):
*			- N/A
*		*IN and OUT (Reference Parameters):
*			- struct CUSTRECORDS Customers[], int CustRecords, struct ROOM Rooms[], int RoomRecords, struct BOOKING Bookings[], int BookingRecords, struct FACILITY Facility[], int FacRecords
*
* History [Date (Author): Description)]:-
*   01/05/2017 (639558)  : Created
**********************************************************************************************/
int FileManagement(struct CUSTRECORDS Customers[], struct ROOM Rooms[], struct FACILITY Facility[], struct BOOKING Bookings[], int *CustRecords, int *RoomRecords, int *FacRecords, int *BookingRecords)
{
	FILE *custfile;
	FILE *roomfile;
	FILE *facfile;
	FILE *bookingfile;
	int i = 0;
	struct CUSTRECORDS Customer;
	struct ROOM Room;
	struct FACILITY Facilities;
	struct BOOKING Booking;
	int CustRecord = 0, BookingRecord = 0, RoomRecord = 0, FacRecord = 0;
	fopen_s(&custfile, "Customer Database", "rb");
	if (custfile == NULL)
	{
		fopen_s(&custfile, "Customer Database", "wb");
	}
	else
	{
		fread(&Customer, sizeof(struct CUSTRECORDS), 1, custfile);
		//Keep going up to end of file marker
		while (!(feof(custfile)))
		{
			Customers[CustRecord] = Customer;
			CustRecord++;

			fread(&Customer, sizeof(struct CUSTRECORDS), 1, custfile);
		}
	}
	fclose(custfile);

	fopen_s(&roomfile, "Room Database", "rb");
	if (roomfile == NULL)
	{
		fopen_s(&roomfile, "Room Database", "wb");
	}
	else
	{
		fread(&Room, sizeof(struct ROOM), 1, roomfile);
		//Keep going up to end of file marker
		while (!(feof(roomfile)))
		{
			Rooms[RoomRecord] = Room;
			RoomRecord++;

			fread(&Room, sizeof(struct ROOM), 1, roomfile);
		}
	}
	fclose(roomfile);

	fopen_s(&facfile, "Facility Database", "rb");
	if (facfile == NULL)
	{
		fopen_s(&facfile, "Facility Database", "wb");
	}
	else
	{
		fread(&Facilities, sizeof(struct FACILITY), 1, facfile);
		//Keep going up to end of file marker
		while (!(feof(facfile)))
		{
			Facility[FacRecord] = Facilities;
			FacRecord++;

			fread(&Facilities, sizeof(struct FACILITY), 1, facfile);
		}
	}
	fclose(facfile);

	fopen_s(&bookingfile, "Booking Database", "rb");
	if (bookingfile == NULL)
	{
		fopen_s(&bookingfile, "Booking Database", "wb");
	}
	else
	{
		fread(&Booking, sizeof(struct BOOKING), 1, bookingfile);
		//Keep going up to end of file marker
		while (!(feof(bookingfile)))
		{
			Bookings[BookingRecord] = Booking;
			BookingRecord++;

			fread(&Booking, sizeof(struct BOOKING), 1, bookingfile);
		}
	}
	fclose(bookingfile);

	*CustRecords = CustRecord;
	*FacRecords = FacRecord;
	*BookingRecords = BookingRecord;
	*RoomRecords = RoomRecord;
}

/**********************************************************************************************
* Function Name: void BookRoom()
*
* Function Description:
*  - Allow user to book room. 
*		- by inputting customer ID, inputting room ID, inputting date, inputting hours, inputting booking time.
*
* User-interface variables:-
*		*OUT (Return values):
*			- N/A
*		*IN (Value Parameters):
*			- N/A
*		*IN and OUT (Reference Parameters):
*			- struct CUSTRECORDS Customers[], int CustRecords, struct ROOM Rooms[], int RoomRecords, struct BOOKING Bookings[], int BookingRecords, struct FACILITY Facility[], int FacRecords
*
* History [Date (Author): Description)]:-
*   01/05/2017 (639558)  : Created
**********************************************************************************************/
void BookRoom(struct CUSTRECORDS Customers[], int *CustRecords, struct ROOM Rooms[], int *RoomRecords, struct BOOKING Bookings[], int *BookingRecords, struct FACILITY Facility[], int *FacRecords){

	const int cFalse = 0, cTrue = 1;
	char ExistCustomer, BookingDate[9], Member, LocalFacilityBooked[48];
	int RoomID, HourBook = 0, RoomFound = 0, AlreadyBooked = 0, LocalBookingID;
	int ID, i = 0, MatchFound = 0, LocalBookingStartTime = 0, LocalBookingEndTime = 0;
	float LocalRoomPrice = 0.00;




	printf("\nAre you an existing Customer?\n");
	printf("\nEnter Y or N: ");
	ExistCustomer = GetValidatedYesOrNo();
	if (ExistCustomer == 'Y' || ExistCustomer == 'y')
	{
		if (*BookingRecords != MAX_NUM_BOOKING)
		{
			do
			{
				Member = 'n';
				if (*CustRecords != 0)
				{
					if (*RoomRecords != 0)
					{
						printf("\n\nEnter Customer ID: ");
						ID = GetValidatedInteger(1, *CustRecords);
						MatchFound = cFalse;
						for (i = 0; i < *CustRecords; i++)
						{
							if (ID == Customers[i].CustomerID)
							{
								MatchFound = cTrue;
								Member = Customers[i].CustMember;
							}
						}

						if (MatchFound == cTrue)
						{
							printf("\n\n%-8s %-16s %-7s", "Room ID.", "Room Name", "Price");
							printf("\n%-8s %-16s%-7s", "--------", "---------", "-------");
							for (i = 0; i < *RoomRecords; i++)
							{
								printf("\n%003d      %-16s%c%-0.2f", Rooms[i].RoomID, Rooms[i].RoomName, POUND_SIGN, Rooms[i].RoomPrice);
							}

							printf("\n\nEnter Room ID: ");
							RoomID = GetValidatedInteger(1, *RoomRecords);
							for (i = 0; i < *RoomRecords; i++)
							{
								if (RoomID == Rooms[i].RoomID);
								{
									RoomFound = cTrue;
									LocalRoomPrice = Rooms[i].RoomPrice;
								}
							}
							if (RoomFound = cTrue)
							{
								GetValidatedDate(BookingDate);
								printf("\n\nSelect Booking");
								printf("\n\nBooking is only avaliable from 11:00 to 17:00");
								printf("\n\n\nHow many Hours do you want to Book (Maxmum is 3 hours): ");
								HourBook = GetValidatedInteger(1, 3);
								if (HourBook == 1)
								{
									printf("\n\nEnter when you want the booking to begin: ");
									LocalBookingStartTime = GetValidatedInteger(11, 17);
									LocalBookingEndTime = LocalBookingStartTime + 1;

									printf("\n\nChecking Avaliablilty");

									if (*BookingRecords == 0)
									{
										Bookings[*BookingRecords].BookingID = 1;
										Bookings[*BookingRecords].CustomerID = ID;
										Bookings[*BookingRecords].RoomID = RoomID;
										strcpy_s(Bookings[*BookingRecords].BookingDate, 9, BookingDate);
										Bookings[*BookingRecords].BookingStartTime = LocalBookingStartTime;
										Bookings[*BookingRecords].BookingEndTime = LocalBookingEndTime;
										if (Member == 'y' || Member == 'Y')
										{
											Bookings[*BookingRecords].BookingPrice = (LocalRoomPrice * 0.75);
										}
										else
										{
											Bookings[*BookingRecords].BookingPrice = LocalRoomPrice;
										}
										GetFacilityBooked(Facility, FacRecords, Bookings[*BookingRecords].FacilityBooked);
										printf("\n\nBooking Successful");
										(*BookingRecords)++;
									}
									else
									{
										AlreadyBooked = cFalse;
										for (i = 0; i < *BookingRecords; i++)
										{
											if (RoomID == Bookings[i].RoomID)
											{
												if (strcmp(BookingDate, Bookings[i].BookingDate) == 0)
												{
													if (LocalBookingStartTime >= Bookings[i].BookingStartTime && (LocalBookingStartTime> Bookings[i].BookingEndTime))
													{
														AlreadyBooked = cTrue;
													}
													else if (LocalBookingEndTime > Bookings[i].BookingStartTime && (LocalBookingEndTime < Bookings[i].BookingEndTime))
													{
														AlreadyBooked = cTrue;
													}
													else if (LocalBookingStartTime <= Bookings[i].BookingStartTime && (LocalBookingEndTime >= Bookings[i].BookingEndTime))
													{
														AlreadyBooked = cTrue;
													}
													else
													{
														//Not booked
													}
												}
												else
												{
													//Not Booked
												}
											}
											else
											{
												//Not Booked
											}
										}
										if (AlreadyBooked == cFalse)
										{
											for (i = 0; i < *BookingRecords; i++)		//Create an unique ID for each record
											{
												if (LocalBookingID < Bookings[i].BookingID)
												{
													LocalBookingID = Bookings[i].BookingID;
												}
											}
											LocalBookingID++;
											Bookings[*BookingRecords].BookingID = LocalBookingID;
											Bookings[*BookingRecords].CustomerID = ID;
											Bookings[*BookingRecords].RoomID = RoomID;
											strcpy_s(Bookings[*BookingRecords].BookingDate, 9, BookingDate);
											Bookings[*BookingRecords].BookingStartTime = LocalBookingStartTime;
											Bookings[*BookingRecords].BookingEndTime = LocalBookingEndTime;
											if (Member == 'y' || Member == 'Y')
											{
												Bookings[*BookingRecords].BookingPrice = (LocalRoomPrice * 0.75);
											}
											else
											{
												Bookings[*BookingRecords].BookingPrice = LocalRoomPrice;
											}
											GetFacilityBooked(Facility, FacRecords, Bookings[*BookingRecords].FacilityBooked);
											printf("\n\nBooking Successful");
											(*BookingRecords)++;
										}
										else
										{
											printf("\n\nRoom have been booked:%s       Time:%d-%d", BookingDate, LocalBookingStartTime, LocalBookingEndTime);
										}
									}
								}
								else if (HourBook == 2)
								{
									printf("\n\nEnter The time you want booking to Start: ");
									LocalBookingStartTime = GetValidatedInteger(11, 15);
									LocalBookingEndTime = LocalBookingStartTime + 2;

									printf("\n\nChecking Avaliablilty");

									if (*BookingRecords == 0)
									{
										Bookings[*BookingRecords].BookingID = 1;
										Bookings[*BookingRecords].CustomerID = ID;
										Bookings[*BookingRecords].RoomID = RoomID;
										strcpy_s(Bookings[*BookingRecords].BookingDate, 9, BookingDate);
										Bookings[*BookingRecords].BookingStartTime = LocalBookingStartTime;
										Bookings[*BookingRecords].BookingEndTime = LocalBookingEndTime;
										if (Member == 'y' || Member == 'Y')
										{
											Bookings[*BookingRecords].BookingPrice = ((LocalRoomPrice * 0.75) * 2);
										}
										else
										{
											Bookings[*BookingRecords].BookingPrice = (LocalRoomPrice * 2);
										}
										GetFacilityBooked(Facility, FacRecords, Bookings[*BookingRecords].FacilityBooked);
										(*BookingRecords++);
										printf("\n\nBooking Successful");
									}
									else
									{
										AlreadyBooked = cFalse;
										for (i = 0; i < *BookingRecords; i++)
										{
											if (RoomID == Bookings[i].RoomID)
											{
												if (strcmp(BookingDate, Bookings[i].BookingDate) == 0)
												{
													if (LocalBookingStartTime >= Bookings[i].BookingStartTime && (LocalBookingStartTime> Bookings[i].BookingEndTime))
													{
														AlreadyBooked = cTrue;
													}
													else if (LocalBookingEndTime > Bookings[i].BookingStartTime && (LocalBookingEndTime < Bookings[i].BookingEndTime))
													{
														AlreadyBooked = cTrue;
													}
													else if (LocalBookingStartTime <= Bookings[i].BookingStartTime && (LocalBookingEndTime >= Bookings[i].BookingEndTime))
													{
														AlreadyBooked = cTrue;
													}
													else
													{
														//Not booked
													}
												}
												else
												{
													//Not Booked
												}
											}
											else
											{
												//Not Booked
											}
										}
										if (AlreadyBooked == cFalse)
										{
											if (AlreadyBooked == cFalse)
											{
												for (i = 0; i < *BookingRecords; i++)		//Create an unique ID for each record
												{
													if (LocalBookingID < Bookings[i].BookingID)
													{
														LocalBookingID = Bookings[i].BookingID;
													}
												}
												LocalBookingID++;
												Bookings[*BookingRecords].BookingID = LocalBookingID;
												Bookings[*BookingRecords].CustomerID = ID;
												Bookings[*BookingRecords].RoomID = RoomID;
												strcpy_s(Bookings[*BookingRecords].BookingDate, 9, BookingDate);
												Bookings[*BookingRecords].BookingStartTime = LocalBookingStartTime;
												Bookings[*BookingRecords].BookingEndTime = LocalBookingEndTime;
												if (Member == 'y' || Member == 'Y')
												{
													Bookings[*BookingRecords].BookingPrice = (LocalRoomPrice * 0.75 * 2);
												}
												else
												{
													Bookings[*BookingRecords].BookingPrice = LocalRoomPrice * 2;
												}
												GetFacilityBooked(Facility, FacRecords, Bookings[*BookingRecords].FacilityBooked);
												printf("\n\nBooking Successful");
												(*BookingRecords)++;
											}
											else
											{
												printf("\n\nRoom have been booked:%s       Time:%d-%d", BookingDate, LocalBookingStartTime, LocalBookingEndTime);
											}
										}
									}
								}
								else
								{
									printf("\nEnter when you want the booking to begin: ");
									LocalBookingStartTime = GetValidatedInteger(11, 14);
									LocalBookingEndTime = LocalBookingStartTime + 3;

									printf("\n\nChecking Avaliablilty");

									if (*BookingRecords == 0)
									{
										Bookings[*BookingRecords].BookingID = 1;
										Bookings[*BookingRecords].CustomerID = ID;
										Bookings[*BookingRecords].RoomID = RoomID;
										strcpy_s(Bookings[*BookingRecords].BookingDate, 9, BookingDate);
										Bookings[*BookingRecords].BookingStartTime = LocalBookingStartTime;
										Bookings[*BookingRecords].BookingEndTime = LocalBookingEndTime;
										if (Member == 'y' || Member == 'Y')
										{
											Bookings[*BookingRecords].BookingPrice = ((LocalRoomPrice * 0.75) * 3);
										}
										else
										{
											Bookings[*BookingRecords].BookingPrice = (LocalRoomPrice * 3);
										}
										GetFacilityBooked(Facility, FacRecords, Bookings[*BookingRecords].FacilityBooked);
										(*BookingRecords)++;
										printf("\n\nBooking Successful");
									}
									else
									{
										AlreadyBooked = cFalse;
										for (i = 0; i < *BookingRecords; i++)
										{
											if (RoomID == Bookings[i].RoomID)
											{
												if (strcmp(BookingDate, Bookings[i].BookingDate) == 0)
												{
													if (LocalBookingStartTime >= Bookings[i].BookingStartTime && (LocalBookingStartTime> Bookings[i].BookingEndTime))
													{
														AlreadyBooked = cTrue;
													}
													else if (LocalBookingEndTime > Bookings[i].BookingStartTime && (LocalBookingEndTime < Bookings[i].BookingEndTime))
													{
														AlreadyBooked = cTrue;
													}
													else if (LocalBookingStartTime <= Bookings[i].BookingStartTime && (LocalBookingEndTime >= Bookings[i].BookingEndTime))
													{
														AlreadyBooked = cTrue;
													}
													else
													{
														//Not booked
													}
												}
												else
												{
													//Not Booked
												}
											}
											else
											{
												//Not Booked
											}
										}
										if (AlreadyBooked == cFalse)
										{
											for (i = 0; i < *BookingRecords; i++)		//Create an unique ID for each record
											{
												if (LocalBookingID < Bookings[i].BookingID)
												{
													LocalBookingID = Bookings[i].BookingID;
												}
											}
											LocalBookingID++;
											Bookings[*BookingRecords].BookingID = LocalBookingID;
											Bookings[*BookingRecords].CustomerID = ID;
											Bookings[*BookingRecords].RoomID = RoomID;
											strcpy_s(Bookings[*BookingRecords].BookingDate, 9, BookingDate);
											Bookings[*BookingRecords].BookingStartTime = LocalBookingStartTime;
											Bookings[*BookingRecords].BookingEndTime = LocalBookingEndTime;
											if (Member == 'y' || Member == 'Y')
											{
												Bookings[*BookingRecords].BookingPrice = (LocalRoomPrice * 0.75) * 3;
											}
											else
											{
												Bookings[*BookingRecords].BookingPrice = LocalRoomPrice * 3;
											}
											GetFacilityBooked(Facility, FacRecords, Bookings[*BookingRecords].FacilityBooked);
											printf("\n\nBooking Successful");
											(*BookingRecords)++;
										}
										else
										{
											printf("\n\nRoom have been booked:%s       Time:%d-%d", BookingDate, LocalBookingStartTime, LocalBookingEndTime);
										}
									}
								}
							}
							else
							{
								printf("\n\nSorry, Room ID incorrect.");
								MatchFound = cFalse;
							}
						}
						else
						{
							MatchFound = cFalse;
							printf("\n\nIncorrect, ID");
						}
					}
					else
					{
						printf("\n\nThere is no Room Record");
						printf("\n\nPlease Add Room, Before Booking A Room");
						Pause();
						main();
					}
				}
				else
				{
					printf("\n\nThere is no customer record");
					printf("\n\nPlease add a customer before booking a room");
					Pause();
					main();
				}
			} while (MatchFound = cFalse);
		}
		else
		{
			printf("\n\nSorry, Booking Database is Full");
		}
	}
	else
	{
		printf("\n\nReturning to Main Menu");
		printf("\n\nPlease add a customer before booking a room");
		Pause();
		main();
	}
	Pause();
}

/**********************************************************************************************
* Function Name: void GetFacilityBooked()
*
* Function Description:
*  - Display all existing facilities, allow customer to select up to 3 facilities by inputted "y" or "n"
*
* User-interface variables:-
*		*OUT (Return values):
*			- BookedFacility
*		*IN (Value Parameters):
*			- N/A
*		*IN and OUT (Reference Parameters):
*			- struct FACILITY Facility[], int FacRecords
*
* History [Date (Author): Description)]:-
*   01/05/2017 (639558)  : Created
**********************************************************************************************/
char GetFacilityBooked(struct FACILITY Facility[], int *FacRecords, char BookedFacility[])
{
	int Counter = 0, i = 0, j = 0;
	char FacilityBooked[48] = "", Choice;
	if (*FacRecords == 0)
	{
		strcpy_s(BookedFacility, 48, "");
	}
	else
	{
		printf("\n\nAll Facility");
		printf("\n\n%-11s %-16s", "Facility ID", "Facility Name");
		printf("\n%-8s %-16s", "-----------", "-------------");
		for (j = 0; j < *FacRecords; j++)
		{
			printf("\n%003d         %-16s", Facility[j].FacID + 1, Facility[j].FacName);;
		}
		do
		{
			if (i < *FacRecords)
			{

				if (i == 0)
				{
					printf("\n\nUp to 3 Facility can be selected");
				}
				printf("\n\nEnter Y or N to following facility");
				printf("\n\n%03d: %s\n", Facility[i].FacID + 1, Facility[i].FacName);
				Choice = GetValidatedYesOrNo();
				if (Choice == 'Y' || Choice == 'y')
				{
					if (Counter == 0)
					{
						strcpy_s(FacilityBooked, MAX_NAME, Facility[i].FacName);
						strcat_s(FacilityBooked, 48, "");

					}
					else
					{
						strcat_s(FacilityBooked, 48, " ");
						strcat_s(FacilityBooked, 48, Facility[i].FacName);
					}

					Counter++;
					i++;
				}
				else
				{
					i++;
				}
			}
			else
			{
				Counter = 3;
			}
		} while (Counter < 3);
		strcpy_s(BookedFacility, 48, FacilityBooked);
	}
}

/**********************************************************************************************
* Function Name: void AddCustomer()
*
* Function Description:
*  - Allows user to add customer 
*  - by inputting FirstName, LastName, House Number, Street, PostCode, Telephone Number, Email address and Member
*
* User-interface variables:-
*		*OUT (Return values):
*			- Customer ID
*		*IN (Value Parameters):
*			- N/A
*		*IN and OUT (Reference Parameters):
*			- struct CUSTRECORDS Customers[], int CustRecords
*
* History [Date (Author): Description)]:-
*   01/05/2017 (639022)  : Created
**********************************************************************************************/
void AddCustomer(struct CUSTRECORDS Customers[], int *CustRecords, int MaxRecords)
{
	char AddAnother; // 'Y' or 'N'
	int ID = 0;
	int	i = 0;
	int TelephoneNum = 0;

	do
	{
		if (*CustRecords == MAX_NUM_RECORDS)
		{
			printf("\nThe catalogue is full. You cannot add another record.");
			Pause();
			return;

		}
		else
		{

			for (i = 0; i < *CustRecords; i++)		//Create an unique ID for each Customer
			{
				if (ID < Customers[i].CustomerID)
				{
					ID = Customers[i].CustomerID;
				}
			}
			ID++;
			Customers[*CustRecords].CustomerID = ID;		//Save it as CustomerID

			printf("\n\nEnter the Customers First name: ");		//Request First name
			GetValidatedName(Customers[*CustRecords].CustFirstName, 1, MAX_NAME - 1);	//Check validation and save it as First name

			printf("\nEnter the Customers Last name: ");		//Request Last name
			GetValidatedName(Customers[*CustRecords].CustLastName, 1, MAX_NAME - 1);	//Check validation and save it as Last name

			printf("\nEnter Customer House Number: ");		//Request House Number
			Customers[*CustRecords].CustHouseNum = GetValidatedInteger(1, 999);	//Check validation and save it as CustHouseNum

			printf("\nEnter Street: ");		//Request Street
			GetValidatedName(Customers[*CustRecords].CustStreet, 1, MAX_STREET - 1);	//Check validation and save it as CustStreet

			printf("\nEnter Postcode: ");		//Request Postcode
			GetValidatedString(Customers[*CustRecords].CustPostCode, 1, MAX_POST - 1);	//Check validation and save it as CustPostCode

			printf("\nEnter the Customers Telephone Number: "); //Request Telephone Number
			scanf_s("%d", &TelephoneNum);
			fflush(stdin);

			Customers[*CustRecords].CustTelephone = TelephoneNum;

			printf("\nEnter the Customers Email Address: ");		//Request Email Address
			GetValidatedString(Customers[*CustRecords].CustEmail, 1, MAX_EMAIL - 1);	//Check validation and save it as CustEmail

			printf("\nIs the Customer a Member? (Y OR N): ");		//Check if customer is a Member
			Customers[*CustRecords].CustMember = GetValidatedYesOrNo();	//Check validation and save it in CustMember

		}
		(*CustRecords)++;

		// Add another?
		AddAnother = 'N';
		if (*CustRecords < MAX_NUM_RECORDS)
		{
			printf("\n Do you want to add another record (Y/N) ? ");
			AddAnother = GetValidatedYesOrNo();

			if (AddAnother == 'Y' || AddAnother == 'y')
			{
				ShowMainMenu();
				printf("1\n");
			}
		}
		else
		{
			printf("\nThe catalogue is full. You cannot add another record.");		//If Maximum number of Customers is met
			Pause();
		}
	} while (AddAnother == 'Y' || AddAnother == 'y');
}

/**********************************************************************************************
* Function Name: EditCustomer()
*
* Function Description:
*  - allow user to edit customer, allow update/change Customer detail.
*
* User-interface variables:-
*		*OUT (Return values):
*			- N/A
*		*IN (Value Parameters):
*			- N/A
*		*IN and OUT (Reference Parameters):
*			- struct CUSTRECORDS Customer[], int CustRecords
*
* History [Date (Author): Description)]:-
*   01/05/2017 (639022)  : Created
**********************************************************************************************/
void EditCustomer(struct CUSTRECORDS Customers[], int CustRecords)
{
	int i = 0;
	int CustID = 0;
	int UpdateChoice = 0;
	int TelephoneNum;


	if (CustRecords == 0)
	{
		printf("\n\nThere are no Customers to display\n\n");		//If there are no Customers to display
	}
	else
	{

		printf("\n\n                      All Customer Details\n");		//Display table headers
		printf("                      --------------------\n\n");
		printf("\n%-3s %-16s %-16s %-9s %-31s", "ID", "First Name", "Last Name", "House Num", "Street");
		printf("\n%-3s %-16s %-16s %-9s %-31s", "---", "----------", "---------", "---------", "------");
		;

		for (i = 0; i < CustRecords; i++)
		{
			printf("\n%003d %-16s %-16s %-3d       %-31s", Customers[i].CustomerID, Customers[i].CustFirstName, Customers[i].CustLastName, Customers[i].CustHouseNum, Customers[i].CustStreet);
		}

		printf("\n\n\n%-8s % -11s % -31s % -6s", "Postcode", "Telephone", "Email", "Member");
		printf("\n%-8s % -11s % -31s % -6s", "--------", "---------", "-----", "------");

		for (i = 0; i < CustRecords; i++)
		{
			printf("\n%-7s  %-11d %-31s %-1c", Customers[i].CustPostCode, Customers[i].CustTelephone, Customers[i].CustEmail, Customers[i].CustMember);
		}


		printf("\n\nEnter the Customers ID: ");	//Ask user which Customers record they want to update
		CustID = GetValidatedInteger(1, CustRecords) - 1; // Array index // Check for validation 

		system("cls");  // NB Not ANSCII-C compliant (Windows-specific)
		printf("\n%-3s %-16s %-16s %-9s %-31s", "ID", "First Name", "Last Name", "House Num", "Street");
		printf("\n%-3s %-16s %-16s %-9s %-31s", "---", "----------", "---------", "---------", "------");
		printf("\n%003d %-16s %-16s %-3d       %-31d", Customers[CustID].CustomerID, Customers[CustID].CustFirstName, Customers[CustID].CustLastName, Customers[CustID].CustHouseNum, Customers[CustID].CustStreet);
		printf("\n\n\n%-8s % -11s % -31s % -6s", "Postcode", "Telephone", "Email", "Member");
		printf("\n%-8s % -11s % -31s % -6s", "--------", "---------", "-----", "------");
		printf("\n%-7s  %-11d %-31s %-1c", Customers[CustID].CustPostCode, Customers[CustID].CustTelephone, Customers[CustID].CustEmail, Customers[CustID].CustMember);


		do
		{

			CustUpdateMenu();	//Menu with update choices
			UpdateChoice = GetValidatedInteger(1, 8);


			switch (UpdateChoice) // What the user chooses
			{
			case 1:
				printf("\n\nPlease enter new Customer First Name: ");		//When selected, request new Customer First Name
				GetValidatedName(Customers[CustID].CustFirstName, 1, MAX_NAME - 1);	//Check validation and save it as First name
				break;
			case 2:
				printf("\n\nPlease enter new Customer Last Name: ");		//When selected, request new Customer Last Name
				GetValidatedName(Customers[CustID].CustLastName, 1, MAX_NAME - 1);	//Check validation and save it as Last name
				break;
			case 3:
				printf("\n\nPlease enter new House Number: ");		//When selected, request new House Number
				Customers[CustID].CustHouseNum = GetValidatedInteger(1, 999);		//Check validation and save it as CustHouseNum
				break;
			case 4:
				printf("\n\nPlease enter new Street: ");		//When selected, request new Street
				GetValidatedName(Customers[CustID].CustStreet, 1, MAX_STREET - 1);	//Check validation and save it as CustStreet
				break;
			case 5:
				printf("\n\nPlease enter new PostCode: ");		//When selected, request new PostCode
				GetValidatedString(Customers[CustID].CustPostCode, 1, MAX_POST - 1);	//Check validation and save it as CustPostCode
				break;
			case 6:
				printf("\nEnter the Customers Telephone Number: "); //Request Telephone Number
				scanf_s("%d", &TelephoneNum);
				fflush(stdin);

				Customers[CustRecords].CustTelephone = TelephoneNum;
				break;
			case 7:
				printf("\n\nPlease enter new Email: ");		//When selected, request new Email
				GetValidatedString(Customers[CustID].CustEmail, 1, MAX_EMAIL - 1);	//Check validation and save it as CustEmail
				break;
			case 8:
				printf("\n\nQuitting Program");		//Quit program and return to Main Menu
				break;
			}
		} while (UpdateChoice != 8);	// Keep looping until 8 is selected
	}

	Pause();
}

/**********************************************************************************************
* Function Name: CustUpdateMenu()
*
* Function Description:
*  - display add/edit Customer Update menu
*
* User-interface variables:-
*		*OUT (Return values):
*			- N/A
*		*IN (Value Parameters):
*			- NA
*		*IN and OUT (Reference Parameters):
*			- N/A
*
* History [Date (Author): Description)]:-
*   01/05/2017 (639022)  : Created
**********************************************************************************************/
void CustUpdateMenu()
{
	//Update menu for Edit Customer
	printf("\n\n 1. First Name");
	printf("\n 2. Last Name");
	printf("\n 3. House Number");
	printf("\n 4. Street");
	printf("\n 5. PostCode");
	printf("\n 6. Telephone");
	printf("\n 7. Email");
	printf("\n 8. Quit");
	printf("\n\nEnter Choice: ");
}

/**********************************************************************************************
* Function Name: void AddRoom()
*
* Function Description:
*  - Allow user to add room(s).
*		- by inputting room name and room price.
*
* User-interface variables:-
*		*OUT (Return values):
*			- N/A
*		*IN (Value Parameters):
*			- int *RoomRecords
*		*IN and OUT (Reference Parameters):
*			- struct ROOM Rooms[], int *RoomRecords
*
* History [Date (Author): Description)]:-
*   01/05/2017 (639020)  : Created
**********************************************************************************************/
void AddRoom(struct ROOM Rooms[], int *RoomRecords)
{
	char AddAnother; // 'Y' or 'N'
	int ID = 0;
	int	i = 0;


	do
	{
		if (*RoomRecords == MAX_NUM_ROOMS)
		{
			printf("\nThe catalogue is full. You cannot add another room."); //Display if there are no records to display in the program
			Pause();
			return;

		}
		else
		{

			for (i = 0; i < *RoomRecords; i++)		//Create an unique ID for each room
			{
				if (ID < Rooms[i].RoomID)
				{
					ID = Rooms[i].RoomID;
				}
			}

			ID++;
			Rooms[*RoomRecords].RoomID = ID;		//Save it as RoomID


			printf("\n\nEnter the Room name: ");		//Request Room name
			GetValidatedName(Rooms[*RoomRecords].RoomName, 1, MAX_NAME - 1);	//Check validation and save it as Room name


			printf("\nEnter the Room cost: %c", POUND_SIGN);		//Request Price for room
			Rooms[*RoomRecords].RoomPrice = GetValidatedInteger(0, 999);	//Check validation and save it as the price for the room
		}

		(*RoomRecords)++;


		// Add another?
		AddAnother = 'N';
		if (*RoomRecords < MAX_NUM_ROOMS)
		{
			printf("\nDo you want to add another room (Y/N) ? ");
			AddAnother = GetValidatedYesOrNo(); //Validation

			if (AddAnother == 'Y' || AddAnother == 'y')
			{
				ShowMainMenu();
				printf("4\n");
			}
		}
		else
		{
			printf("\nThe catalogue is full. You cannot add another record.");		//If Maximum number of record is met
			Pause();
		}
	} while (AddAnother == 'Y' || AddAnother == 'y');
}


/**********************************************************************************************
* Function Name: void EditRoom()
*
* Function Description:
*  - Allow user to add room(s).
*		- by inputting room name and room price.
*
* User-interface variables:-
*		*OUT (Return values):
*			- N/A
*		*IN (Value Parameters):
*			- int *RoomRecords
*		*IN and OUT (Reference Parameters):
*			- struct ROOM Rooms[], int *RoomRecords
*
* History [Date (Author): Description)]:-
*   01/05/2017 (639020)  : Created
**********************************************************************************************/
void EditRoom(struct ROOM Rooms[], int RoomRecords)
{

	int i = 0;
	int SelectID = 0;
	int UpdateChoice = 0;


	if (RoomRecords == 0)
	{
		printf("\n\nThere are no rooms to display\n\n");		//If there are no rooms to display
	}
	else
	{

		printf("\n\n%-8s %-16s %-7s", "Room ID.", "Room Name", "Price");			//Display all the rooms for user to select from in a table format
		printf("\n%-8s %-16s%-7s", "--------", "---------", "-------");


		for (i = 0; i < RoomRecords; i++)
		{
			printf("\n%003d      %-16s%c%-0.2f", Rooms[i].RoomID, Rooms[i].RoomName, POUND_SIGN, Rooms[i].RoomPrice);
		}


		printf("\n\nEnter the Room ID: ");	//Ask user which room record they want to update
		SelectID = GetValidatedInteger(1, RoomRecords) - 1; // Array index // Check for validation 

		system("cls");  // NB Not ANSCII-C compliant (Windows-specific)
		printf("\n\n%-8s %-16s %-7s", "Room ID.", "Room Name", "Price");
		printf("\n%-8s %-16s%-7s", "--------", "---------", "-------");		//Display selected rooms information in a table format
		printf("\n%003d      %-16s%c%-0.2f", Rooms[SelectID].RoomID, Rooms[SelectID].RoomName, POUND_SIGN, Rooms[SelectID].RoomPrice);


		do
		{

			ShowRoomEditMenu();	//Menu with update choices
			UpdateChoice = GetValidatedInteger(1, 3);


			switch (UpdateChoice) // What the user chooses
			{
			case 1:
				printf("\n\nPlease enter new room name: ");		//When selected, request new Room Name
				GetValidatedName(Rooms[SelectID].RoomName, 1, MAX_NAME - 1);	//Check validation and save it to that ID
				break;
			case 2:
				printf("\n\nPlease enter new room price: ");		//When selected, request new Room Price
				Rooms[SelectID].RoomPrice = GetValidatedInteger(0, 999);		//Check validation and save it to that ID
				break;
			case 3:
				printf("\n\nReturning to edit menu...");		//return to edit menu
				break;
			}
		} while (UpdateChoice != 3);	// Keep looping until 3 is selected
	}

	Pause();
}


void ShowRoomEditMenu()
{
	printf("\n\n\n Choose what you want to update\n ------------------------------");	//Options for the user to choose from
	printf("\n  1. Room Name");
	printf("\n  2. Room Price");
	printf("\n  3. Quit");
	printf("\n\n  Enter your choice: ");
}

/**********************************************************************************************
* Function Name: void DisplayAllCustomer()
*
* Function Description:
*  - displays all the customers from the database
*
* User-interface variables:-
*		*OUT (Return values):
*			- N/A
*		*IN (Value Parameters):
*			- N/A
*		*IN and OUT (Reference Parameters):
*			- struct CUSTRECORDS Customers[], int CustRecords
*
* History [Date (Author): Description)]:-
*   01/05/2017 (639022)  : Created
**********************************************************************************************/
void DisplayAllCustomer(struct CUSTRECORDS Customers[], int *CustRecords)
{
	int i = 0;

	if (*CustRecords == 0)
	{
		printf("\n\nThere are no records to display\n\n");	//If there are no customers to diaplay
	}
	else
	{

		printf("\n\n                      All Customer Details\n");		//Display table headers
		printf("                      --------------------\n\n");
		printf("\n%-3s %-16s %-16s %-9s %-31s", "ID", "First Name", "Last Name", "House Num", "Street");
		printf("\n%-3s %-16s %-16s %-9s %-31s", "---", "----------", "---------", "---------", "------");

		// Display all the records
		for (i = 0; i < *CustRecords; i++)
		{
			printf("\n%003d %-16s %-16s %-3d       %-31s", Customers[i].CustomerID, Customers[i].CustFirstName, Customers[i].CustLastName, Customers[i].CustHouseNum, Customers[i].CustStreet);
		}
		// Display on a new line
		printf("\n\n\n%-8s % -11s % -31s % -6s", "Postcode", "Telephone", "Email", "Member");
		printf("\n%-8s % -11s % -31s % -6s", "--------", "---------", "-----", "------");

		for (i = 0; i < *CustRecords; i++)
		{
			printf("\n%-7s  %11d %-31s %-1c", Customers[i].CustPostCode, Customers[i].CustTelephone, Customers[i].CustEmail, Customers[i].CustMember);
		}

	}


	Pause();
}

/**********************************************************************************************
* Function Name: void DisplayAllCustomer()
*
* Function Description:
*  - displays selected customers from the database, from entering the CustomerID
*
* User-interface variables:-
*		*OUT (Return values):
*			- N/A
*		*IN (Value Parameters):
*			- N/A
*		*IN and OUT (Reference Parameters):
*			- struct CUSTRECORDS Customers[], int CustRecords
*
* History [Date (Author): Description)]:-
*   01/05/2017 (639022)  : Created
**********************************************************************************************/
void DisplaySelectedCustomer(struct CUSTRECORDS Customers[], int *CustRecords)
{
	int i = 0;
	int ReqID;


	if (*CustRecords == 0)
	{
		printf("\n\nThere are no records to display\n\n");		//If there are no Customers to display
	}
	else
	{
		printf("\nEnter customer ID (%d - %d): ", MIN_LEN_ID, *CustRecords);	// Request CustomerID
		ReqID = GetValidatedInteger(MIN_LEN_ID, *CustRecords);				// Check validation for CustomerID

		for (i = 0; i < *CustRecords; i++)
		{
			if (Customers[i].CustomerID == ReqID)
			{
				printf("\n%-3s %-16s %-16s %-9s %-31s", "ID", "First Name", "Last Name", "House Num", "Street");
				printf("\n%-3s %-16s %-16s %-9s %-31s", "---", "----------", "---------", "---------", "------");
				printf("\n%003d %-16s %-16s %-3d       %-31s", Customers[i].CustomerID, Customers[i].CustFirstName, Customers[i].CustLastName, Customers[i].CustHouseNum, Customers[i].CustStreet);
				printf("\n\n\n%-8s % -11s % -31s % -6s", "Postcode", "Telephone", "Email", "Member");
				printf("\n%-8s % -11s % -31s % -6s", "--------", "---------", "-----", "------");
				printf("\n%-7s  %-11d %-31s %-1c", Customers[i].CustPostCode, Customers[i].CustTelephone, Customers[i].CustEmail, Customers[i].CustMember);
			}
		}

	}

	Pause();
}


/**********************************************************************************************
* Function Name: void DisplayAllRoom()
*
* Function Description:
*  - Allow user to add room(s).
*		- by inputting room name and room price.
*
* User-interface variables:-
*		*OUT (Return values):
*			- N/A
*		*IN (Value Parameters):
*			- int *RoomRecords
*		*IN and OUT (Reference Parameters):
*			- struct ROOM Rooms[], int *RoomRecords
*
* History [Date (Author): Description)]:-
*   01/05/2017 (639020)  : Created
**********************************************************************************************/
void DisplayAllRooms(struct ROOM Rooms[], int *RoomRecords)
{
	int i = 0;


	if (*RoomRecords == 0)
	{
		printf("\n\nThere are no rooms to display\n\n");	//If there are no rooms to diaplay
	}
	else
	{

		printf("\n\n%-8s %-16s %-7s", "Room ID.", "Room Name", "Price");	// Display table headers
		printf("\n%-8s %-16s%-7s", "--------", "---------", "-------");


		for (i = 0; i < *RoomRecords; i++)
		{
			printf("\n%003d      %-16s%c%-0.2f", Rooms[i].RoomID, Rooms[i].RoomName, POUND_SIGN, Rooms[i].RoomPrice);	// Display all records 
		}
	}


	Pause();
}

/**********************************************************************************************
* Function Name: void DisplaySelectedRoom()
*
* Function Description:
*  - Allow user to add room(s).
*		- by inputting room name and room price.
*
* User-interface variables:-
*		*OUT (Return values):
*			- N/A
*		*IN (Value Parameters):
*			- int *RoomRecords
*		*IN and OUT (Reference Parameters):
*			- struct ROOM Rooms[], int *RoomRecords
*
* History [Date (Author): Description)]:-
*   01/05/2017 (639020)  : Created
**********************************************************************************************/
void DisplaySelectedRoom(struct ROOM Rooms[], int *RoomRecords)
{
	int i = 0;
	int ReqID;


	if (*RoomRecords == 0)
	{
		printf("\n\nThere are no rooms to display\n\n");		//If there are no rooms to display
	}
	else
	{
		printf("\nEnter Room ID (%d - %d): ", MIN_LEN_ID, *RoomRecords);	// Request RoomID
		ReqID = GetValidatedInteger(MIN_LEN_ID, *RoomRecords);				// Check validation for RoomID

		for (i = 0; i < *RoomRecords; i++)
		{
			if (Rooms[i].RoomID == ReqID)
			{
				printf("\n\n%-8s %-16s %-7s", "Room ID.", "Room Name", "Price");	// Display table headers
				printf("\n%-8s %-16s%-7s", "--------", "---------", "-------");
				printf("\n%003d      %-16s%c%-0.2f", Rooms[i].RoomID, Rooms[i].RoomName, POUND_SIGN, Rooms[i].RoomPrice); // Display selected record
			}
		}

	}

	Pause();
}

/**********************************************************************************************
* Function Name: void AddEditFacilities()
*
* Function Description:
*  - Menu Option, carry out user inputted option
*
* User-interface variables:-
*		*OUT (Return values):
*			- N/A
*		*IN (Value Parameters):
*			- N/A
*		*IN and OUT (Reference Parameters):
*			- struct FACILITY Facility[], int FacRecords
*
* History [Date (Author): Description)]:-
*   01/05/2017 (639558)  : Created
**********************************************************************************************/
void AddEditFacilities(struct FACILITY Facility[], int *FacRecords)
{
	int MenuChoice = 0;
	do
	{
		AddEditFacilitiesMenu();
		MenuChoice = GetValidatedInteger(1, 3);
		switch (MenuChoice)
		{
		case 1:
			AddFacility(Facility, FacRecords);
			break;
		case 2:
			EditFacility(Facility, FacRecords);
			break;
		case 3:
			break;
		}
	} while (MenuChoice != 3);
	Pause();
}

/**********************************************************************************************
* Function Name: void AddFacility()
*
* Function Description:
*  - allow user to add a facility
*
* User-interface variables:-
*		*OUT (Return values):
*			- N/A
*		*IN (Value Parameters):
*			- N/A
*		*IN and OUT (Reference Parameters):
*			- struct FACILITY Facility[], int FacRecords
*
* History [Date (Author): Description)]:-
*   01/05/2017 (639558)  : Created
**********************************************************************************************/
void AddFacility(struct FACILITY Facility[], int *FacRecords)
{
	char AddAnother; // 'Y' or 'N'
	int ID = 0;
	int	i = 0;
	const int cTrue = 1, cFalse = 0;

	do
	{
		if (*FacRecords == MAX_NUM_FACILITY)
		{
			printf("\nThe catalogue is full. You cannot add another Facility.");
			Pause();
			return;
		}
		else
		{
			if (*FacRecords == 0)
			{
				ID = 0;
			}
			else
			{
				for (i = 0; i < *FacRecords; i++)		//Create an unique ID for each facility
				{
					if (ID < Facility[i].FacID)
					{
						ID = Facility[i].FacID;
					}
				}

				ID++;
				Facility[*FacRecords].FacID = ID;		//Save it as FacID

			}
			printf("\nEnter Facility's Name: ");
			GetValidatedName(Facility[*FacRecords].FacName, MIN_NAME, MAX_NAME - 1);

			(*FacRecords)++;


			// Add another?
			AddAnother = 'N';
			if (*FacRecords < MAX_NUM_FACILITY)
			{
				printf("\nDo you want to add another facility (Y/N) ? ");
				AddAnother = GetValidatedYesOrNo();

				if (AddAnother == 'Y' || AddAnother == 'y')
				{
					void AddEditFacilitiesMenu();
				}
			}
			else
			{
				printf("\nThe catalogue is full. You cannot add another record.");		//If Maximum number of record is met
				Pause();
			}
		}
	} while (AddAnother == 'y' || AddAnother == 'Y');
}

/**********************************************************************************************
* Function Name: EditFacility()
*
* Function Description:
*  - allow user to edit facility, allow update/change facility name
*
* User-interface variables:-
*		*OUT (Return values):
*			- N/A
*		*IN (Value Parameters):
*			- N/A
*		*IN and OUT (Reference Parameters):
*			- struct FACILITY, int FacReccords
*
* History [Date (Author): Description)]:-
*   01/05/2017 (639558)  : Created
**********************************************************************************************/
void EditFacility(struct FACILITY Facility[], int *FacRecords)
{
	int ID = 0, MatchFound = 0, i = 0;
	const int cTrue = 1, cFalse = 0;
	if (*FacRecords == 0)
	{
		printf("\nThere are no facilities to display.\nPlease Add a Facility before Returning");
		Pause();
	}
	else
	{
		do
		{
			MatchFound = cFalse;
			for (i = 0; i < *FacRecords; i++)
			{
				if (i == 0)
				{
					printf("\n\n%-11s %-16s", "Facility ID", "Facility Name");
					printf("\n%-8s %-16s", "-----------", "-------------");
				}
				printf("\n%003d         %-16s", Facility[i].FacID + 1, Facility[i].FacName);
			}
			printf("\n\nEnter Facility ID to Change: ");
			ID = GetValidatedInteger(1, *FacRecords);
			for (i = 0; i < *FacRecords; i++)
			{
				if (ID == Facility[i].FacID + 1)
				{
					MatchFound = cTrue;
				}
			}

			if (MatchFound == cTrue)
			{
				printf("\n\nEnter New Facility Name: ");
				GetValidatedName(Facility[ID - 1].FacName, MIN_NAME, MAX_NAME - 1);
			}
			Pause();
		} while (MatchFound = cFalse);
	}

}

/**********************************************************************************************
* Function Name: AddEditFacilitiesMenu()
*
* Function Description:
*  - display add/edit facilities menu
*
* User-interface variables:-
*		*OUT (Return values):
*			- N/A
*		*IN (Value Parameters):
*			- NA
*		*IN and OUT (Reference Parameters):
*			- N/A
*
* History [Date (Author): Description)]:-
*   01/05/2017 (639558)  : Created
**********************************************************************************************/
void AddEditFacilitiesMenu()
{
	system("cls");
	printf("\n Facility Menu\n -------------");
	printf("\n  1. Add Facility");
	printf("\n  2. Edit Facility");
	printf("\n  3. Main Menu");
	printf("\n\n  Enter your choice: ");
}

/**********************************************************************************************
* Function Name: void DisplayPastBooking()
*
* Function Description:
*  - display past booking within the database
*
* User-interface variables:-
*		*OUT (Return values):
*			- N/A
*		*IN (Value Parameters):
*			- N/A
*		*IN and OUT (Reference Parameters):
*			- struct BOOKING Bookings[], int BookingRecords, struct ROOM Rooms[], int RoomRecords
*
* History [Date (Author): Description)]:-
*   01/05/2017 (639558)  : Created
**********************************************************************************************/
void DisplayPastBookings(struct BOOKING Bookings[], int *BookingRecords, struct ROOM Rooms[], int *RoomRecords)
{
	int i = 0, RoomID, j = 0;

	if (*BookingRecords == 0)
	{
		printf("\n\nThere are no Booking to display\n\n");	//If there are no records to diaplay
	}
	else
	{
		printf("\n\n%-10s %-11s   %-16s(%c)%-10s %-10s %-9s", "Booking ID", "Customer ID", "Room Name", POUND_SIGN, "Booking Price", "Start Time", "End Time");
		printf("\n%-10s %-11s   %-9s       %-16s %-10s %-8s", "----------", "-----------", "---------", "----------------", "----------", "--------");




		for (i = 0; i < *BookingRecords; i++)
		{
			RoomID = 0;
			for (j = 0; j < *RoomRecords; j++)
			{
				if (Bookings[i].RoomID == Rooms[j].RoomID)
				{
					RoomID = j;
				}
			}
			printf("\n%03d        %03d           %-16s      %0.2f          %2d        %2d", Bookings[i].BookingID, Bookings[i].CustomerID, Rooms[RoomID].RoomName, Bookings[i].BookingPrice, Bookings[i].BookingStartTime, Bookings[i].BookingEndTime);
		}


		printf("\n\n%-10s %-17s", "Booking ID", "Facility Booked");
		printf("\n%-10s %-48s", "----------", "---------------");

		for (i = 0; i < *BookingRecords; i++)
		{
			RoomID = 0;
			for (j = 0; j < *RoomRecords; j++)
			{
				if (Bookings[i].RoomID == Rooms[j].RoomID)
				{
					RoomID = j;
				}
			}
			printf("\n%03d        %-48s", Bookings[i].BookingID, Bookings[i].FacilityBooked);
		}
	}

	Pause();
}

void Pause()
{
	printf("\n\n\n\nPress the ENTER key to continue.");
	getchar();
	return(0);
}

/**********************************************************************************************
* Function Name: int GetValidatedInteger(int Min, int Max)
*
* Function Description:
*  - Gets user-inputted integer value. Validated for data type & value (Min->Max).
*
* User-interface variables:-
*		*OUT (Return values):
*			- int: User-inputted validated integer value in the range Min -> Max.
*		*IN (Value Parameters):
*			- int Min: Minimum valid value
*			- int Max: Maximum valid value
*		*IN and OUT (Reference Parameters):
*			- NONE
*
* History [Date (Author): Description)]:-
*   01/01/2010 (H Fergus)  : Created
**********************************************************************************************/
int GetValidatedInteger(int Min, int Max)
{
	// Local Constants:
	const int cTrue = 1, cFalse = 0;

	// Input Variables:
	float Input = 0;

	// Intermediate Variables:
	int ItemRead = cFalse;
	int Valid = cFalse;

	// Output Variables:
	//None

	do
	{

		ItemRead = scanf_s("%f", &Input);
		fflush(stdin);

		if (ItemRead == cFalse)
		{
			printf("Invalid - must be a number! Please try again (%d-%d): ", Min, Max);
		}
		else if (Input != (int)Input)
		{
			printf("Invalid - must be an integer! Please try again (%d-%d): ", Min, Max);
		}

		else if ((Input < Min) || (Input > Max))
		{
			printf("Invalid - out-of-range! Please try again (%d-%d): ", Min, Max);
		}
		else
		{
			Valid = cTrue;
		}
	} while (Valid == cFalse);

	return((int)Input);
}

/**********************************************************************************************
* Function Name: char GetValidatedYesorNo()
*
* Function Description:
*  - validate y oe n char
*
* User-interface variables:-
*		*OUT (Return values):
-				string: User-inputted validated char
*		*IN (Value Parameters):
*			- user inputted char
*		*IN and OUT (Reference Parameters):
*			- n/a
*
* History [Date (Author): Description)]:-
*    (undated)(City of Brostol ID: 639558, (2016) Program Design and Implementation, Student ID:639558, Year of Study:0, module: UFCE3G-20-0 Program Design and Implementation)
)  : Created
**********************************************************************************************/
char GetValidatedYesOrNo()
{
	const char cTrue = 1, cFalse = 0;
	char Valid = cFalse;
	char Input;



	do
	{
		scanf_s("%c", &Input);
		fflush(stdin);

		if (Input == 'y' || Input == 'N' || Input == 'n' || Input == 'Y')
		{
			Valid = cTrue;
		}
		else
		{
			printf("\nPlease Enter Y or N to continue: ");
		}
	} while (Valid == cFalse);
	return(Input);
}

/**********************************************************************************************
* Function Name: void GetValidatedName()
*
* Function Description:
*  - validate letters string
*
* User-interface variables:-
*		*OUT (Return values):
			- string: User-inputted validated string
*		*IN (Value Parameters):
*			- int Min: Minimum valid value
*			- int Max: Maximum valid value
*		*IN and OUT (Reference Parameters):
*			- n/a
*
* History [Date (Author): Description)]:-
*    (undated)(City of Brostol ID: 63955, (2016) Program Design and Implementation, Student ID:639558, Year of Study:0, module: UFCE3G-20-0 Program Design and Implementation)
)  : Created
**********************************************************************************************/
void GetValidatedName(char ValidatedString[], int MinLength, int MaxLength)
{
	const cTrue = 1, cFalse = 0;
	char Success = cTrue;
	int Found = 1;

	do
	{
		Found = 1;
		Success = GetValidatedString(ValidatedString, MinLength, MaxLength);
		if (Success == cTrue)
		{
			for (int i = 0; i < strlen(ValidatedString); i++)
			{
				if (isalpha(ValidatedString[i]))
				{
				}
				else
				{
					if (ValidatedString[i] == ' ') //ASCII 45
					{
					}
					else
					{
						Found = 0;
					}
				}
			}
			if (Found == 0)
			{
				printf("\nInvalid! One or more character(s) entered is not a letter: ");
				Success = cFalse;
			}
		}
	} while (Success == cFalse);
}

/**********************************************************************************************
* Function Name: char GetValidatedString()
*
* Function Description:
*  - validate user-inputted string (with in the min and max range)
*
* User-interface variables:-
*		*OUT (Return values):
*			- string: User-inputted validated string
*		*IN (Value Parameters):
*			- int Min: Minimum valid value
*			- int Max: Maximum valid value
*		*IN and OUT (Reference Parameters):
*			- NONE
*
* History [Date (Author): Description)]:-
*   September 2016 (Fergus, H. (2016). Beginners C Programming. 1st ed. Bristol: hilary.fergus@cityofbristol.ac.uk)  : Created
**********************************************************************************************/
char GetValidatedString(char ValidatedString[], int MinLength, int MaxLength)
{
	const char cFalse = 0, cTrue = 1;
	char Success = cFalse;
	char YesorNo;

	char Input[255];

	size_t InputArrayMaxLen = sizeof(Input)-2;
	size_t Length;

	if (MaxLength > (int)InputArrayMaxLen)
	{
		printf("\n\nRequired maximum length for called GetValidatedString() function "
			"\ncannot exceed %d characters", (int)InputArrayMaxLen);
		printf("\nData not read. Please contact developer.");
		Pause();
		return(Success);
	}
	do
	{
		do
		{

			YesorNo = 'Y';
			Input[InputArrayMaxLen + 1] = 'z';
			Input[InputArrayMaxLen] = 'z';

			fgets(Input, sizeof(Input), stdin);
			fflush(stdin);

			if ((Input[InputArrayMaxLen + 1] == '\0') && (Input[InputArrayMaxLen] != '\n'))
			{
				printf("\n\nRequired maximum length for called GetValidatedString() function"
					"\ncannot exceed %d characters", InputArrayMaxLen);

				printf("\n\nDo you wish to try again (Y/N)?: ");
				YesorNo = GetValidatedYesOrNo();

				if (YesorNo == 'N')
				{
					printf("Data not read. Please contact developer.");
					Pause();
					return(Success);
				}
				else
				{
					printf("\nRe-enter(%d - %d characters): ", MinLength, MaxLength);
				}
			}

			else
			{
				YesorNo = 'N';
			}

		} while (YesorNo == 'Y');

		Length = strlen(Input) - 1;
		Input[Length] = '\0';

		if ((Length < (size_t)MinLength) || (Length >(size_t)MaxLength))
		{
			printf("Invalid! Please try again (Length %d-%d): ", MinLength, MaxLength);
		}
		else
		{
			Success = cTrue;
		}
	} while (Success == cFalse);

	strcpy_s(ValidatedString, MaxLength + 1, Input);

	return(Success);
}

/**********************************************************************************************
* Function Name: void WriteToFile()
*
* Function Description:
*  - write all struct to file
*
* User-interface variables:-
*		*OUT (Return values):
*			- struct CUSTRECORDS, STRUCT ROOM, STRUCT FACILITY, STRUCT BOOKING, RoomRecords, CustRecords, FacRecords , BookingRecords
*		*IN (Value Parameters):
*			- iN/A
*		*IN and OUT (Reference Parameters):
*			- struct CUSTRECORDS, STRUCT ROOM, STRUCT FACILITY, STRUCT BOOKING, RoomRecords, CustRecords, FacRecords , BookingRecords
*
* History [Date (Author): Description)]:-
*   01/05/2017 (639558)  : Created
**********************************************************************************************/
void WriteToFile(struct CUSTRECORDS Customers[], struct ROOM Rooms[], struct FACILITY Facility[], struct BOOKING Bookings[], int *RoomRecords, int *CustRecords, int *FacRecords, int *BookingRecords)
{
	FILE *custfile;
	FILE *roomfile;
	FILE *facfile;
	FILE *bookingfile;
	
	int i = 0;

	fopen_s(&custfile, "Customer Database", "wb");
	for (i = 0; i < *CustRecords; i++)
	{
		fwrite(&Customers[i], sizeof(struct CUSTRECORDS), 1, custfile);
	}
	fclose(custfile);

	fopen_s(&roomfile, "Room Database", "wb");;
	for (i = 0; i < *RoomRecords; i++)
	{
		fwrite(&Rooms[i], sizeof(struct ROOM), 1, roomfile);
	}
	fclose(roomfile);

	fopen_s(&bookingfile, "Booking Database", "wb");
	for (i = 0; i < *BookingRecords; i++)
	{
		fwrite(&Bookings[i], sizeof(struct BOOKING), 1, bookingfile);
	}
	fclose(bookingfile);

	fopen_s(&facfile, "Facility Database", "wb");
	for (i = 0; i < *FacRecords; i++)
	{
		fwrite(&Facility[i], sizeof(struct FACILITY), 1, facfile);
	}
	fclose(facfile);


}

/**********************************************************************************************
* Function Name: ClearStruct()
*
* Function Description:
*  - clear all struct for file reading 
*
* User-interface variables:-
*		*OUT (Return values):
*			- struct CUSTRECORDS, STRUCT ROOM, STRUCT FACILITY, STRUCT BOOKING
*		*IN (Value Parameters):
*			- NA
*		*IN and OUT (Reference Parameters):
*			-  struct CUSTRECORDS, STRUCT ROOM, STRUCT FACILITY, STRUCT BOOKING
*
* History [Date (Author): Description)]:-
*   01/05/2017 (639558)  : Created
**********************************************************************************************/
void ClearStruct(struct CUSTRECORDS Customers[], struct ROOM Rooms[], struct FACILITY Facility[], struct BOOKING Bookings[])
{
	int i = 0;
	for (i = 0; i <MAX_NUM_RECORDS; i++)
	{
		memset(Customers[i].CustFirstName, ' ', sizeof(Customers[i].CustFirstName));
		strcpy_s(Customers[i].CustFirstName, sizeof(Customers[i].CustFirstName), "");
		memset(Customers[i].CustLastName, ' ', sizeof(Customers[i].CustLastName));
		strcpy_s(Customers[i].CustLastName, sizeof(Customers[i].CustLastName), "");
		memset(Customers[i].CustPostCode, ' ', sizeof(Customers[i].CustPostCode));
		strcpy_s(Customers[i].CustPostCode, sizeof(Customers[i].CustPostCode), "");
		memset(Customers[i].CustEmail, ' ', sizeof(Customers[i].CustEmail));
		strcpy_s(Customers[i].CustEmail, sizeof(Customers[i].CustEmail), "");

		memset(Customers[i].CustStreet, ' ', sizeof(Customers[i].CustStreet));
		strcpy_s(Customers[i].CustStreet, sizeof(Customers[i].CustStreet), "");
		Customers[i].CustHouseNum = 0;
		Customers[i].CustTelephone = 0;
		Customers[i].CustMember = 0;
		Customers[i].CustomerID = 0;
	}

	for (i = 0; i < MAX_NUM_ROOMS; i++)
	{
		memset(Rooms[i].RoomName, ' ', sizeof(Rooms[i].RoomName));
		strcpy_s(Rooms[i].RoomName, sizeof(Rooms[i].RoomName), "");

		Rooms[i].RoomPrice = 0;
	}

	for (i = 0; i < MAX_NUM_FACILITY; i++)
	{
		memset(Facility[i].FacName, ' ', sizeof(Facility[i].FacName));
		strcpy_s(Facility[i].FacName, sizeof(Facility[i].FacName), "");

		Facility[i].FacID = 0;
	}

	for (i = 0; i < MAX_NUM_BOOKING; i++)
	{
		memset(Bookings[i].BookingDate, ' ', sizeof(Bookings[i].BookingDate));
		strcpy_s(Bookings[i].BookingDate, sizeof(Bookings[i].BookingDate), "");

		Bookings[i].BookingEndTime = 0;
		Bookings[i].BookingStartTime = 0;
		Bookings[i].BookingPrice = 0;
		Bookings[i].BookingID = 0;
		Bookings[i].CustomerID = 0;
		Bookings[i].RoomID = 0;

	}
}


/**********************************************************************************************
* Function Name: int GetValidatedDate)
*
* Function Description:
*  - format for for bookign date (dd/mm.yy)
*
* User-interface variables:-
*		*OUT (Return values):
*			-string User-inputted validated date.
*		*IN (Value Parameters):
*			- n/a
*		*IN and OUT (Reference Parameters):
*			-int user inputted date string
*
* History [Date (Author): Description)]:-
*   01/05/2017 (639558)  : Created
**********************************************************************************************/
void GetValidatedDate(char ValidatedString[])
{
	const int cTrue = 1, cFalse = 0;
	int MatchFound = cTrue;
	char Input[9];
	do
	{
		MatchFound = cTrue;
		printf("\n\nEnter Booking Date (dd/mm/yy): ");
		fgets(Input, sizeof(Input), stdin);
		fflush(stdin);

		if (strlen(Input) == 8)
		{
			if (isdigit(Input[0]))
			{
				if (isdigit(Input[1]))
				{
					if (Input[2] == '/')
					{
						if (isdigit(Input[3]))
						{
							if (isdigit(Input[4]))
							{
								if (Input[5] == '/')
								{
									if (isdigit(Input[6]))
									{
										if (isdigit(Input[7]))
										{
											//Successful Validation
										}
									}
									else
									{
										MatchFound = cFalse;
									}
								}
								else
								{
									MatchFound = cFalse;
								}
							}
							else
							{
								MatchFound = cFalse;
							}
						}
						else
						{
							MatchFound = cFalse;
						}
					}
					else
					{
						MatchFound = cFalse;
					}
				}
				else
				{
					MatchFound = cFalse;
				}
			}
			else
			{
				MatchFound = cFalse;
			}

		}
		else
		{
			printf("\n");
			MatchFound = cFalse;
		}
		if (MatchFound == cFalse)
		{
			printf("\nIncorrect!! Please enter in format (dd/mm/yy): ");
		}
	} while (MatchFound == cFalse);
	strcpy_s(ValidatedString, 9, Input);
}