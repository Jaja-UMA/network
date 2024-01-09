#include"libs.h"
#include"header.h"


//第一引数:接続先
//第二引数:ファイルパス
//第三引数:ポート番号

int main(int argc,char *argv[]){
    struct addrinfo hints,*res;
    int s,n,com_code;
    char buf[BUF_SIZE];
    char send_mes[BUF_SIZE];
    if(argc!=4)
    {
        fprintf(stderr,"引数の数が足りません\n第一引数:接続先第二引数:ファイルパス 第三引数:ポート番号\n");
        return 0;
    }
    memset(&hints,0,sizeof(hints));
    memset(buf,0,BUF_SIZE);
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_family = AF_INET;

    printf("argv[1]:%s argv[2]:%s argv[3]:%s\nsend_mes = %s\n",argv[1],argv[2],argv[3],send_mes);

    if(getaddrinfo(argv[1],argv[3],&hints,&res) !=0){
        printf("error:getaddrinfoargv[0]= %s\n",argv[1]);
    }
    s = socket(res->ai_family,res->ai_socktype,res->ai_protocol);
    if(s==-1){
        fprintf(stderr,"socket Error\n");
        return 0;
    }
    if(connect(s,res->ai_addr,res->ai_addrlen) == -1)
    {
        fprintf(stderr,"connect\n");
        return 0;
    }
    printf("connection is done\n");

    while(1){
        memset(send_mes,0,sizeof(send_mes));
        n = read(0,send_mes,256);
        if(n==-1||n==0){
            printf("ファイルの読み込みエラー\nat:inToOut");
            exit(0);
        }
        if(next_procec(send_mes)==0)
        {
            printf("クライアント終了\n");
            break;
        }
        if(next_procec(send_mes)==-1)
        {
            printf("unvaid strings\n");
            break;
        }


        if(send(s,send_mes,BUF_SIZE,0)==-1)
        {
            fprintf(stderr,"sendERROR\n");
            return 0;
        }
        printf("sending is done\nyou send:%s\n",send_mes);


        recv(s,buf,BUF_SIZE,0);
        printf("recieving is done\n");
        myprint(buf);
        printf("~~~~~~~~~~~NEXT PROCECC~~~~~~~~~~~~\n");
    }


    close(s);
    return 0;
}
