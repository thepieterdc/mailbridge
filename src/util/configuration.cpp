#include <fstream>
#include <json.hpp>
#include "configuration.h"

using json = nlohmann::json;

Configuration::Configuration(const std::string &file) {
    std::ifstream file_stream(file);
    json j;
    file_stream >> j;

    this->port = static_cast<std::uint_fast16_t>(j["port"]);
}