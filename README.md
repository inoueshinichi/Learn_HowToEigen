# How to Eigen  
https://eigen.tuxfamily.org/index.php?title=Main_Page  

## データ順序と表記順序による効率  
| データ順序 | 表記順序 | イメージの容易さ | 自然なプログラム記述 | モジュール例 |
| :-- | :-- | :-- | :-- | :-- |
| 列優先 | 列優先 | ◯ | × | Matlab(デフォルト), R, OpenGL |
| 列優先 | 行優先 | × | - | プログラム記述を優先させたパターン |
| 行優先 | 列優先 | ◯ | × | OpenCV, numpy, (数学表記に従ったC/C++計算) |
| 行優先 | 行優先 | × | ◯ | DirectX, (プログラム記述を優先させたC/C++計算) |


## データの行優先と列優先  
```
[m11, m12, m13]
[m21, m22, m23]
[m31, m32, m33]
```
と行列があるとき, メモリ配列として2パターンある  
1. [行優先] m11, m12, m13, m21, m22, m23, m31, m32, m33
2. [列優先] m11, m21, m31, m12, m22, m32, m13, m23, m33
行優先データ・・・C/C++, DirectX, OpenCV, numpy  
列優先データ・・・Fortran, Matrab(デフォルト), R, Eigen(デフォルト), OpenGL  

主にデータのコピー時に問題になる. EigenではRowMajor, ColMajorで指定できる.  
行優先データ -> Matrix3i<int, 3, 3, Eigen::RowMajor>  
列優先データ -> Matrix3i<int, 3, 3, Eigen::ColMajor> (デフォルト)  


## 計算表記の行優先と列優先  
基本：一般数学は列優先表記, プログラム記述は列優先表記的  
列優先表記  
```
v = [x
     y
     z]
```
```
M =
[s1r11, r12, r13, tx]
[r21, s2r22, r23, ty]
[r31, r32, s3r33, tz]
[0  , 0  , 0  , 1 ]
```
スケール→回転→並進  
```
v_new = T@R@S * v = M * v
```

行優先表記   
```
v = [x y z]
```
```
M =  
[s1r11, r21, r31, 0]
[r12, s2r22, r32, 0]
[r13, r23, s3r33, 0]
[ tx,  ty,   tz,  1]
```
スケール→回転→並進  
```
v_new = v * S@R@T = v * M
```
列優先表記(数学表記)・・・OpenGL, OpenCV, numpy, Matlab, R  
行優先表記(プログラム的表記)・・・DirectX  

行列計算時に問題になる  




