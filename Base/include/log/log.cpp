
#include "log.h"
#include "category.h"

namespace base
{
    Log::Log()
        : log_agent_(nullptr)
    {

    }

    Log::~Log()
    {

    }


    Category* Log::GetCategoryIns(const std::string& name) const
    {
        return nullptr;
    }

    void Log::AttachCategory(Category* category)
    {

    }

    void Log::OutputA(const LogFormat& logFormat, char* format, ...)
    {

    }

    void Log::OutputW(const LogFormat &logFormat, wchar_t *format, ...)
    {

    }

    void Log::OutputBin(const unsigned char *addr, unsigned long len)
    {

    }
}

