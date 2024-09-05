/*
 *  Copyright (c) 2021 NetEase Inc.
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 */

/*
 * Project: curve
 * Created Date: Thu Jul 22 10:45:43 CST 2021
 * Author: wuhanqing
 */

#include "curvefs/src/mds/codec/codec.h"

#include <cstdlib>
#include <cstring>

#include "src/common/encode.h"

namespace curvefs {
namespace mds {
namespace codec {

using ::curve::common::EncodeBigEndian;
using ::curve::common::EncodeBigEndian_uint32;
using ::curvefs::mds::BLOCKGROUP_KEY_END;
using ::curvefs::mds::BLOCKGROUP_KEY_PREFIX;
using ::curvefs::mds::COMMON_PREFIX_LENGTH;
using ::curvefs::mds::FS_NAME_KEY_PREFIX;

std::string EncodeFsName(const std::string& fsName) {
  std::string key;

  key.resize(COMMON_PREFIX_LENGTH + fsName.size());

  memcpy(&key[0], FS_NAME_KEY_PREFIX, COMMON_PREFIX_LENGTH);
  memcpy(&key[COMMON_PREFIX_LENGTH], fsName.data(), fsName.size());

  return key;
}

std::string EncodeBlockGroupKey(uint32_t fsId, uint64_t offset) {
  static const size_t size =
      COMMON_PREFIX_LENGTH + sizeof(fsId) + sizeof(offset);

  std::string key;
  key.resize(size);

  memcpy(&key[0], BLOCKGROUP_KEY_PREFIX, COMMON_PREFIX_LENGTH);

  EncodeBigEndian_uint32(&key[COMMON_PREFIX_LENGTH], fsId);
  EncodeBigEndian(&key[COMMON_PREFIX_LENGTH + sizeof(fsId)], offset);

  return key;
}

}  // namespace codec
}  // namespace mds
}  // namespace curvefs
