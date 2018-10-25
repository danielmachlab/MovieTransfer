
// Server side C/C++ program to demonstrate Socket programming 
#include <unistd.h> 
#include <stdio.h> 
#include <sys/socket.h> 
#include <stdlib.h> 
#include <netinet/in.h> 
#include <string.h> 
#define PORT 4000 
int main(int argc, char const *argv[]) 
{ 
    int server_fd, new_socket, valread; 
    struct sockaddr_in address; 
    int opt = 1; 
    int addrlen = sizeof(address); 
    char buffer[1024] = {0}; 
    char *hello = "Hello from server"; 


    /* get file from server */
    int curl_response = system("curl http://user.engineering.uiowa.edu/~jwryan/Communication_Networks/alice.txt -o alice.txt");
    if(curl_response != 0){
        printf("curl request failed %d\n", curl_response);
    }
       
    // Creating socket file descriptor 
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) 
    { 
        perror("socket failed"); 
        exit(EXIT_FAILURE); 
    } 
       
    // Forcefully attaching socket to the port 8080 
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, 
                                                  &opt, sizeof(opt))) 
    { 
        perror("setsockopt"); 
        exit(EXIT_FAILURE); 
    } 
    address.sin_family = AF_INET; 
    address.sin_addr.s_addr = INADDR_ANY; 
    address.sin_port = htons( PORT ); 
       
    // Forcefully attaching socket to the port 8080 
    if (bind(server_fd, (struct sockaddr *)&address,  
                                 sizeof(address))<0) 
    { 
        perror("bind failed"); 
        exit(EXIT_FAILURE); 
    } 
    if (listen(server_fd, 3) < 0) 
    { 
        perror("listen"); 
        exit(EXIT_FAILURE); 
    } 
    if ((new_socket = accept(server_fd, (struct sockaddr *)&address,  
                       (socklen_t*)&addrlen))<0) 
    { 
        perror("accept"); 
        exit(EXIT_FAILURE); 
    } 
    valread = read( new_socket , buffer, 1024); 


    /* send script */
    FILE *fp = fopen("practice.txt", "r+");
    int len = strlen(argv[1]);
    char scanner[len];
    scanner[len] = '\0';
    int buffLen =strlen(scanner);
    printf("wd :'%s' \t     scanner: '%s'\n", argv[1], scanner);
    printf("len: %d \t scanner len: %d\n", len, buffLen);

    for(int i = 0; i < len; i++)
        scanner[i] = fgetc(fp);
    

    char package[1023];
    int index = 0;

    while(feof(fp) == 0){
        int equality = strcmp(scanner, argv[1]);
        int len1 =strlen(scanner);
        int len2 =strlen(argv[1]);

        // if(strcmp(scanner, argv[1])){
        //     printf("\nscanner: '%s', len: %i\t other: '%s', len: %d\n", scanner, len1, argv[1], len2);
        // }
        
        if(equality == 0){
            for(int i = 0; i <  len; i ++){
                package[index] = '*';
                index++;
            }
            for(int i = 0; i< len; i++)
                scanner[i] = fgetc(fp);
        }else{
            package[index] = scanner[0];
            index++;
            for(int i = 0; i <  len - 1; i ++)
                scanner[i] = scanner[i+1]; 
            scanner[len-1] = fgetc(fp);
        }


        if(strlen(package)>970){
            index = 0;
            send(new_socket, package , index, 0 );
            printf("-----------------------\n%s", package); 
            package[0] = '\0';
        }

    }
    send(new_socket, package , index, 0 );
    printf("==================%s", package); 
    
    printf("Script sent\n"); 
    return 0; 
} 
