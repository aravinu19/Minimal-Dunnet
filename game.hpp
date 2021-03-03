#include "MapHandler.hpp"
#include <iostream>
#include <string>
#include <bits/stdc++.h>

using std::cin;
using std::cout;
using std::endl;
using std::string;
using namespace GameState;
using namespace GameOperations;

class Game
{

private:
    MapHandler handler;
    State game_state;
    Room current_room;
    bool is_room_changed;
    int action_count = 0;
    list<string> current_user_command;

    void initiateGameState();
    void showRoomInfo();
    void promptForUserInput();
    void tokenizeInput(string user_input);
    void processUserInput();
    void executeOperation(Operation operation);
    void takeObject();
    void changeRoom();
    void killEnemy();
    void showInventory();

public:
    Game(string map_file);

    void start();
};

Game::Game(string map_file)
{
    MapHandler temp_obj(map_file);
    handler = temp_obj;
    start();
}

void Game::initiateGameState()
{
    game_state.current_room = handler.getInitialRoom();
    game_state.enemies_count = handler.getEnemiesCount();
    game_state.enemy_rooms = handler.getEnemyRooms();
    is_room_changed = true;
}

void Game::tokenizeInput(string user_input)
{
    std::stringstream input_stream(user_input);
    string token;

    while (std::getline(input_stream, token, ' '))
    {
        std::transform(token.begin(), token.end(), token.begin(), ::tolower);
        current_user_command.push_front(token);
    }
}

void Game::promptForUserInput()
{
    string user_input;

    cout << "> ";
    std::getline(cin, user_input);

    tokenizeInput(user_input);
}

void Game::showRoomInfo()
{
    current_room = handler.getRoomById(game_state.current_room);
    is_room_changed = false;

    if (current_room.id != "")
    {
        cout << current_room.desc << endl;

        if (current_room.obj.size() > 0)
        {
            if (game_state.objects.size() > 0)
            {
                for (const auto &obj : current_room.obj)
                {
                    bool is_taken = false;
                    for (const auto &taken_obj : game_state.objects)
                    {
                        if (taken_obj == obj)
                        {
                            is_taken = true;
                            break;
                        }
                    }

                    if (!is_taken)
                    {
                        cout << "There is a " << obj << "." << endl;
                    }
                    

                }
            }
            else
            {
                for (const auto &obj : current_room.obj)
                {
                    cout << "There is a " << obj << "." << endl;
                }
            }
        }

        if (game_state.enemy_rooms.count(current_room.id) == 1)
        {
            game_state.current_enemy_id = game_state.enemy_rooms.find(current_room.id)->second;
            cout << "There is a " << game_state.current_enemy_id << " here!" << endl;
            game_state.is_enemy_present_in_room = true;
            action_count = 0;
        }
        else
        {
            game_state.is_enemy_present_in_room = false;
        }
    }
    else
    {
        cout << "Error in Map File :(" << endl;
        exit(1);
    }
}

void Game::takeObject()
{
    bool is_obj_present = false;

    for (const auto &input : current_user_command)
    {
        for (const auto &obj : current_room.obj)
        {
            // if (obj == input)
            if (obj.find(input) != string::npos)
            {
                is_obj_present = true;
                game_state.objects.insert(obj);
                cout << "you have taken " << obj << "." << endl;
                break;
            }
        }

        if (is_obj_present)
        {
            break;
        }
    }

    if (!is_obj_present)
    {
        cout << "Not Sure what to take !" << endl;
    }
}

void Game::changeRoom()
{
    bool is_found = false;
    Direction direction;

    for (const auto &token : current_user_command)
    {
        direction = getDirection(token);

        if (direction != Direction::INVALID_DIRECTION)
        {
            is_found = true;
            break;
        }
    }

    if (is_found)
    {
        switch (direction)
        {
        case Direction::EAST:
            if (current_room.east != "")
            {
                is_room_changed = true;
                game_state.current_room = current_room.east;
                showRoomInfo();
            }
            else
            {
                cout << "Not sure where to go !" << endl;
            }

            break;

        case Direction::WEST:
            if (current_room.west != "")
            {
                is_room_changed = true;
                game_state.current_room = current_room.west;
                showRoomInfo();
            }
            else
            {
                cout << "Not sure where to go !" << endl;
            }

            break;

        case Direction::SOUTH:
            if (current_room.south != "")
            {
                is_room_changed = true;
                game_state.current_room = current_room.south;
                showRoomInfo();
            }
            else
            {
                cout << "Not sure where to go !" << endl;
            }

            break;

        case Direction::NORTH:
            if (current_room.north != "")
            {
                is_room_changed = true;
                game_state.current_room = current_room.north;
                showRoomInfo();
            }
            else
            {
                cout << "Not sure where to go !" << endl;
            }

            break;

        default:
            break;
        }
    }
    else
    {
        cout << "Not sure where to go !" << endl;
    }
}

void Game::killEnemy()
{
    if (game_state.is_enemy_present_in_room)
    {
        Enemy current_enemy = handler.getEnemyById(game_state.current_enemy_id);
        bool is_enemy_name_correct = false;

        for (const auto &token : current_user_command)
        {
            if (token == game_state.current_enemy_id)
            {
                is_enemy_name_correct = true;
                break;
            }
        }

        if (is_enemy_name_correct)
        {
            if (current_enemy.id != "")
            {
                int required_items = current_enemy.killedBy.size();
                int items_present = 0;

                for (const auto &obj_present : game_state.objects)
                {
                    for (const auto &obj_required : current_enemy.killedBy)
                    {
                        if (obj_present == obj_required)
                        {
                            items_present++;
                        }
                    }
                }

                if (required_items == items_present)
                {
                    game_state.enemies_count -= 1;
                    game_state.enemy_rooms.erase(game_state.current_room);
                    game_state.is_enemy_present_in_room = false;

                    cout << "You have killed the " << game_state.current_enemy_id << "." << endl;
                }
                else
                {
                    cout << "You don't have sufficient items to kill " << game_state.current_enemy_id << " :(" << endl;
                }
            }
            else
            {
                cout << "Something went sideways :(" << endl;
                exit(1);
            }
        } else {
            cout << "Not Sure what to kill !" << endl;
        }
    }
    else
    {
        cout << "Not Sure what to kill !" << endl;
    }
}

void Game::showInventory()
{
    if (game_state.objects.size() > 0)
    {
        cout << "You have following items:" << endl;

        int sno = 0;

        for (const auto &obj : game_state.objects)
        {
            cout << ++sno << ". " << obj << endl;
        }
    }
    else
    {
        cout << "You have nothing in the inventory :(" << endl;
    }
}

void Game::executeOperation(Operation operation)
{

    if (game_state.is_enemy_present_in_room)
    {
        action_count++;
    }
    

    switch (operation)
    {
    case Operation::TAKE:
        takeObject();
        break;

    case Operation::GO:
        changeRoom();
        break;

    case Operation::KILL:
        killEnemy();
        break;

    case Operation::DESCRIBE:
        showRoomInfo();
        break;

    case Operation::INVENTORY:
        showInventory();
        break;

    case Operation::EXIT:
        exit(0);
        break;

    default:
        break;
    }

    if (game_state.is_enemy_present_in_room && action_count > 0)
    {
        cout << "You are killed by " << game_state.current_enemy_id << " :(" << endl;
        cout << "GAME OVER :)" << endl;
        exit(0);
    }
}

void Game::processUserInput()
{
    bool is_found = false;
    Operation operation;

    for (const auto &token : current_user_command)
    {
        operation = getOperation(token);
        if (operation != Operation::INVALID_OPERATION)
        {
            is_found = true;
            break;
        }
    }

    if (is_found)
    {
        // cout << "OPERATION: " << operation << endl;
        executeOperation(operation);
    }
    else
    {
        cout << "I'm not sure, what you're saying!" << endl;
    }
}

void Game::start()
{
    initiateGameState();
    cout << "You find yourself in an unfamiliar room. You can't remember how you get here." << endl;

    while (game_state.enemies_count > 0)
    {

        if (is_room_changed)
        {
            showRoomInfo();
        }

        promptForUserInput();
        processUserInput();
    }

    cout << "You have killed all the enemies!" << endl;
    cout << "Congratulations!, You have won :)" << endl;
}