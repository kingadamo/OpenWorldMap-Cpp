#include "SaveFileManager.h"

/**
 * Base Constructor.
 */
SaveFileManager::SaveFileManager() {}


/**
 * Saves an OpenWorldMap object to a binary file.
 *
 * @param[in] openWorldMap the OpenWorldMap to save into a file.
 * @return whether or not the operation was succesful.
 */
bool SaveFileManager::saveOpenWorldMapToFile(OpenWorldMap &openWorldMap) {
    std::ofstream outFile;
    outFile.open("default.bin", std::ofstream::binary);
    
    __int64 nChunks = openWorldMap._chunkDirectory.size();

    outFile.write(reinterpret_cast<const char*>(&nChunks), sizeof(nChunks));

    std::map<__int32, std::array<std::array<__int8, CHUNK_DIMENSION>, CHUNK_DIMENSION>>::iterator it;
    for (it = openWorldMap._chunkDirectory.begin(); it != openWorldMap._chunkDirectory.end(); it++) {
        
        __int32 key = it->first;
        outFile.write(reinterpret_cast<const char*>(&key), sizeof(key));

        std::array<std::array<__int8, CHUNK_DIMENSION>, CHUNK_DIMENSION> chunk = it->second;
        for (size_t y = 0; y < CHUNK_DIMENSION; y++) {
            for (size_t x = 0; x < CHUNK_DIMENSION; x++) {
                
                __int8 data = chunk[y][x];
                outFile.write(reinterpret_cast<const char*>(&data), sizeof(data));

            }
        }
    }
    outFile.close();
    return false;
}


/**
 * Reads and loads an OpenWorldMap object from a binary file.
 *
 * @return loadedWorldMap the OpenWorldMap that was read from a binary file.
 */
OpenWorldMap SaveFileManager::loadOpenWorldMapFromFile() {
    std::ifstream inFile;
    inFile.open("default.bin", std::ofstream::binary);
    OpenWorldMap loadedWorldMap;

    __int64 nChunks = 0;

    inFile.read(reinterpret_cast<char*>(&nChunks), sizeof(nChunks));
    
   
    for (size_t i = 0; i < nChunks; i++) {
        // Get Key
        __int32 key = 0;
        inFile.read(reinterpret_cast<char*>(&key), sizeof(key));

        // Get Matrix
        std::array<std::array<__int8, CHUNK_DIMENSION>, CHUNK_DIMENSION> newChunk = { 0 };
        
        for (size_t y = 0; y < CHUNK_DIMENSION; y++) {
            for (size_t x = 0; x < CHUNK_DIMENSION; x++) {
                __int8 data = 0;
                inFile.read(reinterpret_cast<char*>(&data), sizeof(data));
                newChunk[y][x] = data;
            }
        }

        // Add Chunk to Directory
        loadedWorldMap._chunkDirectory.insert({ key , newChunk });
    }

    


    inFile.close();
    return loadedWorldMap;
}

bool SaveFileManager::saveOpenWorldMapToAPI(OpenWorldMap& openWorldMap, const string &mapName) {
    Json::Value jsonOpenWorldMap;
    
    __int64 nChunks = openWorldMap._chunkDirectory.size();

    jsonOpenWorldMap[NCHUNKS] = nChunks;

    std::map<__int32, std::array<std::array<__int8, CHUNK_DIMENSION>, CHUNK_DIMENSION>>::iterator it;

    for (it = openWorldMap._chunkDirectory.begin(); it != openWorldMap._chunkDirectory.end(); it++) {
        Json::Value jsonChunk;
        __int32 key = it->first;
        //outFile.write(reinterpret_cast<const char*>(&key), sizeof(key));

        std::array<std::array<__int8, CHUNK_DIMENSION>, CHUNK_DIMENSION> chunk = it->second;
        for (int y = 0; y < CHUNK_DIMENSION; y++) {
            for (int x = 0; x < CHUNK_DIMENSION; x++) {
                __int8 data = chunk[y][x];
                
                jsonChunk[y][x] = data;
                //outFile.write(reinterpret_cast<const char*>(&data), sizeof(data)); DONE

            }
        }
        jsonOpenWorldMap[to_string(key)] = jsonChunk;
    }


    string url = "http://localhost:3000/maps/" + mapName;
    _httpRequestManager.setUrl(url);
    _httpRequestManager.setJSONDocument(jsonOpenWorldMap);
    _httpRequestManager.performRequest();
    _httpRequestManager.printJSONResult();

    return true;
}

OpenWorldMap SaveFileManager::loadOpenWorldMapFromAPI(std::string mapName) {
    string url = "http://localhost:3000/maps/" + mapName;
    _httpRequestManager.setUrl(url);
    _httpRequestManager.setGETType();
    _httpRequestManager.performRequest();
    Json::Value jsonOpenWorldMap = _httpRequestManager.getJSONResult(); 
    Json::Reader jsonReader;


    //cout << "YES : " << jsonOpenWorldMap["mapObject"][NCHUNKS].asInt64() << endl;

   
    OpenWorldMap loadedWorldMap;

    __int64 nChunks = jsonOpenWorldMap["mapObject"][NCHUNKS].asInt64();

    bool isFirstIteration = true;
    
    //cout << "YES : " << jsonOpenWorldMap["mapObject"].toStyledString() << endl;
    for (auto const& id : jsonOpenWorldMap["mapObject"].getMemberNames()) {
        //cout << "ID : " << id << endl;
        if (id == NCHUNKS) {
            //cout << "c le n chunk vag\n";
        } else {
            __int32 key = 0;

            std::array<std::array<__int8, CHUNK_DIMENSION>, CHUNK_DIMENSION> newChunk = { 0 };

            for (int y = 0; y < CHUNK_DIMENSION; y++) {
                for (int x = 0; x < CHUNK_DIMENSION; x++) {
                    __int8 data = jsonOpenWorldMap["mapObject"][id][y][x].asInt();
                    newChunk[y][x] = data;
                }
            }

            //cout << id << " has " << jsonOpenWorldMap[id].toStyledString() << std::endl;

            //cout << "id : " << id << endl;
            __int32 keyFinal = stoi(id.c_str());
            loadedWorldMap._chunkDirectory.insert({ keyFinal, newChunk });
        }

    }
        


    //for (size_t i = 0; i < nChunks; i++) {
    //    // Get Key
    //    __int32 key = 0;
    //    inFile.read(reinterpret_cast<char*>(&key), sizeof(key));

    //    // Get Matrix
    //    std::array<std::array<__int8, CHUNK_DIMENSION>, CHUNK_DIMENSION> newChunk = { 0 };

    //    for (size_t y = 0; y < CHUNK_DIMENSION; y++) {
    //        for (size_t x = 0; x < CHUNK_DIMENSION; x++) {
    //            __int8 data = 0;
    //            inFile.read(reinterpret_cast<char*>(&data), sizeof(data));
    //            newChunk[y][x] = data;
    //        }
    //    }

    //    // Add Chunk to Directory
    //    loadedWorldMap._chunkDirectory.insert({ key , newChunk });
    //}


    return loadedWorldMap;


    // TODO : MANIPULATE data
     /*const std::string dateString(jsonData["date"].asString());
            const std::size_t unixTimeMs(
                jsonData["milliseconds_since_epoch"].asUInt64());
            const std::string timeString(jsonData["time"].asString());

            std::cout << "Natively parsed:" << std::endl;
            std::cout << "\tDate string: " << dateString << std::endl;
            std::cout << "\tUnix timeMs: " << unixTimeMs << std::endl;
            std::cout << "\tTime string: " << timeString << std::endl;
            std::cout << std::endl;*/
    //_httpRequestManager.printJSONResult();

}

bool SaveFileManager::saveOpenWorldMapToGoAPI(OpenWorldMap& openWorldMap, const string& mapName) {
    Json::Value jsonOpenWorldMap;
    Json::Value jsonChunkRepository;

    __int64 nChunks = openWorldMap._chunkDirectory.size();

    jsonOpenWorldMap["map_name"] = mapName.c_str();
    jsonOpenWorldMap["nChunks"] = nChunks;

    

    std::map<__int32, std::array<std::array<__int8, CHUNK_DIMENSION>, CHUNK_DIMENSION>>::iterator it;
    Json::Value jsonChunkList;
    
    int i = 0;
    for (it = openWorldMap._chunkDirectory.begin(); it != openWorldMap._chunkDirectory.end(); it++) {
        Json::Value jsonChunkData;
        __int32 key = it->first;
        //outFile.write(reinterpret_cast<const char*>(&key), sizeof(key));

        std::array<std::array<__int8, CHUNK_DIMENSION>, CHUNK_DIMENSION> chunk = it->second;
        for (int y = 0; y < CHUNK_DIMENSION; y++) {
            for (int x = 0; x < CHUNK_DIMENSION; x++) {
                __int8 data = chunk[y][x];

                jsonChunkData[y][x] = data;
                //outFile.write(reinterpret_cast<const char*>(&data), sizeof(data)); DONE

            }
        }
        //jsonOpenWorldMap[to_string(key)] = jsonChunkData;
        jsonChunkList["chunk_list"][i]["chunk_coordinate"] = key;
        jsonChunkList["chunk_list"][i]["chunk_data"] = jsonChunkData;
        i++;
    }
    jsonOpenWorldMap["chunk_repository"] = jsonChunkList;


    string url = "http://localhost:8000/maps/" + mapName;
    _httpRequestManager.setUrl(url);
    _httpRequestManager.setJSONDocument(jsonOpenWorldMap);
    _httpRequestManager.performRequest();
    _httpRequestManager.printJSONResult();

    cout << jsonOpenWorldMap.toStyledString();

    return true;
}

OpenWorldMap SaveFileManager::loadOpenWorldMapFromGoAPI(std::string mapName) {
    string url = "http://localhost:8000/maps/" + mapName;
    _httpRequestManager.setUrl(url);
    _httpRequestManager.setGETType();
    _httpRequestManager.performRequest();
    Json::Value jsonOpenWorldMap = _httpRequestManager.getJSONResult();
    Json::Reader jsonReader;


    //cout << "YES : " << jsonOpenWorldMap["mapObject"][NCHUNKS].asInt64() << endl;


    OpenWorldMap loadedWorldMap;

    __int64 nChunks = jsonOpenWorldMap["nChunks"].asInt64();

    bool isFirstIteration = true;

    //cout << "YES : " << jsonOpenWorldMap["mapObject"].toStyledString() << endl;
    for (auto const& id : jsonOpenWorldMap["chunk_repository"]["chunk_list"].getMemberNames()) {
        //cout << "ID : " << id << endl;
        if (id == NCHUNKS) {
            //cout << "c le n chunk vag\n";
        }
        else {
            //__int32 key = 0;

            std::array<std::array<__int8, CHUNK_DIMENSION>, CHUNK_DIMENSION> newChunk = { 0 };

            for (int y = 0; y < CHUNK_DIMENSION; y++) {
                for (int x = 0; x < CHUNK_DIMENSION; x++) {
                    __int8 data = jsonOpenWorldMap["chunk_repository"]["chunk_list"][id]["chunk_data"][y][x].asInt();
                    newChunk[y][x] = data;
                }
            }

            //cout << id << " has " << jsonOpenWorldMap[id].toStyledString() << std::endl;

            //cout << "id : " << id << endl;
            __int32 keyFinal = jsonOpenWorldMap["chunk_repository"]["chunk_list"][id]["chunk_coordinate"].asInt();;
            loadedWorldMap._chunkDirectory.insert({ keyFinal, newChunk });
        }

    }




    return loadedWorldMap;
}



