#include"libs.h"
#include"header.h"


//第一引数:接続先
//第二引数:ファイルパス
//第三引数:ポート番号

int main(int argc,char *argv[]){
    if(argc!=4 || argc > 4)
    {
        fprintf(stderr,"引数の数が足りませんor多い\n第一引数:接続先第二引数:ファイルパス 第三引数:ポート番号\n");
        return 0;
    }


    struct addrinfo hints,*res;
    int s,com_code;
    char buf[BUF_SIZE];
    char send_mes[BUF_SIZE];

    memset(send_mes,0,sizeof(send_mes));
    sprintf(send_mes,"GET /%s\r\n",argv[2]);
    memset(buf,0,BUF_SIZE);

    //addrinfoに関する初期化
    memset(&hints,0,sizeof(hints));
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_family = AF_INET;

    printf("argv[1]:%s argv[2]:%s argv[3]:%s\nsend_mes = %s\n",argv[1],argv[2],argv[3],send_mes);

    s=connectServer(argv[1],argv[3],&hints,&res);
    if(send(s,send_mes,BUF_SIZE,0)==-1)
    {
        fprintf(stderr,"sendERROR\n");
        return 0;
    }
    printf("sending is done\nyou send:%s\n",send_mes);


    recv(s,buf,BUF_SIZE,0);
    printf("recieving is done\n");
    myprint(buf);

    close(s);
    return 0;
}
