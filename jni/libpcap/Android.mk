LOCAL_PATH := $(call my-dir)
include $(CLEAR_VARS)
LOCAL_MODULE:= libpcap
LOCAL_SRC_FILES:= \
	pcap-linux.c \
	fad-null.c \
	pcap.c \
	inet.c \
	gencode.c \
	optimize.c \
	nametoaddr.c \
	etherent.c \
	savefile.c \
	sf-pcap.c \
	sf-pcap-ng.c \
	pcap-common.c \
	bpf_image.c \
	bpf_dump.c \
	scanner.c \
	grammar.c \
	bpf_filter.c \
	version.c 
#include $(BUILD_EXECUTABLE)
LOCAL_CFLAGS	:= -DSYS_ANDROID=1 -Dyylval=pcap_lval -DHAVE_CONFIG_H  -D_U_="__attribute__((unused))" -I$(LOCAL_PATH)
LOCAL_LDLIBS	:= -llog
LOCAL_MODULE:= libpcap

include $(BUILD_STATIC_LIBRARY)
