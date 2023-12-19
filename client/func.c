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

int connectServer(const char *host,const char *path,const char *port)
{
    int socket;

    if(getaddrinfo(host,port,&hints,&res) !=0){
        printf("error:getaddrinfoargv[0]= %s\n",argv[1]);
    }
    socket = socket(res->ai_family,res->ai_socktype,res->ai_protocol);
    if(socket == -1){
        fprintf(stderr,"socket Error\n");
        return 0;
    }
    if(connect(socket,res->ai_addr,res->ai_addrlen) == -1)
    {
        fprintf(stderr,"connect\n");
        return 0;
    }
    printf("connection is done\n");

}
