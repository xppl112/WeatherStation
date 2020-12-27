#include <Arduino.h>
#include "WiFiEspClient.h"

class RestClient {

  public:
    RestClient(WiFiEspClient* esp, const char* host);
    RestClient(WiFiEspClient* esp, const char* _host, int _port);

    //Generic HTTP Request
    int request(const char* method, const char* path,
                const char* body, String* response);
    // Set a Request Header
    void setHeader(const char*);
    // Set Content-Type Header
    void setContentType(const char*);

    //Set to use a secure connection
    void setSecureConnection(bool secureConn);
    //Set the fingerprint of SSL certificate to use secure connection
    void setFingerprint(const char* fingerPrint);

    // GET path
    int get(const char*);
    // GET path and response
    int get(const char*, String*);

    // POST path and body
    int post(const char* path, const char* body);
    // POST path and body and response
    int post(const char* path, const char* body, String*);

    // PUT path and body
    int put(const char* path, const char* body);
    // PUT path and body and response
    int put(const char* path, const char* body, String*);

    // DELETE path
    int del(const char*);
    // DELETE path and body
    int del(const char*, const char*);
    // DELETE path and response
    int del(const char*, String*);
    // DELETE path and body and response
    int del(const char*, const char*, String*);

  private:
    WiFiEspClient* _esp;
    int readResponse(String*);
    void write(const char*);
    const char* host;
    int port;
    int num_headers;
    const char* headers[10];
    bool use_https;
    const char* fingerprint;
	const char* contentType;
};