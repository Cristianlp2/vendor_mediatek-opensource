/*
 * Copyright (C) 2016 The Android Open Source Project
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

#define LOG_TAG "libPowerHal"
#include "utils/Log.h"

#include <stdio.h>
#include <dlfcn.h>
#include <unistd.h>
#include "perfservice.h"
#include "testcase.h"
#include "common.h"

using namespace android;

#ifdef min
#undef min
#endif
#define min(a, b) (((a) < (b)) ? (a) : (b))

static int inited = false;

int (*perfBoostEnable)(int) = NULL;
int (*perfBoostDisable)(int) = NULL;

typedef int (*ena)(int);
typedef int (*disa)(int);

#define LIB_FULL_NAME "libpowerhal.so"

void init() {
    void *handle, *func;

    // only enter once
    inited = true;

    handle = dlopen(LIB_FULL_NAME, RTLD_NOW);
    if (handle == NULL) {
        ALOGE("Can't load library: %s", dlerror());
        return;
    }

    func = dlsym(handle, "perfBoostEnable");
    perfBoostEnable = reinterpret_cast<ena>(func);

    if (perfBoostEnable == NULL) {
        ALOGE("perfBoostEnable error: %s", dlerror());
        dlclose(handle);
        return;
    }

    func = dlsym(handle, "perfBoostDisable");
    perfBoostDisable = reinterpret_cast<disa>(func);

    if (perfBoostDisable == NULL) {
        ALOGE("perfBoostDisable error: %s", dlerror());
        perfBoostEnable = NULL;
        dlclose(handle);
        return;
    }
}

static int checkRealCores(int coresToChk) {
    int nOnline = 0;

    /* ToDo: add cpu present condition to check correct cpu cores*/
    nOnline += (1 == get_int_value(PATH_CPUONLINE_0)) ? 1 : 0;
    nOnline += (1 == get_int_value(PATH_CPUONLINE_1)) ? 1 : 0;
    nOnline += (1 == get_int_value(PATH_CPUONLINE_2)) ? 1 : 0;
    nOnline += (1 == get_int_value(PATH_CPUONLINE_3)) ? 1 : 0;

    return (coresToChk == nOnline) ? 0 : nOnline;
}

static int checkCores(int coresToChk) {
    /* note the CPU hotplug driver is still activated during the test.
     * Other activities might cause cpu cores boost thus impact the check condition.
     * thus it's better to confirm both the PATH_CPU_HOTPLUG_CFG and PATH_CPUONLINE_x
     *  - PATH_CPU_HOTPLUG_CFG is to confirm our writes
     *  - PATH_CPUONLINE_x is to double confirm the real cpu cores while in low load.
     */

    int readBackCores = 0, readBackCpuNum = 0;

    readBackCores = get_int_value(PATH_CPUHOTPLUG_CFG);

    if (readBackCores != coresToChk)
        ALOGE("...<<< FAIL >>>, expected: %d, but: %d", coresToChk, readBackCores);
    else
        ALOGI("...<<< PASS >>>, expected: %d", coresToChk);

    readBackCpuNum = checkRealCores(coresToChk);
    if (readBackCpuNum)
        ALOGI(".................real cores and core cfg are not match, expected: %d, real: %d",
              coresToChk, readBackCpuNum);

    return 0;
}

static int android_server_PerfBoostEnable(int scenario) {
    if (!inited) init();

    if (perfBoostEnable) return perfBoostEnable(scenario);

    ALOGE("perfBoostEnable bypassed!");
    return -1;
}

static int android_server_PerfBoostDisable(int scenario) {
    if (!inited) init();

    if (perfBoostDisable) return perfBoostDisable(scenario);

    ALOGE("perfBoostDisable bypassed!");
    return -1;
}

int main(void) {
    int i, cfgState, scnToSet, coresToChk, sleepTime;
    char str[1024];

    ALOGI("********** libPerfService Test Start **********");

    for (i = 0; testcase_set[i].testPattern; i++) {
        ALOGI("TEST(%d): %s", i, testcase_set[i].testDescription);
        ALOGI(" pattern: %s", testcase_set[i].testPattern);

        // strncpy(str, testcase_set[i].testPattern,
        // min(strlen(testcase_set[i].testPattern),sizeof(str)-1));
        strncpy(str, testcase_set[i].testPattern, sizeof(str) - 1);  // fix Klocwork
        str[min(strlen(testcase_set[i].testPattern), sizeof(str) - 1)] = '\0';

        char* p = strtok(str, ",");
        while (p) {
            // scenario
            if (!strncmp(p, "SCN", 3)) {
                scnToSet = atoi(strtok(NULL, ","));
                cfgState = !(strncmp("ON", strtok(NULL, ","), sizeof("ON")));
#ifdef VERBOSE_OUTPUT
                ALOGI("c:%d, s:%d", scnToSet, cfgState);
#endif
                if (cfgState)
                    android_server_PerfBoostEnable(scnToSet);
                else
                    android_server_PerfBoostDisable(scnToSet);
            } else
                // check the cores
                if (!strncmp(p, "CHK", 3)) {
                    coresToChk = atoi(strtok(NULL, ","));
#ifdef VERBOSE_OUTPUT
                    ALOGI("chk: %d", coresToChk);
#endif
                    checkCores(coresToChk);
                } else
                    // check if
                    if (!strncmp(p, "SLP", 3)) {
                        sleepTime = atoi(strtok(NULL, ","));
#ifdef VERBOSE_OUTPUT
                        ALOGI("slp(ms): %d", sleepTime);
#endif
                        usleep(sleepTime * 1000);
                    } else {
                        ALOGE("Unknown test pattern: %s", p);
                    }
            p = strtok(NULL, ",");
        }
    }

    ALOGI("********** libPerfService Test End **********");
    return 0;
}
