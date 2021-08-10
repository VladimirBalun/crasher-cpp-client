#pragma once

#ifndef _GNU_SOURCE
    #define _GNU_SOURCE
#endif

#include <string>
#include <boost/stacktrace.hpp>
#include <boost/exception/all.hpp>

namespace Crashser
{

    template<typename Exception>
    void throwWithStackTrace(const Exception& e) {
        using traced = boost::error_info<struct tag_stacktrace, boost::stacktrace::stacktrace>;
        auto temp = boost::enable_error_info(e) << traced(boost::stacktrace::stacktrace());
        throw temp;
    }

    template<typename Exception>
    std::string getStackTrace(const Exception& e)
    {
        using traced = boost::error_info<struct tag_stacktrace, boost::stacktrace::stacktrace>;
        const boost::stacktrace::stacktrace* stack_trace = boost::get_error_info<traced>(e);
        if (stack_trace) {
            return to_string(*stack_trace);
        } else {
            return boost::diagnostic_information(e);
        }
    }

    inline std::string getStackTrace()
    {
        return to_string(boost::stacktrace::stacktrace());
    }

}

