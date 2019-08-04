# Task 1

画两个半透的相交的正方形（带贴图），叠加的blend模式是——src是 source alpha， dst是 （1 - source alpha）

## solution 

利用了glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA)，可能有问题，周一去交流一下
