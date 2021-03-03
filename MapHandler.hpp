#include "json.hpp"
#include <fstream>
#include <string>
#include <list>
#include <map>
#include "DataModels.hpp"

#include <iostream>

using std::list;
using std::map;
using std::pair;
using std::string;
using json = nlohmann::json;
using namespace GameMap;

class MapHandler
{

public:
    MapHandler();
    MapHandler(string file_name);

    Room getRoomById(string room_id);
    Enemy getEnemyById(string enemy_id);
    string getInitialRoom();
    int getEnemiesCount();
    map<string, string> getEnemyRooms();

private:
    list<Room> rooms_data;
    list<Enemy> enemies_data;
    Player player_data;

    void extractRoomsInfo(json map_data);
    void extractEnemiesInfo(json map_data);
    void extractPlayerInfo(json map_data);
    list<string> extractArrayOfString(json obj);
};

MapHandler::MapHandler() {}

MapHandler::MapHandler(string file_name)
{
    std::ifstream file_data(file_name);
    json map_data;
    file_data >> map_data;

    extractRoomsInfo(map_data);
    extractEnemiesInfo(map_data);
    extractPlayerInfo(map_data);
}

void MapHandler::extractRoomsInfo(json map_data)
{
    auto parsed = map_data["rooms"];

    for (int index = 0; index < parsed.size(); index++)
    {
        Room temp_data{
            parsed[index]["id"].get<string>(),
            parsed[index]["desc"].get<string>(),
            parsed[index]["e"].get<string>(),
            parsed[index]["s"].get<string>(),
            parsed[index]["w"].get<string>(),
            parsed[index]["n"].get<string>(),
            extractArrayOfString(parsed[index]["obj"])};
        rooms_data.push_front(temp_data);
    }
}

void MapHandler::extractEnemiesInfo(json map_data)
{
    auto parsed = map_data["enemies"];

    for (int index = 0; index < parsed.size(); index++)
    {
        Enemy temp_data{
            parsed[index]["id"].get<string>(),
            parsed[index]["initialroom"].get<string>(),
            extractArrayOfString(parsed[index]["killedby"])};
        enemies_data.push_front(temp_data);
    }
}

void MapHandler::extractPlayerInfo(json map_data)
{
    Player temp_data{
        map_data["player"]["initialroom"].get<string>()};
    player_data = temp_data;
}

Room MapHandler::getRoomById(string room_id)
{

    for (const auto &room : rooms_data)
    {
        if (room_id == room.id)
        {
            return room;
        }
    }

    Room new_obj;
    return new_obj;
}

Enemy MapHandler::getEnemyById(string enemy_id)
{
    for (const auto &enemy : enemies_data)
    {
        if (enemy_id == enemy.id)
        {
            return enemy;
        }
    }

    Enemy new_obj;
    return new_obj;
}

string MapHandler::getInitialRoom()
{
    return player_data.initialRoom;
}

int MapHandler::getEnemiesCount()
{
    return enemies_data.size();
}
map<string, string> MapHandler::getEnemyRooms()
{

    map<string, string> enemy_rooms;

    for (const auto &enemy : enemies_data)
    {
        enemy_rooms.insert(pair<string, string>(enemy.initialRoom, enemy.id));
    }

    return enemy_rooms;
}

list<string> MapHandler::extractArrayOfString(json obj)
{
    int size = obj.size();
    list<string> objects;

    for (int index = 0; index < size; index++)
    {
        objects.push_front(obj[index].get<string>());
    }

    return objects;
}