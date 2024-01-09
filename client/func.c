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
int next_procec(char *comm){
    if (strcmp(input, "%%Q") == 0) {
        printf("Qに一致しました\n");
        return 0;
    } else if (strcmp(input, "%%R") == 0) {
        printf("Rに一致しました\n");
        return 1;
    } else if (strcmp(input, "%%C") == 0) {
        printf("Cに一致しました\n");
        return 1;
    } else if (strcmp(input, "%%P") == 0) {
        printf("Pに一致しました\n");
        return 1;
    } else {
        printf("一致する文字列がありません\n");
        return -1;
    }
}
