# Bloxorz
A 3D game implemented in C++ using OpenGL 3.0 . It is similar to : https://www.miniclip.com/games/bloxorz/en/

![bloxorz demo](demo/bloxorz.gif)

## Compile
- Compile using simple 'make'

## Run
- Run using './a.out'

## Dependencies
- Libraries
	- GLAD
	- GLFW
	- GLM
- Change include headers in ![headers.h](/code/headers.h) if needed.

## About The Game
- Take block to target postion defined by a hole. Stand vertically on hole to complete stage.
- You can't stand vertically on orange tiles.
- Light green tiles are normal bridge switches. Normal bridges can be opened by placing block on the switches.
- Dark green tiles are heavy bridge switches. Heavy bridges can be opened by placing block VERTICALLY on the switches.

## Main Features
- Scope of developing multiple levels. Just need to add more data files describing levels. Levels can be changed by changing 'level' variable in main.cpp file.
- Smooth Animated movements of block and camera.
- Map of world at bottom-left corner.

- Object Oriented Programming.
- Dynamic Stage initialization by reading from a data file.
- Smooth movement of block. (Animated movement)
- Implemented normal bridge and heavy bridge(can be open only by verticle position) and fragile tiles.
- Multiple Camera Views. (Described below)


## Controls

### Movement
- Arrow Keys : For up, down, left, right movements of block.

### Camera Views
- X : Helicopter View
- C : Follow View
- V : Vericle View (Top View)
- B : Tower View
- N : Mouse Drag View
- M : Free Rotate View

### Others
- Other Controls are view specific. Specified below.



## Camera Views


1. Vericle View
    - Shows Orthographic view of the world from upside.
    - No Camera movement.
    - No other Controls


2. Tower View
    - Shows Perspective view from side upper point.
    - No Camera movement.
    - No other Controls

3. Helicopter View
    - Shows Perspective view starting from the current position.
    - Camera position can be controlled by 6 keys. (movements : left, right, up, down, in, out)
    - Camere orientation can be controlled by other 4 keys. (movements : left, right, up, down)
    - Controls
        - A, W, S, D : For camera movement.
        - I, J, K, L : For Camera orientation.
        - T, G       : For Camera zoom in, out.

4. Follow View
    - Most classic and default view of my game.
    - Shows block from little above of it and camera moves with block.
    - Camera movement is smooth with block movement. (Animated movement)
    - No other Controls


5. Mouse Drag View
    - Perspective view controlled by mouse.
    - Camera orientation can be controlled by drag and drop. (movements : left, right, up, down)
    - Camera zoom can be controlled by scrolling. (movements: in, out)
    - Controls
        - Mouse left click and drag : For camera orientation.
        - Mouse scroll in and out : For camera zoom in and out.
        - A, W, S, D : For camera movement.
        - T, G       : For Camera zoom in, out.

6. Free Rotate view
    - Keep rotating camera according to cursor postion.
    - Camera position can be controlled by 6 keys. (movements : left, right, up, down, in, out)
    - This view is not for playing. It is just for observing.
    - Controls
        - Mouse scroll in and out : For camera zoom in and out.
        - A, W, S, D : For camera movement.
        - T, G       : For Camera zoom in, out.


## Scope of Improvement
- Add more levels, Just need to create data files in data directory
- Connect levels with each other i.e. sequence of levels
- Display scoreboard on the display
