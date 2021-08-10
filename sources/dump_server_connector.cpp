#include "dump_server_connector.hpp"

#include "core_dump.hpp"
#include "json_serializer.hpp"

Crashser::DumpServerConnector::DumpServerConnector(std::string host, std::string port)
    : m_ioc{}, m_resolver{m_ioc}, m_stream{m_ioc}
{
    auto const resolve_result = m_resolver.resolve(host, port);
    m_stream.connect(resolve_result);
}

void Crashser::DumpServerConnector::sendCoreDump(const CoreDump& core_dump, OnResponse onResponse)
{
    constexpr int HTTP_VERSION = 11;
    boost::beast::http::request<boost::beast::http::string_body> request{boost::beast::http::verb::post, "/core_dump", HTTP_VERSION};
    request.set(boost::beast::http::field::content_type, "application/json");
    request.set(boost::beast::http::field::user_agent, BOOST_BEAST_VERSION_STRING);
    request.body() = JSONSerializer::serialize(core_dump);
    boost::beast::http::write(m_stream, request);

    if (onResponse) {
        boost::beast::flat_buffer buffer{};
        boost::beast::http::response<boost::beast::http::dynamic_body> response{};
        boost::beast::http::read(m_stream, buffer, response);
        onResponse(boost::beast::buffers_to_string(response.body().data()));
    }
}

Crashser::DumpServerConnector::~DumpServerConnector()
{
    boost::beast::error_code error_code;
    m_stream.socket().shutdown(boost::asio::ip::tcp::socket::shutdown_both, error_code);
}
