

// Client side C/C++ program to demonstrate Socket programming 
#include <stdio.h> 
#include <sys/socket.h> 
#include <stdlib.h> 
#include <netinet/in.h> 
#include <string.h> 
#define PORT 4001
   
int main(int argc, char const *argv[]) 
{ 
    char scanner[] = {'W', 'e'};
    char *hello = "whatsupdog";
    char *frick = "ASDF";
    char package[1024];
    char temp = scanner[0];
    package[0] = '\0';

    int pLength = strlen(package);
    printf("scanner[]: %s\t*hello: %s\t package: '%s' \t pLength: %d\n", scanner, hello, package, pLength );

    strcat(package,hello);
    pLength = strlen(package);
    printf("scanner[]: %s\t*hello: %s\t package: '%s' \t pLength: %d\n", scanner, hello, package, pLength );

    strcat(package,frick);
    pLength = strlen(package);
    printf("scanner[]: %s\t*hello: %s\t package: '%s' \t pLength: %d\n", scanner, hello, package, pLength );

    sprintf(package, "%s%c", package, temp);

    pLength = strlen(package);
    printf("scanner[]: %s\t*hello: %s\t package: '%s' \t pLength: %d\n", scanner, hello, package, pLength );

    // package[0] = '\0';

    // pLength = strlen(package);
    // printf("scanner[]: %s\t*hello: %s\t package: %s \t pLength: %d\n", scanner, hello, package, pLength );
} 