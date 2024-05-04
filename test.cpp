#include <iostream>
#include <iomanip>

using namespace std;

int main() {
    float x = 10000000.0;

    while(x > 0) {
        cout << setprecision(10) << x << endl;
        x /= 2.0;
    }

    return 0;
}