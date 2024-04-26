/*
 * Copyright (C) 2017 The Android Open Source Project
 * Copyright (C) 2024 The LineageOS Project
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

#define LOG_TAG "android.hardware.memtrack-service-nvidia"

#include <android/log.h>
#include <utils/Log.h>
#include "Memtrack-aidl.h"
#include <fstream>

namespace aidl {
namespace android {
namespace hardware {
namespace memtrack {

#include "nvmap.cpp"

ndk::ScopedAStatus Memtrack::getMemory(int pid, MemtrackType type,
        std::vector<MemtrackRecord>* records) {
    records->clear();

    switch (type) {
        case MemtrackType::GL:
        case MemtrackType::GRAPHICS:
            *records = getNvmapMemory(pid, type);
            break;

        default:
            break;
    };

    return ndk::ScopedAStatus::ok();
}

ndk::ScopedAStatus Memtrack::getGpuDeviceInfo(std::vector<DeviceInfo>* _aidl_return) {
    _aidl_return->clear();
    DeviceInfo dev_info = {.id = 0, .name = "nvgpu"};
    _aidl_return->emplace_back(dev_info);
    return ndk::ScopedAStatus::ok();
}

}
}
}
}
