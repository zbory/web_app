#pragma once

#include "RequestHandler.h"

class ButtonHandler : public RequestHandler
{
public:
    std::string handle(const http::request<http::string_body>& req, http::response<http::string_body>& res) override
    {
        ++pressCounter_;
        std::stringstream ss;
        ss <<  R"({"pressCount": )" << pressCounter_ << "}";
        return ss.str();
    }
private:
    std::uint32_t pressCounter_{0};
};