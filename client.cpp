/**********************************************************
 * Author        : yang
 * Email         : wk_eternity@163.com
 * Last modified : 2019-08-04 11:03
 * Filename      : client.cpp
 * Description   : 1.获取局域网所有主机IP地址                
 *  2.在线获取在线主机列表(逐个向主机发送配对请求,判断200响应状态)
 *  3.打印在线主机列表,并且用户选择想要查看的主机共享文件
 *  4.向选择的主句发送文件列表请求,获取到文件列表
 *  5.打印文件列表,并且用户选择想要下载的文件
 *  6.下载指定主机指定文件(向指定的主机发送指定的文件下载请求)
 * *******************************************************/
#include <iostream>
#include <string>
#include <vector>
#include <fcntl.h>
#include <unistd.h>
#include <fstream>
#include <ifaddrs.h>
#include <thread>
#include <netinet/in.h>
#include <utility>
#include <arpa/inet.h>
#include "httplib.h"
#include <boost/thread.hpp>
#include <boost/filesystem.hpp>
#include <boost/algorithm/string.hpp>

#define RANGE_SIZE (100<<20)

using namespace httplib;
namespace bf = boost::filesystem;

class PClient{
    private:
        uint16_t _srv_port;
        int _host_idx;
        std::vector<std::string> _online_list;
        std::vector<std::string> _file_list;
    private:
        bool GetAllHost(std::vector<std::string> &list)
        {
            struct ifaddrs *addrs = NULL;
            struct sockaddr_in *ip = NULL;
            struct sockaddr_in *mask = NULL;
            for(getifaddrs(&addrs); addrs != NULL; addrs = addrs->ifa_next)
            {
                ip = (struct sockaddr_in *)addrs->ifa_addr;
                mask = (struct sockaddr_in*)addrs->ifa_netmask;
                if(ip->sin_family != AF_INET)
                {
                    continue;                                                                       
                }
                if(ip->sin_addr.s_addr == inet_addr("127.0.0.1"))
                {
                    continue;
                }
                //转换主机字节序
                uint32_t net = ntohl(ip->sin_addr.s_addr & mask->sin_addr.s_addr);
                uint32_t host = ntohl(~mask->sin_addr.s_addr);
                int i;
                for(i = 2; i < host - 1; i++)
                {
                    struct in_addr ip;
                    //主机字节序转换网络字节序
                    ip.s_addr = htonl(net + i);
                    list.push_back(inet_ntoa(ip));
                }
            }
            freeifaddrs(addrs);
            return true;
        }

        void HostPair(std::string *i)
        {
                Client client(i->c_str(), _srv_port);
                auto rsp = client.Get("/hostpair");
                if (rsp && rsp->status == 200)
                {
                    std::cerr<< "host" << *i << "pair success!\n";
                    _online_list.push_back(*i);
                }
                return ;
        }
        bool GetOnlineHost(std::vector<std::string> &list)
        {
            _online_list.clear();
            std::vector<std::thread> thr_list(list.size());
            for (int i = 0;i < list.size();i++)
            {
                std::thread thr(&PClient::HostPair, this, &list[i]);
                thr_list[i] = std::move(thr);
            }
            for (int i = 0;i < thr_list.size();i++)
            {
                thr_list[i].join();
            }
            return true;
        }
        bool ShowOnlineHost()
        {
            for(int i = 0;i < _online_list.size(); i++)
            {
                std::cout<< i << ". "<< _online_list[i] <<"\n";
            }
            std::cout << "please choose the host:";
            fflush(stdout);
            std::cin >> _host_idx;
            if(_host_idx < 0 || _host_idx > _online_list.size())
            {
                std::cout<<_host_idx;
                _host_idx = -1;
                std::cerr <<"choose error\n";
                return false;
            }
            return true;
        }
        bool GetFileList()
        {
            Client client(_online_list[_host_idx].c_str(), _srv_port);
            auto rsp = client.Get("/list");
            if(rsp && rsp -> status == 200)
            {
                boost::split(_file_list,rsp->body,boost::is_any_of("\n"));
            }
            return true;
        }
        bool ShowFileList(std::string &name)
        {
            for(int i = 1; i < _file_list.size();i++)
            {
                std::cout<< i << ". "<<_file_list[i] << "\n";
            }
            std::cout <<"please choose file: ";
            fflush(stdout);
            int file_idx;
            std::cin>>file_idx;
            if(file_idx < 0 || file_idx > _file_list.size())
            {
                std::cerr << "choose error\n";
                return false;
            }
            name = _file_list[file_idx];
            return true;
        }

        
        int64_t GetFileSize(std::string &host, std::string &name)
        {
            int64_t fsize = -1;
            Client client(host.c_str(),_srv_port);
            std::string path  = "/lsit" + name;
            auto rsp = client.Head(path.c_str());
            
            if (rsp && rsp->status == 200)
            {
                if(rsp->has_header("Content-length"))
                {
                    return -1;
                }
                std::string len = rsp->get_header_value("Content-length");
                std::stringstream tmp;
                tmp << len;
                tmp >> fsize;
            }
            return fsize;
        }

        void RangeDownload(std::string host, std::string name, int64_t start, int64_t end, bool *res)
        {
            std::string uri = "/lsit/" + name;
            std::string realpath = "DownLoad/" + name;
            std::stringstream range_val;
            range_val << "bytes=" << start << "-" << end;

            *res = false;
            Client clinet(host.c_str(), _srv_port);
            //range : bytes =  start - end;
            Headers header;
            header.insert(std::make_pair("Range", range_val.str().c_str()));
            auto rsp = clinet.Get(uri.c_str(), header);
            
            if(rsp && rsp->status == 206)
            {
                int fd = open(realpath.c_str(), O_CREAT | O_WRONLY, 0664);
                if(fd < 0)
                {
                    std::cerr << "file" << realpath << "open error\n";
                    return;

                }
                lseek(fd, start, SEEK_SET);
                int ret = write(fd, &rsp->body[0], rsp->body.size());

                if(ret < 0)
                {
                    std::cerr << "file" << realpath << "write error\n";
                    close(fd);
                    return ;
                }
                close(fd);
                *res = true;
                std::cerr << "file" << realpath << "DownLoad range: ";
                std::cerr << range_val.str() << "success!\n";
            }
            return ;
        } 

        
        bool DownLoadFile(std::string &name)
        {
            //1.获取文件总长度
            //2.根据文件总长度和分块大小分割线程的下载区域
            //3.创建线程下载指定文件的指定分块数据
            //4.同步等待所有线程结束,获取下载结果

            //url:完整请求路径,统一资源定位符,定义网络中唯一资源
            //uri:资源在服务器上路径,统一资源定位符
            std::string host = _online_list[_host_idx];
            int64_t fsize = GetFileSize(host, name);
            if(fsize < 0)
            {
                std::cerr <<"download file " << name << " failed\n";
                return false;
            }

            int count = fsize / RANGE_SIZE;
            //保存线程对象
            std::vector<boost::thread> thr_list(count + 1);
            std::vector<bool> res_list(count + 1);

            for(int i = 0;i <= count;i++)
            {
                int64_t start, end, rlen;
                start = i * RANGE_SIZE;
                end = (i + 1) * RANGE_SIZE - 1;
                
                //处理最后一个分块
                if (i == count)
                {
                    if((fsize % RANGE_SIZE) == 0)
                    {//表示没没有最后一个分块
                        break;
                    }
                    end = RANGE_SIZE - 1;
                }

                rlen = fsize + 1;
                
                bool res;
                //Range: bytes = start- end
                boost::thread thr(&PClient::RangeDownload, this, host, name, start, end, &res);
                res_list[i] = std::move(res);
                thr_list[i] = std::move(thr);
            }

            bool ret = true;
            for(int i = 0; i <= count ; i++)
            {
                if(i == count && fsize % RANGE_SIZE == 0)
                {
                    break;
                }
                //等待线程退出
                thr_list[i].join();
                if(res_list[i] == false )
                {
                    ret = false;
                }
            }
            if(ret == true)
            {
                std::cout << "download file" << name << "success!\n";
            }else
            {
                std::cerr << "download file" << name << "failed\n";
                return false;
            }
            return true;
        }
        int DoFace()
        {
            std::cout << "0. 退出\n";
            std::cout << "1. 搜索附近主机\n";
            std::cout << "2. 显示在线主机\n";
            std::cout << "3. 显示文件列表\n";

            int choose;
            fflush(stdout);
            std::cout << "Enter your choose: ";
            std::cin>>choose;
            return choose;
        }
    public:
        PClient(uint16_t port):_srv_port(port){}
        bool Start()
        {
            while(1)
            {
                int choose = DoFace();
                std::vector<std::string> list;
                std::string filename;
                switch(choose)
                {
                case 1:
                    GetAllHost(list);
                    GetOnlineHost(list);
                    break;
                case 2:
                    if(ShowOnlineHost() == false)
                    {
                        break;    
                    }
                    GetFileList();
                    break;
                case 3:
                    if(ShowFileList(filename) == false)
                    {
                        break;
                    }
                    DownLoadFile(filename);
                    break;
                case 0:
                    exit(0);
                default:
                    break;
                }
            }
        }
};

int main ()
{
    PClient client (10086);
    client.Start();
    return 0;
}

