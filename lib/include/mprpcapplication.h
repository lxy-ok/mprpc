#pragma once

#include "mprpcconfig.h"
#include "mprpcchannel.h"
#include "mprpccontroller.h"

// mprpc框架的基础类，负责框架的一些初始化操作
class mprpcapplication{
public:
static void init(int argc,char **argv);
static mprpcapplication &getinstance();
static mprpcconfig & getconfig();  
private:
static mprpcconfig m_config;
mprpcapplication(){}
mprpcapplication(const mprpcapplication&a1)=delete;
mprpcapplication & operator=(const mprpcapplication&a1)=delete;
/*MprpcApplication(const MprpcApplication&) = delete;
MprpcApplication(MprpcApplication&&) = delete;
还有这种写法*/




};