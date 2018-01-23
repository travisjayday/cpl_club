# The ARMv7 is significanly faster due to the use of the hardware FPU
APP_ABI := armeabi armeabi-v7a
APP_STL := stlport_static
#STLPORT_FORCE_REBUILD := true
APP_CPPFLAGS += -O2 
APP_PLATFORM := android-9
APP_OPTIM := release
NDK_TOOLCHAIN_VERSION=4.9
