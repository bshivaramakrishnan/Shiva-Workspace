/*#include <iostream>
#include <stdexcept> // For standard exceptions

int main() {
    double num, denom;
    std::cout << "Enter numerator: ";
    std::cin >> num;
    std::cout << "Enter denominator: ";
    std::cin >> denom;

    try {
        if (denom == 0) {
            throw std::runtime_error("Error: Division by zero is not allowed.");
        }
        double result = num / denom;
        std::cout << "Result: " << result << std::endl;
    } catch (const std::runtime_error& e) {
        std::cerr << e.what() << std::endl;
    }
    
    return 0;
}

*/
#include <iostream>
#include <stdexcept>
using namespace std;
int main() {
    double num, denom;
    cout << "Enter the numberator : \n";
    cin >> num;
    cout << "Enter the Denominator : \n";
    cin >> denom;
    try {
        if (denom == 0) {
            throw runtime_error("Zero Division Error.\n");
        }
        double result = num / denom;
        cout << "Result : " << result << endl;

    }
    catch (const runtime_error& e) {
        cerr << e.what() << endl;
    }
    return 0;
}



