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

#ifndef MTK_WPA_SUPPLICANT_HIDL_STA_NETWORK_H
#define MTK_WPA_SUPPLICANT_HIDL_STA_NETWORK_H

#include <array>
#include <vector>

#include <android-base/macros.h>

#include <vendor/mediatek/hardware/wifi/supplicant/2.0/ISupplicantStaNetwork.h>
#include <vendor/mediatek/hardware/wifi/supplicant/2.0/ISupplicantStaNetworkCallback.h>

namespace vendor {
namespace mediatek {
namespace hardware {
namespace wifi {
namespace supplicant {
namespace V2_1 {
namespace implementation {
using android::sp;
using android::hardware::hidl_string;
using android::hardware::Return;
using android::hardware::wifi::supplicant::V1_0::IfaceType;
using android::hardware::wifi::supplicant::V1_0::SupplicantNetworkId;
using android::hardware::wifi::supplicant::V1_0::SupplicantStatus;

/**
 * Implementation of StaNetwork hidl object. Each unique hidl
 * object is used for control operations on a specific network
 * controlled by wpa_supplicant.
 */
class StaNetwork : public V2_0::ISupplicantStaNetwork {
  public:
    StaNetwork(struct wpa_global* wpa_global, const char ifname[], int network_id);
    ~StaNetwork() override = default;
    // Refer to |StaIface::invalidate()|.
    void invalidate();
    bool isValid();

    // Hidl methods exposed.
    Return<void> getId(getId_cb _hidl_cb) override;
    Return<void> getInterfaceName(getInterfaceName_cb _hidl_cb) override;
    Return<void> getType(getType_cb _hidl_cb) override;
    Return<void> registerCallback(const sp<V2_0::ISupplicantStaNetworkCallback>& callback,
                                  registerCallback_cb _hidl_cb) override;
    Return<void> setWapiCertAlias(const hidl_string& alias, setWapiCertAlias_cb _hidl_cb) override;
    Return<void> setEapOcsp(Ocsp ocsp, setEapOcsp_cb _hidl_cb) override;

  private:
    std::pair<SupplicantStatus, uint32_t> getIdInternal();
    std::pair<SupplicantStatus, std::string> getInterfaceNameInternal();
    std::pair<SupplicantStatus, IfaceType> getTypeInternal();
    // Corresponding worker functions for the HIDL methods.
    SupplicantStatus registerCallbackInternal(
            const sp<V2_0::ISupplicantStaNetworkCallback>& callback);

    SupplicantStatus setWapiCertAliasInternal(const std::string& alias);
    SupplicantStatus setEapOcspInternal(Ocsp ocsp);

    struct wpa_ssid* retrieveNetworkPtr();
    struct wpa_supplicant* retrieveIfacePtr();
    void resetInternalStateAfterParamsUpdate();
    int setStringFieldAndResetState(const char* value, uint8_t** to_update_field,
                                    const char* hexdump_prefix);
    int setStringFieldAndResetState(const char* value, char** to_update_field,
                                    const char* hexdump_prefix);
    int setStringKeyFieldAndResetState(const char* value, char** to_update_field,
                                       const char* hexdump_prefix);
    int setByteArrayFieldAndResetState(const uint8_t* value, const size_t value_len,
                                       uint8_t** to_update_field, size_t* to_update_field_len,
                                       const char* hexdump_prefix);
    int setByteArrayKeyFieldAndResetState(const uint8_t* value, const size_t value_len,
                                          uint8_t** to_update_field, size_t* to_update_field_len,
                                          const char* hexdump_prefix);

    // Reference to the global wpa_struct. This is assumed to be valid
    // for the lifetime of the process.
    struct wpa_global* wpa_global_;
    // Name of the iface this network belongs to.
    const std::string ifname_;
    // Id of the network this hidl object controls.
    const int network_id_;
    bool is_valid_;

    DISALLOW_COPY_AND_ASSIGN(StaNetwork);
};

}  // namespace implementation
}  // namespace V2_1
}  // namespace supplicant
}  // namespace wifi
}  // namespace hardware
}  // namespace mediatek
}  // namespace vendor
#endif  // MTK_WPA_SUPPLICANT_HIDL_STA_NETWORK_H
