#pragma once

#include <string_view>
#include "parser/http_types.hpp"

namespace parser {

    class HttpParser {
        public:
            bool parser(std::string_view input, HttpRequest& request);
        
        private:
            bool parser_request_line(std::string_view line, HttpRequest& request);
            bool parser_header_line(std::string_view line, HttpRequest& request);
    };
    
} // namespace parser

