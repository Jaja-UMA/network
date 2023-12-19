#include"libs.h"
#include"header.h"

int myprint(const char *text){
    int n,textLen;
    char tmpText[BUF_SIZE];

    textLen = strlen(text);
    n=0;
    while(n<=textLen){
        strncpy(tmpText,text+n,BUF_SIZE);
        write(1,tmpText,BUF_SIZE);
        n+=BUF_SIZE;
    }
    putchar('\n');
    return 1;
}
//recvでもらった文字列からGETやPOSTを判断
char * bufToFile(const char *path)
{
    char method[10];
    char data[BUF_SIZE];

    // Use sscanf to extract the method and data
    if (sscanf(path, "%s %s", method, data) != 2) {
        fprintf(stderr, "Invalid request format: %s\n", path);
        return;
    }

    // Process the request based on the method
    if (strcmp(method, "POST") == 0) {
        printf("Processing POST request with data: %s\n", data);

    } else if (strcmp(method, "GET") == 0) {
        printf("Processing GET request for: %s\n", data);
        // Add your GET request handling code here
    } else {
        fprintf(stderr, "Unsupported method: %s\n", method);
    }

    return '0';

}

char* countStrlen(const char *messege)
{
    char len[10];

}
