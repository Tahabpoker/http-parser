#pragma once

#include <string>
#include <vector>

namespace parser {

    struct Header {
      std::string key;
      std::string value;  
    };

    struct HttpRequest {
        std::string method;
        std::string uri;
        std::string version;
        std::vector<Header> headers;
    };

} // namespace parser


