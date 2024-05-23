#include "mprpcconfig.h"
#include <iostream>
#include <string>

// 负责解析加载配置文件
   void mprpcconfig::loadconfigfile(const char* config_file){

 FILE *pf=fopen(config_file,"r");
 if (nullptr == pf)
    {
        std::cout << config_file << " is note exist!" << std::endl;
        exit(EXIT_FAILURE);//返回一个表示失败的状态码
    }
// # rpc节点的ip地址
// rpcserverip=127.0.0.1     
// # rpc节点的port端口号
// rpcserverport=8000
// # zk的ip地址
// zookeeperip=127.0.0.1
// # zk的port端口号
// zookeeperport=2181
    // 1.注释   2.正确的配置项 =    3.去掉开头的多余的空格 
    //feof循环读取文件直到达到末尾
   while(!feof(pf)){
    char buf[1024]={0};
    fgets(buf,512,pf);
     std::string src_buf(buf);
   trim(src_buf);
        // 判断#的注释
        if (src_buf[0] == '#' || src_buf.empty())
        {
            continue;
        }

        // 解析配置项
      int  idx=src_buf.find('=');
        if (idx == -1)
        {
            // 配置项不合法
            continue;
        }

        std::string key;
        std::string value;
         key = src_buf.substr(0, idx);
        //还要考虑等号附近的空格
        trim(key);
        // rpcserverip=127.0.0.1\n这种情况
        int endidx=src_buf.find('\n',idx);
        value = src_buf.substr(idx+1, endidx-idx-1);
        trim(value);
        m_configMap.insert({key,value});
       
    }

   }
   
    // 查询配置项信息
  std::string mprpcconfig::load(const std::string &key){
 auto it = m_configMap.find(key);
    if (it == m_configMap.end())
    {
        return "";
    }
    return it->second;
  } 

  // 去掉字符串前后的空格
  void mprpcconfig::trim(std::string &src_buf){
//正向查找在原字符串中第一个与指定字符串（或字符）中的任一字符都不匹配的字符，返回它的位置
    int idx = src_buf.find_first_not_of(' ');
    if (idx != -1)
    {
        // 说明字符串前面有空格
        src_buf = src_buf.substr(idx, src_buf.size()-idx);
    }
    // 去掉字符串后面多余的空格
    idx = src_buf.find_last_not_of(' ');
    if (idx != -1)
    {
        // 说明字符串后面有空格
        src_buf = src_buf.substr(0, idx+1);
    }
  }