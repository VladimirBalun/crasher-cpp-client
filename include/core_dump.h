#pragma once

#include <vector>
#include <string>
#include <chrono>

#include "os_info.h"
#include "app_info.h"

namespace Crashser
{

    inline std::uint64_t getCurrentTimestamp()
    {
        using namespace std::chrono;
        return duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
    }

    class CoreDump
    {
    public:
        CoreDump(std::string core_dump_data, const OSInfo* os_info, const AppInfo* app_info, std::uint64_t timestamp = getCurrentTimestamp())
            : m_os_info{os_info}, m_app_info{app_info}, m_core_dump_data{std::move(core_dump_data)}, m_timestamp{timestamp} {}
        void addExtension(std::pair<std::string, std::string> ext) { m_extensions.push_back(std::move(ext)); }
        const OSInfo* getOSInfo() const noexcept { return m_os_info; }
        const AppInfo* getAppInfo() const noexcept { return m_app_info; }
        const std::vector<std::pair<std::string, std::string>>& getExtensions() const noexcept { return m_extensions; }
        const std::string& getCoreDumpData() const noexcept { return m_core_dump_data; }
        std::uint64_t getTimestamp() const noexcept { return m_timestamp; }
    private:
        const OSInfo* m_os_info;
        const AppInfo* m_app_info;
        std::vector<std::pair<std::string, std::string>> m_extensions;
        std::string m_core_dump_data;
        std::uint64_t m_timestamp;
    };

}