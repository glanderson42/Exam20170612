#include <iostream>
#include <string>
#include "cmmap.h"
#include <algorithm>
#include <set>
#include "cmmap.h"

struct increment
{

  int operator()( int i ) const
  {
    return i + 1;
  }

};


struct value
{

  int operator()( int ) const
  {
    return -1;
  }

};


struct append
{

  std::string operator()( const std::string& s ) const
  {
    return s + "!";
  }

};

struct string_size_less: std::binary_function<std::string, std::string, bool>
{

  bool operator()( const std::string& a, const std::string& b ) const
  {
    return a.size() < b.size();
  }

};

const int max = 1024;

int main()
{
  int your_mark = 1;
  // 2-es
  convenient_multimap<int, int> m;
  for( int i = 0; i < max; ++i )
  {
    m.add( i % 2, i );
  }
  m.update_key( 1, 2 );
  const convenient_multimap<int, int> cm = m;

  convenient_multimap<std::string, std::string> s;
  s.add( "Hello", "World" );
  const convenient_multimap<std::string, std::string> cs = s;
  s.update_key( "Hello", "Hi" );

  if ( &std::multimap<int,int>::size != &convenient_multimap<int,int>::size )
  {
    std::cerr << "Use inheritence!";
  }
  else
  {
    if ( "World" == cs.front() && 0 == cm.front() % 2 &&
         1U == s.size() && 1U * max == cm.size() &&
         max / 2 == cm.count( 2 ) && max / 2 == cm.count( 0 ) )
    {
      your_mark = s.begin()->first.size();
    }
  }
  
  // 3-as
  s.back() = "C++";
  m.front() = max;
  m.back() = max;

  if ( m.front() == m.back() && cm.front() != m.front() &&
       "C++" == s.front() && max / 2 == m.count( your_mark ) )
  {
    your_mark = s.back().size();
  }
  
  // 4-es
  convenient_multimap<int, int> mm = m;
  m.transform_keys( increment() );
  mm.transform_keys( value() );
  mm.update_key( -1, 1 );

  s.transform_keys( append() );

  if ( mm.size() == mm.count( 1 ) && max / 2 == m.count( your_mark ) &&
       0 == s.count( "Hi" ) && 0 == mm.count( -1 ) )
  {
    your_mark = s.begin()->first.size() + s.size();
  }
  
  // 5-os
  convenient_multimap<std::string, std::string, string_size_less> langs;
  langs.add( "C++", "awesome" );
  langs.add( "C++", "cool" );
  langs.add( "C++", ":-)" );
  langs.add( "C++", "<3" );
  langs.add( "C++", "fine" );
  langs.add( "Scala", "weird" );
  langs.add( "Java", "NullPointerException" );
  langs.add( "JavaScript", "Kernel Panic" );
  langs.add( "Pascal", "Simple" );
  langs.update_key( "Pascal", "Python" );
  langs.update_key( "Cobol", "Haskell" );
  langs.update_key( "Perl", "C#" );

  const std::multiset<std::string, string_size_less> sl = langs;
  const std::multiset<int> ms = cm;

  if ( 1 == langs.count( "C#" ) && 0 == langs.count( "Java" ) &&
       1 == langs.count( "Pascal" ) && "Kernel Panic" == langs.back() &&
       5 == sl.count( "Ada" ) && sl.size() == langs.size() &&
       1U * max == ms.size() && 1U == sl.count( "Prolog" ) )
  {
    your_mark = langs.count( "C++" );
  }
  
  std::cout << "Your mark is " << your_mark;
  std::endl( std::cout );
}
