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

#ifndef AUDIO_EFFECT_DEFAULT_H
#define AUDIO_EFFECT_DEFAULT_H

#define BSRD_LEVEL 50
#define BSRD_DISTANCE1 20
#define BSRD_DISTANCE2 30
#define BSRD_BAND_SELECT 0

#define BASS_CUTOFF_FREQ 400
#define BASS_ISVB 0

#define NORMAL_GAIN_LEVEL 0, 0, 0, 0, 0, 0, 0, 0
#define DANCE_GAIN_LEVEL 16, 64, 0, 8, 32, 40, 32, 16
#define BASS_GAIN_LEVEL 48, 32, 24, 16, 0, 0, 0, 0
#define CLASSICAL_GAIN_LEVEL 40, 24, 0, -16, -8, 0, 24, 32
#define TREBLE_GAIN_LEVEL 0, 0, 0, 0, 8, 24, 40, 48
#define PARTY_GAIN_LEVEL 40, 32, 0, 0, 0, 0, 0, 32
#define POP_GAIN_LEVEL -12, 0, 8, 40, 40, 8, -8, -16
#define ROCK_GAIN_LEVEL 48, 16, 8, -8, -16, 8, 24, 40

#define LOUDENHANCEMODE 3

#define TIME_TD_TF 0
#define TIME_TS_RATIO 100

#endif
