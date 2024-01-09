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
int next_procec(char *input){
    //printf("%d:next_procec\n",strlen(input));
    if (strcmp(input, "%Q") == 0) {
        return 0;
    }else if(input[0]=='%'){
        return 1;
    } else {
        printf("一致する文字列がありません\n");
        return -1;
    }
}
