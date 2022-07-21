/**
 * @file deie_logger.hpp
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2022-05-03
 * 
 * @copyright Copyright (c) 2022 Deepedge.ai, Inc.
 * 
 */
#ifndef DEIE_LOGGER_HPP
#define DEIE_LOGGER_HPP

#include <cstdio>
#include <memory>
#include <sstream>

namespace deie {

/*!
 * Example initialization:
 *
 * using deie::L;
 *
 * L::init("myLog.txt");
 *
 * Example logging:
 *
 * L().info() << "Initialization finished.";
 * L().error() << "Foo happened!";
 */
class Logger
{
public:
    enum class Level
    {
        Trace,
        Debug,
        Info,
        Warning,
        Error,
        Fatal,
        None
    };

    enum class TimestampMode
    {
        None,
        DateTime,
        EpochSeconds,
        EpochMilliseconds,
        EpochMicroseconds
    };

    //! Constructor.
    Logger();

    //! Destructor.
    ~Logger();

    /*! Initialize the logger.
     *  \param filename Log to filename. Disabled if empty.
     *  \param append The existing log will be appended if true.
     *  Throws on error. */
    static void init(std::string filename, bool append = false);

    //! Enable/disable echo mode.
    //! \param enable Echo everything if true. Default is false.
    static void enableEchoMode(bool enable);

    //! Set the logging level.
    //! \param level The minimum level. Default is Info.
    static void setLoggingLevel(Level level);

    //! Set custom symbol for the given logging level.
    //! \param level The level.
    //! \param symbol The symbol outputted for the messages of this level.
    static void setLevelSymbol(Level level, std::string symbol);

    //! Set/enable timestamp mode.
    //! \param timestampMode Timestamp mode enumeration.
    //! \param separator Separator string outputted after timestamp.
    static void setTimestampMode(TimestampMode timestampMode, std::string separator = " ");

    //! Set specific stream.
    //! \param level The level.
    //! \param stream The output stream.
    static void setStream(Level level, std::ostream & stream);

    //! \return Library version in x.y.z
    static std::string version();

    //! Get stream to the trace log message.
    std::ostringstream & trace();

    //! Get stream to the debug log message.
    std::ostringstream & debug();

    //! Get stream to the info log message.
    std::ostringstream & info();

    //! Get stream to the warning log message.
    std::ostringstream & warning();

    //! Get stream to the error log message.
    std::ostringstream & error();

    //! Get stream to the fatal log message.
    std::ostringstream & fatal();

private:
    Logger(const Logger & r) = delete;
    Logger & operator=(const Logger & r) = delete;

    class Impl;
    std::unique_ptr<Impl> m_impl;
};

using L = Logger;

} // deie

#endif // DEIE_LOGGER_HPP
