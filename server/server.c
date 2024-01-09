#include"libs.h"
#include"header.h"
extern struct profile profile_data[10000];
extern int    nprofiles;
extern char   sending[BUF_SIZE];


int main(int argc,char *argv)
{
    memset(sending,0,BUF_SIZE);
    struct sockaddr_in sa, ca;
    //struct sockaddr;
    int s_s,news,com_code,err_num;
    int len;
    char buf[BUF_SIZE];

    memset((char *)&sa,0,sizeof(sa));
    s_s=socket(AF_INET, SOCK_STREAM, 0);
    if(s_s==-1){
        fprintf(stderr,"socket\n");
        return -1;
    }

    sa.sin_family = AF_INET;
    sa.sin_addr.s_addr = htonl(INADDR_ANY);
    sa.sin_port = htons((uint)atoi("61001"));

    if(bind(s_s, (struct sockaddr*)&sa, sizeof(sa)) == -1)
    {
        fprintf(stderr,"bindERROR (%s)\n",strerror(errno));
        return -1;
    }
    printf("bind is done\n");

    if(listen(s_s,5) == -1)
    {
        fprintf(stderr,"listenERROR\n");
        return -1;
    }
    printf("listen is done\n");

    while(1){
        len = sizeof(ca);
        news = accept(s_s,(struct sockaddr*)&ca,&len);
        //news = accept(s_s,NULL,NULL);
        if(news==-1){
            err_num=errno;
            fprintf(stderr,"acceptingERROR (%s)\n",strerror(err_num));
            return 0;
        }
        printf("Connection accepted from %s:%d\n", inet_ntoa(ca.sin_addr), ntohs(ca.sin_port));

    //受信フロー
        char buf2[BUF_SIZE];
        char str_length[5];


        if(recv(news,buf,BUF_SIZE,0) == -1){
            fprintf(stderr,"recvERROR\n");
            //return 0;
        }
        myprint(buf);
        printf("receive is done\n");
        parse_input(buf);

        if(send(news,sending,BUF_SIZE,0)==-1)
        {
            fprintf(stderr,"sendERROR (%s)\n",strerror(errno));
            //return 0;
        }

        printf("sending is done\nYou send:%s\n",str_length);
        printf("~~~~~~~~~~~~~~~~~~~~~~~~~ALL DONE~~~~~~~~~~~~~~~~~~~~~~~~\n");
        close(news);
    }

    printf("finished\n");

    close(s_s);

    return 0;
}
