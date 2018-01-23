LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := locnet_al

CG_SUBDIRS := .\

# Add more subdirs here, like src/subdir1 src/subdir2

MY_PATH := $(LOCAL_PATH)

LOCAL_PATH := "/media/root/USB/dosbox2.0/com.fishstix.dbox/src/main/jni/locnet_al"

CG_SRCDIR := $(LOCAL_PATH)
LOCAL_CFLAGS :=	-I$(LOCAL_PATH)/include \
				$(foreach D, $(CG_SUBDIRS), -I$(CG_SRCDIR)/$(D)) \
				-I$(LOCAL_PATH)/../fishstix/include \
				-I$(LOCAL_PATH)/../sdl/include \
				-I$(LOCAL_PATH)/../dosbox \
				-I$(LOCAL_PATH)/../dosbox/include \
				-I$(LOCAL_PATH)/../dosbox/src \
				-I$(LOCAL_PATH) 
				
				
LOCAL_PATH := $(MY_PATH)

#Change C++ file extension as appropriate
LOCAL_CPP_EXTENSION := .cpp

LOCAL_SRC_FILES := $(foreach F, $(CG_SUBDIRS), $(addprefix $(F)/,$(notdir $(wildcard $(LOCAL_PATH)/$(F)/*.cpp))))
LOCAL_CPPFLAGS := $(LOCAL_CFLAGS)
LOCAL_CXXFLAGS := $(LOCAL_CFLAGS)


include $(BUILD_STATIC_LIBRARY)
