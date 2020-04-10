#include "util.h"
#include <sstream>

   
using namespace std;

const mutlib::splitString::stringsplit_t& mutlib::splitString::split( const char* a_psz, const char* a_pcDelim )
{
   return split( string( a_psz ), a_pcDelim );
}


const mutlib::splitString::stringsplit_t& mutlib::splitString::split( const string& a_str, const char* a_pcDelim )
{
   m_vElements.clear();
   m_unPos = a_str.find_first_of( a_pcDelim ) + 1;
   if( 0 == m_unPos )
   {
      m_vElements.push_back( a_str );
      return m_vElements; // if no delim, then return string
   }
   stringstream ss( a_str );
   string str;
   while( getline( ss, str, *a_pcDelim ) )
   {
      m_vElements.push_back( str );
   }
   return m_vElements;
}


const string mutlib::splitString::operator[] ( const uint32_t a_nIndex ) const
{
   if( m_vElements.empty() )
   {
      return string();
   }
   if( a_nIndex <= m_vElements.size() )
      return m_vElements[a_nIndex];
   else
      return string();
}


/**
 * @brief return the number of elements in split
 * 
 * @return int32_t
 */
int32_t mutlib::splitString::count() const
{
   return m_vElements.size();
}
