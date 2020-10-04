// SPDX-License-Identifier: Apache-2.0

/*
 * Copyright 2020 Joel E. Anderson
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

#include <stdatomic.h>
#include <stdbool.h>
#include <stdint.h>
#include "private/config/have_stdatomic.h"
#include "private/config/wrapper/thread_safety.h"

bool
stdatomic_compare_exchange_ptr( config_atomic_ptr_t *p,
                                const void *expected,
                                void *replacement ) {
  uintptr_t expected_uint = ( uintptr_t ) expected;

  return atomic_compare_exchange_strong( p,
                                         &expected_uint,
                                         ( uintptr_t ) replacement );
}

void *
stdatomic_read_ptr( config_atomic_ptr_t *p ) {
  return ( void * ) atomic_load( p );
}

void
stdatomic_write_ptr( config_atomic_ptr_t *p, void *replacement ) {
  atomic_store( p, ( uintptr_t ) replacement );
}
