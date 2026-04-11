#include "parser/http_parser.hpp"

#include <iostream>
#include <string_view>

int main()
{

    std::string_view raw =
        "GET /hello HTTP/1.1\r\n"
        "Host: localhost\r\n"
        "\r\n";

    parser::HttpParser parser;
    parser::HttpRequest request;

    if(!parser.parser(raw, request)) {
        std::cout << "parser failed" << std::endl;
        return 1;
    }

    std::cout << "method: " << request.method << std::endl;
    std::cout << "URI: " << request.uri << std::endl;
    std::cout << "Version: " << request.version << std::endl;

    for(const auto& header : request.headers) {
        std::cout << header.key << ": " << header.value << std::endl;
    }

    return 0;
}
