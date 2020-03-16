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

/*
 * read a config text file as name value pairs into assoc ontainer
 * use # to make comment
 * 
 */

#include <map>
#include <string>
#include <exception>
#include <boost/lexical_cast.hpp>

namespace mutlib
{
    using config_t = std::map< std::string, std::string >;


    class config final
    {
        private:
            config_t m_mapConfig;
            
        public:
            config() : m_mapConfig( config_t() ) {}
            config( const config& )  = delete;
            ~config() {}
            
            config& operator=   ( const config& ) = delete;
            bool    operator==  ( const config& ) = delete;

            bool read( std::string a_strConfigFileName );
            bool get ( std::string a_strName, std::string& a_strValue );
            
            template< typename T > bool get( std::string a_strName, T& value )
            {
                auto iter = m_mapConfig.find( a_strName );
                if( iter == m_mapConfig.end() )
                {
                    return false;
                }
                try
                {
                    value = boost::lexical_cast<T>( iter->second );
                } catch( std::exception& e )
                {
                    // log the error
                    return false;
                }
                
                return true;
            }

    };
}

