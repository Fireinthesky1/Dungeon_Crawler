#pragma once
#include <iostream>
#include <windows.h>


//Get a user integer
inline int getUserInputInt(int min, int max)
{
	int input;
	std::cin >> input;
	if (!std::cin || input < min || input > max)
	{
		//Clear the input buffer Call the function
		std::cin.clear();
		std::cin.ignore(INT_MAX, '\n');
		return getUserInputInt(min, max);
	}
	return input;
}



inline std::string getUserInputString()
{
	std::string string;
	std::cin >> string;
	if (!std::cin)
	{
		//Clear the input buffer Call the function
		std::cin.clear();
		std::cin.ignore(INT_MAX, '\n');
		return getUserInputString();
	}
	return string;
}



//Returns the last error as a string
inline std::string GetLastErrorAsString()
{
	//Get the error message ID, if any
	DWORD errorMessageID = ::GetLastError();
	if (errorMessageID == 0)
	{
		return std::string(); //No error message has been recorded
	}

	LPSTR messageBuffer = nullptr;

	//Ask Win32 to give us the the string version of that message ID
	//The parameters we pass in, tell Win32 to creat the buffer that 
	//holds the message for us (because we don't know how long the message string will be)
	size_t size = FormatMessageA(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
		NULL, errorMessageID, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPSTR)&messageBuffer, 0, NULL);

	//Copy the error message into a std::string
	std::string message(messageBuffer, size);

	//Free the Win32's string's buffer
	LocalFree(messageBuffer);

	return message;
}



//Clear the screen
inline void clearScreen(HANDLE currentBuffer)
{	
	COORD topLeft = { 0,0 };
	DWORD cCharsWritten;
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	DWORD dwConSize;



	//Get the number of character cells in the current buffer
	if (!GetConsoleScreenBufferInfo(currentBuffer, &csbi))
	{
		std::cout << "error calling GetConsoleScreenBufferInfo: " << std::endl;
		std::cout << GetLastErrorAsString() << std::endl;
		abort();
	}



	//Calculating the number of cells in the console
	dwConSize = csbi.dwSize.X * csbi.dwSize.Y;



	//Fill the entire screen with blanks
	if (!FillConsoleOutputCharacter(currentBuffer,		//Handle to console Screen Buffer
		(TCHAR)' ',		//Character to write to the buffer
		dwConSize,			//Number of cells to write
		topLeft,			//Coordinate of first cell
		&cCharsWritten))	//Recieve number of characters written
	{
		return;
	}



	//Get the current text attribute
	if (!GetConsoleScreenBufferInfo(currentBuffer, &csbi))
	{
		std::cout << "error calling GetConsoleScreenBufferInfo: " << std::endl;
		std::cout << GetLastErrorAsString() << std::endl;
		abort();
	}



	//set the buffer's attributes accordingly
	if (!FillConsoleOutputAttribute(currentBuffer,		//Handle to console Screen Buffer	
		csbi.wAttributes,	//Character attributes to use
		dwConSize,			//Number of cells to set attribute
		topLeft,			//Coordinates of the first cell
		&cCharsWritten))	//Recieve number of characters written
	{
		return;
	}



	//Put the cursor at its home coordinates
	SetConsoleCursorPosition(currentBuffer, topLeft);
}



inline void clearInputBuffer()
{
	std::cin.clear();
	std::cin.ignore(INT_MAX, '\n');
}



inline int generateRandomNumber(int leftBound, int rightBound)
{
	return ((rand() % (rightBound - leftBound)) + leftBound);
}



inline bool successfulAction(int bonus, int difficulty)
{
	int roll = rand() % 21;
	roll += bonus;
	if (roll >= difficulty)
		return true;
	else
		return false;
}



inline void launchAudioFiles(LPCWSTR sound)
{
	PlaySound(sound, NULL, SND_SYNC);
}