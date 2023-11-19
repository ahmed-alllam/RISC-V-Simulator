
#include <iostream>
using namespace std;

void myStrcpy(char *dest, const char *src) {
    while (*src) {
        *dest++ = *src++;
    }
    *dest = '\0';
}

int main() {
    char src[] = "Hello World";
    char dest[20];

    myStrcpy(dest, src);

    return 0;
}
