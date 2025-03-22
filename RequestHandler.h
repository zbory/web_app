#pragma once

#include <boost/beast.hpp>

namespace beast = boost::beast;
namespace http = beast::http;

class RequestHandler
{
public:
    virtual ~RequestHandler() = default;
    virtual std::string handle(const http::request<http::string_body>& req, http::response<http::string_body>& res) = 0;
};