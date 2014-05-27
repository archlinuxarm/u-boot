/*
 * Copyright (C) 2012
 * David Purdy <david.c.purdy@gmail.com>
 *
 * Based on Kirkwood support:
 * (C) Copyright 2009
 * Marvell Semiconductor <www.marvell.com>
 * Written-by: Prafulla Wadaskar <prafulla@marvell.com>
 *
 * SPDX-License-Identifier:	GPL-2.0+
 */

#ifndef _CONFIG_POGO_E02_H
#define _CONFIG_POGO_E02_H

/*
 * Machine type definition and ID
 */
#define MACH_TYPE_POGO_E02		3542
#define CONFIG_MACH_TYPE		MACH_TYPE_POGO_E02
#define CONFIG_IDENT_STRING		" Arch Linux ARM\nPogo E02"

/*
 * High Level Configuration Options (easy to change)
 */
#define CONFIG_FEROCEON_88FR131		/* CPU Core subversion */
#define CONFIG_KIRKWOOD			/* SOC Family Name */
#define CONFIG_KW88F6281		/* SOC Name */
#define CONFIG_SKIP_LOWLEVEL_INIT	/* disable board lowlevel_init */

/*
 * Commands configuration
 */
#define CONFIG_SYS_NO_FLASH		/* Declare no flash (NOR/SPI) */
#define CONFIG_CONSOLE_MUX
#define CONFIG_SYS_CONSOLE_IS_IN_ENV

#include <config_cmd_default.h>
#define CONFIG_CMD_DHCP
#define CONFIG_CMD_ENV
#define CONFIG_CMD_MII
#define CONFIG_CMD_NAND
#define CONFIG_CMD_PING
#define CONFIG_CMD_USB
#define CONFIG_SYS_MVFS         /* Picks up Filesystem from mv-common.h */
#define CONFIG_CMD_BOOTZ
#define CONFIG_CMD_SETEXPR
#define CONFIG_SUPPORT_RAW_INITRD
#define CONFIG_OF_LIBFDT

/*
 * mv-common.h should be defined after CMD configs since it used them
 * to enable certain macros
 */
#include "mv-common.h"

#undef CONFIG_SYS_PROMPT	/* previously defined in mv-common.h */
#define CONFIG_SYS_PROMPT	"PogoE02> "	/* Command Prompt */
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

#define CONFIG_ENV_SIZE			0x20000	/* 128k */
#define CONFIG_ENV_ADDR			0xC0000
#define CONFIG_ENV_OFFSET		0xC0000	/* env starts here */
#define CONFIG_LOADADDR			0x810000

/*
 * Default environment variables
 */
#define CONFIG_MTDPARTS \
	"mtdparts=orion_nand:1M(u-boot),-(rootfs)\0"

#define CONFIG_EXTRA_ENV_SETTINGS \
	"console=ttyS0\0" \
	"mtdids=nand0=orion_nand\0" \
	"mtdparts="CONFIG_MTDPARTS \
	"zimage=/boot/zImage\0" \
	"uimage=/boot/uImage\0" \
	"fdt_file=/boot/dtbs/kirkwood-pogo_e02.dtb\0" \
	"fdt_addr=0x800000\0" \
	"setargs=setenv bootargs console=${console},${baudrate} " \
		"${optargs} " \
		"root=/dev/sd${letter}1 rw rootwait " \
		"${mtdparts}\0" \
	"loadbootenv=load ${type} ${disk}:1 ${loadaddr} /boot/uEnv.txt\0" \
	"importbootenv=echo Importing environment (uEnv.txt)...; " \
		"env import -t $loadaddr $filesize\0" \
	"loaduimage=load ${type} ${disk}:1 ${loadaddr} ${uimage}\0" \
	"loadzimage=load ${type} ${disk}:1 ${loadaddr} ${zimage}\0" \
	"loadfdt=load ${type} ${disk}:1 ${fdt_addr} ${fdt_file}\0" \
	"bootz=echo Booting from ${disk} ...; " \
		"run setargs; " \
		"bootz ${loadaddr} - ${fdt_addr};\0" \
	"bootm=echo Booting from ${disk} ...; " \
		"run setargs; " \
		"bootm ${loadaddr};\0" \
	"load=echo Attempting to boot from ${type} ${disk}:1...;" \
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
			"run bootz;" \
		"fi;" \
		"echo Running default loaduimage ...;" \
		"if run loaduimage; then " \
			"run bootm;" \
		"fi;\0"

#define CONFIG_BOOTCOMMAND \
	"usb start; setenv letter 9;" \
	"for type in usb; do " \
		"for disk in 0 1 2 3; do " \
			"if ${type} part ${disk};then " \
				"setexpr letter $letter + 1;" \
				"run load;" \
			"fi;" \
		"done;" \
	"done;"

/*
 * Ethernet Driver configuration
 */
#ifdef CONFIG_CMD_NET
#define CONFIG_MVGBE_PORTS	{1, 0}	/* enable port 0 only */
#define CONFIG_PHY_BASE_ADR	0
#endif /* CONFIG_CMD_NET */

#endif /* _CONFIG_POGO_E02_H */
