/*
 * Copyright 2019 International Business Machines
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
#ifndef BUFMEMCOPY_H_h
#define BUFMEMCOPY_H_h

#include <vector>
#include <boost/shared_ptr.hpp>
#include <boost/thread.hpp>
#include "BufBase.h"
#include "HardwareManager.h"

class BufMemCopy : public BufBase
{
public:
    // Constructor of buffer base
    BufMemCopy();
    BufMemCopy (int in_id);
    BufMemCopy (int in_id, int in_timeout);

    // Destructor of buffer base
    ~BufMemCopy();

    // Get source address
    void* get_src_ptr();

    // Get destination address
    void* get_dest_ptr();

    // Get the size of the source buffer
    size_t get_src_size();

    // Get the size of the destination buffer
    size_t get_dest_size();

    // Allocate memory buffers
    int allocate (size_t in_src_size, size_t in_dest_size);

    // Work with the jobs
    virtual void work_with_job (JobPtr in_job);

private:
    // Source address
    void* m_src;

    // Destination address
    void* m_dest;

    // The size of the source buffer
    size_t m_src_size;

    // The size of the destination buffer
    size_t m_dest_size;

    // Helper function to alloc aligned memory buffers
    void* aalloc (int align, int size);

    // Locks to sync between buffers (threads) on the same kernel,
    // specific to the number of kernels
    static boost::mutex m_kernel_mutex[8];
};

typedef boost::shared_ptr<BufMemCopy> BufMemCopyPtr;

#endif
