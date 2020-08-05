//
// Created by zqlxt on 2020/3/29.
//
#ifndef ZQLPLAYER_ZQLPLAYERLOG_H
#define ZQLPLAYER_ZQLPLAYERLOG_H

#include "android/log.h"

#define LOGD(FORMAT, ...) __android_log_print(ANDROID_LOG_DEBUG,"zqlplayer",FORMAT, ##__VA_ARGS__);
#define LOGE(FORMAT, ...) __android_log_print(ANDROID_LOG_ERROR,"zqlplayer",FORMAT, ##__VA_ARGS__);

#endif //ZQLPLAYER_ZQLPLAYERLOG_H
