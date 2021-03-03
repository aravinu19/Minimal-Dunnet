#include <string>
#include <list>
#include <set>
#include <map>

using std::string;
using std::list;
using std::set;
using std::map;

namespace GameMap {

    struct Room {
        string id = "";
        string desc;
        string east;
        string south;
        string west;
        string north;
        list<string> obj;
    };

    struct Enemy {
        string id = "";
        string initialRoom;
        list<string> killedBy;

    };

    struct Player {
        string initialRoom;
    };
}

namespace GameState {
    struct State {
        set<string> objects;
        string current_room;
        map<string, string> enemy_rooms;
        int enemies_count;
        bool is_enemy_present_in_room;
        string current_enemy_id = "";
    };
}

namespace GameOperations {
    enum Operation {
        TAKE,
        GO,
        KILL,
        DESCRIBE,
        INVENTORY,
        EXIT,
        INVALID_OPERATION
    };

    enum Direction {
        EAST,
        WEST,
        NORTH,
        SOUTH,
        INVALID_DIRECTION
    };

    Operation getOperation(string command) {

        if (command == "take")
        {
            return Operation::TAKE;
        }
        else if (command == "go" || command == "open" || command == "move")
        {
            return Operation::GO;
        }
        else if (command == "kill")
        {
            return Operation::KILL;
        }
        else if (command == "describe" || command == "explain" || command == "look")
        {
            return Operation::DESCRIBE;
        }
        else if (command == "inventory")
        {
            return Operation::INVENTORY;
        }
        else if (command == "exit" || command == "quit")
        {
            return Operation::EXIT;
        }
        else
        {
            return Operation::INVALID_OPERATION;
        }
        
    }

    Direction getDirection(string direction) {

        if (direction == "east")
        {
            return Direction::EAST;
        }
        else if (direction == "west")
        {
            return Direction::WEST;
        }
        else if (direction == "south")
        {
            return Direction::SOUTH;
        }
        else if (direction == "north")
        {
            return Direction::NORTH;
        }
        else
        {
            return Direction::INVALID_DIRECTION;
        }
        

    }
}