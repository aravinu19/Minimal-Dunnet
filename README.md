# Minimal-Dunnet
A minimal version of dunnet (Text Based Survival Game) developed in C++ as fun project.

## Dunnet
Dunnet is a Text Adventure game written by Ron Schnell, for more details [Wikipedia](https://en.wikipedia.org/wiki/Dunnet_(video_game))

Online version of similar game [Zork](http://textadventures.co.uk/games/view/5zyoqrsugeopel3ffhz_vq/zork)

## Build Step

The basic requirement is make and gcc/g++.
Windows users, please use [WSL 2](https://docs.microsoft.com/en-us/windows/wsl/install-win10) to run Linux in windows.

Run the below command to build and start the game

```
make All
./main <map_file>
```

### Example
```
make All
./main map2.json
```

## Dependencies

- Standard Template Library 
- [JSON](https://github.com/nlohmann/json)

## Supported Commands
- TAKE < objects in the room >
- GO < to navigate to the available location or door or path >
- KILL < to kill enemies with weapons taken from other room >
- DESCRIBE < shows the current situation >
- INVENTORY < shows all the available items >
- EXIT < To Quit the game >

## Screenshot
![Game Screenshot](https://raw.githubusercontent.com/aravinu19/Minimal-Dunnet/main/sample_game_flow.png "Game Screenshot")

## License

Creative Commons Legal Code

CC0 1.0 Universal

    CREATIVE COMMONS CORPORATION IS NOT A LAW FIRM AND DOES NOT PROVIDE
    LEGAL SERVICES. DISTRIBUTION OF THIS DOCUMENT DOES NOT CREATE AN
    ATTORNEY-CLIENT RELATIONSHIP. CREATIVE COMMONS PROVIDES THIS
    INFORMATION ON AN "AS-IS" BASIS. CREATIVE COMMONS MAKES NO WARRANTIES
    REGARDING THE USE OF THIS DOCUMENT OR THE INFORMATION OR WORKS
    PROVIDED HEREUNDER, AND DISCLAIMS LIABILITY FOR DAMAGES RESULTING FROM
    THE USE OF THIS DOCUMENT OR THE INFORMATION OR WORKS PROVIDED
    HEREUNDER.
