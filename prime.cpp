#
if defined(_WIN32)
#define _CRT_SECURE_NO_WARNINGS#
else
#define _FILE_OFFSET_BITS 64# endif
#include <cstddef>
#include <cstdint>

static int64_t classTable_[21];
#include <memory>
#define new_(...) std::make_shared<__VA_ARGS__> 
#define type_(...) std::shared_ptr<__VA_ARGS__> 
#define newPrim_(...) new __VA_ARGS__
#define delPrim_(x) delete x
#define newPrimArray_(x, ...) new __VA_ARGS__[x]
#define delPrimArray_(x) delete[] x
#define dcast_(...) std::dynamic_pointer_cast<__VA_ARGS__> 
#define addr_(...)(__VA_ARGS__ == nullptr ? 0 : reinterpret_cast<uint64_t> (__VA_ARGS__.get()))
#include <algorithm>
#include <chrono>
#include <cmath>
#include <codecvt>
#include <cstdarg>
#include <cstdio>
#include <cstring>
#include <iomanip>
#include <iostream>
#include <list>
#include <map>
#include <queue>
#include <sstream>
#include <stack>
#include <sys/stat.h>
#include <type_traits>
#include <vector>

namespace
{
    template < typename T > std::size_t bufLen_()
    {
        return 0;
    }

    template < > std::size_t bufLen_<char16_t> ()
    {
        return 1;
    }
}

static int64_t exitCode_ = 0;

struct Class_
{
    Class_(): Y(0 LL) {}

    virtual~Class_() {}

    int64_t Y;
};
template < typename T > struct Array_
{
    Array_(): L(), B() {}

    template < typename...A >
        explicit Array_(A...a)
        {
            L = sizeof...(a);
            B = newPrimArray_(static_cast<std::size_t > (sizeof...(a) + bufLen_<T> ()), T);
            BufferCopy(B, std::forward<A> (a)...);
            if (bufLen_<T> () > 0)
                B[sizeof...(a)] = 0;
        }~Array_()
        {
            delPrimArray_(B);
        }

    void BufferCopy(T *b) {}

    template < typename A, typename...B >
        void BufferCopy(T *b, A h, B...t)
        {
            *b = h;
            BufferCopy(b + 1, std::forward<B> (t)...);
        }

    type_(Array_ < T>) Cat(const type_(Array_ < T>) t)
    {
        type_(Array_ < T>) r = new_(Array_ < T>)();
        r->B = newPrimArray_(static_cast<std::size_t > (L + t->L + bufLen_<T> ()), T);
        for (int64_t i = 0; i < L; i++)
            r->B[i] = B[i];
        for (int64_t i = 0; i<static_cast<int64_t> (t->L + bufLen_<T> ()); i++)
            r->B[L + i] = t->B[i];
        r->L = L + t->L;
        return r;
    }

    int64_t Len()
    {
        return L;
    }

    T &At(int64_t n)
    {
        if (n < 0 || n >= L) throw 0xe9170002;
        return B[n];
    }

    int64_t L;
    T * B;
};
template < typename T > struct List_
{
    List_(): B(), I(B.end()) {}

    int64_t Len()
    {
        return static_cast<int64_t> (B.size());
    }

    std::list<T> B;
    typename std::list<T>::iterator I;
};
template < typename T > struct Stack_
{
    Stack_(): B() {}

    int64_t Len()
    {
        return static_cast<int64_t> (B.size());
    }

    std::stack<T> B;
};
template < typename T > struct Queue_
{
    Queue_(): B() {}

    int64_t Len()
    {
        return static_cast<int64_t> (B.size());
    }

    std::queue<T> B;
};
template < typename T1, typename T2 > struct dictImpl_;
template < typename T1, typename T2 > dictImpl_<T1, T2> *dictAddRec_(dictImpl_<T1, T2> *n, T1 k, T2 v, bool *a);
template < typename T1, typename T2 > dictImpl_<T1, T2> *dictDelRec_(dictImpl_<T1, T2> *n, T1 k, bool *d);
template < typename T1, typename T2 > dictImpl_<T1, T2> *dictCopyRec_(dictImpl_<T1, T2> *n);
template < typename T1, typename T2 > void dictToBinRec_(type_(Array_ < uint8_t>) a, dictImpl_<T1, T2> *d);
template < typename T1, typename T2 > void dictFreeRec_(dictImpl_<T1, T2> *n);
template < typename T1, typename T2 > struct Dict_
{
    Dict_(): L(0 LL), B(nullptr) {}
	~Dict_()
    {
        dictFreeRec_<T1, T2> (B);
    }

    int64_t Len()
    {
        return L;
    }

    void Add(T1 k, T2 v)
    {
        bool a = false;
        B = dictAddRec_<T1, T2> (B, k, v, &a);
        B->R = false;
        if (a)
            L++;
    }

    void Del(T1 k)
    {
        bool d = false;
        B = dictDelRec_<T1, T2> (B, k, &d);
        if (B != nullptr)
            B->R = false;
        if (d)
            L--;
    }

    int64_t L;
    dictImpl_<T1, T2> *B;
};
template < typename T1, typename T2 > struct dictImpl_
{
    dictImpl_(T1 k, T2 v): K(k), V(v), CL(nullptr), CR(nullptr), R(true) {}

    T1 K;
    T2 V;
    dictImpl_ * CL;
    dictImpl_ * CR;
    bool R;
};

#
if _MSC_VER >= 1900 && _MSC_VER < 1922
static std::string utf16ToUtf8_(const std::u16string &s)
{
    const int16_t *p = reinterpret_cast<const int16_t*> (s.data());
    return std::wstring_convert<std::codecvt_utf8_utf16 < int16_t>, int16_t> {}.to_bytes(p, p + s.size());
}

static std::u16string utf8ToUtf16_(const std::string &s)
{
    const auto t = std::wstring_convert<std::codecvt_utf8_utf16 < int16_t>, 
        int16_t > {}.from_bytes(s);
    return std::u16string(reinterpret_cast<const char16_t*> (t.data()), t.size());
}#
else
    static std::string utf16ToUtf8_(const std::u16string &s)
    {
        return std::wstring_convert<std::codecvt_utf8_utf16 < char16_t>, char16_t> {}.to_bytes(s);
    }

static std::u16string utf8ToUtf16_(const std::string &s)
{
    return std::wstring_convert<std::codecvt_utf8_utf16 < char16_t>, char16_t> {}.from_bytes(s);
}#
endif

#
if defined(_WIN32)

# pragma comment(lib, "shlwapi.lib")
#define STRICT
#define _WIN32_DCOM
#include <Windows.h>
#include <Shlwapi.h>
#include <io.h>

const char newLine_[] = { '\r', '\n' };

static void normPath_(char16_t *p, bool d)
{
    if (*p == 0)
        return;
    do {
        if (*p == '\\')
            *
            p = '/';
        p++;
    } while (*p != 0);
    if (d && p[-1] != '/')
    {
        p[0] = '/';
        p[1] = 0;
    }
}

static bool fileExists_(const char16_t *p)
{
    return PathFileExistsW(reinterpret_cast<const wchar_t*> (p)) != 0;
}

static int64_t getCurDir_(char16_t *p)
{
    if (!::GetCurrentDirectoryW(511, reinterpret_cast<wchar_t*> (p)))
        return 0;
    normPath_(p, true);
    return ::wcslen(reinterpret_cast<wchar_t*> (p));
}

static void setCurDir_(const char16_t *p)
{::SetCurrentDirectoryW(reinterpret_cast<const wchar_t*> (p));
}

static bool makeDir_(const char16_t *p)
{
    return ::CreateDirectoryW(reinterpret_cast<const wchar_t*> (p), 0) != 0;
}

static bool delFile_(const char16_t *p)
{
    if (!PathFileExistsW(reinterpret_cast<const wchar_t*> (p)))
        return true;
    return ::DeleteFileW(reinterpret_cast<const wchar_t*> (p)) != 0;
}

static bool copyFile_(const char16_t *d, const char16_t *s)
{
    return ::CopyFileW(reinterpret_cast<const wchar_t*> (s), reinterpret_cast<const wchar_t*> (d), false) != 0;
}

static bool moveFile_(const char16_t *d, const char16_t *s)
{
    return ::MoveFileExW(reinterpret_cast<const wchar_t*> (s), reinterpret_cast<const wchar_t*> (d), MOVEFILE_COPY_ALLOWED | MOVEFILE_WRITE_THROUGH | MOVEFILE_REPLACE_EXISTING) != 0;
}

static int64_t fullPath_(char16_t *p, const char16_t *q)
{
    wchar_t *f;
    if (!::GetFullPathNameW(reinterpret_cast<const wchar_t*> (q), 511, reinterpret_cast<wchar_t*> (p), &f))
        return 0;
    normPath_(p, q[::wcslen(reinterpret_cast<const wchar_t*> (q)) - 1] == '/');
    return ::wcslen(reinterpret_cast<wchar_t*> (p));
}

static void sleep_(int64_t t)
{
    for (int64_t i = 0; i < t / 10000; i++)
        Sleep(10000);
    Sleep(static_cast<DWORD> (t % 10000));
}

#
else

    
#include <unistd.h>

    
#include <fcntl.h>

    
#include <dirent.h>
#define _A_SUBDIR 0x10

const char newLine_[] = { '\n' };

static void normPath_(char *p, bool d)
{
    if (*p == 0)
        return;
    std::size_t l = ::strlen(p);
    if (d && p[l - 1] != '/')
    {
        p[l] = '/';
        p[l + 1] = 0;
    }
}

static bool fileExists_(const char16_t *p)
{
    struct stat b;
    std::u16string s = p;
    const std::string &t = utf16ToUtf8_(s);
    return ::stat(t.c_str(), &b) == 0;
}

static int64_t getCurDir_(char16_t *p)
{
    char b[512];
    if (getcwd(b, 511) == nullptr)
        return 0;
    normPath_(b, true);
    std::string s = b;
    const std::u16string &t = utf8ToUtf16_(s);
    if (t.size() >= 512)
        return 0;
    memcpy(p, t.c_str(), sizeof(char16_t) *(t.size() + 1));
    return static_cast<int64_t> (t.size());
}

static void setCurDir_(const char16_t *p)
{
    std::u16string s = p;
    const std::string &t = utf16ToUtf8_(s);::chdir(t.c_str());
}

static bool makeDir_(const char16_t *p)
{
    std::u16string s = p;
    const std::string &t = utf16ToUtf8_(s);
    return ::mkdir(t.c_str(), S_IRWXU | S_IRWXG | S_IRWXO) == 0;
}

static bool delFile_(const char16_t *p)
{
    struct stat b;
    std::u16string s = p;
    const std::string &t = utf16ToUtf8_(s);
    if (::stat(t.c_str(), &b) != 0)
        return true;
    return ::unlink(t.c_str()) == 0;
}

static bool copyFile_(const char16_t *d, const char16_t *s)
{
    std::u16string s1 = d;
    const std::string &t1 = utf16ToUtf8_(s1);
    std::u16string s2 = s;
    const std::string &t2 = utf16ToUtf8_(s2);
    int i = ::open(t2.c_str(), O_RDONLY);
    if (i < 0)
        return false;
    struct stat f;
    if (::stat(t2.c_str(), &f) != 0)
    {::close(i);
        return false;
    }

    int o = ::open(t1.c_str(), O_CREAT | O_WRONLY | O_TRUNC, f.st_mode);
    if (o < 0)
    {::close(i);
        return false;
    }

    ssize_t r = 1;
    char *buf = newPrimArray_(65536, char);
    while (r > 0 && (r = ::read(i, buf, 65536)) > 0)
    {
        ssize_t z, w = 0;
        do {
            if ((z = ::write(o, buf + w, r - w)) < 0)
            {
                r = z;
                break;
            }

            w += z;
        } while (w < r);
    }

    if (::close(i) < 0)
        r = -1;
    if (::close(o) < 0)
        r = -1;
    delPrimArray_(buf);
    return r >= 0;
}

static bool moveFile_(const char16_t *d, const char16_t *s)
{
    std::u16string s1 = d;
    const std::string &t1 = utf16ToUtf8_(s1);
    std::u16string s2 = s;
    const std::string &t2 = utf16ToUtf8_(s2);
    struct stat b;
    if (::stat(t1.c_str(), &b) == 0)
    {
        if (::unlink(t1.c_str()) != 0)
            return false;
    }

    return ::rename(t2.c_str(), t1.c_str()) == 0;
}

static int64_t fullPath_(char16_t *p, const char16_t *q)
{
    std::u16string s1 = q;
    const std::string &t1 = utf16ToUtf8_(s1);
    char a[512 + 1];
    if (::realpath(t1.c_str(), a) == nullptr)
        return 0;
    normPath_(a, t1[t1.size() - 1] == '/');
    std::string s2 = a;
    const std::u16string &t2 = utf8ToUtf16_(s2);
    if (t2.size() >= 512)
        return 0;
    memcpy(p, t2.c_str(), sizeof(char16_t) *(t2.size() + 1));
    return static_cast<int64_t> (t2.size());
}

static void sleep_(int64_t t)
{
    timespec r = { t / 1000, t % 1000 * 1000000
    };
    nanosleep(&r, nullptr);
}

# endif

static bool fileForEach_(const std::u16string &p, bool r, bool(*f)(type_(Array_ < char16_t>), bool, type_(Class_)), type_(Class_) d)
    {
        if (p.size() > 512)
            return false;#
        if defined(_WIN32)
        WIN32_FIND_DATAW t;
        HANDLE h;#
        else
            dirent * t;
        DIR * h;#
        endif
        bool a = true;
        {#
            if defined(_WIN32)
            wchar_t p3[514];
            memcpy(p3, p.c_str(), sizeof(wchar_t) *static_cast<std::size_t > (p.size()));
            p3[p.size()] = '*';
            p3[p.size() + 1] = 0;
            h = FindFirstFileW(p3, &t);
            if (h == INVALID_HANDLE_VALUE)
                return false;#
            else
                const std::string &p2 = utf16ToUtf8_(p);
            h = ::opendir(p2.c_str());
            if (h == nullptr)
                return false;#
            endif
        }

        {
            type_(Array_ < char16_t>) x = new_(Array_ < char16_t>)();
            x->L = static_cast<int64_t> (p.size());
            x->B = newPrimArray_(static_cast<std::size_t > (p.size() + 1), char16_t);
            memcpy(x->B, p.c_str(), sizeof(char16_t) *static_cast<std::size_t > (p.size() + 1));
            if (!f(x, true, d))
                a = false;
        }

        if (a)
        {#
            if defined(_WIN32)
            do {
                wchar_t *b = t.cFileName;
                if ((t.dwFileAttributes &FILE_ATTRIBUTE_DIRECTORY) == 0)
                {
                    std::size_t l = ::wcslen(b);#
                    else
                        while ((t = readdir(h)) != nullptr)
                        {
                            if ((t->d_type &_A_SUBDIR) == 0)
                            {
                                std::string s = t->d_name;
                                const std::u16string &p2 = utf8ToUtf16_(s);
                                std::size_t l = p2.size();
                                const char16_t *b = p2.c_str();#
                                endif
                                type_(Array_ < char16_t>) p3 = new_(Array_ < char16_t>)();
                                p3->L = p.size() + static_cast<int64_t> (l);
                                p3->B = newPrimArray_(static_cast<std::size_t > (p.size() + l + 1), char16_t);
                                memcpy(p3->B, p.c_str(), sizeof(char16_t) *static_cast<std::size_t > (p.size()));
                                memcpy(p3->B + p.size(), b, sizeof(char16_t) *(l + 1));
                                if (!f(p3, false, d))
                                {
                                    a = false;
                                    break;
                                }
                            }
                            else if (r)
                            {
                                std::u16string p3 = p;#
                                if defined(_WIN32)
                                if (wcscmp(b, L ".") == 0 || wcscmp(b, L "..") == 0)
                                    continue;
                                p3 += reinterpret_cast<const char16_t*> (b);

                                #
                                else
                                    const char *n = t->d_name;
                                if (strcmp(n, ".") == 0 || strcmp(n, "..") == 0)
                                    continue;
                                std::string s = n;
                                const std::u16string &p2 = utf8ToUtf16_(s);
                                p3 += p2;#
                                endif
                                p3 += u '/';
                                if (!fileForEach_(p3, r, f, d))
                                {
                                    a = false;
                                    break;
                                }
                            }
                        }#
                    if defined(_WIN32)
                    while (FindNextFileW(h, &t));#
                    endif
                }#
                if defined(_WIN32)
                FindClose(h);#
                else
                    closedir(h);#
                endif
                return a;
            }

            static bool delDir_(const std::u16string &p)
                {
                    if (p.size() > 512)
                        return false;
                    if (!fileExists_(p.c_str()))
                        return true;#
                    if defined(_WIN32)
                    WIN32_FIND_DATAW t;
                    HANDLE h;#
                    else
                        dirent * t;
                    DIR * h;#
                    endif
                    bool a = true;
                    {#
                        if defined(_WIN32)
                        wchar_t p3[514];
                        memcpy(p3, p.c_str(), sizeof(wchar_t) *static_cast<std::size_t > (p.size()));
                        p3[p.size()] = '*';
                        p3[p.size() + 1] = 0;
                        h = FindFirstFileW(p3, &t);
                        if (h == INVALID_HANDLE_VALUE)
                            return false;#
                        else
                            const std::string &p2 = utf16ToUtf8_(p);
                        h = ::opendir(p2.c_str());
                        if (h == nullptr)
                            return false;#
                        endif
                    }#
                    if defined(_WIN32)
                    do {
                        if ((t.dwFileAttributes &FILE_ATTRIBUTE_DIRECTORY) == 0)
                        {
                            std::u16string b = p;
                            b += reinterpret_cast<const char16_t*> (t.cFileName);#
                            else
                                while ((t = readdir(h)) != nullptr)
                                {
                                    if ((t->d_type &_A_SUBDIR) == 0)
                                    {
                                        std::string n = t->d_name;
                                        const std::u16string &n2 = utf8ToUtf16_(n);
                                        std::u16string b = p;
                                        b += n2;#
                                        endif
                                        if (!delFile_(b.c_str()))
                                        {
                                            a = false;
                                            break;
                                        }
                                    }
                                    else
                                    {
                                        std::u16string p2 = p;#
                                        if defined(_WIN32)
                                        const wchar_t *n = t.cFileName;
                                        if (wcscmp(n, L ".") == 0 || wcscmp(n, L "..") == 0)
                                            continue;
                                        p2 += reinterpret_cast<const char16_t*> (n);#
                                        else
                                            const char *n = t->d_name;
                                        if (strcmp(n, ".") == 0 || strcmp(n, "..") == 0)
                                            continue;
                                        std::string s = n;
                                        const std::u16string &n2 = utf8ToUtf16_(s);
                                        p2 += n2;#
                                        endif
                                        p2 += u "/";
                                        if (!delDir_(p2))
                                        {
                                            a = false;
                                            break;
                                        }
                                    }
                                }#
                            if defined(_WIN32)
                            while (FindNextFileW(h, &t));
                            FindClose(h);#
                            else
                                closedir(h);#
                            endif
                            if (a)
                            {#
                                if defined(_WIN32)
                                a = ::RemoveDirectoryW(reinterpret_cast<const wchar_t*> (p.c_str())) != 0;#
                                else
                                    const std::string &p2 = utf16ToUtf8_(p);
                                a = ::rmdir(p2.c_str()) == 0;#
                                endif
                            }

                            return a;
                        }

                        static bool copyDir_(const std::u16string &d, const std::u16string &s)
                            {
                                if (s.size() > 512)
                                    return false;#
                                if defined(_WIN32)
                                WIN32_FIND_DATAW t;
                                HANDLE h;#
                                else
                                    dirent * t;
                                DIR * h;#
                                endif
                                bool a = true;
                                {#
                                    if defined(_WIN32)
                                    wchar_t p3[514];
                                    memcpy(p3, s.c_str(), sizeof(wchar_t) *static_cast<std::size_t > (s.size()));
                                    p3[s.size()] = '*';
                                    p3[s.size() + 1] = 0;
                                    h = FindFirstFileW(p3, &t);
                                    if (h == INVALID_HANDLE_VALUE)
                                        return false;#
                                    else
                                        const std::string &p2 = utf16ToUtf8_(s);
                                    h = ::opendir(p2.c_str());
                                    if (h == nullptr)
                                        return false;#
                                    endif
                                }

                                if (!fileExists_(d.c_str()))
                                {
                                    if (!makeDir_(d.c_str()))
                                        a = false;
                                }

                                if (a)
                                {#
                                    if defined(_WIN32)
                                    do {
                                        if ((t.dwFileAttributes &FILE_ATTRIBUTE_DIRECTORY) == 0)
                                        {
                                            std::u16string s2 = s;
                                            s2 += reinterpret_cast<const char16_t*> (t.cFileName);
                                            std::u16string d2 = d;
                                            d2 += reinterpret_cast<const char16_t*> (t.cFileName);#
                                            else
                                                while ((t = readdir(h)) != nullptr)
                                                {
                                                    if ((t->d_type &_A_SUBDIR) == 0)
                                                    {
                                                        std::string n = t->d_name;
                                                        const std::u16string &n2 = utf8ToUtf16_(n);
                                                        std::u16string s2 = s;
                                                        s2 += n2;
                                                        std::u16string d2 = d;
                                                        d2 += n2;#
                                                        endif
                                                        if (!copyFile_(d2.c_str(), s2.c_str()))
                                                        {
                                                            a = false;
                                                            break;
                                                        }
                                                    }
                                                    else
                                                    {
                                                        std::u16string s2 = s;
                                                        std::u16string d2 = d;#
                                                        if defined(_WIN32)
                                                        const wchar_t *n = t.cFileName;
                                                        if (wcscmp(n, L ".") == 0 || wcscmp(n, L "..") == 0)
                                                            continue;
                                                        s2 += reinterpret_cast<const char16_t*> (n);
                                                        d2 += reinterpret_cast<const char16_t*> (n);#
                                                        else
                                                            const char *n = t->d_name;
                                                        if (strcmp(n, ".") == 0 || strcmp(n, "..") == 0)
                                                            continue;
                                                        std::string t = n;
                                                        const std::u16string &n2 = utf8ToUtf16_(t);
                                                        s2 += n2;
                                                        d2 += n2;#
                                                        endif
                                                        s2 += u "/";
                                                        d2 += u "/";
                                                        if (!copyDir_(d2, s2))
                                                        {
                                                            a = false;
                                                            break;
                                                        }
                                                    }
                                                }#
                                            if defined(_WIN32)
                                            while (FindNextFileW(h, &t));#
                                            endif
                                        }#
                                        if defined(_WIN32)
                                        FindClose(h);#
                                        else
                                            closedir(h);#
                                        endif
                                        return a;
                                    }

                                    static bool moveDir_(const char16_t *d, const char16_t *s)
                                    {#
                                        if defined(_WIN32)
                                        if (::MoveFileExW(reinterpret_cast<const wchar_t*> (s), reinterpret_cast<const wchar_t*> (d), MOVEFILE_COPY_ALLOWED | MOVEFILE_WRITE_THROUGH | MOVEFILE_REPLACE_EXISTING))
                                            return true;#
                                        endif
                                        std::u16string d2 = d;
                                        std::u16string s2 = s;
                                        if (!copyDir_(d2, s2))
                                            return false;
                                        if (!delDir_(s2))
                                            return false;
                                        return true;
                                    }

                                    static bool makeDir2_(const char16_t *p)
                                    {
                                        char16_t b[512];
                                        int64_t l = fullPath_(b, p);
                                        if (l == 0)
                                            return false;
                                        const char16_t *q = b;
                                        while (*q != 0)
                                        {
                                            while (*q != '/')
                                                q++;
                                            char16_t a[512];
                                            memcpy(a, b, sizeof(char16_t) *static_cast<std::size_t > (q - b + 1));
                                            a[q - b + 1] = 0;
                                            if (!fileExists_(a))
                                            {
                                                if (!makeDir_(a))
                                                    return false;
                                            }

                                            q++;
                                        }

                                        return true;
                                    }

                                    template < typename T > struct newArraysRec_
                                    {
                                        T operator()()
                                        {
                                            throw 0;
                                        }

                                        template < typename A, typename...B > T operator()(A h, B...t)
                                        {
                                            throw 0;
                                        }
                                    };
                                    template < typename T > struct newArraysRec_<type_(Array_ < T>) >
                                    {
                                        type_(Array_ < T>) operator()()
                                        {
                                            throw 0;
                                        }

                                        template < typename A, typename...C > type_(Array_ < T>) operator()(A h, C...t)
                                        {
                                            if (h < 0) throw 0xe917000b;
                                            type_(Array_ < T>) r = new_(Array_ < T>)();
                                            r->L = h;
                                            r->B = newPrimArray_(static_cast<std::size_t > (h + bufLen_<T> ()), T);
                                            if (sizeof...(t) == 0)
                                                memset(r->B, 0, sizeof(T) *static_cast<std::size_t > (h + bufLen_<T> ()));
                                            else
                                            {
                                                for (int64_t i = 0; i < h; i++)
                                                    r->B[i] = newArraysRec_<T> ()(std::forward<C> (t)...);
                                            }

                                            return r;
                                        }
                                    };
                                    template < typename T, typename...A > T newArrays_(A...a)
                                    {
                                        if (sizeof...(a) > 64)
                                            return nullptr;
                                        return newArraysRec_<T> ()(std::forward<A> (a)...);
                                    }

                                    template < typename T>
                                        type_(Array_ < T>) newArrayBin_(int64_t l, const void *d)
                                        {
                                            type_(Array_ < T>) r = new_(Array_ < T>)();
                                            r->L = l;
                                            r->B = newPrimArray_(static_cast<std::size_t > (l) + bufLen_<T> (), T);
                                            memcpy(r->B, d, sizeof(T) *static_cast<std::size_t > (l));
                                            if (bufLen_<T> () > 0)
                                                r->B[l] = 0;
                                            return r;
                                        }

                                    template < typename T > type_(Array_ < T>) toArray_(type_(List_ < T>) l)
                                    {
                                        type_(Array_ < T>) a = new_(Array_ < T>)();
                                        a->L = l->Len();
                                        a->B = newPrimArray_(static_cast<std::size_t > (a->L) + bufLen_<T> (), T);
                                        int64_t i = 0;
                                        for (auto &e: l->B)
                                        {
                                            a->B[i] = e;
                                            i++;
                                        }

                                        if (bufLen_<T> () > 0)
                                            a->B[a->L] = 0;
                                        return a;
                                    }

                                    template < typename T > struct copy_ {};
                                    template < typename T > struct copy_<type_(Array_ < T>) >
                                    {
                                        type_(Array_ < T>) operator()(type_(Array_ < T>) t)
                                        {
                                            if (t == nullptr)
                                                return nullptr;
                                            type_(Array_ < T>) r = new_(Array_ < T>)();
                                            r->L = t->L;
                                            r->B = newPrimArray_(static_cast<std::size_t > (t->L) + bufLen_<T> (), T);
                                            for (int64_t i = 0; i < t->L; i++)
                                                r->B[i] = copy_<T> ()(t->B[i]);
                                            if (bufLen_<T> () > 0)
                                                r->B[r->L] = 0;
                                            return r;
                                        }
                                    };
                                    template < typename T > struct copy_<type_(List_ < T>) >
                                    {
                                        type_(List_ < T>) operator()(type_(List_ < T>) t)
                                        {
                                            if (t == nullptr)
                                                return nullptr;
                                            type_(List_ < T>) r = new_(List_ < T>)();
                                            for (auto i = t->B.begin(); i != t->B.end(); ++i)
                                            {
                                                r->B.push_back(copy_<T> ()(*i));
                                                if (i == t->I)
                                                {
                                                    auto e = r->B.end();
                                                    --e;
                                                    r->I = e;
                                                }
                                            }

                                            return r;
                                        }
                                    };
                                    template < typename T > struct copy_<type_(Stack_ < T>) >
                                    {
                                        type_(Stack_ < T>) operator()(type_(Stack_ < T>) t)
                                        {
                                            if (t == nullptr)
                                                return nullptr;
                                            type_(Stack_ < T>) r = new_(Stack_ < T>)();
                                            std::stack<T> b;
                                            while (!t->B.empty())
                                            {
                                                b.push(t->B.top());
                                                t->B.pop();
                                            }

                                            while (!b.empty())
                                            {
                                                r->B.push(copy_<T> ()(b.top()));
                                                t->B.push(b.top());
                                                b.pop();
                                            }

                                            return r;
                                        }
                                    };
                                    template < typename T > struct copy_<type_(Queue_ < T>) >
                                    {
                                        type_(Queue_ < T>) operator()(type_(Queue_ < T>) t)
                                        {
                                            if (t == nullptr)
                                                return nullptr;
                                            type_(Queue_ < T>) r = new_(Queue_ < T>)();
                                            std::queue<T> b;
                                            while (!t->B.empty())
                                            {
                                                b.push(t->B.front());
                                                t->B.pop();
                                            }

                                            while (!b.empty())
                                            {
                                                r->B.push(copy_<T> ()(b.front()));
                                                t->B.push(b.front());
                                                b.pop();
                                            }

                                            return r;
                                        }
                                    };
                                    template < typename T1, typename T2 > struct copy_<type_(Dict_<T1, T2>) >
                                    {
                                        type_(Dict_<T1, T2>) operator()(type_(Dict_<T1, T2>) t)
                                        {
                                            if (t == nullptr)
                                                return nullptr;
                                            type_(Dict_<T1, T2>) r = new_(Dict_<T1, T2>)();
                                            r->L = t->L;
                                            r->B = dictCopyRec_<T1, T2> (t->B);
                                            return r;
                                        }
                                    };
                                    template < typename T > struct copy_ < type_(T) >
                                    {
                                        type_(T) operator()(type_(T) t)
                                        {
                                            if (std::is_class<T>::value)
                                            {
                                                if (t == nullptr)
                                                    return nullptr;
                                                return dcast_(T)(reinterpret_cast< type_(Class_)(*)(type_(Class_)) > (classTable_[t->Y + 4])(t));
                                            }
                                            else
                                                return t;
                                        }
                                    };
                                    template < > struct copy_ < int64_t>
                                    {
                                        int64_t operator()(int64_t t)
                                        {
                                            return t;
                                        }
                                    };
                                    template < > struct copy_ < char16_t>
                                    {
                                        char16_t operator()(char16_t t)
                                        {
                                            return t;
                                        }
                                    };
                                    template < > struct copy_ < bool>
                                    {
                                        bool operator()(bool t)
                                        {
                                            return t;
                                        }
                                    };
                                    template < > struct copy_ < double>
                                    {
                                        double operator()(double t)
                                        {
                                            return t;
                                        }
                                    };
                                    template < > struct copy_ < uint8_t>
                                    {
                                        uint8_t operator()(uint8_t t)
                                        {
                                            return t;
                                        }
                                    };
                                    template < > struct copy_ < uint16_t>
                                    {
                                        uint16_t operator()(uint16_t t)
                                        {
                                            return t;
                                        }
                                    };
                                    template < > struct copy_ < uint32_t>
                                    {
                                        uint32_t operator()(uint32_t t)
                                        {
                                            return t;
                                        }
                                    };
                                    template < > struct copy_ < uint64_t>
                                    {
                                        uint64_t operator()(uint64_t t)
                                        {
                                            return t;
                                        }
                                    };

                                    static type_(Array_ < char16_t>) toStr_(int64_t v)
                                    {
                                        std::stringstream s;
                                        s << v;
                                        const std::string &t = s.str();
                                        type_(Array_ < char16_t>) r = new_(Array_ < char16_t>)();
                                        r->L = static_cast<int64_t> (t.size());
                                        r->B = newPrimArray_(t.size() + 1, char16_t);
                                        int64_t p = 0;
                                        for (char c: t)
                                            r->B[p++] = c;
                                        r->B[t.size()] = 0;
                                        return r;
                                    }

                                    static type_(Array_ < char16_t>) toStr_(char16_t v)
                                    {
                                        type_(Array_ < char16_t>) r = new_(Array_ < char16_t>)();
                                        r->L = static_cast<int64_t> (1);
                                        r->B = newPrimArray_(2, char16_t);
                                        r->B[0] = v;
                                        r->B[1] = 0;
                                        return r;
                                    }

                                    static type_(Array_ < char16_t>) toStr_(bool v)
                                    {
                                        type_(Array_ < char16_t>) r = new_(Array_ < char16_t>)();
                                        if (v)
                                        {
                                            r->L = static_cast<int64_t> (4);
                                            r->B = newPrimArray_(5, char16_t);
                                            r->B[0] = 't';
                                            r->B[1] = 'r';
                                            r->B[2] = 'u';
                                            r->B[3] = 'e';
                                            r->B[4] = 0;
                                        }
                                        else
                                        {
                                            r->L = static_cast<int64_t> (5);
                                            r->B = newPrimArray_(6, char16_t);
                                            r->B[0] = 'f';
                                            r->B[1] = 'a';
                                            r->B[2] = 'l';
                                            r->B[3] = 's';
                                            r->B[4] = 'e';
                                            r->B[5] = 0;
                                        }

                                        return r;
                                    }

                                    static type_(Array_ < char16_t>) toStr_(double v)
                                    {
                                        std::stringstream s;
                                        s << std::setprecision(16) << v;
                                        const std::string &t = s.str();
                                        type_(Array_ < char16_t>) r = new_(Array_ < char16_t>)();
                                        r->L = static_cast<int64_t> (t.size());
                                        r->B = newPrimArray_(t.size() + 1, char16_t);
                                        int64_t p = 0;
                                        for (char c: t)
                                            r->B[p++] = c;
                                        r->B[t.size()] = 0;
                                        return r;
                                    }

                                    static type_(Array_ < char16_t>) toStr_(uint8_t v)
                                    {
                                        std::stringstream s;
                                        s << "0x" << std::uppercase << std::setfill('0') << std::setw(2) <<std::hex <<static_cast<uint16_t> (v);
                                        const std::string &t = s.str();
                                        type_(Array_ < char16_t>) r = new_(Array_ < char16_t>)();
                                        r->L = static_cast<int64_t> (t.size());
                                        r->B = newPrimArray_(t.size() + 1, char16_t);
                                        int64_t p = 0;
                                        for (char c: t)
                                            r->B[p++] = c;
                                        r->B[t.size()] = 0;
                                        return r;
                                    }

                                    static type_(Array_ < char16_t>) toStr_(uint16_t v)
                                    {
                                        std::stringstream s;
                                        s << "0x" << std::uppercase << std::setfill('0') << std::setw(4) << std::hex << v;
                                        const std::string &t = s.str();
                                        type_(Array_ < char16_t>) r = new_(Array_ < char16_t>)();
                                        r->L = static_cast<int64_t> (t.size());
                                        r->B = newPrimArray_(t.size() + 1, char16_t);
                                        int64_t p = 0;
                                        for (char c: t)
                                            r->B[p++] = c;
                                        r->B[t.size()] = 0;
                                        return r;
                                    }

                                    static type_(Array_ < char16_t>) toStr_(uint32_t v)
                                    {
                                        std::stringstream s;
                                        s << "0x" << std::uppercase << std::setfill('0') << std::setw(8) << std::hex << v;
                                        const std::string &t = s.str();
                                        type_(Array_ < char16_t>) r = new_(Array_ < char16_t>)();
                                        r->L = static_cast<int64_t> (t.size());
                                        r->B = newPrimArray_(t.size() + 1, char16_t);
                                        int64_t p = 0;
                                        for (char c: t)
                                            r->B[p++] = c;
                                        r->B[t.size()] = 0;
                                        return r;
                                    }

                                    static type_(Array_ < char16_t>) toStr_(uint64_t v)
                                    {
                                        std::stringstream s;
                                        s << "0x" << std::uppercase << std::setfill('0') << std::setw(16) << std::hex << v;
                                        const std::string &t = s.str();
                                        type_(Array_ < char16_t>) r = new_(Array_ < char16_t>)();
                                        r->L = static_cast<int64_t> (t.size());
                                        r->B = newPrimArray_(t.size() + 1, char16_t);
                                        int64_t p = 0;
                                        for (char c: t)
                                            r->B[p++] = c;
                                        r->B[t.size()] = 0;
                                        return r;
                                    }

                                    static type_(Array_ < char16_t>) toStr_(type_(Array_ < char16_t>) v)
                                    {
                                        return v;
                                    }

                                    static int64_t cmp_(type_(Array_ < char16_t>) a, type_(Array_ < char16_t>) b)
                                    {
                                        int64_t p = 0;
                                        while (p < a->L && p < b->L)
                                        {
                                            if (a->B[p] != b->B[p])
                                                return a->B[p] > b->B[p] ? 1 : (a->B[p] < b->B[p] ? -1 : 0);
                                            p++;
                                        }

                                        return a->L > b->L ? 1 : (a->L < b->L ? -1 : 0);
                                    }

                                    static int64_t cmp_(type_(Class_) a, type_(Class_) b)
                                    {
                                        return reinterpret_cast<int64_t(*)(type_(Class_), type_(Class_)) > (classTable_[a->Y + 3])(a, b);
                                    }

                                    static int64_t cmp_(int64_t a, int64_t b)
                                    {
                                        return a - b;
                                    }

                                    static int64_t cmp_(char16_t a, char16_t b)
                                    {
                                        return static_cast<int64_t> (a) - static_cast<int64_t> (b);
                                    }

                                    static int64_t cmp_(double a, double b)
                                    {
                                        return a > b ? 1 LL : (a < b ? -1 LL : 0 LL);
                                    }

                                    static int64_t cmp_(uint8_t a, uint8_t b)
                                    {
                                        return static_cast<int64_t> (a) - static_cast<int64_t> (b);
                                    }

                                    static int64_t cmp_(uint16_t a, uint16_t b)
                                    {
                                        return static_cast<int64_t> (a) - static_cast<int64_t> (b);
                                    }

                                    static int64_t cmp_(uint32_t a, uint32_t b)
                                    {
                                        return static_cast<int64_t> (a) - static_cast<int64_t> (b);
                                    }

                                    static int64_t cmp_(uint64_t a, uint64_t b)
                                    {
                                        return a > b ? 1 LL : (a < b ? -1 LL : 0 LL);
                                    }

                                    static type_(Array_ < uint8_t>) makeBin_(const void *v, std::size_t s)
                                    {
                                        type_(Array_ < uint8_t>) r = new_(Array_ < uint8_t>)();
                                        r->L = s;
                                        r->B = newPrimArray_(s, uint8_t);
                                        memcpy(r->B, v, s);
                                        return r;
                                    }

                                    static void mergeBin_(type_(Array_ < uint8_t>) a, const type_(Array_ < uint8_t>) b)
                                    {
                                        int64_t l = a->L + b->L;
                                        uint8_t *d = newPrimArray_(static_cast<std::size_t > (l), uint8_t);
                                        memcpy(d, a->B, static_cast<std::size_t > (a->L));
                                        memcpy(d + a->L, b->B, static_cast<std::size_t > (b->L));
                                        a->L = l;
                                        a->B = d;
                                    }

                                    template < typename T > struct toBin_ {};
                                    template < typename T > struct toBin_<type_(Array_ < T>) >
                                    {
                                        type_(Array_ < uint8_t>) operator()(type_(Array_ < T>) v)
                                        {
                                            if (v == nullptr)
                                            {
                                                int64_t p = -1;
                                                return makeBin_(&p, sizeof(p));
                                            }

                                            type_(Array_ < uint8_t>) r = makeBin_(&v->L, sizeof(int64_t));
                                            for (int64_t i = 0; i < v->L; i++)
                                                mergeBin_(r, toBin_<T> ()(v->B[i]));
                                            return r;
                                        }
                                    };
                                    template < typename T > struct toBin_<type_(List_ < T>) >
                                    {
                                        type_(Array_ < uint8_t>) operator()(type_(List_ < T>) v)
                                        {
                                            if (v == nullptr)
                                            {
                                                int64_t p = -1;
                                                return makeBin_(&p, sizeof(p));
                                            }

                                            int64_t s = static_cast<int64_t> (v->B.size());
                                            type_(Array_ < uint8_t>) r = makeBin_(&s, sizeof(int64_t));
                                            int64_t c = 0, d = -1;
                                            for (auto i = v->B.begin(); i != v->B.end(); ++i, ++c)
                                                if (i == v->I)
                                                {
                                                    d = c;
                                                    break;
                                                }

                                            mergeBin_(r, makeBin_(&d, sizeof(int64_t)));
                                            for (auto &n: v->B)
                                                mergeBin_(r, toBin_<T> ()(n));
                                            return r;
                                        }
                                    };
                                    template < typename T > struct toBin_<type_(Stack_ < T>) >
                                    {
                                        type_(Array_ < uint8_t>) operator()(type_(Stack_ < T>) v)
                                        {
                                            if (v == nullptr)
                                            {
                                                int64_t p = -1;
                                                return makeBin_(&p, sizeof(p));
                                            }

                                            int64_t s = static_cast<int64_t> (v->B.size());
                                            std::stack<T> b;
                                            type_(Array_ < uint8_t>) r = makeBin_(&s, sizeof(int64_t));
                                            while (!v->B.empty())
                                            {
                                                b.push(v->B.top());
                                                v->B.pop();
                                            }

                                            while (!b.empty())
                                            {
                                                T n = b.top();
                                                mergeBin_(r, toBin_<T> ()(n));
                                                v->B.push(n);
                                                b.pop();
                                            }

                                            return r;
                                        }
                                    };
                                    template < typename T > struct toBin_<type_(Queue_ < T>) >
                                    {
                                        type_(Array_ < uint8_t>) operator()(type_(Queue_ < T>) v)
                                        {
                                            if (v == nullptr)
                                            {
                                                int64_t p = -1;
                                                return makeBin_(&p, sizeof(p));
                                            }

                                            int64_t s = static_cast<int64_t> (v->B.size());
                                            std::queue<T> b;
                                            type_(Array_ < uint8_t>) r = makeBin_(&s, sizeof(int64_t));
                                            while (!v->B.empty())
                                            {
                                                T n = v->B.front();
                                                b.push(n);
                                                mergeBin_(r, toBin_<T> ()(n));
                                                v->B.pop();
                                            }

                                            while (!b.empty())
                                            {
                                                v->B.push(b.front());
                                                b.pop();
                                            }

                                            return r;
                                        }
                                    };
                                    template < typename T1, typename T2 > struct toBin_<type_(Dict_<T1, T2>) >
                                    {
                                        type_(Array_ < uint8_t>) operator()(type_(Dict_<T1, T2>) v)
                                        {
                                            if (v == nullptr)
                                            {
                                                int64_t p = -1;
                                                return makeBin_(&p, sizeof(p));
                                            }

                                            type_(Array_ < uint8_t>) r = makeBin_(&v->L, sizeof(int64_t));
                                            dictToBinRec_<T1, T2> (r, v->B);
                                            return r;
                                        }
                                    };
                                    template < typename T > struct toBin_ < type_(T) >
                                    {
                                        type_(Array_ < uint8_t>) operator()(type_(T) v)
                                        {
                                            if (v == nullptr)
                                            {
                                                int64_t p = -1;
                                                return makeBin_(&p, sizeof(p));
                                            }

                                            auto w = dcast_(Class_)(v);
                                            type_(Array_ < uint8_t>) r = makeBin_(&w->Y, sizeof(int64_t));
                                            mergeBin_(r, reinterpret_cast<type_(Array_ < uint8_t>)(*)(type_(Class_)) > (classTable_[w->Y + 5])(w));
                                            return r;
                                        }
                                    };
                                    template < > struct toBin_ < int64_t>
                                    {
                                        type_(Array_ < uint8_t>) operator()(int64_t v)
                                        {
                                            return makeBin_(&v, sizeof(v));
                                        }
                                    };
                                    template < > struct toBin_ < double>
                                    {
                                        type_(Array_ < uint8_t>) operator()(double v)
                                        {
                                            return makeBin_(&v, sizeof(v));
                                        }
                                    };
                                    template < > struct toBin_ < char16_t>
                                    {
                                        type_(Array_ < uint8_t>) operator()(char16_t v)
                                        {
                                            return makeBin_(&v, sizeof(v));
                                        }
                                    };
                                    template < > struct toBin_ < bool>
                                    {
                                        type_(Array_ < uint8_t>) operator()(bool v)
                                        {
                                            return makeBin_(&v, sizeof(v));
                                        }
                                    };
                                    template < > struct toBin_ < uint8_t>
                                    {
                                        type_(Array_ < uint8_t>) operator()(uint8_t v)
                                        {
                                            return makeBin_(&v, sizeof(v));
                                        }
                                    };
                                    template < > struct toBin_ < uint16_t>
                                    {
                                        type_(Array_ < uint8_t>) operator()(uint16_t v)
                                        {
                                            return makeBin_(&v, sizeof(v));
                                        }
                                    };
                                    template < > struct toBin_ < uint32_t>
                                    {
                                        type_(Array_ < uint8_t>) operator()(uint32_t v)
                                        {
                                            return makeBin_(&v, sizeof(v));
                                        }
                                    };
                                    template < > struct toBin_ < uint64_t>
                                    {
                                        type_(Array_ < uint8_t>) operator()(uint64_t v)
                                        {
                                            return makeBin_(&v, sizeof(v));
                                        }
                                    };
                                    template < typename T > type_(Array_ < uint8_t>) toBinFunc_(T v)
                                    {
                                        int64_t p = -1;
                                        return makeBin_(&p, sizeof(p));
                                    }

                                    template < typename T > struct fromBin_ {};
                                    template < typename T > struct fromBin_<type_(Array_ < T>) >
                                    {
                                        type_(Array_ < T>) operator()(type_(Array_ < uint8_t>) b, int64_t &o)
                                        {
                                            int64_t l = *reinterpret_cast<int64_t*> (b->B + o);
                                            o += sizeof(int64_t);
                                            if (l == -1) return nullptr;
                                            type_(Array_ < T>) r = new_(Array_ < T>)();
                                            r->L = l;
                                            r->B = newPrimArray_(static_cast<std::size_t > (l) + bufLen_<T> (), T);
                                            for (int64_t i = 0; i < l; i++)
                                                r->B[i] = fromBin_<T> ()(b, o);
                                            if (bufLen_<T> () > 0)
                                                r->B[l] = 0;
                                            return r;
                                        }
                                    };
                                    template < typename T > struct fromBin_<type_(List_ < T>) >
                                    {
                                        type_(List_ < T>) operator()(type_(Array_ < uint8_t>) b, int64_t &o)
                                        {
                                            int64_t l = *reinterpret_cast<int64_t*> (b->B + o);
                                            o += sizeof(int64_t);
                                            if (l == -1) return nullptr;
                                            type_(List_ < T>) r = new_(List_ < T>)();
                                            int64_t d = *reinterpret_cast<int64_t*> (b->B + o);
                                            o += sizeof(int64_t);
                                            for (int64_t i = 0; i < l; i++)
                                            {
                                                r->B.push_back(fromBin_<T> ()(b, o));
                                                if (i == d)
                                                {
                                                    auto e = r->B.end();
                                                    --e;
                                                    r->I = e;
                                                }
                                            }

                                            return r;
                                        }
                                    };
                                    template < typename T > struct fromBin_<type_(Stack_ < T>) >
                                    {
                                        type_(Stack_ < T>) operator()(type_(Array_ < uint8_t>) b, int64_t &o)
                                        {
                                            int64_t l = *reinterpret_cast<int64_t*> (b->B + o);
                                            o += sizeof(int64_t);
                                            if (l == -1) return nullptr;
                                            type_(Stack_ < T>) r = new_(Stack_ < T>)();
                                            for (int64_t i = 0; i < l; i++)
                                                r->B.push(fromBin_<T> ()(b, o));
                                            return r;
                                        }
                                    };
                                    template < typename T > struct fromBin_<type_(Queue_ < T>) >
                                    {
                                        type_(Queue_ < T>) operator()(type_(Array_ < uint8_t>) b, int64_t &o)
                                        {
                                            int64_t l = *reinterpret_cast<int64_t*> (b->B + o);
                                            o += sizeof(int64_t);
                                            if (l == -1) return nullptr;
                                            type_(Queue_ < T>) r = new_(Queue_ < T>)();
                                            for (int64_t i = 0; i < l; i++)
                                                r->B.push(fromBin_<T> ()(b, o));
                                            return r;
                                        }
                                    };
                                    template < typename T1, typename T2 > struct fromBin_<type_(Dict_<T1, T2>) >
                                    {
                                        type_(Dict_<T1, T2>) operator()(type_(Array_ < uint8_t>) b, int64_t &o)
                                        {
                                            int64_t l = *reinterpret_cast<int64_t*> (b->B + o);
                                            o += sizeof(int64_t);
                                            if (l == -1) return nullptr;
                                            type_(Dict_<T1, T2>) r = new_(Dict_<T1, T2>)();
                                            r->L = l;
                                            for (int64_t i = 0; i < l; i++)
                                            {
                                                T1 k = fromBin_<T1> ()(b, o);
                                                T2 v = fromBin_<T2> ()(b, o);
                                                r->Add(k, v);
                                            }

                                            return r;
                                        }
                                    };
                                    template < typename T > struct fromBin_ < type_(T) >
                                    {
                                        type_(T) operator()(type_(Array_ < uint8_t>) b, int64_t &o)
                                        {
                                            int64_t y = *reinterpret_cast<int64_t*> (b->B + o);
                                            o += sizeof(int64_t);
                                            if (y == -1) return nullptr;
                                            return dcast_(T)(reinterpret_cast< type_(Class_)(*)(type_(Class_), type_(Array_ < uint8_t>), int64_t *) > (classTable_[y + 6])(nullptr, b, &o));
                                        }
                                    };
                                    template < > struct fromBin_ < int64_t>
                                    {
                                        int64_t operator()(type_(Array_ < uint8_t>) b, int64_t &o)
                                        {
                                            int64_t r = *reinterpret_cast<int64_t*> (b->B + o);
                                            o += sizeof(int64_t);
                                            return r;
                                        }
                                    };
                                    template < > struct fromBin_ < double>
                                    {
                                        double operator()(type_(Array_ < uint8_t>) b, int64_t &o)
                                        {
                                            double r = *reinterpret_cast<double*> (b->B + o);
                                            o += sizeof(double);
                                            return r;
                                        }
                                    };
                                    template < > struct fromBin_ < char16_t>
                                    {
                                        char16_t operator()(type_(Array_ < uint8_t>) b, int64_t &o)
                                        {
                                            char16_t r = *reinterpret_cast<char16_t*> (b->B + o);
                                            o += sizeof(char16_t);
                                            return r;
                                        }
                                    };
                                    template < > struct fromBin_ < bool>
                                    {
                                        bool operator()(type_(Array_ < uint8_t>) b, int64_t &o)
                                        {
                                            bool r = *reinterpret_cast<bool*> (b->B + o);
                                            o += sizeof(bool);
                                            return r;
                                        }
                                    };
                                    template < > struct fromBin_ < uint8_t>
                                    {
                                        uint8_t operator()(type_(Array_ < uint8_t>) b, int64_t &o)
                                        {
                                            uint8_t r = *reinterpret_cast<uint8_t*> (b->B + o);
                                            o += sizeof(uint8_t);
                                            return r;
                                        }
                                    };
                                    template < > struct fromBin_ < uint16_t>
                                    {
                                        uint16_t operator()(type_(Array_ < uint8_t>) b, int64_t &o)
                                        {
                                            uint16_t r = *reinterpret_cast<uint16_t*> (b->B + o);
                                            o += sizeof(uint16_t);
                                            return r;
                                        }
                                    };
                                    template < > struct fromBin_ < uint32_t>
                                    {
                                        uint32_t operator()(type_(Array_ < uint8_t>) b, int64_t &o)
                                        {
                                            uint32_t r = *reinterpret_cast<uint32_t*> (b->B + o);
                                            o += sizeof(uint32_t);
                                            return r;
                                        }
                                    };
                                    template < > struct fromBin_ < uint64_t>
                                    {
                                        uint64_t operator()(type_(Array_ < uint8_t>) b, int64_t &o)
                                        {
                                            uint64_t r = *reinterpret_cast<uint64_t*> (b->B + o);
                                            o += sizeof(uint64_t);
                                            return r;
                                        }
                                    };
                                    template < typename T > T fromBinFunc_(type_(Array_ < uint8_t>) b, int64_t &o)
                                    {
                                        o += sizeof(void*);
                                        return nullptr;
                                    }

                                    template < typename T > type_(Array_ < T>) sub_(type_(Array_ < T>) a, int64_t start, int64_t len)
                                    {
                                        if (len == -1)
                                            len = a->L - start;
                                        if (start < 0 || len < 0 || start + len > a->L)
                                            throw 0xe9170006;
                                        type_(Array_ < T>) r = new_(Array_ < T>)();
                                        r->L = len;
                                        r->B = newPrimArray_(static_cast<std::size_t > (len + bufLen_<T> ()), T);
                                        for (int64_t i = 0; i < len; i++)
                                            r->B[i] = a->B[start + i];
                                        if (bufLen_<T> () > 0)
                                            r->B[len] = 0;
                                        return r;
                                    }

                                    template < typename T > type_(T) as_(const int64_t *y, type_(Class_) c, int64_t o)
                                    {
                                        if (c == nullptr)
                                            return nullptr;
                                        int64_t m = c->Y;
                                        for (;;)
                                        {
                                            if (m == o)
                                                return dcast_(T)(c);
                                            if (m == 0)
                                                return nullptr;
                                            m = y[m];
                                        }
                                    }

                                    static bool is_(const int64_t *y, type_(Class_) c, int64_t o)
                                    {
                                        int64_t m = c->Y;
                                        for (;;)
                                        {
                                            if (m == o)
                                                return true;
                                            if (m == 0)
                                                return false;
                                            m = y[m];
                                        }
                                    }

                                    template < typename T > T min_(type_(Array_ < T>) a)
                                    {
                                        if (a->L == 0)
                                            return (T) 0;
                                        T r = a->B[0];
                                        for (int64_t i = 0; i < a->L; i++)
                                        {
                                            if (cmp_(r, a->B[i]) > 0)
                                                r = a->B[i];
                                        }

                                        return r;
                                    }

                                    template < typename T > T max_(type_(Array_ < T>) a)
                                    {
                                        if (a->L == 0)
                                            return (T) 0;
                                        T r = a->B[0];
                                        for (int64_t i = 0; i < a->L; i++)
                                        {
                                            if (cmp_(r, a->B[i]) < 0)
                                                r = a->B[i];
                                        }

                                        return r;
                                    }

                                    template < typename T > type_(Array_ < T>) repeat_(type_(Array_ < T>) a, int64_t n)
                                    {
                                        type_(Array_ < T>) r = new_(Array_ < T>)();
                                        r->L = a->L * n;
                                        r->B = newPrimArray_(static_cast<std::size_t > (r->L) + bufLen_<T> (), T);
                                        for (int64_t i = 0; i < n; i++)
                                        {
                                            for (int64_t j = 0; j < a->L; j++)
                                                r->B[i *a->L + j] = a->B[j];
                                        }

                                        if (bufLen_<T> () > 0)
                                            r->B[r->L] = 0;
                                        return r;
                                    }

                                    template < typename T1, typename T2 > dictImpl_<T1, T2> *dictRotateLeft_(dictImpl_<T1, T2> *n)
                                    {
                                        dictImpl_<T1, T2> *r = n->CR;
                                        n->CR = r->CL;
                                        r->CL = n;
                                        r->R = n->R;
                                        n->R = true;
                                        return r;
                                    }

                                    template < typename T1, typename T2 > dictImpl_<T1, T2> *dictRotateRight_(dictImpl_<T1, T2> *n)
                                    {
                                        dictImpl_<T1, T2> *l = n->CL;
                                        n->CL = l->CR;
                                        l->CR = n;
                                        l->R = n->R;
                                        n->R = true;
                                        return l;
                                    }

                                    template < typename T1, typename T2 > void dictFlip_(dictImpl_<T1, T2> *n)
                                    {
                                        n->R = !n->R;
                                        n->CL->R = !n->CL->R;
                                        n->CR->R = !n->CR->R;
                                    }

                                    template < typename T1, typename T2 > dictImpl_<T1, T2> *dictFixUp_(dictImpl_<T1, T2> *n)
                                    {
                                        if (n->CR != nullptr && n->CR->R)
                                            n = dictRotateLeft_<T1, T2> (n);
                                        if (n->CL != nullptr && n->CL->R && n->CL->CL != nullptr && n->CL->CL->R)
                                            n = dictRotateRight_<T1, T2> (n);
                                        if (n->CL != nullptr && n->CL->R && n->CR != nullptr && n->CR->R)
                                            dictFlip_<T1, T2> (n);
                                        return n;
                                    }

                                    template < typename T1, typename T2 > dictImpl_<T1, T2> *dictAddRec_(dictImpl_<T1, T2> *n, T1 k, T2 v, bool *a)
                                    {
                                        if (n == nullptr)
                                        {
                                            *a = true;
                                            return newPrim_(dictImpl_<T1, T2>)(k, v);
                                        }

                                        int64_t c = cmp_(k, n->K);
                                        if (c == 0)
                                        {
                                            n->V = v;
                                            return n;
                                        }

                                        if (c < 0)
                                            n->CL = dictAddRec_<T1, T2> (n->CL, k, v, a);
                                        else
                                            n->CR = dictAddRec_<T1, T2> (n->CR, k, v, a);
                                        return dictFixUp_<T1, T2> (n);
                                    }

                                    template < typename T1, typename T2 > dictImpl_<T1, T2> *dictMoveRedLeft_(dictImpl_<T1, T2> *n)
                                    {
                                        dictFlip_<T1, T2> (n);
                                        if (n->CR->CL != nullptr && n->CR->CL->R)
                                        {
                                            n->CR = dictRotateRight_<T1, T2> (n->CR);
                                            n = dictRotateLeft_<T1, T2> (n);
                                            dictFlip_<T1, T2> (n);
                                        }

                                        return n;
                                    }

                                    template < typename T1, typename T2 > dictImpl_<T1, T2> *dictMoveRedRight_(dictImpl_<T1, T2> *n)
                                    {
                                        dictFlip_<T1, T2> (n);
                                        if (n->CL->CL != nullptr && n->CL->CL->R)
                                        {
                                            n = dictRotateRight_<T1, T2> (n);
                                            dictFlip_<T1, T2> (n);
                                        }

                                        return n;
                                    }

                                    template < typename T1, typename T2 > dictImpl_<T1, T2> *dictDelMinRec_(dictImpl_<T1, T2> *n)
                                    {
                                        if (n->CL == nullptr)
                                            return nullptr;
                                        if (!n->CL->R && !(n->CL->CL != nullptr && n->CL->CL->R))
                                            n = dictMoveRedLeft_<T1, T2> (n);
                                        n->CL = dictDelMinRec_<T1, T2> (n->CL);
                                        return dictFixUp_<T1, T2> (n);

                                    }

                                    template < typename T1, typename T2 > dictImpl_<T1, T2> *dictDelRec_(dictImpl_<T1, T2> *n, T1 k, bool *d)
                                    {
                                        if (n == nullptr)
                                            return nullptr;
                                        if (cmp_(k, n->K) < 0)
                                        {
                                            if (n->CL != nullptr && !n->CL->R && !(n->CL->CL != nullptr && n->CL->CL->R))
                                                n = dictMoveRedLeft_<T1, T2> (n);
                                            n->CL = dictDelRec_<T1, T2> (n->CL, k, d);
                                        }
                                        else
                                        {
                                            if (n->CL != nullptr && n->CL->R)
                                                n = dictRotateRight_<T1, T2> (n);
                                            if (n->CR != nullptr && !n->CR->R && !(n->CR->CL != nullptr && n->CR->CL->R))
                                                n = dictMoveRedRight_<T1, T2> (n);
                                            if (cmp_(k, n->K) == 0)
                                            {
                                                *d = true;
                                                if (n->CR == nullptr)
                                                    return nullptr;
                                                dictImpl_<T1, T2> *p = n->CR;
                                                while (p->CL != nullptr)
                                                    p = p->CL;
                                                n->K = p->K;
                                                n->V = p->V;
                                                n->CR = dictDelMinRec_<T1, T2> (n->CR);
                                            }
                                            else
                                                n->CR = dictDelRec_<T1, T2> (n->CR, k, d);
                                        }

                                        return dictFixUp_<T1, T2> (n);
                                    }

                                    template < typename T1, typename T2 > dictImpl_<T1, T2> *dictCopyRec_(dictImpl_<T1, T2> *n)
                                    {
                                        if (n == nullptr)
                                            return nullptr;
                                        dictImpl_<T1, T2> *r = newPrim_(dictImpl_<T1, T2>)(copy_<T1> ()(n->K), copy_<T2> ()(n->V));
                                        r->R = n->R;
                                        r->CL = dictCopyRec_(n->CL);
                                        r->CR = dictCopyRec_(n->CR);
                                        return r;
                                    }

                                    template < typename T1, typename T2 > void dictToBinRec_(type_(Array_ < uint8_t>) a, dictImpl_<T1, T2> *d)
                                    {
                                        if (d->CL != nullptr)
                                            dictToBinRec_(a, d->CL);
                                        mergeBin_(a, toBin_<T1> ()(d->K));
                                        mergeBin_(a, toBin_<T2> ()(d->V));
                                        if (d->CR != nullptr)
                                            dictToBinRec_(a, d->CR);
                                    }

                                    template < typename T1, typename T2 > T2 dictSearch_(dictImpl_<T1, T2> *r, T1 k, bool *f)
                                    {
                                        dictImpl_<T1, T2> *n = r;
                                        while (n != nullptr)
                                        {
                                            int64_t c = cmp_(k, n->K);
                                            if (c == 0)
                                            {
                                                *f = true;
                                                return n->V;
                                            }

                                            if (c < 0)
                                                n = n->CL;
                                            else
                                                n = n->CR;
                                        }

                                        *f = false;
                                        return (T2) 0;
                                    }

                                    template < typename T1, typename T2 > bool dictForEach_(dictImpl_<T1, T2> *r, bool(*f)(T1, T2, type_(Class_)), type_(Class_) p)
                                    {
                                        if (r == nullptr)
                                            return true;
                                        if (!dictForEach_<T1, T2> (r->CL, f, p))
                                            return false;
                                        if (!f(r->K, r->V, p))
                                            return false;
                                        if (!dictForEach_<T1, T2> (r->CR, f, p))
                                            return false;
                                        return true;
                                    }

                                    template < typename T1, typename T2 > bool dictExist_(dictImpl_<T1, T2> *r, T1 k)
                                    {
                                        dictImpl_<T1, T2> *n = r;
                                        while (n != nullptr)
                                        {
                                            int64_t c = cmp_(k, n->K);
                                            if (c == 0)
                                                return true;
                                            if (c < 0)
                                                n = n->CL;
                                            else
                                                n = n->CR;
                                        }

                                        return false;
                                    }

                                    template < typename T1, typename T2 > void dictFreeRec_(dictImpl_<T1, T2> *n)
                                    {
                                        if (n == nullptr)
                                            return;
                                        dictFreeRec_<T1, T2> (n->CL);
                                        dictFreeRec_<T1, T2> (n->CR);
                                        delPrim_(n);
                                    }

                                    static int64_t powI_(int64_t a, int64_t b)
                                    {
                                        switch (b)
                                        {
                                            case 0 LL:
                                                return 1 LL;
                                            case 1 LL:
                                                return a;
                                            case 2 LL:
                                                return a * a;
                                        }

                                        if (a == 1 LL)
                                            return 1 LL;
                                        if (a == -1 LL)
                                            return (b &1 LL) == 0 LL ? 1 LL : -1 LL;
                                        if (b < 0 LL)
                                            return 0 LL;
                                        int64_t r = 1 LL;
                                        for (;;)
                                        {
                                            if ((b &1 LL) == 1 LL)
                                                r *= a;
                                            b >>= 1 LL;
                                            if (b == 0 LL)
                                                break;
                                            a *= a;
                                        }

                                        return r;
                                    }

                                    template < typename T > void reverse_(type_(Array_ < T>) me)
                                    {
                                        std::reverse<T*> (me->B, me->B + me->L);
                                    }

                                    template < typename T > bool sortCmp_(const T &a, const T &b)
                                    {
                                        return cmp_(a, b) < 0;
                                    }

                                    template < typename T > void sort_(type_(Array_ < T>) me)
                                    {
                                        std::sort<T*, bool(*)(const T &, const T &) > (me->B, me->B + me->L, sortCmp_ < T>);
                                    }

                                    static uint8_t sar_(uint8_t me_, int64_t n)
                                    {
                                        return static_cast<uint8_t> (static_cast<int8_t> (me_) >> n);
                                    }

                                    static uint16_t sar_(uint16_t me_, int64_t n)
                                    {
                                        return static_cast<uint16_t> (static_cast<int16_t> (me_) >> n);
                                    }

                                    static uint32_t sar_(uint32_t me_, int64_t n)
                                    {
                                        return static_cast<uint32_t> (static_cast<int32_t> (me_) >> n);
                                    }

                                    static uint64_t sar_(uint64_t me_, int64_t n)
                                    {
                                        return static_cast<uint64_t> (static_cast<int64_t> (me_) >> n);
                                    }

                                    static uint8_t endian_(uint8_t me_)
                                    {
                                        return me_;
                                    }

                                    static uint16_t endian_(uint16_t me_)
                                    {
                                        return ((me_ & 0x00ff) << 8) | ((me_ & 0xff00) >> 8);
                                    }

                                    static uint32_t endian_(uint32_t me_)
                                    {
                                        me_ = ((me_ & 0x00ff00ff) << 8) | ((me_ & 0xff00ff00) >> 8);
                                        return ((me_ & 0x0000ffff) << 16) | ((me_ & 0xffff0000) >> 16);
                                    }

                                    static uint64_t endian_(uint64_t me_)
                                    {
                                        me_ = ((me_ & 0x00ff00ff00ff00ff) << 8) | ((me_ & 0xff00ff00ff00ff00) >> 8);
                                        me_ = ((me_ & 0x0000ffff0000ffff) << 16) | ((me_ & 0xffff0000ffff0000) >> 16);
                                        return ((me_ & 0x00000000ffffffff) << 32) | ((me_ & 0xffffffff00000000) >> 32);
                                    }

                                    struct reader_
                                    {
                                        reader_(): F(nullptr) {}

                                        std::FILE * F;
                                    };

                                    struct writer_
                                    {
                                        writer_(): F(nullptr) {}

                                        std::FILE * F;
                                    };

                                    template < typename T>
                                        struct listPtr_
                                        {
                                            listPtr_<T> () {}

                                            typename T::iterator I;
                                        };

                                    static void init_()
                                    {
                                        setlocale(LC_ALL, "");
                                    }

                                    class k_o;
                                    class k_n;
                                    void k_main_();
                                    static void k_d();
                                    static void k_e();
                                    static void k_f();
                                    static void k_g();
                                    static void k_i();
                                    static void k_j();
                                    static void k_l(int64_t k_bd /*excpt*/);
                                    static void k_p(type_(k_o) k_bg /*me*/);
                                    static void k_q(k_o *k_bh);
                                    static int64_t k_r(type_(k_o) k_bi /*me*/, type_(k_o) k_bj /*t*/);
                                    static type_(k_o) k_s(type_(k_o) k_bk /*me*/);
                                    static type_(Array_ < uint8_t>) k_t(type_(k_o) k_bn /*me*/);
                                    static type_(k_o) k_u(type_(k_o) k_bp /*me*/, type_(Array_ < uint8_t>) k_bq /*bin*/, int64_t *k_br /*idx*/);
                                    static type_(Array_ < char16_t>) k_v(type_(k_o) k_bu /*me*/);
                                    static void k_w(type_(k_n) k_bv /*me*/);
                                    using k_bx = void(*)(type_(k_o));
                                    static int64_t k_x(type_(k_n) k_by /*me*/, int64_t k_bz /*min*/, int64_t k_ca /*max*/);
                                    using k_ck = uint64_t(*)(type_(k_n));
                                    static uint64_t k_y(type_(k_n) k_cn /*me*/);
                                    using k_cp = uint32_t(*)(type_(k_n));
                                    static double k_z(type_(k_n) k_cs /*me*/, double k_ct /*min*/, double k_cu /*max*/);
                                    static void k_aa(type_(k_n) k_cz /*me*/, uint32_t k_da /*seed*/);
                                    static uint32_t k_ab(type_(k_n) k_dg /*me*/);
                                    static void k_ac(k_n *k_di);
                                    static type_(k_n) k_ad(type_(k_n) k_dj);
                                    static type_(Array_ < uint8_t>) k_ae(type_(k_n) k_dm);
                                    static type_(k_n) k_af(type_(k_n) k_ds, type_(Array_ < uint8_t>) k_dt, int64_t *k_du);
                                    static type_(k_n) k_ag(type_(k_n) k_dx /*me2*/, uint32_t k_dy /*seed*/);
                                    using k_dz = void(*)(type_(k_n), uint32_t);
                                    template < typename T_ > static T_ k_ai(T_ k_ea /*me_*/, type_(Array_ < int64_t>) k_eb /*type*/, T_ k_ec /*n*/);
                                    static int64_t k_aj();
                                    static int64_t k_ak();
                                    static void k_bb(type_(Array_ < char16_t>) k_ed /*str*/);
                                    template < typename T_ > static type_(Array_ < char16_t>) k_bc(T_ k_ee /*me_*/, type_(Array_ < int64_t>) k_ef /*type*/);
                                    template < typename T_ > static T_ k_cq(T_ k_eg /*me_*/, type_(Array_ < int64_t>) k_eh /*type*/, T_ k_ei /*n*/);
                                    template < typename T_ > static T_ k_cr(T_ k_ej /*me_*/, type_(Array_ < int64_t>) k_ek /*type*/, int64_t k_el /*n*/);
                                    template < typename T_ > static T_ k_df(T_ k_eo /*me_*/, type_(Array_ < int64_t>) k_ep /*type*/, int64_t k_eq /*n*/);
                                    static int64_t argc_;
                                    static char **argv_;
                                   	// Class
                                    class k_o: public Class_
                                    {
                                        public_colon
                                        k_o();
                                        virtual~k_o();
                                    };
                                   	// Rnd
                                    class k_n: public k_o
                                    {
                                        public_colon
                                        k_n();
                                        virtual~k_n();
                                        uint32_t k_db;	// x
                                        uint32_t k_dc;	// y
                                        uint32_t k_dd;	// z
                                        uint32_t k_de;	// w
                                    };
                                    static type_(k_n) k_m;
                                    static type_(Array_ < char16_t>) k_al;
                                    k_o::k_o(): Class_()
                                    {
                                        Y = 0;
                                    }

                                    k_o::~k_o()
                                    {
                                        k_q(this);
                                    }

                                    k_n::k_n(): k_o(), k_db(), k_dc(), k_dd(), k_de()
                                    {
                                        Y = 8;
                                    }

                                    k_n::~k_n()
                                    {
                                        k_ac(this);
                                    }

                                   	// k_main_
                                    void k_main_()
                                    {
                                        int64_t k_b;	// $
                                        try
                                        {
                                            try
                                            {
                                                (k_d)();
                                                (k_e)();
                                                (k_f)();
                                                (k_g)();
                                                (k_i)();
                                                (k_j)();
                                            }

                                            catch (int64_t k_b)
                                            {
                                                if (((0 LL) <= k_b && k_b <= (4294967295 LL)))
                                                {
                                                    (k_l)((k_b));
                                                }
                                                else
                                                {
                                                    throw;
                                                }
                                            }
                                        }

                                        catch (...)
                                        {
                                            (k_i)();
                                            (k_j)();
                                            throw;
                                        }
                                    }

                                   	// _init
                                    static void k_d() {}

                                   	// _init
                                    static void k_e()
                                    {
                                        type_(k_n) k_ah;
                                        (k_m) = ((k_ag)((k_ah = new_(k_n)(), k_w(k_ah), k_ah), (k_ai<uint32_t> ((static_cast<uint32_t> ((k_aj)())), (nullptr), (static_cast<uint32_t> ((k_ak)()))))));
                                    }

                                   	// _initVars
                                    static void k_f()
                                    {
                                        (k_al) = (newArrayBin_<char16_t> (3, "\x20\x00\x2C\x00\x0A\x00"));
                                    }

                                   	// main
                                    static void k_g()
                                    {
                                        int64_t k_ap;
                                        bool k_ar;	// b
                                        int64_t k_av;
                                        int64_t k_aq;
                                        int64_t k_aw;
                                        for (k_ap = (2 LL), k_aq = (100 LL); k_ap <= k_aq; k_ap += (1 LL))
                                        {
                                            (k_ar) = (false);
                                            for (k_av = (2 LL), k_aw = ((k_ap) - (1 LL)); k_av <= k_aw; k_av += (1 LL))
                                            {
                                                if (((k_ap) % (k_av)) == (0 LL))
                                                {
                                                    (k_ar) = (true);
                                                }
                                            }

                                            if (!(k_ar))
                                            {
                                                (k_bb)((((newArrayBin_<char16_t> (0, ""))->Cat(k_bc<int64_t> ((k_ap), (nullptr))))->Cat(newArrayBin_<char16_t> (1, "\x0A\x00"))));
                                            }
                                        }
                                    }

                                   	// _finVars
                                    static void k_i()
                                    {
                                        (k_al) = (nullptr);
                                        (k_m) = (nullptr);
                                    }

                                   	// _fin
                                    static void k_j() {}

                                   	// _err
                                    static void k_l(int64_t k_bd /*excpt*/) {}

                                   	// ctor
                                    static void k_p(type_(k_o) k_bg /*me*/) {}

                                   	// _dtor
                                    static void k_q(k_o *k_bh) {}

                                   	// cmp
                                    static int64_t k_r(type_(k_o) k_bi /*me*/, type_(k_o) k_bj /*t*/)
                                    {
                                        throw 3910598660 LL;
                                    }

                                   	// _copy
                                    static type_(k_o) k_s(type_(k_o) k_bk /*me*/)
                                    {
                                        type_(k_o) k_bl;
                                        type_(k_o) k_bm;
                                        (k_bl) = (k_bm = new_(k_o)(), k_p(k_bm), k_bm);
                                        return as_<k_o> (classTable_, (k_bl), 0);
                                    }

                                   	// _toBin
                                    static type_(Array_ < uint8_t>) k_t(type_(k_o) k_bn /*me*/)
                                    {
                                        type_(Array_ < uint8_t>) k_bo;
                                        (k_bo) = (newArrays_<type_(Array_ < uint8_t>) > ((0 LL)));
                                        return k_bo;
                                    }

                                   	// _fromBin
                                    static type_(k_o) k_u(type_(k_o) k_bp /*me*/, type_(Array_ < uint8_t>) k_bq /*bin*/, int64_t *k_br /*idx*/)
                                    {
                                        type_(k_o) k_bs;
                                        type_(k_o) k_bt;
                                        (k_bs) = (k_bt = new_(k_o)(), k_p(k_bt), k_bt);
                                        return k_bs;
                                    }

                                   	// toStr
                                    static type_(Array_ < char16_t>) k_v(type_(k_o) k_bu /*me*/)
                                    {
                                        return newArrayBin_<char16_t> (0, "");
                                    }

                                   	// ctor
                                    static void k_w(type_(k_n) k_bv /*me*/)
                                    {
                                        k_bx k_bw;	// super
                                        (k_bw) = (k_p);
                                    }

                                   	// rnd
                                    static int64_t k_x(type_(k_n) k_by /*me*/, int64_t k_bz /*min*/, int64_t k_ca /*max*/)
                                    {
                                        uint64_t k_cf;	// n
                                        uint64_t k_cg;	// m
                                        uint64_t k_ch;	// r
                                        if (((k_ca) - (k_bz)) < (0 LL))
                                        {
                                            throw 3910598662 LL;
                                        }

                                        (k_cf) = (static_cast<uint64_t> (((k_ca) - (k_bz)) + (1 LL)));
                                        (k_cg) = ((0x0000000000000000 ULL) - (((0x0000000000000000 ULL) - (k_cf)) % (k_cf)));
                                        (k_ch) = (0x0000000000000000 ULL);
                                        if ((k_cg) == (0x0000000000000000 ULL))
                                        {
                                            (k_ch) = ((reinterpret_cast<k_ck> (classTable_[(k_by)->Y + 9]))((k_by)));
                                        }
                                        else
                                        {
                                            do {
                                                (k_ch) = ((reinterpret_cast<k_ck> (classTable_[(k_by)->Y + 9]))((k_by)));
                                            } while ((k_cg) <= (k_ch));
                                        }

                                        return (static_cast<int64_t> ((k_ch) % (k_cf))) + (k_bz);
                                    }

                                   	// rndBit64
                                    static uint64_t k_y(type_(k_n) k_cn /*me*/)
                                    {
                                        uint32_t k_co;	// t
                                        (k_co) = ((reinterpret_cast<k_cp> (classTable_[(k_cn)->Y + 12]))((k_cn)));
                                        return k_cq<uint64_t> ((k_cr<uint64_t> ((static_cast<uint64_t> (k_co)), (nullptr), (32 LL))), (nullptr), (static_cast<uint64_t> ((reinterpret_cast<k_cp> (classTable_[(k_cn)->Y + 12]))((k_cn)))));
                                    }

                                   	// rndFloat
                                    static double k_z(type_(k_n) k_cs /*me*/, double k_ct /*min*/, double k_cu /*max*/)
                                    {
                                        if ((k_ct) >= (k_cu))
                                        {
                                            throw 3910598662 LL;
                                        }

                                        return (((static_cast<double> ((reinterpret_cast<k_ck> (classTable_[(k_cs)->Y + 9]))((k_cs)))) / (18446744073709552000.0)) *((k_cu) - (k_ct))) + (k_ct);
                                    }

                                   	// setSeed
                                    static void k_aa(type_(k_n) k_cz /*me*/, uint32_t k_da /*seed*/)
                                    {
                                        ((k_cz)->k_db) = (0x075BCD15 U);
                                        ((k_cz)->k_dc) = (0x159A55E5 U);
                                        ((k_cz)->k_dd) = ((0x1F123BB5 U) *(k_da));
                                        ((k_cz)->k_de) = ((0x05491333 U) *(k_df<uint32_t> (((k_cz)->k_dd), (nullptr), (1 LL))));
                                    }

                                   	// xs128
                                    static uint32_t k_ab(type_(k_n) k_dg /*me*/)
                                    {
                                        uint32_t k_dh;	// t
                                        (k_dh) = (k_ai<uint32_t> (((k_dg)->k_db), (nullptr), (k_cr<uint32_t> (((k_dg)->k_db), (nullptr), (11 LL)))));
                                        ((k_dg)->k_db) = ((k_dg)->k_dc);
                                        ((k_dg)->k_dc) = ((k_dg)->k_dd);
                                        ((k_dg)->k_dd) = ((k_dg)->k_de);
                                        ((k_dg)->k_de) = (k_ai<uint32_t> ((k_ai<uint32_t> (((k_dg)->k_de), (nullptr), (k_df<uint32_t> (((k_dg)->k_de), (nullptr), (19 LL))))), (nullptr), (k_ai<uint32_t> ((k_dh), (nullptr), (k_df<uint32_t> ((k_dh), (nullptr), (8 LL)))))));
                                        return (k_dg)->k_de;
                                    }

                                   	// _dtor
                                    static void k_ac(k_n *k_di) {}

                                   	// _copy
                                    static type_(k_n) k_ad(type_(k_n) k_dj)
                                    {
                                        type_(k_n) k_dk;
                                        type_(k_n) k_dl;
                                        (k_dk) = (k_dl = new_(k_n)(), k_w(k_dl), k_dl);
                                        ((k_dk)->k_db) = ((k_dj)->k_db);
                                        ((k_dk)->k_dc) = ((k_dj)->k_dc);
                                        ((k_dk)->k_dd) = ((k_dj)->k_dd);
                                        ((k_dk)->k_de) = ((k_dj)->k_de);
                                        return as_<k_n> (classTable_, (k_dk), 8);
                                    }

                                   	// _toBin
                                    static type_(Array_ < uint8_t>) k_ae(type_(k_n) k_dm)
                                    {
                                        type_(Array_ < uint8_t>) k_dn;
                                        (k_dn) = (newArrays_<type_(Array_ < uint8_t>) > ((0 LL)));
                                        (k_dn) = ((k_dn)->Cat(toBin_<uint32_t> ()(((k_dm)->k_db))));
                                        (k_dn) = ((k_dn)->Cat(toBin_<uint32_t> ()(((k_dm)->k_dc))));
                                        (k_dn) = ((k_dn)->Cat(toBin_<uint32_t> ()(((k_dm)->k_dd))));
                                        (k_dn) = ((k_dn)->Cat(toBin_<uint32_t> ()(((k_dm)->k_de))));
                                        return k_dn;
                                    }

                                   	// _fromBin
                                    static type_(k_n) k_af(type_(k_n) k_ds, type_(Array_ < uint8_t>) k_dt, int64_t *k_du)
                                    {
                                        type_(k_n) k_dv;
                                        type_(k_n) k_dw;
                                        (k_dv) = (k_dw = new_(k_n)(), k_w(k_dw), k_dw);
                                        ((k_dv)->k_db) = (fromBin_<uint32_t> ()((k_dt), (*k_du)));
                                        ((k_dv)->k_dc) = (fromBin_<uint32_t> ()((k_dt), (*k_du)));
                                        ((k_dv)->k_dd) = (fromBin_<uint32_t> ()((k_dt), (*k_du)));
                                        ((k_dv)->k_de) = (fromBin_<uint32_t> ()((k_dt), (*k_du)));
                                        return k_dv;
                                    }

                                   	// makeRnd
                                    static type_(k_n) k_ag(type_(k_n) k_dx /*me2*/, uint32_t k_dy /*seed*/)
                                    {
                                        (reinterpret_cast<k_dz> (classTable_[(k_dx)->Y + 11]))((k_dx), (k_dy));
                                        return k_dx;
                                    }

                                   	// _xor
                                    template < typename T_ > static T_ k_ai(T_ k_ea /*me_*/, type_(Array_ < int64_t>) k_eb /*type*/, T_ k_ec /*n*/)
                                    {
                                        return k_ea ^ k_ec;
                                    }

                                   	// sysTime
                                    static int64_t k_aj()
                                    {
                                        return static_cast<int64_t> (std::chrono::duration_cast<std::chrono::milliseconds > (std::chrono::system_clock::now().time_since_epoch()).count());
                                    }

                                   	// now
                                    static int64_t k_ak()
                                    {
                                        return std::time(nullptr);
                                    }

                                   	// print
                                    static void k_bb(type_(Array_ < char16_t>) k_ed /*str*/)
                                    {
                                        if (k_ed == nullptr)
                                        {
                                            fputs("(null)", stdout);
                                            return;
                                        }#
                                        if defined(_WIN32)
                                        fputws(reinterpret_cast<const wchar_t*> (k_ed->B), stdout);#
                                        else
                                            std::u16string s_ = k_ed->B;
                                        const std::string &t_ = utf16ToUtf8_(s_);
                                        fputs(t_.c_str(), stdout);#
                                        endif
                                    }

                                   	// _toStr
                                    template < typename T_ > static type_(Array_ < char16_t>) k_bc(T_ k_ee /*me_*/, type_(Array_ < int64_t>) k_ef /*type*/)
                                    {
                                        return toStr_(k_ee);
                                    }

                                   	// _or
                                    template < typename T_ > static T_ k_cq(T_ k_eg /*me_*/, type_(Array_ < int64_t>) k_eh /*type*/, T_ k_ei /*n*/)
                                    {
                                        return k_eg | k_ei;
                                    }

                                   	// _shl
                                    template < typename T_ > static T_ k_cr(T_ k_ej /*me_*/, type_(Array_ < int64_t>) k_ek /*type*/, int64_t k_el /*n*/)
                                    {
                                        if (k_el < 0 || k_el >= sizeof(k_ej) *8) throw 0xe9170006;
                                        return k_ej << k_el;
                                    }

                                   	// _shr
                                    template < typename T_ > static T_ k_df(T_ k_eo /*me_*/, type_(Array_ < int64_t>) k_ep /*type*/, int64_t k_eq /*n*/)
                                    {
                                        if (k_eq < 0 || k_eq >= sizeof(k_eo) *8) throw 0xe9170006;
                                        return k_eo >> k_eq;
                                    }

                                    int main(int c, char **v)
                                    {
                                        argc_ = static_cast<int64_t> (c) - 1;
                                        argv_ = v + 1;
                                        classTable_[0] = 0;
                                        classTable_[1] = reinterpret_cast<int64_t> (k_p);
                                        classTable_[2] = reinterpret_cast<int64_t> (k_q);
                                        classTable_[3] = reinterpret_cast<int64_t> (k_r);
                                        classTable_[4] = reinterpret_cast<int64_t> (k_s);
                                        classTable_[5] = reinterpret_cast<int64_t> (k_t);
                                        classTable_[6] = reinterpret_cast<int64_t> (k_u);
                                        classTable_[7] = reinterpret_cast<int64_t> (k_v);
                                        classTable_[8] = 0;
                                        classTable_[9] = reinterpret_cast<int64_t> (k_w);
                                        classTable_[10] = reinterpret_cast<int64_t> (k_ac);
                                        classTable_[11] = reinterpret_cast<int64_t> (k_r);
                                        classTable_[12] = reinterpret_cast<int64_t> (k_ad);
                                        classTable_[13] = reinterpret_cast<int64_t> (k_ae);
                                        classTable_[14] = reinterpret_cast<int64_t> (k_af);
                                        classTable_[15] = reinterpret_cast<int64_t> (k_v);
                                        classTable_[16] = reinterpret_cast<int64_t> (k_x);
                                        classTable_[17] = reinterpret_cast<int64_t> (k_y);
                                        classTable_[18] = reinterpret_cast<int64_t> (k_z);
                                        classTable_[19] = reinterpret_cast<int64_t> (k_aa);
                                        classTable_[20] = reinterpret_cast<int64_t> (k_ab);
                                        init_();
                                        k_main_();
                                        return static_cast<int> (exitCode_);
                                    }
                                }
                        }
                    }
            }
        }
}
