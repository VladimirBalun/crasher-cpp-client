#pragma once

#include <boost/beast/core.hpp>
#include <boost/beast/http.hpp>
#include <boost/beast/version.hpp>
#include <boost/asio/connect.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <boost/core/noncopyable.hpp>

namespace Crashser
{

    class CoreDump;

    class DumpServerConnector : private boost::noncopyable
    {
        using OnResponse = std::function<void(const std::string&)>;
    public:
        DumpServerConnector(std::string host, std::string port);
        void sendCoreDump(const CoreDump& core_dump, OnResponse onResponse = nullptr);
        ~DumpServerConnector();
    private:
        boost::asio::io_context m_ioc;
        boost::asio::ip::tcp::resolver m_resolver;
        boost::beast::tcp_stream m_stream;
    };

}
