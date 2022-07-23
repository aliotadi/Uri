#include <memory>

namespace Uri
{

    class Uri
    {
    public:
        ~Uri();
        Uri(const Uri &) = delete;
        Uri(Uri &&) = delete;
        Uri &operator=(const Uri &) = delete;
        Uri &operator=(Uri &&) = delete;

    public:
        Uri();

    private:
        struct Impl;

        std::unique_ptr<struct Impl> impl_;
    };
}

#endif
