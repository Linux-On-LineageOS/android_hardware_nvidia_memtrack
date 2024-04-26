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

#pragma once

#include <aidl/android/hardware/memtrack/BnMemtrack.h>
#include <aidl/android/hardware/memtrack/DeviceInfo.h>
#include <aidl/android/hardware/memtrack/MemtrackRecord.h>
#include <aidl/android/hardware/memtrack/MemtrackType.h>
#include <vector>

namespace aidl {
namespace android {
namespace hardware {
namespace memtrack {

using aidl::android::hardware::memtrack::BnMemtrack;
using aidl::android::hardware::memtrack::DeviceInfo;
using aidl::android::hardware::memtrack::MemtrackRecord;
using aidl::android::hardware::memtrack::MemtrackType;

class Memtrack : public BnMemtrack {
public:
    ndk::ScopedAStatus getMemory(int pid, MemtrackType type,
                                 std::vector<MemtrackRecord>* _aidl_return) override;
    ndk::ScopedAStatus getGpuDeviceInfo(std::vector<DeviceInfo>* _aidl_return) override;

private:
    enum MemtrackFlag {
      SMAPS_ACCOUNTED = MemtrackRecord::FLAG_SMAPS_ACCOUNTED,
      SMAPS_UNACCOUNTED = MemtrackRecord::FLAG_SMAPS_UNACCOUNTED,
      PRIVATE = MemtrackRecord::FLAG_PRIVATE,
      SHARED_PSS = MemtrackRecord::FLAG_SHARED_PSS,
      DEDICATED = MemtrackRecord::FLAG_DEDICATED,
      SYSTEM = MemtrackRecord::FLAG_SYSTEM,
      NONSECURE = MemtrackRecord::FLAG_NONSECURE,
    };

    std::vector<MemtrackRecord> getNvmapMemory(int pid, MemtrackType type);
    bool valid_type(MemtrackType requested_type, uint32_t entry_type);
};

}
}
}
}
