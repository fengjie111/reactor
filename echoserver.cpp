/*
 * 程序名：echoserver.cpp，回显（EchoServer）服务器。
 * 作者：吴从周
*/
#include "EchoServer.h"
#include <signal.h>

EchoServer *echoserver;

void Stop(int sig){     //信号2和15的处理函数，功能是停止服务程序
    printf("sig=%d\n",sig);
    //调用EchoServer::Stop()停止服务
    echoserver->Stop();
    printf("echoserver已停止\n");
    delete echoserver;
    printf("delete echoserver\n");
    exit(0);
}

int main(int argc,char *argv[])
{
    if (argc != 3) 
    { 
        printf("usage: ./echoserver ip port\n"); 
        printf("example: ./echoserver 192.168.163.128 5005\n\n"); 
        return -1; 
    }

    signal(SIGTERM,Stop);   //信号15，系统kill或killall命令默认发送的信号
    signal(SIGINT,Stop);    //信号2，按Ctrl+C发送的信号

    echoserver=new EchoServer(argv[1],atoi(argv[2]),3,3);
    echoserver->Start();

    return 0;
}
