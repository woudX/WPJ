WPJ (Woud Project)
===

这是一个关于游戏引擎的项目，由C++开发

  我个人很喜欢玩像Touhou系列这样的STG游戏，因此我打算开发一个游戏引擎用来开发STG游戏。目前看来这个引擎设计完成后，不仅是能做STG了.. 对于RPG或者AVG估计也是可以的，不过依然还是以STG为重点开发。引擎开发完成后，会尽力引入脚本，使游戏开发变得更加方便快捷。因为这个项目是我在学习Cocos2d-x的过程中开发的，所以学习借鉴了其内部设计的方法，尤其是绘制树部分非常的喜欢！
  
  目前为止这个项目还在开发中，以下是所完成或正在开发的功能点：

This is a project about Game Engine, developed by C++

  I love to play STG games, for example touhou series~ Thus I plan to develop a game engine so I can use this to make STG games 
by myself. And this engine can not only make STG, but also make other games, rpg, avg ... 

  Now this project is under developing ,so far I have realized these function points:
  
  + Memory
    * Auto Garbage Collection
    + Object Pool
      * Customed Object Pool
      * Object Pool Manager
    + String
	  * Create
      * Hash Compare
      * String Manager
  + Flow Control
    * WPJTimer
    * WPJScheduler
    * WPJDirector
    * Fps
  + Allegro Engine - WPJALGO
    * Window Interface
    * Event Interface
    * Drawing Interface
    * WPJTexture2D
  + Action
    * WPJActionManager
    + Actions
      + FiniteAction
        * WPJMoveTo
        * WPJMoveBy
        * WPJRotateTo
		* WPJRotateBy
		* WPJWait
		* WPJSequence
		* ...
  + Drawing Tree
    + WPJLayer (Working ...)
    + WPJScene
    + WPJSprite
      * Basic properties
      + Coordinate System
        * Relative Coordinate
        * World Coordinate
        * Allegro Coordinate
        * Coordinate Transition
    + WPJNode
      * Children and Parent
      * Event Callbacks
      + Actions
      * Scheduler and Timer
      * Draw
      + Transformation
        * Rotate
        * Scale
        * Transition
        * Skew  (Working ...)
  + Math Geometry
    * WPJPoint
    * WPJSize
    * WPJRectangle
  
  ---

  
  如果对这个项目感兴趣或者是有什么建议，欢迎联系我。
  If you are intresting with this Project or have some suggestions ,welcome to contact me.
  
  E-mail address : jccgls001@126.com
  
  WoudX 
  2014/4/16
