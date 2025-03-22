#include <iostream>
#include "Server.h"

Server::Server(std::uint16_t port_number)
    : acceptor_(io_ctx_, {boost::asio::ip::tcp::v4(), port_number})     //  {endpoint != socket}
{}

void Server::register_handler(const std::string& name, std::unique_ptr<RequestHandler> handler)
{
    handlers_[name] = std::move(handler);
}

void Server::run()
{
    std::cout << "Server listening on port " << acceptor_.local_endpoint().port() << "...\n";
    while(true)
    {
        boost::asio::ip::tcp::socket socket(io_ctx_);
        acceptor_.accept(socket);
        handle_connection(std::move(socket));
    }
}

void Server::handle_connection(boost::asio::ip::tcp::socket socket)
{
    std::cout << "handling request\n";
    try {
        beast::flat_buffer buffer;
        http::request<http::string_body> req;
        http::read(socket, buffer, req);

        std::string target = req.target().to_string();
        std::cout << "Received request for: " << target << '\n';
        
        http::response<http::string_body> res;
        res.version(req.version());
        res.set(http::field::content_type, "application/json");

        if(handlers_.count(target)) {
            res.body() = handlers_[target]->handle(req, res);
        } else {
            res.result(http::status::not_found);
        }

        res.prepare_payload();
        http::write(socket, res);
    } catch (const std::exception& e) {
        std::cerr << "Connection error: " << e.what() << '\n';
    }
}