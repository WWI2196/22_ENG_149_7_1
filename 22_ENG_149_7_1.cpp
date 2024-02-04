#include <iostream>
using namespace std;

float mean(int* table, int size);
float median(int* table, int size);
int mode(int* table, int size);

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

int mode(int* table, int size) {
    
    int* temp= new int[size];

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

	int max = 0;
	for (int i = 0; i < size; i++) {
        if (*(temp + i) > max) {
			max = *(temp + i);
		}
	}

	if (max == 0) {
	}
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
        cout << "Mode\t:" << mode(table, numberOfSt) << endl;
        
        
        delete[] table;
    }
    
    return 0;
}
