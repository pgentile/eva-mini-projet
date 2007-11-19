#ifndef HTTPREQUEST_H
#define HTTPREQUEST_H

#include <string>

// namespace Utils
// {
  
  class HTTPRequest
  {
  public:
    HTTPRequest();
    HTTPRequest(std::string uri, std::string method,std::string version="HTTP/1.0");
    virtual ~HTTPRequest();
    
    
    inline std::string getURI() const {return _uri;}
    inline std::string getMethod() const {return _method;}
    inline std::string getVersion() const {return _version;}

    inline void setURI(std::string uri) {_uri=uri;}
    inline void setMethod(std::string method) {_method=method;}
    inline void setVersion(std::string version) {_version=version;}
  
  protected:
  private:
    std::string _uri,_method,_version;
  
  };
  
//}//namespace Utils

#endif
