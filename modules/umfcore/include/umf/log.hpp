/* 
 * Copyright 2015 Intel(r) Corporation
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http ://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */

#ifndef __UMF_LOG_H__
#define __UMF_LOG_H__

#include <string>

#include "config.hpp"

/*!
* \file log.hpp
* \brief Logging framework of Video Metadata Framework
*/

namespace umf
{
/*! 
 * \brief Verbosity level of a Logger
 */
enum LogLevel
{
    LOG_INFO,       /*!< Information message. Least importance */
    LOG_WARNING,    /*!< Warning message */
    LOG_ERROR,       /*!< Error message. The most important */
    LOG_NO_MESSAGE  /*!< Use as verbosity level in case you want to omit all log messages */
};

#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable: 4251)
#endif

/*!
 * \brief Log is responsible for logging error, warning and info messages
 * \details Log builds message with using given parameters and writes them. 
 * You can choose a file or the console to write messages.
 */
class UMF_EXPORT Log
{
public:
     /*!
     * \brief Build message and write it to the file or to the console
     * \param[in] level Logging level. There is three possible values of this parameter: 
     * LOG_INFO, LOG_WARNING, LOG_ERROR
     * \param[in] _msg A format string that follows the same specifications as format in printf
     * \param[in] func Function where method was called
     * \param[in] file File where method was called
     * \param[in] line Line where method was called
     * \param[in] ... Parameters for the format string msg
     */
    static void log(LogLevel level, const std::string &_msg, const std::string &func, const std::string &file, int line, ...);

    /*!
     * \brief Redirect log messages to the file
     * \param[in] file Path to the log file
     */
    static void logToFile(const std::string &file); 

    /*!
     * \brief Redirect log messages to the console
     */
    static void logToConsole();

    /*!
     * \brief Set verbosity level
     * \details All messages with level less than verbosity level will be ignored
     * \param[in] level Verbosity level
     */
    static void setVerbosityLevel(LogLevel level);

    /*!
     * \brief Get verbosity level  
     * \return Verbosity level
     */
    static LogLevel getVerbosityLevel();

protected:

private:
    static void writeMessageToFile(const std::string &msg);
    static void writeMessageToConsole(const std::string &msg);

    static std::string logFile;
    static bool writeToFile;
    static LogLevel verbosityLevel;
};

#ifdef _MSC_VER
#pragma warning(pop)
#endif

/*!
 * \brief Log message with given level
 */
#ifdef __GNUC__
#define UMF_LOG(level, msg, ...) umf::Log::log(level, msg, __func__, __FILE__, __LINE__, ##__VA_ARGS__)
#else
#define UMF_LOG(level, msg, ...) umf::Log::log(level, msg, "", __FILE__, __LINE__, ##__VA_ARGS__)
#endif

/*!
 * \brief Log info message
 */
#define UMF_LOG_INFO(msg, ...) UMF_LOG(umf::LOG_INFO, msg, ##__VA_ARGS__)

/*!
 * \brief Log warning message
 */
#define UMF_LOG_WARNING(msg, ...) UMF_LOG(umf::LOG_WARNING, msg, ##__VA_ARGS__)

/*!
 * \brief Log error message
 */
#define UMF_LOG_ERROR(msg, ...) UMF_LOG(umf::LOG_ERROR, msg, ##__VA_ARGS__)

/*!
 * \brief Redirects log messages to the file
 */
#define UMF_LOG_TO_FILE(file) Log::logToFile(file)

/*!
 * \brief Redirects log messages to the console
 */
#define UMF_LOG_TO_CONSOLE() Log::logToConsole()

/*!
 * \brief Sets verbosity level, all messages with level less than verbosity level will be ignored
 */
#define UMF_LOG_VERBOSITY_LEVEL(level) Log::setVerbosityLevel(level)

};
/** @}*/
#endif
