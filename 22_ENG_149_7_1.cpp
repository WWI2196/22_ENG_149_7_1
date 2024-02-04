#include <iostream>
#include <cmath>
using namespace std;

float mean(int* table, int size); //function for mean
float median(int* table, int size); //function for median
void mode(int* table, int size); //function for mode
void stdDeviationAndVariance(int* table, int size); //function for standard deviation and variance

float mean(int* table, int size) {
	float sum = 0;

    for (int i = 0; i < size; i++) { //loop for sum of all elements
		sum += *(table+i);
	}
	return sum / size;
}

float median(int* table, int size) {

    if (size == 1) { //if size is 1, return the only element
        return *table;
    }

    for (int i = 0; i < size; i++) { //loop for sorting the elements
        for (int y = 0; y < size - 1; y++) {
            if (*(table + y) > *(table + y + 1)) {
				int temp = *(table+y);
				*(table+y) = *(table+y+1);
				*(table+y+1) = temp;
			}
		}
    }

    if (size % 2 != 0) { //if size is odd, return the middle element
		return *(table + (size / 2)-1);
	}
    else {
		return (*(table + (size / 2)) + *(table + (size / 2)-1))/2.0;
	}
}

void mode(int* table, int size) {

    int* temp = new int[size];

    for (int i = 0; i < size; i++) { //loop for counting the frequency of each element
        int count = 0;

        for (int j = 0; j < size; j++) {
            if (j == i) {
                continue; //skip the current element to avoid counting itself
            }
            else if (*(table + i) == *(table + j)) {
                count++;
            }
        }
        *(temp + i) = count; //store the frequency of each element
    }

    bool modeExist = false;
    for (int i = 0; i < size; i++) { //loop for checking if there is a mode
        if (*(temp + i) > 0) { //if there is a mode, set modeExist to true
            modeExist = true;
            break;
        }
    }

    if (modeExist) { 
        int max = 0;
        int index = 0;

        for (int i = 0; i < size; i++) { //loop for finding the maximum frequency
            if (max < *(temp + i)) {
                max = *(temp + i);
            }
        }

        int* indexT = new int[size];

        for (int i = 0; i < size; i++) { //loop for finding the index of the maximum frequency
            if (max == *(temp + i)) {
                index++;

                *(indexT + (index - 1)) = i; //store the index of the maximum frequency
            }
        }

        if (index == 1) {
            cout << *(table + *(indexT)); //if there is only one mode, print the mode
        }
        else { //if there are multiple modes, print all the modes
            cout << "Mode\t\t\t:";

            bool printed = false;

            for (int i = 0; i < index; i++) {
                bool alreadyPrinted = false;

                for (int j = 0; j < i; j++) { //loop for checking if the mode is already printed
                    if (*(table + *(indexT + i)) == *(table + *(indexT + j))) { //if the mode is already printed, set alreadyPrinted to true
                        alreadyPrinted = true;
                        break;
                    }
                }
                if (!alreadyPrinted) { //if the mode is not already printed, print the mode
                    cout << (printed == false ? "" : ",") << *(table + *(indexT + i)) ;
                    printed = true;
                }
            }
            cout << endl;
        }
        delete[] indexT; 
    }

    delete[] temp;
}

void stdDeviationAndVariance(int* table, int size) {
    float variance = 0;

    float mean_ = mean(table,size); //get the mean
    
    for (int i = 0; i < size; i++) { //loop for calculating the variance
        variance += pow(*(table+i) - mean_, 2); 
    }

    cout << "Variance\t\t:" << variance / size << endl;

    cout << "Standard Deviation\t:" << sqrt(variance / size) << endl; //print the standard deviation

}


int main() {
    while (true) {

        int numberOfSt;
        cout << "Enter number of students\t: ";
        cin >> numberOfSt; //get the number of students

        int* table = new int[numberOfSt]; //create a dynamic array
        cout << "Enter data for " << numberOfSt << " students\t: "; \

        for (int i = 0; i < numberOfSt; i++) {
            cin >> *(table+i); //store the data in the array for each student
        }

        cout << "-------------------------------------------" << endl;

        cout << "Mean\t\t\t:" << mean(table, numberOfSt) << endl;
        cout << "Median\t\t\t:" << median(table, numberOfSt) << endl;
        mode(table, numberOfSt);
        stdDeviationAndVariance(table, numberOfSt);

        delete[] table; //delete the dynamic array

        cout << "-------------------------------------------" << endl;

        cout << "Do you want to continue(y/n)? "; //ask the user if they want to continue

        char choice;
        cin >> choice;

        if (tolower(choice) == 'n') { //if the user enters no, break the loop
			break;
		}

        cout << endl;
    }
    
    return 0;
}
