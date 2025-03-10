/*
 * Copyright (C) 2022 The LineageOS Project
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

#define LOG_TAG "vendor.lineage.livedisplay@2.1-service.sdm710"

#include <android-base/logging.h>
#include <binder/ProcessState.h>
#include <hidl/HidlTransportSupport.h>
#include <livedisplay/sdm/PictureAdjustment.h>

#include "AntiFlicker.h"
#include "SunlightEnhancement.h"

using ::vendor::lineage::livedisplay::V2_0::sdm::PictureAdjustment;
using ::vendor::lineage::livedisplay::V2_0::sdm::SDMController;
using ::vendor::lineage::livedisplay::V2_1::implementation::AntiFlicker;
using ::vendor::lineage::livedisplay::V2_1::implementation::SunlightEnhancement;

int main() {
    android::sp<SunlightEnhancement> sunlightEnhancement = new SunlightEnhancement();
    android::sp<AntiFlicker> antiFlicker = new AntiFlicker();
    std::shared_ptr<SDMController> controller = std::make_shared<SDMController>();
    android::sp<PictureAdjustment> pictureAdjustment = new PictureAdjustment(controller);

    android::hardware::configureRpcThreadpool(1, true /*callerWillJoin*/);

    if (pictureAdjustment->registerAsService() != android::OK) {
        LOG(ERROR) << "Cannot register picture adjustment HAL service.";
        return 1;
    }

#ifdef SUPPORT_ANTI_FLICKER
    if (antiFlicker->isSupported()) {
        if (antiFlicker->registerAsService() != android::OK) {
            LOG(ERROR) << "Cannot register antiflicker HAL service.";
            return 1;
        }
    }
#endif

#ifdef SUPPORT_SUNLIGHT_ENHANCEMENT
    if (sunlightEnhancement->isSupported()) {
        if (sunlightEnhancement->registerAsService() != android::OK) {
            LOG(ERROR) << "Cannot register sunlight enhancement HAL service.";
	          return 1;
	      }
    }
#endif

    LOG(INFO) << "LiveDisplay HAL service is ready.";

    android::hardware::joinRpcThreadpool();

    LOG(ERROR) << "LiveDisplay HAL service failed to join thread pool.";

    return 1;
}
