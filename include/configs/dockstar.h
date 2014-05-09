/*
 * Copyright (C) 2010  Eric C. Cooper <ecc@cmu.edu>
 *
 * Based on sheevaplug.h originally written by
 * Prafulla Wadaskar <prafulla@marvell.com>
 * (C) Copyright 2009
 * Marvell Semiconductor <www.marvell.com>
 *
 * SPDX-License-Identifier:	GPL-2.0+
 */

#ifndef _CONFIG_DOCKSTAR_H
#define _CONFIG_DOCKSTAR_H

/*
 * Version number information
 */
#define CONFIG_IDENT_STRING	" Arch Linux ARM\nSeagate FreeAgent DockStar"

/*
 * High Level Configuration Options (easy to change)
 */
#define CONFIG_FEROCEON_88FR131	1	/* CPU Core subversion */
#define CONFIG_KIRKWOOD		1	/* SOC Family Name */
#define CONFIG_KW88F6281	1	/* SOC Name */
#define CONFIG_MACH_DOCKSTAR	/* Machine type */
#define CONFIG_SKIP_LOWLEVEL_INIT	/* disable board lowlevel_init */
#define CONFIG_LOADADDR		0x800000

/*
 * Commands configuration
 */
#define CONFIG_SYS_NO_FLASH		/* Declare no flash (NOR/SPI) */
#include <config_cmd_default.h>
#define CONFIG_CMD_DHCP
#define CONFIG_CMD_ENV
#define CONFIG_CMD_MII
#define CONFIG_CMD_NAND
#define CONFIG_CMD_PING
#define CONFIG_CMD_USB
#define CONFIG_CMD_BOOTZ
#define CONFIG_SUPPORT_RAW_INITRD

/*
 * mv-common.h should be defined after CMD configs since it used them
 * to enable certain macros
 */
#include "mv-common.h"

#undef CONFIG_SYS_PROMPT	/* previously defined in mv-common.h */
#define CONFIG_SYS_PROMPT	"DockStar> "	/* Command Prompt */
#define CONFIG_SYS_HUSH_PARSER
#define CONFIG_SYS_PROMPT_HUSH_PS2 "> "

/*
 *  Environment variables configurations
 */
#ifdef CONFIG_CMD_NAND
#define CONFIG_ENV_IS_IN_NAND		1
#define CONFIG_ENV_SECT_SIZE		0x20000	/* 128K */
#else
#define CONFIG_ENV_IS_NOWHERE		1	/* if env in SDRAM */
#endif
/*
 * max 4k env size is enough, but in case of nand
 * it has to be rounded to sector size
 */
#define CONFIG_ENV_SIZE			0x20000	/* 128k */
#define CONFIG_ENV_ADDR			0x60000
#define CONFIG_ENV_OFFSET		0x60000	/* env starts here */

/*
 * Default environment variables
 */
#define CONFIG_MTDPARTS		"mtdparts=orion_nand:1M(u-boot),4M(uImage),32M(rootfs),-(data)\0"

#define CONFIG_EXTRA_ENV_SETTINGS \
	"console=console=ttyS0,115200\0" \
	"mtdids=nand0=orion_nand\0" \
	"mtdparts="CONFIG_MTDPARTS \
	"zimage=/boot/zImage\0" \
	"uimage=/boot/uImage\0" \
	"fdt_file=/boot/dtbs/kirkwood-dockstar.dtb\0" \
	"fdt_addr=0x1400000\0" \
	"usbdev=0\0" \
	"usbpart=1\0" \
	"usbroot=/dev/sda1 rw rootwait\0" \
	"usbargs=setenv bootargs console=${console} " \
		"${optargs} " \
		"root=${usbroot} " \
		"${mtdparts}\0" \
	"loadbootenv=load usb ${usbdev}:${usbpart} ${loadaddr} /boot/uEnv.txt\0" \
	"importbootenv=echo Importing environment from mmc (uEnv.txt)...; " \
		"env import -t $loadaddr $filesize\0" \
	"loaduimage=load usb ${usbdev}:${usbpart} ${loadaddr} ${uimage}\0" \
	"loadzimage=load usb ${usbdev}:${usbpart} ${loadaddr} ${zimage}\0" \
	"loadfdt=load usb ${usbdev}:${usbpart} ${fdt_addr} ${fdt_file}\0" \
	"usbbootz=echo Booting from USB ...; " \
		"run usbargs; " \
		"bootz ${loadaddr} - ${fdt_addr};\0" \
	"usbbootm=echo Booting from USB ...; " \
		"run usbargs; " \
		"bootm ${loadaddr};\0"

#define CONFIG_BOOTCOMMAND \
	"usb start;" \
	"if run loadbootenv; then " \
		"run importbootenv;" \
	"fi;" \
	"echo Checking if uenvcmd is set ...;" \
	"if test -n $uenvcmd; then " \
		"echo Running uenvcmd ...;" \
		"run uenvcmd;" \
	"fi;" \
	"echo Running default loadzimage ...;" \
	"if run loadzimage; then " \
		"run loadfdt;" \
		"run mmcbootz;" \
	"fi;" \
	"echo Running default loaduimage ...;" \
	"if run loaduimage; then " \
		"run mmcbootm;" \
	"fi;\0"

/*
 * Ethernet Driver configuration
 */
#ifdef CONFIG_CMD_NET
#define CONFIG_MVGBE_PORTS	{1, 0}	/* enable port 0 only */
#define CONFIG_PHY_BASE_ADR	0
#endif /* CONFIG_CMD_NET */

/*
 * File system
 */
#define CONFIG_CMD_EXT2
#define CONFIG_CMD_FAT
#define CONFIG_CMD_EXT4
#define CONFIG_CMD_FS_GENERIC
#define CONFIG_CMD_JFFS2
#define CONFIG_JFFS2_NAND
#define CONFIG_JFFS2_LZO
#define CONFIG_CMD_UBI
#define CONFIG_CMD_UBIFS
#define CONFIG_RBTREE
#define CONFIG_MTD_DEVICE               /* needed for mtdparts commands */
#define CONFIG_MTD_PARTITIONS
#define CONFIG_CMD_MTDPARTS
#define CONFIG_LZO
#define CONFIG_EFI_PARTITION
#define CONFIG_OF_LIBFDT

#endif /* _CONFIG_DOCKSTAR_H */
