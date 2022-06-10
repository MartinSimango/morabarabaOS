#pragma once

#include "types.h"

#define VBE_BLOCK_ADDRESS 0x8000
#define VBE_MODE_INFO_ADDRESS 0x8200

typedef struct _vbeInfoBlock {
  char signature[4];     // “VESA”
  uint16 version;        // Either 0x0200 (VBE 2.0) or 0x0300 (VBE 3.0)
  uint32 oemString;      // Far pointer to OEM name
  uint8 capabilities[4]; // capabilities
  uint32 videoModesPtr;  // Far pointer to video mode list
  uint16 totalMemory;    // Memory size in 64K blocks
  uint16 oemSoftwareRev;
  uint32 oemVenderNamePtr;
  uint32 oemProductNamePtr;
  uint32 oemProductRevPtr;
  uint8 reserved[222];
  uint8 oemData[256];
} __attribute__((packed)) vbeInfoBlock;

typedef struct _vbeModeInfo {
  /*  Mandatory information for all VBE revisions */
  uint16 ModeAttributes; /**< @brief mode attributes */
  uint8 WinAAttributes;  /**< @brief window A attributes */
  uint8 WinBAttributes;  /**< @brief window B attributes */
  uint16 WinGranularity; /**< @brief window granularity */
  uint16 WinSize;        /**< @brief window size */
  uint16 WinASegment;    /**< @brief window A start segment */
  uint16 WinBSegment;    /**< @brief window B start segment */
  uint32 WinFuncPtr;     /**< @brief real mode/far pointer to window function */
  uint16 BytesPerScanLine; /**< @brief bytes per scan line */

  /* Mandatory information for VBE 1.2 and above */

  uint16 XResolution; /**< @brief horizontal resolution in pixels/characters */
  uint16 YResolution; /**< @brief vertical resolution in pixels/characters */
  uint8 XCharSize;    /**< @brief character cell width in pixels */
  uint8 YCharSize;    /**< @brief character cell height in pixels */
  uint8 NumberOfPlanes;     /**< @brief number of memory planes */
  uint8 BitsPerPixel;       /**< @brief bits per pixel */
  uint8 NumberOfBanks;      /**< @brief number of banks */
  uint8 MemoryModel;        /**< @brief memory model type */
  uint8 BankSize;           /**< @brief bank size in KB */
  uint8 NumberOfImagePages; /**< @brief number of images */
  uint8 Reserved_1;         /**< @brief reserved for page function */

  /* Direct Color fields (required for direct/6 and YUV/7 memory models) */

  uint8 RedMaskSize;         /* size of direct color red mask in bits */
  uint8 RedFieldPosition;    /* bit position of lsb of red mask */
  uint8 GreenMaskSize;       /* size of direct color green mask in bits */
  uint8 GreenFieldPosition;  /* bit position of lsb of green mask */
  uint8 BlueMaskSize;        /* size of direct color blue mask in bits */
  uint8 BlueFieldPosition;   /* bit position of lsb of blue mask */
  uint8 RsvdMaskSize;        /* size of direct color reserved mask in bits */
  uint8 RsvdFieldPosition;   /* bit position of lsb of reserved mask */
  uint8 DirectColorModeInfo; /* direct color mode attributes */

  /* Mandatory information for VBE 2.0 and above */
  uint32
      PhysBasePtr; /**< @brief physical address for flat memory frame buffer */
  uint8 Reserved_2[4]; /**< @brief Reserved - always set to 0 */
  uint8 Reserved_3[2]; /**< @brief Reserved - always set to 0 */

  /* Mandatory information for VBE 3.0 and above */
  uint16 LinBytesPerScanLine;  /* bytes per scan line for linear modes */
  uint8 BnkNumberOfImagePages; /* number of images for banked modes */
  uint8 LinNumberOfImagePages; /* number of images for linear modes */
  uint8 LinRedMaskSize; /* size of direct color red mask (linear modes) */
  uint8
      LinRedFieldPosition; /* bit position of lsb of red mask (linear modes) */
  uint8 LinGreenMaskSize;  /* size of direct color green mask (linear modes) */
  uint8 LinGreenFieldPosition; /* bit position of lsb of green mask (linear
                                  modes) */
  uint8 LinBlueMaskSize; /* size of direct color blue mask (linear modes) */
  uint8 LinBlueFieldPosition; /* bit position of lsb of blue mask (linear modes
                                 ) */
  uint8 LinRsvdMaskSize; /* size of direct color reserved mask (linear modes) */
  uint8 LinRsvdFieldPosition; /* bit position of lsb of reserved mask (linear
                                 modes) */
  uint32 MaxPixelClock;  /* maximum pixel clock (in Hz) for graphics mode */
  uint8 Reserved_4[190]; /* remainder of ModeInfoBlock change fromed 189 to 190
                            to make struct 256 bytes*/
} __attribute__((packed)) vbeModeInfo;

static vbeInfoBlock *VBE_INFO_BlOCK = (vbeInfoBlock *)VBE_BLOCK_ADDRESS;

static vbeModeInfo *VBE_MODE_INFO = (vbeModeInfo *)VBE_MODE_INFO_ADDRESS;

#define VBE_BLOCK_SIZE (sizeof(VBE_INFO_BlOCK[0]) + sizeof(VBE_MODE_INFO[0]))
