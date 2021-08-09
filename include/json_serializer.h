#pragma once

#include <vector>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>

namespace Crashser
{

    class OSInfo;
    class AppInfo;
    class CoreDump;

    class JSONSerializer
    {
    public:
        static std::string serialize(const CoreDump& core_dump);
    private:
        static boost::property_tree::ptree serialize(const OSInfo* os_info);
        static boost::property_tree::ptree serialize(const AppInfo* app_info);
    };

}