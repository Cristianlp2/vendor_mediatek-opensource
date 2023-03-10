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

#include "libnvram_sec.h"
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define NVRAM_PROTECT_META_MODE_WRITE 1
#define NVRAM_PROTECT_SECURITY_ENABLE 2
extern const TCFG_FILE g_akCFG_File[];
extern const TCFG_FILE g_akCFG_File_Custom[];
extern const TCFG_FILE_PROTECT g_akCFG_File_Protect[];

extern int iCustomBeginLID;
extern const int g_i4CFG_File_Count;
extern const int g_i4CFG_File_Custom_Count;
extern const int g_i4CFG_File_Protect_Count;

static bool NVM_InProtectList(int file_lid, int protect_type);
static bool NVM_CheckBootMode();
static const TCFG_FILE* NVM_GetCfgFileTableForSec(int file_lid);

int __attribute__((weak)) sec_nvram_enc(META_CONTEXT* meta_ctx) {
    //		NVRAM_LOG("weak enc!\n");
    return 0;
}

int __attribute__((weak)) sec_nvram_dec(META_CONTEXT* meta_ctx) {
    //		NVRAM_LOG("weak dec!\n");
    return 0;
}
bool NVM_CheckWritePermission(bool IsRead, int file_lid) {
    if (!NVM_CheckBootMode() && !IsRead &&
        NVM_InProtectList(file_lid, NVRAM_PROTECT_META_MODE_WRITE)) {
        NVRAM_LOG("[%s] : can not write in this mode!!!\n", __func__);
        return false;
    }
    return true;
}

bool NVM_Enc_Dnc_File(int file_lid, bool IS_enc) {
    struct stat file_stat;
    int loop_time;
    META_CONTEXT meta_ctx;
    // bobule workaround pdk build error, needing fixed
    static int length = NVRAM_CIPHER_LEN;
    int fd;
    int file_offset = 0;
    int op_size = 0;
    int sec_ret = 0;
    int left_size = 0;
    char* temp_buf = NULL;
    const TCFG_FILE* pCfgFielTable = NULL;
    int iRealFileLid = 0;

    if (!NVM_InProtectList(file_lid, NVRAM_PROTECT_SECURITY_ENABLE)) {
        // NVRAM_LOG("no need to enc/dnc\n");
        return true;
    }

    NVRAM_LOG("Enc/Dnc(%d) security file_lid : %d!!! \n", IS_enc, file_lid);
    pCfgFielTable = NVM_GetCfgFileTableForSec(file_lid);
    if (file_lid < iCustomBeginLID) {
        iRealFileLid = file_lid;
    } else {
        iRealFileLid = file_lid - iCustomBeginLID;
    }
    if (pCfgFielTable == NULL) {
        NVRAM_LOG("NVM_GetCfgFileTable Fail!!! \n");
        goto end;
    }

    fd = open(pCfgFielTable[iRealFileLid].cFileName, O_RDWR, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP);
    if (fd < 0) {
        NVRAM_LOG("open for Enc/Dnc error\n");
        goto end;
    }

    if (fstat(fd, &file_stat) < 0) {
        NVRAM_LOG("fstat fail,%s\n", strerror(errno));
        close(fd);
        goto end;
    }

    temp_buf = (char*)malloc(file_stat.st_size);
    if (NULL == temp_buf) {
        NVRAM_LOG("malloc fail,%s\n", strerror(errno));
        close(fd);
        goto end;
    }

    left_size = file_stat.st_size % NVRAM_CIPHER_LEN;
    if (left_size) {
        loop_time = file_stat.st_size / NVRAM_CIPHER_LEN + 1;
    } else
        loop_time = file_stat.st_size / NVRAM_CIPHER_LEN;

    while (loop_time--) {
        if (!loop_time && left_size) {
            length = left_size;
        } else
            length = NVRAM_CIPHER_LEN;

        op_size = read(fd, meta_ctx.data, length);
        if (length != op_size) {
            NVRAM_LOG("read file error,length(%d),op_size(%d),%s\n", length, op_size,
                      strerror(errno));
            close(fd);
            goto free_buff;
        }
        if (length == NVRAM_CIPHER_LEN) {
            if (IS_enc) {
                if (0 != (sec_ret = sec_nvram_enc(&meta_ctx))) {
                    NVRAM_LOG("enc security failed(%d)\n", sec_ret);
                    close(fd);
                    goto free_buff;
                }
            } else {
                if (0 != (sec_ret = sec_nvram_dec(&meta_ctx))) {
                    NVRAM_LOG("dec security failed(%d)\n", sec_ret);
                    close(fd);
                    goto free_buff;
                }
            }
        }
        if (memcpy(temp_buf + file_offset, meta_ctx.data, length) == -1) {
            NVRAM_LOG("write buffer error,%s\n", strerror(errno));
            close(fd);
            goto free_buff;
        }
        file_offset += length;
    }

    if (lseek(fd, 0, SEEK_SET) == -1) {
        NVRAM_LOG("write lseek error,%s\n", strerror(errno));
        close(fd);
        goto free_buff;
    }

    op_size = write(fd, temp_buf, file_stat.st_size);
    if (file_stat.st_size != op_size) {
        NVRAM_LOG("write file error,length(%d),op_size(%d),file_offset(%d),%s\n", length, op_size,
                  file_offset, strerror(errno));
        close(fd);
        goto free_buff;
    }
    free(temp_buf);
    close(fd);
    NVRAM_LOG("ENC/DNC(%d) Security done\n", IS_enc);
    return true;

free_buff:
    free(temp_buf);
end:
    return false;
}

static bool NVM_InProtectList(int file_lid, int protect_type) {
    int index = 0;
    for (index = 0; index < g_i4CFG_File_Protect_Count; index++) {
        if (file_lid == g_akCFG_File_Protect[index].lid) {
            if ((protect_type == NVRAM_PROTECT_META_MODE_WRITE) &&
                g_akCFG_File_Protect[index].meta_mode_write)
                return true;

            if ((protect_type == NVRAM_PROTECT_SECURITY_ENABLE) &&
                g_akCFG_File_Protect[index].security_enable)
                return true;
            break;
        }
    }
    return false;
}

static bool NVM_CheckBootMode() {
    int fd;
    bool ret = 0;
    size_t s;
    volatile char data[20];

    fd = open(BOOT_MODE_FILE, O_RDONLY);
    if (fd < 0) {
        NVRAM_LOG("fail to open %s: ", BOOT_MODE_FILE);
        perror("");
        return false;
    }

    s = read(fd, (void*)data, sizeof(char) * 3);
    if (s <= 0) {
        NVRAM_LOG("fail to read %s", BOOT_MODE_FILE);
        perror("");
        ret = false;
    } else {
        if (data[0] == META_MODE || data[0] == ADVMETA_MODE) {
            ret = true;
        } else {
            ret = false;
        }
    }

    close(fd);
    return ret;
}

static const TCFG_FILE* NVM_GetCfgFileTableForSec(int file_lid) {
    NVRAM_LOG("NVM_GetCfgFileTableForSec : file_lid = %d\n", file_lid);

    if (file_lid >= (g_i4CFG_File_Count + g_i4CFG_File_Custom_Count)) {
        NVRAM_LOG("NVM_GetCfgFileTable file_lid is over than maximum %d\n",
                  (g_i4CFG_File_Count + g_i4CFG_File_Custom_Count));
        return NULL;
    }

    if (file_lid < iCustomBeginLID) {
        return g_akCFG_File;
    }

    return g_akCFG_File_Custom;
}
