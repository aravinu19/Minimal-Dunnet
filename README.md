# Minimal-Dunnet
A minimal version of dunnet (Text Based Survival Game) developed in C++ as fun project.

## Build Step

The basic requirement is make and gcc/g++.
Windows users, please use [WSL2](https://docs.microsoft.com/en-us/windows/wsl/install-win10) to run Linux in windows.

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
