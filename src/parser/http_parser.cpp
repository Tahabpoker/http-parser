#include "parser\http_parser.hpp"

#include <string>

namespace parser {
    
    bool HttpParser::parser(std::string_view input, HttpRequest& request) {
        request = HttpRequest{};

        std::size_t pos = 0;
        bool first_line = true;

        while(pos < input.size()) {
            std::size_t line_end = input.find("\r\n", pos);
            if(line_end == std::string_view::npos) {
                return false;
            }

            std::string_view line = input.substr(pos, line_end - pos);
            pos = line_end + 2;

            if(line.empty()) {
                return true;
            }

            if(first_line) {
                if(!parser_request_line(line, request)) {
                    return false;
                }
                first_line = false;
            } else {
                if(!parser_header_line(line, request)) {
                    return false;
                }
            }
        }
        return false;
    }

    bool HttpParser::parser_request_line(std::string_view line, HttpRequest& request) {
        std::size_t first_space = line.find(' ');
        if(first_space == std::string_view::npos) {
            return false;
        }

        std::size_t second_space = line.find(' ', first_space + 1);
        if(second_space == std::string_view::npos) {
            return false;
        }

        request.method = std::string(line.substr(0, first_space));
        request.uri = std::string(line.substr(first_space + 1, second_space - first_space - 1));
        request.version = std::string(line.substr(second_space + 1));

        if(request.method.empty() || request.uri.empty() || request.version.empty()) {
            return false;
        }

        return true;
    }

    bool HttpParser::parser_header_line(std::string_view line, HttpRequest& request) {
        std::size_t colon = line.find(':');
        if(colon == std::string_view::npos || colon == 0) {
            return false;
        }

        std::string key(line.substr(0, colon));

        std::size_t value_start = colon + 1;
        while(value_start < line.size() && line[value_start] == ' ') {
            ++value_start;
        }

        std::string value(line.substr(value_start));

        request.headers.push_back(Header{std::move(key), std::move(value)});
        return true;
    }

} // namespace parser 