#ifndef HTTPCLIENT_H
#define HTTPCLIENT_H

#include "httprequest.h"
#include "httpresponse.h"
#include "tcpsocket.h"

// namespace Utils
// {
//Base64 encoding functions from http://www.kbcafe.com/articles/HowTo.Base64.pdf
//The code has been modified here since we just need to encode strings (not binary streams as in the example)
//Here we handle HTTP (and related) base64 encoding, there may be differences 
//in implementation for the last two characters
class Base64
{
public:
  //Encode one character to base64
  static inline char encode(unsigned char uc)
  {
    if (uc < 26)
      {
	return 'A'+uc;
      }
    if (uc < 52)
      {
	return 'a'+(uc-26);
      }
    if (uc < 62)
      {
	return '0'+(uc-52);
      }
    if (uc == 62)
      {
	return '+';
      }
    return '/';
  }
  //Decode a character from base64
  static inline unsigned char decode(char c)
  {
    if (c >= 'A' && c <= 'Z')
      {
	return c - 'A';
      }
    if (c >= 'a' && c <= 'z')
      {
	return c - 'a' + 26;
      }
    if (c >= '0' && c <= '9')
      {
	return c - '0' + 52;
      }
    if (c == '+')
      {
	return 62;
      };
    return 63;
  }
  //True if the character is in base64
  static inline bool isBase64(char c)
  {
    if (c >= 'A' && c <= 'Z')
      {
	return true;
      }
    if (c >= 'a' && c <= 'z')
      {
	return true;
      }
    if (c >= '0' && c <= '9')
      {
	return true;
      }
    if (c == '+')
      {
	return true;
      };
    if (c == '/')
      {
	return true;
      };
    if (c == '=')
      {
	return true;
      };
    return false;
  }

  static inline std::string encode(const std::string& vby)
  {
    //The returned encoded string
    std::string retval;
    
    if (vby.size() == 0)//If there's nothing to encode then return an empty string
      {
	return retval;
      };
    //Go through all data
    for (unsigned int i=0;i<vby.size();i+=3)
      {
	//Read bytes by group of 3 (3*8=24=6*4)
	unsigned char by1=0,by2=0,by3=0;
	by1 = vby[i];
	if (i+1<vby.size())
	  {
	    by2 = vby[i+1];
	  };
	if (i+2<vby.size())
	  {
	    by3 = vby[i+2];
	  }
	//Then convert to 4 6-bit values
	unsigned char by4=0,by5=0,by6=0,by7=0;
	by4 = by1>>2;
	by5 = ((by1&0x3)<<4)|(by2>>4);
	by6 = ((by2&0xf)<<2)|(by3>>6);
	by7 = by3&0x3f;
	//Then encode each 6-bits byte into base64
	retval += encode(by4);
	retval += encode(by5);
	if (i+1<vby.size())
	  {
	    retval += encode(by6);
	  }
	else
	  {
	    retval += "=";
	  };
	if (i+2<vby.size())
	  {
	    retval += encode(by7);
	  }
	else
	  {
	    retval += "=";
	  };
	//The following is to be human readable (max 76 base64 characters in a line)
	//We don't need this in our HTTP code
	// 	if (i % (76/4*3) == 0)
	// 	  {
	// 	    retval += "\r\n";
	// 	  }
	
      };
    return retval;
  }

  static inline std::string decode(const std::string & _str)
  {
    std::string str;
    for (unsigned int j=0;j<_str.length();j++)
      {
	if (isBase64(_str[j]))
	  {
	    str += _str[j];
	  }
      }
    std::string retval="";
    if (str.length() == 0)
      {
	return retval;
      }
    for (unsigned int i=0;i<str.length();i+=4)
      {
	char c1='A',c2='A',c3='A',c4='A';
	c1 = str[i];
	if (i+1<str.length())
	  {
	    c2 = str[i+1];
	  };
	if (i+2<str.length())
	  {
	    c3 = str[i+2];
	  };
	if (i+3<str.length())
	  {
	    c4 = str[i+3];
	  };
	unsigned char by1=0,by2=0,by3=0,by4=0;
	by1 = decode(c1);
	by2 = decode(c2);
	by3 = decode(c3);
	by4 = decode(c4);
	retval+= ( (by1<<2)|(by2>>4) );
	if (c3 != '=')
	  {
	    retval+= ( ((by2&0xf)<<4)|(by3>>2) );
	  }
	if (c4 != '=')
	  {
	    retval+= ( ((by3&0x3)<<6)|by4 );
	  };
      };
    return retval;
  }

};
  
/**
   HTTPClient class.
   Handle connection and request to an HTTP server
   FIXME: handle non blocking I/O
*/
class HTTPClient
{
public:
  HTTPClient();
  virtual ~HTTPClient();
    
 
  inline void setProxy(std::string host,unsigned short port)
  {
    _proxyHost=host;
    _proxyPort=port;
  }
    
  virtual HTTPResponse* request(HTTPRequest& request);

  virtual HTTPResponse* getDataPart();//For multipart content type

  inline bool isReady()
  {
    return _socket.isReady();
  }

  inline void disconnect() {_socket.disconnect();}

  inline void setAuthentication(std::string username,std::string passwd)
  {
    std::string tmp_str=username;
    tmp_str+=":";
    tmp_str+=passwd;
    _authentication=Base64::encode(tmp_str);
  }
    
protected:
  virtual void connect(std::string host,unsigned short port);
    
private:
  std::string _host,_proxyHost;
  unsigned short _port,_proxyPort;
  TCPSocket _socket;
  //For basic authentication support
  //TODO: This should probably go into HTTPRequest 
  //TODO: but this should work anyway
  std::string _authentication;
  //Multipart support
  std::string _boundary;
  bool _multipart;
};

//}//namespace Utils

#endif
