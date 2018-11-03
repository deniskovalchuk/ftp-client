#include "request_handler.hpp"
#include "request_parser.hpp"

bool request_handler::execute(const string & request)
{
    vector<string> parsed_request = request_parser::parse(request);

    if (parsed_request.empty())
    {
        return true;
    }

    return true;
}
