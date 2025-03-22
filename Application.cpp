#include "Server.h"
#include "ButtonHandler.h"

int main()
{
    const uint16_t port_number{8888};

    Server server(port_number);
    server.register_handler("/api/button_press", std::make_unique<ButtonHandler>());

    server.run();

    return 0;
}