# wip-nameless-gaem
It's a work in progress, it has no name and it might turn out to be a gaem.

####Master branch build status: 
![](https://travis-ci.org/GtDM/wip-nameless-gaem.svg?branch=master)

#Installation guide on arch linux:
-sudo pacman -S box2d sfml clang git
-git clone https://github.com/GtDM/wip-nameless-gaem.git
-cd wip-nameless-gaem/
-make
-./wip-nameless-gaem

#Controls in current build:
-WASD - Movement
-CV - Place static boxes of two predefined sizes in cursor's location
-B - Save current map to file "levels/map1.ams"
-N - Load map "levels/map1.ams"

Currently loading a map that doesn't exist is not recommended and the main red rectangle spawns in the same location every time
That build status will keep failing until someone will link box2d and sfml inside the project
Also, it should be split into directories, but it's WIP as everything else.

#Have a nice day or night
