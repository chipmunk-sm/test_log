#include "logger.h"

//**************************************
//+ CLogger
//**************************************

CLogger& CLogger::Instance()
{
    static CLogger thisInstance;
    return thisInstance;
}

CLogger::CLogger()
{
    dummy[0] =0;
    try
    {
#if defined(WINDOWS_PLATFORM)
        fopen_s(&m_dummyFile, "NUL", "wb");
#else
        m_dummyFile = fopen("/dev/null", "wb");
#endif
    }
    catch (...)
    {
        std::_Exit(-10);
    }
    try
    {
        //OpenLogFile();
    }
    catch (...)
    {
        std::_Exit(-20);
    }
}

CLogger::~CLogger()
{
    std::lock_guard<std::mutex> mlock(m_mutexLog);
    m_bExit = true;
    //CloseLogFile();
    if (m_dummyFile != nullptr)
        fclose(m_dummyFile);
}

void CLogger::SetDisplayExtInfo(bool val) {
    m_displayExtInfo = val;
}

const wchar_t* CLogger::GetErrorLevelStr(const CLogger::eLogLevel lvl, const std::wstring&)
{
    switch (lvl) {
    case eLogLevel_error: return L";E;";
    case eLogLevel_info:  return L";I;";
    case eLogLevel_trace: return L";T;";
    }
    return L";U;";
}

const char* CLogger::GetErrorLevelStr(const CLogger::eLogLevel lvl, const std::string&)
{
    switch (lvl) {
    case eLogLevel_error: return ";E;";
    case eLogLevel_info:  return ";I;";
    case eLogLevel_trace: return ";T;";
    }
    return ";U;";
}

std::string CLogger::GetTimestamp(const std::string&)
{
    auto timeUtc = std::chrono::system_clock::now();
    auto ttime_t = std::chrono::system_clock::to_time_t(timeUtc);
    auto timeInSeconds = std::chrono::system_clock::from_time_t(ttime_t);
    auto ms = std::chrono::duration_cast<std::chrono::microseconds>(timeUtc - timeInSeconds);


#if defined(_MSC_VER) || defined(__MINGW32__) || defined(__MINGW64__)
    struct tm  gmTime;
    gmtime_s(&gmTime, &ttime_t);// Coordinated Universal Time (UTC).
    struct tm  localTime;
    localtime_s(&localTime, &ttime_t);// local Time
#else
    struct tm gmTime;
    gmtime_r(&ttime_t, &gmTime);// Coordinated Universal Time (UTC).
    struct tm  localTime;
    localtime_r(&ttime_t, &localTime);// local Time
#endif

    int32_t offset = static_cast<int32_t>(mktime(&localTime) - mktime(&gmTime)) / 3600;

    const auto& printTime = localTime;

    auto res = stringutils::FormatString(
             "%04" PRId32
            "-%02" PRId32
            "-%02" PRId32
            " %02" PRId32
            ":%02" PRId32
            ":%02" PRId32
            ".%06" PRIu64
            " %+03" PRId32 "00",
            1900 + printTime.tm_year,
            1 + printTime.tm_mon,
            printTime.tm_mday,

            printTime.tm_hour,
            printTime.tm_min,
            printTime.tm_sec,
            static_cast<uint64_t>(ms.count()),// milliseconds or microseconds
            offset);

    return res;
}

std::wstring CLogger::GetTimestamp(const std::wstring&)
{
    return stringutils::ConvertA2W(GetTimestamp(""), true);
}

#define MACROREPLACESYMBOLS \
    ADDSYM("%hs", "");\
    ADDSYM("%s", "");\
    ADDSYM("%wZ", "");\
    ADDSYM("\n\r", " ");\
    ADDSYM("\n", " ");\
    ADDSYM("\r", " ");\
    ADDSYM("%", "%%");

std::string ClearMessage(std::string val)
{
#undef  ADDSYM
#define ADDSYM(oldVal,newVal) stringutils::replaceSubstringWithString(val, oldVal, newVal);
    MACROREPLACESYMBOLS;
#undef  ADDSYM
    return val;
}

std::wstring ClearMessage(std::wstring val)
{
#undef  ADDSYM
#define ADDSYM(oldVal,newVal) stringutils::replaceSubstringWithString(val, L##oldVal, L##newVal);
    MACROREPLACESYMBOLS;
#undef ADDSYM
    return val;
}

std::string CLogger::GetErrorStringA(const int32_t errorCode) {
    std::vector<char> buf(20, 0);
    std::snprintf(buf.data(), buf.size(), "[0x%08X] ", errorCode);
    return std::string(buf.data()) + ClearMessage(std::system_category().message(errorCode));
}

std::wstring CLogger::GetErrorStringW(const int32_t errorCode) {
    std::vector<wchar_t> buf(1024, 0);
    const auto &len = std::swprintf(buf.data(), buf.size() - 1, L"[0x%08X] ", errorCode);
    if (len < 1)
        return  L"[" + std::to_wstring(errorCode) + L"]";

#if defined(WINDOWS_PLATFORM)
    FormatMessageW(FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS, nullptr, 
        static_cast<DWORD>(errorCode),
        MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), buf.data() + len, static_cast<DWORD>(buf.size()) - len - 1, nullptr);
    return ClearMessage(buf.data());
#else
    UNREFERENCED_PARAMETER_LOG(len);
    return buf.data();
#endif
}

void CLogger::PrintExtInfo(std::string& val, const char* szFile, const char* szFunc, const int iLine) {
    val += ";";
    val += szFile;
    val += ";";
    val += szFunc;
    val += ";";
    val += std::to_string(iLine);
}

void CLogger::PrintExtInfo(std::wstring& val, const char* szFile, const char* szFunc, const int iLine) {
    val += L";";
    val += stringutils::Latin1ToStdWString(szFile);
    val += L";";
    val += stringutils::Latin1ToStdWString(szFunc);
    val += L";";
    val += std::to_wstring(iLine);
}

void CLogger::BufferOut(const std::string &val, bool isError) {
#if defined(USEQDEBUG)
    UNREFERENCED_PARAMETER_LOG(isError);
    qDebug() << QString().fromStdString(val);
#else
    if (isError) {
        std::cerr << val.c_str();
        std::cerr << std::endl;
        if (std::cerr.fail()) {
            std::cerr.clear();
            std::cerr << std::endl;
        }
    } else {
        std::cout << val.c_str();
        std::cout << std::endl;
        if (std::cout.fail()) {
            std::cout.clear();
            std::cout << std::endl;
        }
    }
#endif
}

void CLogger::BufferOut(const std::wstring &val, bool isError) {
#if defined(USEQDEBUG)
    UNREFERENCED_PARAMETER_LOG(isError);
    qDebug() << QString().fromStdWString(val);
#else
    if (isError) {
        std::wcerr << val.c_str();
        std::wcerr << std::endl;
        if (std::wcerr.fail()) {
            std::wcerr.clear();
            std::wcerr << std::endl;
        }
    } else {
        std::wcout << val.c_str();
        std::wcout << std::endl;
        if (std::wcout.fail()) {
            std::wcout.clear();
            std::wcout << std::endl;
        }
    }
#endif
}

//**************************************
//~ CLogger
//**************************************
