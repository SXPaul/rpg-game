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