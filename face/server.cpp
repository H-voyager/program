#include "httplib.h"
#include <iostream>
#include <boost/filesystem.hpp>
#include <fstream>

using namespace httplib;
namespace bf = boost::filesystem;

#define SHARED_PATH "shared"

//#define LOG(...) std<<cout<< __VA_ARGS__
#define LOG(fmt, ...) fprintf(stderr,fmt, __VA_ARGS__)

class p2pserver{
private:
    Server _server;
private:
    static void GetHostPair(const Request &req, Response &rsp)
    {
        rsp.status = 200;
    }
    static void GetFileList(const Request &req, Response &rsp)
    {
        bf::directory_iterator item_begin(SHARED_PATH);
        bf::directory_iterator item_end;
        std::stringstream body;
        //body << "<html><body>";
        //std::string body;

        for(; item_begin != item_end; ++item_begin)
        {
           if(bf::is_directory(item_begin->status()))
           {
               continue;
           }

           bf::path path = item_begin->path();
           //只显示文件名称
           std::string name = path.filename().string();
           rsp.body += name + '\n';
        }
        rsp.status = 200;
    }
    static void GetFileDate(const Request &req, Response &rsp)   
    {   //请求时为一个路径 /list/filename -> /Download/filename
        bf::path path(req.path);
        //文件流操作
        std::stringstream name;
        name << SHARED_PATH << "/" << path.filename().string();
        //将文件名传入以打开文件  c++输入文件流ifstream
        

        if(!bf::exists(name.str()))
        {
            rsp.status = 404;
            return ;
        }
        if(bf::is_directory(name.str()))
        {
            rsp.status = 406;
            return ;
        }
        int64_t fsize = bf::file_size(name.str());
        if (req.method == "HEAD")
        {
            rsp.status = 200;
            std::string len = std::to_string(fsize);
            rsp.set_header("Content-length", len.c_str());
            return ;
        }else{
            if(!req.has_header("Range"))
            {
                rsp.status = 400;
                return;
            }
            std::string range_val;
            range_val = req.get_header_value("Range");

            //byte = start - end
            int64_t start, rlen;
            bool ret = RangeParse(range_val, start, rlen);
            if(ret == false)
            {
                rsp.status == 400;
                return ;
            }

            //打开指定文件
            std::ifstream file(name.str(), std::ios::binary);
            if(!file.is_open())
            {
                std::cerr<<"open file" << name.str()<<"failed\n";
                rsp.status = 404;
                return ;
            }

            //跳转指定位置
            file.seekg(start, std::ios::beg);//brg :偏移量
            rsp.body.resize(rlen);
            file.read(&rsp.body[0], rlen);
            if(!file.good())
            {
                std::cerr<< "read " << name.str() << " body error\n";
                rsp.status = 500;
                return;
            }
            file.close();
            rsp.status = 206;
            rsp.set_header("Content-Type", "application/octent-stream");
            std::cerr << "file range: " << range_val;
            std::cerr << "download succesn";
        }
    }
    static bool RangeParse(std::string &range_val, int64_t &start, int64_t &len)
    {
            size_t pos1 = range_val.find("=");
            size_t pos2 = range_val.find("-");
            if(pos1 == std::string::npos || pos2 == std::string::npos)
            {
                std::cerr<<"range"<<range_val<<"format error\n";
                return false;
            }

            int64_t end;
            std::string rstart;
            std::string rend;
            rstart = range_val.substr(pos1 + 1,pos2 - pos1 -1);
            rend = range_val.substr(pos2 + 1);
            std::stringstream tmp;
            tmp << rstart;
            tmp >> start;
            tmp.clear();
            tmp << rend;
            tmp >> end;
            len = end - start + 1;

            return true;
    }
public:
    p2pserver()
    {
        if(!bf::exists(SHARED_PATH))
        {
            bf::create_directory(SHARED_PATH);
        }

    }
    bool Start(uint16_t port )
    {
        _server.Get("/hostpair", GetHostPair);
        _server.Get("/list", GetFileList);
        _server.Get("/list/(.*)", GetFileDate);
        _server.listen("0.0.0.0",port);

    }

};
 
int main()
{
    p2pserver server;

    server.Start (10086);
    return 0;
}
