/*
 * Copyright (C) 2023 The LineageOS Project
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

#pragma once

#include <hidl/MQDescriptor.h>
#include <hidl/Status.h>
#include <stdint.h>
#include <vendor/lineage/fastcharge/1.0/IRestrictedCurrent.h>

namespace vendor {
namespace lineage {
namespace fastcharge {
namespace V1_0 {
namespace implementation {

using ::android::sp;
using ::android::hardware::hidl_array;
using ::android::hardware::hidl_memory;
using ::android::hardware::hidl_string;
using ::android::hardware::hidl_vec;
using ::android::hardware::Return;
using ::android::hardware::Void;

using ::vendor::lineage::fastcharge::V1_0::IRestrictedCurrent;

struct RestrictedCurrent : public IRestrictedCurrent {
    RestrictedCurrent();

    Return<int32_t> getRestrictedCurrent() override;
    Return<bool> setRestrictedCurrent(int32_t current_mA) override;
    Return<int32_t>  getMaxSupportedCurrent() override;
};

} // namespace implementation
} // namespace V1_0
} // namespace fastcharge
} // namespace lineage
} // namespace vendor
