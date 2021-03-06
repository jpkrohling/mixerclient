/* Copyright 2017 Istio Authors. All Rights Reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *    http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef MIXERCLIENT_ATTRIBUTE_CONTEXT_H
#define MIXERCLIENT_ATTRIBUTE_CONTEXT_H

#include "include/client.h"
#include "src/context_update.h"

namespace istio {
namespace mixer_client {

// A class to manage dictionary and context.
class AttributeContext {
 public:
  AttributeContext() : request_index_(0) {}

  // Fill Attributes protobuf.
  void FillProto(const Attributes& attributes,
                 ::istio::mixer::v1::Attributes* pb);
  // Increments request_index
  int64_t IncRequestIndex() { return ++request_index_; }

 private:
  // Find the index for a name. If not found, create a new one.
  int GetNameIndex(const std::string& name);

  // Create a StringMap message.
  ::istio::mixer::v1::StringMap CreateStringMap(
      const std::map<std::string, std::string>& string_map,
      const std::set<std::string>& exclude_keys);

  // dictionary map.
  std::map<std::string, int> dict_map_;

  // The request_index for this context.
  int64_t request_index_;

  // The attribute context update object.
  ContextUpdate context_;
};

}  // namespace mixer_client
}  // namespace istio

#endif  // MIXERCLIENT_ATTRIBUTE_CONTEXT_H
