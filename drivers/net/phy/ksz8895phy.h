/*
 * drivers/net/phy/ksz8895phy.h
 *
 * PHY Driver header file for Micrel KSZ8895 serial switch
 *
 * Copyright (c) 2010 SAGEM Communications.
 *
 * Author: Karl Beldan <karl.beldan@sagemcom.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 *
 */
#ifndef KSZ8873PHY_H
#define KSZ8873PHY_H

#include <linux/mii.h>
#if defined(CONFIG_ARCH_PEGASUS)
#include <mach/platform.h>
#endif

#define KSZ8895_PHY_VER   "1.0.0"

#define KSZ8895_PHY1_ADDR               1
#define KSZ8895_PHY2_ADDR               2
#define KSZ8895_PHY3_ADDR               3
#define KSZ8895_PHY4_ADDR               4

#define KSZ8895_SPI_CMD_READ            0x03
#define KSZ8895_SPI_CMD_WRITE           0x02

#define KSZ8895_FAMILY_ID               0x95
#define KSZ8895_PHYID1                  0x0022
#define KSZ8895_PHYID2                  0x1450
#define KSZ8895_PORTS_REGS_OFFSET       16

#define KSZ8895_PHY1_DFLT_ADDR          1
#define KSZ8895_PHY4_DFLT_ADDR          4

#define KSZ8895_MDIO_MIN                MII_BMCR
#define KSZ8895_MDIO_MAX                MII_LPA

#define KSZ8895_MIDO_BUS                1
#define KSZ8895_SPI_BUS                 2


/* max switch port support logical Network interface */
#if defined (CONFIG_KSPHY_FOR_KSZ8864)
#define KSZ8895_INT_MASK                0x0E
#define KSZ8895_MAX_ETH                 3
#define KSZ8895_ALL_PHY_ADDR            0xE
#else
#define KSZ8895_INT_MASK                0x0f
#define KSZ8895_MAX_ETH                 4
#define KSZ8895_ALL_PHY_ADDR            0xF
#endif

#define KSZ8895_MIM_ETH                 1

#if defined (CONFIG_NET_PEGASUS)
#define KSZ8895_IRQ                     (LOW_IRQS + KS8692_INT_EXT_INT0)
#endif

struct ksz8895_mdio {
    int	phy_addr;
};

struct ksz8895_fns_t {
    int (*read)(struct mii_bus *, int, int);
    int (*write)(struct mii_bus *, int, int, u16);
};

struct ksz8895_io_fns_t {
    int (*nread)(u8, u8 *, int);
    int (*nwrite)(u8, u8 *, int);
    int (*init)(void);
    void (*exit)(void);
};
extern struct ksz8895_io_fns_t *ksz8895_io_fns;


/* enum from sources.blackfin.uclinux.org/net/dsa/ksz8893.h with ksz8863 bits */
enum switch_reg {
    /* Global Registers: 0-15 */
    ChipID0 = 0,
    ChipID1,

    LinkChangeInterrupt = 124,
    InterruptEnable,

};

/* Export functions */
#if defined (CONFIG_NET_PEGASUS)
extern int ksz9692_mdio_read(struct mii_bus *, int, int);
extern int ksz9692_mdio_write(struct mii_bus *, int, int, u16);
extern void ksz9692_mac_adjust_link(struct net_device *);
#endif

#if defined (CONFIG_KSPHY_BUS_SPI)
extern inline int ksz8895_spibus_read(struct mii_bus *, int, int);
extern inline int ksz8895_spibus_write(struct mii_bus *, int, int, u16);
extern int  ksz8895_spibus_mod_init(void);
extern void ksz8895_spibus_mod_exit(void);

extern int  ksz8895_spi_nread(u8, u8 *, int);
extern int  ksz8895_spi_nwrite(u8, u8 *, int);

extern struct spi_device *spi_ksswitch;

#endif

#endif /* KSZ8873PHY_H */
