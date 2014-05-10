/*
 * Copyright (C) 2013 Suriyan Ramasami <suriyan.r@gmail.com>
 *
 * Based on dockstar.h originally written by
 * Copyright (C) 2010  Eric C. Cooper <ecc@cmu.edu>
 *
 * Based on sheevaplug.h originally written by
 * Prafulla Wadaskar <prafulla@marvell.com>
 * (C) Copyright 2009
 * Marvell Semiconductor <www.marvell.com>
 *
 * SPDX-License-Identifier:	GPL-2.0+
 */

#ifndef _CONFIG_GOFLEXHOME_H
#define _CONFIG_GOFLEXHOME_H

/*
 * Version number information
 */
#define CONFIG_IDENT_STRING	" Arch Linux ARM\nSeagate GoFlex Home"

/*
 * High Level Configuration Options (easy to change)
 */
#define CONFIG_FEROCEON_88FR131	1	/* CPU Core subversion */
#define CONFIG_KIRKWOOD		1	/* SOC Family Name */
#define CONFIG_KW88F6281	1	/* SOC Name */
#define CONFIG_MACH_GOFLEXHOME		/* Machine type */
#define CONFIG_SKIP_LOWLEVEL_INIT	/* disable board lowlevel_init */

/*
 * Default GPIO configuration and LED status
 */
#define GOFLEXHOME_OE_LOW               (~(0))
#define GOFLEXHOME_OE_HIGH              (~(0))
#define GOFLEXHOME_OE_VAL_LOW           (1 << 29)       /* USB_PWEN low */
#define GOFLEXHOME_OE_VAL_HIGH          (1 << 17)       /* LED pin high */

/* PHY related */
#define MV88E1116_LED_FCTRL_REG         10
#define MV88E1116_CPRSP_CR3_REG         21
#define MV88E1116_MAC_CTRL_REG          21
#define MV88E1116_PGADR_REG             22
#define MV88E1116_RGMII_TXTM_CTRL       (1 << 4)
#define MV88E1116_RGMII_RXTM_CTRL       (1 << 5)

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
#define CONFIG_CMD_IDE
#define CONFIG_CMD_DATE
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
#define CONFIG_SYS_PROMPT	"GoFlexHome> "	/* Command Prompt */
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
#define CONFIG_ENV_ADDR			0xC0000
#define CONFIG_ENV_OFFSET		0xC0000	/* env starts here */
#define CONFIG_LOADADDR			0x810000

/*
 * Default environment variables
 */
#define CONFIG_MTDPARTS \
	"mtdparts=orion_nand:1M(u-boot),128k(fdt),8M(uImage),-(rootfs)\0"

#define CONFIG_EXTRA_ENV_SETTINGS \
	"console=ttyS0\0" \
	"mtdids=nand0=orion_nand\0" \
	"mtdparts="CONFIG_MTDPARTS \
	"zimage=/boot/zImage\0" \
	"uimage=/boot/uImage\0" \
	"fdt_file=/boot/dtbs/kirkwood-goflexnet.dtb\0" \
	"fdt_addr=0x800000\0" \
	"usbdev=0\0" \
	"usbpart=1\0" \
	"usbroot=/dev/sda1 rw rootwait\0" \
	"usbargs=setenv bootargs console=${console},${baudrate} " \
		"${optargs} " \
		"root=${usbroot} " \
		"${mtdparts}\0" \
	"loadbootenv=load usb ${usbdev}:${usbpart} ${loadaddr} /boot/uEnv.txt\0" \
	"importbootenv=echo Importing environment from USB (uEnv.txt)...; " \
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
		"run usbbootz;" \
	"fi;" \
	"echo Running default loaduimage ...;" \
	"if run loaduimage; then " \
		"run usbbootm;" \
	"fi;"

/*
 * Ethernet Driver configuration
 */
#ifdef CONFIG_CMD_NET
#define CONFIG_MVGBE_PORTS	{1, 0}	/* enable port 0 only */
#define CONFIG_PHY_BASE_ADR	0
#endif /* CONFIG_CMD_NET */

/*
 * SATA Driver configuration
 */
#ifdef CONFIG_MVSATA_IDE
#define CONFIG_SYS_ATA_IDE0_OFFSET      MV_SATA_PORT0_OFFSET
#endif /*CONFIG_MVSATA_IDE*/

/*
 * RTC driver configuration
 */
#ifdef CONFIG_CMD_DATE
#define CONFIG_RTC_MV
#define CONFIG_CMD_SNTP
#define CONFIG_CMD_DNS
#endif /* CONFIG_CMD_DATE */

#endif /* _CONFIG_GOFLEXHOME_H */
