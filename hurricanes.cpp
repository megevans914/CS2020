// Program #1 – Hurricane Program
// Programmer:  Megan Evans
// Class:  CS 2020, Spring 2025
// Due Date: 2/2/25
// Purpose of program: Create a program that 
// will read data from a file called hurricanes.txt.  
// The data will consist of a city’s name, wind velocity 
//and amount of rain for the hurricanes that occurred in the United States.

#include <iostream>
#include <vector>
#include <fstream>
#include <iomanip>
#include <string>
//global constants
const int MAXCITIES = 50;
using namespace std;

// Prototype (ADD MISSING PROTOTYPES)
void ReadData(vector<string>& city, vector<int>& wind, vector<double>& rain, int& numcities);
void printvectors(vector<string>city, vector<int>wind, vector<double>rain, int numcities);
void ReadData(vector<string>& city, vector<int>& wind, vector<double>& rain, int& numcities);
void SelSort(vector<string>& city, vector<int>& wind, vector<double>& rain, int numcities);
void ViolentWinds(vector<string>city, vector<int>wind, int numcities);
void MajorFlood(vector<string>city, vector<double>rain, int numcities);


//A few more prototypes, note the return types
int Windiestcitypos(vector<string>city, vector<int>wind, int numcities);
double Averagewind(vector<string>city, vector<int>wind, int numcities);
double AverRain(vector<string>city, vector<double>rain, int numcities);


int main()
{
// Declared variables and vectors
	vector<string>city(MAXCITIES);
	vector<int>wind(MAXCITIES);
	vector<double>rain(MAXCITIES);
	int numcities(MAXCITIES);


// call to the functions
	cout << left << fixed << setprecision(1); //sets the decimal place
	
	ReadData(city, wind, rain, numcities);
	SelSort(city, wind, rain, numcities);
	printvectors(city, wind, rain, numcities);
	ViolentWinds(city, wind, numcities);
	MajorFlood(city, rain, numcities); //FIXME: clarify that output is correct and it's >= 2.5 inches and not > 2.5 inches
	int windiestCityPosition = Windiestcitypos(city, wind, numcities);
	Averagewind(city, wind, numcities);
	AverRain(city, rain, numcities); //FIXME: NOT DONE


// output averages and highest
	
	cout << city.at(windiestCityPosition) << " is the windiest city at " << wind.at(windiestCityPosition) << " mph." << endl;
	cout << endl;
	cout << "The average wind is " << Averagewind(city, wind, numcities) << endl;
	cout << "The average rain is " << setprecision(3) << AverRain(city, rain, numcities) << endl;


	system("Pause");
	return 0;
}
//************************************************************************************
//Function: ReadData
//Function to read and fill vectors. The file is opened and closed after filling vectors
//************************************************************************************

void ReadData(vector<string>&city, vector<int>&wind, vector<double>&rain, int& numcities)
{
	ifstream infile; //file variable
	numcities = 0;
	unsigned int i;

	//This code will open the file
	infile.open("hurricanes.txt");
	if (!infile)
	{
		cerr << "Error" << endl;
	}

	//Write a loop to get all of the data from the file and assign it to the proper vectors
	while (!infile.eof()) {
		//for (i = 0; i < MAXCITIES; ++i) {
			getline(infile, city.at(numcities));
			infile >> wind.at(numcities);
			infile >> rain.at(numcities);
			infile.ignore();
			++numcities;
		//}
	}


	infile.close();
}
//************************************************************************************
//Function: printvectors
//Function to print the vectors in tabular form
//************************************************************************************
void printvectors(vector<string>city, vector<int>wind, vector<double>rain, int numcities)
{

	//declare variables
	int i;

	//output stuff
	cout << "The Data file conist of:" << endl;
	cout << setw(15) << "City";
	cout << setw(8) << "Wind";
	cout << setw(5) << "Rain";
	cout << endl;

	cout << setw(15) << "------" << setw(8) << "----" << setw(5) << "-----";
	cout << endl;

	for (i = 0; i < numcities; ++i) {
		cout << setw(15) << city.at(i);
		cout << setw(8) << wind.at(i);
		cout << setw(5) << rain.at(i);
		cout << endl;
	}


}

//************************************************************************************
//Function: Windiestcitypos
//Function to return the vector position of the city with the highest wind speed
//************************************************************************************
int Windiestcitypos(vector<string>city, vector<int>wind, int numcities)
{
	//declare variables
	int i;
	int max = wind.at(0);
	int pos;

	for (i = 0; i < numcities; ++i) {
		if (wind.at(i) > max) {
			max = wind.at(i);
			pos = i;
		}
	}


	return pos;
}
//************************************************************************************
//Function: Averagewind
//Function to return the average wind velocity
//************************************************************************************
double Averagewind(vector<string>city, vector<int>wind, int numcities)
{
	//declare variables
	int i;
	double sum = 0;
	double average;

	//computations
	for (i = 0; i < numcities; ++i) {
		sum += wind.at(i);
	}
	average = sum / numcities;

	
	
	return average;
}

//************************************************************************************
//Function: SelSort
//Function to sort all three vectors by city
//************************************************************************************
void SelSort(vector<string>& city, vector<int>& wind, vector<double>& rain, int numcities) {
	//declare variables
	unsigned int i;
	unsigned int j;
	string tempCity;
	int tempWind;
	double tempRain;
	int lowestAlphaIndex;


	//selection sort
	for (i = 0; i < numcities - 1; ++i) {
		
		//find index of "lowest" (alphabetical) element in city vector
		lowestAlphaIndex = i;
		for (j = i + 1; j < numcities; ++j) {
			if (city.at(j) < city.at(lowestAlphaIndex)) {
				lowestAlphaIndex = j;
			}
		}

		//swap city.at(i) and city.at(lowestAlphaIndex) and also swap the values of the other vectors to match
		tempCity = city.at(i);
		city.at(i) = city.at(lowestAlphaIndex);
		city.at(lowestAlphaIndex) = tempCity;

		tempWind = wind.at(i);
		wind.at(i) = wind.at(lowestAlphaIndex);
		wind.at(lowestAlphaIndex) = tempWind;

		tempRain = rain.at(i);
		rain.at(i) = rain.at(lowestAlphaIndex);
		rain.at(lowestAlphaIndex) = tempRain;

	}

}

//************************************************************************************
//Function: ViolentWinds
//Function to print each city where a hurricane was violent (wind speed at least 110 mph)
//************************************************************************************
void ViolentWinds(vector<string>city, vector<int>wind, int numcities)
{
	//declare variables
	int i;

	//begin output
	cout << endl << endl << "Violent Winds" << endl;

	//loop to find values of cities with violent winds
	for (i = 0; i < numcities; ++i) {
		if (wind.at(i) >= 110) {
			cout << setw(15) << city.at(i) << setw(3) << wind.at(i) << endl;
		}
	}

}


//************************************************************************************
//Function: MajorFlood
//Function to print each city where a hurricane produced a flood (rainfall at least 2.5 inches)
//************************************************************************************
void MajorFlood(vector<string>city, vector <double> rain, int numcities)
{
	//declare variables
	int i;

	//begin output
	cout << endl << "Major Floods" << endl;

	//loop to find values of cities with violent winds
	for (i = 0; i < numcities; ++i) {
		if (rain.at(i) >= 2.5) {
			cout << setw(15) << city.at(i) << setw(3) << rain.at(i) << endl;
		}
	}
	cout << endl;
}


//************************************************************************************
//Function: AverRain
//Function to return the average rainfall
//************************************************************************************
double AverRain(vector<string>city, vector<double>rain, int numcities) {
	//declare variables
	int i;
	double sum = 0;
	double average;

	//computations
	for (i = 0; i < numcities; ++i) {
		sum += rain.at(i);
	}
	average = sum / numcities;

	return average;
}