#ifndef URI_HPP
#define URI_HPP

#include <memory>
#include <string>
#include <vector>

namespace Uri
{

    class Uri
    {
    public:
        ~Uri();
        Uri(const Uri&) = delete;
        Uri(Uri&&) = delete;
        Uri& operator=(const Uri&) = delete;
        Uri& operator=(Uri&&) = delete;

    public:
        Uri();

        void SetPathDelimiter(const std::string& newPathDelimiter);

        bool ParseFromString(const std::string& uriString);

        std::string GetScheme() const;

        std::string GetHost() const;

        std::vector< std::string > GetPath() const;

    private:
        struct Impl;

        std::unique_ptr<struct Impl> impl_;
    };
}

#endif
