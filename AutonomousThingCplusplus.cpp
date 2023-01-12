// AutonomousThingCplusplus.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.
//

#include "Coordinate.h"
#include "OpenWorldMap.h"
#include "EnvironmentMap.h"

#include "SaveFileManager.h"
#include<thread>
#include <random>

#include <iostream>
#include <iomanip>
#include <list>



using namespace std;




int main() {
    cout << "Hello World!\n";

    

   /* KeyType type = QuadrantKey;
    Coordinate coord("-1,55", type);
    cout << coord.getQuadrantKey() << endl;*/


    

    /*Coordinate target(-5, 25);
    cout << "Target : " << target.getCoordKey() << endl;

    
    for (size_t i = 0; i < 150; i++) {
        envMap.addObstacleAtCoord(target);
    }*/

    //TIMER
    clock_t start, end, fileSaveStart, fileSaveEnd, fileLoadStart, fileLoadEnd, APISaveStart, APISaveEnd, APILoadStart, APILoadEnd;
    start = clock();
    
    OpenWorldMap envMap;
    

    std::random_device rd; // obtain a random number from hardware
    std::mt19937 gen(rd()); // seed the generator
    std::uniform_int_distribution<int> uni(-5000, 5000);
    
    /*for (size_t i = 0; i < 1'000'000; i+=1) {
            int y = uni(gen);
            int x = uni(gen);
            Coordinate targetRand(y, x);
            envMap.addObstacleAtCoord(targetRand);
    }*/

    //list<thread> myThreadList;
    
    

    //for (int i = 0; i < 25; i+=25) {
    //    for (int j = 0; j < 25; j+=25) {
    //        int y = i;
    //        int x = j;
    //        Coordinate targetRand(y, x);

    //        //myThreadList.push_back(thread(&EnvironmentMap::addObstacleAtCoord, &envMap, targetRand));
    //        /*thread thread1(&EnvironmentMap::addObstacleAtCoord, &envMap, targetRand);
    //        thread1.join();*/
    //        envMap.addObstacleAtCoord(targetRand);
    //    }
    //}

    // ----------------------------------------------------
    // BEGIN SAVE FILE TEST -------------------------------
    // ----------------------------------------------------
    cout << "\n\nTESTING BINARY FILES" << endl;
    OpenWorldMap openWorldMapToSave;
    
    // Targeting One Point
    int y = 5;
    int x = 5;
    Coordinate targetToTest(y, x);
    for (int i = 0; i < 25; i++) {
        openWorldMapToSave.addObstacleAtCoord(targetToTest);
    }

    // Generate a ton of chunks
    for (int i = 0; i < 4000; i += 25) {
        for (int j = 0; j < 4000; j += 25) {
            int y = i;
            int x = j;
            Coordinate chunkSpammerCoord(y, x);

            //myThreadList.push_back(thread(&EnvironmentMap::addObstacleAtCoord, &envMap, targetRand));
            /*thread thread1(&EnvironmentMap::addObstacleAtCoord, &envMap, targetRand);
            thread1.join();*/
            openWorldMapToSave.addObstacleAtCoord(chunkSpammerCoord);
        }
    }


    
    SaveFileManager saveFileManager;
    fileSaveStart = clock();
    saveFileManager.saveOpenWorldMapToFile(openWorldMapToSave);
    fileSaveEnd = clock();
    double time_takenToSave = (double(fileSaveEnd) - double(fileSaveStart)) / double(CLOCKS_PER_SEC);

    cout << "Target to test value (must be identical with loaded): " << (int)openWorldMapToSave.getValueAtCoord(targetToTest) << endl;
    cout << "Number of chunks : " << openWorldMapToSave._chunkDirectory.size() << endl;
    cout << "Time to save : " << fixed << time_takenToSave * 1000 << setprecision(5) << " ms " << endl << endl;

    fileLoadStart = clock();
    OpenWorldMap openWorldMapLoaded = saveFileManager.loadOpenWorldMapFromFile();
    fileLoadEnd = clock();
    double time_takenToLoad = (double(fileLoadEnd) - double(fileLoadStart)) / double(CLOCKS_PER_SEC);
    
    cout << "Result after save : " << (int) openWorldMapLoaded.getValueAtCoord(targetToTest) << endl;
    cout << "Number of chunks : " << openWorldMapLoaded._chunkDirectory.size() << endl;
    cout << "Time to load : " << fixed << time_takenToLoad * 1000 << setprecision(5) << " ms " << endl << endl;

    // ----------------------------------------------------
    // END SAVE FILE TEST -------------------------------
    // ----------------------------------------------------

    

    // ----------------------------------------------------
    // BEGIN SAVE TO API TEST -------------------------------
    // ----------------------------------------------------
    cout << "\n\nTESTING API" << endl;
    OpenWorldMap openWorldMapToSaveAPI;

    // Targeting One Point
    int yAPI = 5;
    int xAPI = 5;
    Coordinate targetToTestAPI(y, x);
    for (int i = 0; i < 25; i++) {
        openWorldMapToSaveAPI.addObstacleAtCoord(targetToTestAPI);
    }

    // Generate a ton of chunks
    for (int i = 0; i < 50; i += 25) {
        for (int j = 0; j < 50; j += 25) {
            int y = i;
            int x = j;
            Coordinate chunkSpammerCoord(y, x);

            //myThreadList.push_back(thread(&EnvironmentMap::addObstacleAtCoord, &envMap, targetRand));
            /*thread thread1(&EnvironmentMap::addObstacleAtCoord, &envMap, targetRand);
            thread1.join();*/
            openWorldMapToSaveAPI.addObstacleAtCoord(chunkSpammerCoord);
        }
    }
    APISaveStart = clock();
    saveFileManager.saveOpenWorldMapToGoAPI(openWorldMapToSaveAPI, "map1");
    APISaveEnd = clock();

    double time_takenToSaveAPI = (double(APISaveEnd) - double(APISaveStart)) / double(CLOCKS_PER_SEC);

    cout << "Target to test value (must be identical with loaded): " << (int)openWorldMapToSaveAPI.getValueAtCoord(targetToTestAPI) << endl;
    cout << "Number of chunks : " << openWorldMapToSaveAPI._chunkDirectory.size() << endl;
    cout << "Time to save : " << fixed << time_takenToSaveAPI * 1000 << setprecision(5) << " ms " << endl << endl;

    cout << "STARTING LOAD API\n";
    APILoadStart = clock();
    OpenWorldMap openWorldMapLoadedAPI = saveFileManager.loadOpenWorldMapFromGoAPI("map1");
    APILoadEnd = clock();
    double time_takenToLoadAPI = (double(APILoadEnd) - double(APILoadStart)) / double(CLOCKS_PER_SEC);

    cout << "Result after save : " << (int)openWorldMapLoadedAPI.getValueAtCoord(targetToTestAPI) << endl;
    cout << "Number of chunks : " << openWorldMapLoadedAPI._chunkDirectory.size() << endl;
    cout << "Time to load : " << fixed << time_takenToLoadAPI * 1000 << setprecision(5) << " ms " << endl << endl;

    // ----------------------------------------------------
    // END SAVE TO API TEST -------------------------------
    // ----------------------------------------------------















    

    /*for (size_t i = 0; i < 200000; i++) {
        myThreads[i].join();
    }*/
    
    end = clock();

    double time_taken = (double(end) - double(start)) / double(CLOCKS_PER_SEC);
    cout << "Total time : " << fixed << time_taken*1000 << setprecision(15) << " ms " << endl;

    //cout << "Obstacle added" << endl;
    cout << "5";
    //cout << "Result : " << (int)envMap.getValueAtCoord(targetRand);

    return 0;
}