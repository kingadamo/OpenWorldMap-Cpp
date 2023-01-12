#pragma once
#include "Util.h"
#include "OpenWorldMap.h"

#include <fstream>
#include <iostream>

#include <map>

#include "MyHTTPRequestManager.h"
#include <json/json.h>

static class SaveFileManager {
	
	public:
		SaveFileManager();
		bool saveOpenWorldMapToFile(OpenWorldMap &openWorldMap);
		OpenWorldMap loadOpenWorldMapFromFile();

		bool saveOpenWorldMapToAPI(OpenWorldMap& openWorldMap, const string &mapName);
		OpenWorldMap loadOpenWorldMapFromAPI(std::string mapName);

		bool saveOpenWorldMapToGoAPI(OpenWorldMap& openWorldMap, const string& mapName);
		OpenWorldMap loadOpenWorldMapFromGoAPI(std::string mapName);

	private:
		const string NCHUNKS = "nChunks";

		HTTPRequestManager _httpRequestManager = HTTPRequestManager();
};

