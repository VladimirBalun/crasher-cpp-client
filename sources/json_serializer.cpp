#include "json_serializer.hpp"

#include "core_dump.hpp"

#define PUT_IN_JSON_IF_EXISTS(json, key, value) \
    do { if(!value.empty()) json.put(key, value); } while(false)

std::string Crashser::JSONSerializer::serialize(const CoreDump& core_dump)
{
    boost::property_tree::ptree core_dump_json{};
    boost::property_tree::ptree os_info_json = serialize(core_dump.getOSInfo());
    boost::property_tree::ptree app_info_json = serialize(core_dump.getAppInfo());
    core_dump_json.add_child("os_info", std::move(os_info_json));
    core_dump_json.add_child("app_info", std::move(app_info_json));
    core_dump_json.put("data", core_dump.getCoreDumpData());
    core_dump_json.put("timestamp", core_dump.getTimestamp());
    for (const auto& extension : core_dump.getExtensions()) {
        core_dump_json.put(extension.first, extension.second);
    }

    std::ostringstream oss{};
    boost::property_tree::json_parser::write_json(oss, core_dump_json);
    return oss.str();
}

boost::property_tree::ptree Crashser::JSONSerializer::serialize(const OSInfo* os_info)
{
    boost::property_tree::ptree os_info_json{};
    if (os_info) {
        PUT_IN_JSON_IF_EXISTS(os_info_json, "name", os_info->getName());
        PUT_IN_JSON_IF_EXISTS(os_info_json, "architecture", os_info->getArchitecture());
        PUT_IN_JSON_IF_EXISTS(os_info_json, "version", os_info->getVersion());
    }
    return os_info_json;
}

boost::property_tree::ptree Crashser::JSONSerializer::serialize(const AppInfo* app_info)
{
    boost::property_tree::ptree app_info_json{};
    if (app_info) {
        PUT_IN_JSON_IF_EXISTS(app_info_json, "name", app_info->getName());
        PUT_IN_JSON_IF_EXISTS(app_info_json, "version", app_info->getVersion());
        PUT_IN_JSON_IF_EXISTS(app_info_json, "programming_language", app_info->getProgrammingLanguage());
    }
    return app_info_json;
}
