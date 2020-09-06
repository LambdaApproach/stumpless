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

#include <cstddef>
#include <cstdio>
#include <fstream>
#include <gtest/gtest.h>
#include <stumpless.h>
#include <thread>
#include "test/function/rfc5424.hpp"
#include "test/helper/assert.hpp"

namespace {
  const int THREAD_COUNT = 16;
  const int MESSAGE_COUNT = 100;

  void
  write_messages( struct stumpless_target *target ) {
    for( int i = 0; i < MESSAGE_COUNT; i++ ) {
      stumpless_add_message( target,
                             "message number #%d from thread #%d",
                             i,
                             pthread_self(  ) );
    }

    stumpless_free_thread(  );
  }

  TEST( WriteConsistency, SimultaneousWrites ) {
    const char *filename = "file_target_thread_safety.log";
    FILE *log_stream;
    struct stumpless_target *target;
    size_t i;
    std::thread *threads[THREAD_COUNT];

    log_stream = fopen( filename, "w+" );
    ASSERT_NOT_NULL( log_stream );

    // set up the target to log to
    target = stumpless_open_stream_target( filename,
                                           log_stream,
                                           STUMPLESS_OPTION_NONE,
                                           STUMPLESS_FACILITY_USER );
    EXPECT_NO_ERROR;
    ASSERT_NOT_NULL( target );

    for( i = 0; i < THREAD_COUNT; i++ ) {
      threads[i] = new std::thread( write_messages, target );
    }

    for( i = 0; i < THREAD_COUNT; i++ ) {
      threads[i]->join(  );
      delete threads[i];
    }

    // cleanup after the test
    stumpless_close_stream_target( target );
    fclose( log_stream );
    EXPECT_NO_ERROR;

    stumpless_free_all(  );

    // check for consistency in the log file
    std::ifstream log_file( filename );
    std::string line;
    i = 0;
    while( std::getline( log_file, line ) ) {
      TestRFC5424Compliance( line.c_str() );
      i++;
    }
    EXPECT_EQ( i, THREAD_COUNT * MESSAGE_COUNT );

    remove( filename );
  }
}