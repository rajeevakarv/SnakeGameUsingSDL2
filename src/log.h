#ifndef __LOG__
#define __LOG__

#include <linux/unistd.h>
#include <string.h>
#include <sys/syscall.h>
#include <unistd.h>

#define S1(x) #x
#define S2(x) S1(x)
#define __FILENAME__ (strrchr(__FILE__, '/') ? strrchr(__FILE__, '/') + 1 : __FILE__)
#define LOCATION S2(__LINE__)

#ifdef __ANDROID__
#include <android/log.h>
#define smu_log(a, format, ...) __android_log_print(a, "SMARTMU", format, ##__VA_ARGS__)
#endif //__ANDROID__

// Converting the result to long since 64Bit uses long and 32bit uses int.
#define getmyid static_cast<long>(syscall(__NR_gettid))

#if defined(__ANDROID__)
#define logd(format, ...) smu_log(ANDROID_LOG_DEBUG, "#(%ld) [ %s : %s] " format, getmyid, __FILENAME__, LOCATION, ##__VA_ARGS__)
#define logi(format, ...) smu_log(ANDROID_LOG_INFO, "#(%ld) [ %s : %s] " format, getmyid, __FILENAME__, LOCATION, ##__VA_ARGS__)
#define loge(format, ...) smu_log(ANDROID_LOG_ERROR, "#(%ld) [ %s : %s] " format, getmyid, __FILENAME__, LOCATION, ##__VA_ARGS__)
#define logw(format, ...) smu_log(ANDROID_LOG_WARN, "#(%ld) [ %s : %s] " format, getmyid, __FILENAME__, LOCATION, ##__VA_ARGS__)
#else
#include <stdio.h>
#define logd(format, ...) printf("%s :" LOCATION "#(%ld) " format, __FILENAME__, getmyid, ##__VA_ARGS__);
#define logi(format, ...) printf("%s :" LOCATION "#(%ld) " format, __FILENAME__, getmyid, ##__VA_ARGS__);
#define loge(format, ...) printf("%s :" LOCATION "#(%ld) " format, __FILENAME__, getmyid, ##__VA_ARGS__);
#define logw(format, ...) printf("%s :" LOCATION "#(%ld) " format, __FILENAME__, getmyid, ##__VA_ARGS__);
#endif //__ANDROID__

#endif //__LOG__
