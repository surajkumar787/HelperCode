// Copyright Koninklijke Philips N.V., 2025. All Rights Reserved

#pragma once
#include "Utility/StringHelper.h"
#include <windows.h>

namespace Philips::IGT::A2D::Components::Utility::String {

std::wstring wstring(const std::string& input)
{
    if (input.empty()) return std::wstring();

    int          size_needed = MultiByteToWideChar(CP_UTF8, 0, input.c_str(), static_cast<int>(input.size()), nullptr, 0);
    std::wstring wstr(size_needed, 0);
    MultiByteToWideChar(CP_UTF8, 0, input.c_str(), static_cast<int>(input.size()), &wstr[0], size_needed);

    return wstr;
}

std::string string(const std::wstring& input)
{
    if (input.empty()) return std::string();
    int         size_needed = WideCharToMultiByte(CP_UTF8, 0, input.c_str(), static_cast<int>(input.size()), nullptr, 0, nullptr, nullptr);
    std::string str(size_needed, 0);
    WideCharToMultiByte(CP_UTF8, 0, input.c_str(), static_cast<int>(input.size()), &str[0], size_needed, nullptr, nullptr);
    return str;
}

std::string lowercase(const std::string& input)
{
    std::string result = input;
    for (auto& c : result)
    {
        c = static_cast<char>(std::tolower(static_cast<unsigned char>(c)));
    }
    return result;
}

std::wstring lowercase(const std::wstring& input)
{
    std::wstring result = input;
    for (auto& c : result)
    {
        c = static_cast<wchar_t>(std::tolower(static_cast<wchar_t>(c)));
    }
    return result;
}

std::string uppercase(const std::string& input)
{
    std::string result = input;
    for (auto& c : result)
    {
        c = static_cast<char>(std::toupper(static_cast<unsigned char>(c)));
    }
    return result;
}

std::wstring uppercase(const std::wstring& input)
{
    std::wstring result = input;
    for (auto& c : result)
    {
        c = static_cast<wchar_t>(std::toupper(static_cast<wchar_t>(c)));
    }
    return result;
}

} // namespace Philips::IGT::A2D::Components::Utility::String
