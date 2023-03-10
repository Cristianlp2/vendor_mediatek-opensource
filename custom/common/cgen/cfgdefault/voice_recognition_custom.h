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

#ifndef VOICE_RECOGNITION_CUSTOM_H
#define VOICE_RECOGNITION_CUSTOM_H

/****************************************************
 * Define default voice feature customization parameters
 *****************************************************/

#define DEFAULT_AP_NUM 5
#define DEFAULT_LANGUAGE_NUM 3

// for voice ui - pattern file
#define DEFAULT_LANGUAGE_FOLDER_NAME                                                     \
    "Chinese-Mandarin", "Chinese-Taiwan", "English", "Reserve1", "Reserve2", "Reserve3", \
            "Reserve4", "Reserve5"

#define DEFAULT_COMMAND_NUM_PER_LAN 17, 17, 17, 0, 0, 0, 0, 0

#define DEFAULT_PHONE_SUPPORT_INFO                                                        \
    {1, 2, 0, 0, 0, 0, 0, 0}, {1, 2, 0, 0, 0, 0, 0, 0}, {1, 2, 0, 0, 0, 0, 0, 0},         \
            {0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0}, \
            {0, 0, 0, 0, 0, 0, 0, 0}, {                                                   \
        0, 0, 0, 0, 0, 0, 0, 0                                                            \
    }

#define DEFAULT_CAMERA_SUPPORT_INFO                                                       \
    {3, 4, 0, 0, 0, 0, 0, 0}, {3, 4, 0, 0, 0, 0, 0, 0}, {3, 4, 0, 0, 0, 0, 0, 0},         \
            {0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0}, \
            {0, 0, 0, 0, 0, 0, 0, 0}, {                                                   \
        0, 0, 0, 0, 0, 0, 0, 0                                                            \
    }

#define DEFAULT_ALARM_SUPPORT_INFO                                                        \
    {5, 6, 16, 17, 0, 0, 0, 0}, {5, 6, 16, 17, 0, 0, 0, 0}, {5, 6, 16, 17, 0, 0, 0, 0},   \
            {0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0}, \
            {0, 0, 0, 0, 0, 0, 0, 0}, {                                                   \
        0, 0, 0, 0, 0, 0, 0, 0                                                            \
    }

#define DEFAULT_MUSIC_SUPPORT_INFO                                                            \
    {7, 8, 9, 10, 11, 12, 13, 0}, {7, 8, 9, 10, 11, 12, 13, 0}, {7, 8, 9, 10, 11, 12, 13, 0}, \
            {0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0},     \
            {0, 0, 0, 0, 0, 0, 0, 0}, {                                                       \
        0, 0, 0, 0, 0, 0, 0, 0                                                                \
    }

#define DEFAULT_EBOOK_SUPPORT_INFO                                                        \
    {14, 15, 0, 0, 0, 0, 0, 0}, {14, 15, 0, 0, 0, 0, 0, 0}, {14, 15, 0, 0, 0, 0, 0, 0},   \
            {0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0}, \
            {0, 0, 0, 0, 0, 0, 0, 0}, {                                                   \
        0, 0, 0, 0, 0, 0, 0, 0                                                            \
    }

#define DEFAULT_RESERVE_SUPPORT_INFO                                                      \
    {0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0},         \
            {0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0}, \
            {0, 0, 0, 0, 0, 0, 0, 0}, {                                                   \
        0, 0, 0, 0, 0, 0, 0, 0                                                            \
    }

#define DEFAULT_AP_SUPPORT_INFO                                                                \
    {DEFAULT_PHONE_SUPPORT_INFO}, {DEFAULT_CAMERA_SUPPORT_INFO}, {DEFAULT_ALARM_SUPPORT_INFO}, \
            {DEFAULT_MUSIC_SUPPORT_INFO}, {DEFAULT_EBOOK_SUPPORT_INFO},                        \
            {DEFAULT_RESERVE_SUPPORT_INFO}, {DEFAULT_RESERVE_SUPPORT_INFO},                    \
            {DEFAULT_RESERVE_SUPPORT_INFO}, {DEFAULT_RESERVE_SUPPORT_INFO},                    \
            {DEFAULT_RESERVE_SUPPORT_INFO}, {DEFAULT_RESERVE_SUPPORT_INFO},                    \
            {DEFAULT_RESERVE_SUPPORT_INFO}, {DEFAULT_RESERVE_SUPPORT_INFO},                    \
            {DEFAULT_RESERVE_SUPPORT_INFO}, {DEFAULT_RESERVE_SUPPORT_INFO}, {                  \
        DEFAULT_RESERVE_SUPPORT_INFO                                                           \
    }

// for CTO
#define DEFAULT_ALGORITHM_PARAM                                                                   \
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,                                              \
     0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},                                             \
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,                                      \
             0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},                                     \
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,                                      \
             0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},                                     \
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,                                      \
             0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},                                     \
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,                                      \
             0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},                                     \
            {10, 7, 6, 8, 15, 2, 3, 2, 3, 3, 0, 0, 0, 0, 0, 0,                                    \
             0,  0, 0, 0, 0,  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},                                   \
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,                                      \
             0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},                                     \
    {                                                                                             \
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, \
                0, 0                                                                              \
    }

#endif
