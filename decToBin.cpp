#include <iostream>
#include <math.h>

using namespace std;

int main() {
    float decFrac;
    int precision;
    cin >> decFrac;
    cin >> precision;
    string binary("0.");
    for (int n = -1; decFrac != 0.0 && precision > 0; --n, --precision) {
        if (decFrac >= pow(2, n)) {
            binary += '1';
            decFrac -= pow(2, n);
        } else {
            binary += '0';
        }
    }
    cout << binary << '\n';
}