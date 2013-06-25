/** @file
  Coreboot PEI module include file.

  Copyright (c) 2013, Google Inc. All rights reserved.<BR>
  This program and the accompanying materials
  are licensed and made available under the terms and conditions of the BSD License
  which accompanies this distribution.  The full text of the license may be found at
  http://opensource.org/licenses/bsd-license.php

  THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
  WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.

**/

#ifndef _COREBOOT_PEI_H_INCLUDED_
#define _COREBOOT_PEI_H_INCLUDED_

struct cbuint64 {
  UINT32 lo;
  UINT32 hi;
};

struct cb_header {
  UINT32 signature;
  UINT32 header_bytes;
  UINT32 header_checksum;
  UINT32 table_bytes;
  UINT32 table_checksum;
  UINT32 table_entries;
};

struct cb_record {
  UINT32 tag;
  UINT32 size;
};

#define CB_TAG_UNUSED     0x0000
#define CB_TAG_MEMORY     0x0001

struct cb_memory_range {
  struct cbuint64 start;
  struct cbuint64 size;
  UINT32 type;
};

#define CB_MEM_RAM    1
#define CB_MEM_RESERVED     2
#define CB_MEM_ACPI   3
#define CB_MEM_NVS    4
#define CB_MEM_UNUSABLE     5
#define CB_MEM_VENDOR_RSVD  6
#define CB_MEM_TABLE       16

struct cb_memory {
  UINT32 tag;
  UINT32 size;
  struct cb_memory_range map[0];
};

#define CB_TAG_MAINBOARD  0x0003

struct cb_mainboard {
  UINT32 tag;
  UINT32 size;
  UINT8 vendor_idx;
  UINT8 part_number_idx;
  UINT8 strings[0];
};
#define CB_TAG_VERSION  0x0004
#define CB_TAG_EXTRA_VERSION  0x0005
#define CB_TAG_BUILD    0x0006
#define CB_TAG_COMPILE_TIME   0x0007
#define CB_TAG_COMPILE_BY     0x0008
#define CB_TAG_COMPILE_HOST   0x0009
#define CB_TAG_COMPILE_DOMAIN 0x000a
#define CB_TAG_COMPILER       0x000b
#define CB_TAG_LINKER   0x000c
#define CB_TAG_ASSEMBLER      0x000d

struct cb_string {
  UINT32 tag;
  UINT32 size;
  UINT8 string[0];
};

#define CB_TAG_SERIAL   0x000f

struct cb_serial {
  UINT32 tag;
  UINT32 size;
#define CB_SERIAL_TYPE_IO_MAPPED     1
#define CB_SERIAL_TYPE_MEMORY_MAPPED 2
  UINT32 type;
  UINT32 baseaddr;
  UINT32 baud;
};

#define CB_TAG_CONSOLE       0x00010

struct cb_console {
  UINT32 tag;
  UINT32 size;
  UINT16 type;
};

#define CB_TAG_CONSOLE_SERIAL8250 0
#define CB_TAG_CONSOLE_VGA  1 // OBSOLETE
#define CB_TAG_CONSOLE_BTEXT      2 // OBSOLETE
#define CB_TAG_CONSOLE_LOGBUF     3
#define CB_TAG_CONSOLE_SROM       4 // OBSOLETE
#define CB_TAG_CONSOLE_EHCI       5

#define CB_TAG_FORWARD       0x00011

struct cb_forward {
  UINT32 tag;
  UINT32 size;
  UINT64 forward;
};

#define CB_TAG_FRAMEBUFFER      0x0012
struct cb_framebuffer {
  UINT32 tag;
  UINT32 size;

  UINT64 physical_address;
  UINT32 x_resolution;
  UINT32 y_resolution;
  UINT32 bytes_per_line;
  UINT8 bits_per_pixel;
  UINT8 red_mask_pos;
  UINT8 red_mask_size;
  UINT8 green_mask_pos;
  UINT8 green_mask_size;
  UINT8 blue_mask_pos;
  UINT8 blue_mask_size;
  UINT8 reserved_mask_pos;
  UINT8 reserved_mask_size;
};

#define CB_TAG_VDAT     0x0015
struct cb_vdat {
  UINT32 tag;
  UINT32 size;  /* size of the entire entry */
  UINT64 vdat_addr;
  UINT32 vdat_size;
};

#define CB_TAG_TIMESTAMPS       0x0016
#define CB_TAG_CBMEM_CONSOLE    0x0017
#define CB_TAG_MRC_CACHE  0x0018
struct cb_cbmem_tab {
  UINT32 tag;
  UINT32 size;
  UINT64 cbmem_tab;
};

/* Helpful inlines */

static inline UINT64 cb_unpack64(struct cbuint64 val)
{
  return (((UINT64) val.hi) << 32) | val.lo;
}

static inline const char *cb_mb_vendor_string(const struct cb_mainboard *cbm)
{
  return (char *)(cbm->strings + cbm->vendor_idx);
}

static inline const char *cb_mb_part_string(const struct cb_mainboard *cbm)
{
  return (char *)(cbm->strings + cbm->part_number_idx);
}

/* Helpful macros */

#define MEM_RANGE_COUNT(_rec) \
  (((_rec)->size - sizeof(*(_rec))) / sizeof((_rec)->map[0]))

#define MEM_RANGE_PTR(_rec, _idx) \
  (void *)(((UINT8 *) (_rec)) + sizeof(*(_rec)) \
    + (sizeof((_rec)->map[0]) * (_idx)))


VOID
FindCorebootTable (
  VOID
  );

#endif // _COREBOOT_PEI_H_INCLUDED_
