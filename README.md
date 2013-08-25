Tilter2d
========

This is a simple tilt table game that I designed for a class. 

###Summary
For my project I made the classic table tilt game using the cocos2d-x/box2d.  Cocos2d-x is a c++ port of the Cocos2d for iphone game engine. Using this allowed me to create a game that runs on multiple platform without changing the source code.  Box2d is a physic engine that I used to take care of collision and movement. 

###Game Objects
Ball: Moves around the screen based on the accelerometer <br/> 
End Zone: User must have at least one ball object touching  each End Zone on the screen in order to proceed to next level. <br/>
Thruster: An object that applies a linear impulse in the direction it points on a ball <br/>
Hole: An object that sends a Ball object back to its original starting position <br/>
Anti-Accelerometer area: If a Ball enters this area the accelerometer controls for that ball will be reversed. <br/>
Block: An inaccessible area

###Setup
Download cocos2d-x 3.0 from http://www.cocos2d-x.org/ or get from github:https://github.com/cocos2d/cocos2d-x <br/> 
Clone Tilter2dx repo in [COCOS2D-X INSTALL FOLDER]\projects

###Tools & Tech
Language: C++ <br/>
Framework: cocos2d-3.0, Box2d <br/>


###Things to do
Load a level from JSON
Create an in-game level creator



 
