#include "logger.h"
#include <time.h>
#include <iostream>

// 获取日志的单例
 Logger& Logger::GetInstance(){
    static Logger  logger;
    return  logger;
}
Logger::Logger(){
    // 启动专门的写日志线程,&是按引用捕获，可以修改值
    std::thread writelogtask([&](){
           for(;;){
       // 获取当前的日期，然后取日志信息，写入相应的日志文件当中 a+
       time_t now=time(nullptr);//获取当前时间的时间戳,秒数
       tm *nowtm=localtime(&now);   //将时间戳转换为本地时间

        char file_name[128];
        //sprintf把后面的东西打印在给的file_name中
        sprintf(file_name, "%d-%d-%d-log.txt", nowtm->tm_year+1900, nowtm->tm_mon+1, nowtm->tm_mday);   

//第二个参数是打开方式，"a+"表示以读写方式打开文件，并将输出添加到文件末尾。如果文件不存在，则会创建一个新文件。
      FILE *pf=fopen(file_name,"a+");         
            if (pf == nullptr)
            {
                std::cout << "logger file : " << file_name << " open error!" << std::endl;
                exit(EXIT_FAILURE);
            }
            //队列里面存了很多日志，然后现在输出到文件中
      std::string msg=m_lckQue.Pop();
      char time_buf[128] = {0};
            sprintf(time_buf, "%d:%d:%d =>[%s] ", 
                    nowtm->tm_hour, 
                    nowtm->tm_min, 
                    nowtm->tm_sec,
                    (m_loglevel == INFO ? "info" : "error"));

        msg.insert(0, time_buf);
            msg.append("\n");
     fputs(msg.c_str(),pf);
     fclose(pf);
 }         
    
});
    // 设置分离线程，守护线程，主程序结束，线程仍运行
   writelogtask.detach();
}

// 设置日志级别 
void Logger::SetLogLevel(LogLevel level)
{
   m_loglevel=level;
}

// 写日志， 把日志信息写入lockqueue缓冲区当中
void Logger::Log(std::string msg)
{
    m_lckQue.Push(msg);
}