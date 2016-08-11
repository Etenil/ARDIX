#ifndef PLATFORM_ARDUINO_NANO_H
#define PLATFORM_ARDUINO_NANO_H

/* Memory topology. */


/* SRAM size is 2kB or 2048 */
#define TOTAL_MEMORY 0x800

#define INTERRUPT_START 0x100
#define INTERRUPT_END 0x200

#define KERNEL_START 0x200
#define KERNEL_END 0x300

#define MAIN_MEMORY_START 0x300

/* The arduino nano has 2kB of RAM and we start the main memory at 768B.
 * Therefore we could assign the page size to 5B and still keep track of
 * the count of pages in one byte. Let's choose 8 instead. That means we
 * can allocate 160 pages in memory. */
#define PAGE_SIZE 8

#endif

