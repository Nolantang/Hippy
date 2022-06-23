/*
 * Tencent is pleased to support the open source community by making
 * Hippy available.
 *
 * Copyright (C) 2017-2019 THL A29 Limited, a Tencent company.
 * All rights reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#pragma once

#include <string>
#include <vector>
#include "tunnel/net_channel.h"
#include "web_socket_client.h"

namespace hippy::devtools {
/**
 * @brief web socket channel to implement net
 */
class WebSocketChannel : public hippy::devtools::NetChannel, public std::enable_shared_from_this<WebSocketChannel> {
 public:
  explicit WebSocketChannel(const std::string& ws_uri);
  void Connect(ReceiveDataHandler handler) override;
  void Send(const std::string& rsp_data) override;
  void Close(int32_t code, const std::string& reason) override;

 private:
  void SetNeedsHandlers();
  void HandleConnectFail();
  void HandleConnectOpen();
  void HandleReceiveMessage(const std::string& message);
  void HandleClose();

  std::shared_ptr<WebSocketBaseClient> ws_client_;
  std::string ws_uri_;
  ReceiveDataHandler data_handler_;
  std::vector<std::string> unset_messages_{};
};
}  // namespace hippy::devtools
