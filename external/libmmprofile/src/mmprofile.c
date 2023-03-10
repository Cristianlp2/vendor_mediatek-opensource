/*
 * Copyright (C) 2021 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <sys/mman.h>
#include <dlfcn.h>
#include <log/log.h>
#include <cutils/atomic.h>
#include <hardware/hardware.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/ioctl.h>
#include <string.h>
#include <stdlib.h>
#include <sched.h>
#include <sys/resource.h>
#include <linux/fb.h>
#include <wchar.h>
#include <pthread.h>

#include <linux/mmprofile_internal.h>
#include "mmprofile_function.h"

#ifdef LOG_TAG
#undef LOG_TAG
#endif
#define LOG_TAG "MMProfile"
#define LogPrint(...) __android_log_print(ANDROID_LOG_DEBUG, LOG_TAG, ##__VA_ARGS__)

static int MMProfile_FD = -1;
static pthread_mutex_t MMProfile_FDMutex = PTHREAD_MUTEX_INITIALIZER;

#define likely(x) __builtin_expect(!!(x), 1)
#define unlikely(x) __builtin_expect(!!(x), 0)

// Internal functions begin
static unsigned int MMProfileInitFD(void) {
    unsigned int ret = 1;
    pthread_mutex_lock(&MMProfile_FDMutex);
    if (unlikely(MMProfile_FD < 0)) {
        MMProfile_FD = open("/sys/kernel/debug/mmprofile/mmp", O_RDONLY);
        if (MMProfile_FD < 0) {
            ret = 0;
        }
    }
    pthread_mutex_unlock(&MMProfile_FDMutex);
    return ret;
}

static unsigned int IsMMProfileEnabled(void) {
    unsigned int enable = 0;
    if (MMProfileInitFD() == 0) return 0;
    ioctl(MMProfile_FD, MMP_IOC_ISENABLE, &enable);
    return enable;
}
// Internal functions end

// Exposed APIs begin
MMP_Event MMProfileRegisterEvent(MMP_Event parent, const char* name) {
    MMProfile_EventInfo_t EventInfo;

    if (MMProfileInitFD() == 0) return MMP_InvalidEvent;

    if (!IsMMProfileEnabled()) return 0;

    // Register the event.
    if (strlen(name) > MMProfileEventNameMaxLen) {
        memcpy(EventInfo.name, name, MMProfileEventNameMaxLen);
        EventInfo.name[MMProfileEventNameMaxLen] = 0;
    } else
        strncpy(EventInfo.name, name, strlen(name) + 1);
    EventInfo.parentId = parent;
    ioctl(MMProfile_FD, MMP_IOC_REGEVENT, &EventInfo);
    LogPrint("Register Event: %s id=%d Parent=%d\n", EventInfo.name, EventInfo.parentId, parent);
    return EventInfo.parentId;
}

MMP_Event MMProfileFindEvent(MMP_Event parent, const char* name) {
    MMProfile_EventInfo_t EventInfo;

    if (MMProfileInitFD() == 0) return MMP_InvalidEvent;

    if (!IsMMProfileEnabled()) return 0;

    if (strlen(name) > MMProfileEventNameMaxLen) {
        memcpy(EventInfo.name, name, MMProfileEventNameMaxLen);
        EventInfo.name[MMProfileEventNameMaxLen] = 0;
    } else
        strncpy(EventInfo.name, name, strlen(name) + 1);
    EventInfo.parentId = parent;
    ioctl(MMProfile_FD, MMP_IOC_FINDEVENT, &EventInfo);
    LogPrint("Find Event: %s id=%d\n", EventInfo.name, EventInfo.parentId);
    return EventInfo.parentId;
}

void MMProfileEnableEvent(MMP_Event event, long enable) {
    unsigned int cmd[3];
    if (MMProfileInitFD() == 0) return;

    cmd[0] = event;
    cmd[1] = enable;
    cmd[2] = 0;
    ioctl(MMProfile_FD, MMP_IOC_ENABLEEVENT, cmd);
    LogPrint("Enable event: id=%d enable=%ld\n", event, enable);
}

void MMProfileEnableEventRecursive(MMP_Event event, long enable) {
    unsigned int cmd[3];
    if (MMProfileInitFD() == 0) return;

    cmd[0] = event;
    cmd[1] = enable;
    cmd[2] = 1;
    ioctl(MMProfile_FD, MMP_IOC_ENABLEEVENT, cmd);
    LogPrint("Enable event: id=%d enable=%ld\n", event, enable);
}

long MMProfileQueryEnable(MMP_Event event) {
    unsigned int enable = (unsigned int)event;
    if (MMProfileInitFD() == 0) return 0;
    ioctl(MMProfile_FD, MMP_IOC_ISENABLE, &enable);
    return enable;
}

void MMProfileLog(MMP_Event event, MMP_LogType type) { MMProfileLogEx(event, type, 0, 0); }

void MMProfileLogEx(MMP_Event event, MMP_LogType type, unsigned long data1, unsigned long data2) {
    unsigned int cmd[4];
    if (MMProfileInitFD() == 0) return;
    cmd[0] = event;
    cmd[1] = type;
    cmd[2] = data1;
    cmd[3] = data2;
    ioctl(MMProfile_FD, MMP_IOC_LOG, cmd);
}

long MMProfileLogMeta(MMP_Event event, MMP_LogType type, MMP_MetaData_t* pMetaData) {
    int ret = 0;
    MMProfile_MetaLog_t MetaLog;
    if (MMProfileInitFD() == 0) return -1;

    MetaLog.id = event;
    MetaLog.type = type;
    MetaLog.meta_data = *pMetaData;
    ret = ioctl(MMProfile_FD, MMP_IOC_METADATALOG, &MetaLog);
    return ret;
}

long MMProfileLogMetaStringEx(MMP_Event event, MMP_LogType type, unsigned long data1,
                              unsigned long data2, const char* str) {
    int ret = 0;
    MMP_MetaData_t MetaData;

    if (MMProfileInitFD() == 0) return -1;

    if (ioctl(MMProfile_FD, MMP_IOC_TRYLOG, event) != 0) return -1;

    MetaData.data1 = data1;
    MetaData.data2 = data2;
    MetaData.data_type = MMProfileMetaStringMBS;
    MetaData.size = strlen(str) + 1;
    MetaData.pData = malloc(MetaData.size);
    if (!MetaData.pData) return -1;
    strncpy((char*)MetaData.pData, str, strlen(str) + 1);
    ret = MMProfileLogMeta(event, type, &MetaData);
    free(MetaData.pData);
    return ret;
}

long MMProfileLogMetaString(MMP_Event event, MMP_LogType type, const char* str) {
    return MMProfileLogMetaStringEx(event, type, 0, 0, str);
}

long MMProfileLogMetaStructure(MMP_Event event, MMP_LogType type,
                               MMP_MetaDataStructure_t* pMetaData) {
    int ret = 0;
    MMP_MetaData_t MetaData;

    if (MMProfileInitFD() == 0) return -1;

    if (ioctl(MMProfile_FD, MMP_IOC_TRYLOG, event) != 0) return -1;

    MetaData.data1 = pMetaData->data1;
    MetaData.data2 = pMetaData->data2;
    MetaData.data_type = MMProfileMetaStructure;
    MetaData.size = 32 + pMetaData->struct_size;
    MetaData.pData = malloc(MetaData.size);
    if (!MetaData.pData) return -1;
    memcpy(MetaData.pData, pMetaData->struct_name, 32);
    memcpy((void*)((unsigned long)(MetaData.pData) + 32), pMetaData->pData, pMetaData->struct_size);
    ret = MMProfileLogMeta(event, type, &MetaData);
    free(MetaData.pData);
    return ret;
}

long MMProfileLogMetaBitmap(MMP_Event event, MMP_LogType type, MMP_MetaDataBitmap_t* pMetaData) {
    int ret = 0;
    MMP_MetaData_t MetaData;
    char* pSrc;
    char* pDst;
    int pitch;

    if (MMProfileInitFD() == 0) return -1;

    if (ioctl(MMProfile_FD, MMP_IOC_TRYLOG, event) != 0) return -1;

    MetaData.data1 = pMetaData->data1;
    MetaData.data2 = pMetaData->data2;
    MetaData.data_type = MMProfileMetaBitmap;
    MetaData.size = sizeof(MMP_MetaDataBitmap_t) + pMetaData->data_size;
    MetaData.pData = malloc(MetaData.size);
    if (!MetaData.pData) return -1;
    pSrc = (char*)pMetaData->pData + pMetaData->start_pos;
    pDst = (char*)((unsigned long)(MetaData.pData) + sizeof(MMP_MetaDataBitmap_t));
    pitch = pMetaData->pitch;
    memcpy(MetaData.pData, pMetaData, sizeof(MMP_MetaDataBitmap_t));
    if (pitch < 0) ((MMP_MetaDataBitmap_t*)(MetaData.pData))->pitch = -pitch;
    if ((pitch > 0) && (pMetaData->down_sample_x == 1) && (pMetaData->down_sample_y == 1))
        memcpy(pDst, pSrc, pMetaData->data_size);
    else {
        unsigned int x, y, x0, y0;
        unsigned int new_width, new_height;
        unsigned int Bpp = pMetaData->bpp / 8;
        new_width = (pMetaData->width - 1) / pMetaData->down_sample_x + 1;
        new_height = (pMetaData->height - 1) / pMetaData->down_sample_y + 1;
        for (y = 0, y0 = 0; y < pMetaData->height; y0++, y += pMetaData->down_sample_y) {
            if (pMetaData->down_sample_x == 1)
                memcpy(pDst + new_width * Bpp * y0, pSrc + pMetaData->pitch * y,
                       pMetaData->width * Bpp);
            else {
                for (x = 0, x0 = 0; x < pMetaData->width; x0++, x += pMetaData->down_sample_x) {
                    memcpy(pDst + (new_width * y0 + x0) * Bpp,
                           pSrc + pMetaData->pitch * y + x * Bpp, Bpp);
                }
            }
        }
        MetaData.size = sizeof(MMP_MetaDataBitmap_t) + new_width * Bpp * new_height;
    }
    ret = MMProfileLogMeta(event, type, &MetaData);
    free(MetaData.pData);
    return ret;
}

// Exposed APIs end
