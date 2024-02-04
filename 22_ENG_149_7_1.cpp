#include <iostream>
#include <cmath>
using namespace std;

float mean(int* table, int size);
float median(int* table, int size);
void mode(int* table, int size);
void stdDeviationAndVariance(int* table, int size);

float mean(int* table, int size) {
	float sum = 0;
    for (int i = 0; i < size; i++) {
		sum += *(table+i);
	}
	return sum / size;
}

float median(int* table, int size) {

    for (int i = 0; i < size; i++) {
        for (int y = 0; y < size - 1; y++) {
            if (*(table + y) > *(table + y + 1)) {
				int temp = *(table+y);
				*(table+y) = *(table+y+1);
				*(table+y+1) = temp;
			}
		}
    }

    if (size % 2 != 0) {
		return *(table + (size / 2)-1);
	}
    else {
		return (*(table + (size / 2)) + *(table + (size / 2)-1))/2.0;
	}
}

void mode(int* table, int size) {

    int* temp = new int[size];

    for (int i = 0; i < size; i++) {
        int count = 0;
        for (int j = 0; j < size; j++) {
            if (j == i) {
                continue;
            }
            else if (*(table + i) == *(table + j)) {
                count++;
            }
        }
        *(temp + i) = count;
    }

    bool modeExist = false;
    for (int i = 0; i < size; i++) {
        if (*(temp + i) > 0) {
            modeExist = true;
            break;
        }
    }

    if (modeExist) {
        int max = 0;
        int index = 0;

        for (int i = 0; i < size; i++) {
            if (max < *(temp + i)) {
                max = *(temp + i);
            }
        }

        int* indexT = new int[size]; // Allocate memory for size elements instead of index

        for (int i = 0; i < size; i++) {
            if (max == *(temp + i)) {
                index++;
                *(indexT + (index - 1)) = i;
            }
        }

        if (index == 1) {
            cout << *(table + *(indexT));
        }
        else {
            cout << "Mode\t:";
            for (int i = 0; i < index; i++) {
                bool alreadyPrinted = false;
                for (int j = 0; j < i; j++) {
                    if (*(table + *(indexT + i)) == *(table + *(indexT + j))) {
                        alreadyPrinted = true;
                        break;
                    }
                }
                if (!alreadyPrinted) {
                    cout << *(table + *(indexT + i)) << " ";
                }
            }
            cout << endl;
        }
        delete[] indexT;
    }

    delete[] temp;
}

void stdDeviationAndVariance(int* table, int size) {
    float sum=0,variance = 0;

    for (int i = 0; i < size; i++) {
        sum += *(table+i);
    }

    float mean = sum / size;
    
    for (int i = 0; i < size; i++) {
        variance += pow(*(table+i) - mean, 2);
    }

    cout << "Variance\t:" << variance / size << endl;

    cout << "Standard Deviation\t:" << sqrt(variance / size) << endl;

}


int main() {
    while (true) {

        int numberOfSt;
        cout << "Enter number of students\t: ";
        cin >> numberOfSt;

        int* table = new int[numberOfSt];
        cout << "Enter data for " << numberOfSt << " students\t: ";

        for (int i = 0; i < numberOfSt; i++) {
            cin >> *(table+i);
        }

        cout << "-------------------------------------------" << endl;

        cout << "Mean\t:" << mean(table, numberOfSt) << endl;
        cout << "Median\t:" << median(table, numberOfSt) << endl;
        mode(table, numberOfSt);
        stdDeviationAndVariance(table, numberOfSt);

        delete[] table;

        cout << "-------------------------------------------" << endl;

        cout << "Do you want to continue(y/n)? ";

        char choice;
        cin >> choice;

        if (tolower(choice) == 'n') {
			break;
		}
    }
    
    return 0;
}
