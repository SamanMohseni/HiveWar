# HiveWar
This project is part of the **Advanced Programming and Lab** course.

A real-time strategy game developed with Qt, where players can engage in battles against an AI opponent.

## Gameplay
In each round, players have a set time to strategize and dictate the subsequent actions for their units or structures.
Actions for soldiers include movement and attack commands.
For workers, players can plan their next move, assign tasks such as harvesting wood or mining resources, or, if resources permit, command them to construct various buildings.
Buildings also have actionable options; some can fire upon designated targets within their range, while others are capable of producing soldiers or workers.
Once the designated time interval concludes, all actions are executed (or advanced by one step).
The image below shows a gameplay moment where a worker is selected. The left-side menu displays the potential actions that can be assigned to this worker as their next move, and the highlighted green cells indicate the possible positions the worker can move to.

![image_2016-06-27_16-33-40](https://github.com/SamanMohseni/HiveWar/assets/51726090/fba64bf7-31a1-4f8b-b764-6918bb112e34)


## Map Builder
HiveWar also includes a map editor that allows players to design and create custom maps.
Designed maps can be saved, and they will be accessible from the map selection menu upon your next game session.
