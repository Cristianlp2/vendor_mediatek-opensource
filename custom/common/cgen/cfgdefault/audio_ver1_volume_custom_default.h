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

#ifndef AUDIO_VER1_VOLUME_CUSTOM_DEFAULT_H
#define AUDIO_VER1_VOLUME_CUSTOM_DEFAULT_H

#define VER1_AUD_VOLUME_RING                                                               \
    {32, 48, 64, 80, 96, 112, 128, 144, 160, 176, 192, 208, 224, 240, 255},                \
            {32, 48, 64, 80, 96, 112, 128, 144, 160, 176, 192, 208, 224, 240, 255},        \
            {128, 136, 144, 152, 160, 168, 176, 184, 192, 200, 212, 224, 236, 248, 255}, { \
        128, 136, 144, 152, 160, 168, 176, 184, 192, 200, 212, 224, 236, 248, 255          \
    }

#define VER1_AUD_VOLUME_SIP                                                \
    {112, 136, 160, 184, 208, 232, 255, 0, 0, 0, 0, 0, 0, 0, 0},           \
            {112, 136, 160, 184, 208, 232, 255, 0, 0, 0, 0, 0, 0, 0, 0},   \
            {112, 136, 160, 184, 208, 232, 255, 0, 0, 0, 0, 0, 0, 0, 0}, { \
        0, 43, 85, 128, 171, 213, 255, 0, 0, 0, 0, 0, 0, 0, 0              \
    }

#define VER1_AUD_VOLUME_MIC                                                      \
    {64, 112, 192, 144, 192, 192, 184, 184, 184, 184, 184, 0, 0, 0, 0},          \
            {255, 192, 192, 180, 192, 192, 196, 184, 184, 184, 184, 0, 0, 0, 0}, \
            {255, 208, 208, 180, 255, 208, 196, 0, 0, 0, 0, 0, 0, 0, 0}, {       \
        255, 208, 208, 164, 255, 208, 172, 0, 0, 0, 0, 0, 0, 0, 0                \
    }

#define VER1_AUD_VOLUME_FM                                                              \
    {32, 48, 64, 80, 96, 112, 128, 144, 160, 176, 192, 208, 224, 255, 255},             \
            {88, 100, 112, 124, 136, 148, 160, 172, 184, 196, 208, 220, 232, 244, 255}, \
            {68, 80, 92, 104, 116, 128, 140, 152, 168, 176, 188, 200, 212, 232, 248}, { \
        32, 48, 64, 80, 96, 112, 128, 144, 160, 176, 192, 208, 224, 255, 255            \
    }

#define VER1_AUD_VOLUME_SPH                                           \
    {40, 52, 64, 76, 88, 100, 112, 0, 0, 0, 0, 0, 0, 0, 0},           \
            {40, 52, 64, 76, 88, 100, 112, 0, 0, 0, 0, 0, 0, 0, 0},   \
            {48, 60, 72, 84, 96, 108, 120, 0, 0, 0, 0, 0, 0, 0, 0}, { \
        40, 52, 64, 76, 88, 100, 112, 0, 0, 0, 0, 0, 0, 0, 0          \
    }

#define VER1_AUD_VOLUME_SID                                  \
    {0, 0, 16, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},          \
            {0, 0, 32, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},  \
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, { \
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0          \
    }

#define VER1_AUD_VOLUME_MEDIA                                                           \
    {32, 48, 64, 80, 96, 112, 160, 144, 160, 176, 192, 208, 224, 240, 255},             \
            {88, 100, 112, 124, 136, 148, 160, 172, 184, 196, 208, 220, 232, 244, 255}, \
            {68, 80, 92, 104, 116, 128, 140, 152, 168, 176, 188, 200, 212, 232, 248}, { \
        32, 48, 64, 80, 96, 112, 128, 144, 160, 176, 192, 208, 224, 240, 255            \
    }

#define VER1_AUD_VOLUME_MATV                                                            \
    {32, 48, 64, 80, 96, 112, 128, 144, 160, 176, 192, 208, 224, 240, 255},             \
            {88, 100, 112, 124, 136, 148, 160, 172, 184, 196, 208, 220, 232, 244, 255}, \
            {68, 80, 92, 104, 116, 128, 140, 152, 168, 176, 188, 200, 212, 232, 248}, { \
        32, 48, 64, 80, 96, 112, 128, 144, 160, 176, 192, 208, 224, 240, 255            \
    }

#define VER1_AUD_NORMAL_VOLUME_DEFAULT 128, 128, 128, 128, 128, 128

#define VER1_AUD_HEADSER_VOLUME_DEFAULT 124, 148, 148, 148, 148, 148

#define VER1_AUD_SPEAKER_VOLUME_DEFAULT 160, 120, 120, 120, 120, 120

#define VER1_AUD_HEADSETSPEAKER_VOLUME_DEFAULT 112, 160, 132, 132, 132, 132, 132, 132

#define VER1_AUD_EXTAMP_VOLUME_DEFAULT 132, 132, 132, 132, 132, 132

#define VER1_AUD_VOLUME_LEVEL_DEFAULT 15, 7, 15, 15, 7, 7, 7, 15, 15

/* mic volume setting for 2G/3G HAC mode */
#define DEFAULT_VER1_AUD_VOLUME_MIC_HAC \
    64, 112, 192, 144, 192, 192, 184, 184, 184, 184, 184, 0, 0, 0, 0

/* speech dl volume setting for 2G/3G HAC mode */
#define DEFAULT_VER1_AUD_VOLUME_SPH_HAC 40, 52, 64, 76, 88, 100, 112, 0, 0, 0, 0, 0, 0, 0, 0

/* sidetone volume setting for 2G/3G HAC mode */
#define DEFAULT_VER1_AUD_VOLUME_SID_HAC 0, 0, 16, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0

#endif
