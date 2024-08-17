//-------------------------------------------------------
//   CS215-402  Lab 7
//-------------------------------------------------------
// Author: Joseph Crain
// Date: 4/1/2020
// Description: Inventory report
//-------------------------------------------------------

#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
using namespace std;

struct prod {
	double price;
	int inStock;
	string name;
};

const int maxProd = 15;

//-------------------------------------------------------
//                readInventory
//-------------------------------------------------------
void readInventory(prod p[maxProd], int& num) {
	ifstream fin;
	fin.open("inventory.txt");
	if (fin.fail()) {
		// for failure
		cout << "Unable to open ionput file" << endl;
		num = 0;
	}
	else {
		int b = 0;
		num = 0;
		int i = 0;
		// running a loop until it detects that it hits the end of data / also adding to numProd for each loop
		while (b < 5) {
			double test;
			test = 0.0;
			fin >> test;
			if (test == -1) {
				b = 10;
			}
			else {
				p[i].price = test;
				fin >> p[i].inStock;
				fin >> p[i].name;
				num = num + 1;
			}
			i = i + 1;
		}
		cout << "inventory read" << endl;
	}
}

//-------------------------------------------------------
//                totalValue
//-------------------------------------------------------
double totalValue(prod p[], int num) {
	// adding together each price * each number of stock 
	double totalPrice = 0;
	for (int i = 0; i < num; i++) {
		totalPrice = totalPrice + (p[i].inStock * p[i].price);
	}
	return totalPrice;
}

//-------------------------------------------------------
//                   Sort
//-------------------------------------------------------
void sort(prod p[], int num) {
	// filling a array with the names and comparing them, then using a temporary structure to switch them 
	string sort[maxProd];
	prod t[maxProd];
	for (int i = 0; i < num; i++) {
		sort[i] = p[i].name;
	}
	for (int i = 0; i < num; i++) {
		for (int j = i + 1; j < num; j++) {
			if (sort[i] > sort[j]) {
				t[5] = p[j];
				p[j] = p[i];
				p[i] = t[5];
			}
		}
	}
}

//-------------------------------------------------------
//                writeReport
//-------------------------------------------------------
void writeReport(prod p[maxProd], int num) {
	// writing to the output file
	ofstream fout;
	fout.open("report.txt");
	if (fout.fail()) {
		cout << "Unable to open output file.\n";
	}
	else {
		fout << "+" << setfill('-') << setw(31) << "+" << setfill(' ') << endl;
		fout << "|" << right << setw(24) << "Current Inventory" << right << setw(7) << "|" << endl;
		fout << "+" << setfill('-') << setw(31) << "+" << setfill(' ') << endl;
		fout << left << setw(20) << "NAME" << setw(7) << " PRICE" << setw(2) << "  #" << endl;
		fout << setfill('-') << setw(20) << right << " " << setw(8) << right << " " << setw(4) << right << " " << setfill(' ') << endl;
		for (int i = 0; i < num; i++) {
			fout << setw(20) << left << p[i].name;
			fout << "$ "  << fixed << setprecision(2) << right << setw(5) << p[i].price;
			fout << setw(4) << right << p[i].inStock << endl;
		}
		fout << "+" << setfill('-') << setw(31) << "+" << setfill(' ') << endl;
		// finding the total value
		double T = totalValue(p, num);
		fout << "Number of products:    " << num << endl;
		fout << "Inventory total value: " << fixed << setprecision(2) << T << endl;
	}
}

//-------------------------------------------------------
//                 main
//-------------------------------------------------------
int main() {
	prod p[maxProd];
	int numProd = 0;

	readInventory(p, numProd);
	sort(p, numProd);
	writeReport(p, numProd);
	system("pause");
	return 0;
}