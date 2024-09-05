/*
 *  Copyright (c) 2020 NetEase Inc.
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
 * File Created: 2019-12-05
 * Author: charisu
 */

#ifndef TEST_TOOLS_MOCK_MOCK_ETCD_CLIENT_H_
#define TEST_TOOLS_MOCK_MOCK_ETCD_CLIENT_H_

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <map>
#include <string>
#include <vector>

#include "src/tools/etcd_client.h"

using ::testing::Return;
namespace curve {
namespace tool {
class MockEtcdClient : public EtcdClient {
 public:
  MockEtcdClient() {}
  ~MockEtcdClient() {}
  MOCK_METHOD1(Init, int(const std::string&));
  MOCK_METHOD2(GetEtcdClusterStatus,
               int(std::vector<std::string>*, std::map<std::string, bool>*));
  MOCK_METHOD2(GetAndCheckEtcdVersion,
               int(std::string*, std::vector<std::string>*));
};
}  // namespace tool
}  // namespace curve
#endif  // TEST_TOOLS_MOCK_MOCK_ETCD_CLIENT_H_
