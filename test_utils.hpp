/**
 * @file test_utils.hpp
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2023-02-14
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#pragma once

#include <string>
#include <iostream>
#include <sstream>

#include <cstdio>
#include <cstdlib>
#include <random>

#include <vector>

#include <cstring>
#include <memory>

#if _MSC_VER
#define _USE_MATH_DEFINES
#endif
#include <cmath>

#include <limits>
#include <numeric>

#include <algorithm>


#if __has_include(<numbers>)
    #include <numbers>
#endif

#if __has_include(<filesystem>)
    #include <filesystem>
#endif

#if __has_include(<cxxabi.h>)
    #include <cxxabi.h>
#endif

// #include <Eigen/Dense>    // 全部詰め合わせ

#include <Eigen/Core>        // 基本演算

#include <Eigen/Geometry>    // 3次元ベクトル計算

#include <Eigen/Eigen>       // 固有値
#include <Eigen/Eigenvalues> // 固有値分解

#include <Eigen/Jacobi>      // ヤコビアン(ヤコビ行列)
#include <Eigen/Householder> // ハウスホルダー変換

// 行列分解
#include <Eigen/SVD>         // 特異値分解
#include <Eigen/LU>          // LU分解
#include <Eigen/Cholesky>    // コレスキー分解
#include <Eigen/QR>          // QR分解

// スパース行列
#include <Eigen/Sparse>
#include <Eigen/SparseCore>
#include <Eigen/SparseLU>
#include <Eigen/SparseQR>
#include <Eigen/SparseCholesky>

// STLコンテナサポート
#include <Eigen/StdVector>
#include <Eigen/StdList>
#include <Eigen/StdDeque>

// 各サポート
// #include <Eigen/CholmodSupport>
// #include <Eigen/MetisSupport>
// #include <Eigen/OrderingMethods>
// #include <Eigen/PardisoSupport>
// #include <Eigen/PaStiXSupport>
// #include <Eigen/SuperLUSupport>
// #include <Eigen/SPQRSupport>
// #include <Eigen/UmfPackSupport>

// その他
#include <Eigen/IterativeLinearSolvers>
#include <Eigen/QtAlignedMalloc>

// @note unsupportedフォルダは除外