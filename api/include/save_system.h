#ifndef API_SAVE_SYSTEM_H
#define API_SAVE_SYSTEM_H
#include <string>

//TODO: SOON Save & Load system
//Things that need saving: me
//Tilemap -> tiles_(type(if type kPlain, then buildable = true), position, walkable, tile_texture_index_)
//all vectors in tilemap
class SaveSystem
{
public:
	void SaveGame(const std::string& file_name);
	void LoadGame(const std::string& file_name);
};







#endif // API_SAVE_SYSTEM_H
