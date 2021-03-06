/*Copyright 2015 Intel(r) Corporation

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

http ://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.*/

#ifndef __UMF_DATASOURCE_HPP__
#define __UMF_DATASOURCE_HPP__

#include "config.hpp"

namespace umf {
/*!
 * \brief Prepares UMF internal objects for work
 */
void UMF_EXPORT initialize();

/*!
 * \brief Destroys UMF internal objects
 */
void UMF_EXPORT terminate();

} // namespace umf

#endif /* __UMF_DATASOURCE_HPP__ */
