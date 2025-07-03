// config.h
/* #ifndef CONFIG_H
#define CONFIG_H

#define PAGE_SIZE_4KB (4 * 1024)          // 4KB
#define PAGE_SIZE_2KB (2 * 1024)          // 2KB
#define PAGE_SIZE_1KB (1 * 1024)          // 1KB

#define VIRTUAL_MEMORY_SIZE_4GB (1ULL << 32)  // 4GB
#define VIRTUAL_MEMORY_SIZE_8GB (1ULL << 33)  // 8GB
#define PHYSICAL_MEMORY_SIZE_4GB (1ULL << 32) // 4GB
#define PHYSICAL_MEMORY_SIZE_8GB (1ULL << 33) // 8GB
#define PHYSICAL_MEMORY_SIZE_16GB (1ULL << 34) // 16GB

#define MULTI_LEVEL_TABLE_LEVELS 2       // Example: Two-level page table

#endif // CONFIG_H
 */
#ifndef CONFIG_H
#define CONFIG_H

// Define fixed starting addresses for different sections (in hex)
#define TEXT_SECTION_START 0x400000
#define DATA_SECTION_START 0x600000
#define STACK_SECTION_START 0x800000
#define SHARED_LIB_SECTION_START 0xA00000
#define HEAP_SECTION_START 0xC00000
#define PAGESIZE 1024 
// Define the minimum page size in KB
#define PAGE_SIZE_4KB (4*1024) // 4KB page size
#define PAGE_SIZE_2KB (2*1024) // 2KB page size
#define PAGE_SIZE_1KB (1*1024) // 1KB page size
#define PAGE_SIZE_IN_POWER_OF_2 12 // for 4 KB page size, 2^12 = 4096



// Define memory sizes
#define VIRTUAL_MEMORY_SIZE_4GB (1ULL << 32) // 4GB
#define VIRTUAL_MEMORY_SIZE_8GB (1ULL << 33) // 8GB
#define VIRTUAL_MEMORY_SIZE_16GB (1ULL << 34) // 16GB

#define PHYSICAL_MEMORY_SIZE_4GB (1ULL << 32) // 4GB
#define PHYSICAL_MEMORY_SIZE_8GB (1ULL << 33) // 8GB
#define PHYSICAL_MEMORY_SIZE_16GB (1ULL << 34) // 16GB
#define MULTILEVEL_TABLE_LEVELS 2 // Example: Two-level page table

#endif // CONFIG_H