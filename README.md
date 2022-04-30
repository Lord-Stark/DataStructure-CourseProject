# Introduction

A simple `course project` for `data structure`.

In this project, I constructed a function demonstration system with menu to realize the basic operation of `linear list` and `binary tree`.

The introduction of the contents of these files is as follows.

- `src/LinearList/LinearList_SeqLinearlistManagement.c`: Use sequential linear lists to manage multiple linear lists.
- `src/LinearList/LinearList_ChainLinearlistManagement.c`: Use chain stored linear lists to manage multiple linear lists.
- `src/BinaryTree/BinaryTree_SeqLinearlistManagement.c`: Use sequential linear lists to manage multiple binary trees.
- `src/BinaryTree/BinaryTree_ChainLinearlistManagement.c`: Use chain stored linear lists to manage multiple binary trees.

# Build

```bash
mkdir build
cd ./build
mkdir LinearList
mkdir BinaryTree
```

```bash
cd ./src/LinearList
gcc LinearList_ChainLinearlistManagement.c -o ../../build/LinearList/LinearList_ChainLinearlistManagement.exe
gcc LinearList_SeqLinearlistManagement.c -o ../../build/LinearList/LinearList_SeqLinearlistManagement.exe
```

```bash
cd ./src/BinaryTree
gcc BinaryTree_SeqLinearlistManagement.c -o ../../build/BinaryTree/BinaryTree_SeqLinearlistManagement.exe
gcc BinaryTree_ChainLinearlistManagement.c -o ../../build/BinaryTree/BinaryTree_ChainLinearlistManagement.exe
```

# Run

```bash
"./build/ws_server.exe"
"./build/ws_client.exe"
```

# Garbled Character

You can solve `garbled code` problems simply by switching `character sets`.

```bash
chcp 65001
```

# Blog

For more details on this project :

[数据结构课程设计——基于链式存储结构的线性表实现（C语言）](https://blog.csdn.net/WZZ_2363173126/article/details/104197493)

[数据结构课程设计——基于二叉链表的二叉树实现（C语言）](https://blog.csdn.net/WZZ_2363173126/article/details/105005076)
