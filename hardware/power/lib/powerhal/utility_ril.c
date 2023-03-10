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

#include "utility_ril.h"
#include <assert.h>
#include <cutils/sockets.h>
#include <unistd.h>
#include <utils/Log.h>
#include <netinet/in.h>
#include "perfservice_types.h"

#undef LOG_TAG
#define LOG_TAG "RilUtility"
#define SOCKET_NAME "rild-oem"

static int certPid = -1;

/*
 * Connect to socket
 *
 * int socket = socketConnect();
 * if (socket < 0) {
 *       sleep(5);
 *       socket = socketConnect();
 * }
 *
 */
int socketConnect() {
    int sock = socket_local_client(SOCKET_NAME, ANDROID_SOCKET_NAMESPACE_RESERVED, SOCK_STREAM);
    if (sock < 0) return -1;

    return sock;
}

/*
 * Disconnect form socket
 */
int socketDisconnect(int sock) {
    int ret;

    assert(sock > 0);
    ret = close(sock);

    return ret;
}

/*
 * Send data to socket
 * argCount indicates how many line to send
 */
int sendData(int socket, int argCount, char** data) {
    assert(socket >= 0);
    int ret = -1, i, msgLen = -1;

    // send number of argument
    ret = send(socket, (const void*)&argCount, sizeof(int), 0);
    if (sizeof(int) == ret) {
        // success, send length parameter
        for (i = 0; i < argCount; i++) {
            // send length of parameter
            msgLen = strlen(data[i]);
            ret = send(socket, &msgLen, sizeof(int), 0);

            if (sizeof(int) == ret) {
                // send parameter
                ret = send(socket, data[i], msgLen, 0);
                return ret;
            }
        }
    }
    return -1;
}

/*
 * Notify game event to rild
 * gameMode represents the state in game
 * lowLatencyMode represents whether low latency mode or not
 */
int notify_rild_game_event(int gameMode, int lowLatencyMode) {
    int ret = -1;

    // connect
    int socket = socketConnect();
    if (socket < 0) {
        return -1;
    }

    // send data
    char** data = (char**)calloc(1, 1 * sizeof(char*));
    if (data == NULL) {
        ret = socketDisconnect(socket);
        return -1;
    }
    asprintf(&data[0], "GAME_MODE, %d, %d", gameMode, lowLatencyMode);
    ret = sendData(socket, 1, data);
    free(data[0]);
    free(data);

    // disconnect
    ret = socketDisconnect(socket);
    ALOGE("notify_rild_game_event %d %d %d\n", socket, gameMode, lowLatencyMode);

    return 0;
}

/*
 * Update phantom packet to rild
 * return
 *     0: fail
 *     count: number of byte sent
 */
int update_packet(const char* packet) {
    int ret = 0;

    // connect
    int socket = socketConnect();
    if (socket < 0) {
        return 0;
    }

    // send data
    char** data = (char**)calloc(1, 1 * sizeof(char*));
    if (data == NULL) {
        ret = socketDisconnect(socket);
        return 0;
    }
    asprintf(&data[0], "MNGMT_PACKET, %s", packet);
    ret = sendData(socket, 1, data);
    free(data[0]);
    free(data);

    // disconnect
    socketDisconnect(socket);
    ALOGD("update_packet %d %s\n", socket, packet);

    return ret;
}

/*
 * Notify optimization information to rild
 * lowLatencyMode represents whether low latency mode or not
 * period represents the period in low latency mode
 */
int notify_rild_opt_info(int lowLatencyMode, int period) {
    int ret = -1;

    // connect
    int socket = socketConnect();
    if (socket < 0) {
        ALOGE("notify_rild_opt_info socket error\n");
        return -1;
    }

    // send data
    char** data = (char**)calloc(1, 1 * sizeof(char*));
    if (data == NULL) {
        ret = socketDisconnect(socket);
        return -1;
    }
    asprintf(&data[0], "LOW_LATENCY_MODE, %d, %d", lowLatencyMode, period);
    ret = sendData(socket, 1, data);
    free(data[0]);
    free(data);

    // disconnect
    ret = socketDisconnect(socket);
    ALOGD("notify_rild_opt_info %d %d %d\n", socket, lowLatencyMode, period);

    return 0;
}

/*
 * Notify optimization information to rild
 * enable represents whether 1st arrow enable or not
 */
int notify_rild_weak_signal_opt(int enable) {
    int ret = -1;

    // connect
    int socket = socketConnect();
    if (socket < 0) {
        return -1;
    }

    // send data
    char** data = (char**)calloc(1, 1 * sizeof(char*));
    if (data == NULL) {
        ret = socketDisconnect(socket);
        return -1;
    }
    asprintf(&data[0], "WEAK_SIGNAL_OPT, %d", enable);
    ret = sendData(socket, 1, data);
    if (ret < 0) {
        ALOGE("notify_rild_weak_signal_opt sendData error %d\n", errno);
    }
    free(data[0]);
    free(data);

    // disconnect
    ret = socketDisconnect(socket);
    ALOGD("notify_rild_weak_signal_opt %d %d\n", socket, enable);

    return 0;
}

/*
 * Notify app status to rild
 * pid represents process id
 * status represents the status of the process
 */
int notify_rild_app_status(int pid, int status) {
    int ret = -1;

    // connect
    int socket = socketConnect();
    if (socket < 0) {
        ALOGE("notify_rild_app_status socket error\n");
        return -1;
    }

    // send data
    char** data = (char**)calloc(1, 1 * sizeof(char*));
    if (data == NULL) {
        ret = socketDisconnect(socket);
        return -1;
    }
    asprintf(&data[0], "APP_STATUS, %d, %d", pid, status);
    ret = sendData(socket, 1, data);
    free(data[0]);
    free(data);

    // disconnect
    ret = socketDisconnect(socket);
    ALOGD("notify_rild_app_status %d %d %d\n", socket, pid, status);

    return 0;
}

/*
 * Query capability status
 */
int query_capability(int pid, const char* featureName) {
    int ret = -1;

    // connect
    int socket = socketConnect();
    if (socket < 0) {
        return ret;
    }
    ALOGI("query_capability %d %d %s\n", socket, pid, featureName);

    // send data
    char** data = (char**)malloc(1 * sizeof(char*));
    asprintf(&data[0], "QUERY_CAP, %d, %s", pid, featureName);
    sendData(socket, 1, data);
    free(data[0]);
    free(data);

    // receive response
    int socketRes = -1;
    int recvRes = -1;
    recvRes = recv(socket, &socketRes, sizeof(int), 0);
    if (recvRes < 0) {
        ALOGE("query_capability receive data error %d\n", errno);
        socketDisconnect(socket);
        return ret;
    }
    ret = ntohl(socketRes);
    ALOGI("query_capability result %d\n", ret);

    // disconnect
    socketDisconnect(socket);

    return ret;
}

/*
 * Interface for resource register
 * Reset rild related function
 * power_on_init: 1 if it is powerhal init first time
 */
int reset_rild_opt_info(int power_on_init) {
    if (power_on_init != 1) {
        notify_rild_opt_info(0, 0);
        notify_rild_weak_signal_opt(0);
    }
    return 0;
}

/*
 * Interface for resource register (PERF_RES_NET_MD_LOW_LATENCY)
 * Notify low latency mode
 */
int notify_rild_opt_update(int lowLatencyMode, void* scn) {
    int period = 0;
    tScnNode* ptr = scn;

    if (lowLatencyMode == 1 && ptr != NULL) {
        period = ptr->lock_duration;
    }

    notify_rild_opt_info(lowLatencyMode, period);
    return 0;
}

/*
 * Interface for resource register (PERF_RES_NET_MD_CERT_PID)
 * Set certificate pid
 */
int notify_rild_cert_pid_set(int pid, void* scn) {
    certPid = pid;
    ALOGD("notify_rild_cert_pid_set pid:%d, scn:%p\n", certPid, scn);
    return 0;
}

/*
 * Interface for resource register (PERF_RES_NET_MD_CERT_PID)
 * Reset certificate pid
 */
int notify_rild_cert_pid_reset(int pid, void* scn) {
    certPid = -1;
    ALOGV("notify_rild_cert_pid_reset, %d, %p\n", pid, scn);
    return 0;
}

/*
 * Interface for resource register (PERF_RES_NET_MD_CRASH_PID)
 * Set crash pid
 */
int notify_rild_crash_pid_set(int pid, void* scn) {
    ALOGD("notify_rild_crash_pid_set certPid:%d, crash:%d, scn:%p\n", certPid, pid, scn);
    if (pid == certPid) {
        notify_rild_app_status(pid, STATE_DEAD);
    }
    return 0;
}

/*
 * Interface for resource register (PERF_RES_NET_MD_CRASH_PID)
 * Reset crash pid
 */
int notify_rild_crash_pid_reset(int pid, void* scn) {
    ALOGV("notify_rild_crash_pid_reset, %d, %p\n", pid, scn);
    return 0;
}

/*
 * Interface for resource register (PERF_RES_NET_MD_WEAK_SIG_OPT)
 * Set crash pid
 */
int notify_rild_weak_sig_opt_set(int enable, void* scn) {
    ALOGI("notify_rild_weak_sig_opt_set enable:%d, scn:%p\n", enable, scn);
    notify_rild_weak_signal_opt(enable);
    return 0;
}
