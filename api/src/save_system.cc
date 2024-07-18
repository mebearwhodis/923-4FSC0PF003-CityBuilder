#include "save_system.h"

#include <iostream>
#include <fstream>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

void SaveSystem::SaveGame(Tilemap& tilemap, BuildingManager& building_manager, EconomyManager& economy_manager)
{
    //// Create a JSON object to store the data
    //json saveData;

    //// Save tilemap data
    //saveData["tilemap"] = tilemap.GetData();

    //// Save building data
    //saveData["buildings"] = building_manager.GetBuildingsData();

    //// Save economy data
    //saveData["economy"]["food"] = economy_manager.food();
    //saveData["economy"]["wood"] = economy_manager.wood();
    //saveData["economy"]["stone"] = economy_manager.stone();
    //saveData["economy"]["costs"] = economy_manager.GetCosts();

    //// Convert the JSON object to a string
    //std::string saveDataString = saveData.dump();

    //// Save the data to a JSON file
    //std::ofstream outputFile("save_data.json");
    //if (outputFile.is_open())
    //{
    //    outputFile << saveDataString;
    //    outputFile.close();
    //    std::cout << "Data saved successfully." << std::endl;
    //}
    //else
    //{
    //    std::cout << "Failed to save data." << std::endl;
    //}
}