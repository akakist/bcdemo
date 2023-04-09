#ifndef ___________GUARD_VERSION_H
#define ___________GUARD_VERSION_H
#define GUARD_VERSION 0x00010201
#define GUARD_VERSION_S "1.2.1"
#define USER_AGENT_DESKTOP "Desktop"
#ifdef __MACH__
#define USER_AGENT_ANDROID "IOS"
#else
#define USER_AGENT_ANDROID "Android-NDK"
#endif
#define GUARD_URL_SCHEME "tl"

#endif // DS_VERSION_H
