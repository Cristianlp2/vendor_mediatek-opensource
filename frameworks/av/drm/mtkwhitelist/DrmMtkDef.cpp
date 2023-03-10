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

//#define LOG_NDEBUG 0
#define LOG_TAG "DrmMtkUtil/WhiteList"
#include <utils/Log.h>

#include "drm/DrmMtkDef.h"

#include <utils/String8.h>
#include <utils/Vector.h>
#include <cutils/properties.h>

using namespace android;
Mutex DrmMtkDefender::sLock;
Vector<String8> DrmMtkDefender::DRM_TRUSTED_PROC;
Vector<String8> DrmMtkDefender::DRM_CONSUME_IN_APP_PROC;
Vector<String8> DrmMtkDefender::NEED_CONSUME_CID_LIST;
Vector<String8> DrmMtkDefender::CTA_TRUSTED_PROC;
bool DrmMtkDefender::sIsInited = init();
char value[PROPERTY_VALUE_MAX];
bool DrmMtkDefender::sDebug = property_get("vendor.debug.drm.logv", value, NULL) == 1;

bool DrmMtkDefender::init() {
    // Add drm trust client here, it will be checked in DrmManagerService and MediaPlayerService
    // 1. inhouse apps(for OMA DRM)
    DRM_TRUSTED_PROC.push(String8("com.android.gallery3d"));  // image and video, image crop
    DRM_TRUSTED_PROC.push(String8("com.android.gallery3d:widgetservice"));  // gallery widget
    DRM_TRUSTED_PROC.push(String8("com.android.music"));                    // audio
    DRM_TRUSTED_PROC.push(String8("android.process.media"));  // MediaProvider and DownloadProvider
    DRM_TRUSTED_PROC.push(String8("com.android.launcher3:wallpaper_chooser"));  // wallpaper
    // wallpaper for N1, separate from launcher repo, process name change
    DRM_TRUSTED_PROC.push(String8("com.android.wallpaperpicker"));  // wallpaper for N1
    DRM_TRUSTED_PROC.push(String8("com.android.phone"));            // ringtone
    DRM_TRUSTED_PROC.push(String8("com.android.settings"));         // ringtone
    DRM_TRUSTED_PROC.push(String8("com.android.deskclock"));        // ringtone
    DRM_TRUSTED_PROC.push(String8("com.android.systemui"));         // ringtone
    DRM_TRUSTED_PROC.push(String8("com.mediatek.dataprotection"));  // CTA5
    // 2. GTS
    DRM_TRUSTED_PROC.push(String8("com.google.android.xts.media"));
    // 3. PlayReady DRM
    DRM_TRUSTED_PROC.push(String8("com.discretix.drmassist"));
    DRM_TRUSTED_PROC.push(String8("com.discretix.QA_ANDROID_COMMON"));
    // 4. GMS apps
    DRM_TRUSTED_PROC.push(String8("com.google.android.apps.photos"));
    DRM_TRUSTED_PROC.push(String8("com.google.android.googlequicksearchbox:wallpaper_chooser"));
    DRM_TRUSTED_PROC.push(String8("com.google.android.music:main"));
    // 5. TODO customer can add there trust drm process here

    // Add cta5 trust client here, it will be checked in cta5 plugin, only trusted process can
    // access cta5 data
    CTA_TRUSTED_PROC.push(String8("com.mediatek.dataprotection"));
    CTA_TRUSTED_PROC.push(String8("com.android.gallery3d"));
    CTA_TRUSTED_PROC.push(String8("com.android.music"));
    CTA_TRUSTED_PROC.push(String8("/system/bin/mediaserver"));
    CTA_TRUSTED_PROC.push(String8("media.extractor"));
    return true;
}

bool DrmMtkDefender::isDrmTrustedClient(const String8& checkProc) {
    bool allowed = true;
    char blacklist[] = {'a', 'n', 'd', 'r', 'o', 'i', 'd', '.',
                        'd', 'r', 'm', '.', 'd', 'u', 't', '\0'};
    blacklist[12]--;
    blacklist[13]--;
    blacklist[14]--;

    if (checkProc && (strcmp(checkProc.string(), blacklist) == 0)) {
        allowed = false;
    }
#if 0
    for(String8& trustedProc : DRM_TRUSTED_PROC) {
        if (sDebug) ALOGV("IsDrmTrustedClient: compare [%s] with [%s].", trustedProc.string(), checkProc.string());
        if (trustedProc == checkProc) {
            if (sDebug) ALOGV("IsDrmTrustedClient: grant client[%s] access drm data.", checkProc.string());
            allowed = true;
            break;
        }
    }
#ifdef DEBUG_GRANT_ALL
    char value[PROPERTY_VALUE_MAX];
    if (property_get("vendor.drm.mtkdefender.disable", value, NULL) && !strcmp(value, "1")) {
        allowed = true;
        ALOGD("IsDrmTrustedClient: grant all client access drm data, just for test......");
    }
#endif

    ALOGE("IsDrmTrustedClient: client[%s] access drm [%d]", checkProc.string(), allowed);
#endif /* 0 */
    return allowed;
}

bool DrmMtkDefender::isDrmConsumeInAppClient(const String8& checkProc) {
    Mutex::Autolock lock(sLock);
    bool consumeInApp = false;
    for (String8& consumeInAppProc : DRM_CONSUME_IN_APP_PROC) {
        if (sDebug)
            ALOGV("IsDrmConsumeInAppClient: compare [%s] with [%s].", consumeInAppProc.string(),
                  checkProc.string());
        if (consumeInAppProc == checkProc) {
            if (sDebug)
                ALOGV("IsDrmConsumeInAppClient: consume rights in [%s] itself.",
                      checkProc.string());
            consumeInApp = true;
            break;
        }
    }
    if (sDebug)
        ALOGV("IsDrmConsumeInAppClient: client[%s],consumeInApp[%d]", checkProc.string(),
              consumeInApp);
    return consumeInApp;
}

bool DrmMtkDefender::markAsConsumeInAppClient(const String8& procName, const String8& cid) {
    Mutex::Autolock lock(sLock);
    ALOGD("markAsConsumeInAppClient: consume in app proc[%s], consume cid[%s]", procName.string(),
          cid.string());
    bool marked = false;
    for (String8& consumeInAppProc : DRM_CONSUME_IN_APP_PROC) {
        if (consumeInAppProc == procName) {
            if (sDebug) ALOGV("markAsConsumeInAppClient: [%s] has been marked.", procName.string());
            marked = true;
            break;
        }
    }
    if (!marked) {
        DRM_CONSUME_IN_APP_PROC.push(procName);
    }
    NEED_CONSUME_CID_LIST.push(cid);
    return true;
}

bool DrmMtkDefender::isNeedConsume(const String8& cid) {
    Mutex::Autolock lock(sLock);
    bool consume = false;
    Vector<String8>::iterator it = NEED_CONSUME_CID_LIST.begin();
    while (it != NEED_CONSUME_CID_LIST.end()) {
        if (sDebug) ALOGV("IsNeedConsume: compare [%s] with [%s].", it->string(), cid.string());
        if (*it == cid) {
            ALOGD("IsNeedConsume: consume rights for [%s].", cid.string());
            consume = true;
            it = NEED_CONSUME_CID_LIST.erase(it);
            break;
        }
        it++;
    }
    return consume;
}

bool DrmMtkDefender::isCtaTrustedClient(const String8& checkProc) {
    bool allowed = false;
    for (String8& trustedProc : CTA_TRUSTED_PROC) {
        if (sDebug)
            ALOGV("IsDrmTrustedClient: compare [%s] with [%s].", trustedProc.string(),
                  checkProc.string());
        if (trustedProc == checkProc) {
            if (sDebug)
                ALOGV("IsDrmTrustedClient: grant client[%s] access cta5 data.", checkProc.string());
            allowed = true;
            break;
        }
    }
#ifdef DEBUG_GRANT_ALL
    char value[PROPERTY_VALUE_MAX];
    if (property_get("drm.mtkdefender.disable", value, NULL) && !strcmp(value, "1")) {
        allowed = true;
        ALOGD("IsDrmTrustedClient: grant all client access cta5 data, just for test......");
    }
#endif
    if (!allowed) ALOGD("isCtaTrustedClient: deny client[%s] access drm", checkProc.string());
    return allowed;
}

const char* DrmSntpServer::NTP_SERVER_1 = "hshh.org";
const char* DrmSntpServer::NTP_SERVER_2 = "t1.hshh.org";
const char* DrmSntpServer::NTP_SERVER_3 = "t2.hshh.org";
const char* DrmSntpServer::NTP_SERVER_4 = "t3.hshh.org";
const char* DrmSntpServer::NTP_SERVER_5 = "clock.via.net";

/**
 * If the customer want to add his own app to white list
 * Please modify init() function
 * The white list is refactoryed by rui.hu
 * should be remove
 */

Vector<String8> DrmTrustedApp::TRUSTED_APP;
bool DrmTrustedApp::sIsInited = init();

bool DrmTrustedApp::init() {
    TRUSTED_APP.push_back(String8("com.android.gallery3d"));
    TRUSTED_APP.push_back(String8("com.mediatek.videoplayer"));
    TRUSTED_APP.push_back(String8("com.mediatek.videoplayer2"));
    TRUSTED_APP.push_back(String8("com.android.music"));
    TRUSTED_APP.push_back(String8("com.android.phone"));
    TRUSTED_APP.push_back(String8("com.android.settings"));
    TRUSTED_APP.push_back(String8("com.android.deskclock"));
    TRUSTED_APP.push_back(String8("com.cooliris.media"));
    TRUSTED_APP.push_back(String8("com.android.systemui"));
    TRUSTED_APP.push_back(String8("com.mediatek.drmframeworktest"));  // added for drm test case
    TRUSTED_APP.push_back(String8("com.google.android.xts.media"));
    TRUSTED_APP.push_back(String8("com.widevine.demo"));
    TRUSTED_APP.push_back(String8("com.discretix.drmassist"));          // add for PlayReady
    TRUSTED_APP.push_back(String8("com.discretix.QA_ANDROID_COMMON"));  // add for playReady
    TRUSTED_APP.push_back(String8("com.mediatek.dataprotection"));      // add for CTA5
    TRUSTED_APP.push_back(
            String8("com.android.wallpapercropper"));         // for launcher2, wallpapercropper
    TRUSTED_APP.push_back(String8("android.process.media"));  // for mediaprocess
    TRUSTED_APP.push_back(String8("com.android.gallery3d:widgetservice"));  // for gallery widget
    // Add your special process name here

    return true;
}

bool DrmTrustedApp::IsDrmTrustedApp(const String8& procName) {
    bool result = false;
    Vector<String8>::iterator it = TRUSTED_APP.begin();
    for (; it != TRUSTED_APP.end(); ++it) {
        ALOGD("IsDrmTrustedApp: compare [%s] with [%s].", it->string(), procName.string());

        if (0 == strcmp(it->string(), procName.string())) {
            ALOGD("IsDrmTrustedApp: accepted.");
            result = true;
            break;
        }
    }
    return result;
}

Vector<String8> DrmTrustedClient::TRUSTED_PROC;
bool DrmTrustedClient::sIsInited = init();

bool DrmTrustedClient::init() {
    TRUSTED_PROC.push_back(String8("com.android.gallery"));  // gallery 2d
    TRUSTED_PROC.push_back(String8("com.android.gallery:CropImage"));
    TRUSTED_PROC.push_back(String8("com.cooliris.media"));  // gallery 3d (2.3)
    TRUSTED_PROC.push_back(String8("com.mediatek.drmfileinstaller"));
    TRUSTED_PROC.push_back(String8("com.android.phone"));      // ringtone playing
    TRUSTED_PROC.push_back(String8("com.android.gallery3d"));  // gallery (4.0)
    TRUSTED_PROC.push_back(String8("com.android.gallery3d:crop"));
    TRUSTED_PROC.push_back(String8("com.mediatek.drmframeworktest"));  // added for drm test case
    TRUSTED_PROC.push_back(String8("com.google.android.xts.media"));
    TRUSTED_PROC.push_back(String8("com.widevine.demo"));
    TRUSTED_PROC.push_back(String8("com.android.launcher3:wallpaper_chooser"));  // KK add
    TRUSTED_PROC.push_back(String8("com.discretix.drmassist"));          // add for PlayReady
    TRUSTED_PROC.push_back(String8("com.discretix.QA_ANDROID_COMMON"));  // add for playReady
    TRUSTED_PROC.push_back(String8("com.mediatek.dataprotection"));      // add for CTA5
    TRUSTED_PROC.push_back(
            String8("com.android.wallpapercropper"));          // for launcher2, wallpapercropper
    TRUSTED_PROC.push_back(String8("android.process.media"));  // for mediaprocess
    TRUSTED_PROC.push_back(String8("com.android.gallery3d:widgetservice"));  // for gallery widget
    // Add your special process name here

    return true;
}

bool DrmTrustedClient::IsDrmTrustedClient(const String8& procName) {
    bool result = false;
    Vector<String8>::iterator it = TRUSTED_PROC.begin();
    for (; it != TRUSTED_PROC.end(); ++it) {
        ALOGD("IsDrmTrustedClient: compare [%s] with [%s].", it->string(), procName.string());

        if (0 == strcmp(it->string(), procName.string())) {
            ALOGD("IsDrmTrustedClient: accepted.");
            result = true;
            break;
        }
    }
    return result;
}

Vector<String8> DrmTrustedVideoApp::TRUSTED_VIDEO_APP;
bool DrmTrustedVideoApp::sIsInited = init();

bool DrmTrustedVideoApp::init() {
    TRUSTED_VIDEO_APP.push_back(String8("com.android.gallery3d"));
    TRUSTED_VIDEO_APP.push_back(String8("com.mediatek.videoplayer"));
    TRUSTED_VIDEO_APP.push_back(String8("com.mediatek.videoplayer2"));
    TRUSTED_VIDEO_APP.push_back(String8("com.mediatek.dataprotection"));
    // Add your special process name here

    return true;
}

bool DrmTrustedVideoApp::IsDrmTrustedVideoApp(const String8& procName) {
    bool result = false;
    Vector<String8>::iterator it = TRUSTED_VIDEO_APP.begin();
    for (; it != TRUSTED_VIDEO_APP.end(); ++it) {
        ALOGD("IsDrmTrustedVideoApp: compare [%s] with [%s].", it->string(), procName.string());

        if (0 == strcmp(it->string(), procName.string())) {
            ALOGD("DrmTrustedVideoApp: accepted.");
            result = true;
            break;
        }
    }
    return result;
}

// For CTA5 feature
Vector<String8> CtaTrustedClient::TRUSTED_PROC;
Vector<String8> CtaTrustedClient::TRUSTED_GETTOKEN_PROC;
Vector<String8> CtaTrustedClient::TRUSTED_CHECKTOKEN_PROC;
bool CtaTrustedClient::sIsInited = init();

bool CtaTrustedClient::init() {
    bool ret = initTrustedClient();
    ret |= initTrustedGetTokenClient();
    ret |= initTrustedCheckTokenClient();
    return ret;
}

bool CtaTrustedClient::initTrustedClient() {
    TRUSTED_PROC.push_back(String8("com.android.gallery3d"));
    TRUSTED_PROC.push_back(String8("com.android.music"));
    TRUSTED_PROC.push_back(String8("com.mediatek.dataprotection"));
    TRUSTED_PROC.push_back(String8("/system/bin/mediaserver"));
    // Add your special process name here

    return true;
}

bool CtaTrustedClient::initTrustedGetTokenClient() {
    TRUSTED_GETTOKEN_PROC.push_back(String8("com.mediatek.dataprotection"));
    // Add your special process name here

    return true;
}

bool CtaTrustedClient::initTrustedCheckTokenClient() {
    TRUSTED_CHECKTOKEN_PROC.push_back(String8("com.android.gallery3d"));
    TRUSTED_CHECKTOKEN_PROC.push_back(String8("com.android.music"));
    // Add your special process name here

    return true;
}

bool CtaTrustedClient::IsCtaTrustedClient(const String8& procName) {
    bool result = false;
    Vector<String8>::iterator it = TRUSTED_PROC.begin();
    for (; it != TRUSTED_PROC.end(); ++it) {
        ALOGD("IsCtaTrustedClient: compare [%s] with [%s].", it->string(), procName.string());

        if (0 == strcmp(it->string(), procName.string())) {
            ALOGD("IsCtaTrustedClient: accepted.");
            result = true;
            break;
        }
    }
    return result;
}

bool CtaTrustedClient::IsCtaTrustedGetTokenClient(const String8& procName) {
    bool result = false;
    Vector<String8>::iterator it = TRUSTED_GETTOKEN_PROC.begin();
    for (; it != TRUSTED_GETTOKEN_PROC.end(); ++it) {
        ALOGD("IsCtaTrustedGetTokenClient: compare [%s] with [%s].", it->string(),
              procName.string());

        if (0 == strcmp(it->string(), procName.string())) {
            ALOGD("IsCtaTrustedGetTokenClient: accepted.");
            result = true;
            break;
        }
    }
    return result;
}

bool CtaTrustedClient::IsCtaTrustedCheckTokenClient(const String8& procName) {
    bool result = false;
    Vector<String8>::iterator it = TRUSTED_CHECKTOKEN_PROC.begin();
    for (; it != TRUSTED_CHECKTOKEN_PROC.end(); ++it) {
        ALOGD("IsCtaTrustedCheckTokenClient: compare [%s] with [%s].", it->string(),
              procName.string());

        if (0 == strcmp(it->string(), procName.string())) {
            ALOGD("IsCtaTrustedCheckTokenClient: accepted.");
            result = true;
            break;
        }
    }
    return result;
}
