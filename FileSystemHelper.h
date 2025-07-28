// Copyright Koninklijke Philips N.V., 2025. All Rights Reserved

#pragma once

#include <filesystem>

namespace Philips::IGT::A2D::Components::Utility::FileSystem {

/**
 * @brief Check if the specified path exists.
 * @details Returns true if the path exists, false if not.
 * The function traces messages and errors, the consumer does not have to.
 */
bool pathExists(const std::filesystem::path& path);

/**
 * @brief Create directories, if they do not exist.
 * @details Returns true if a directory with the same path already exists.
 * Returns true if the directory/directories are created.
 * Returns false if a file with the same path already exists.
 * Returns false if the directory/directories are not created.
 * The function traces messages and errors, the consumer does not have to.
 */
bool createDirectories(const std::filesystem::path& path);

/**
 * @brief Convert the path to long path in Windows.
 */
std::filesystem::path::string_type longPath(const std::filesystem::path& path);

/**
 * @brief If the path is a directory, remove the directories and files recursively, after clearing the read-only flag.
 * @details If the path is a file or symbolic link, remove it, after clearing the read-only flag.
 * Returns true if the directory/file does not exist.
 * Returns true if the directory/file is deleted successfully.
 * Returns false if deletion failed.
 * The function traces messages and errors, the consumer does not have to.
 */
bool removePath(const std::filesystem::path& path);

/**
 * @brief Returns the path to the Philips ProgramData directory.
 * @details This function locates and returns the absolute path to the Philips-specific
 * ProgramData directory used for storing application data and configuration files.
 * The function traces messages and errors; the consumer does not have to.
 * @return The absolute path to the Philips ProgramData directory.
 */
std::filesystem::path philipsRoot();

/**
 * @brief Returns the directory containing the current executable.
 * @details This function determines and returns the absolute path to the directory
 * where the currently running executable resides.
 * The function traces messages and errors; the consumer does not have to.
 * @return The absolute path to the directory of the current executable.
 */
std::filesystem::path executionDirectory();

} // namespace Philips::IGT::A2D::Components::Utility::FileSystem
