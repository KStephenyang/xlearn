//------------------------------------------------------------------------------
// Copyright (c) 2016 by contributors. All Rights Reserved.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//------------------------------------------------------------------------------

/*
Author: Chao Ma (mctt90@gmail.com)

This file defines the KVStore class, which allows workers to get
and set the model parameters.
*/

#ifndef XLEARN_DISTRIBUTED_KVSTORE_H_
#define XLEARN_DISTRIBUTED_KVSTORE_H_

#include <vector>

#include "src/base/common.h"
#include "src/data/data_structure.h"

namespace xLearn {

//------------------------------------------------------------------------------
// KVStore are used for distributed training and it allows workers to get
// and set the model parameters by using pull() and push() API.
//------------------------------------------------------------------------------
class KVStore {
 public:
   // Constructor and Destructor
   KVStore() { }
   ~KVStore() { }

   // Push a list of (key, value) into store.
   // For example:
   //  ------------------------------------------------------
   // |  key:   |  0  |  2  |  4  |  5  |  6   |  7   |  9   |
   // | value:  | 0.2 | 1.0 | 0.5 | 1.0 | 0.33 |  0.7 |  0.8 |
   //  ------------------------------------------------------
   virtual void Push(const std::vector<index_t>& key,
   	                 const std::vector<real_t>& value);

   // Push a list of (key, value_list) into store.
   // For example:
   //  ------------------------------------------------------
   // |  key:   |  0  |  2  |  4  |  5  |  6   |  7   |  9   |
   // | value:  | 0.2 | 1.0 | 0.5 | 1.0 | 0.33 |  0.7 |  0.8 |
   // |         | 0.1 | 1.2 | 0.1 | 0.8 | 0.9  |  1.0 |  0.5 |
   // |         | 0.5 | 1.4 | 1.7 | 1.5 | 0.8  |  0.7 |  0.6 |
   // |         | 0.2 | 1.2 | 1.4 | 1.8 | 0.5  |  1.1 |  1.8 |
   // |         | ..  | ..  | ..  | ..  | ..   |  ..  |  ..  |
   //  ------------------------------------------------------
   // This method is useful for the FM and FFM task.
   virtual void Push(const std::vector<index_t>& key,
   	                 const std::vector<real_t>& value_list,
   	                 const size_t length);

   // Pull the values for a list of keys from store.
   // For example:
   //  ------------------------------------------------------
   // |  key:   |  0  |  2  |  4  |  5  |  6   |  7   |  9   |
   // | value:  | 0.2 | 1.0 | 0.5 | 1.0 | 0.33 |  0.7 |  0.8 |
   //  ------------------------------------------------------
   virtual void Pull(const std::vector<index_t>& key,
   	                 std::vector<real_t>* value);

   // Pull the value list for a list of keys from store.
   // For example:
   //  ------------------------------------------------------
   // |  key:   |  0  |  2  |  4  |  5  |  6   |  7   |  9   |
   // | value:  | 0.2 | 1.0 | 0.5 | 1.0 | 0.33 |  0.7 |  0.8 |
   // |         | 0.1 | 1.2 | 0.1 | 0.8 | 0.9  |  1.0 |  0.5 |
   // |         | 0.5 | 1.4 | 1.7 | 1.5 | 0.8  |  0.7 |  0.6 |
   // |         | 0.2 | 1.2 | 1.4 | 1.8 | 0.5  |  1.1 |  1.8 |
   // |         | ..  | ..  | ..  | ..  | ..   |  ..  |  ..  |
   //  ------------------------------------------------------
   // This method is useful for the FM and FFM task.
   virtual void Pull(const std::vector<index_t>& key,
   	                 std::vector<real_t>* value_list,
   	                 const size_t length);
};

}  // namespace xLearn

#endif  // XLEARN_DISTRIBUTED_KVSTORE_H_