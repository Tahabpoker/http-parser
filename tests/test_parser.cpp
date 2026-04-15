#include "parser/http_parser.hpp"

#include <cassert>
#include <iostream>
#include <string_view>

using namespace parser;

void test_valid_request() {
    
    std::string_view raw = 
        "GET /index.html HTTP/1.1\r\n"
        "Host: example.com\r\n"
        "Connection: close\r\n"
        "\r\n";
    
    HttpParser parser;
    HttpRequest request;

    bool ok = parser.parser(raw, request);

    assert(ok);
    assert(request.method == "GET");
    assert(request.uri == "/index.html");
    assert(request.version == "HTTP/1.1");
    assert(request.headers.size() == 2);
    assert(request.headers[0].key == "Host");
    assert(request.headers[0].value == "example.com");
    assert(request.headers[1].key == "Connection");
    assert(request.headers[1].value == "close");
}

void test_invalid_request_line() {
 
    std::string_view raw = 
        "GET /index.html\r\n"
        "Host: example.com\r\n"
        "\r\n";

    HttpParser parser;
    HttpRequest request;
    
    bool ok = parser.parser(raw, request);
    assert(!ok);

}

void test_invalid_header() {
 
    std::string_view raw = 
        "GET / HTTP/1.1\r\n"
        "Host: example.com\r\n"
        "\r\n";

    HttpParser parser;
    HttpRequest request;
    
    bool ok = parser.parser(raw, request);
    assert(!ok);

}

int main() {
    test_valid_request();
    test_invalid_request_line();
    test_invalid_header();

    std::cout << "All parser tests passed\n";
    return 0;
}