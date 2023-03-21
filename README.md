# OpenWorldMap-Cpp
A low level Real-Time 2D Mapping library for embedded systems. 

## How it works
The OpenWorldMap divides the world in chunks that are generated on discovery (like Minecraft chunk system). On map creation, the area around the spawn is generated. 

![Schematic](/schematic.png)

Now your robot can navigate around and collect data about its environnement through it's captors. You can add an obstacle at a coordinate which will increment the weight of a cell. A low value cell can be interpretated as empty and a high value cell as occupied. 

Whenever, you try to add a new coordinate, the targeted chunk will automatically be calculated and 2 scenarios can happen :
 1. The targeted chunk exists : The corresponding cell will be incremented.
 2. The targeted chunk does not exist : A new chunk will be allocated in memory and added to the chunk repository.
 
As such, you can manage your MCUs memory more efficiently. With a resolution of 1 cm^2, you can fit a 1500sqft map in just about 1.4MB.
