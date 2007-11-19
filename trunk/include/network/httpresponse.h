#ifndef HTTPRESPONSE_H
#define HTTPRESPONSE_H

#include <string>
#include <vector>
#include <map>

// namespace Utils
// {

  class HTTPResponse
  {
  public:
    HTTPResponse();
    //    HTTPResponse(HTTPResponse& response);
    virtual ~HTTPResponse();

    inline void setStatus(std::string status) {_status=status;}
    inline void setStatusCode(unsigned int code) {_statusCode=code;}
    inline void setVersion(std::string version) {_version=version;}
    inline void addHeader(std::string header) 
    {
      //first we split header name and content
      //by finding the first ':' occurence
      //TODO: remove trailing whitespaces
      std::string::size_type separator_pos = header.find_first_of( ":", 0 ) ; 
      std::string header_name=header.substr(0,separator_pos);
      std::string header_value=header.substr(separator_pos+1,header.length());
      _headers[header_name]=header_value;
    }
    inline void setData(unsigned char* data,unsigned int size) //makes a copy of the data (may be changed???)
    {
      _size=size;
      _data=new unsigned char[size];
      memcpy((void*)_data,(void*)data,size*sizeof(unsigned char));
    }

    inline std::string getStatus() {return _status;}
    inline std::string getVersion() {return _version;}
    inline unsigned int getStatusCode() {return _statusCode;}
    inline std::map<std::string,std::string> getHeaders() {return _headers;}
    inline const char* getHeader(std::string header_name)
    {
      std::map<std::string,std::string>::iterator it=_headers.find(header_name);
      return ((it!=_headers.end())?((*it).second.c_str()):NULL);
    }
    inline std::string getHeaderStringValue(std::string header_name) {return _headers[header_name];}
    inline unsigned int getHeaderIntValue(std::string header_name) 
    {
      unsigned int result;
      sscanf(_headers[header_name].c_str(),"%u",&result);
      return result;
    }
    inline unsigned char* getData() {return _data;}

    inline unsigned int getDataSize() {return _size;}//return data size in bytes

  protected:
  private:
    std::string _status;
    unsigned int _statusCode;
    std::string _version;
    std::map<std::string,std::string> _headers;
    unsigned char*  _data;
    unsigned int _size;
  };

// }//namespace Utils

#endif
