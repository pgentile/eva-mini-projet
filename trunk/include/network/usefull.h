#ifndef USEFULL_H
#define USEFULL_H

#include <vector>
#include <string>

//usefull macros
#ifndef MAX
#define MAX(a,b)      ((a<b)?(b):(a))
#endif

#ifndef MIN
#define MIN(a,b)      ((a>b)?(b):(a))
#endif

#ifndef CELL
#define CELL(a,max)   ((a<max)?(a):(max))
#endif

#ifndef FLOOR
#define FLOOR(a,min)  ((a<min)?(min):(a))
#endif

#ifndef ABS
#define ABS(x)        ((x<0)?-(x):(x))
#endif

#ifndef POS
#define POS(x)        ((x<0)?(0):(x))
#endif

#ifndef SQRDIST
#define SQRDIST(x0,y0,x1,y1) ((x1-x0)*(x1-x0)+(y1-y0)*(y1-y0))
#endif

#ifndef OVERLAPS
#define OVERLAPS(x0,y0,x1,y1,x2,y2,x3,y3) ((!(((x0)<(x2) && (x1)<(x2))	\
					      || ((x0)>(x3) && (x1)>(x3)) \
					      || ((y0)<(y2) && (y1)<(y2)) \
					      || ((y0)>(y3) && (y1)>(y3)))))
#endif

//usefull functions
class Utils
{
 public:

  static std::vector<std::string> split_string(std::string& str,std::string delimiters)
    {
      std::vector<std::string> splited_str;//splited string

      // Skip delimiters at beginning.
      std::string::size_type lastPos = str.find_first_not_of( delimiters, 0 );

      // Find first "non-delimiter".
      std::string::size_type pos = str.find_first_of( delimiters, lastPos ) ; 
      
      while ( std::string::npos != pos || std::string::npos != lastPos )
	{
	  // Found a token, add it to the vector.
	  splited_str.push_back( str.substr( lastPos, pos - lastPos ) );
	  // Skip delimiters.  Note the "not_of"
	  lastPos = str.find_first_not_of( delimiters, pos );
	  // Find next "non-delimiter"
	  pos = str.find_first_of( delimiters, lastPos ) ;
	}

      return splited_str;
    }



};







#endif
