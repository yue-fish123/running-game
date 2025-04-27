# running-game
## 简介  
南开大学2025年C++课程大作业。一个基于Qt框架的跑酷小游戏。  
## 实现效果  
开始界面：
![开始界面](https://github.com/yue-fish123/running-game/blob/main/%E5%B1%95%E7%A4%BA/%E5%B1%8F%E5%B9%95%E6%88%AA%E5%9B%BE%202025-04-11%20223922.png?raw=true)  
游戏界面：
![游戏界面](https://github.com/yue-fish123/running-game/blob/main/%E5%B1%95%E7%A4%BA/%E5%B1%8F%E5%B9%95%E6%88%AA%E5%9B%BE%202025-04-13%20154854.png?raw=true)    
结束界面：
![结束界面](https://github.com/yue-fish123/running-game/blob/main/%E5%B1%95%E7%A4%BA/%E5%B1%8F%E5%B9%95%E6%88%AA%E5%9B%BE%202025-04-11%20224316.png?raw=true)    
## 项目结构  
> |-- README.md   
|-- barrier.cpp   
|-- barrier.h   
|-- character.cpp    
|-- character.h     
|-- feibiao.cpp    
|-- feibiao.h    
|-- gamesence.cpp    
|-- gamesence.h     
|-- main.cpp     
|-- mainwindow.cpp     
|-- mainwindow.h     
|-- mainwindow.ui     
|-- res      
|-- startscence.cpp     
|-- startscence.h     
|-- startscence.ui                
## 细节说明  
- barrier类中有两种障碍物分别为spear（长矛）、spike（地刺）。
    spear类对象有动画，且在角色靠近时才会触发，并且该类对象的碰撞只有在动画播放到特定动画帧之后才有效。
  spike类就单纯地躺在地上。
  两种障碍物生成都是随机的。
- gamescence类中的背景的运动是采用两张一样的图片进行滚轮播放实现的。
- feibiao（飞镖）文件里的类叫attack，原先是打算写两种以上的类似飞镖的攻击物，但是之后的工作量有点大，就放弃了。并且干脆把文件名从attack改成了feibiao。   
