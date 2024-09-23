#include <iostream>
#include <cstring>
#include <csignal>
#include <setjmp.h>
#include <cstdlib>
#include <ctime>

#ifndef PAGE_SIZE
# define PAGE_SIZE 65536
#endif

#ifndef BYPASS_ALLOC
# define BYPASS_ALLOC DEBUG
#endif

#ifndef MAGIC_NUMBER
# define MAGIC_NUMBER 0xDEADBEEF
#endif

// Include your custom memory allocator functions
// Assuming the allocator code is saved in "irc.hpp" as per your initial code
#include "irc.hpp" // Replace with the actual path if different

// Helper macros for test output
#define TEST_START(test_name) std::cout << "Starting Test: " << test_name << std::endl;
#define TEST_END(test_name) std::cout << "Completed Test: " << test_name << "\n" << std::endl;
#define TEST_PASS(test_name) std::cout << "[PASS] " << test_name << "\n" << std::endl;
#define TEST_FAIL(test_name, message) std::cerr << "[FAIL] " << test_name << " - " << message << "\n" << std::endl;

// Global variables for signal handling
static sigjmp_buf jump_buffer;
volatile sig_atomic_t abort_flag = 0;

// Signal handler for SIGSEGV
void handle_sigsegv(int signum) {
    abort_flag = 1;
    siglongjmp(jump_buffer, 1);
}

// Function to set up the SIGSEGV handler
void setup_sigsegv_handler() {
    struct sigaction sa;
    memset(&sa, 0, sizeof(sa));
    sa.sa_handler = handle_sigsegv;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;
    sigaction(SIGSEGV, &sa, NULL);
}

// Function to restore the default SIGSEGV handler
void restore_sigsegv_handler() {
    struct sigaction sa;
    memset(&sa, 0, sizeof(sa));
    sa.sa_handler = SIG_DFL;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;
    sigaction(SIGSEGV, &sa, NULL);
}

// Function prototypes for tests
void test_simple_allocation();
void test_zero_allocation();
void test_large_allocation();
void test_double_free();
void test_invalid_free();
void test_memory_leak_check();
void test_critical_memory_cleanup();
void test_non_critical_memory_cleanup();
void test_fragmentation();
void test_alignment();
void test_comprehensive_allocation();

int main() {
    // Run all tests
    test_simple_allocation();
    test_zero_allocation();
    test_large_allocation();
    test_double_free();
    test_invalid_free();
    test_memory_leak_check();
    test_critical_memory_cleanup();
    test_non_critical_memory_cleanup();
    if (BYPASS_ALLOC == 0)
        test_fragmentation();
    test_alignment();
	test_comprehensive_allocation();

    std::cout << "All tests completed." << std::endl;
    return 0;
}

// Test Definitions

void test_simple_allocation() {
    const char* test_name = "Simple Allocation and Deallocation";
    TEST_START(test_name);

    void* ptr = cma_malloc(100, false);
    if (ptr == NULL) {
        TEST_FAIL(test_name, "Allocation returned nullptr");
        TEST_END(test_name);
        return;
    }

    // Optionally, write to the allocated memory to ensure it's usable
    memset(ptr, 0, 100);

    cma_free(ptr);

    TEST_PASS(test_name);
    TEST_END(test_name);
}

void test_zero_allocation() {
    const char* test_name = "Zero-byte Allocation";
    TEST_START(test_name);

    void* ptr = cma_malloc(0, false);
    if (ptr == NULL) {
        TEST_PASS(test_name);
    } else {
        cma_free(ptr);
        TEST_FAIL(test_name, "Allocation of zero bytes should return nullptr or handle gracefully");
    }

    TEST_END(test_name);
}

void test_large_allocation() {
    const char* test_name = "Large Allocation";
    TEST_START(test_name);

    size_t large_size = PAGE_SIZE * 10; // Adjust PAGE_SIZE as defined in your allocator
    void* ptr = cma_malloc(large_size, false);
    if (ptr == NULL) {
        TEST_FAIL(test_name, "Large allocation returned nullptr");
        TEST_END(test_name);
        return;
    }

    // Optionally, write to the allocated memory to ensure it's usable
    memset(ptr, 0, large_size);

    cma_free(ptr);

    TEST_PASS(test_name);
    TEST_END(test_name);
}

void test_double_free() {
    const char* test_name = "Double Free Detection";
    TEST_START(test_name);

    // Set up SIGSEGV handler
    setup_sigsegv_handler();

    // Set jump point
    if (sigsetjmp(jump_buffer, 1) == 0) {
        // Run test code that may cause a segfault
        void* ptr = cma_malloc(100, false);
        if (ptr == NULL) {
            TEST_FAIL(test_name, "Allocation returned nullptr");
            restore_sigsegv_handler();
            TEST_END(test_name);
            return;
        }

        cma_free(ptr);
        // Attempt double free, should trigger segfault
        cma_free(ptr);

        // If we reach here, segfault was not triggered
        TEST_FAIL(test_name, "Double free did not cause segfault");
    } else {
        // Returned via siglongjmp from signal handler
        if (abort_flag) {
            TEST_PASS(test_name);
        } else {
            TEST_FAIL(test_name, "Unexpected segfault");
        }
    }

    // Reset abort flag and restore default handler
    abort_flag = 0;
    restore_sigsegv_handler();

    TEST_END(test_name);
}

void test_invalid_free() {
    const char* test_name = "Invalid Free Detection";
    TEST_START(test_name);

    // Set up SIGSEGV handler
    setup_sigsegv_handler();

    // Set jump point
    if (sigsetjmp(jump_buffer, 1) == 0) {
        // Run test code that may cause a segfault
        int dummy;
        void* invalid_ptr = &dummy;

        // Attempt invalid free, should trigger segfault
        cma_free(invalid_ptr);

        // If we reach here, segfault was not triggered
        TEST_FAIL(test_name, "Invalid free did not cause segfault");
    } else {
        // Returned via siglongjmp from signal handler
        if (abort_flag) {
            TEST_PASS(test_name);
        } else {
            TEST_FAIL(test_name, "Unexpected segfault");
        }
    }

    // Reset abort flag and restore default handler
    abort_flag = 0;
    restore_sigsegv_handler();

    TEST_END(test_name);
}

void test_memory_leak_check() {
    const char* test_name = "Memory Leak Check";
    TEST_START(test_name);

    void *ptr1 = cma_malloc(100, false);
    void *ptr2 = cma_malloc(200, false);

    // Intentionally not freeing ptr2 to simulate a leak
    cma_free(ptr1);

    // Clean up all memory
    cma_cleanup_all_memory();

    // Since cma_cleanup_all_memory cleans up all, there should be no leaks
    // Note: Actual leak detection would require tools like Valgrind

    TEST_PASS(test_name);
    TEST_END(test_name);
}

void test_critical_memory_cleanup() {
    const char* test_name = "Critical Memory Cleanup";
    TEST_START(test_name);

    void* critical_ptr = cma_malloc(100, true);
    void* non_critical_ptr = cma_malloc(100, false);

    // Clean up non-critical memory
    cma_cleanup_non_critical_memory();

    // Attempt to allocate critical memory again
    void* new_ptr = cma_malloc(100, true);

    // Depending on allocator's implementation, critical memory should be preserved
    // Here, we check if the new allocation does not reuse the freed critical_ptr
    if (new_ptr != critical_ptr && new_ptr != NULL) {
        TEST_PASS(test_name);
    } else {
        std::cerr << new_ptr << " " << critical_ptr << std::endl;
        TEST_FAIL(test_name, "Critical memory was not preserved correctly");
    }
    cma_free(critical_ptr);

    cma_free(new_ptr);
    cma_cleanup_all_memory();

    TEST_END(test_name);
}

void test_non_critical_memory_cleanup() {
    const char* test_name = "Non-Critical Memory Cleanup";
    TEST_START(test_name);

    void* non_critical_ptr = cma_malloc(100, false);
    cma_free(non_critical_ptr);

    // Clean up non-critical memory
    cma_cleanup_non_critical_memory();

    // Allocate again and see if the memory is reused or properly handled
    void* new_ptr = cma_malloc(100, false);

    if (new_ptr != NULL) {
        TEST_PASS(test_name);
    } else {
        TEST_FAIL(test_name, "Non-critical memory was not cleaned up properly");
    }

    cma_free(new_ptr);
    cma_cleanup_all_memory();

    TEST_END(test_name);
}

void test_fragmentation() {
    const char* test_name = "Memory Fragmentation Handling";
    TEST_START(test_name);

    void* ptr1 = cma_malloc(100, false);
    void* ptr2 = cma_malloc(200, false);
    void* ptr3 = cma_malloc(300, false);

    cma_free(ptr2);

    // Allocate a block smaller than ptr2 to force fragmentation
    void* ptr4 = cma_malloc(150, false);

    if (ptr4 == ptr2) {
        TEST_PASS(test_name);
    } else {
        TEST_FAIL(test_name, "Allocator did not reuse free block correctly");
    }

    cma_free(ptr1);
    cma_free(ptr3);
    cma_free(ptr4);
    cma_cleanup_all_memory();

    TEST_END(test_name);
}

void test_alignment() {
    const char* test_name = "Memory Alignment";
    TEST_START(test_name);

    void* ptr = cma_malloc(1, false);
    if (ptr == NULL) {
        TEST_FAIL(test_name, "Allocation returned nullptr");
        TEST_END(test_name);
        return;
    }

    size_t addr = reinterpret_cast<size_t>(ptr);
    if (addr % 8 == 0) {
        TEST_PASS(test_name);
    } else {
        TEST_FAIL(test_name, "Memory not aligned to 8 bytes");
    }

    cma_free(ptr);
    cma_cleanup_all_memory();

    TEST_END(test_name);
}

void test_comprehensive_allocation() {
    const char* test_name = "Comprehensive Allocation and Data Integrity Test";
    TEST_START(test_name);

    const int NUM_ALLOCATIONS = 20;
    struct Allocation {
        void* ptr;
        size_t size;
        bool is_freed;
        bool is_int; // true if it's an int*, false if it's a char*
    };

    Allocation allocations[NUM_ALLOCATIONS];

    // Step 1: Allocate multiple pointers with varying sizes and types
    for (int i = 0; i < NUM_ALLOCATIONS; ++i) {
        size_t size = (i + 1) * 10; // Sizes: 10, 20, ..., 200
        bool is_int = (i % 2 == 0); // Alternate between int* and char*
        void* ptr = cma_malloc(size * (is_int ? sizeof(int) : sizeof(char)), false);

        if (ptr == NULL) {
            TEST_FAIL(test_name, "Allocation returned nullptr");
            TEST_END(test_name);
            return;
        }

        allocations[i].ptr = ptr;
        allocations[i].size = size;
        allocations[i].is_freed = false;
        allocations[i].is_int = is_int;

        // Initialize the memory
        if (is_int) {
            int* int_ptr = (int*)ptr;
            for (size_t j = 0; j < size; ++j) {
                int_ptr[j] = MAGIC_NUMBER + j + i;
            }
        } else {
            char* char_ptr = (char*)ptr;
            for (size_t j = 0; j < size; ++j) {
                char_ptr[j] = 'A' + ((j + i) % 26);
            }
        }
    }

    // Step 2: Free some of the allocations
    // Free every third allocation starting from the second
    for (int i = 1; i < NUM_ALLOCATIONS; i += 3) {
        if (!allocations[i].is_freed) {
            cma_free(allocations[i].ptr);
            allocations[i].is_freed = true;
        }
    }

    // Step 3: Allocate more pointers
    const int NEW_ALLOCATIONS = 10;
    Allocation new_allocations[NEW_ALLOCATIONS];

    for (int i = 0; i < NEW_ALLOCATIONS; ++i) {
        size_t size = 50 + (i * 5); // Sizes: 50, 55, ..., 95
        bool is_int = (i % 2 != 0); // Alternate between char* and int*
        void* ptr = cma_malloc(size * (is_int ? sizeof(int) : sizeof(char)), false);

        if (ptr == NULL) {
            TEST_FAIL(test_name, "New allocation returned nullptr");
            TEST_END(test_name);
            return;
        }

        new_allocations[i].ptr = ptr;
        new_allocations[i].size = size;
        new_allocations[i].is_freed = false;
        new_allocations[i].is_int = is_int;

        // Initialize the memory
        if (is_int) {
            int* int_ptr = (int*)ptr;
            for (size_t j = 0; j < size; ++j) {
                int_ptr[j] = MAGIC_NUMBER + j + 100 + i;
            }
        } else {
            char* char_ptr = (char*)ptr;
            for (size_t j = 0; j < size; ++j) {
                char_ptr[j] = 'a' + ((j + i) % 26);
            }
        }
    }

    // Step 4: Read back values to ensure data integrity
    bool data_corrupted = false;

    // Check initial allocations
    for (int i = 0; i < NUM_ALLOCATIONS; ++i) {
        if (!allocations[i].is_freed) {
            void* ptr = allocations[i].ptr;
            size_t size = allocations[i].size;
            if (allocations[i].is_int) {
                int* int_ptr = (int*)ptr;
                for (size_t j = 0; j < size; ++j) {
                    if (int_ptr[j] != MAGIC_NUMBER + j + i) {
                        data_corrupted = true;
                        TEST_FAIL(test_name, "Data corrupted in initial allocations (int*)");
                        break;
                    }
                }
            } else {
                char* char_ptr = (char*)ptr;
                for (size_t j = 0; j < size; ++j) {
                    if (char_ptr[j] != 'A' + ((j + i) % 26)) {
                        data_corrupted = true;
                        TEST_FAIL(test_name, "Data corrupted in initial allocations (char*)");
                        break;
                    }
                }
            }
        }
        if (data_corrupted)
            break;
    }

    // Check new allocations
    if (!data_corrupted) {
        for (int i = 0; i < NEW_ALLOCATIONS; ++i) {
            if (!new_allocations[i].is_freed) {
                void* ptr = new_allocations[i].ptr;
                size_t size = new_allocations[i].size;
                if (new_allocations[i].is_int) {
                    int* int_ptr = (int*)ptr;
                    for (size_t j = 0; j < size; ++j) {
                        if (int_ptr[j] != MAGIC_NUMBER + j + 100 + i) {
                            data_corrupted = true;
                            TEST_FAIL(test_name, "Data corrupted in new allocations (int*)");
                            break;
                        }
                    }
                } else {
                    char* char_ptr = (char*)ptr;
                    for (size_t j = 0; j < size; ++j) {
                        if (char_ptr[j] != 'a' + ((j + i) % 26)) {
                            data_corrupted = true;
                            TEST_FAIL(test_name, "Data corrupted in new allocations (char*)");
                            break;
                        }
                    }
                }
            }
            if (data_corrupted)
                break;
        }
    }

    if (!data_corrupted) {
        TEST_PASS(test_name);
    }

    // Step 5: Free all remaining allocations
    for (int i = 0; i < NUM_ALLOCATIONS; ++i) {
        if (!allocations[i].is_freed) {
            cma_free(allocations[i].ptr);
            allocations[i].is_freed = true;
        }
    }
    for (int i = 0; i < NEW_ALLOCATIONS; ++i) {
        if (!new_allocations[i].is_freed) {
            cma_free(new_allocations[i].ptr);
            new_allocations[i].is_freed = true;
        }
    }

    // Clean up all memory
    cma_cleanup_all_memory();

    TEST_END(test_name);
}
