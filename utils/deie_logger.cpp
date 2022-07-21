/**
 * @file deie_logger.cpp
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2022-05-03
 * 
 * @copyright Copyright (c) 2022 Deepedge.ai, Inc.
 * 
 */
#include "deie_logger.hpp"
#include <chrono>
#include <ctime>
#include <fstream>
#include <iostream>
#include <map>
#include <mutex>
#include <stdexcept>

#ifdef Q_OS_ANDROID
#include <QDebug>
#endif

namespace deie {

class Logger::Impl
{
public:

    Impl();

    ~Impl();

    std::ostringstream & trace();

    std::ostringstream & debug();

    std::ostringstream & info();

    std::ostringstream & warning();

    std::ostringstream & error();

    std::ostringstream & fatal();

    static void enableEchoMode(bool enable);

    static void setLevelSymbol(Logger::Level level, std::string symbol);

    static void setLoggingLevel(Logger::Level level);

    static void setTimestampMode(Logger::TimestampMode timestampMode, std::string separator);

    static void setStream(Level level, std::ostream & stream);

    static void init(std::string filename, bool append);

    void flush();

    std::ostringstream & getStream(Logger::Level level);

    void prefixTimestamp();

private:

    static bool m_echoMode;

    static Logger::Level m_level;

    static Logger::TimestampMode m_timestampMode;

    static std::string m_timestampSeparator;

    static std::ofstream m_fout;

    using SymbolMap = std::map<Logger::Level, std::string>;
    static SymbolMap m_symbols;

    using StreamMap = std::map<Logger::Level, std::ostream *>;
    static StreamMap m_streams;

    static std::recursive_mutex m_mutex;

    Logger::Level m_activeLevel = Logger::Level::Info;

    std::lock_guard<std::recursive_mutex> m_lock;

    std::ostringstream m_oss;
};

bool Logger::Impl::m_echoMode = true;

Logger::Level Logger::Impl::m_level = Logger::Level::Info;

Logger::TimestampMode Logger::Impl::m_timestampMode = Logger::TimestampMode::DateTime;

std::string Logger::Impl::m_timestampSeparator = ": ";

std::ofstream Logger::Impl::m_fout;

// Default level symbols
Logger::Impl::SymbolMap Logger::Impl::m_symbols = {
    {Logger::Level::Trace,   "Trace:"},
    {Logger::Level::Debug,   "Debug:"},
    {Logger::Level::Info,    "Info:"},
    {Logger::Level::Warning, "Warn:"},
    {Logger::Level::Error,   "Error:"},
    {Logger::Level::Fatal,   "Fatal:"}
};

// Default streams
Logger::Impl::StreamMap Logger::Impl::m_streams = {
    {Logger::Level::Trace,   &std::cout},
    {Logger::Level::Debug,   &std::cout},
    {Logger::Level::Info,    &std::cout},
    {Logger::Level::Warning, &std::cerr},
    {Logger::Level::Error,   &std::cerr},
    {Logger::Level::Fatal,   &std::cerr}
};

std::recursive_mutex Logger::Impl::m_mutex;

Logger::Impl::Impl()
  : m_lock(Logger::Impl::m_mutex)
{
}

Logger::Impl::~Impl()
{
    flush();
}

void Logger::Impl::enableEchoMode(bool enable)
{
    Impl::m_echoMode = enable;
}

std::ostringstream & Logger::Impl::getStream(Logger::Level level)
{
    m_activeLevel = level;
    Impl::prefixTimestamp();
    m_oss << Impl::m_symbols[level] << " ";
    return m_oss;
}

void Logger::Impl::setLevelSymbol(Level level, std::string symbol)
{
    Impl::m_symbols[level] = symbol;
}

void Logger::Impl::setLoggingLevel(Logger::Level level)
{
    Impl::m_level = level;
}

void Logger::Impl::setTimestampMode(TimestampMode timestampMode, std::string separator)
{
    Impl::m_timestampMode = timestampMode;
    Impl::m_timestampSeparator = separator;
}

void Logger::Impl::prefixTimestamp()
{
    std::string timeStr;

    using std::chrono::duration_cast;
    using std::chrono::system_clock;

    switch (Impl::m_timestampMode)
    {
    case Logger::TimestampMode::None:
        break;
    case Logger::TimestampMode::DateTime:
    {
        time_t rawTime;
        time(&rawTime);
        timeStr = ctime(&rawTime);
        timeStr.erase(timeStr.length() - 1);
    }
        break;
    case Logger::TimestampMode::EpochSeconds:
        timeStr = std::to_string(duration_cast<std::chrono::seconds>(system_clock::now().time_since_epoch()).count());
        break;
    case Logger::TimestampMode::EpochMilliseconds:
        timeStr = std::to_string(duration_cast<std::chrono::milliseconds>(system_clock::now().time_since_epoch()).count());
        break;
    case Logger::TimestampMode::EpochMicroseconds:
        timeStr = std::to_string(duration_cast<std::chrono::microseconds>(system_clock::now().time_since_epoch()).count());
        break;
    }

    if (!timeStr.empty())
    {
        m_oss << timeStr << m_timestampSeparator;
    }
}

void Logger::Impl::flush()
{
    if (m_activeLevel < m_level)
    {
        return;
    }

    if (!m_oss.str().size())
    {
        return;
    }

    if (Impl::m_fout.is_open())
    {
        Impl::m_fout << m_oss.str() << std::endl;
        Impl::m_fout.flush();
    }

    if (Impl::m_echoMode)
    {
#ifdef Q_OS_ANDROID
        qDebug() << m_oss.str().c_str();
#else
        auto stream = Impl::m_streams[m_activeLevel];
        if (stream) {
            *stream << m_oss.str() << std::endl;
            stream->flush();
        }
#endif
    }
}

void Logger::Impl::init(std::string filename, bool append)
{
    if (!filename.empty())
    {
        Impl::m_fout.open(filename, append ? std::ofstream::out | std::ofstream::app : std::ofstream::out);
        if (!Impl::m_fout.is_open())
        {
            throw std::runtime_error("ERROR!!: Couldn't open '" + filename + "' for write.\n");
        }
    }
}

std::ostringstream & Logger::Impl::trace()
{
    return getStream(Logger::Level::Trace);
}

std::ostringstream & Logger::Impl::debug()
{
    return getStream(Logger::Level::Debug);
}

std::ostringstream & Logger::Impl::info()
{
    return getStream(Logger::Level::Info);
}

std::ostringstream & Logger::Impl::warning()
{
    return getStream(Logger::Level::Warning);
}

std::ostringstream & Logger::Impl::error()
{
    return getStream(Logger::Level::Error);
}

std::ostringstream & Logger::Impl::fatal()
{
    return getStream(Logger::Level::Fatal);
}

void Logger::Impl::setStream(Level level, std::ostream & stream)
{
    Logger::Impl::m_streams[level] = &stream;
}

Logger::Logger()
    : m_impl(new Logger::Impl)
{
}

void Logger::init(std::string filename, bool append)
{
    Impl::init(filename, append);
}

void Logger::enableEchoMode(bool enable)
{
    Impl::enableEchoMode(enable);
}

void Logger::setLoggingLevel(Level level)
{
    Impl::setLoggingLevel(level);
}

void Logger::setLevelSymbol(Level level, std::string symbol)
{
    Impl::setLevelSymbol(level, symbol);
}

void Logger::setTimestampMode(TimestampMode timestampMode, std::string separator)
{
    Impl::setTimestampMode(timestampMode, separator);
}

void Logger::setStream(Level level, std::ostream & stream)
{
    Impl::setStream(level, stream);
}

std::ostringstream & Logger::trace()
{
    return m_impl->trace();
}

std::ostringstream & Logger::debug()
{
    return m_impl->debug();
}

std::ostringstream & Logger::info()
{
    return m_impl->info();
}

std::ostringstream & Logger::warning()
{
    return m_impl->warning();
}

std::ostringstream & Logger::error()
{
    return m_impl->error();
}

std::ostringstream & Logger::fatal()
{
    return m_impl->fatal();
}

std::string Logger::version()
{
    return "1.4.0";
}

Logger::~Logger() = default;

} // deie
