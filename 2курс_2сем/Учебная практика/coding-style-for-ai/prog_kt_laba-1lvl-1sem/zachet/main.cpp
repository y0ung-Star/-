#include <iostream>
#include <math.h>
using namespace std;

int main() {
    double max_value;
    double min_value;
    int max_value_index;
    int min_value_index;
    int above_zero_count = NAN;

    int AVec[] = {0, 13, -2, 16, 32, -8, -17, 10, -6, 3};
    for (int i=0; i < sizeof(AVec)/sizeof(AVec[0]); i++) {

        if(i==0) {
            max_value = AVec[i];
            max_value_index = i;
            min_value = AVec[i];
            min_value_index = i;
        }

        if(max_value < AVec[i]) {
            max_value = AVec[i];
            max_value_index = i;
        }

        if(min_value > AVec[i]) {
            min_value = AVec[i];
            min_value_index = i;
        }
    }

    for (int i=max_value_index; i < min_value_index; i++) {
        if(AVec[i] > 0) {
            above_zero_count++;
        }
    }
   
    // for (int i = min_value_index + 1; i < max_value_index; ++i) {


    cout << "AVec: ";
    for (int i=0; i < sizeof(AVec)/sizeof(AVec[0]); i++) {
        cout << AVec[i] << " ";
    }

    cout << endl << "Максимальное значение: " << max_value << endl;
    cout << "Минимальное значение: " << min_value << endl;
    cout << "Количество отрицательных элементов между min и max значениями: " << above_zero_count << endl;
}
