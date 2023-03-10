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

#ifndef __DRM_CTA_PLUGIN_H__
#define __DRM_CTA_PLUGIN_H__

#include <DrmEngineBase.h>
#include <SessionMap.h>
#include <DrmCtaUtil.h>
#include <DrmDef.h>
#include <DrmTypeDef.h>
#include <string.h>
#include <strings.h>
#include <unistd.h>
#include <semaphore.h>
#include <utils/Vector.h>
#include <utils/KeyedVector.h>

#include <Cta5File.h>
#include <Cta5FileFactory.h>

using namespace std;

namespace android {

class DrmCtaPlugIn : public DrmEngineBase {
  public:
    DrmCtaPlugIn();
    virtual ~DrmCtaPlugIn();

  protected:
    DrmConstraints* onGetConstraints(int uniqueId, const String8* path, int action);

    DrmMetadata* onGetMetadata(int uniqueId, const String8* path);

    status_t onInitialize(int uniqueId);

    status_t onSetOnInfoListener(int uniqueId, const IDrmEngine::OnInfoListener* infoListener);

    status_t onTerminate(int uniqueId);

    bool onCanHandle(int uniqueId, const String8& path);

    DrmInfoStatus* onProcessDrmInfo(int uniqueId, const DrmInfo* drmInfo);

    status_t onSaveRights(int uniqueId, const DrmRights& drmRights, const String8& rightsPath,
                          const String8& contentPath);

    DrmInfo* onAcquireDrmInfo(int uniqueId, const DrmInfoRequest* drmInfoRequest);

    String8 onGetOriginalMimeType(int uniqueId, const String8& path, int fd);

    int onGetDrmObjectType(int uniqueId, const String8& path, const String8& mimeType);

    int onCheckRightsStatus(int uniqueId, const String8& path, int action);

    status_t onConsumeRights(int uniqueId, sp<DecryptHandle>& decryptHandle, int action,
                             bool reserve);

    status_t onSetPlaybackStatus(int uniqueId, sp<DecryptHandle>& decryptHandle, int playbackStatus,
                                 int64_t position);

    bool onValidateAction(int uniqueId, const String8& path, int action,
                          const ActionDescription& description);

    status_t onRemoveRights(int uniqueId, const String8& path);

    status_t onRemoveAllRights(int uniqueId);

    status_t onOpenConvertSession(int uniqueId, int convertId);

    DrmConvertedStatus* onConvertData(int uniqueId, int convertId, const DrmBuffer* inputData);

    DrmConvertedStatus* onCloseConvertSession(int uniqueId, int convertId);

    DrmSupportInfo* onGetSupportInfo(int uniqueId);

    status_t onOpenDecryptSession(int uniqueId, sp<DecryptHandle>& decryptHandle, int fd,
                                  off64_t offset, off64_t length);

    status_t onOpenDecryptSession(int uniqueId, sp<DecryptHandle>& decryptHandle, const char* uri);

    status_t onCloseDecryptSession(int uniqueId, sp<DecryptHandle>& decryptHandle);

    status_t onInitializeDecryptUnit(int uniqueId, sp<DecryptHandle>& decryptHandle,
                                     int decryptUnitId, const DrmBuffer* headerInfo);

    status_t onDecrypt(int uniqueId, sp<DecryptHandle>& decryptHandle, int decryptUnitId,
                       const DrmBuffer* encBuffer, DrmBuffer** decBuffer, DrmBuffer* IV);

    status_t onFinalizeDecryptUnit(int uniqueId, sp<DecryptHandle>& decryptHandle,
                                   int decryptUnitId);

    ssize_t onPread(int uniqueId, sp<DecryptHandle>& decryptHandle, void* buffer, ssize_t numBytes,
                    off64_t offset);

  private:
    /*
     * an inner class for storing necessary information needed for decryption.
     */
    class DecryptSession {
      private:
        DecryptSession() : pCta5File(NULL) {}

      public:
        DecryptSession(Cta5File* pFile) {
            pCta5File = pFile;
            if (pCta5File == NULL) {
                ALOGE("pCta5File is NULL");
            }
        }

        ~DecryptSession() {
            // close fd
            if (pCta5File != NULL) {
                delete pCta5File;
                pCta5File = NULL;
            }
        }

      public:
        Cta5File* pCta5File;
    };

  private:
    /**
     * Session Map Tables for Conversion and Decoding of forward lock files.
     */
    SessionMap<DecryptSession*> m_decryptSessionMap;
    volatile bool mIsEncryptThreadCreated;
    volatile bool mIsDecryptThreadCreated;
    volatile bool mEncryptThreadNeedCanceled;
    volatile bool mDecryptThreadNeedCanceled;
    sem_t mAvailEncryptSem;
    sem_t mAvailDecryptSem;
    Vector<Cta5File*> mAvailEncryptFiles;
    Vector<Cta5File*> mAvailDecryptFiles;
    pthread_t mEncryptThreadId;
    pthread_t mDecryptThreadId;
    Mutex mEncryptMutex;
    Mutex mDecryptMutex;
    String8 mKey;
    KeyedVector<String8, String8>* mTokenMap;
    //(path,processname)
    KeyedVector<String8, String8> mTokenCheckedMap;

    static Vector<DrmCtaUtil::Listener>* sJavaAPIListeners;

  private:
    bool encrypt(const DrmInfoRequest* drmInfoRequest);
    bool decryptInfR(const DrmInfoRequest* drmInfoRequest);
    bool cancel(const DrmInfoRequest* drmInfoRequest);
    bool setKey(const DrmInfoRequest* drmInfoRequest);
    bool ChangeKey(const DrmInfoRequest* drmInfoRequest);
    bool isCta5File(const DrmInfoRequest* drmInfoRequest);
    bool getProgress(const DrmInfoRequest* drmInfoRequest);
    bool isTokenValid(const DrmInfoRequest* drmInfoRequest);
    bool clearToken(const DrmInfoRequest* drmInfoRequest);
    String8 getToken(const DrmInfoRequest* drmInfoRequest);

    // create a encrypt/decrypt thread
    bool createEncryptThread();
    bool createDecryptThread();
    friend void* encryptThread(void* arg);
    friend void* decryptThread(void* arg);
};
}  // namespace android

#endif /* __DRM_CTA_PLUGIN_H__ */
