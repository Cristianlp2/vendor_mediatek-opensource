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

#ifndef _CFG_AUDIO_H
#define _CFG_AUDIO_H
/* include rule :
   1st : find path/files relative current position (Common)
   2nd : find path/files from other projects
*/
#include "CFG_AUDIO_File.h"

// audio related default value
#include "cfgdefault/sph_coeff_record_mode_default.h"
#include "cfgdefault/sph_coeff_dmnr_default.h"
#include "cfgdefault/sph_coeff_dmnr_handsfree_default.h"
#include "cfgdefault/audio_hd_record_custom.h"
#include "cfgdefault/audio_acf_default.h"
#include "cfgdefault/audio_hcf_default.h"
#include "cfgdefault/audio_effect_default.h"
#include "cfgdefault/audio_gain_table_default.h"
#include "cfgdefault/audio_ver1_volume_custom_default.h"
#include "cfgdefault/voice_recognition_custom.h"
#include "cfgdefault/audio_audenh_control_option.h"
#include "cfgdefault/audio_voip_custom.h"
#include "cfgdefault/audio_hfp_custom.h"
//#include "cfgdefault/audio_acfsub_default.h"
#include "cfgdefault/audio_music_drc_default.h"
#include "cfgdefault/audio_ringtone_drc_default.h"
#include "cfgdefault/sph_coeff_anc_default.h"
#include "cfgdefault/audio_speaker_monitor_custom.h"
#include "cfgdefault/sph_coeff_lpbk_default.h"
#include "cfgdefault/audio_function_switch_default.h"

// speech related default value
#include "cfgdefault/sph_coeff_default.h"
#include "cfgdefault/audio_custom.h"
#include "cfgdefault/med_audio_default.h"
#include "cfgdefault/audio_volume_custom_default.h"
#include "cfgdefault/audio_ver1_volume_custom_default.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifdef __ALLOCATE_CFG_AUDIO_DEFAULT_H
// Allocate data by \vendor\mediatek\proprietary\external\nvram\libcustom_nvram\CFG_file_info.c

const AUDIO_CUSTOM_PARAM_STRUCT speech_custom_default = {
        /* INT8 volume[MAX_VOL_CATE][MAX_VOL_TYPE] */
        /* Normal volume: TON, SPK, MIC, FMR, SPH, SID, MED */
        {{GAIN_NOR_TON_VOL, GAIN_NOR_KEY_VOL, GAIN_NOR_MIC_VOL, GAIN_NOR_FMR_VOL, GAIN_NOR_SPH_VOL,
          GAIN_NOR_SID_VOL, GAIN_NOR_MED_VOL},
         /* Headset volume: TON, SPK, MIC, FMR, SPH, SID, MED */
         {GAIN_HED_TON_VOL, GAIN_HED_KEY_VOL, GAIN_HED_MIC_VOL, GAIN_HED_FMR_VOL, GAIN_HED_SPH_VOL,
          GAIN_HED_SID_VOL, GAIN_HED_MED_VOL},
         /* Handfree volume: TON, SPK, MIC, FMR, SPH, SID, MED */
         {GAIN_HND_TON_VOL, GAIN_HND_KEY_VOL, GAIN_HND_MIC_VOL, GAIN_HND_FMR_VOL, GAIN_HND_SPH_VOL,
          GAIN_HND_SID_VOL, GAIN_HND_MED_VOL}},
        /* UINT16 speech_common_para[12] */
        {DEFAULT_SPEECH_COMMON_PARA},
        /* UINT16 speech_mode_para[8][16] */
        {{DEFAULT_SPEECH_NORMAL_MODE_PARA},
         {DEFAULT_SPEECH_EARPHONE_MODE_PARA},
         {DEFAULT_SPEECH_LOUDSPK_MODE_PARA},
         {DEFAULT_SPEECH_BT_EARPHONE_MODE_PARA},
         {DEFAULT_SPEECH_BT_CORDLESS_MODE_PARA},
         {DEFAULT_SPEECH_CARKIT_MODE_PARA},
         {DEFAULT_SPEECH_AUX1_MODE_PARA},
         {DEFAULT_SPEECH_AUX2_MODE_PARA}},
        /* UINT16 speech_volume_para[4] */
        {DEFAULT_SPEECH_VOL_PARA},
        /* UINT16 debug_info[16] */
        {DEFAULT_AUDIO_DEBUG_INFO},
        /* INT16 sph_in_fir[6][45], sph_out_fir */
        {SPEECH_INPUT_FIR_COEFF},
        {SPEECH_OUTPUT_FIR_COEFF},
        /* UINT16 DG_DL_Speech */
        DG_DL_Speech,
        /* UINT16 DG_Microphone */
        DG_Microphone,
        /* UINT16 FM record volume*/
        FM_Record_Vol,
        /* UINT16 BT sync type and length*/
        DEFAULT_BLUETOOTH_SYNC_TYPE,
        DEFAULT_BLUETOOTH_SYNC_LENGTH,
        /* UINT16 BT PCM in/out digital gain*/
        DEFAULT_BT_PCM_IN_VOL,
        DEFAULT_BT_PCM_OUT_VOL,
        /* user mode : normal mode, earphone mode, loud speaker mode */
        /* UCHAR  user_mode             */
        VOL_NORMAL,
        /* auto VM record setting */
        DEFAULT_VM_SUPPORT,
        DEFAULT_AUTO_VM,
        /* Micbais voltage 1900 --> 2200 */
        MICBAIS,
};

const AUDIO_CUSTOM_WB_PARAM_STRUCT wb_speech_custom_default = {
        /* unsigned short speech_mode_wb_para[8][16] */
        {{DEFAULT_WB_SPEECH_NORMAL_MODE_PARA},
         {DEFAULT_WB_SPEECH_EARPHONE_MODE_PARA},
         {DEFAULT_WB_SPEECH_LOUDSPK_MODE_PARA},
         {DEFAULT_WB_SPEECH_BT_EARPHONE_MODE_PARA},
         {DEFAULT_WB_SPEECH_BT_CORDLESS_MODE_PARA},
         {DEFAULT_WB_SPEECH_CARKIT_MODE_PARA},
         {DEFAULT_WB_SPEECH_AUX1_MODE_PARA},
         {DEFAULT_WB_SPEECH_AUX2_MODE_PARA}},
        /* short sph_wb_in_fir[6][90] */
        {WB_Speech_Input_FIR_Coeff},
        /* short sph_wb_out_fir[6][90] */
        {WB_Speech_Output_FIR_Coeff},
};

/*
const unsigned int bes_loudness_Sep_LR_Filter;
    unsigned int bes_loudness_WS_Gain_Max;
    unsigned int bes_loudness_WS_Gain_Min;
    unsigned int bes_loudness_Filter_First;
    unsigned int bes_loudness_Num_Bands;
    unsigned int bes_loudness_Flt_Bank_Order;
    unsigned int bes_loudness_Cross_Freq[7];
    int DRC_Th[8][5];
    int DRC_Gn[8][5];
    int SB_Gn[8];
    unsigned int SB_Mode[8];
    unsigned int DRC_Delay;
    unsigned int Att_Time[8][6];
    unsigned int Rel_Time[8][6];
    int Hyst_Th[8][6];
    int Lim_Th;
    int Lim_Gn;
    unsigned int Lim_Const;
    unsigned int Lim_Delay;
    int SWIPRev;

*/
const AUDIO_ACF_CUSTOM_PARAM_STRUCT audio_custom_default = {
        {{BES_LOUDNESS_ACF_L_HPF_FC,
          BES_LOUDNESS_ACF_L_HPF_ORDER,
          BES_LOUDNESS_ACF_L_LPF_FC,
          BES_LOUDNESS_ACF_L_LPF_ORDER,
          {BES_LOUDNESS_ACF_L_BPF_FC},
          {BES_LOUDNESS_ACF_L_BPF_BW},
          {BES_LOUDNESS_ACF_L_BPF_GAIN},

          BES_LOUDNESS_ACF_R_HPF_FC,
          BES_LOUDNESS_ACF_R_HPF_ORDER,
          BES_LOUDNESS_ACF_R_LPF_FC,
          BES_LOUDNESS_ACF_R_LPF_ORDER,
          {BES_LOUDNESS_ACF_R_BPF_FC},
          {BES_LOUDNESS_ACF_R_BPF_BW},
          {BES_LOUDNESS_ACF_R_BPF_GAIN}}},

        BES_LOUDNESS_ACF_SEP_LR_FILTER,
        BES_LOUDNESS_ACF_WS_GAIN_MAX,
        BES_LOUDNESS_ACF_WS_GAIN_MIN,
        BES_LOUDNESS_ACF_FILTER_FIRST,
        BES_LOUDNESS_ACF_NUM_BANDS,
        BES_LOUDNESS_ACF_FLT_BANK_ORDER,
        {BES_LOUDNESS_ACF_CROSSOVER_FREQ},
        {BES_LOUDNESS_ACF_GAIN_MAP_IN},
        {BES_LOUDNESS_ACF_GAIN_MAP_OUT},
        {BES_LOUDNESS_ACF_SB_GAIN},
        {BES_LOUDNESS_ACF_SB_MODE},
        BES_LOUDNESS_ACF_DRC_DELAY,
        {BES_LOUDNESS_ACF_ATT_TIME},
        {BES_LOUDNESS_ACF_REL_TIME},
        {BES_LOUDNESS_ACF_HYST_TH},
        BES_LOUDNESS_ACF_LIM_TH,
        BES_LOUDNESS_ACF_LIM_GN,
        BES_LOUDNESS_ACF_LIM_CONST,
        BES_LOUDNESS_ACF_LIM_DELAY,
        0x0520,
};

const AUDIO_ACF_CUSTOM_PARAM_STRUCT audio_hcf_custom_default = {
        {{BES_LOUDNESS_HCF_L_HPF_FC,
          BES_LOUDNESS_HCF_L_HPF_ORDER,
          BES_LOUDNESS_HCF_L_LPF_FC,
          BES_LOUDNESS_HCF_L_LPF_ORDER,
          {BES_LOUDNESS_HCF_L_BPF_FC},
          {BES_LOUDNESS_HCF_L_BPF_BW},
          {BES_LOUDNESS_HCF_L_BPF_GAIN},

          BES_LOUDNESS_HCF_R_HPF_FC,
          BES_LOUDNESS_HCF_R_HPF_ORDER,
          BES_LOUDNESS_HCF_R_LPF_FC,
          BES_LOUDNESS_HCF_R_LPF_ORDER,
          {BES_LOUDNESS_HCF_R_BPF_FC},
          {BES_LOUDNESS_HCF_R_BPF_BW},
          {BES_LOUDNESS_HCF_R_BPF_GAIN}}},

        BES_LOUDNESS_HCF_SEP_LR_FILTER,
        BES_LOUDNESS_HCF_WS_GAIN_MAX,
        BES_LOUDNESS_HCF_WS_GAIN_MIN,
        BES_LOUDNESS_HCF_FILTER_FIRST,
        BES_LOUDNESS_HCF_NUM_BANDS,
        BES_LOUDNESS_HCF_FLT_BANK_ORDER,
        {BES_LOUDNESS_HCF_CROSSOVER_FREQ},
        {BES_LOUDNESS_HCF_GAIN_MAP_IN},
        {BES_LOUDNESS_HCF_GAIN_MAP_OUT},
        {BES_LOUDNESS_HCF_SB_GAIN},
        {BES_LOUDNESS_HCF_SB_MODE},
        BES_LOUDNESS_HCF_DRC_DELAY,
        {BES_LOUDNESS_HCF_ATT_TIME},
        {BES_LOUDNESS_HCF_REL_TIME},
        {BES_LOUDNESS_HCF_HYST_TH},
        BES_LOUDNESS_HCF_LIM_TH,
        BES_LOUDNESS_HCF_LIM_GN,
        BES_LOUDNESS_HCF_LIM_CONST,
        BES_LOUDNESS_HCF_LIM_DELAY,
        0x0520,
};

const AUDIO_ACF_CUSTOM_PARAM_STRUCT audio_vibspk_custom_default = {
        {{BES_LOUDNESS_ACF_L_HPF_FC,
          BES_LOUDNESS_ACF_L_HPF_ORDER,
          BES_LOUDNESS_ACF_L_LPF_FC,
          BES_LOUDNESS_ACF_L_LPF_ORDER,
          {BES_LOUDNESS_ACF_L_BPF_FC},
          {BES_LOUDNESS_ACF_L_BPF_BW},
          {BES_LOUDNESS_ACF_L_BPF_GAIN},

          BES_LOUDNESS_ACF_R_HPF_FC,
          BES_LOUDNESS_ACF_R_HPF_ORDER,
          BES_LOUDNESS_ACF_R_LPF_FC,
          BES_LOUDNESS_ACF_R_LPF_ORDER,
          {BES_LOUDNESS_ACF_R_BPF_FC},
          {BES_LOUDNESS_ACF_R_BPF_BW},
          {BES_LOUDNESS_ACF_R_BPF_GAIN}}},

        0,
        BES_LOUDNESS_ACF_WS_GAIN_MAX,
        BES_LOUDNESS_ACF_WS_GAIN_MIN,
        BES_LOUDNESS_ACF_FILTER_FIRST,
        BES_LOUDNESS_ACF_NUM_BANDS,
        BES_LOUDNESS_ACF_FLT_BANK_ORDER,
        {BES_LOUDNESS_ACF_CROSSOVER_FREQ},
        {BES_LOUDNESS_ACF_GAIN_MAP_IN},
        {BES_LOUDNESS_ACF_GAIN_MAP_OUT},
        {BES_LOUDNESS_ACF_SB_GAIN},
        {BES_LOUDNESS_ACF_SB_MODE},
        BES_LOUDNESS_ACF_DRC_DELAY,
        {BES_LOUDNESS_ACF_ATT_TIME},
        {BES_LOUDNESS_ACF_REL_TIME},
        {BES_LOUDNESS_ACF_HYST_TH},
        BES_LOUDNESS_ACF_LIM_TH,
        BES_LOUDNESS_ACF_LIM_GN,
        BES_LOUDNESS_ACF_LIM_CONST,
        BES_LOUDNESS_ACF_LIM_DELAY,
        0x0520,
};

const AUDIO_ACF_CUSTOM_PARAM_STRUCT audio_musicdrc_custom_default = {
        {{BES_LOUDNESS_MUSICDRC_L_HPF_FC,
          BES_LOUDNESS_MUSICDRC_L_HPF_ORDER,
          BES_LOUDNESS_MUSICDRC_L_LPF_FC,
          BES_LOUDNESS_MUSICDRC_L_LPF_ORDER,
          {BES_LOUDNESS_MUSICDRC_L_BPF_FC},
          {BES_LOUDNESS_MUSICDRC_L_BPF_BW},
          {BES_LOUDNESS_MUSICDRC_L_BPF_GAIN},

          BES_LOUDNESS_MUSICDRC_R_HPF_FC,
          BES_LOUDNESS_MUSICDRC_R_HPF_ORDER,
          BES_LOUDNESS_MUSICDRC_R_LPF_FC,
          BES_LOUDNESS_MUSICDRC_R_LPF_ORDER,
          {BES_LOUDNESS_MUSICDRC_R_BPF_FC},
          {BES_LOUDNESS_MUSICDRC_R_BPF_BW},
          {BES_LOUDNESS_MUSICDRC_R_BPF_GAIN}}},

        BES_LOUDNESS_MUSICDRC_SEP_LR_FILTER,
        BES_LOUDNESS_MUSICDRC_WS_GAIN_MAX,
        BES_LOUDNESS_MUSICDRC_WS_GAIN_MIN,
        BES_LOUDNESS_MUSICDRC_FILTER_FIRST,
        BES_LOUDNESS_MUSICDRC_NUM_BANDS,
        BES_LOUDNESS_MUSICDRC_FLT_BANK_ORDER,
        {BES_LOUDNESS_MUSICDRC_CROSSOVER_FREQ},
        {BES_LOUDNESS_MUSICDRC_GAIN_MAP_IN},
        {BES_LOUDNESS_MUSICDRC_GAIN_MAP_OUT},
        {BES_LOUDNESS_MUSICDRC_SB_GAIN},
        {BES_LOUDNESS_MUSICDRC_SB_MODE},
        BES_LOUDNESS_MUSICDRC_DRC_DELAY,
        {BES_LOUDNESS_MUSICDRC_ATT_TIME},
        {BES_LOUDNESS_MUSICDRC_REL_TIME},
        {BES_LOUDNESS_MUSICDRC_HYST_TH},
        BES_LOUDNESS_MUSICDRC_LIM_TH,
        BES_LOUDNESS_MUSICDRC_LIM_GN,
        BES_LOUDNESS_MUSICDRC_LIM_CONST,
        BES_LOUDNESS_MUSICDRC_LIM_DELAY,
        0x0520,
};

const AUDIO_ACF_CUSTOM_PARAM_STRUCT audio_ringtonedrc_custom_default = {
        {{BES_LOUDNESS_RINGTONEDRC_L_HPF_FC,
          BES_LOUDNESS_RINGTONEDRC_L_HPF_ORDER,
          BES_LOUDNESS_RINGTONEDRC_L_LPF_FC,
          BES_LOUDNESS_RINGTONEDRC_L_LPF_ORDER,
          {BES_LOUDNESS_RINGTONEDRC_L_BPF_FC},
          {BES_LOUDNESS_RINGTONEDRC_L_BPF_BW},
          {BES_LOUDNESS_RINGTONEDRC_L_BPF_GAIN},

          BES_LOUDNESS_RINGTONEDRC_R_HPF_FC,
          BES_LOUDNESS_RINGTONEDRC_R_HPF_ORDER,
          BES_LOUDNESS_RINGTONEDRC_R_LPF_FC,
          BES_LOUDNESS_RINGTONEDRC_R_LPF_ORDER,
          {BES_LOUDNESS_RINGTONEDRC_R_BPF_FC},
          {BES_LOUDNESS_RINGTONEDRC_R_BPF_BW},
          {BES_LOUDNESS_RINGTONEDRC_R_BPF_GAIN}}},

        BES_LOUDNESS_RINGTONEDRC_SEP_LR_FILTER,
        BES_LOUDNESS_RINGTONEDRC_WS_GAIN_MAX,
        BES_LOUDNESS_RINGTONEDRC_WS_GAIN_MIN,
        BES_LOUDNESS_RINGTONEDRC_FILTER_FIRST,
        BES_LOUDNESS_RINGTONEDRC_NUM_BANDS,
        BES_LOUDNESS_RINGTONEDRC_FLT_BANK_ORDER,
        {BES_LOUDNESS_RINGTONEDRC_CROSSOVER_FREQ},
        {BES_LOUDNESS_RINGTONEDRC_GAIN_MAP_IN},
        {BES_LOUDNESS_RINGTONEDRC_GAIN_MAP_OUT},
        {BES_LOUDNESS_RINGTONEDRC_SB_GAIN},
        {BES_LOUDNESS_RINGTONEDRC_SB_MODE},
        BES_LOUDNESS_RINGTONEDRC_DRC_DELAY,
        {BES_LOUDNESS_RINGTONEDRC_ATT_TIME},
        {BES_LOUDNESS_RINGTONEDRC_REL_TIME},
        {BES_LOUDNESS_RINGTONEDRC_HYST_TH},
        BES_LOUDNESS_RINGTONEDRC_LIM_TH,
        BES_LOUDNESS_RINGTONEDRC_LIM_GN,
        BES_LOUDNESS_RINGTONEDRC_LIM_CONST,
        BES_LOUDNESS_RINGTONEDRC_LIM_DELAY,
        0x0520,
};

const AUDIO_EFFECT_CUSTOM_PARAM_STRUCT audio_effect_custom_default = {
        // DSRD parameters
        BSRD_LEVEL,
        BSRD_DISTANCE1,
        BSRD_DISTANCE2,
        BSRD_BAND_SELECT,

        // BASS
        BASS_CUTOFF_FREQ,
        BASS_ISVB,

        // EQ effect
        {NORMAL_GAIN_LEVEL},
        {DANCE_GAIN_LEVEL},
        {BASS_GAIN_LEVEL},
        {CLASSICAL_GAIN_LEVEL},
        {TREBLE_GAIN_LEVEL},
        {PARTY_GAIN_LEVEL},
        {POP_GAIN_LEVEL},
        {ROCK_GAIN_LEVEL},

        // loudness mode
        LOUDENHANCEMODE,

        // TS
        TIME_TD_TF,
        TIME_TS_RATIO};

const AUDIO_PARAM_MED_STRUCT audio_param_med_default = {{SPEECH_INPUT_MED_FIR_COEFF},
                                                        {SPEECH_OUTPUT_MED_FIR_COEFF},
                                                        {FIR_output_index},
                                                        {FIR_input_index},
                                                        {{MED_SPEECH_NORMAL_MODE_PARA},
                                                         {MED_SPEECH_EARPHONE_MODE_PARA},
                                                         {MED_SPEECH_BT_EARPHONE_MODE_PARA},
                                                         {MED_SPEECH_LOUDSPK_MODE_PARA},
                                                         {MED_SPEECH_CARKIT_MODE_PARA},
                                                         {MED_SPEECH_BT_CORDLESS_MODE_PARA},
                                                         {MED_SPEECH_AUX1_MODE_PARA},
                                                         {MED_SPEECH_AUX2_MODE_PARA}}};

const AUDIO_VER1_CUSTOM_VOLUME_STRUCT audio_ver1_custom_default = {
        {VER1_AUD_VOLUME_RING},
        {VER1_AUD_VOLUME_SIP},
        {VER1_AUD_VOLUME_MIC},
        {VER1_AUD_VOLUME_FM},
        {VER1_AUD_VOLUME_SPH},
        {VER1_AUD_VOLUME_SPH},  // sph2 now use the same
        {VER1_AUD_VOLUME_SID},
        {VER1_AUD_VOLUME_MEDIA},
        {VER1_AUD_VOLUME_MATV},
        {VER1_AUD_NORMAL_VOLUME_DEFAULT},
        {VER1_AUD_HEADSER_VOLUME_DEFAULT},
        {VER1_AUD_SPEAKER_VOLUME_DEFAULT},
        {VER1_AUD_HEADSETSPEAKER_VOLUME_DEFAULT},
        {VER1_AUD_EXTAMP_VOLUME_DEFAULT},
        {VER1_AUD_VOLUME_LEVEL_DEFAULT}};

const AUDIO_VOLUME_CUSTOM_STRUCT audio_volume_custom_default = {
        {AUD_VOLUME_RING}, {AUD_VOLUME_KEY}, {AUD_VOLUME_MIC},   {AUD_VOLUME_FMR},
        {AUD_VOLUME_SPH},  {AUD_VOLUME_SID}, {AUD_VOLUME_MEDIA}, {AUD_VOLUME_MATV}};

const AUDIO_CUSTOM_EXTRA_PARAM_STRUCT dual_mic_custom_default = {
        {DEFAULT_SPEECH_DUAL_MIC_ABF_PARA, DEFAULT_SPEECH_DUAL_MIC_ABFWB_PARA},
        {DEFAULT_SPEECH_DUAL_MIC_ABF_PARA_LoudSPK, DEFAULT_SPEECH_DUAL_MIC_ABFWB_PARA_LoudSPK},
        {DEFAULT_SPEECH_DUAL_MIC_ABFWB_PARA_VR},
        {DEFAULT_SPEECH_DUAL_MIC_ABFWB_PARA_VOIP},
        {DEFAULT_SPEECH_DUAL_MIC_ABFWB_PARA_VOIP_LoudSPK}};

const AUDIO_GAIN_TABLE_STRUCT Gain_control_table_default = {
        {DEFAULT_VOICE_GAIN_TABLE_PARA},
        {DEFAULT_SYSTEM_GAIN_TABLE_PARA},
        {DEFAULT_RINGTONE_GAIN_TABLE_PARA},
        {DEFAULT_MUSIC_GAIN_TABLE_PARA},
        {DEFAULT_ALARM_GAIN_TABLE_PARA},
        {DEFAULT_NOTIFICATION_GAIN_TABLE_PARA},
        {DEFAULT_BLUETOOTH_SCO_GAIN_TABLE_PARA},
        {DEFAULT_ENFORCEAUDIBLE_GAIN_TABLE_PARA},
        {DEFAULT_DTMF_GAIN_TABLE_PARA},
        {DEFAULT_TTS_GAIN_TABLE_PARA},
        {DEFAULT_FM_GAIN_TABLE_PARA},
        {DEFAULT_MATV_GAIN_TABLE_PARA},
        {DEFAULT_SPEECH_NB_GAIN_TABLE_PARA},
        {DEFAULT_SPEECH_WB_GAIN_TABLE_PARA},
        {DEFAULT_SIDETONE_NB_GAIN_TABLE_PARA},
        {DEFAULT_SIDETONE_WB_GAIN_TABLE_PARA},
        {DEFAULT_MICROPHONE_GAIN_TABLE_PARA}};

const AUDIO_BT_GAIN_STRUCT bt_gain_control_default = {{DEFAULT_BLUETOOTH_NREC_GAIN_TABLE_PARA}};

const AUDIO_HD_RECORD_PARAM_STRUCT Hd_Recrod_Par_default = {
        // hd_rec mode num & fir num
        HD_REC_MODE_INDEX_NUM,
        HD_REC_FIR_INDEX_NUM,
        // hd_rec_speech_mode_para
        {DEFAULT_HD_RECORD_SPH_MODE_PAR},
        // hd_rec_fir
        {DEFAULT_HD_RECORD_FIR_Coeff},
        // hd_rec fir mapping - ch1
        {DEFAULT_HD_RECORD_MODE_FIR_MAPPING_CH1},
        // hd_rec fir mapping - ch2
        {DEFAULT_HD_RECORD_MODE_FIR_MAPPING_CH2},
        // hd_rec device mode mapping
        {DEFAULT_HD_RECORD_MODE_DEV_MAPPING},
        // hd_rec_map_to_input_src
        {DEFAULT_HD_RECORD_MODE_INPUT_SRC_MAPPING},
        // hd_rec_map_to_stereo_flag
        {DEFAULT_HD_RECORD_MODE_STEREO_FLAGS}};

const AUDIO_HD_RECORD_SCENE_TABLE_STRUCT Hd_Recrod_Scene_Table_default = {
        DEFAULT_HD_RECORD_NUM_VOICE_RECOGNITION_SCENES,
        DEFAULT_HD_RECORD_NUM_VOICE_SCENES,
        DEFAULT_HD_RECORD_NUM_VIDEO_SCENES,
        DEFAULT_HD_RECORD_NUM_VOICE_UNLOCK_SCENES,
        DEFAULT_HD_RECORD_NUM_CUSTOMIZATION_SCENES,
        {DEFAULT_HD_RECORD_SCENE_TABLE},
        {DEFAULT_HD_RECORD_SCENE_NAME}};

const VOICE_RECOGNITION_PARAM_STRUCT Voice_Recognize_Par_default = {
        // for framework, voice ui related
        DEFAULT_AP_NUM,
        DEFAULT_LANGUAGE_NUM,
        {DEFAULT_LANGUAGE_FOLDER_NAME},
        {DEFAULT_COMMAND_NUM_PER_LAN},
        {DEFAULT_AP_SUPPORT_INFO},
        {DEFAULT_ALGORITHM_PARAM}  // for CTO
};

const AUDIO_AUDENH_CONTROL_OPTION_STRUCT AUDENH_Control_Option_Par_default = {
        DEFAULT_AUDIO_AUDENH_CONTROL_OPTION_Coeff};

const AUDIO_BUFFER_DC_CALIBRATION_STRUCT Audio_Buffer_DC_Calibration_Par_default = {
        0xFFFF, 0, 0, 0, 0, 0, {0}};

const AUDIO_VOIP_PARAM_STRUCT Audio_VOIP_Par_default = {{DEFAULT_VOIP_SPEECH_COMMON_PARAM},
                                                        {DEFAULT_VOIP_SPEECH_MODE_PARAM},
                                                        {DEFAULT_VOIP_IN_FIR_PARAM},
                                                        {DEFAULT_VOIP_OUT_FIR_PARAM}};

const AUDIO_HFP_PARAM_STRUCT audio_hfp_param_custom_default = {{DEFAULT_HFP_SPEECH_COMMON_PARAM},
                                                               {DEFAULT_HFP_SPEECH_MODE_PARAM},
                                                               {DEFAULT_HFP_IN_FIR_PARAM},
                                                               {DEFAULT_HFP_OUT_FIR_PARAM}};

const AUDIO_ANC_CUSTOM_PARAM_STRUCT speech_ANC_custom_default = {{DEFAULT_SPEECH_ANC_PARA},
                                                                 DEFAULT_SPEECH_ANC_APPLY,
                                                                 DEFAULT_SPEECH_ANC_LOG_ENABLE,
                                                                 DEFAULT_SPEECH_ANC_LOG_DOWNSAMPLE,
                                                                 DEFAULT_SPEECH_ANC_DL_PGA};

const AUDIO_CUSTOM_MAGI_CONFERENCE_STRUCT speech_magi_conference_custom_default = {
        {DEFAULT_SPEECH_VOICE_TRACKING_MODE_PARA}, {DEFAULT_WB_SPEECH_VOICE_TRACKING_MODE_PARA}};

const AUDIO_CUSTOM_HAC_PARAM_STRUCT speech_hac_param_custom_default = {
        {DEFAULT_SPEECH_HAC_MODE_PARA},          {DEFAULT_WB_SPEECH_HAC_MODE_PARA},
        {DEFAULT_SPEECH_HAC_INPUT_FIR_COEFF},    {DEFAULT_SPEECH_HAC_OUTPUT_FIR_COEFF},
        {DEFAULT_WB_SPEECH_HAC_INPUT_FIR_COEFF}, {DEFAULT_WB_SPEECH_HAC_OUTPUT_FIR_COEFF},
        {DEFAULT_VER1_AUD_VOLUME_MIC_HAC},       {DEFAULT_VER1_AUD_VOLUME_SPH_HAC},
        {DEFAULT_VER1_AUD_VOLUME_SID_HAC}};

const AUDIO_CUSTOM_SPEECH_LPBK_PARAM_STRUCT speech_lpbk_param_custom_default = {
        {{DEFAULT_SPEECH_LPBK_NORMAL_MODE_PARA},
         {DEFAULT_SPEECH_LPBK_EARPHONE_MODE_PARA},
         {DEFAULT_SPEECH_LPBK_LOUDSPK_MODE_PARA}}};

AUDIO_CUSTOM_AUDIO_FUNC_SWITCH_PARAM_STRUCT audio_func_swtich_param_custom_default = {
        DEFAULT_VMLOG_DUMP_CONFIG, DEFAULT_BGS_DUMP_ENABLE, DEFAULT_CUSTOM_XML_ENABLE};

const AUDIO_SPEAKER_MONITOR_PARAM_STRUCT speaker_monitor_par_default = {
        {DEFAULT_SPEAKER_MONITOR_PARAM},
        DEFAULT_SPEAKER_TEMP_INITIAL,
        /* hardware setting */
        DEFAULT_SPEAKER_CURRENT_SENSE_RESISTOR,
        /* resonant frqquency*/
        DEFAULT_SPEAKER_RESONANT_FC,
        DEFAULT_SPEAKER_RESONANT_BW,
        DEFAULT_SPEAKER_RESONANT_TH,
        /* temperature estimation */
        DEFAULT_SPEAKER_PREFER_HIGH_BAND,
        DEFAULT_SPEAKER_PREFER_LOW_BAND,
        /* temperature estimation control*/
        DEFAULT_SPEAKER_TEMP_CONTROL_LOW,   // low limit
        DEFAULT_SPEAKER_TEMP_CONTROL_HIGH,  // high limit
        DEFAULT_SPEAKER_TEMP_CONTROL_LOG,   // max log time
        /* monitor interval */
        DEFAULT_SPEAKER_MONITOR_INTERVAL  // unit: ms
};

#else
extern AUDIO_CUSTOM_PARAM_STRUCT speech_custom_default;

extern AUDIO_VER1_CUSTOM_VOLUME_STRUCT audio_ver1_custom_default;

extern AUDIO_CUSTOM_WB_PARAM_STRUCT wb_speech_custom_default;

extern AUDIO_ACF_CUSTOM_PARAM_STRUCT audio_custom_default;

extern AUDIO_ACF_CUSTOM_PARAM_STRUCT audio_hcf_custom_default;
extern AUDIO_ACF_CUSTOM_PARAM_STRUCT audio_vibspk_custom_default;
extern AUDIO_ACF_CUSTOM_PARAM_STRUCT audio_musicdrc_custom_default;
extern AUDIO_ACF_CUSTOM_PARAM_STRUCT audio_ringtonedrc_custom_default;

extern AUDIO_EFFECT_CUSTOM_PARAM_STRUCT audio_effect_custom_default;

extern AUDIO_PARAM_MED_STRUCT audio_param_med_default;

extern AUDIO_VOLUME_CUSTOM_STRUCT audio_volume_custom_default;

extern AUDIO_CUSTOM_EXTRA_PARAM_STRUCT dual_mic_custom_default;

extern AUDIO_GAIN_TABLE_STRUCT Gain_control_table_default;

extern AUDIO_HD_RECORD_PARAM_STRUCT Hd_Recrod_Par_default;

extern AUDIO_HD_RECORD_SCENE_TABLE_STRUCT Hd_Recrod_Scene_Table_default;

extern VOICE_RECOGNITION_PARAM_STRUCT Voice_Recognize_Par_default;

extern AUDIO_AUDENH_CONTROL_OPTION_STRUCT AUDENH_Control_Option_Par_default;

extern AUDIO_BUFFER_DC_CALIBRATION_STRUCT Audio_Buffer_DC_Calibration_Par_default;

extern AUDIO_VOIP_PARAM_STRUCT Audio_VOIP_Par_default;
extern AUDIO_HFP_PARAM_STRUCT audio_hfp_param_custom_default;
extern AUDIO_ANC_CUSTOM_PARAM_STRUCT speech_ANC_custom_default;
extern AUDIO_SPEAKER_MONITOR_PARAM_STRUCT speaker_monitor_par_default;
extern AUDIO_CUSTOM_MAGI_CONFERENCE_STRUCT speech_magi_conference_custom_default;
extern AUDIO_CUSTOM_HAC_PARAM_STRUCT speech_hac_param_custom_default;
extern AUDIO_CUSTOM_SPEECH_LPBK_PARAM_STRUCT speech_lpbk_param_custom_default;
extern AUDIO_BT_GAIN_STRUCT bt_gain_control_default;
extern AUDIO_CUSTOM_AUDIO_FUNC_SWITCH_PARAM_STRUCT audio_func_swtich_param_custom_default;

#endif
#ifdef __cplusplus
}
#endif

#endif
