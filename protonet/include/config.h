#ifndef CONFIG_H
#define CONFIG_H

#pragma once

#ifdef _WIN32
#include <Windows.h>
#include <stdio.h>
#include <stdint.h>
#pragma comment(lib,"user32.lib")
#pragma comment(lib,"ws2_32.lib")
#endif

#endif