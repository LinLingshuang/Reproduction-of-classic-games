#pragma once
#include<io.h>
#include<process.h>
#include<direct.h>
#include<windows.h>
#define access _access
#define F_OK 0
#define getcwd _getcwd
#define chdir _chdir
#define unlink _unlink
#define dup2 _dup2
#define sleep Sleep
#define isatty _isatty
#ifdef _WIN64
typedef __int64 ssize_t;
#else
typedef long ssize_t;
#endif