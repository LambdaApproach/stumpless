// SPDX-License-Identifier: Apache-2.0

/*
 * Copyright 2019-2020 Joel E. Anderson
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <stddef.h>
#include <stumpless/facility.h>
#include <stumpless/option.h>
#include <stumpless/target.h>
#include <stumpless/target/socket.h>
#include "private/config/socket_supported.h"

struct stumpless_target *
socket_open_default_target( void ) {
  return stumpless_open_socket_target( STUMPLESS_DEFAULT_SOCKET,
                                       NULL,
                                       STUMPLESS_OPTION_NONE,
                                       STUMPLESS_FACILITY_USER );
}
