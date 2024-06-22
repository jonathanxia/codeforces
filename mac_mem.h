/**
 * Computes the memory usage of the current process, but for
 * mac instead.
 */
#pragma once
#include <mach/mach.h>

int mem_usage() {
    task_t task = mach_task_self();
    struct task_basic_info info;
    mach_msg_type_number_t info_count = TASK_BASIC_INFO_COUNT;

    if (task_info(task, TASK_BASIC_INFO, (task_info_t)&info, &info_count) != KERN_SUCCESS) {
        return -1;
    }

    // The resident_size is in bytes, converting to KB
    return info.resident_size / 1024;
}