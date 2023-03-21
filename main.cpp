#include "logger.h"


#if defined(MSVC_COMPILER)
#pragma warning(push)
#pragma warning( disable : 4365) // conversion from '' to ''
#pragma warning( disable : 4668) // is not defined as a preprocessor macro
#pragma warning( disable : 4710) // function not inlined
#pragma warning( disable : 4711) // selected for automatic inline expansion
#pragma warning( disable : 4820) // bytes padding added after data member
#pragma warning( disable : 5039) // pointer or reference to potentially throwing
#pragma warning( disable : 4625) // copy constructor was implicitly defined as deleted
#pragma warning( disable : 5026) // move constructor was implicitly defined as deleted
#pragma warning( disable : 4626) // assignment operator was implicitly defined as
#pragma warning( disable : 5027) // move assignment operator was implicitly defined as
#pragma warning( disable : 4514) // unreferenced inline function has been removed
#endif

// #include <QCoreApplication>
// #include <QMessageBox>

#if defined(MSVC_COMPILER)
#pragma warning(pop)
#endif

#ifndef ERROR_SUCCESS
#define ERROR_SUCCESS 0x0L
#endif

static bool test_replaceSubstr() {
    auto ret = true;
    {
        std::string tst("12345%%6");
        stringutils::replaceSubstringWithString(tst, "", "");
        _ASSERT(tst == "12345%%6");
        if (tst != "12345%%6")
            ret = false;
    }
    {
        std::string tst("12345%%6");
        stringutils::replaceSubstringWithString(tst, "", "66667777");
        _ASSERT(tst == "12345%%6");
        if (tst != "12345%%6")
            ret = false;
    }
    {
        std::string tst("12345%%6");
        stringutils::replaceSubstringWithString(tst, "%", "%%");
        _ASSERT(tst == "12345%%%%6");
        if (tst != "12345%%%%6")
            ret = false;
    }
    {
        std::string tst("12345%%%%6");
        stringutils::replaceSubstringWithString(tst, "%%", "%");
        _ASSERT(tst == "12345%%6");
        if (tst != "12345%%6")
            ret = false;
    }
    {
        std::string tst("123456");
        stringutils::replaceSubstringWithString(tst, "%%", "%%");
        _ASSERT(tst == "123456");
        if (tst != "123456")
            ret = false;
    }
    {
        std::string tst(",,,%\ncce\nghh%");
        stringutils::replaceSubstringWithString(tst, "%\n", "");
        _ASSERT(tst == ",,,cce\nghh%");
        if (tst != ",,,cce\nghh%")
            ret = false;
    }
    {
        std::string tst("");
        stringutils::replaceSubstringWithString(tst, "%\n", "");
        _ASSERT(tst == "");
        if (tst != "")
            ret = false;
    }
    {
        std::string tst("123%\n\r45");
        stringutils::replaceSubstringWithString(tst, "%\n\r", "");
        _ASSERT(tst == "12345");
        if (tst != "12345")
            ret = false;
    }
    {
        std::string tst("12345%\n\r");
        stringutils::replaceSubstringWithString(tst, "%\n\r", "");
        _ASSERT(tst == "12345");
        if (tst != "12345")
            ret = false;
    }
    {
        std::string tst("12345%\n\r");
        stringutils::replaceSubstringWithString(tst, "%\n\r", "87654321");
        _ASSERT(tst == "1234587654321");
        if (tst != "1234587654321")
            ret = false;
    }
    {
        std::string tst("%\n\r12345");
        stringutils::replaceSubstringWithString(tst, "%\n\r", "");
        _ASSERT(tst == "12345");
        if (tst != "12345")
            ret = false;
    }
    {
        std::string tst("123%sh\n\r45");
        stringutils::replaceSubstringWithString(tst, "%sh", "");
        _ASSERT(tst == "123\n\r45");
        if (tst != "123\n\r45")
            ret = false;
    }
    {
        std::wstring tst(L"123%sh\n\r45");
        stringutils::replaceSubstringWithString(tst, L"%sh", L"");
        _ASSERT(tst == L"123\n\r45");
        if (tst != L"123\n\r45")
            ret = false;
    }
    {
        std::wstring tst(L"123%sh\n\r45");
        stringutils::replaceSubstringWithString(tst, std::wstring(L"%sh"), std::wstring(L""));
        _ASSERT(tst == L"123\n\r45");
        if (tst != L"123\n\r45")
            ret = false;
    }

    {
        std::wstring tst(L"123%sh\n\r45");
        stringutils::replaceSubstringWithString(tst, std::wstring(L"%sh"), L"----");
        _ASSERT(tst == L"123----\n\r45");
        if (tst != L"123----\n\r45")
            ret = false;
    }
    {
        std::wstring tst(L"123%sh\n\r45");
        stringutils::replaceSubstringWithString(tst, L"%sh", std::wstring(L"----"));
        _ASSERT(tst == L"123----\n\r45");
        if (tst != L"123----\n\r45")
            ret = false;
    }
    return ret;
}

static bool test_splitString() {
    auto ret = true;
    {
        auto res = stringutils::splitString(std::string(",,,cce\nghh"), ",\n");
        _ASSERT(res.size() == 2);
        _ASSERT(res[0] == "cce");
        _ASSERT(res[1] == "ghh");
        if (res.size() != 2 || res[0] != "cce" || res[1] != "ghh")
            ret = false;
    }
    {
        auto res = stringutils::splitString(std::string(",,,cce\nghh"), std::string(",\n"));
        _ASSERT(res.size() == 2);
        _ASSERT(res[0] == "cce");
        _ASSERT(res[1] == "ghh");
        if (res.size() != 2 || res[0] != "cce" || res[1] != "ghh")
            ret = false;
    }

    {
        auto res = stringutils::splitString(std::string("aa"), ',');
        _ASSERT(res.size() == 1);
        _ASSERT(res[0] == "aa");
        if (res.size() != 1 || res[0] != "aa")
            ret = false;
    }
    {
        auto res = stringutils::splitString(std::string("aa,BB,cc"), ',');
        _ASSERT(res.size() == 3);
        _ASSERT(res[0] == "aa");
        _ASSERT(res[1] == "BB");
        _ASSERT(res[2] == "cc");
        if (res.size() != 3 || res[0] != "aa" || res[1] != "BB" || res[2] != "cc")
            ret = false;
    }
    {
        auto res = stringutils::splitString(std::string(",cc"), ',');
        _ASSERT(res.size() == 1);
        _ASSERT(res[0] == "cc");
        if (res.size() != 1 || res[0] != "cc")
            ret = false;
    }
    {
        auto res = stringutils::splitString(std::string(",ff,,cc,,"), ',');
        _ASSERT(res.size() == 2);
        _ASSERT(res[0] == "ff");
        _ASSERT(res[1] == "cc");
        if (res.size() != 2 || res[0] != "ff" || res[1] != "cc")
            ret = false;
    }
    {
        auto res = stringutils::splitString(std::string(",cc,"), ',');
        _ASSERT(res.size() == 1);
        _ASSERT(res[0] == "cc");
        if (res.size() != 1 || res[0] != "cc")
            ret = false;
    }
    {
        auto res = stringutils::splitString(std::string("cc,,,"), ',');
        _ASSERT(res.size() == 1);
        _ASSERT(res[0] == "cc");
        if (res.size() != 1 || res[0] != "cc")
            ret = false;
    }
    {
        auto res = stringutils::splitString(std::string(",,,cce"), ',');
        _ASSERT(res.size() == 1);
        _ASSERT(res[0] == "cce");
        if (res.size() != 1 || res[0] != "cce")
            ret = false;
    }

    {
        auto res = stringutils::splitString(std::wstring(L""), L',');
        _ASSERT(res.size() == 0);
        if (res.size() != 0)
            ret = false;
    }
    {
        auto res = stringutils::splitString(std::wstring(L"aa,BB,cc"), L',');
        _ASSERT(res.size() == 3);
        _ASSERT(res[0] == L"aa");
        _ASSERT(res[1] == L"BB");
        _ASSERT(res[2] == L"cc");
        if (res.size() != 3 || res[0] != L"aa" || res[1] != L"BB" || res[2] != L"cc")
            ret = false;
    }
    {
        auto res = stringutils::splitString(std::wstring(L"aa,BB,cc dd\n\rxx"), std::wstring(L", \n\r"));
        _ASSERT(res.size() == 5);
        _ASSERT(res[0] == L"aa");
        _ASSERT(res[1] == L"BB");
        _ASSERT(res[2] == L"cc");
        _ASSERT(res[3] == L"dd");
        _ASSERT(res[4] == L"xx");
        if (res.size() != 5 || res[0] != L"aa" || res[1] != L"BB" || res[2] != L"cc" || res[3] != L"dd" || res[4] != L"xx")
            ret = false;
    }
    return ret;
}

static bool test_StringConvert()
{
    auto ret = true;
    {
        std::vector<std::pair<std::wstring, std::string>> errorVect;
        std::vector<std::wstring> tst;
        const auto rangeStart = 0x20;
        const auto rangeEnd = 512;
        for (int val = rangeStart; val < rangeEnd; val++) {
            const auto &testChar = val;
            const auto testWChar =static_cast<wchar_t>(testChar);
            const auto str1W = std::wstring(1, testWChar);
            auto ret1A = stringutils::ConvertW2A(str1W, true);
            auto ret1W = stringutils::ConvertA2W(ret1A, true);
            if (str1W == ret1W)
                tst.emplace_back(str1W);
            else
                errorVect.emplace_back(str1W, ret1A);
            //_ASSERT(str1W == ret1W);
        }
        if (!errorVect.empty()){
            ret = false;
            _ASSERT(0);
        }
    }

    {
        const auto str1W = std::wstring(L"abcd4567]]");
        auto ret1A = stringutils::ConvertW2A(str1W, true);
        auto ret1W = stringutils::ConvertA2W(ret1A, true);
        _ASSERT(str1W == ret1W);
        if (str1W != ret1W)
            ret = false;
    }
    {
        const auto str1W = std::wstring(L"АБВГД");
        auto ret1A = stringutils::ConvertW2A(str1W, true);
        auto ret1W = stringutils::ConvertA2W(ret1A, true);
        _ASSERT(str1W == ret1W);
        if (str1W != ret1W)
            ret = false;
    }
    {
        const auto str1W = std::wstring(L"\u0410\u0411\u0412\u0413\u0414\u0415\uFEE6\uFEE7\uFEE8\uFEE9");
        auto ret1A = stringutils::ConvertW2A(str1W, true);
        auto ret1W = stringutils::ConvertA2W(ret1A, true);
        _ASSERT(str1W == ret1W);
        if (str1W != ret1W)
            ret = false;
    }
    {

        const auto str1W = std::wstring(L"абвгіЇüöä");
        auto ret1A = stringutils::ConvertW2A(str1W, true);
        auto ret1W = stringutils::ConvertA2W(ret1A, true);
        _ASSERT(str1W == ret1W);
        if (str1W != ret1W)
            ret = false;
    }
    {

        const auto str1W = std::wstring();
        auto ret1A = stringutils::ConvertW2A(str1W, true);
        auto ret1W = stringutils::ConvertA2W(ret1A, true);
        _ASSERT(str1W == ret1W);
        if (str1W != ret1W)
            ret = false;
    }
    {

        const auto str1W = std::wstring();
        auto ret1A = stringutils::ConvertW2A(str1W, true);
        auto ret1W = stringutils::ConvertA2W(ret1A, true);
        _ASSERT(str1W == ret1W);
        if (str1W != ret1W)
            ret = false;
    }
    {
        const auto str1W = std::wstring(
            L"a b c d e f x y "
            L"\u0410\u0411\u0412\u0413\u0414\u0415\uFEE6\uFEE7\uFEE8\uFEE9");
        auto ret1A = stringutils::ConvertW2A(str1W, true);
        auto ret1W = stringutils::ConvertA2W(ret1A, true);
        _ASSERT(str1W == ret1W);
        if (str1W != ret1W)
            ret = false;
    }
    return ret;
}

static void testLogOutput()
{
    {

#if !defined(_MSC_VER) && defined(__cplusplus) && (__cplusplus < 202002L)
        LOG_TRACE("------------------- Start Log EXT CHARS -------------------");
        LOG_TRACE( u8"6 - sym abvgiy [абвгіЇ]");
        LOG_TRACE( u8"6 - sym abvgiy [абвгіЇ]");
        LOG_TRACE( u8"3 - sym uoa [üöä]");
        LOG_TRACE( u8"5 - [こんにちは]");
        LOG_TRACE("------------------- End Log EXT CHARS -------------------");
#endif

        LOG_TRACE("------------------- Start Log empty lines -------------------");
        LOG_TRACE(std::string("").c_str());
        LOG_TRACE(std::wstring(L"").c_str());
        LOG_TRACE(std::string(""));
        LOG_TRACE(std::wstring(L""));
        LOG_TRACE("");
        LOG_INFO("");
        LOG_ERROR("");
        LOG_TRACE("------------------- End Log empty lines -------------------");

        LOG_TRACE("------------------- Start Log simple lines -------------------");
        LOG_TRACE("[TRACE  simple char]");
        LOG_INFO("[INFO   simple char]");
        LOG_ERROR("[ERROR  simple char]");

        LOG_TRACE(L"[TRACE simple wchar]");
        LOG_INFO(L"[INFO  simple wchar]");
        LOG_ERROR(L"[ERROR simple wchar]");

        LOG_TRACE(std::string("[TRACE  std::string]"));
        LOG_INFO(std::string("[INFO   std::string]"));
        LOG_ERROR(std::string("[ERROR  std::string]"));

        LOG_TRACE(std::wstring(L"[TRACE std::wstring]"));
        LOG_INFO(std::wstring(L"[INFO  std::wstring]"));
        LOG_ERROR(std::wstring(L"[ERROR std::wstring]"));
        LOG_TRACE("------------------- End Log simple lines -------------------");
    }
    {
        LOG_TRACE("------------------- Start Log extend info -------------------");
        LOG_EXTENDEDLOG(true);
        LOG_TRACE("[TRACE  simple char]");
        LOG_INFO("[INFO   simple char]");
        LOG_ERROR("[ERROR  simple char]");

        LOG_TRACE(L"[TRACE simple wchar]");
        LOG_INFO(L"[INFO  simple wchar]");
        LOG_ERROR(L"[ERROR simple wchar]");
        LOG_EXTENDEDLOG(false);
        LOG_TRACE("------------------- End Log extend info -------------------");
    }

    LOG_TRACE("------------------- Start Log overload test -------------------");
    {
        LOG_TRACE("[TRACE [" PRF_CH_STRING "]]", "char string");
        LOG_INFO("[INFO  [" PRF_CH_STRING "]]", "char string");
        LOG_ERROR("[ERROR [" PRF_CH_STRING "]]", "char string");

        LOG_TRACE("[TRACE [" PRF_CH_STRING "]]", "char string");
        LOG_INFO("[INFO  [" PRF_CH_STRING "]]", "char string");
        LOG_ERROR("[ERROR [" PRF_CH_STRING "]]", "char string");

        LOG_TRACE(std::string("[TRACE [" PRF_CH_STRING "]]"), "char std::string");
        LOG_INFO(std::string("[INFO  [" PRF_CH_STRING "]]"), "char std::string");
        LOG_ERROR(std::string("[ERROR [" PRF_CH_STRING "]]"), "char std::string");

        LOG_TRACE(std::wstring(L"[TRACE [" PRF_W_STRING "]]"), L"wchar std::wstring");
        LOG_INFO(std::wstring(L"[INFO  [" PRF_W_STRING "]]"), L"wchar std::wstring");
        LOG_ERROR(std::wstring(L"[ERROR [" PRF_W_STRING "]]"), L"wchar std::wstring");
    }
    {
        LOG_TRACE(L"[VAL [" PRF_W_STRING "] [%" PRId8  "]]", L"test -128", -128);
        LOG_TRACE(L"[VAL [" PRF_W_STRING "] [%" PRId16 "]]", L"test -32767", -32767);
        LOG_TRACE(L"[VAL [" PRF_W_STRING "] [%" PRId32 "]]", L"test -2147483647", -2147483647);

        LOG_TRACE(L"[VAL [" PRF_W_STRING "] [%" PRIu8  "]]", L"test 255", 255);
        LOG_TRACE(L"[VAL [" PRF_W_STRING "] [%" PRIu16 "]]", L"test 65535", 65535);
        LOG_TRACE(L"[VAL [" PRF_W_STRING "] [%" PRIu32 "]]", L"test 4294967295", 4294967295);
    }
    {
        LOG_TRACE(std::string("[TRACE std::string [%" PRIu64 "] [" PRF_CH_STRING "]]"), 33ull, "test 33");
        LOG_INFO(std::string("[INFO  std::string [%" PRIu64 "] [" PRF_CH_STRING "]]"), 34ull, "test 34");
        LOG_ERROR(std::string("[ERROR std::string [%" PRIu64 "] [" PRF_CH_STRING "]]"), 35ull, "test 35");

        LOG_TRACE(std::wstring(L"[TRACE std::wstring [%" PRId64 "] [" PRF_W_STRING "]]"), 36ll, L"test 36");
        LOG_INFO(std::wstring(L"[INFO  std::wstring [%" PRId64 "] [" PRF_W_STRING "]]"), 37ll, L"test 37");
        LOG_ERROR(std::wstring(L"[ERROR std::wstring [%" PRId64 "] [" PRF_W_STRING "]]"), 38ll, L"test 38");
    }
    {
        LOG_TRACE(std::string("[TEST  CH STR PRId64 [" PRF_CH_STRING "] [%" PRId64 "]]"), "9223372036854775807", 0x7FFFFFFFFFFFFFFFll);
        LOG_TRACE(std::string("[TEST  CH PRId64 STR [%" PRId64 "] [" PRF_CH_STRING "]]"), 0x7FFFFFFFFFFFFFFFll, "9223372036854775807");

        LOG_TRACE(std::wstring(L"[TEST WCH STR PRId64 [" PRF_W_STRING L"] [%" TOWSTRING(PRId64) L"]]"), L"9223372036854775807", 0x7FFFFFFFFFFFFFFFll);
        LOG_TRACE(std::wstring(L"[TEST WCH PRId64 STR [%" TOWSTRING(PRId64) L"] [" PRF_W_STRING L"]]"), 0x7FFFFFFFFFFFFFFFll, L"9223372036854775807");

        LOG_TRACE(std::string("[TEST  CH STR PRId64 [" PRF_CH_STRING "] [%" PRId64 "]]"), "0", 0ll);
        LOG_TRACE(std::string("[TEST  CH PRId64 STR [%" PRId64 "] [" PRF_CH_STRING "]]"), 0ll, "0");

        LOG_TRACE(std::wstring(L"[TEST WCH STR PRId64 [" PRF_W_STRING L"] [%" TOWSTRING(PRId64) L"]]"), L"0", 0ll);
        LOG_TRACE(std::wstring(L"[TEST WCH PRId64 STR [%" TOWSTRING(PRId64) L"] [" PRF_W_STRING L"]]"), 0ll, L"0");

        LOG_TRACE(std::string("[TEST  CH STR PRId64 [" PRF_CH_STRING "] [%" PRId64 "]]"), "60", 60ll);
        LOG_TRACE(std::string("[TEST  CH PRId64 STR [%" PRId64 "] [" PRF_CH_STRING "]]"), 60ll, "60");

        LOG_TRACE(std::wstring(L"[TEST WCH STR PRId64 [" PRF_W_STRING L"] [%" TOWSTRING(PRId64) L"]]"), L"60", 60ll);
        LOG_TRACE(std::wstring(L"[TEST WCH PRId64 STR [%" TOWSTRING(PRId64) L"] [" PRF_W_STRING L"]]"), 60ll, L"60");
    }
    LOG_TRACE("------------------- End Log overload test -------------------");
}

static bool test_guid()
{
    auto ret = true;
    {
        constexpr GUID guid = {0xf54f83c5, 0x9724, 0x41ba, {0xbb, 0xdb, 0x69, 0x26, 0xf7, 0xbd, 0x68, 0x13}};
        auto retres = stringutils::guidToString(&guid);
        _ASSERT(retres == "F54F83C5-9724-41BA-BBDB-6926F7BD6813");
        if (retres != "F54F83C5-9724-41BA-BBDB-6926F7BD6813")
            ret = false;
    }
    return ret;
}

static void test_GetVersionString()
{
    // overload test
    info::GetVersionString(std::string("1"));
    info::GetVersionString(std::wstring(L"2"));
    info::GetVersionString("3");
    info::GetVersionString(L"4");
}


class TestThreadsLog {
public:
    TestThreadsLog(TestThreadsLog&) = delete;
    TestThreadsLog& operator=(const TestThreadsLog&) = delete;
    TestThreadsLog() {
        for (size_t i = 0; i < 100; i++)
        {
            const int32_t threadid = m_threadsStart++;
            auto RunThread = [threadid](TestThreadsLog* pThis) {
                pThis->m_threadsRun++;
                LOG_TRACE("START ________ thread id %04" PRId32, threadid);
                try {
                    for (int64_t i = 0; i < 300; i++) {
                        const decltype(i)& ind = i;
                        LOG_TRACE("[%04" PRId32 "] [%08" PRId64 "]", threadid, ind);
                    }
                }
                catch (...) {
                    _ASSERT(0);
                }
                pThis->m_threadsRun--;
                pThis->m_threadsStart--;
                LOG_TRACE("EXIT ________ thread id %04" PRId32, threadid);
            };
            (std::thread(RunThread, this)).detach();
        }
     }
     ~TestThreadsLog() {
         auto timeout = 100;
         while (runThreadsCount() > 0 && timeout-- > 0) {
             std::this_thread::sleep_for(std::chrono::milliseconds(20));
         }

         if (timeout == 0) {
             //do something
             _ASSERT(0);
         }
     }
     int32_t runThreadsCount() {
         return (m_threadsRun.load() + m_threadsStart.load());
     }
private:
    std::atomic_int32_t m_threadsRun = {};
    std::atomic_int32_t m_threadsStart = {};
};

class TestThreadsStringFormat {
public:
    TestThreadsStringFormat(TestThreadsStringFormat&) = delete;
    TestThreadsStringFormat& operator=(const TestThreadsStringFormat&) = delete;
    TestThreadsStringFormat() {
        for (size_t xxx = 0; xxx < 100; xxx++)
        {
            const int32_t threadid = m_threadsStart++;
            auto RunThread = [threadid](TestThreadsStringFormat* pThis) {
                pThis->m_threadsRun++;
                //LOG_TRACE("START ________ thread id %04" PRId32, threadid);
				try {
					for (int64_t i = 0; i < 1000; i++) {
                        {
                            const decltype(i)& ind = i;
                            const auto paramInd = std::to_string(ind);
                            const auto paramId = std::to_string(threadid);
                            const auto res = stringutils::FormatString(" Thread [" PRF_CH_STRING "] [" PRF_CH_STRING "]", paramInd.c_str(), paramId.c_str());
                            const auto tst = std::string(" Thread [") + paramInd + "] [" + paramId + "]";
                            _ASSERT(res == tst);
                            if (res != tst)
                                throw std::runtime_error("Oh no, something wrong here");
                        }
                        {
                            const decltype(i)& ind = i;
                            const auto paramInd = std::to_wstring(ind);
                            const auto paramId = std::to_wstring(threadid);
                            const auto res = stringutils::FormatString(L" Thread [" PRF_W_STRING "] [" PRF_W_STRING "]", paramInd.c_str(), paramId.c_str());
                            const auto tst = std::wstring(L" Thread [") + paramInd + L"] [" + paramId + L"]";
                            _ASSERT(res == tst);
                            if (res != tst)
                                throw std::runtime_error("Oh no, something wrong here");
                        }
                    }
				}
				catch (...) {
                    _ASSERT(0);
                    LOG_ERROR("TestThreadsStringFormat FAILED");
				}
                pThis->m_threadsRun--;
                pThis->m_threadsStart--;
                //LOG_TRACE("EXIT ________ thread id %04" PRId32, threadid);
            };
            (std::thread(RunThread, this)).detach();
        }
     }
     ~TestThreadsStringFormat() {
         auto timeout = 100;
         while (runThreadsCount() > 0 && timeout-- > 0) {
             std::this_thread::sleep_for(std::chrono::milliseconds(20));
         }

         if (timeout == 0) {
             //do something
             _ASSERT(0);
         }
     }
     int32_t runThreadsCount() {
         return (m_threadsRun.load() + m_threadsStart.load());
     }
private:
    std::atomic_int32_t m_threadsRun = {};
    std::atomic_int32_t m_threadsStart = {};
};


//#define STRINTEMPLATETEST
#ifdef STRINTEMPLATETEST

std::string myStr(std::string val) {
    return val;
}

std::wstring myStr(std::wstring val) {
    return val;
}

template<typename T>
auto strOverloadAndTemplate(T val)
{
    std::basic_string<typename decltype(myStr(val))::value_type> retString(val);
    return retString;
}

/// <summary>
/// make std::string or std::wstring from std::string, std::wstring, const char *,const wchar_t*
/// </summary>
/// <typeparam name="T">std::string, std::wstring, const char*,const wchar_t*</typeparam>
/// <param name="val">text </param>
/// <returns>std::string or std::wstring with text</returns>
template<typename T>
auto strTemplate(T val)
{
    std::basic_string<
        typename std::conditional<(((std::is_same<T, std::string>::value) || std::is_convertible<T, char const*>::value)),
        char, wchar_t
    >::type>
        retString(val);
    return retString;
}

void OverloadTest(){
    const char* t1 = "const char*";
    static_assert(std::is_same<decltype(strOverloadAndTemplate(t1)), std::string>::value,"");
    static_assert(std::is_same<decltype(strTemplate(t1)), std::string>::value,"");
    UNREFERENCED_PARAMETER_LOG(t1);

    char t2[] = "char*";
    static_assert(std::is_same<decltype(strTemplate(t2)), std::string>::value, "");
    UNREFERENCED_PARAMETER_LOG(t2);

    const wchar_t* t3 = L"const wchar_t*";
    static_assert(std::is_same<decltype(strTemplate(t3)), std::wstring>::value, "");
    UNREFERENCED_PARAMETER_LOG(t3);

    wchar_t t4[] = L"wchar_t*";
    static_assert(std::is_same<decltype(strTemplate(t4)), std::wstring>::value, "");
    UNREFERENCED_PARAMETER_LOG(t4);

    std::string t5 = "std::string";
    static_assert(std::is_same<decltype(strTemplate(t5)), std::string>::value, "");
    UNREFERENCED_PARAMETER_LOG(t5);

    std::wstring t6 = L"std::wstring";
    static_assert(std::is_same<decltype(strTemplate(t6)), std::wstring>::value, "");
    UNREFERENCED_PARAMETER_LOG(t6);

    const std::string t7 = "const std::string";
    static_assert(std::is_same<decltype(strTemplate(t7)), std::string>::value, "");
    UNREFERENCED_PARAMETER_LOG(t7);

    const std::wstring t8 = L"const std::wstring";
    static_assert(std::is_same<decltype(strTemplate(t8)), std::wstring>::value, "");
    UNREFERENCED_PARAMETER_LOG(t8);

}
#endif // STRINTEMPLATETEST

//#define SLICINGEXAMPLE
#ifdef SLICINGEXAMPLE
struct AAA {
    AAA(){std::cout << "+++AAA()" << std::endl;};
    virtual ~AAA(){std::cout << "~AAA()" << std::endl;};
    virtual int Tst(){ return 41;};
};

struct BBB : public AAA {
    BBB(){std::cout << "+++BBB()" << std::endl;};
    virtual ~BBB(){std::cout << "~BBB()" << std::endl;};
    virtual int Tst() override { return 42;};
};

void PolymorphicSlicingTestCopy(AAA x){
    std::cout << "x.Tst() [41 = " << x.Tst() << "]" << std::endl;
    _ASSERT(x.Tst() == 41);
}

void PolymorphicSlicingTestRef(AAA &x){
    std::cout << "x.Tst() [42 = " << x.Tst() << "]" << std::endl;
    _ASSERT(x.Tst() == 42);
}

void PolymorphicSlicingExample(){
    BBB x;
    std::cout << "call PolymorphicSlicingTestCopy(AAA x)" << std::endl;
    PolymorphicSlicingTestCopy(x);
    std::cout << "call PolymorphicSlicingTestRef(AAA &x)" << std::endl;
    PolymorphicSlicingTestRef(x);
}
#endif

//#define TEST_TESTREMOVECONSTANDPOINTER
#ifdef TEST_TESTREMOVECONSTANDPOINTER
template <typename T, typename U>
constexpr bool is_decay_equ = std::is_same<typename std::decay<T>::type, U>::value;

void tstDecay()
{

    //static_assert(is_decay_equ<const wchar_t* const, wchar_t*>, "");
    //static_assert(is_decay_equ<const char* const, char>, "");
    static_assert(is_decay_equ<int, int>, "");
    static_assert(!is_decay_equ<int, float>, "");
    static_assert(is_decay_equ<const wchar_t* const, const wchar_t*>, "");
    static_assert(is_decay_equ<const char* const, const char*>, "");
    static_assert(is_decay_equ<const int, int>, "");
    static_assert(is_decay_equ<int&, int>, "");
    static_assert(is_decay_equ<int&&, int>, "");
    static_assert(is_decay_equ<const int&, int>, "");
    static_assert(is_decay_equ<int[2], int*>, "");
    static_assert(!is_decay_equ<int[4][2], int*>, "");
    static_assert(!is_decay_equ<int[4][2], int**>, "");
    static_assert(is_decay_equ<int[4][2], int(*)[2]>, "");
    static_assert(is_decay_equ<int(int), int(*)(int)>, "");

    {
        const wchar_t* const _Format = nullptr;
        using typ2 = typename std::remove_const<std::remove_pointer<decltype(_Format)>::type>::type;
        static_assert(std::is_same<typ2, wchar_t>::value, "");
    }
    {
        const char* const _Format = nullptr;
        using typ2 = typename std::remove_const<std::remove_pointer<decltype(_Format)>::type>::type;
        static_assert(std::is_same<typ2, char>::value, "");
    }
}

template <typename T, typename U>
std::wstring TestRemoveConstAndPointer(const T* const _Format) {
    using typ1 = typename std::remove_const<typename std::remove_pointer<decltype(_Format)>::type>::type;
    static_assert(std::is_same<typ1, U>::value, "");
    std::vector<typ1> buffer(2, 0);
    return buffer.data();
};

#endif

/////////////////////////////////////////////////////////////


static void FormatStringTestBase()
{
	const wchar_t* ptrW = nullptr;
	stringutils::FormatString(ptrW);
	const char* ptrA = nullptr;
	stringutils::FormatString(ptrA);
	const char* ptrA1 = "";
	stringutils::FormatString(ptrA1);
	stringutils::FormatString(L"");
	stringutils::FormatString("");

	auto resAs1 = stringutils::FormatString<16, 256, 8192>("123456789012345");
	_ASSERT(resAs1 == std::string("123456789012345"));

	auto resWs1 = stringutils::FormatString<16, 256, 8192>(L"123456789012345");
	_ASSERT(resWs1 == std::wstring(L"123456789012345"));

	auto resAs2 = stringutils::FormatString<16, 256, 8192>("1234567890123456");
	_ASSERT(resAs2 == std::string("1234567890123456"));

	auto resWs2 = stringutils::FormatString<16, 256, 8192>(L"1234567890123456");
	_ASSERT(resWs2 == std::wstring(L"1234567890123456"));

	auto resAs3 = stringutils::FormatString<16, 256, 8192>("12345678901234567");
	_ASSERT(resAs3 == std::string("12345678901234567"));

	auto resWs3 = stringutils::FormatString<16, 256, 8192>(L"12345678901234567");
	_ASSERT(resWs3 == std::wstring(L"12345678901234567"));

	auto resAs4 = stringutils::FormatString<16, 256, 8192>("123456789012345678");
	_ASSERT(resAs4 == std::string("123456789012345678"));

	auto resWs4 = stringutils::FormatString<16, 256, 8192>(L"123456789012345678");
	_ASSERT(resWs4 == std::wstring(L"123456789012345678"));

	{
		int64_t i64val1 = INT64_MAX;
		auto resWs = stringutils::FormatString(L"[0x%08" PRIX64 "0x%08" PRIX64 "0x%08" PRIX64 "0x%08" PRIX64 "0x%08" PRIX64 "0x%08" PRIX64 " " PRF_CH_STRING "]",
			i64val1, i64val1, i64val1, i64val1, i64val1, i64val1,
			L"12345678890123456788901234567889012345678890123456788901234567889012345678890123456788901234567889012345678890"
			"12345678890123456788901234567889012345678890123456788901234567889012345678890123456788901234567889012345678890"
			"12345678890123456788901234567889012345678890123456788901234567889012345678890123456788901234567889012345678890"
		);

		_ASSERT(resWs == std::wstring(
			L"["
			"0x7FFFFFFFFFFFFFFF0x7FFFFFFFFFFFFFFF0x7FFFFFFFFFFFFFFF0x7FFFFFFFFFFFFFFF0x7FFFFFFFFFFFFFFF0x7FFFFFFFFFFFFFFF"
			" "
			"12345678890123456788901234567889012345678890123456788901234567889012345678890123456788901234567889012345678890"
			"12345678890123456788901234567889012345678890123456788901234567889012345678890123456788901234567889012345678890"
			"12345678890123456788901234567889012345678890123456788901234567889012345678890123456788901234567889012345678890"
			"]"));
	}



    int64_t i64val = 9223372036854775807ll;
#if 0
	stringutils::FormatString("%" PRId32, i64val);
	stringutils::FormatString(L"%" PRId32, i64val);
#else
	stringutils::FormatString("%" PRId64, i64val);
	stringutils::FormatString(L"%" PRId64, i64val);
#endif // 0


	// declare and initialize signed variables with max values
	int8_t i8_max = INT8_MAX;  // 127
	int16_t i16_max = INT16_MAX; // 32767
	int32_t i32_max = INT32_MAX; // 2147483647
	int64_t i64_max = INT64_MAX; // 9223372036854775807

	// declare and initialize signed variables with min values
	int8_t i8_min = INT8_MIN;  // -128
	int16_t i16_min = INT16_MIN; // -32768
	int32_t i32_min = INT32_MIN; // -2147483648
	int64_t i64_min = INT64_MIN; // -9223372036854775808

	// declare and initialize unsigned variables with max values
	uint8_t u8_max = UINT8_MAX;  // 255
	uint16_t u16_max = UINT16_MAX; // 65535
	uint32_t u32_max = UINT32_MAX; // 4294967295
	uint64_t u64_max = UINT64_MAX; // 18446744073709551615

	{
		auto strParamA = "some1234teststring";
		auto strParamA2 = "End teststring";

		auto srcA1 =
			"[" PRF_CH_STRING "==some1234teststring] "
			"[%" PRId8 "==127] "
			"[%" PRId16 "==32767] "
			"[%" PRId32 "==2147483647] "
			"[%" PRId64 "==9223372036854775807] "

			"[%" PRId8 "==-128] "
			"[%" PRId16 "==-32768] "
			"[%" PRId32 "==2147483648] "
			"[%" PRId64 "==-9223372036854775808] "

			"[%" PRIu8 "==255] "
			"[%" PRIu16 "==65535] "
			"[%" PRIu32 "==4294967295] "
			"[%" PRIu64 "==18446744073709551615] "
			"[" PRF_CH_STRING "==End teststring]"
			;
		auto resA1 = std::string(
			"[some1234teststring==some1234teststring] "
			"[127==127] "
			"[32767==32767] "
			"[2147483647==2147483647] "
			"[9223372036854775807==9223372036854775807] "
			"[-128==-128] "
			"[-32768==-32768] "
			"[-2147483648==2147483648] "
			"[-9223372036854775808==-9223372036854775808] "
			"[255==255] "
			"[65535==65535] "
			"[4294967295==4294967295] "
			"[18446744073709551615==18446744073709551615] "
			"[End teststring==End teststring]");

		auto tst1 = stringutils::FormatString(srcA1,
			strParamA,
			i8_max,  // 127
			i16_max, // 32767
			i32_max, // 2147483647
			i64_max, // 9223372036854775807

			// declare and initialize signed variables with min values
			i8_min,  // -128
			i16_min, // -32768
			i32_min, // -2147483648
			i64_min, // -9223372036854775808

			// declare and initialize unsigned variables with max values
			u8_max,  // 255
			u16_max, // 65535
			u32_max, // 4294967295
			u64_max,  // 18446744073709551615
			strParamA2
		);

		_ASSERT(tst1 == resA1);
		UNREFERENCED_PARAMETER_LOG(tst1);
		UNREFERENCED_PARAMETER_LOG(resA1);
	}
	{
		auto strParamW = L"some1234teststring";
		auto strParamW2 = L"End teststring";
		auto srcW1 =
			L"[" PRF_W_STRING "==some1234teststring] "
			"[%" PRId8 "==127] "
			"[%" PRId16 "==32767] "
			"[%" PRId32 "==2147483647] "
			"[%" PRId64 "==9223372036854775807] "

			"[%" PRId8 "==-128] "
			"[%" PRId16 "==-32768] "
			"[%" PRId32 "==2147483648] "
			"[%" PRId64 "==-9223372036854775808] "

			"[%" PRIu8 "==255] "
			"[%" PRIu16 "==65535] "
			"[%" PRIu32 "==4294967295] "
			"[%" PRIu64 "==18446744073709551615] "
			"[" PRF_W_STRING "==End teststring]"
			;

		auto resW1 = std::wstring(
			L"[some1234teststring==some1234teststring] "
			L"[127==127] "
			L"[32767==32767] "
			L"[2147483647==2147483647] "
			L"[9223372036854775807==9223372036854775807] "
			L"[-128==-128] "
			L"[-32768==-32768] "
			L"[-2147483648==2147483648] "
			L"[-9223372036854775808==-9223372036854775808] "
			L"[255==255] "
			L"[65535==65535] "
			L"[4294967295==4294967295] "
			L"[18446744073709551615==18446744073709551615] "
			L"[End teststring==End teststring]");

		auto tst1 = stringutils::FormatString(srcW1,
			strParamW,
			i8_max,  // 127
			i16_max, // 32767
			i32_max, // 2147483647
			i64_max, // 9223372036854775807

			// declare and initialize signed variables with min values
			i8_min,  // -128
			i16_min, // -32768
			i32_min, // -2147483648
			i64_min, // -9223372036854775808

			// declare and initialize unsigned variables with max values
			u8_max,  // 255
			u16_max, // 65535
			u32_max, // 4294967295
			u64_max,  // 18446744073709551615
			strParamW2
		);

		_ASSERT(tst1 == resW1);
		UNREFERENCED_PARAMETER_LOG(tst1);
		UNREFERENCED_PARAMETER_LOG(resW1);
	}
	_ASSERT(stringutils::FormatString(L"[VAL [" PRF_W_STRING "] [%" PRId8  "]]", L"test -128", -128)
		== std::wstring(L"[VAL [test -128] [-128]]"));

	_ASSERT(stringutils::FormatString(L"[VAL [" PRF_W_STRING "] [%" PRId16 "]]", L"test -32767", -32767)
		== std::wstring(L"[VAL [test -32767] [-32767]]"));

	_ASSERT(stringutils::FormatString(L"[VAL [" PRF_W_STRING "] [%" PRId32 "]]", L"test -2147483647", -2147483647)
		== std::wstring(L"[VAL [test -2147483647] [-2147483647]]"));

	_ASSERT(stringutils::FormatString(L"[VAL [" PRF_W_STRING "] [%" PRIu8  "]]", L"test 255", 255U)
		== std::wstring(L"[VAL [test 255] [255]]"));

	_ASSERT(stringutils::FormatString(L"[VAL [" PRF_W_STRING "] [%" PRIu16 "]]", L"test 65535", 65535U)
		== std::wstring(L"[VAL [test 65535] [65535]]"));

	_ASSERT(stringutils::FormatString(L"[VAL [" PRF_W_STRING "] [%" PRIu32 "]]", L"test 4294967295", 4294967295UL)
		== std::wstring(L"[VAL [test 4294967295] [4294967295]]"));

	_ASSERT(stringutils::FormatString("[%" PRIu64 "][" PRF_CH_STRING "]", 33ull, "33")
		== std::string("[33][33]"));

	_ASSERT(stringutils::FormatString(L"[%" PRId64 "][" PRF_W_STRING "]", 36ll, L"36")
		== std::wstring(L"[36][36]"));

	_ASSERT(stringutils::FormatString("[" PRF_CH_STRING "][%" PRId64 "]", "9223372036854775807", 0x7FFFFFFFFFFFFFFFll)
		== std::string("[9223372036854775807][9223372036854775807]"));

	_ASSERT(stringutils::FormatString("[%" PRId64 "][" PRF_CH_STRING "]", 0x7FFFFFFFFFFFFFFFll, "9223372036854775807")
		== std::string("[9223372036854775807][9223372036854775807]"));

	_ASSERT(stringutils::FormatString(L"[" PRF_W_STRING L"][%" TOWSTRING(PRId64) L"]", L"9223372036854775807", 0x7FFFFFFFFFFFFFFFll)
		== std::wstring(L"[9223372036854775807][9223372036854775807]"));

	_ASSERT(stringutils::FormatString(L"[%" TOWSTRING(PRId64) L"][" PRF_W_STRING L"]", 0x7FFFFFFFFFFFFFFFll, L"9223372036854775807")
		== std::wstring(L"[9223372036854775807][9223372036854775807]"));

}

static inline void test() {

    std::string s1("0");
    STRAPPEND(s1, "1");
    STRAPPEND2(s1, std::string("2"));
    _ASSERT(s1 == std::string("012"));

    std::wstring s2(L"0");
    STRAPPEND2(s2, L"1");
    STRAPPEND2(s2, std::wstring(L"2"));
    _ASSERT(s2 == std::wstring(L"012"));

    std::string s3("0");
    STRAPPEND2(s3, L"1");
    STRAPPEND2(s3, std::wstring(L"2"));
    _ASSERT(s3 == std::string("012"));

    std::wstring s4(L"0");
    STRAPPEND2(s4, "1");
    STRAPPEND2(s4, std::string("2"));
    _ASSERT(s4 == std::wstring(L"012"));
}

static void FormatStringFTest()
{
    CLogger::Instance().FormatStringF("szFmt %s %s", "args", "...");

    CLogger::Instance().FormatStringF(L"szFmt %s %s", L"args", L"...");

    //{
    //    CDummyXFile xf;
    //    FormatStringF(xf.GetFilePtr(), "szFmt %s %s", "args", "...");
    //}

    //{
    //    CDummyXFile xf;
    //    FormatStringF(xf.GetFilePtr(), L"szFmt %s %s", L"args", L"...");
    //}

    CLogger::Instance().LogMess( CLogger::eLogLevel::eLogLevel_trace, "szFile", "szFunc", 0, "szFmt %s", "args...");
    CLogger::Instance().LogMess( CLogger::eLogLevel::eLogLevel_trace, "szFile", "szFunc", 0, std::string("szFmt %s"), "args...");

    CLogger::Instance().LogMess( CLogger::eLogLevel::eLogLevel_trace, "szFile", "szFunc", 0, L"szFmt %ls", L"args...");
    CLogger::Instance().LogMess( CLogger::eLogLevel::eLogLevel_trace, "szFile", "szFunc", 0, std::wstring(L"szFmt %ls"), L"args...");

    char arr1[] = "hello %s";
    CLogger::Instance().LogMess( CLogger::eLogLevel::eLogLevel_trace, "szFile", "szFunc", 0, arr1, "args...");
    wchar_t arr2[] = L"hello %s";
    CLogger::Instance().LogMess( CLogger::eLogLevel::eLogLevel_trace, "szFile", "szFunc", 0, arr2, L"args...");

    const std::string cp1("szFmt %s");
    CLogger::Instance().LogMess( CLogger::eLogLevel::eLogLevel_trace, "szFile", "szFunc", 0, cp1, "args...");
    const std::wstring cp2(L"szFmt %ls");
    CLogger::Instance().LogMess( CLogger::eLogLevel::eLogLevel_trace, "szFile", "szFunc", 0, cp2, L"args...");

}


int main(/*int argc, char *argv[]*/) {

    // QCoreApplication app(argc, argv);

    {
        char tst = 0;
        static_assert(std::is_convertible<decltype(tst),const char >::value, "");
           
        wchar_t tstW1 = 0;
        static_assert(std::is_convertible<decltype(tstW1),const char >::value, "");

        char tst1[10]{};
        static_assert(std::is_convertible<decltype(tst1),const char *>::value, "");

        const char* tst2 = "";
        static_assert(std::is_convertible<decltype(tst2),const char *>::value, "");

        const char* const tst3 = "";
        static_assert(std::is_convertible<decltype(tst3),const char *>::value, "");

        wchar_t tstW = 0;
        static_assert(!std::is_convertible<decltype(tstW),const char *>::value, "");

        wchar_t tst1W[10]{};
        static_assert(!std::is_convertible<decltype(tst1W),const char *>::value, "");

        const wchar_t* tst2W = L"";
        static_assert(!std::is_convertible<decltype(tst2W),const char *>::value, "");

        const wchar_t* const tst3W = L"";
        static_assert(!std::is_convertible<decltype(tst3W),const char *>::value, "");
    }

    FormatStringTestBase();
#if 0
    FormatStringFTest();
#endif

#ifdef SLICINGEXAMPLE
    PolymorphicSlicingExample();
#endif // SLICINGEXAMPLE

 #if defined(WINDOWS_PLATFORM)
    SetConsoleOutputCP(CP_UTF8);
#endif // defined(WINDOWS_PLATFORM)

    //_ASSERT(0);
    _ASSERT(1);
    DBGASSERT(1);


 //__PRETTY_FUNCTION__
 //__FUNCSIG__

    int retres = ERROR_SUCCESS;

    try {

#if 0
        LOG_TRACE("------------------- Start String format threads test -------------------");
        {
            const auto startTime = std::chrono::high_resolution_clock::now();
            TestThreadsStringFormat testThread;
            while (testThread.runThreadsCount() > 0) {
                std::this_thread::sleep_for(std::chrono::milliseconds(20));
            }
            const auto finishTime = std::chrono::high_resolution_clock::now();
            const auto duration = std::chrono::duration_cast<std::chrono::duration<double>>(finishTime - startTime).count();
            LOG_TRACE("------------------- Test take %.6f sec. -------------------", duration);
        }
        LOG_TRACE("------------------- End  String format threads test -------------------");
#endif

        LOG_INITIALIZE();
        LOG_EXTENDEDLOG(false);
        {
            int64_t valInt64_1 = 0x5a6bc;
            int64_t valInt64_2 = 0x1;
            int64_t valInt64_3 = 0xaabbcc;
            int64_t valInt64_4 = 0xabc;
       
            LOGSTREAMA(CLogger::eLogLevel::eLogLevel_info)
                << "[Hi, char !]"
                /*
                     showbase useless with uppercase and setw
                    << "HEX [00X5A6BC]==["
                    << std::hex
                    << std::showbase
                    << std::uppercase
                    << std::setfill('0')
                    << std::setw(sizeof(valInt64_1))
                    << valInt64_1
                    << "] "
                */

                << "HEX [0x0005A6BC]==[0x"
                << std::hex
                << std::noshowbase
                << std::uppercase
                << std::setfill('0')
                << std::setw(sizeof(valInt64_1))
                << valInt64_1
                << "] "

                << "HEX [0x00000001]==[0x"
                << std::hex
                << std::setfill('0')
                << std::setw(sizeof(valInt64_2))
                << std::noshowbase
                << std::uppercase
                << valInt64_2
                << "] "

                << "HEX [0xABC]==[0x"
                << std::hex
                << valInt64_4
                << "] "

                << " DEC [7778]==["
                << std::dec
                << 7778
                << "] "

                << "HEX [0xAABBCC]==[0x"
                << std::hex
                << valInt64_3
                << "] "

                << " DEC [-1]==["
                << std::dec
                << -1
                << "] "

                << "[End!]";

            LOGSTREAMW(CLogger::eLogLevel::eLogLevel_info)
                << L"[Hi, char !]"

                /*
                     showbase useless with uppercase and setw
                    << "HEX [00X5A6BC]==["
                    << std::hex
                    << std::showbase
                    << std::uppercase
                    << std::setfill('0')
                    << std::setw(sizeof(valInt64_1))
                    << valInt64_1
                    << "] "
                */

                << "HEX [0x0005A6BC]==[0x"
                << std::hex
                << std::noshowbase
                << std::uppercase
                << std::setfill(L'0')
                << std::setw(sizeof(valInt64_1))
                << valInt64_1
                << "] "

                << "HEX [0x00000001]==[0x"
                << std::hex
                << std::setfill(L'0')
                << std::setw(sizeof(valInt64_2))
                << std::noshowbase
                << std::uppercase
                << valInt64_2
                << "] "

                << "HEX [0xABC]==[0x"
                << std::hex
                << valInt64_4
                << "] "

                << " DEC [7778]==["
                << std::dec
                << 7778
                << "] "

                << "HEX [0xAABBCC]==[0x"
                << std::hex
                << valInt64_3
                << "] "

                << " DEC [-1]==["
                << std::dec
                << -1
                << "] "

                << "[End!]";

        }
#if 0
        qDebug() << "[" << GetACP() << "]";
        qDebug() << "The default locale is " << std::locale().name().c_str() << '\n';
        qDebug() << "The user's locale is " << std::locale("").name().c_str() << '\n';

        const auto reser = std::system_category().message(0x3);
        auto xr1 = QString().fromLatin1(reser.c_str());
        auto xr2 = QString().fromStdString(reser);
        auto xr3 = QString().fromLocal8Bit(reser.c_str());

        qDebug() << "[" << xr1 << "]";
        qDebug() << "[" << xr2 << "]";
        qDebug() << "[" << xr3 << "]";
#endif

        try {
            throw app_error("111 test err");
            //throw std::runtime_error("111 test err");
        }
        catch (const std::exception& ex) {

            auto ptr = dynamic_cast<const app_error*>(&ex);
            if (ptr != nullptr) {
                auto p1 = ptr->Error();
                auto p2 = ST("111 test err");
                auto s1 = STRINGEXT(p1);
                auto s2 = STRINGEXT(p2);
                _ASSERT(s1 == s2);
            }
            _ASSERT(std::string(ex.what()) == std::string("111 test err"));
        } catch (...) {
            _ASSERT(0);
        }

        try {
            throw app_error(L"222 test err");
        }
        catch (const std::exception& ex) {
            auto ptr = dynamic_cast<const app_error*>(&ex);
            if (ptr != nullptr) {
                _ASSERT(STRINGEXT(ptr->Error()) == STRINGEXT(ST("222 test err")));
            }
            _ASSERT(std::string(ex.what()) == std::string("222 test err"));
        }

        try {
            throw app_error(L"333 test こんにちは err");
        }
        catch (const std::exception& ex) {

            auto ptr = dynamic_cast<const app_error*>(&ex);
            if (ptr){
                constexpr auto pa1 = ST("333 test こんにちは err");
                auto pa2 = ptr->Error();
                auto sa1 = STRINGEXT(pa1);
                auto sa2 = STRINGEXT(pa2);
                _ASSERT(sa1 == sa2);
            }

//            constexpr auto pb1 = u8"333 test こんにちは err";
//            auto pb2 = ex.what();

//            auto sb1 = std::string(pb1);
//            auto sb2 = std::string(pb2);

//            _ASSERT(sb1 == sb2);

        }

        LOG_INFO(ST("Thread [%") PRId32 "]", std::this_thread::get_id());

        auto executablePathAndName = info::executable_PathAndName();
        LOG_INFO(ST("executable_PathAndName [" ) PRF_T_STRING ST("]"), executablePathAndName.c_str());

        auto executableName = fsutils::getNameFromPath(executablePathAndName);

        LOG_INFO(info::GetVersionString(executableName));

        test_GetVersionString();

        auto res_test_guid = test_guid();
        _ASSERT(res_test_guid);
        if (!res_test_guid)
            retres = EXIT_FAILURE;

        auto res_test_StringConvert = test_StringConvert();
        _ASSERT(res_test_StringConvert);
        if (!res_test_StringConvert)
            retres = EXIT_FAILURE;

        auto res_test_replaceSubstr = test_replaceSubstr();
        _ASSERT(res_test_replaceSubstr);
        if (!res_test_replaceSubstr)
            retres = EXIT_FAILURE;

        auto res_test_splitString = test_splitString();
        _ASSERT(res_test_splitString);
        if (!res_test_splitString)
            retres = EXIT_FAILURE;

        testLogOutput();

        LOG_ERROR("------------------- Start Log predefined error codes -------------------");
        LOG_ERROR(CLogger::GetErrorStringW(573));
        LOG_ERROR(CLogger::GetErrorStringW(574));
        LOG_ERROR(CLogger::GetErrorStringW(712));
        //LOG_ERROR(CLogger::GetErrorStringW(0x0000168D));
        LOG_ERROR("-------------------  End Log predefined error codes -------------------");

        LOG_ERROR("-------------------  Start Log range error codes -------------------");
        auto index = 0x0L;
        while (index++ <= 0x10L) {
            const auto &ind = index;
            LOG_ERROR(CLogger::GetErrorStringW(ind));
        }
        LOG_ERROR("-------------------  End Log range error codes -------------------");


#if 0
        LOG_TRACE("------------------- Start Log threads test -------------------");
       {
            const auto startTime = std::chrono::high_resolution_clock::now();
            TestThreadsLog testThread;
            while (testThread.runThreadsCount() > 0) {
                std::this_thread::sleep_for(std::chrono::milliseconds(20));
            }
            const auto finishTime = std::chrono::high_resolution_clock::now();
            const auto duration = std::chrono::duration_cast<std::chrono::duration<double>>(finishTime - startTime).count();
            LOG_TRACE("------------------- Test take %.6f sec. -------------------", duration);
       }
       LOG_TRACE("------------------- End Log threads test -------------------");
#endif

       LOG_INFO(info::GetVersionString(executableName));



    } catch (const std::exception &ex) {
        std::cerr << "FAILED [" + std::string(typeid(ex).name()) << "] [" << ex.what() << "]" << std::endl;
        retres = EXIT_FAILURE;
    } catch (...) {
        retres = EXIT_FAILURE;
        try {
            std::rethrow_exception(std::current_exception());
        } catch (const std::exception &ex) {
            std::cerr << "FAILED [" + std::string(typeid(ex).name()) << "] [" << ex.what() << "]" << std::endl;
        } catch (...) {
            std::cerr << "FAILED [Unexpected exception]" << std::endl;
        }
    }

    _ASSERT(retres == ERROR_SUCCESS);
    std::cout << ">>>>>>>>>>>> EXIT! res[" << retres << "] <<<<<<<<<<<<<<<" << std::endl;

    return retres;
    // return app.exec();
}
/*
    QString getLogPath()
    {

        QSettings settings(QCoreApplication::organizationName(),QCoreApplication::applicationName());
        settings.sync();

        auto appName =QCoreApplication::applicationName().trimmed().replace(" ", "_") + ".log";
        auto orgName =QCoreApplication::organizationName().trimmed().replace(" ", "_");
        //test saved path exist and access allowed
        {
            QString loadedPath =settings.value(CONFIG_LOG_NAME).toString();
            if (!loadedPath.isEmpty())
            {
                try
                {
                    if (!loadedPath.endsWith(appName))
                        loadedPath =CFileIO::CombiningTwoPaths(loadedPath, appName);

                    QString testDir =CFileIO::GetPathWithoutFilename2(loadedPath);
                    if (!CFileIO::IsDirectoryExist(testDir))
                        CFileIO::CreateDirX(testDir);

                    if (!CFileIO::IsFileExist(loadedPath))
                        setLogPath(loadedPath);
                    return loadedPath;
                }
                catch (...)
                {
                }
            }
        }
        // search path to temporary folder and make worked path to log
        {
            QStringList locations;
            CFilesystemStandartPath::GetLogPath(locations);
            for (const auto& item : qAsConst(locations))
            {
                try
                {
                    auto tempPath =CFileIO::CombiningTwoPaths(item, orgName);
                    if(!CFileIO::IsDirectoryExist(tempPath))
                        CFileIO::CreateDirX(tempPath);
                    auto newPath =CFileIO::CombiningTwoPaths(tempPath, appName);
                    setLogPath(newPath);
                    return newPath;
                }
                catch (...)
                {
                }
            }
        }

#if defined(_WIN32) || defined(WIN32) || defined(_WIN64) || defined(WIN64)
        QString tempPath("c:\\log\\");
#else
        QString tempPath("/tmp/");
#endif

        tempPath = CFileIO::CombiningTwoPaths(tempPath, orgName);
        tempPath = CFileIO::CombiningTwoPaths(tempPath, appName);

        QString testDir = CFileIO::GetPathWithoutFilename2(tempPath);
        if (!CFileIO::IsDirectoryExist(testDir))
            CFileIO::CreateDirX(testDir);

        if (!CFileIO::IsFileExist(tempPath))
            setLogPath(tempPath);

        return tempPath;
    }

    void setLogPath(const QString& path)
    {
        // path = "z" + path;
        if (!CFileIO::IsFileExist(path))
        {
            std::ofstream ofs(path.toStdString().c_str());
            if (!ofs.is_open())
                throw std::runtime_error("Failed create log");

            ofs.close();
        }
        QSettings settings(QCoreApplication::organizationName(),QCoreApplication::applicationName());
        settings.sync();
        settings.setValue(CONFIG_LOG_NAME, path);
    }

    void CLogger::Flush()
    {
        m_io->Flush(true);
    }

    QString copyLogTo(const QString& destPath)
    {
        std::lock_guard<std::mutex> mlock(m_mutexLog);
        QString srcPath;
        std::string err;
        try
        {
            srcPath = getLogPath();
            std::ifstream  src;
            std::ofstream  dst;

            src.open(srcPath.toStdString(), std::ios::binary);
            if (!src.is_open())
            {
                throw  std::runtime_error("Source error " +app_error::GetErrorString(errno));
            }

            dst.open(destPath.toStdString(), std::ios::binary);
            if (!dst.is_open())
            {
                throw  std::runtime_error("Export error " +app_error::GetErrorString(errno));
            }

            src.exceptions(dst.exceptions() | std::ios::badbit |std::ios::failbit);
            src.exceptions(src.exceptions() | std::ios::badbit |std::ios::failbit);


            dst << src.rdbuf();
            src.close();
            dst.close();
            return "";
        }
        catch (const std::exception& ex)
        {
            err = ex.what();
        }
        catch (...)
        {
            err = "Unexpected exception";
        }
        return "Failed copy file: " + QString::fromStdString(err) +"\n[" + srcPath + "]\n[" + destPath + "]";

    }

    void clearLog()
    {
        std::lock_guard<std::mutex> mlock(m_mutexLog);
        CloseLogFile();
        try
        {
            OpenLogFile();
        }
        catch ()//const std::exception &e
        {
            //qDebug() << "Error OpenLogFile();" << e.what();
            exit(-20);
        }
    }

    void OpenLogFile()
    {
        if (!m_io)
        {
            auto path = getLogPath();

            if (m_logFileCount > 0)
                CFileIO::DeleteFileX(path + "." +QString::number(m_logFileCount));

            for (int32_t index = m_logFileCount - 1; index > 0;index--)
            {
                auto tmpOld = path + "." +QString::number(index);
                auto tmpNew = path + "." + QString::number(index+ 1);
                CFileIO::RenameFileX(tmpOld, tmpNew);
            }

            auto tmpNew = path + "." + QString::number(1);
            CFileIO::RenameFileX(path, tmpNew);

            m_io = new CFileIO(path, CInputOutput::writer, true);

#if defined(_WIN32) || defined(WIN32) || defined(_WIN64) || defined(WIN64)
            const auto infostring = appv.toStdWString();
            auto sz = sizeof(infostring[0]);
            //static_assert ((sz == 2), "ERROR");

            uint8_t chA = 0xFF;
            m_io->Write(&chA, sizeof(chA), false);
            uint8_t chB = 0xFE;
            m_io->Write(&chB, sizeof(chB), false);

#else
            const auto infostring = appv.toStdString();
            auto sz = sizeof(infostring[0]);
            static_assert ((sizeof(infostring[0]) == 1), "ERROR");

#endif

            m_io->Write(infostring.c_str(), infostring.length() *sz, false);
            m_io->Flush(true);
        }
    }

    void CloseLogFile()
    {
        auto tmp = m_io;
        m_io = nullptr;
        delete tmp;
    }

    void printTest()
    {
        auto resA = CLogger::Instance().FormatString("%d", 0L);
        std::wcout << resA.c_str() << std::endl;
        auto resW = CLogger::Instance().FormatString(L"%d", 0L);
        std::wcout << resW.c_str() << std::endl;

        //auto resA = FormatStringX<std::vsnprintf,std::vfprintf>("%d", 0L);
        //auto resW = FormatStringX<std::vswprintf,std::vfwprintf, std::wstring>(L"%d", 0L);

        //const auto& size = DummyPrintX(m_dummyFile, baseFmt.c_str(), args...);
        //if (size > 0){
        //auto xres = BufferPrintX(static_cast<size_t>(size), baseFmt.c_str(), args...);
        //for (auto& item : xres)
        //    if (item == L';')
        //        item = L':';
        //    logstr.append();
        //}

    }

    int CLogger::DummyPrintX(FILE* const _Stream, const char* const _Format, ...) {
        va_list args;
        va_start(args, _Format);
        auto ret = std::vfprintf(_Stream, _Format, args);
        va_end(args);
        return ret;
    }

    int CLogger::DummyPrintX(FILE* const _Stream, const wchar_t* const _Format, ...) {
        va_list args;
        va_start(args, _Format);
        auto ret = std::vfwprintf(_Stream, _Format, args);
        va_end(args);
        return ret;
    }

    std::string CLogger::BufferPrintX(size_t size, const char* const _Format, ...) {
        std::vector<char> buffer(size + 2, 0);
        va_list args;
        va_start(args, _Format);
        auto res = std::vsnprintf(buffer.data(), buffer.size() - 1, _Format, args);
        va_end(args);
        if (res == -1)
            return std::string();
        return buffer.data();
    }

    std::wstring CLogger::BufferPrintX(size_t size, const wchar_t* const _Format, ...) {
        std::vector<wchar_t> buffer(size + 2, 0);
        va_list args;
        va_start(args, _Format);
        auto res = std::vswprintf(buffer.data(), buffer.size() - 1, _Format, args);
        va_end(args);
        if (res == -1)
            return std::wstring();
        return buffer.data();
    }


 
*/


/*
* 
template<typename QEnum>
std::string QtEnumToString(const QEnum value)
{
    return std::string(QMetaEnum::fromType<QEnum>().valueToKey(value));
}

using typ = typename std::remove_const<std::remove_pointer<decltype(_Format)>::type>::type;

auto t1 = std::basic_string<typename decltype(a1)::value_type>();
auto t2 = std::basic_string<decltype(a2)::value_type>();
auto t3 = std::basic_string<typename decltype(a3)>();
auto t4 = std::basic_string<decltype(a4)::type>();
auto t5 = std::basic_string<typeof(a5)>();

auto t6 = std::basic_string<decltype(a6)::value_type>();
auto t7 = std::basic_string<typename decltype(a7)>();
auto t8 = std::basic_string<decltype(a8)::type>();

constexpr auto isWChar1 = (std::is_same<T, std::wstring>::value) || std::is_convertible_v<T, wchar_t const*>;
constexpr auto isChar1 = ((std::is_same<T, std::string>::value) || std::is_convertible_v<T, char const*>);
using xType = typename std::conditional<isChar1,  char, wchar_t>::type;

val type char*
val type wchar_t*
auto retString = std::basic_string<decltype(val)>();

val type std::string
val type std::wstring
auto retString = std::basic_string<typename decltype(val)::value_type>();

#ifdef _DEBUG
        constexpr auto isWChar1 = (std::is_same<T, std::wstring>::value) || std::is_convertible_v<T, wchar_t const*>;
        // runtime check
        const auto isChar2 = (typeid(T) == typeid(std::string)) || (typeid(T) == typeid(const char*)) || (typeid(T) == typeid(char*));
        const auto isWChar2 = (typeid(T) == typeid(std::wstring)) || (typeid(T) == typeid(const wchar_t*)) || (typeid(T) == typeid(wchar_t*));
        _ASSERT(isChar2 != isWChar2);
        _ASSERT(isChar1 == isChar2);
        _ASSERT(isWChar1 == isWChar2);
#endif // _DEBUG*/


/*

//int CLogger::DummyPrintX(FILE* const _Stream, const char* const _Format, ...) {
//    va_list args;
//    va_start(args, _Format);
//    auto ret = std::vfprintf(_Stream, _Format, args);
//    va_end(args);
//    return ret;
//}

//int CLogger::DummyPrintX(FILE* const _Stream, const wchar_t* const _Format, ...) {
//    va_list args;
//    va_start(args, _Format);
//    auto ret = std::vfwprintf(_Stream, _Format, args);
//    va_end(args);
//    return ret;
//}

template<typename T, typename...Targs>
int printToFile(FILE* const _Stream, T const* const _Format, Targs...args) {
		//auto size = std::vfprintf(m_dummyFile, _Format, args);
		//auto size = std::vfwprintf(m_dummyFile, _Format, args);
    return 0;
};

template<typename T, typename...Targs>
int printToBuffer(T* buffer, int bufferSize, T const* const _Format, Targs...args) {
		//auto res = std::vsnprintf(buffer.data(), buffer.size() - 1, _Format, args);
		//auto res = std::vswprintf(buffer.data(), buffer.size() - 1, _Format, args);
    return bufferSize;
};

template<typename T >
inline auto FormatStringX(T _Format, ...)
{
	std::vector<typename std::conditional<(((std::is_same<T, std::string>::value) || std::is_convertible<T, const char*>::value)),
        char,
        wchar_t>::type > buffer(2, 0);

	{
		va_list args;
		va_start(args, _Format);
        CDummyXFile x;
		auto size = printToFile(x.get(), _Format, args);
		va_end(args);
		if (size < 1)
			return buffer.data();
		buffer.resize(2Ui64 + size, 0);
	}
	{
		va_list args;
		va_start(args, _Format);
		auto res = printToBuffer(buffer.data(), static_cast<int>(buffer.size() - 1), _Format, args);
		va_end(args);
		if (res < 1)
			return buffer.data();
	}
	return buffer.data();
}
*/

/*
void FormatStringTestTmp()
{
    const int64_t tst64_t = 5634563456;
    FormatStringX(L"[VAL [" PRF_W_STRING "] [%" PRId64  "]]", L"test int64_t", tst64_t);

    // declare and initialize signed variables with max values
    int8_t i8_max = INT8_MAX;  // 127
    int16_t i16_max = INT16_MAX; // 32767
    int32_t i32_max = INT32_MAX; // 2147483647
    int64_t i64_max = INT64_MAX; // 9223372036854775807

    // declare and initialize signed variables with min values
    int8_t i8_min = INT8_MIN;  // -128
    int16_t i16_min = INT16_MIN; // -32768
    int32_t i32_min = INT32_MIN; // -2147483648
    int64_t i64_min = INT64_MIN; // -9223372036854775808

    // declare and initialize unsigned variables with max values
    uint8_t u8_max = UINT8_MAX;  // 255
    uint16_t u16_max = UINT16_MAX; // 65535
    uint32_t u32_max = UINT32_MAX; // 4294967295
    uint64_t u64_max = UINT64_MAX; // 18446744073709551615

    {
        auto strParamA = "some1234teststring";
        auto strParamA2 = "End teststring";

        auto srcA1 =
            "[" PRF_CH_STRING "==some1234teststring] "
            "[%" PRId8 "==127] "
            "[%" PRId16 "==32767] "
            "[%" PRId32 "==2147483647] "
            "[%" PRId64 "==9223372036854775807] "

            "[%" PRId8 "==-128] "
            "[%" PRId16 "==-32768] "
            "[%" PRId32 "==2147483648] "
            "[%" PRId64 "==-9223372036854775808] "

            "[%" PRIu8 "==255] "
            "[%" PRIu16 "==65535] "
            "[%" PRIu32 "==4294967295] "
            "[%" PRIu64 "==18446744073709551615] "
            "[" PRF_CH_STRING "==End teststring]"
            ;
        auto resA1 = std::string(
            "[some1234teststring==some1234teststring] "
            "[127==127] "
            "[32767==32767] "
            "[2147483647==2147483647] "
            "[9223372036854775807==9223372036854775807] "
            "[-128==-128] "
            "[-32768==-32768] "
            "[-2147483648==2147483648] "
            "[-9223372036854775808==-9223372036854775808] "
            "[255==255] "
            "[65535==65535] "
            "[4294967295==4294967295] "
            "[18446744073709551615==18446744073709551615] "
            "[End teststring==End teststring]");

        auto tst1 = FormatStringX(srcA1,
            strParamA,
            i8_max,  // 127
            i16_max, // 32767
            i32_max, // 2147483647
            i64_max, // 9223372036854775807

            // declare and initialize signed variables with min values
            i8_min,  // -128
            i16_min, // -32768
            i32_min, // -2147483648
            i64_min, // -9223372036854775808

            // declare and initialize unsigned variables with max values
            u8_max,  // 255
            u16_max, // 65535
            u32_max, // 4294967295
            u64_max,  // 18446744073709551615
            strParamA2
        );

        _ASSERT(tst1 == resA1);
        UNREFERENCED_PARAMETER_LOG(tst1);
        UNREFERENCED_PARAMETER_LOG(resA1);
    }
    {
        auto strParamW = L"some1234teststring";
        auto strParamW2 = L"End teststring";
        auto srcW1 =
            L"[" PRF_W_STRING "==some1234teststring] "
            "[%" PRId8 "==127] "
            "[%" PRId16 "==32767] "
            "[%" PRId32 "==2147483647] "
            "[%" PRId64 "==9223372036854775807] "

            "[%" PRId8 "==-128] "
            "[%" PRId16 "==-32768] "
            "[%" PRId32 "==2147483648] "
            "[%" PRId64 "==-9223372036854775808] "

            "[%" PRIu8 "==255] "
            "[%" PRIu16 "==65535] "
            "[%" PRIu32 "==4294967295] "
            "[%" PRIu64 "==18446744073709551615] "
            "[" PRF_W_STRING "==End teststring]"
            ;

        auto resW1 = std::wstring(
            L"[some1234teststring==some1234teststring] "
            L"[127==127] "
            L"[32767==32767] "
            L"[2147483647==2147483647] "
            L"[9223372036854775807==9223372036854775807] "
            L"[-128==-128] "
            L"[-32768==-32768] "
            L"[-2147483648==2147483648] "
            L"[-9223372036854775808==-9223372036854775808] "
            L"[255==255] "
            L"[65535==65535] "
            L"[4294967295==4294967295] "
            L"[18446744073709551615==18446744073709551615] "
            L"[End teststring==End teststring]");

        auto tst1 = FormatStringX(srcW1,
            strParamW,
            i8_max,  // 127
            i16_max, // 32767
            i32_max, // 2147483647
            i64_max, // 9223372036854775807

            // declare and initialize signed variables with min values
            i8_min,  // -128
            i16_min, // -32768
            i32_min, // -2147483648
            i64_min, // -9223372036854775808

            // declare and initialize unsigned variables with max values
            u8_max,  // 255
            u16_max, // 65535
            u32_max, // 4294967295
            u64_max,  // 18446744073709551615
            strParamW2
        );

        _ASSERT(tst1 == resW1);
        UNREFERENCED_PARAMETER_LOG(tst1);
        UNREFERENCED_PARAMETER_LOG(resW1);
    }
    _ASSERT(FormatStringX(L"[VAL [" PRF_W_STRING "] [%" PRId8  "]]", L"test -128", -128)
        == std::wstring(L"[VAL [test -128] [-128]]"));

    _ASSERT(FormatStringX(L"[VAL [" PRF_W_STRING "] [%" PRId16 "]]", L"test -32767", -32767)
        == std::wstring(L"[VAL [test -32767] [-32767]]"));

    _ASSERT(FormatStringX(L"[VAL [" PRF_W_STRING "] [%" PRId32 "]]", L"test -2147483647", -2147483647)
        == std::wstring(L"[VAL [test -2147483647] [-2147483647]]"));

    _ASSERT(FormatStringX(L"[VAL [" PRF_W_STRING "] [%" PRIu8  "]]", L"test 255", 255)
        == std::wstring(L"[VAL [test 255] [255]]"));

    _ASSERT(FormatStringX(L"[VAL [" PRF_W_STRING "] [%" PRIu16 "]]", L"test 65535", 65535)
        == std::wstring(L"[VAL [test 65535] [65535]]"));

    _ASSERT(FormatStringX(L"[VAL [" PRF_W_STRING "] [%" PRIu32 "]]", L"test 4294967295", 4294967295)
        == std::wstring(L"[VAL [test 4294967295] [4294967295]]"));

    _ASSERT(FormatStringX("[%" PRIu64 "][" PRF_CH_STRING "]", 33ull, "33")
        == std::string("[33][33]"));

    _ASSERT(FormatStringX(L"[%" PRId64 "][" PRF_W_STRING "]", 36ll, L"36")
        == std::wstring(L"[36][36]"));

    _ASSERT(FormatStringX("[" PRF_CH_STRING "][%" PRId64 "]", "9223372036854775807", 0x7FFFFFFFFFFFFFFFll)
        == std::string("[9223372036854775807][9223372036854775807]"));

    _ASSERT(FormatStringX("[%" PRId64 "][" PRF_CH_STRING "]", 0x7FFFFFFFFFFFFFFFll, "9223372036854775807")
        == std::string("[9223372036854775807][9223372036854775807]"));

    _ASSERT(FormatStringX(L"[" PRF_W_STRING L"][%" TOWSTRING(PRId64) L"]", L"9223372036854775807", 0x7FFFFFFFFFFFFFFFll)
        == std::wstring(L"[9223372036854775807][9223372036854775807]"));

    _ASSERT(FormatStringX(L"[%" TOWSTRING(PRId64) L"][" PRF_W_STRING L"]", 0x7FFFFFFFFFFFFFFFll, L"9223372036854775807")
        == std::wstring(L"[9223372036854775807][9223372036854775807]"));

}


*/



//////////////////////////////////////////////////////////////////////
#if 0

std::string FormatStringB(FILE* const stream, _Printf_format_string_ const char* const _Format, ...)
{
    std::vector<typename std::remove_const<std::remove_pointer<decltype(_Format)>::type>::type> buffer(2, 0);
    {
        va_list argList;
        va_start(argList, _Format);
        auto size = std::vfprintf(stream, _Format, argList);
        va_end(argList);
        if (size < 1)
            return buffer.data();
        buffer.resize(2ULL + size, 0);
    }
    {
        va_list argList;
        va_start(argList, _Format);
        auto size = std::vsnprintf(buffer.data(), (buffer.size() - 1), _Format, argList);
        va_end(argList);
        if (size < 1)
            return buffer.data();
    }
    return buffer.data();
}

std::wstring FormatStringB(FILE* const stream, _Printf_format_string_ wchar_t const* const _Format, ...)
{
    std::vector<typename std::remove_const<std::remove_pointer<decltype(_Format)>::type>::type> buffer(2, 0);
    {
        va_list argList;
        va_start(argList, _Format);
        auto size = std::vfwprintf(stream, _Format, argList);
        va_end(argList);
        if (size < 1)
            return buffer.data();
        buffer.resize(2ULL + size, 0);
    }
    {
        va_list argList;
        va_start(argList, _Format);
        auto size = std::vswprintf(buffer.data(), (buffer.size() - 1), _Format, argList);
        va_end(argList);
        if (size < 1)
            return buffer.data();
    }
    return buffer.data();
}

template<typename...Targ>
std::string FormatStringY(_Printf_format_string_ const char* const _Format, Targ...arg) FATTR(1, 2) {
    helpers::CDummyXFile xf;
    return FormatStringB(xf.GetFilePtr(), _Format, arg...);
};

template<typename...Targ>
std::wstring FormatStringY(_Printf_format_string_ const wchar_t* const _Format, Targ...arg) {
    helpers::CDummyXFile xf;
    return FormatStringB(xf.GetFilePtr(), _Format, arg...);
};

template<typename...Targ>
std::string FormatStringY(FILE* const stream, _Printf_format_string_ const char* const _Format, Targ...arg) FATTR(2, 3) {
    return FormatStringB(stream, _Format, arg...);
};

template<typename...Targ>
std::wstring FormatStringY(FILE* const stream, _Printf_format_string_ const wchar_t* const _Format, Targ...arg) {
    return FormatStringB(stream, _Format, arg...);
};

void instantation() {
    {
        helpers::CDummyXFile xf;
        FormatStringY(xf.GetFilePtr(), "%d%d", 778, 888);
    }
    {
        helpers::CDummyXFile xf;
        FormatStringY(xf.GetFilePtr(), L"%d%d", 778, 888);
    }
    {
        FormatStringY("%d%d", 778, 888);
    }
    {
        FormatStringY(L"%d%d", 778, 888);
    }

}

//std::string FormatStringT(_Printf_format_string_ const char * const _Format, ...)
//{
//    std::vector<typename std::remove_const<std::remove_pointer<decltype(_Format)>::type>::type> buffer(2,0);
//    {
//        helpers::CDummyXFile xf;
//        va_list argList;
//        va_start(argList, _Format);
//        auto size = std::vfprintf(xf.GetFilePtr(), _Format, argList);
//        va_end(argList);
//        if (size < 1)
//            return buffer.data();
//        buffer.resize(2ULL + size, 0);
//    }
//    {
//        va_list argList;
//        va_start(argList, _Format);
//        auto res = std::vsnprintf(buffer.data(), buffer.size() - 1, _Format, argList);
//        va_end(argList);
//        if (res < 1)
//            return buffer.data();
//    }
//    return buffer.data();
//};
//
//std::wstring FormatStringT(_Printf_format_string_ wchar_t const* const _Format, ...)
//{
//    std::vector<typename std::remove_const<std::remove_pointer<decltype(_Format)>::type>::type> buffer(2,0);
//    helpers::CDummyXFile xf;
//    {
//        va_list args;
//        va_start(args, _Format);
//        auto size = std::vfwprintf(xf.GetFilePtr(), _Format, args);
//        va_end(args);
//        if (size < 1)
//            return buffer.data();
//        buffer.resize(2ULL + size, 0);
//    }
//    {
//        va_list args;
//        va_start(args, _Format);
//        auto res = std::vswprintf(buffer.data(), buffer.size() - 1, _Format, args);
//        va_end(args);
//        if (res < 1)
//            return buffer.data();
//    }
//    return buffer.data();
//};


#endif // 0

/*
    class CDummyXFile
    {
    public:
        CDummyXFile(FILE* const file) {
            m_storedFile = file;
        }

        CDummyXFile() {
        }

        ~CDummyXFile() {
            if (m_dummyFile != nullptr)
                fclose(m_dummyFile);
        }

        FILE* GetFilePtr() {

            if (m_storedFile)
                return m_storedFile;

            if (m_dummyFile == nullptr) {
#if defined(WINDOWS_PLATFORM)
                auto ret = fopen_s(&m_dummyFile, "NUL", "wb");
                if (ret != 0) {
                    _ASSERT(0);
                }
#else
                m_dummyFile = fopen("/dev/null", "wb");
                if (m_dummyFile == nullptr) {
                    _ASSERT(0);
                }
#endif
            }

            _ASSERT(m_dummyFile);

            return m_dummyFile;
        }

    private:
        FILE* m_dummyFile = nullptr;
        FILE* m_storedFile = nullptr;

        // Copy constructor
        CDummyXFile(const CDummyXFile& t) = delete;
        // Copy assignment operator
        CDummyXFile& operator = (const CDummyXFile& t) = delete;
    };

*/


/*
    template<typename... TArg>
    int printX(std::vector<char>& buffer, _Printf_format_string_ const char* const szFmt, TArg...args) {
        return std::vsnprintf(buffer.data(), buffer.size() - 1, szFmt, args...);
    }

    template<typename... TArg>
    int printX(std::vector<wchar_t>& buffer, _Printf_format_string_ const wchar_t* const szFmt, TArg...args) {
        return std::vswprintf(buffer.data(), buffer.size() - 1, szFmt, args...);
    }

    template<typename... TArg>
    int dummyPrintX(_Printf_format_string_  const char* const szFmt, TArg...args) {
        return std::vfprintf(m_dummyFile, szFmt, args...);
    }

    template<typename... TArg>
    int dummyPrintX(_Printf_format_string_ const wchar_t* const szFmt, TArg...args) {
        return std::vfwprintf(m_dummyFile, szFmt, args...);
    }

    /// <summary>
    ///
    /// </summary>
    /// <typeparam name="Tstring"></typeparam>
    /// <param name="stream"></param>
    /// <param name="szFmt"></param>
    /// <param name=""></param>
    /// <returns>Formated std::string or std::wstring</returns>
    template<typename Tstring>
    inline auto FormatStringF(_Printf_format_string_ Tstring const szFmt, ...)
    {
        constexpr auto isCharS = std::is_same<Tstring, std::string>::value;
        constexpr auto isCharC = std::is_convertible<Tstring, const char*>::value;
        constexpr auto isChar = isCharS || isCharC;
        using sTyp = typename std::conditional< isChar, char, wchar_t>::type;

        std::basic_string<sTyp> formatString;

        if (szFmt == nullptr)
            return formatString;

        formatString = szFmt;
        if (formatString.length() < 1)
            return formatString;

        const auto* fmtString = formatString.c_str();

        int64_t size = -1;
        {
            va_list argsx;
            va_start(argsx, fmtString);
            size = dummyPrintX(fmtString, argsx);
            va_end(argsx);
        }

        if (size < 1) {
            formatString.clear();
            return formatString;
        }

        std::vector<sTyp> buffer(2ULL + size, 0);

        {
            va_list argsx;
            va_start(argsx, fmtString);
            size = printX(buffer, fmtString, argsx);
            va_end(argsx);
        }

        if (size < 1)
            buffer[0] = 0;

        formatString = buffer.data();
        return formatString;
    };


    //template<typename Tstring, typename ...TArg>
    //static inline auto FormatString(_Printf_format_string_ Tstring const szFmt, TArg...args) {
    //    CDummyXFile x;
    //    return FormatStringF(x.GetFilePtr(), szFmt, args...);
    //}
    //template<typename Tstring, typename...Targ>
    //static auto FormatString(_Printf_format_string_ Tstring const* const szFmt, Targ...args) {
    //    return FormatStringF(nullptr, szFmt, args...);
    //}


*/
