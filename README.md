# 3J_MLA
多倍長演算のプログラム

## Description
多倍長演算で円周率を計算するプログラムです.計算アルゴリズムはゼータ関数$\zeta(s)$で$s=4$のとき
の値から円周率$\pi$を計算します.

$$\zeta(4) = \sum_{n=1}^{\infty} \frac{1}{n^4} = \frac{\pi^4}{90}$$

## Directory structure

```
.
├── MLA.c : 基数変更前のプログラム
├── README.md 
├── ml_repo.c : メイン関数
├── ml_repo.exe
├── mulprec.c : 10000進数における関数保存ファイル
├── mulprec.h 
├── mulprec.o
└── repo : レポート
```

## Compile
```
gcc -Wall -c mulprec.c
gcc -Wall -o ml_repo.exe ml_repo.c mulprec.o -lm
```