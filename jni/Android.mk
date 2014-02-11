LOCAL_PATH := $(call my-dir)
include $(CLEAR_VARS)

LOCAL_MODULE := native-activity-sample

LOCAL_C_INCLUDES := $(LOCAL_PATH)
LOCAL_SRC_FILES := Main.cpp android_native_app_glue.c Game.cpp GraphicsAdapter.cpp Effect.cpp Vector3.cpp Vertex.cpp Wall.cpp DrawableObject.cpp Ball.cpp  Rectangle.cpp Triangle.cpp
LOCAL_LDLIBS := -landroid -lEGL -lGLESv2 -llog

include $(BUILD_SHARED_LIBRARY)
