// Copyright Koninklijke Philips N.V., 2025. All Rights Reserved

#include "Utility/FileSystemHelper.h"
#include <Trace.h>
#include <array>
#include <ShlObj_core.h>
#include <windows.h>

namespace Philips::IGT::A2D::Components::Utility::FileSystem {

namespace {

constexpr wchar_t kLongPathPrefix[]    = LR"(\\?\)";
constexpr wchar_t kProgramDataEnvVar[] = L"ProgramData";
constexpr wchar_t kPhilipsDirName[]    = L"Philips";

void clearReadOnlyFlag(const std::filesystem::path& path)
{
    std::error_code error;
    std::filesystem::permissions(path, std::filesystem::perms::all, error);

    if (std::cmp_not_equal(error.value(), 0))
    {
        TraceError() << "Failed to clear read-only flag for: " << path << std::endl
                     << "Error code: " << error.value() << std::endl
                     << "Error message: " << error.message();
    }
}

void clearReadOnly(const std::filesystem::path& path)
{
    clearReadOnlyFlag(path);

    std::error_code error;
    if (!std::filesystem::is_directory(path, error))
    {
        if (std::cmp_not_equal(error.value(), 0))
        {
            TraceError() << "Failed to check if the path is a directory: " << path << std::endl
                         << "Error code: " << error.value() << std::endl
                         << "Error message: " << error.message();
        }
        return;
    }

    const std::filesystem::recursive_directory_iterator directory_iterator(path, std::filesystem::directory_options::skip_permission_denied, error);
    if (std::cmp_not_equal(error.value(), 0))
    {
        TraceError() << "Failed to create the directory iterator for: " << path << std::endl
                     << "Error code: " << error.value() << std::endl
                     << "Error message: " << error.message();
        return;
    }

    for (const auto& item : directory_iterator) clearReadOnlyFlag(item.path());
}

} // namespace

bool pathExists(const std::filesystem::path& path)
{
    // Normalize lexically to avoid // in the path.
    const auto _path = path.lexically_normal();

    if (std::error_code error; !std::filesystem::exists(_path, error) && !std::filesystem::is_symlink(_path, error))
    {
        TraceMessage() << "The specified path does not exist" << std::endl
                       << "Path: " << _path << std::endl
                       << "Error code: " << error.value() << std::endl
                       << "Error message: " << error.message();
        return false;
    }

    return true;
}

bool createDirectories(const std::filesystem::path& path)
{
    // Normalize lexically to avoid // in the path.
    const auto _path = path.lexically_normal();

    if (pathExists(_path))
    {
        if (std::error_code error; std::filesystem::is_directory(_path, error)) return true;

        TraceError() << "Failed to create directory as a file with the same path already exists: " << path;
        return false;
    }

    if (std::error_code error; !std::filesystem::create_directories(_path, error))
    {
        // The next two checks are for paths with trailing \\, in which case create_directories()
        // returns false.
        if (std::cmp_equal(error.value(), 0))
            return true;
        else
            TraceWarning() << "Received error after creating: " << _path << std::endl
                           << "Error code: " << error.value() << std::endl
                           << "Error message: " << error.message();

        if (pathExists(_path)) return true;

        TraceError() << "Failed to create: " << _path << std::endl
                     << "Error code: " << error.value() << std::endl
                     << "Error message: " << error.message();

        return false;
    }

    return true;
}

std::filesystem::path::string_type longPath(const std::filesystem::path& path)
{
    return path.is_absolute() && (path.native().find(kLongPathPrefix) != 0) ? (kLongPathPrefix + path.native()) : path.native();
}

bool removePath(const std::filesystem::path& path)
{
    // Normalize lexically to avoid // in the path.
    std::filesystem::path _path = longPath(path.lexically_normal());

    if (!pathExists(_path)) return true;

    clearReadOnly(_path);

    if (std::error_code error; std::cmp_equal(std::filesystem::remove_all(_path, error), std::uintmax_t(-1)))
    {
        TraceError() << "Failed to delete: " << _path << std::endl
                     << "Error code: " << error.value() << std::endl
                     << "Error message: " << error.message();
        return false;
    }

    return true;
}

std::filesystem::path philipsRoot()
{
    // Try to get the ProgramData environment variable using Windows API for wide strings
    std::array<wchar_t, MAX_PATH> str{};
    DWORD                         len = GetEnvironmentVariableW(kProgramDataEnvVar, str.data(), static_cast<DWORD>(str.size()));
    if (len > 0 && len < str.size())
    {
        return std::filesystem::path(str.data()).append(kPhilipsDirName);
    }

    // Fallback to SHGetFolderPathW if the environment variable is not set
    if (!FAILED(SHGetFolderPathW(nullptr, CSIDL_COMMON_APPDATA, nullptr, SHGFP_TYPE_DEFAULT, str.data())))
    {
        return std::filesystem::path(str.data()).append(kPhilipsDirName);
    }

    return {};
}

std::filesystem::path executionDirectory()
{
    std::uint32_t        currentSize{100U};
    std::vector<wchar_t> charBuffer;
    do {
        currentSize *= 2;
        charBuffer.resize(currentSize);
    }
    while (GetModuleFileNameW(nullptr, charBuffer.data(), currentSize) == currentSize);

    std::filesystem::path path(charBuffer.data()); // Contains the full path including .exe
    return path.remove_filename();                 // Extract the directory ...
}

} // namespace Philips::IGT::A2D::Components::Utility::FileSystem
