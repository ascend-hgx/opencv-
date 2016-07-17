# opencv-
训练opencv级联分类器

### 准备 ###
1. 编译安装opencv，在cmake中开启TBB（使训练级联分类器支持多线程）
2. 在编译好的文件中会有opencv_traincascade和opencv_createsamples两个文件，使用这两个可执行文件训练

### 假设你已经有了大小相同的正样本图片和比正样本大的负样本图片 ###
3. 处理图片，正样本归一化（最好是把pos.dat & neg.dat单独放在执行文件同目录，好几次出错改这就好了）
    find pos/ -name '*.bmp' -exec echo {} 1 0 0 20 20 \; > pos.dat
    或者ls语法
    ls -1 neg/*.jpg > neg.dat             //正样本文件格式为  图片名字 + 正样本数量 + 起点左边（x,y) + 长 + 宽  为一行

### 训练 ###
4. //生成正样本vec文件
  opencv_createsamples -info pos.dat -vec pos.vec -bg neg.dat -num 46 -w 64 -h 64
5. //训练文件
  opencv_traincascade -data dt -vec pos.vec -bg neg.dat -numPos 30 -numNeg 60 -numStages 16 -w 64 -h 64 -mode ALL
