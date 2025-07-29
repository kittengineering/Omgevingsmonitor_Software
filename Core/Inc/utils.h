/*
 * utils.h
 *
 *  Created on: May 16, 2023
 *      Author: frank
 */

#ifndef INC_UTILS_H_
#define INC_UTILS_H_

#include <stdarg.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>

typedef enum {
	VERBOSE_NONE = 0,
  VERBOSE_MINIMAL = 1,
  VERBOSE_INFO = 2,
  VERBOSE_ALL = 3
} VerboseLevel;

bool TimestampIsReached(uint32_t timestamp);
void CreateLine(VerboseLevel verboseLevel, char* tag, char* format, ...);
void SetVerboseLevel(VerboseLevel level);
uint8_t GetVerboseLevel();
void BinaryReleaseInfo(void);
void errorHandler(const char * func, const uint32_t line, const char * file);

#define Info(...)               CreateLine(VERBOSE_INFO, "I", __VA_ARGS__)
#define Warning(...)            CreateLine(VERBOSE_MINIMAL, "W", __VA_ARGS__)
#define Error(...)              CreateLine(VERBOSE_MINIMAL, "E", __VA_ARGS__)
#define Fatal(...)              CreateLine(VERBOSE_MINIMAL, "F", __VA_ARGS__)
#define Debug(...)              CreateLine(VERBOSE_ALL, "D", __VA_ARGS__)

#endif
