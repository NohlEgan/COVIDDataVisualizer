// Nohl Egan
// this class contains the main function, which when used will use data from a specified file to create a chart based on a field specified by the user
// October 7, 2020

#include "iostream"
#include "fstream"
#include "array"
#include "algorithm"
#include "cmath"
#include "dataRecord.h"

using namespace std;


// sort functions to be used to sort by any of the six statistical counts
bool sortNewConfirmedCases(dataRecord i, dataRecord j){
	return i.getNewConfirmedCases() < j.getNewConfirmedCases();
}

bool sortNewDeaths(dataRecord i, dataRecord j){
	return i.getNewDeaths() < j.getNewDeaths();
}

bool sortNewRecoveredCases(dataRecord i, dataRecord j){
	return i.getNewRecoveredCases() < j.getNewRecoveredCases();
}

bool sortTotalConfirmedCases(dataRecord i, dataRecord j){
	return i.getTotalConfirmedCases() < j.getTotalConfirmedCases();
}

bool sortTotalDeaths(dataRecord i, dataRecord j){
	return i.getTotalDeaths() < j.getTotalDeaths();
}

bool sortTotalRecoveredCases(dataRecord i, dataRecord j){
	return i.getTotalRecoveredCases() < j.getTotalRecoveredCases();
}


int main () {
	// this variable is the container for all the country records
	dataRecord countryRecords[186];
	int countryCount = 0;
	
	string line;
	string fileName;
	ifstream file;
	cout << "Enter the file name: ";
	cin >> fileName;
	file.open(fileName);
	
	// checking to make sure the file name given is valid
	if (!file) {
		cout << "Exception occured while reading in file" << endl;
		exit(0);
	}
	
	// taking input line from line from the summary file
	while (getline(file, line)) {
		string countryName;
		string countryCode;
		int newConfirmedCases;
		int newDeaths;
		int newRecoveredCases;
		int totalConfirmedCases;
		int totalDeaths;
		int totalRecoveredCases;
		
		int count = 0;
		int nextWordPosition = 0;
		
		// checking if this line is not the first line, which should not be parsed
		if (line.find("Country") == string::npos) {
			// splitting the line up into individual data items
			while (line.find(",") != string::npos) {
				//if this is the first line, which is the top row of the CSV data
				if (line.find("Country") != string::npos) {
					break;
				}
				
				if (count == 0) {
					string tempLine = line.substr(1);
					int endOfCountryName = tempLine.find_first_of('"') + 1;
					countryName = line.substr(0, endOfCountryName + 1);
					line = line.substr(endOfCountryName + 2);
				}
				else {
					int firstCommaPosition = line.find_first_of(",");
					string item = line.substr(nextWordPosition, firstCommaPosition - nextWordPosition);
					
					// these if statements will check if this item is an element that should be stored in this country's record. There are certain elements in the line that are not needed for the record, so those will be ignored
					if (count == 1) {
						countryCode = item;
					} 
					else if (count == 3) {
						newConfirmedCases = stoi(item);
					} 
					else if (count == 4) {
						newDeaths = stoi(item);
					}
					else if (count == 5) {
						newRecoveredCases = stoi(item);
					}
					else if (count == 8) {
						totalConfirmedCases = stoi(item);
					}
					else if (count == 9) {
						totalDeaths = stoi(item);
					}
					
					line = line.substr(firstCommaPosition + 1);
				}
				count++;
			}
			totalRecoveredCases = stoi(line);
			
			// creating a new dataRecord item, and storing it into the map
			dataRecord newRecord(countryName, countryCode, newConfirmedCases, newDeaths, newRecoveredCases, totalConfirmedCases, totalDeaths, totalRecoveredCases);
			countryRecords[countryCount] = newRecord;
			countryCount++;
		}
	}
	
	// now that the data has been ingested, it can now be processed
	// first the data field that will be sorted on will be taken in
	int dataField;
	cout << "What data field should be searched on? (Enter the number)\n1. New Confirmed Cases\n2. New Deaths\n3. New Recovered Cases\n4. Total Confirmed cases\n5. Total Deaths\n6. Total Recovered Cases\n";
	cin >> dataField;
	
	switch(dataField) {
		case 1:
			sort(countryRecords, countryRecords + 186, sortNewConfirmedCases);
			break;
		case 2:
			sort(countryRecords, countryRecords + 186, sortNewDeaths);
			break;
		case 3:
			sort(countryRecords, countryRecords + 186, sortNewRecoveredCases);
			break;
		case 4:
			sort(countryRecords, countryRecords + 186, sortTotalConfirmedCases);
			break;
		case 5:
			sort(countryRecords, countryRecords + 186, sortTotalDeaths);
			break;
		case 6:
			sort(countryRecords, countryRecords + 186, sortTotalRecoveredCases);
			break;
		default:
			cout << "Exception occured due to invalid input" << endl;
			exit(0);
	}
	
	// then the order of the data (ascending or descending) will be decided
	int order;
	cout << "What order should the data be in? (Enter the number)\n1. Ascending\n2. Descending\n";
	cin >> order;
	
	if (order == 1) {
		// the list is already sorted in ascending order, so nothing is done here
	}
	else if (order == 2) {
		reverse(countryRecords, countryRecords + 186);
	}
	else {
		cout << "Exception occured due to invalid input" << endl;
	}
	
	// this variable represents how many cases are represented by the # symbol
	double pound;
	
	// now that the data is processed, it will now displayed as a table. This switch statement will display the table based on the chosen data field
	switch(dataField){
		// new confirmed cases
		case 1:
			// if the table is displayed in descending order
			if (order == 2){
				pound = countryRecords[0].getNewConfirmedCases() / 70.0;
				pound = round(pound);
			}
			// if the table is displayed in ascending order
			else{
				pound = countryRecords[9].getNewConfirmedCases() / 70.0;
				pound = round(pound);
				
				// this has to be done to prevent posssible division by 0 later on
				if (pound == 0){
					pound++;
				}
			}
			
			// printing out the table
			for (int i = 0; i < 10; i++){
				cout << countryRecords[i].getCountryCode() << "  |  ";
				double numPounds = countryRecords[i].getNewConfirmedCases() / pound;
				numPounds = round(numPounds);
				for (int j = 0; j < numPounds; j++){
					cout << "#";
				}
				cout << "\n----------\n";
			}
			
			cout << "----------------------------------------------------------------------\n" << "New Confirmed Cases; Each # is approx. " << pound << " cases" << endl;
			
			break;
			
			
		// new deaths
		case 2:
			// if the table is displayed in descending order
			if (order == 2){
				pound = countryRecords[0].getNewDeaths() / 70.0;
				pound = round(pound);
			}
			// if the table is displayed in ascending order
			else{
				pound = countryRecords[9].getNewDeaths() / 70.0;
				pound = round(pound);
				
				// this has to be done to prevent posssible division by 0 later on
				if (pound == 0){
					pound++;
				}
			}
			
			// printing out the table
			for (int i = 0; i < 10; i++){
				cout << countryRecords[i].getCountryCode() << "  |  ";
				double numPounds = countryRecords[i].getNewDeaths() / pound;
				numPounds = round(numPounds);
				for (int j = 0; j < numPounds; j++){
					cout << "#";
				}
				cout << "\n----------\n";
			}
			
			cout << "----------------------------------------------------------------------\n" << "New Deaths; Each # is approx. " << pound << " deaths" << endl;
			
			break;
		
		// new recovered cases
		case 3:
			// if the table is displayed in descending order
			if (order == 2){
				pound = countryRecords[0].getNewRecoveredCases() / 70.0;
				pound = round(pound);
			}
			// if the table is displayed in ascending order
			else{
				pound = countryRecords[9].getNewRecoveredCases() / 70.0;
				pound = round(pound);
				
				// this has to be done to prevent posssible division by 0 later on
				if (pound == 0){
					pound++;
				}
			}
			
			// printing out the table
			for (int i = 0; i < 10; i++){
				cout << countryRecords[i].getCountryCode() << "  |  ";
				double numPounds = countryRecords[i].getNewRecoveredCases() / pound;
				numPounds = round(numPounds);
				for (int j = 0; j < numPounds; j++){
					cout << "#";
				}
				cout << "\n----------\n";
			}
			
			cout << "----------------------------------------------------------------------\n" << "New Recovered Cases; Each # is approx. " << pound << " cases" << endl;
			
			break;
		
		// total confirmed cases
		case 4:
			// if the table is displayed in descending order
			if (order == 2){
				pound = countryRecords[0].getTotalConfirmedCases() / 70.0;
				pound = round(pound);
			}
			// if the table is displayed in ascending order
			else{
				pound = countryRecords[9].getTotalConfirmedCases() / 70.0;
				pound = round(pound);
				
				// this has to be done to prevent posssible division by 0 later on
				if (pound == 0){
					pound++;
				}
			}
			
			// printing out the table
			for (int i = 0; i < 10; i++){
				cout << countryRecords[i].getCountryCode() << "  |  ";
				double numPounds = countryRecords[i].getTotalConfirmedCases() / pound;
				numPounds = round(numPounds);
				for (int j = 0; j < numPounds; j++){
					cout << "#";
				}
				cout << "\n----------\n";
			}
			
			cout << "----------------------------------------------------------------------\n" << "Total Confirmed Cases; Each # is approx. " << pound << " cases" << endl;
			
			break;
		
		// total deaths
		case 5:
			// if the table is displayed in descending order
			if (order == 2){
				pound = countryRecords[0].getTotalDeaths() / 70.0;
				pound = round(pound);
			}
			// if the table is displayed in ascending order
			else{
				pound = countryRecords[9].getTotalDeaths() / 70.0;
				pound = round(pound);
				
				// this has to be done to prevent posssible division by 0 later on
				if (pound == 0){
					pound++;
				}
			}
			
			// printing out the table
			for (int i = 0; i < 10; i++){
				cout << countryRecords[i].getCountryCode() << "  |  ";
				double numPounds = countryRecords[i].getTotalDeaths() / pound;
				numPounds = round(numPounds);
				for (int j = 0; j < numPounds; j++){
					cout << "#";
				}
				cout << "\n----------\n";
			}
			
			cout << "----------------------------------------------------------------------\n" << "Total deaths; Each # is approx. " << pound << " deaths" << endl;
			
			break;
		
		// total recovered cases
		case 6:
			// if the table is displayed in descending order
			if (order == 2){
				pound = countryRecords[0].getTotalRecoveredCases() / 70.0;
				pound = round(pound);
			}
			// if the table is displayed in ascending order
			else{
				pound = countryRecords[9].getTotalRecoveredCases() / 70.0;
				pound = round(pound);
				
				// this has to be done to prevent posssible division by 0 later on
				if (pound == 0){
					pound++;
				}
			}
			
			// printing out the table
			for (int i = 0; i < 10; i++){
				cout << countryRecords[i].getCountryCode() << "  |  ";
				double numPounds = countryRecords[i].getTotalRecoveredCases() / pound;
				numPounds = round(numPounds);
				for (int j = 0; j < numPounds; j++){
					cout << "#";
				}
				cout << "\n----------\n";
			}
			
			cout << "----------------------------------------------------------------------\n" << "Total Recovered Cases; Each # is approx. " << pound << " cases" << endl;
			
			break;
		
	}
}
