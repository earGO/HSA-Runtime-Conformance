/*
 * =============================================================================
 *   HSA Runtime Conformance Release License
 * =============================================================================
 * The University of Illinois/NCSA
 * Open Source License (NCSA)
 *
 * Copyright (c) 2014, Advanced Micro Devices, Inc.
 * All rights reserved.
 *
 * Developed by:
 *
 *                 AMD Research and AMD HSA Software Development
 *
 *                 Advanced Micro Devices, Inc.
 *
 *                 www.amd.com
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to
 * deal with the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 *  - Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimers.
 *  - Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimers in
 *    the documentation and/or other materials provided with the distribution.
 *  - Neither the names of <Name of Development Group, Name of Institution>,
 *    nor the names of its contributors may be used to endorse or promote
 *    products derived from this Software without specific prior written
 *    permission.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
 * THE CONTRIBUTORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR
 * OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS WITH THE SOFTWARE.
 *
 */

#include <hsa.h>
#include <framework.h>

/**
 *
 * Test Name: hsa_signal_cas_relaxed.
 *
 * Purpose:
 * Verify that is the API works as expected.
 *
 * Description:
 *
 * 1) Create an new signal object and call hsa_signal_cas_relaxed API to exchange the initial value.
 *    Load the value of signal to check is the new value if stored in to signal.
 *
 */

/**
 *
 * @Brief:
 * Implement description #1
 *
 * @Return:
 * int
 *
 */

int test_hsa_signal_cas_relaxed() {
    hsa_status_t status;

    status = hsa_init();
    ASSERT(HSA_STATUS_SUCCESS == status);

    hsa_signal_t signal_handle;
    hsa_signal_value_t initial_value = 100, expected_value = 100, new_value = 200, observed_value, loaded_value;

    status = hsa_signal_create(initial_value, 0, NULL, &signal_handle);
    ASSERT(HSA_STATUS_SUCCESS == status);

    observed_value = hsa_signal_cas_relaxed(signal_handle, expected_value, new_value);
    ASSERT_MSG(observed_value == initial_value, "The hsa_signal_cas_relaxed API failed to return the initial value.\n");

    loaded_value = hsa_signal_load_relaxed(signal_handle);
    ASSERT_MSG(new_value == loaded_value, "The hsa_signal_cas_relaxed API failed to exchange the new value.\n");

    status = hsa_signal_destroy(signal_handle);
    ASSERT(HSA_STATUS_SUCCESS == status);

    status = hsa_shut_down();
    ASSERT(HSA_STATUS_SUCCESS == status);

    return 0;
}
