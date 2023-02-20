#ifndef CLIENT_H
#define CLIENT_H

#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>

typedef void (*SIGNAL1CALLBACK)(const char*);
typedef void (*SIGNAL2CALLBACK)(const int, const char*);
typedef void (*METHOD1CALLBACK)(const char *, const bool isFail);
typedef void (*METHOD2CALLBACK)(const char *, const int, const bool isFail);

typedef struct
{
  METHOD1CALLBACK callback1;
  METHOD2CALLBACK callback2;
} METHOD_CALLBACK_T;

typedef struct
{
  SIGNAL1CALLBACK callback1;
  SIGNAL2CALLBACK callback2;
} SIGNAL_CALLBACK_T;

/////////////////////////////////////////////////////////////////////////////////////////
// Thread functions' definition
/////////////////////////////////////////////////////////////////////////////////////////
bool initialize();
void uninitialize();

void registerSignalCallback(SIGNAL_CALLBACK_T *callback);
void registerMethodCallback(METHOD_CALLBACK_T *callback);
//void My_method_1(const char * in_arg, char** out_arg, GError** pError);
void My_method_1_Async(const char * in_arg);
//void My_method_2(const int in_arg1, const int in_arg2, char **out_arg1, int *out_arg2, GError** pError);
void My_method_2_Async(const int in_arg1, const int in_arg2);

int startDBusCommunication();
int stopDBusCommunication();

#endif
