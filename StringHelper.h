// Copyright Koninklijke Philips N.V., 2025. All Rights Reserved

#pragma once

#include <string>

namespace Philips::IGT::A2D::Components::Utility::String {

/**
 * @brief Converts a UTF-8 encoded std::string to a std::wstring.
 * @param input The UTF-8 encoded string to convert.
 * @return The converted wide string.
 */
std::wstring wstring(const std::string& input);

/**
 * @brief Converts a std::wstring to a UTF-8 encoded std::string.
 * @param input The wide string to convert.
 * @return The converted UTF-8 encoded string.
 */
std::string string(const std::wstring& input);

/**
 * @brief Converts all characters in the input string to lowercase.
 * @param input The string to convert.
 * @return A new string with all characters in lowercase.
 */
std::string lowercase(const std::string& input);

/**
 * @brief Converts all characters in the input wide string to lowercase.
 * @param input The wide string to convert.
 * @return A new wide string with all characters in lowercase.
 */
std::wstring lowercase(const std::wstring& input);

/**
 * @brief Converts all characters in the input string to uppercase.
 * @param input The string to convert.
 * @return A new string with all characters in uppercase.
 */
std::string uppercase(const std::string& input);

/**
 * @brief Converts all characters in the input wide string to uppercase.
 * @param input The wide string to convert.
 * @return A new wide string with all characters in uppercase.
 */
std::wstring uppercase(const std::wstring& input);

} // namespace Philips::IGT::A2D::Components::Utility::String
