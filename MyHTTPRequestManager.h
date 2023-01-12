#pragma once
#include <cstddef>
#include <string>
#include <curl/curl.h>
#include <json/json.h>
#include <iostream>
#include <memory>

using namespace std;


class HTTPRequestManager {
private:
    CURL* curl;
    
    // Request Info
    string _url;

    // Response information.
    int httpCode;
    //static std::unique_ptr<std::string> _httpData;

   /*struct memory {
    char* response;
    size_t size;
};*/

public: 
    /*static size_t curl_write(char* wd, size_t size, size_t nmemb, string *stream) {
        size_t actualSize = size * nmemb;
        _httpData.append(wd, actualSize);
        return 0;
    }*/
    //struct memory chunk = { 0 };
    /*static size_t callback(const char* in, size_t size, size_t num, string* out) {
        cout << "CALLBAVCK ";
        const std::size_t totalBytes(size * num);
        out->append(in, totalBytes);
        return totalBytes;
    }*/

    
    static size_t CurlWrite_CallbackFunc_StdString(void* contents, size_t size, size_t nmemb, std::string* s) {
        size_t newLength = size * nmemb;
        try {
            s->append((char*)contents, newLength);
        }
        catch (std::bad_alloc& e) {
            //handle memory problem
            return 0;
        }
        return newLength;
    }
    //static size_t cb(void* data, size_t size, size_t nmemb, void* userp) {
    //    cout << "DSADASDSADASDAS";
    //    size_t realsize = size * nmemb;
    //    struct memory* mem = (struct memory*)userp;

    //    char* ptr = (char *) realloc(mem->response, mem->size + realsize + 1);
    //    if (ptr == NULL)
    //        return 0;  /* out of memory! */

    //    mem->response = ptr;
    //    memcpy(&(mem->response[mem->size]), data, realsize);
    //    mem->size += realsize;
    //    mem->response[mem->size] = 0;

    //    return realsize;
    //}
    void setupHandler();
    void setGETType();
    HTTPRequestManager();
    void setUrl(std::string url);
    void setJSONDocument(Json::Value jsonDoc);
    Json::Value createJSONDocument();
    Json::Value getJSONResult();
    void performRequest();
    void printJSONResult();

    static std::string httpData;
    Json::Value jsonData;
};
