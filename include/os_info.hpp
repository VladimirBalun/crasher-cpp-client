#pragma once

#include <boost/version.hpp>
#include <boost/config.hpp>

namespace Crashser
{

    class OSInfo
    {
    public:
        OSInfo(std::string name = BOOST_PLATFORM, std::string version = "", std::string architecture = "")
            : m_name{std::move(name)}, m_version{std::move(version)}, m_architecture{std::move(architecture)} {}

        void setName(std::string name) { m_name = std::move(name); }
        void setArchitecture(std::string architecture) { m_architecture = std::move(architecture); }
        void setVersion(std::string version) { m_version = std::move(version); }

        const std::string& getName() const noexcept { return m_name; }
        const std::string& getArchitecture() const noexcept { return m_architecture; }
        const std::string& getVersion() const noexcept { return m_version; }
    private:
        std::string m_name;
        std::string m_version;
        std::string m_architecture;
    };

}
