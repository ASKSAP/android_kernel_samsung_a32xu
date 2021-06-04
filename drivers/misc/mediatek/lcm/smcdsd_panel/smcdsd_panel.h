/* SPDX-License-Identifier: GPL-2.0 */
/*
 * Copyright (c) Samsung Electronics Co., Ltd.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */

#ifndef __SMCDSD_PANEL_H__
#define __SMCDSD_PANEL_H__

#include "smcdsd_abd.h"

struct LCM_PARAMS;

enum CMDQ_DISP_MODE {
	CMDQ_PRIMARY_DISPLAY = 0,
	CMDQ_MASK_BRIGHTNESS = 1,
};

struct mipi_dsi_lcd_common {
	struct platform_device		*pdev;
	struct mipi_dsi_lcd_driver	*drv;
	unsigned int			probe;
	unsigned int			power;
	unsigned int			lcdconnected;
	unsigned int			data_rate[4];

	int (*tx)(void *drvdata, unsigned int id, unsigned long data0, unsigned int data1, bool need_lock);
	int (*rx)(void *drvdata, unsigned int id, unsigned int offset, u8 cmd, unsigned int len, u8 *buf, bool need_lock);

	// add from jihoonn.kim in samsung because ALPS05482657
	int (*tx_with_framedone)(void *drvdata, unsigned int id, unsigned long data0, unsigned int data1, bool need_lock, bool wait_framedone);
	int (*rx_with_framedone)(void *drvdata, unsigned int id, unsigned int offset, u8 cmd, unsigned int len, u8 *buf, bool need_lock, bool wait_framedone);

	struct abd_protect		abd;

	struct LCM_PARAMS		*lcm_params;

	// add samsung for finger print
	bool			mask_wait;
	bool			set_mask_state;
	bool			get_mask_state;
	void			*mask_qhandle;
	int 			cmdq_index;

	bool			lcm_path_lock;;
};

struct mipi_dsi_lcd_driver {
	struct platform_device	*pdev;
	struct device_driver	driver;
	int	(*match)(void *maybe_unused);
	int	(*probe)(struct platform_device *p);
	int	(*init)(struct platform_device *p);
	int	(*exit)(struct platform_device *p);
	int	(*panel_reset)(struct platform_device *p, unsigned int on);
	int	(*panel_power)(struct platform_device *p, unsigned int on);
	int	(*displayon_late)(struct platform_device *p);
	int	(*dump)(struct platform_device *p);
#if defined(CONFIG_SMCDSD_DOZE)
#if defined(CONFIG_SMCDSD_DOZE_USE_NEEDLOCK)
	int	(*doze_init)(struct platform_device *p, unsigned int on, bool need_lock);
#else
	int	(*doze_init)(struct platform_device *p, unsigned int on);
#endif
#endif
	int	(*set_fps)(struct platform_device *p, int to_level);
	int (*set_mask)(struct platform_device *pdev, int on);
	int (*get_mask)(struct platform_device *pdev);
	int	(*lock)(struct platform_device *pdev);				// add samsung
	int	(*framedone_notify)(struct platform_device *pdev);
};

extern struct mipi_dsi_lcd_common *g_lcd_common;
extern unsigned int lcdtype;
extern unsigned char rx_offset;
extern unsigned char data_type;
extern unsigned int islcmconnected;

static inline struct mipi_dsi_lcd_common *get_lcd_common(u32 id)
{
	return g_lcd_common;
}

#define call_drv_ops(x, op, args...)				\
	(((x) && ((x)->drv) && ((x)->drv->op) && ((x)->drv->pdev)) ? ((x)->drv->op((x)->drv->pdev, ##args)) : 0)

#define __XX_ADD_LCD_DRIVER(name)		\
struct mipi_dsi_lcd_driver *p_##name __attribute__((used, section("__lcd_driver"))) = &name;	\
static struct mipi_dsi_lcd_driver __maybe_unused *this_driver = &name	\

extern struct mipi_dsi_lcd_driver *__start___lcd_driver;
extern struct mipi_dsi_lcd_driver *__stop___lcd_driver;
extern struct mipi_dsi_lcd_driver *mipi_lcd_driver;

extern int lcd_driver_init(void);

extern int smcdsd_panel_get_params_from_dt(struct LCM_PARAMS *lcm_params);
extern int smcdsd_panel_dsi_command_tx(void *drvdata,
	unsigned int id, unsigned long data0, unsigned int data1, bool need_lock);
extern int smcdsd_panel_dsi_command_rx(void *drvdata,
	unsigned int id, unsigned int offset, u8 cmd, unsigned int len, u8 *buf, bool need_lock);

extern int smcdsd_panel_dsi_command_tx_with_framedone(void *drvdata,
	unsigned int id, unsigned long data0, unsigned int data1, bool need_lock, bool wait_framedone);
extern int smcdsd_panel_dsi_command_rx_with_framedone(void *drvdata,
	unsigned int id, unsigned int offset, u8 cmd, unsigned int len, u8 *buf, bool need_lock, bool wait_framedone);

#endif
