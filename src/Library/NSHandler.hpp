#pragma once
#include <string>
#include <vector>

#include <tao/pegtl.hpp>

namespace usbguard {

  namespace nsswitch {

    struct blanked
      : tao::pegtl::star< tao::pegtl::blank > {};

    struct prop_name
      : tao::pegtl::istring< 'u', 's', 'b', 'g', 'u', 'a', 'r', 'd' > {};

    struct value
      : tao::pegtl::plus< tao::pegtl::alpha > {};

    struct grammar
      : tao::pegtl::must< blanked, prop_name, blanked, tao::pegtl::one< ':' >, blanked, value, blanked, tao::pegtl::eof > {};

    template< typename Rule >
    struct action
      : tao::pegtl::nothing< Rule > {};

    template<> 
    struct action< value >
    {
       template < typename Input >
       static void apply(const Input & in, std::string & str )
       {
          std::locale loc;
          str = in.string();
          for (unsigned i = 0; i < str.length(); ++i)
          {
             str[i] = std::tolower(str[i], loc);
          }
       }
    };
 }

  class NSHandler
    {
      public:

        enum class SourceType
        {
          LOCAL,
          LDAP,
          SSSD
        };

      NSHandler();

      void getRuleset();
      void parseNSSwitch();

      void setNSSwitchPath(const std::string& path);
      void setPropertyName(const std::string& name);

    private:
      std::string _prop_name;
      std::string _nsswitch_path;
      unsigned _num_possible_values;
      std::vector<std::string> _possible_values;

      SourceType _source;


    };
}