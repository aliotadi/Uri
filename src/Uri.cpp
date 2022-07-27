#include<string>
#include <Uri/Uri.hpp>

namespace Uri
{
    struct Uri::Impl
    {
        std::string pathDelimiter = "/";
        std::string scheme;
        std::string host;
        std::vector< std::string > path;
    };

    Uri::~Uri() = default;

    Uri::Uri() : impl_(new Impl)
    {
    }

    void Uri::SetPathDelimiter(const std::string& newPathDelimiter) {
        impl_->pathDelimiter = newPathDelimiter;
    }

    bool Uri::ParseFromString(const std::string& uriString) {
        // parse the scheme
        const auto schemeEnd = uriString.find(':');
        impl_->scheme = uriString.substr(0, schemeEnd);

        auto rest = uriString.substr(schemeEnd + 1);

        // parse the host
        if (rest.substr(0, 2) == "//") {
            const auto authorityEnd = rest.find(impl_->pathDelimiter, 2);
            impl_->host = rest.substr(2, authorityEnd - 2);
            rest = rest.substr(authorityEnd);
        }
        else {
            impl_->host.clear();
        }

        // parse the path
        impl_->path.clear();
        if (rest == impl_->pathDelimiter) {
            impl_->path.emplace_back("");
        }
        else if (!rest.empty())
            for (;;) {
                auto pathDelimiter = rest.find(impl_->pathDelimiter);
                if (pathDelimiter == std::string::npos) {
                    impl_->path.emplace_back(rest);
                    break;
                }
                impl_->path.emplace_back(
                    rest.begin(),
                    rest.begin() + pathDelimiter
                );
                rest = rest.substr(pathDelimiter + impl_->pathDelimiter.length());
            }

        return true;
    }

    std::string Uri::GetScheme() const {
        return impl_->scheme;
    }

    std::string Uri::GetHost() const {
        return impl_->host;
    }

    std::vector< std::string > Uri::GetPath() const {
        return impl_->path;
    }
}
