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
#include "primary_display.h"
#include "disp_drv_log.h"
#include "ddp_dsi.h"

void set_lcm(struct LCM_setting_table_V3 *para_tbl,
			unsigned int size, bool hs, bool need_lock)
{
	DISPFUNC();

	if (need_lock) {
		_primary_path_switch_dst_lock();
		primary_display_manual_lock();
	}
	primary_display_idlemgr_kick(__func__, 0);

	if (_is_power_on_status(DISP_MODULE_DSI0))
		DSI_dcs_set_lcm_reg_v4(DISP_MODULE_DSI0, hs, para_tbl, size, 1);
	else
		DISPERR("%s invalid: dsi is power off\n", __func__);

	if (need_lock) {
		primary_display_manual_unlock();
		_primary_path_switch_dst_unlock();
	}
}

int read_lcm(unsigned char cmd, unsigned char *buf,
			unsigned char buf_size, bool sendhs, bool need_lock,
			unsigned char offset)
{
	int ret = 0;

	DISPFUNC();
	if (need_lock) {
		_primary_path_switch_dst_lock();
		primary_display_manual_lock();
	}
	primary_display_idlemgr_kick(__func__, 0);

	if (_is_power_on_status(DISP_MODULE_DSI0))
		ret = DSI_dcs_read_lcm_reg_v4(DISP_MODULE_DSI0,
					cmd, buf, buf_size, sendhs, offset);
	else
		DISPERR("%s invalid: dsi is power off\n", __func__);

	if (need_lock) {
		primary_display_manual_unlock();
		_primary_path_switch_dst_unlock();
	}

	return ret;
}

#if defined(CONFIG_SMCDSD_PANEL)
// add from jihoonn.kim in samsung because ALPS05482657
void set_lcm_with_check_framedone(struct LCM_setting_table_V3 *para_tbl,
			unsigned int size, bool hs, bool need_lock, bool wait_framedone)
{
	DISPFUNC();

	if (need_lock) {
		_primary_path_switch_dst_lock();
		primary_display_manual_lock();
	}
	primary_display_idlemgr_kick(__func__, 0);

	if (_is_power_on_status(DISP_MODULE_DSI0)) {
		if (wait_framedone)
			DSI_dcs_set_lcm_reg_v4(DISP_MODULE_DSI0, hs, para_tbl, size, 1);
		else
			DSI_dcs_set_lcm_reg_v4_without_framedone(DISP_MODULE_DSI0, hs, para_tbl, size, 1);
	} else {
		DISPERR("%s invalid: dsi is power off\n", __func__);
	}
	if (need_lock) {
		primary_display_manual_unlock();
		_primary_path_switch_dst_unlock();
	}
}

// it is same(read_lcm)
int read_lcm_with_check_framedone(unsigned char cmd, unsigned char *buf,
			unsigned char buf_size, bool sendhs, bool need_lock,
			unsigned char offset, bool wait_framedone)
{
	int ret = 0;

	DISPFUNC();
	if (need_lock) {
		_primary_path_switch_dst_lock();
		primary_display_manual_lock();
	}
	primary_display_idlemgr_kick(__func__, 0);

	if (_is_power_on_status(DISP_MODULE_DSI0)) {
		ret = DSI_dcs_read_lcm_reg_v4(DISP_MODULE_DSI0,
					cmd, buf, buf_size, sendhs, offset);
	} else {
		DISPERR("%s invalid: dsi is power off\n", __func__);
	}

	if (need_lock) {
		primary_display_manual_unlock();
		_primary_path_switch_dst_unlock();
	}

	return ret;
}
#endif
