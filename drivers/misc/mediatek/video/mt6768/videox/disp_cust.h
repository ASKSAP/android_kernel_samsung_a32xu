/*
 * Copyright (C) 2018 MediaTek Inc.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See http://www.gnu.org/licenses/gpl-2.0.html for more details.
 */
#ifndef _DISP_CUST_H_
#define _DISP_CUST_H_

extern void set_lcm(struct LCM_setting_table_V3 *para_tbl,
			unsigned int size, bool hs, bool need_lock);
extern int read_lcm(unsigned char cmd, unsigned char *buf,
		unsigned char buf_size, bool sendhs, bool need_lock,
		unsigned char offset);

#if defined(CONFIG_SMCDSD_PANEL)
// add from jihoonn.kim in samsung because ALPS05482657
extern void set_lcm_with_check_framedone(struct LCM_setting_table_V3 *para_tbl,
			unsigned int size, bool hs, bool need_lock, bool wait_framedone);
extern int read_lcm_with_check_framedone(unsigned char cmd, unsigned char *buf,
		unsigned char buf_size, bool sendhs, bool need_lock,
		unsigned char offset, bool wait_framedone);
#endif
#endif
