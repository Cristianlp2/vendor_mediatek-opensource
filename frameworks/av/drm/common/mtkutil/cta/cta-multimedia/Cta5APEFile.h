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

#ifndef __CTA5_APE_FILE_H__
#define __CTA5_APE_FILE_H__

#include <Cta5File.h>
#include <Cta5CommonMultimediaFile.h>

namespace android {

#define APE_MIN_VERSION 3950 /* originally set to 3970, but 3950 should work */
#define APE_MAX_VERSION 4100
#define APE_MAX_COMPRESS 4000

#define MAC_FORMAT_FLAG_8_BIT 1           // is 8-bit [OBSOLETE]
#define MAC_FORMAT_FLAG_CRC 2             // uses the new CRC32 error detection [OBSOLETE]
#define MAC_FORMAT_FLAG_HAS_PEAK_LEVEL 4  // uint32 nPeakLevel after the header [OBSOLETE]
#define MAC_FORMAT_FLAG_24_BIT 8          // is 24-bit [OBSOLETE]
#define MAC_FORMAT_FLAG_HAS_SEEK_ELEMENTS \
    16  // has the number of seek elements after the peak level
#define MAC_FORMAT_FLAG_CREATE_WAV_HEADER \
    32  // create the wave header on decompression (not stored)

#define MIN_RANDOM_FRAMES_TO_SCAN 4
#define MIN_RANDOM_LOCATION_TO_SCAN 30

#define ape_parser_uint32_t unsigned int
#define ape_parser_uint16_t unsigned short
#define ape_parser_uint8_t unsigned char
#define ape_parser_int32_t signed int
#define ape_parser_int16_t signed short
#define ape_parser_int8_t signed char

struct ape_parser_ctx_t {
    /* Derived fields */
    ape_parser_uint32_t junklength;
    ape_parser_uint32_t firstframe;
    ape_parser_uint32_t totalsamples;

    /* Info from Descriptor Block */
    char magic[4];
    ape_parser_uint16_t fileversion;
    ape_parser_uint16_t padding1;
    ape_parser_uint32_t descriptorlength;
    ape_parser_uint32_t headerlength;
    ape_parser_uint32_t seektablelength;
    ape_parser_uint32_t wavheaderlength;
    ape_parser_uint32_t audiodatalength;
    ape_parser_uint32_t audiodatalength_high;
    ape_parser_uint32_t wavtaillength;
    ape_parser_uint8_t md5[16];

    /* Info from Header Block */
    ape_parser_uint16_t compressiontype;
    ape_parser_uint16_t formatflags;
    ape_parser_uint32_t blocksperframe;
    ape_parser_uint32_t finalframeblocks;
    ape_parser_uint32_t totalframes;
    ape_parser_uint16_t bps;
    ape_parser_uint16_t channels;
    ape_parser_uint32_t samplerate;

    int seektablefilepos; /* Location in .ape file of seektable */
    uint32_t* seektable;  /* Seektable buffer */
};

/**
 * This class is used to construct a CTA5 common multimedia file
 * If you want to parse a CTA5 file, the class is your beset choice
 * If you want to Convert a normal file to a CTA5 file, this class is your best choice
 * This class is a super class, and it's used for most multimedia fils which only has one header.
 * If you want to convert other multimedia files which have two or more headers,
 * you need to create a new class and implented from Cta5CommonMultimediaFile
 */
class Cta5APEFile : public Cta5CommonMultimediaFile {
  public:
    Cta5APEFile(int fd, String8 key);

    // This constructor is useful when you want to get a Cta5 file format
    // To convert a normal file to a CTA5 file, you may need this version
    Cta5APEFile(String8 mimeType, String8 cid, String8 dcfFlHeaders, uint64_t datatLen,
                String8 key);

    // Now dcf header is no need
    Cta5APEFile(String8 mimeType, uint64_t datatLen, String8 key);

  public:
    virtual ~Cta5APEFile() {}
    /*
     * This function is used to parse all main header of specified multimedia files
     * the result is one or more header offset and size
     */
    virtual bool parseHeaders(int fd);
};
}  // namespace android
#endif  //__CTA5_APE_FILE_H__
