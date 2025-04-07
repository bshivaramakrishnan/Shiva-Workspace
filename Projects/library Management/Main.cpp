#include"librarysystem.h"

int main() {
    LibrarySystem system;


    system.addBorrower(101, "shiva", "1234", 50.0);
    system.addBorrower(102, "dhisha", "5678", 20.0);

    system.mainMenu();

    return 0;
}
