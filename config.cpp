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


#include "config.h"
#include <string>
#include <vector>
#include <sstream>
#include <boost/filesystem.hpp>
#include <boost/filesystem/fstream.hpp>
#include <boost/algorithm/string/trim.hpp>
#include <boost/algorithm/string/split.hpp>

#include "logger.h"

using namespace std;

namespace mutlib 
{


    /**
     * @brief read nME VALUE Pirs from config file, store in assoc container
     * 
     * use # to comment line out
     * 
     * @param a_strConfigFileName path to config
     * @return true if file config file is opened, else false
     */
    bool config::read( std::string a_strConfigFileName )
    {
        //config_t m_mapConfig;
        boost::filesystem::path pthConfig( a_strConfigFileName );
        if( boost::filesystem::exists( pthConfig ) )
        {
            boost::filesystem::ifstream inConfig;
            inConfig.open( pthConfig );
            
            string strLine;
            while( inConfig )
            {
                std::getline( inConfig, strLine );
                
                if( strLine.length() == 0 ) 
                {
                    continue;
                }
                
                if( strLine[0] == '#' )
                {
                    continue;
                }
                
                
                boost::algorithm::trim_left( strLine );
                boost::algorithm::trim_right( strLine );

                vector<string> vNameVal;
                boost::algorithm::split( vNameVal, strLine, boost::is_any_of( "=" ) );
                if( vNameVal.size() != 2 )
                {
                    // log error
                    stringstream sstr;
                    sstr << "error: name value pair not found, usage: name=value, found " << strLine;
                    logger::error( sstr );
                } else
                {
                    auto it = m_mapConfig.find( vNameVal[0] );
                    if( it == m_mapConfig.end() )
                    {
                        // this config entry will be stored
                        stringstream sstr;
                        sstr << "ok: value stored " << strLine;
                        logger::info( sstr );
                        m_mapConfig[ vNameVal[0] ] = vNameVal[1];   // more efficient if you use existing iterator
                    } else
                    {
                        // log duplicate config entry, ignoring
                        stringstream sstr;
                        sstr << "name value pair duplicate " << strLine;
                        logger::warning( sstr );                        
                    }
                }
            }
            return true;
        }        
        return false;
    }
    
    
    bool config::get ( string a_strName, string& a_strValue )
    {
        auto iter = m_mapConfig.find( a_strName );
        if( iter == m_mapConfig.end() )
        {
            return false;
        }
        a_strValue = iter->second;
        
        return true;
    }

}

