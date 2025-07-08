# Journal
2025-6-29 wsx
初始化了代码仓库，上传了游戏资源，其中 `Surroundings\Medieval_Castle` 为背景图片，可以直接使用。
`Main Character` 为主角的帧图，已切割好，但并未分类各个动作，还需进一步设置。

2025-7-1 wsx
配置了角色其他的动画，如下蹲，轻\重攻击，滑铲，爬梯子等。

2025-7-2 wsx
写了 boss1level 文件，搭建了一个场景的背景，其他内容没做，更新了一下项目架构。

2025-7-6 wsx
完成了 enemy1 的编写，除了伤害设置部分
提供的接口为
	```cpp
	void SetChaseBoundary(FVector2D minBoundary, FVector2D maxBoundary);	
	void SetSightRange(float r);
	void SetMoveSpeed(float r);
	void SetAttackCooldown(float r);
	```
设置enemy1的移动范围边界、视野范围、移动速度、攻击冷却
完成了第一个 Boss NightBorne 的编写，修复了部分 Enemy 中的bug

- 2025-6-29 djw
初步实现Player类，设置了Player的碰撞箱，成功将Player的碰撞箱绑定到物理引擎，并且可以在Level中调用创建角色
实现了一个FirstLevel，搭建了一个长平台，用于debug玩家的移动逻辑等

- 2025-6-30 ~ 2025-7-1 djw
实现了Player的左右移动逻辑，设置了其移动速度，可以在调试中看见角色的移动

- 2025-7-2 djw
修复Player的移动逻辑的bug，解决了其卡墙问题，现在角色可以正常的移动，不会卡在台阶的拐角上

- 2025-7-3 djw 
实现Player的跳跃逻辑，使得角色可以正常的进行跳跃

- 2025-7-4 djw
初步实现Player的attack逻辑，添加了上下左右四个方向的attackbox，可以进行攻击，不会与之前的逻辑冲突，但是没有实现攻击伤害逻辑

- 2025-7-5 djw
实现了Player的受伤逻辑，为Player添加了无敌帧，避免受到重复的伤害，实现了Player的死亡逻辑，可以在调试中看见角色的死亡逻辑
 
- 2025-7-6 djw
完善了Player的死亡逻辑，尝试将Player的攻击绑定在伤害引擎上，实现了Player的二段跳，猛冲等功能，且不会与之前的逻辑冲突

- 2025-7-7 djw
成功将Player的攻击绑定到上海系统，现在可以攻击敌人&被敌人攻击，添加了Player的攻击，跳跃，死亡动画