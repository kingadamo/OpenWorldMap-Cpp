#include "MyHTTPRequestManager.h"



HTTPRequestManager::HTTPRequestManager() {
    // Don't bother trying IPv6, which would increase DNS resolution time.
    curl_global_init(CURL_GLOBAL_DEFAULT);
    this->curl = curl_easy_init();
    curl_easy_setopt(curl, CURLOPT_IPRESOLVE, CURL_IPRESOLVE_V4);
    // Don't wait forever, time out after 10 seconds.
    curl_easy_setopt(curl, CURLOPT_TIMEOUT, 10);
    // Follow HTTP redirects if necessary.
    //curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);

    this->httpCode = 0;
   /* std::unique_ptr<std::string> newHttpData(new std::string());
    this->_httpData = std::move(newHttpData);*/

    // Hook up data handling function.
    //curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, HTTPRequestManager::callback);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, HTTPRequestManager::CurlWrite_CallbackFunc_StdString);
    // Hook up data container (will be passed as the last parameter to the
    // callback handling function).  Can be any pointer type, since it will
    // internally be passed as a void pointer.
    //curl_easy_setopt(curl, CURLOPT_WRITEDATA, this->_httpData.get()->c_str());
    /* send all data to this function  */
    //curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, HTTPRequestManager::cb);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &httpData);
    /* we pass our 'chunk' struct to the callback function */
    //curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void*)&chunk);
}

void HTTPRequestManager::setupHandler() {
    curl_global_init(CURL_GLOBAL_DEFAULT);
    this->curl = curl_easy_init();

    curl_easy_setopt(curl, CURLOPT_IPRESOLVE, CURL_IPRESOLVE_V4);
    curl_easy_setopt(curl, CURLOPT_TIMEOUT, 10);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, HTTPRequestManager::CurlWrite_CallbackFunc_StdString);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &httpData);
    httpData = "";

}

void HTTPRequestManager::setUrl(std::string url) {
    setupHandler();

    _url = url;

    // Set remote URL.
    curl_easy_setopt(curl, CURLOPT_URL, _url.c_str());
}

Json::Value HTTPRequestManager::createJSONDocument(){
    Json::Value jsonDoc;
    Json::Value jsonMatrix;
    Json::Reader reader;

    //string strJson = "{\"mykey\" : \"myvalue\"}";

    //bool parsingSuccessful = reader.parse(strJson.c_str(), jsonDoc);
    int matrix[25]{ 0 };
    for (__int8 i = 0; i < 25; i++) {
        for (__int8 j = 0; j < 25; j++) {
            jsonMatrix[i][j] = i * 5;
        }
    }
    jsonDoc["matrix1"] = jsonMatrix;
    return jsonDoc;
}

void HTTPRequestManager::setJSONDocument(Json::Value jsonDoc) {
   
    //jsonDoc = createJSONDocument();

    //cout << "SETTING THIS JSON DOCUMENT : " << jsonDoc.toStyledString() << endl;
    cout << "SETTING JSON DOCUMENT" << endl;

    curl_easy_setopt(curl, CURLOPT_COPYPOSTFIELDS, jsonDoc.toStyledString().c_str());
    
    struct curl_slist* slist1;
    slist1 = NULL;
    slist1 = curl_slist_append(slist1, "Content-Type: application/json");
    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, slist1);
    curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "POST");
}
void HTTPRequestManager::setGETType() {
    curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "GET");
    curl_easy_setopt(curl, CURLOPT_HTTPGET, 1L);

}

void HTTPRequestManager::performRequest() {
    if (curl_easy_perform(curl) == CURLE_OK)
        //cout << "OKKKKKKKKKKKK";

    //string res(chunk.response);
   //cout << httpData;
    curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &httpCode);
    curl_easy_cleanup(curl);

    cout << "CODE : " << httpCode << " - END CODE" << endl;
}

void HTTPRequestManager::printJSONResult() {
    //cout << "PRINTING JSON RESULT" << endl;
    //if (httpCode == 200) {
    //    cout << "\nGot successful response from " << _url << std::endl;

    //    // Response looks good - done using Curl now.  Try to parse the results
    //    // and print them out.
    //    Json::Value jsonData;
    //    Json::Reader jsonReader;

    //    if (jsonReader.parse(_httpData, jsonData)) {
    //        cout << "Successfully parsed JSON data" << std::endl;
    //        cout << "\nJSON data received:" << std::endl;
    //        cout << jsonData.toStyledString() << std::endl;

    //        /*const std::string dateString(jsonData["date"].asString());
    //        const std::size_t unixTimeMs(
    //            jsonData["milliseconds_since_epoch"].asUInt64());
    //        const std::string timeString(jsonData["time"].asString());

    //        std::cout << "Natively parsed:" << std::endl;
    //        std::cout << "\tDate string: " << dateString << std::endl;
    //        std::cout << "\tUnix timeMs: " << unixTimeMs << std::endl;
    //        std::cout << "\tTime string: " << timeString << std::endl;
    //        std::cout << std::endl;*/
    //    }
    //    else {
    //        std::cout << "Could not parse HTTP data as JSON" << std::endl;
    //        std::cout << "HTTP data was:\n" << _httpData << std::endl;
    //        return;
    //    }
    //}
    //else {
    //    std::cout << "Couldn't GET from " << _url << " - exiting" << std::endl;
    //    return;
    //}
}


Json::Value HTTPRequestManager::getJSONResult() {
    cout << "GET JSON RESULT" << endl;

    Json::Value jsonData;
    Json::Reader jsonReader;

    if (httpCode == 201 || httpCode == 202) {
        cout << "\nGot successful response from " << _url << std::endl;

        // Response looks good - done using Curl now.  Try to parse the results
        // and print them out.

        if (jsonReader.parse(httpData, jsonData)) {
            return jsonData;
        } else {
            std::cout << "Could not parse HTTP data as JSON" << std::endl;
            std::cout << "HTTP data was:\n" << httpData << std::endl;
            return jsonData;
        }
    } else {
        std::cout << "Couldn't GET from " << _url << " - exiting" << std::endl;
        return jsonData;
    }


}


//std::unique_ptr<std::string> HTTPRequestManager::_httpData;
std::string HTTPRequestManager::httpData;