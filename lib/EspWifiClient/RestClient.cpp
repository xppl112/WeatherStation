#include "RestClient.h"
#include "WiFiEspClient.h"

#ifdef HTTP_DEBUG
#define HTTP_DEBUG_PRINT(string) (Serial.print(string))
#endif

#ifndef HTTP_DEBUG
#define HTTP_DEBUG_PRINT(string)
#endif

RestClient::RestClient(WiFiEspClient* esp, const char* _host){
  host = _host;
  port = 80;
  num_headers = 0;
  contentType = "application/x-www-form-urlencoded";	// default
  use_https = false;
  fingerprint = "";
  _esp = esp;
}

RestClient::RestClient(WiFiEspClient* esp, const char* _host, int _port){
  host = _host;
  port = _port;
  num_headers = 0;
  contentType = "application/x-www-form-urlencoded";	// default
  use_https = false;
  fingerprint = "";
  _esp = esp;
}

// GET path
int RestClient::get(const char* path){
  return request("GET", path, NULL, NULL);
}

//GET path with response
int RestClient::get(const char* path, String* response){
  return request("GET", path, NULL, response);
}

// POST path and body
int RestClient::post(const char* path, const char* body){
  return request("POST", path, body, NULL);
}

// POST path and body with response
int RestClient::post(const char* path, const char* body, String* response){
  return request("POST", path, body, response);
}

// PUT path and body
int RestClient::put(const char* path, const char* body){
  return request("PUT", path, body, NULL);
}

// PUT path and body with response
int RestClient::put(const char* path, const char* body, String* response){
  return request("PUT", path, body, response);
}

// DELETE path
int RestClient::del(const char* path){
  return request("DELETE", path, NULL, NULL);
}

// DELETE path and response
int RestClient::del(const char* path, String* response){
  return request("DELETE", path, NULL, response);
}

// DELETE path and body
int RestClient::del(const char* path, const char* body ){
  return request("DELETE", path, body, NULL);
}

// DELETE path and body with response
int RestClient::del(const char* path, const char* body, String* response){
  return request("DELETE", path, body, response);
}

void RestClient::write(const char* string){
  HTTP_DEBUG_PRINT(string);
  if(use_https) {
    _esp->print(string);
  } else {
    _esp->print(string);
  }
}

void RestClient::setHeader(const char* header){
  headers[num_headers] = header;
  num_headers++;
}

void RestClient::setContentType(const char* contentTypeValue){
  contentType = contentTypeValue;
}

void RestClient::setSecureConnection(bool secureConn){
  use_https = secureConn;
}

// Use web browser to view and copy
// SHA1 fingerprint of the certificate
// EX: CF 05 98 89 CA FF 8E D8 5E 5C E0 C2 E4 F7 E6 C3 C7 50 DD 5C
void RestClient::setFingerprint(const char* fingerPrint){
  fingerprint = fingerPrint;
}

// The mother- generic request method.
//
int RestClient::request(const char* method, const char* path,
                  const char* body, String* response){

  HTTP_DEBUG_PRINT("HTTP: connect\n");

  if(use_https) {
    //Secure connection
    if(!_esp->connectSSL(host, port)){
      HTTP_DEBUG_PRINT("HTTPS Connection failed\n");
      return 0;
    }
/*
    if (_esp.verify(fingerprint, host)) {
      HTTP_DEBUG_PRINT("SSL fingerprint certificate matches!");
    } else {
      HTTP_DEBUG_PRINT("SSL fingerprint certificate doesn't match!");
      return 0;
    }
*/
  } else {
    //Normal connection
    if(!_esp->connect(host, port)){
      HTTP_DEBUG_PRINT("HTTP Connection failed\n");
      return 0;
    }
  }

  HTTP_DEBUG_PRINT("HTTP: connected\n");
  HTTP_DEBUG_PRINT("REQUEST: \n");

  // Make a HTTP request line:
  write(method);
  write(" ");
  write(path);
  write(" HTTP/1.1\r\n");
  for(int i=0; i<num_headers; i++){
    write(headers[i]);
    write("\r\n");
  }
  write("Host: ");
  write(host);
  write("\r\n");
  write("Connection: close\r\n");

  if(body != NULL){
    char contentLength[30];
    sprintf(contentLength, "Content-Length: %d\r\n", strlen(body));
    write(contentLength);

  write("Content-Type: ");
  write(contentType);
  write("\r\n");
  }

  write("\r\n");

  if(body != NULL){
    write(body);
    write("\r\n");
    write("\r\n");
  }

  //make sure you write all those bytes.
  delay(100);

  HTTP_DEBUG_PRINT("HTTP: call readResponse\n");
  int statusCode = readResponse(response);
  HTTP_DEBUG_PRINT("HTTP: return readResponse\n");

  //cleanup
  HTTP_DEBUG_PRINT("HTTP: stop client\n");
  num_headers = 0;

  if(use_https) {
    _esp->stop();
  } else {
    _esp->stop();
  }

  delay(50);
  HTTP_DEBUG_PRINT("HTTP: client stopped\n");

  return statusCode;
}

int RestClient::readResponse(String* response) {

  // an http request ends with a blank line
  boolean currentLineIsBlank = true;
  boolean httpBody = false;
  boolean inStatus = false;

  boolean isPayload = false;
  int payloadBytesLeft = 0;
  String payloadLength;

  char statusCode[4];
  int i = 0;
  int code = 0;

  //Normal connection
  if(response == NULL){
    HTTP_DEBUG_PRINT("HTTP: NULL RESPONSE POINTER: \n");
  }else{
    HTTP_DEBUG_PRINT("HTTP: NON-NULL RESPONSE POINTER: \n");
  }

  HTTP_DEBUG_PRINT("HTTP: RESPONSE: \n");
  while (_esp->connected()) {
    HTTP_DEBUG_PRINT(".");

    if (_esp->available()) {
      HTTP_DEBUG_PRINT(",");

      char c = _esp->read();
      HTTP_DEBUG_PRINT(c);

      if(c == ' ' && !inStatus){
        inStatus = true;
      }

      if(inStatus && i < 3 && c != ' '){
        statusCode[i] = c;
        i++;
      }
      if(i == 3){
        statusCode[i] = '\0';
        code = atoi(statusCode);
      }

      if(httpBody){
        //only write response if its not null
        if(response != NULL){
          /*if(!isPayload){
            if (c == '\r')continue;
            else if (c == '\n'){
              isPayload = true;
              payloadBytesLeft = atoi(payloadLength.c_str());              
            }
            else payloadLength+=c;
          }
          else if(isPayload && payloadBytesLeft > 0){*/
            response->concat(c);
          /*  payloadBytesLeft--;
          }*/
        }
      }
      else
      {
          if (c == '\n' && currentLineIsBlank) {
            httpBody = true;
          }

          if (c == '\n') {
            // you're starting a new line
            currentLineIsBlank = true;
          }
          else if (c != '\r') {
            // you've gotten a character on the current line
            currentLineIsBlank = false;
          }
      }
    }
  }

  HTTP_DEBUG_PRINT("HTTP: return readResponse3\n");
  return code;  
}