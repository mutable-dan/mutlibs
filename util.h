#pragma once
	
#include <string>
#include <vector>


namespace mutlib 
{

   /**
   * @brief 
   * 
   */
   class splitString
   {
      public:
         typedef std::vector<std::string> stringsplit_t;
      private:
         stringsplit_t m_vElements; 
         char          m_cDelim;
         uint32_t      m_unPos;
         

   public:
         
      const stringsplit_t&    split( const char* a_psz, const char* a_pcDelim );
      const stringsplit_t&    split( const std::string& a_str, const char* a_pcDelim );
      const std::string       operator[] ( const uint32_t a_nIndex ) const;
      int32_t                 count() const;
      void                    clear() { m_vElements.clear(); }
   };

}
