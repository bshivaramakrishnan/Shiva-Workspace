#include <iostream>
using namespace std;

class Engine {
private:
    int horsepower;

public:
    Engine(int hp) : horsepower(hp) {}
    friend class Car;
};

class Car {
public:
    void showEnginePower(Engine& eng) {
        cout << "Engine Horsepower: " << eng.horsepower << " HP" << endl;
    }
};

int main() {
    Engine engine(150);  
    Car car;  
    car.showEnginePower(engine);  // C

    return 0;
}
