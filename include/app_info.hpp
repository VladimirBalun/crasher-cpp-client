#pragma once

#include <string>

namespace Crashser
{

    class AppInfo
    {
    public:
        AppInfo() = default;
        AppInfo(std::string name, std::string version = "", std::string programming_language = "C++")
            : m_name{std::move(name)}, m_version{std::move(version)}, m_programming_language{std::move(programming_language)} {}

        void setName(std::string name) { m_name = std::move(name); }
        void setVersion(std::string version) { m_version = std::move(version); }
        void setProgrammingLanguage(std::string programming_language) { m_programming_language = std::move(programming_language); }

        const std::string& getName() const noexcept { return m_name; };
        const std::string& getVersion() const noexcept { return m_version; };
        const std::string& getProgrammingLanguage() const noexcept { return m_programming_language; };
    private:
        std::string m_name;
        std::string m_version;
        std::string m_programming_language = "C++";
    };

}