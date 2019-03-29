#include <fstream>
#include <json.hpp>
#include "configuration.h"

using json = nlohmann::json;

Configuration::Configuration(const std::string &file) {
    std::ifstream file_stream(file);
    json j;
    file_stream >> j;

    json handler = j["handler"];
    this->handler_configuration = handler.get_ref<json::object_t &>();

    this->name = j["name"].get<std::string>();
    this->port = j["port"].get<std::uint_fast16_t>();
}