#include<mprpcapplication.h>
#include<iostream>
#include <unistd.h>
#include <string>
 mprpcconfig mprpcapplication::m_config;
void showargshelp(){
    std::cout<<"command -i configfile"<<std::endl;
}
void mprpcapplication::init(int argc,char **argv){
if(argc<2)
{
    showargshelp();
    exit(EXIT_FAILURE);
}
int c=0;
std::string config_file;
//getopt 用于解析命令行参数
while((c=getopt(argc,argv,"i:"))!=-1){
    switch(c){
        case 'i':
        config_file=optarg;//optarg是一个全局变量，用来存储使用getopt函数获取到的参数值
        break;

        case '?':
        showargshelp();
        exit(EXIT_FAILURE);

        case ':':
        showargshelp();
        exit(EXIT_FAILURE);

        default:
        break;
     }
}
// 开始加载配置文件了,交给config去分解文件各个部分
// rpcserver_ip=  rpcserver_port   zookeeper_ip=  zookepper_port=
   m_config.loadconfigfile(config_file.c_str());

     std::cout << "rpcserverip:" << m_config.load("rpcserverip") << std::endl;
     std::cout << "rpcserverport:" << m_config.load("rpcserverport") << std::endl;
     std::cout << "zookeeperip:" << m_config.load("zookeeperip") << std::endl;
    std::cout << "zookeeperport:" << m_config.load("zookeeperport") << std::endl;

    }

 mprpcapplication& mprpcapplication::getinstance(){
    static mprpcapplication app;
    return app;

}

mprpcconfig& mprpcapplication::getconfig(){
    return m_config;
}
