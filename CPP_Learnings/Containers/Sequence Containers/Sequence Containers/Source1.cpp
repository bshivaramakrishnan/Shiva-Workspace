#include <iostream>
#include <map>
#include <vector>
#include<chrono>
#include<ctime>
#include<sstream>
#include"account.h"
#include"transactions.h"
#include"ATM.h"

using namespace std;

int main() {
    ATM atm;
    atm.run();
    return 0;
}
