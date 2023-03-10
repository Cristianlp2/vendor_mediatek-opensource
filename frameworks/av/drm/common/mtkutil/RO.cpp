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

#define LOG_NDEBUG 0
#define LOG_TAG "DrmMtkUtil/RO"
#include <utils/Log.h>

#include <DrmDef.h>
#include <DrmUtil.h>
#include <RO.h>
#include <StrUtil.h>

#include <utils/String8.h>

using namespace android;

Entry::Entry() {
    next = 0xFF;
    type = DrmDef::CONSTRAINT_UNINIT;
    used_count = 0;
    total_count = 0;
    start_time = DrmDef::MIN_START_TIME;
    end_time = DrmDef::MAX_END_TIME;
    interval = 0;
    start_intv = 0;
    end_intv = 0;
}

void Entry::dump() {
    // get String8 for type  ---->
    String8 typeStr("");
    for (int i = DrmDef::CONSTRAINT_COUNT; i <= DrmDef::CONSTRAINT_NONE; i = i << 1) {
        if (0 != (type & i)) {
            typeStr += DrmDef::getConstraintStr(i);
        } else {
            typeStr += "_";
        }
        if (i != DrmDef::CONSTRAINT_NONE) {
            typeStr += "|";
        }
    }
    // get String8 for type <----

    // get String8 for constraints ---->
    String8 conStr("");
    conStr = conStr + "used_count[" + StrUtil::toString(used_count) + "] ";
    conStr = conStr + "total_count[" + StrUtil::toString(total_count) + "] ";

    String8 dt_start_str = StrUtil::toTimeStr((time_t*)(&start_time));
    String8 dt_end_str = StrUtil::toTimeStr((time_t*)(&end_time));
    String8 start_intv_str = StrUtil::toTimeStr((time_t*)(&start_intv));
    String8 end_intv_str = StrUtil::toTimeStr((time_t*)(&end_intv));

    conStr = conStr + "start_time[" + StrUtil::toString(start_time) + "]" + dt_start_str + " ";
    conStr = conStr + "end_time[" + StrUtil::toString(end_time) + "]" + dt_end_str + " ";
    conStr = conStr + "interval[" + StrUtil::toString(interval) + "] ";
    conStr = conStr + "start_intv[" + StrUtil::toString(start_intv) + "]" + start_intv_str + " ";
    conStr = conStr + "end_intv[" + StrUtil::toString(end_intv) + "]" + end_intv_str + " ";
    // get String8 for constraints <----
    if (DrmUtil::sVDebug)
        ALOGV("        next[%s] type[%s] %s", StrUtil::toString(next), typeStr.string(),
              conStr.string());
}

Rights::Rights() {
    memset(key, NULL, DrmDef::DRM_MAX_KEY_LENGTH);

    permission = DrmDef::PERMISSION_NONE;
    entryPtr = NULL;
    for (int i = 0, count = DrmDef::PERMISSION_TOTAL_INDEX; i < count; i++) {
        best[i] = 0xFF;
        num[i] = 0;
    }
}

Rights::~Rights() {
    if (entryPtr != NULL) {
        delete[] entryPtr;
        entryPtr = NULL;
    }
}

void Rights::dump() {
    if (DrmUtil::sVDebug) ALOGV("Rights ---->");
    if (DrmUtil::sVDebug) ALOGV("%s", getGeneralStr().string());

    // print constraint by permission ---->
    for (int i = DrmDef::PERMISSION_PLAY_INDEX; i <= DrmDef::PERMISSION_PRINT_INDEX; i++) {
        String8 pStr = DrmDef::getPermissionStr(i);
        if (DrmUtil::sVDebug) ALOGV("[%s] ---->", pStr.string());
        // print constraint list ---->
        if (best[i] != 0xFF)  // have constraint for the permission
        {
            int entryIndex = best[i];
            while (entryIndex != 0xFF) {
                Entry* entry = &entryPtr[entryIndex];
                // print entry ---->
                if (DrmUtil::sVDebug) ALOGV("    entry[%d] ---->", entryIndex);
                entry->dump();
                if (DrmUtil::sVDebug) ALOGV("    entry[%d] <----", entryIndex);
                // print entry <----
                entryIndex = entry->next;
            }
        }
        // print constraint list <----
        if (DrmUtil::sVDebug) ALOGV("[%s] <----", pStr.string());
    }
    // print constraint by permission <----
    if (DrmUtil::sVDebug) ALOGV("Rights <----");
}

String8 Rights::getGeneralStr() {
    String8 permissionStr("");
    String8 numStr("");
    String8 bestStr("");
    for (int i = DrmDef::PERMISSION_PLAY_INDEX; i <= DrmDef::PERMISSION_PRINT_INDEX; i++) {
        int p = DrmDef::getPermission(i);
        String8 pStr = DrmDef::getPermissionStr(i);
        numStr += StrUtil::toString(num[i]);
        bestStr += StrUtil::toString(best[i]);
        if (permission & p) {
            permissionStr += pStr;
        } else {
            permissionStr += "_";
        }
        if (i != DrmDef::PERMISSION_PRINT_INDEX) {
            permissionStr += "|";
            numStr += "|";
            bestStr += "|";
        }
    }
    String8 allStr("");
    allStr = allStr + "permission[" + permissionStr + "] ";
    allStr = allStr + "num[" + numStr + "] ";
    allStr = allStr + "best[" + bestStr + "] ";
    String8 cidStr(cid);
    allStr = allStr + "cid[" + cid + "] ";
    String8 keyStr(key, DrmDef::DRM_MAX_KEY_LENGTH);
    allStr = allStr + "key[" + keyStr + "] ";

    return allStr;
}

void RO::dump() {
    if (DrmUtil::sVDebug) ALOGV("RO ---->");
    rights.dump();
    if (DrmUtil::sVDebug) ALOGV("RO <----");
}
