#pragma once

#ifndef LOGGER_H
#define LOGGER_H

#define CONFIG_LOG_NAME "LOG_NAME"

//use in main before start logging
#define LOG_INITIALIZE() CLogger::Instance()

// enable or disable display source file, function name and line number in log
#define LOG_EXTENDEDLOG(val) CLogger::Instance().SetDisplayExtInfo(val)

// flush data from the log buffer
#define LOG_FLUSH()  CLogger::Instance().Flush();


#if defined(_MSC_VER)
#define MSVC_COMPILER 1
#endif

#if defined(_WIN32) || defined(WIN32) || defined(_WIN64) || defined(WIN64) || defined(__WINNT__)
#define WINDOWS_PLATFORM 1
#endif


//////////////  START string helper macros

#if defined(WINDOWS_PLATFORM)

// COMPILE TIME OS DEPENDED (Windows "std::wstring"; Linux "std::string") 
#define STRINGEXT std::wstring

// COMPILE TIME OS DEPENDED (for Windows make L""; for Linux make "") 
#define DONOTUSEDIRECTLY_ST(str) L##str
#define ST(str) DONOTUSEDIRECTLY_ST(str)

// COMPILE TIME OS DEPENDED (Windows "wchar_t"; Linux "char") 
#define PRF_T_STRING L"%ls"

// string format for char "%s"
#define PRF_CH_STRING "%s"

// string format for wchar_t "%ls"
#define PRF_W_STRING L"%ls"

#else

// COMPILE TIME OS DEPENDED (Windows "std::wstring"; Linux "std::string") 
#define STRINGEXT std::string

// COMPILE TIME OS DEPENDED (for Windows make L""; for Linux make "") 
#define ST(str) str

// COMPILE TIME OS DEPENDED (Windows "wchar_t"; Linux "char") 
#define PRF_T_STRING "%s"

// string format for char "%s"
#define PRF_CH_STRING "%s"

// string format for wchar_t "%ls"
#define PRF_W_STRING  L"%ls"

#endif

// preprocessor make string from number
#define quoteStr1(XXX1) #XXX1
#define quoteStr(XXX2) quoteStr1(XXX2)

// preprocessor make "wide char string" from "char string" 
#define TOWSTRING1(x) L##x
#define TOWSTRING(x) TOWSTRING1(x)

 
#if defined(__cplusplus) && (__cplusplus >= 201703L)

// append wchar_t string "STR" to the std::string "SRC" or vice-versa
#define STRAPPEND(SRC, STR ) stringutils::strAppendX(SRC, STR)
#define STRAPPEND2(SRC, STR ) stringutils::strAppendX(SRC, STR )

#else

// append char or wchar_t string "STR" to the std::string or wstring "SRC"
#define STRAPPEND(SRC, STR ) stringutils::strAppend(SRC, ( STR ), TOWSTRING( STR ) )

//append wchar_t string "STR" to the std::string "SRC" or vice-versa
#define STRAPPEND2(SRC, STR ) stringutils::strAppend(SRC, ( STR ))

#endif

////////////// END string helper macros




//C++98 = 199711L; C++11 = 201103L; C++14 = 201402L; C++17 = 201703L; C++20 = 202002L
#if defined(__cplusplus) && (__cplusplus < 201703L)
#define STDCCODECVTPRESENT 1
#else
#define STDCCODECVTPRESENT 1
#endif // __cplusplus < 201703L

// ============ START INCLUDE SECTION

#if defined(MSVC_COMPILER)
#pragma warning( push )
#pragma warning( disable : 4365 ) // conversion from '' to ''
#pragma warning( disable : 4371 ) // layout of class may have changed from a previous version of the compiler due to better packing of member
#pragma warning( disable : 4668 ) // is not defined as a preprocessor macro
#pragma warning( disable : 4710 ) // function not inlined
#pragma warning( disable : 4625 ) // '' : copy constructor was implicitly defined as deleted
#pragma warning( disable : 4626 ) // assignment operator was implicitly defined as deleted
#pragma warning( disable : 4711 ) // selected for automatic inline expansion
#pragma warning( disable : 4820 ) // bytes padding added after data member
#pragma warning( disable : 4946 ) // reinterpret_cast used between related classes
#pragma warning( disable : 5026 ) // move constructor was implicitly defined as deleted
#pragma warning( disable : 5027 ) // move assignment operator was implicitly defined as deleted
#pragma warning( disable : 5039 ) // pointer or reference to potentially throwing function passed to 'extern "C"' function under - EHc.Undefined behavior may occur if this function throws an exception.
#pragma warning( disable : 5219 ) // implicit conversion from 'int' to 'float', possible loss of data

#   if _MSC_VER >= 1934
#   pragma warning( disable : 5262 ) // implicit fall-through occurs here
#   pragma warning( disable : 5264 ) // 'const' variable is not used
#   endif

#endif // defined(MSVC_COMPILER)

#if defined(WINDOWS_PLATFORM)
#   include <Windows.h>
#endif // defined(WINDOWS_PLATFORM)

//#define __STDC_WANT_LIB_EXT1__ 1

//#include <QString>

#include <iostream>
#include <string>
#include <map>
#include <atomic>
#include <thread>
#include <vector>
#include <mutex>
#include <exception>
#include <deque>
#include <sstream>
#include <iomanip>
#include <locale>
#include <algorithm>
#include <cinttypes>
#include <cassert>
#include <fstream>
#include <type_traits>

#ifdef STDCCODECVTPRESENT
#include <codecvt>
#endif // STDCCODECVTPRESENT

#if defined(__cplusplus) && (__cplusplus >= 201703L)
#include <filesystem>
#define USESTDFILESYSTEM 1
#endif // __cplusplus < 201703L

#include <time.h>
#include <inttypes.h>

#ifdef __GLIBC__
#include <gnu/libc-version.h>
#endif


#if defined(__ANDROID__)
#include <QDebug>
#define USEQDEBUG 1
#else
//#define USEQDEBUG 0
#endif

#if defined(MSVC_COMPILER)
#pragma warning( pop )
#pragma warning(disable : 4514) // unreferenced inline function has been removed
#endif

#if defined(MSVC_COMPILER)
#define FATTR(par1,par2) 
#else
#define FATTR(par1,par2) __attribute__((format(printf, par1, par2)));
#define _Printf_format_string_ 
#endif


// ============ END INCLUDE SECTION

#if __cplusplus >= 199711L
using namespace std::chrono_literals;
#else
constexpr std::chrono::seconds operator "" s(unsigned long long x_val)
{
    return (std::chrono::seconds(x_val));
}

constexpr std::chrono::milliseconds operator "" ms(unsigned long long x_val)
{
    return (std::chrono::milliseconds(x_val));
}
#endif



#ifndef UNREFERENCED_PARAMETER_LOG
#define UNREFERENCED_PARAMETER_LOG(expr) do { (void)(expr); } while (0)
#endif //UNREFERENCED_PARAMETER_LOG

#if defined(__ANDROID__) || defined(Q_OS_ANDROID)
#define ANDROIDPRESENT 1
#endif // Q_OS_ANDROID





// ============ START _ASSERT SECTION

#ifndef _ASSERT

#  if defined(_MSC_VER) || defined(__INTEL_COMPILER)
#    define EXTASSERT() __debugbreak()
#  elif defined(__ARMCC_VERSION)
#    define EXTASSERT() __breakpoint(42)
#  elif defined(__ibmxl__) || defined(__xlC__)
#    include <builtins.h>
#    define EXTASSERT() __trap(42)
#  elif defined(__DMC__) && defined(_M_IX86)
     inline void EXTASSERT(void) { __asm int 3h; }
#  elif defined(__i386__) || defined(__x86_64__)
     inline void EXTASSERT(void) { __asm__ __volatile__("int3"); }
#  elif defined(__thumb__)
     inline void EXTASSERT(void) { __asm__ __volatile__(".inst 0xde01"); }
#  elif defined(__aarch64__)
     inline void EXTASSERT(void) { __asm__ __volatile__(".inst 0xd4200000"); }
#  elif defined(__arm__)
     inline void EXTASSERT() { __asm__ __volatile__(".inst 0xe7f001f0"); }
#  elif defined (__alpha__) && !defined(__osf__)
     inline void EXTASSERT(void) { __asm__ __volatile__("bpt"); }
#  elif defined(_54_)
     inline void EXTASSERT(void) { __asm__ __volatile__("ESTOP"); }
#  elif defined(_55_)
     inline void EXTASSERT(void) { __asm__ __volatile__(";\n .if (.MNEMONIC)\n ESTOP_1\n .else\n ESTOP_1()\n .endif\n NOP"); }
#  elif defined(_64P_)
     inline void EXTASSERT(void) { __asm__ __volatile__("SWBP 0"); }
#  elif defined(_6x_)
     inline void EXTASSERT(void) { __asm__ __volatile__("NOP\n .word 0x10000000"); }
#  elif defined(__STDC_HOSTED__) && (__STDC_HOSTED__ == 0) && defined(__GNUC__)
#    define EXTASSERT() __builtin_trap()
#  else
#    include <signal.h>
#    if defined(SIGTRAP)
#      define EXTASSERT() raise(SIGTRAP)
#    else
#      define EXTASSERT() raise(SIGABRT)
#    endif
#  endif

#if defined(_DEBUG) || defined(DEBUG) || defined(QT_QML_DEBUG) || defined(QT_DEBUG)
#   define _ASSERT(expr) { if (!(expr)) { EXTASSERT();} }
#else
#   define _ASSERT(expr) ((void)0)
#endif

#endif // #ifndef _ASSERT

#ifdef QT_DEBUG
#define DBGASSERT(cond)\
    do {\
        if (!(cond)) {\
            LOG_INFO("DBGASSERT:");\
            Q_ASSERT(false);\
        }\
    } while(0)

#else
#define DBGASSERT(cond) do { (void)sizeof(cond); } while(0)
#endif

// ============ END _ASSERT SECTION





#if !defined(GUID_DEFINED)
#define GUID_DEFINED
        typedef struct _GUID {
            unsigned long  Data1;
            unsigned short Data2;
            unsigned short Data3;
            unsigned char  Data4[8];
        } GUID;
#endif

// ============ START namespace helpers
namespace helpers
{
class CDummyXFile
{
public:
    CDummyXFile() {
#if defined(WINDOWS_PLATFORM)
        fopen_s(&m_dummyFile, "NUL", "wb");
#else
        m_dummyFile = fopen("/dev/null", "wb");
#endif
    }
    ~CDummyXFile() {
        if (m_dummyFile != nullptr)
            fclose(m_dummyFile);
    }


    FILE* GetFilePtr() {
        return m_dummyFile;
    }
private:
    FILE* m_dummyFile = nullptr;
    //void* operator new (size_t);

    // Copy constructor
    CDummyXFile(const CDummyXFile& t) = delete;
    // Copy assignment operator
    CDummyXFile & operator = (const CDummyXFile& t) = delete;
};
} // namespace helpers
// ============ END namespace helpers


// ============ START namespace stringutils
namespace stringutils
{
    // trim right
    // stringutils::rtrim(stringToReplace, "\\/;.:");
    template <typename T, typename X>
    X& rtrim(X& sValue, const T* trimCharArray) {
        sValue.erase(sValue.find_last_not_of(trimCharArray) + 1);
        return sValue;
    }

    // trim left
    // stringutils::ltrim(stringToReplace, "\\/;.:");
    template <typename T, typename X>
    X& ltrim(X& sValue, const T* trimCharArray) {
        sValue.erase(0, sValue.find_first_not_of(trimCharArray));
        return sValue;
    }

    // trim right and left
    // stringutils::trim(stringToReplace, "\\/;.:");
    template <typename T, typename X>
    X& trim(X& sValue, const T* trimCharArray) {
        return ltrim(rtrim(sValue, trimCharArray), trimCharArray);
    }

    // true if string end with XXX
    // stringutils::endsWith(stringToCheck, "some string at the end");
    template <typename T, typename X>
    bool endsWith(const T& value, const X& endString) {
        T v1 = endString;
        return value.size() >= v1.size() && 0 == value.compare(value.size() - v1.size(), v1.size(), v1);
    }

    // true if string start with XXX
    // stringutils::startsWith(stringToCheck, "some string at the begin");
    template <typename T, typename X>
    bool startsWith(const T& value, const X& startString) {
        T v1 = startString;
        return value.size() >= v1.size() && 0 == value.compare(0, v1.size(), v1);
    }

    // Replace substring with another substring
    // stringutils::replaceSubstringWithString(stringToReplace, "old substring", "new substring")
    template <typename T, typename X, typename Y>
    void replaceSubstringWithString(T& val, const X oldSymbol, const Y newSymbol) {
               
        auto lenRep = T(oldSymbol).length();
        if (lenRep == 0)
            return;

        decltype(lenRep) pos = 0;

        while (true)
        {
            auto res = val.find(oldSymbol, pos);
            if (res == T::npos)
                return;

            val.replace(res, lenRep, newSymbol);
            pos = res + (T(newSymbol).length());
        }
    }

    // convert buffer to HEX string 
    // stringutils::byteBufferToByteHexString(sourceBuffer, sizeof(sourceBuffer), ",", "0x")
    inline std::string byteBufferToByteHexString(const uint8_t* ptr, uint64_t length, const std::string& separator, const std::string& ptefix) {
        if (length < 1)
            return "";

        std::stringstream ss;
        for (decltype(length) i = 0; i < length; ++i) {
            ss << ptefix << std::hex << std::setfill('0') << std::setw(2) << static_cast<uint32_t>(ptr[i]) << std::dec;
            if (i + 1 < length)
                ss << separator;
        }
        return ss.str();
    }

    template <typename T>
    auto toHexString(const int64_t value, const char* fmt = "0x%08X"){
        int sz = std::snprintf(nullptr, 0, fmt, value);
        std::vector<T> buf(sz + 1, 0);
        std::snprintf(buf.data(), buf.size(), fmt, value);
        return buf.data();
    }
    template <typename T>
    auto toHexString(const int64_t value, const wchar_t* fmt = L"0x%08X"){
        int sz = std::swprintf(nullptr, 0, fmt, value);
        std::vector<wchar_t> buf(sz + 1, 0);
        std::swprintf(buf.data(), buf.size(), fmt, value);
        return buf.data();
    }

    /// <summary>
    /// convert guid to string
    /// </summary>
    /// <param name="guid">some guid as GUID</param>
    /// <returns>string representation of the guid</returns>
    inline std::string guidToString(const GUID* guid) {
#if 0
        std::ostringstream stream;

        stream << std::uppercase;
        stream << std::setfill('0');
        stream.width(8);
        stream << std::hex << guid->Data1 << '-';

        stream.width(4);
        stream << std::hex << guid->Data2 << '-';

        stream.width(4);
        stream << std::hex << guid->Data3 << '-';

        stream.width(2);
        stream << std::hex << static_cast<short>(guid->Data4[0]);
        stream.width(2);
        stream << std::hex << static_cast<short>(guid->Data4[1]);
        stream << '-';
        stream.width(2);
        stream << std::hex << static_cast<short>(guid->Data4[2]);
        stream.width(2);
        stream << std::hex << static_cast<short>(guid->Data4[3]);
        stream.width(2);
        stream << std::hex << static_cast<short>(guid->Data4[4]);
        stream.width(2);
        stream << std::hex << static_cast<short>(guid->Data4[5]);
        stream.width(2);
        stream << std::hex << static_cast<short>(guid->Data4[6]);
        stream.width(2);
        stream << std::hex << static_cast<short>(guid->Data4[7]);

        return stream.str();

#else
        std::vector<char> buff(40, 0);
        std::snprintf(
            buff.data(), buff.size(),
            "%08lX-%04hX-%04hX-%02hhX%02hhX-%02hhX%02hhX%02hhX%02hhX%02hhX%02hhX",
            guid->Data1, guid->Data2, guid->Data3, guid->Data4[0], guid->Data4[1],
            guid->Data4[2], guid->Data4[3], guid->Data4[4], guid->Data4[5],
            guid->Data4[6], guid->Data4[7]);
        return buff.data();
#endif
    }

    /// <summary>
    // auto res = stringutils::splitString(std::string("aa,bb,cc"), ',');
    // auto wres = stringutils::splitString(std::wstring(L"aa,bb,cc"), L',');
    /// </summary>
    /// <typeparam name="T">std::string or std::wstring</typeparam>
    /// <typeparam name="X">char or wchar_t</typeparam>
    /// <param name="source">std::string("aa,BB,cc") or wstring(L"aa,bb,cc")</param>
    /// <param name="delimiter">','</param>
    /// <returns>vector with string or wstring</returns>
    template <typename T, typename X>
    std::vector<T> splitString(const T& source, const X delimiter) {
        std::vector<T> array;
        if (source.length() > 0) {
            decltype(source.length()) startSearch = 0;
            while (true) {
                auto delimiterPos = source.find_first_of(delimiter, startSearch);
                if (delimiterPos == T::npos) {
                    const auto& len = source.length() - startSearch;
                    if (len > 0)
                        array.push_back(source.substr(startSearch));
                    return array;
                }
                const auto & len = delimiterPos - startSearch;
                if (len > 0)
                    array.push_back(source.substr(startSearch, len));
                startSearch = ++delimiterPos;
            }
        }
        return array;
    }

    template<class Facet>
    struct deletable_facet : Facet
    {
        template<class... Args>
        deletable_facet(Args&&... args) :
            Facet(std::forward<Args>(args)...) 
        {
        }
        ~deletable_facet() {}
    };

    /// convert std::wstring to std::string
    /// windows: uses the current locale for any locale-dependent behavior
    /// Linux: use utf8 to 
    /// std::wstring = stringutils::ConvertA2W(std::string)
    inline std::wstring ConvertA2W(const std::string& val, const bool encodeUTF8) {
        if (val.empty())
            return std::wstring();

        try {
#if defined(QT_VERSION) && !defined(WINDOWS_PLATFORM)
            //fromUtf8
            //Returns a QString initialized with the first size
            // bytes of the UTF-8 string .

            //If size is -1 (default), it is taken to be strlen(str).
            // UTF-8 is a Unicode codec and can represent all characters
            // in a Unicode string like QString. However, invalid sequences are possible with UTF-8 and,
            // if any such are found, they will be replaced with one or more "replacement characters",
            // or suppressed. These include non-Unicode sequences, non-characters, overlong sequences or
            // surrogate codepoints encoded into UTF-8.

            //This function can be used to process incoming data incrementally as long as all
            // UTF-8 characters are terminated within the incoming data.
            // Any unterminated characters at the end of the string will be replaced or suppressed.
            // In order to do stateful decoding, please use QTextDecoder.

            //toStdWString
            //Returns a std::wstring object with the data contained
            //in this QString. The std::wstring is encoded in utf16
            // on platforms where wchar_t is 2 bytes wide (e.g. windows)
            //and in ucs4 on platforms where wchar_t is 4 bytes wide
            //(most Unix systems).
            UNREFERENCED_PARAMETER_LOG(encodeUTF8);
            return QString::fromUtf8(val.c_str()).toStdWString();
#elif defined(WINDOWS_PLATFORM)
            auto len = MultiByteToWideChar(static_cast<UINT>(encodeUTF8 ? CP_UTF8 : CP_ACP),
                                           0, val.c_str(), -1, NULL, 0);
            if (len < 1)
                return L"";
            std::vector<wchar_t> buf(1ULL + len, 0);
            if (MultiByteToWideChar(static_cast<UINT>(encodeUTF8 ? CP_UTF8 : CP_ACP),
                                    0, val.c_str(), -1, buf.data(), static_cast<int>(buf.size())) < 1)
                return L"";
            return buf.data();
#elif defined(STDCCODECVTPRESENT)
            std::wstring_convert<std::codecvt_utf8<wchar_t>, wchar_t> convert;
            return convert.from_bytes(val); 
#elif defined(_MSC_VER) && (_MSC_VER >= 1400)
            auto len = val.size() + 1;
            size_t size = 0;
            auto err = mbstowcs_s(&size, nullptr, 0, val.c_str(), len);
            if (err != 0)
                return std::wstring();

            std::wstring result(size, ' ');
            err = mbstowcs_s(&size, &result[0], size, val.c_str(), len);
            if (err != 0)
                return std::wstring();

            if (!result.empty() && result[size - 1] == '\0')
                result.erase(size - 1);
            return result;
#else
#error
#endif
        }
        catch (const std::exception& ex) {
            std::cerr << "Failed ConvertA2W " << ex.what() << std::endl;
        }
        return std::wstring();
    }

    /// convert std::string to std::wstring
    /// windows: uses the current locale for any locale-dependent behavior
    /// Linux: convert to utf8
    inline std::string ConvertW2A(const std::wstring& val, const bool encodeUTF8) {

        if (val.empty())
            return std::string();

        try {

#if defined(QT_VERSION) && !defined(WINDOWS_PLATFORM)
            //fromStdWString
            //Returns a copy of the string.
            //The given string is assumed to be encoded in utf16 if
            //the size of wchar_t is 2 bytes (e.g. on windows) and ucs4
            //if the size of wchar_t is 4 bytes (most Unix systems).

            //toStdString
            //Returns a std::string object with the data contained in this QString.
            //The Unicode data is converted into 8-bit characters using the
            //toUtf8() function
            UNREFERENCED_PARAMETER_LOG(encodeUTF8);
            return QString::fromStdWString(val).toStdString();
#elif defined(WINDOWS_PLATFORM)
            static_assert(sizeof(val[0]) == 2, "");
            auto len = WideCharToMultiByte(static_cast<UINT>(encodeUTF8 ? CP_UTF8 : CP_ACP),
                                           0, val.c_str(), -1, NULL, 0, NULL, NULL);
            if (len < 1)
                return "";
            std::vector<char> buf(1ULL + len, 0);
            if (WideCharToMultiByte(static_cast<UINT>(encodeUTF8 ? CP_UTF8 : CP_ACP),
                                    0, val.c_str(), -1, buf.data(), static_cast<int>(buf.size()), NULL, NULL) < 1)
                return "";
            return buf.data();
#elif defined(STDCCODECVTPRESENT)
            static std::wstring_convert<std::codecvt_utf8<wchar_t>, wchar_t> convert;
            return convert.to_bytes(val);
#elif defined(_MSC_VER) && (_MSC_VER >= 1400)
            // range 0-255
            static_assert(sizeof(val[0]) == 2, "");
            const auto len = val.size() + 1;
            size_t size = 0;
            auto err = wcstombs_s(&size, nullptr, 0, val.c_str(), len * sizeof(wchar_t));
            if (err != 0)
                return std::string();
            std::string result(size, ' ');
            err = wcstombs_s(&size, &result[0], size, val.c_str(), len * sizeof(wchar_t));
            if (err != 0)
                return std::string();

            if (!result.empty() && result[size - 1] == '\0')
                result.erase(size - 1);
            return result;
#else
#error
#endif
        }
        catch (const std::exception& ex) {
            std::cerr << "Failed ConvertW2A " << ex.what() << std::endl;
        }
        return std::string();
    }
  

    template<typename... TArg>
    inline int dummyPrintX(FILE* const _Stream,  _Printf_format_string_  const char* const _Format, TArg...args) {
        return std::vfprintf(_Stream, _Format, args...);
    }

    template<typename... TArg>
    inline int dummyPrintX(FILE* const _Stream, _Printf_format_string_ const wchar_t* const _Format, TArg...args) {
        return std::vfwprintf(_Stream, _Format, args...);
    }

    template<typename... TArg>
    inline int printX(std::vector<char>& buffer, _Printf_format_string_ const char* const _Format, TArg...args) {
        return std::vsnprintf(buffer.data(), buffer.size() - 1, _Format, args...);
    }

    template<typename... TArg>
    inline int printX(std::vector<wchar_t>& buffer, _Printf_format_string_ const wchar_t* const _Format, TArg...args) {
        return std::vswprintf(buffer.data(), buffer.size() - 1, _Format, args...);
    }

    inline const std::string retType(const std::string& val) { return val; };
    inline const std::wstring retType(const std::wstring& val) { return val; };

    template<typename T, typename...>
    auto FormatStringF(FILE* const stream, _Printf_format_string_ T const* const _Format, ...)
    {
        std::vector<typename std::remove_const<typename std::remove_pointer<decltype(_Format)>::type>::type> buffer;
        {
            va_list argsx;
            va_start(argsx, _Format);
            auto size = dummyPrintX(stream, _Format, argsx);//args...
            va_end(argsx);
            if (size < 1) {
                buffer.resize(1ULL, 0);
                return retType(buffer.data());
            }
            buffer.resize(2ULL + size, 0);
        }
        if (buffer.size() > 1)
        {
            va_list argsx;
            va_start(argsx, _Format);
            auto size = printX(buffer, _Format, argsx);
            va_end(argsx);
            if (size < 1)
                buffer[0] = 0;
        }
        return retType(buffer.data());
    };

    template<typename...Targ>
    inline std::string FormatString(FILE* const stream, _Printf_format_string_ const char* const _Format, Targ...arg) {
        return FormatStringF(stream, _Format, arg...);
    }

    template<typename...Targ>
    inline std::wstring FormatString(FILE* const stream, _Printf_format_string_ wchar_t const* const _Format, Targ...arg) {
        return FormatStringF(stream, _Format, arg...);
    }

    template<typename...Targ>
    inline std::string FormatString(_Printf_format_string_ const char* const _Format, Targ...arg) {
        helpers::CDummyXFile xf;
        return FormatStringF(xf.GetFilePtr(), _Format, arg...);
    };

    template<typename...Targ>
    inline std::wstring FormatString(_Printf_format_string_ wchar_t const* const _Format, Targ...arg) {
        helpers::CDummyXFile xf;
        return FormatStringF(xf.GetFilePtr(), _Format, arg...);
    };
 
    /// <summary>
    /// std::wstring = stringutils::Latin1ToStdWString("")
    /// </summary>
    /// <param name="source">std::string with Latin1 charset</param>
    /// <returns>std::wstring as multi-byte</returns>
    inline std::wstring Latin1ToStdWString(const std::string &source) {
        return std::wstring(source.begin(), source.end());
    }

#if defined(__cplusplus) && (__cplusplus >= 201703L)

    template<typename T, typename X>
    constexpr void strAppendX(T& firstVal, const X& secondVal) {

        constexpr auto firstIsChar = (std::is_same<T, std::string>::value) || std::is_convertible_v<T, char const*>;
        constexpr auto firstIsWChar = (std::is_same<T, std::wstring>::value) || std::is_convertible_v<T, wchar_t const*>;
        static_assert(firstIsChar || firstIsWChar, "");

        constexpr auto secondIsChar = (std::is_same<X, std::string>::value) || std::is_convertible_v<X, char const*>;
        constexpr auto secondIsWChar = (std::is_same<X, std::wstring>::value) || std::is_convertible_v<X, wchar_t const*>;
        static_assert(secondIsChar || secondIsWChar, "");

        //char += char
        //wchar_t += wchar_t 
        //std::string += std::string 
        //std::wstring += std::wstring
        if constexpr (firstIsChar == secondIsChar) firstVal += secondVal;

        //char += wchar_t
        //std::string += std::string 
        if constexpr (firstIsChar && !secondIsChar) firstVal += ConvertW2A(secondVal, true);

        //wchar_t += char
        //std::wstring += std::string
        if constexpr (!firstIsChar && secondIsChar) firstVal += ConvertA2W(secondVal, true);
     }

#else 

    inline void strAppend(std::string& val, const char* c, const wchar_t*) {
        val += c;
    }
    inline void strAppend(std::wstring& val, const char*, const wchar_t* w) {
        val += w;
    }
    inline void strAppend(std::string& val, const std::string& c) {
        val += c;
    }
    inline void strAppend(std::wstring& val, const std::wstring& w) {
        val += w;
    }
    inline void strAppend(std::wstring& val, const char* c) {
        val += ConvertA2W(c, true);
    }
    inline void strAppend(std::string& val, const wchar_t* c) {
        val += ConvertW2A(c, true);
    }
    inline void strAppend(std::wstring& val, const std::string &c) {
        val += ConvertA2W(c, true);
    }
    inline void strAppend(std::string& val, const std::wstring& c) {
        val += ConvertW2A(c, true);
    }

#endif

} // namespace stringutils
// ============ END namespace stringutils




// ============ START namespace fsutils
namespace fsutils {
    template<typename T>
    inline T getNameFromPath(T const & path)
    {
    #ifdef USESTDFILESYSTEM
            return std::filesystem::path(path).filename();
    #else
        return path.substr(path.find_last_of(ST("/\\")) + 1);
    #endif
    }
} // namespace fsutils
// ============ END namespace fsutils






// ============ START namespace info
namespace info {
    inline auto executable_PathAndName()
    {
#if defined(WINDOWS_PLATFORM)
        wchar_t buf[MAX_PATH];
        GetModuleFileNameW(nullptr, buf, MAX_PATH);
        return std::wstring(buf);
#elif defined(PLATFORM_POSIX) || defined(__linux__)
        std::string sp;
        std::ifstream("/proc/self/comm") >> sp;
        return sp;
#else
        static_assert(false, "unrecognized platform");
#endif
    }

    template <typename T>
    inline auto GetVersionString(T appname)
    {
        std::basic_string<typename std::conditional<(((std::is_same<T, std::string>::value) || std::is_convertible<T, char const*>::value)), char, wchar_t>::type> appv;

        STRAPPEND(appv, "App [");
        STRAPPEND2(appv, appname);
        STRAPPEND(appv, "] ");

#if defined(__ANDROID__) || defined(Q_OS_ANDROID)
        STRAPPEND(appv, "Android ");
#endif

#if defined(_M_X64) ||\
    defined(_M_AMD64) ||\
    defined(_WIN64) ||\
    defined(WIN64) ||\
    defined(_M_ARM64) ||\
    defined(__MINGW64__) ||\
    defined(LP64) ||\
    defined(AMD64) ||\
    defined(X64) ||\
    defined(__ppc64__) ||\
    defined(__x86_64__)||\
    defined(__aarch64__)

        STRAPPEND(appv, "64-bit ");
        static_assert(sizeof(nullptr) == 8, "");
#else
        //defined(_WIN32) || defined (_M_ARM)
        static_assert(sizeof(nullptr) == 4, "");
        STRAPPEND(appv, "32-bit ");
#endif

#if  defined(__CYGWIN__)
        STRAPPEND(appv, "CYGWIN ");
#endif

#if  defined(__unix) || defined(__unix__)//Unix (Linux, *BSD, but not Mac OS X)
        STRAPPEND(appv, "Unix ");
#endif

#if  defined(__APPLE__) //Mac OS X Also used for classic
        STRAPPEND(appv, "Apple ");
#endif

#if defined(__MACH__)
        STRAPPEND(appv, "MACH ");
#endif

#if defined(__aarch64__)
        STRAPPEND(appv, "aarch64 ");
#endif

#if  defined(__linux__) || defined(__linux)//Linux; __linux - Linux Obsolete (not POSIX compliant)
        STRAPPEND(appv, "Linux ");
#endif

#if  defined(__FreeBSD__)//FreeBSD
        STRAPPEND(appv, "FreeBSD ");
#endif

#if defined (_M_ARM)
    #include <armintr.h>
    #include <arm_neon.h>
#endif

#if defined (_M_ARM64)
    #include <arm64intr.h>
    #include <arm64_neon.h>
#endif // _M_ARM64


#ifdef QT_VERSION
        STRAPPEND(appv, "Qt[" QT_VERSION_STR " runtime(");
        STRAPPEND2(appv, qVersion());
        STRAPPEND(appv, ")] ");
#endif // QT_VERSION

#if defined(_MSVC_LANG)
#   if   (_MSVC_LANG == 199711L)
        STRAPPEND(appv, "std:C++98 ");
#   elif   (_MSVC_LANG == 201402L)
        STRAPPEND(appv, "std:C++14 ");
#   elif (_MSVC_LANG == 201703L)
        STRAPPEND(appv, "std:C++17 ");
#   elif (_MSVC_LANG == 202002L)
        STRAPPEND(appv, "std:C++20 ");
#   else
#   error  std:c++??
#   endif
// ~_MSVC_LANG
#elif defined(__cplusplus)
#   if   (__cplusplus == 199711L)
        STRAPPEND(appv, "std:C++98 ");
#   elif (__cplusplus == 201103L)
        STRAPPEND(appv, "std:C++11 ");
#   elif (__cplusplus == 201402L)
        STRAPPEND(appv, "std:C++14 ");
#   elif   (__cplusplus == 201703L)
        STRAPPEND(appv, "std:C++17 ");
#   elif (_MSVC_LANG == 202002L)
        STRAPPEND(appv, "std:C++20 ");
#else
     #error  std:c++??
#endif
#endif // defined(__cplusplus)

#ifdef __GLIBC__
  STRAPPEND(appv, "GNU libc [");
  STRAPPEND(appv, quoteStr(__GLIBC__));
  STRAPPEND(appv, ".");
  STRAPPEND(appv, quoteStr(__GLIBC_MINOR__));
  STRAPPEND(appv, " runtime(");
  STRAPPEND2(appv, gnu_get_libc_version());
  STRAPPEND(appv, ")] ");
#endif // __GLIBC__

// CLANG
#if defined(__clang__)
        STRAPPEND(appv, "clang++[");
        STRAPPEND(appv, quoteStr(__clang_major__));
        STRAPPEND(appv, ".");
        STRAPPEND(appv, quoteStr(__clang_minor__));
        STRAPPEND(appv, ".");
        STRAPPEND(appv, quoteStr(__clang_patchlevel__));
        STRAPPEND(appv, "] ");
#elif defined(__MINGW32__) && !defined(__MINGW64__)
        STRAPPEND(appv, "MINGW32[");
        STRAPPEND(appv, quoteStr(__MINGW32_MAJOR_VERSION));
        STRAPPEND(appv, ".");
        STRAPPEND(appv, quoteStr(__MINGW32_MINOR_VERSION));
        STRAPPEND(appv, "] ");
#elif defined(__MINGW64__)
        STRAPPEND(appv, "MINGW64[");
        STRAPPEND(appv, quoteStr(__MINGW64_VERSION_MAJOR));
        STRAPPEND(appv, ".");
        STRAPPEND(appv, quoteStr(__MINGW64_VERSION_MINOR));
        STRAPPEND(appv, "] ");
#elif defined(__GNUC__) || defined(__GNUG__)
#   ifdef __VERSION__
        STRAPPEND(appv, "g++[");
        STRAPPEND(appv, __VERSION__);
        STRAPPEND(appv, "] ");
#   else
#       ifndef __GNUC_MINOR__
#           error GNUC_MINOR
#       endif // __GNUC_MINOR__
#       ifndef __GNUC_PATCHLEVEL__
#           error GNUC_PATCHLEVEL
#       endif // __GNUC_PATCHLEVEL__
        STRAPPEND(appv, "g++[");
        STRAPPEND(appv, quoteStr(__GNUC__));
        STRAPPEND(appv, ".");
        STRAPPEND(appv, quoteStr(__GNUC_MINOR__));
        STRAPPEND(appv, ".");
        STRAPPEND(appv, quoteStr(__GNUC_PATCHLEVEL__));
        STRAPPEND(appv, "] ");
#   endif // __VERSION__

        // MSVC
#elif defined(_MSC_VER)
        STRAPPEND(appv, "MSVC[");
        STRAPPEND(appv, quoteStr(_MSC_VER));
        STRAPPEND(appv, ".");
        STRAPPEND(appv, quoteStr(_MSC_BUILD));
        STRAPPEND(appv, " (");
        STRAPPEND(appv, quoteStr(_MSC_FULL_VER));
        STRAPPEND(appv, ") ");

#if (_MSC_VER >= 1935)
        STRAPPEND(appv, " VS??");
#error undefined
#elif (_MSC_VER >= 1930)
        STRAPPEND(appv, "VS2022");
#elif(_MSC_VER >= 1920)
        STRAPPEND(appv, "VS2019");
#elif(_MSC_VER >= 1910)
        STRAPPEND(appv, "VS2017");
#elif(_MSC_VER >= 1900)
        STRAPPEND(appv, "VS2015");
#elif(_MSC_VER >= 1800)
        STRAPPEND(appv, "VS2013");
#elif(_MSC_VER >= 1700)
        STRAPPEND(appv, "VS2012");
#elif(_MSC_VER >= 1600)
        STRAPPEND(appv, "VS2010");
#elif(_MSC_VER >= 1500)
        STRAPPEND(appv, "VS2008");
#elif(_MSC_VER >= 1400)
        STRAPPEND(appv, "VS2005");
#elif(_MSC_VER >= 1310)
        STRAPPEND(appv, "VS2003");
#elif(_MSC_VER >= 1300)
        STRAPPEND(appv, "VS2002");
#elif(_MSC_VER >= 1200)
        STRAPPEND(appv, "VS6.0");
#elif(_MSC_VER >= 1100)
        STRAPPEND(appv, "VS5.0");
#elif(_MSC_VER >= 1020)
        STRAPPEND(appv, "VS4.2");
#elif(_MSC_VER >= 1010)
        STRAPPEND(appv, "VS4.1");
#elif(_MSC_VER >= 1000)
        STRAPPEND(appv, "VS4.0");
#elif(_MSC_VER >= 900)
        STRAPPEND(appv, "VS2.0");
#elif(_MSC_VER >= 800)
        STRAPPEND(appv, "VS1.0");
#endif
        STRAPPEND(appv, "] ");
#else
#error unsupported compiler
#endif

        return appv;
    }

} // ~namespace info
// ============ END namespace info






//**************************************
// +CLogger
//**************************************
class CLogger
{
public:
    typedef enum {
        eLogLevel_error = 0,
        eLogLevel_info = 1,
        eLogLevel_trace = 2
    }eLogLevel;

public:
    static CLogger& Instance();
    CLogger(const CLogger&) = delete;
    CLogger(const CLogger&&) = delete;
    CLogger& operator=(const CLogger&) = delete;
    CLogger& operator=(const CLogger&&) = delete;

private:
    explicit CLogger();
    ~CLogger();

public:

    void SetDisplayExtInfo(bool val);

    /// return string describing error number
    static std::string GetErrorStringA(const int32_t errorCode);

    /// return string describing error number
    static std::wstring GetErrorStringW(const int32_t errorCode);

    template<typename T, typename...Targs>
#if defined(MSVC_COMPILER)
    void LogMess(eLogLevel lvl, const char* szFile, const char* szFunc, const int iLine, _Printf_format_string_ const T szFmt, Targs...args)
#else
    void LogMess(eLogLevel lvl, const char* szFile, const char* szFunc, const int iLine, const T szFmt, Targs...args) //__attribute__((format(printf, 5, 6)))
#endif
    {

        if (m_bExit || !(m_logLevel >= lvl))
            return;

        auto logstr = GetTimestamp(szFmt);

        const auto baseFmt = std::basic_string<typename decltype(logstr)::value_type>(szFmt);

        logstr.append(GetErrorLevelStr(lvl, baseFmt));

        auto xres = stringutils::FormatString(m_dummyFile, baseFmt.c_str(), args...);
        logstr.append(xres);

        if (m_displayExtInfo)
            PrintExtInfo(logstr, szFile, szFunc, iLine);

        std::lock_guard<std::mutex> mlock(m_mutexLog);
        BufferOut(logstr, lvl == eLogLevel::eLogLevel_error);

    }

private:

    static const wchar_t* GetErrorLevelStr(const CLogger::eLogLevel lvl, const std::wstring&);
    static const char* GetErrorLevelStr(const CLogger::eLogLevel lvl, const std::string&);

    static std::string GetTimestamp(const std::string&);
    static std::wstring GetTimestamp(const std::wstring&);

    static void PrintExtInfo(std::string& val, const char* szFile, const char* szFunc, const int iLine);
    static void PrintExtInfo(std::wstring& val, const char* szFile, const char* szFunc, const int iLine);

    static void BufferOut(const std::string& val, bool isError);
    static void BufferOut(const std::wstring& val, bool isError);

private:
    FILE* m_dummyFile = nullptr;
    std::mutex  m_mutexLog;
    eLogLevel   m_logLevel = eLogLevel::eLogLevel_trace;
    //const int32_t m_logFileCount = 3 + 2;
    bool m_displayExtInfo = false;
    bool m_bExit = false;
    uint8_t dummy[2]{};

public: 

    void LogMessTest()
    {
        LogMess(eLogLevel::eLogLevel_trace, "szFile", "szFunc", 0, "szFmt %s", "args...");
        LogMess(eLogLevel::eLogLevel_trace, "szFile", "szFunc", 0, std::string("szFmt %s"), "args...");

        LogMess(eLogLevel::eLogLevel_trace, "szFile", "szFunc", 0, L"szFmt %ls", L"args...");
        LogMess(eLogLevel::eLogLevel_trace, "szFile", "szFunc", 0, std::wstring(L"szFmt %ls"), L"args...");

        char arr1[] = "hello %s";
        LogMess(eLogLevel::eLogLevel_trace, "szFile", "szFunc", 0, arr1, "args...");
        wchar_t arr2[] = L"hello %s";
        LogMess(eLogLevel::eLogLevel_trace, "szFile", "szFunc", 0, arr2, L"args...");

        const std::string cp1("szFmt %s");
        LogMess(eLogLevel::eLogLevel_trace, "szFile", "szFunc", 0, cp1, "args...");
        const std::wstring cp2(L"szFmt %ls");
        LogMess(eLogLevel::eLogLevel_trace, "szFile", "szFunc", 0, cp2, L"args...");
    }
};

#define LOG_TRACE(messfmt, ...) { CLogger::Instance().LogMess(CLogger::eLogLevel_trace, __FILE__, __FUNCTION__, __LINE__, messfmt, ##__VA_ARGS__); };
#define LOG_INFO(messfmt, ...) { CLogger::Instance().LogMess(CLogger::eLogLevel_info,  __FILE__, __FUNCTION__, __LINE__, messfmt, ##__VA_ARGS__); };
#define LOG_ERROR(messfmt, ...) { CLogger::Instance().LogMess(CLogger::eLogLevel_error, __FILE__, __FUNCTION__, __LINE__, messfmt, ##__VA_ARGS__); };

//**************************************
//~ CLogger
//**************************************
 
//**************************************
//+ Stream log
//**************************************
#define LOGSTREAMA(level) LogT<std::ostringstream>().Get(level, __FILE__, __FUNCTION__, __LINE__)
#define LOGSTREAMW(level) LogT<std::wstringstream>().Get(level, __FILE__, __FUNCTION__, __LINE__)


/// <summary>
/// LogT<std::ostringstream>().Get(level, __FILE__, __FUNCTION__, __LINE__) << "some char";
/// LogT<std::wstringstream>().Get(level, __FILE__, __FUNCTION__, __LINE__) << L"some wchar_t";
/// </summary>
/// <typeparam name="T"></typeparam>
template<class T>
class LogT
{
public:
    LogT() {
    };

    LogT(const LogT&) = delete;
    LogT(const LogT&&) = delete;
    LogT& operator=(const LogT&) = delete;
    LogT& operator=(const LogT&&) = delete;

    T& Get(CLogger::eLogLevel lvl, const char* szFile, const char* szFunc, const int iLine) {
        m_Level = lvl;
        m_file = szFile;
        m_function = szFunc;
        m_line = iLine;
        return m_os;
    };
    ~LogT() {
        CLogger::Instance().LogMess(m_Level, m_file.c_str(), m_function.c_str(), m_line, m_os.str().c_str(), nullptr);
    };
private:
    T m_os;
    std::string m_file;
    std::string m_function;
    CLogger::eLogLevel m_Level = CLogger::eLogLevel::eLogLevel_error;
    int m_line = 0;
};

//**************************************
//~ Stream log
//**************************************

/*
Polymorphic class app_error is copyable - Potential slicing.
Use brain or do not use class app_error
 */
class app_error : public std::exception
{
public:
    app_error(const app_error& other) noexcept{
       m_msgA = other.m_msgA;
       m_msgW = other.m_msgW;
    }
    app_error& operator=(const app_error& other) noexcept{
        if (this == &other)
            return *this;
        m_msgA = other.m_msgA;
        m_msgW = other.m_msgW;
        return *this;
    }
    explicit app_error(const char* message)
        : m_msgW(stringutils::ConvertA2W(message, true))
        , m_msgA(message)
    {
    }
    explicit app_error(const wchar_t* message)
        : m_msgW(message)
        , m_msgA(stringutils::ConvertW2A(message, true))
    {
    }
    virtual const char* what() const noexcept override{
        return m_msgA.c_str();
    };
    void getErrorMessage(std::string &ret) const noexcept {
        ret = m_msgA;
    }
    void getErrorMessage(std::wstring &ret) const noexcept {
        ret = m_msgW;
    }
#if defined(WINDOWS_PLATFORM)
    const wchar_t* Error() const noexcept {
        return m_msgW.c_str();
    }
#else
    const char* Error() const noexcept {
        return m_msgA.c_str();
    }
#endif
protected:
    std::wstring m_msgW;
    std::string m_msgA;
};

#endif // LOGGER_H

