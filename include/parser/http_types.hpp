#pragma once

#include <string_view>
#include <vector>

namespace parser {
    struct Header {
        std::string_view key;
        std::string_view value;  
    };

    struct HttpRequest {
        std::string_view method;
        std::string_view uri;
        std::string_view version;
        std::vector<Header> headers;
    };

} // namespace parser


