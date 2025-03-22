#pragma once

#include <cstdint>
#include <boost/asio.hpp>
#include "RequestHandler.h"

class Server
{
public:
    explicit Server(std::uint16_t port_number);
    void run();
    void register_handler(const std::string& name, std::unique_ptr<RequestHandler> handler);

private:
    boost::asio::io_context io_ctx_;
    boost::asio::ip::tcp::acceptor acceptor_;
    std::unordered_map<std::string, std::unique_ptr<RequestHandler>> handlers_;

    void handle_connection(boost::asio::ip::tcp::socket socket);
};