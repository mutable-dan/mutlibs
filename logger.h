// MIT License
// Copyright (c) 2019 G. Dan
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.


#pragma once

#include <string>
#include <sstream>
#include <atomic>

#include <syslog.h>

namespace mutlib
{

/**
 * @brief logger
 * 
 * @remarks setup logger
 * @code
 * logger::init();
 * logger::level_info();
 * logger::info( "some log message" );
 * ...
 * logger::close();
 * 
 **/
class logger
{
    private:
        logger()  = delete;
        ~logger() = delete;

        static std::atomic<int64_t> g_logMask;

    public:

        static void init( const char* a_pszApp )
        {
            if( nullptr == a_pszApp )
            {
                return;
            }

            setlogmask( LOG_UPTO( LOG_NOTICE ) );
            openlog( a_pszApp, LOG_PID , LOG_DAEMON | LOG_PERROR );
        }


        // set log levels.  logging will proceed up to this level but not before
        static void level_debug()
        {
            setlogmask( LOG_UPTO( LOG_DEBUG ) );
        }

        static void level_info()
        {
            setlogmask( LOG_UPTO( LOG_INFO ) );
        }

        static void level_warning()
        {
            setlogmask( LOG_UPTO( LOG_WARNING ) );
        }

        static void level_error()
        {
            setlogmask( LOG_UPTO( LOG_ERR ) );
        }

        static void level_critical()
        {
            setlogmask( LOG_UPTO( LOG_CRIT ) );
        }

        static void level_fail()
        {
            setlogmask( LOG_UPTO( LOG_ALERT ) );
        }




        // set a log level, for example, level_info()
        // all calls to info and above, (warning, error, etc) will be logged
        // call below, such as debug, will not be logged
        
        static void inline debug( const std::string& a_str )
        {
            syslog( LOG_DEBUG, "%s", a_str.c_str() );
        }
        static void inline debug( const std::stringstream& a_stream )
        {
            syslog( LOG_DEBUG, "%s", a_stream.str().c_str() );
        }
        static void inline debug( const char* a_pszMessage )
        {
            syslog( LOG_DEBUG, "%s", a_pszMessage );
        }



        static void inline info( const std::string& a_str )
        {
            syslog( LOG_INFO, "%s", a_str.c_str() );
        }
        static void inline info( const std::stringstream& a_stream )
        {
            syslog( LOG_INFO, "%s", a_stream.str().c_str() );
        }
        static void inline info( const char* a_pszMessage )
        {
            syslog( LOG_INFO, "%s", a_pszMessage );
        }



        static void inline warning( const std::string& a_str )
        {
            syslog( LOG_WARNING, "%s", a_str.c_str() );
        }
        
        static void inline warning( const std::stringstream& a_stream )
        {
            syslog( LOG_WARNING, "%s", a_stream.str().c_str() );
        }
        
        static void inline warning( const char* a_pszMessage )
        {
            syslog( LOG_WARNING, "%s", a_pszMessage );
        }




        static void inline error( const std::string& a_str )
        {
            syslog( LOG_ERR, "%s", a_str.c_str() );
        }
        
        static void inline error( const std::stringstream& a_stream )
        {
            syslog( LOG_ERR, "%s", a_stream.str().c_str() );
        }
        
        static void inline error( const char* a_pszMessage )
        {
            syslog( LOG_ERR, "%s", a_pszMessage );
        }




        static void inline critical( const std::string& a_str )
        {
            syslog( LOG_CRIT, "%s", a_str.c_str() );
        }
        
        static void inline critical( const std::stringstream& a_stream )
        {
            syslog( LOG_CRIT, "%s", a_stream.str().c_str() );
        }
        
        static void inline critical( const char* a_pszMessage )
        {
            syslog( LOG_CRIT, "%s", a_pszMessage );
        }





        static void inline fail( const std::string& a_str )
        {
            syslog( LOG_ALERT, "%s", a_str.c_str() );
        }
        
        static void inline fail( const std::stringstream& a_stream )
        {
            syslog( LOG_ALERT, "%s", a_stream.str().c_str() );
        }
        
        static void inline fail( const char* a_pszMessage )
        {
            syslog( LOG_ALERT, "%s", a_pszMessage );
        }



        static void close()
        {
            closelog();
        }
};

}
