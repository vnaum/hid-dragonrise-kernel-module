/*
 *  HID driver for Aureal Cy se W-01RN USB_V3.1 devices
 *
 *  Copyright (c) 2010 Franco Catrin <fcatrin@gmail.com>
 *  Copyright (c) 2010 Ben Cropley <bcropley@internode.on.net>
 *
 *  Based on HID sunplus driver by
 *  Copyright (c) 1999 Andreas Gal
 *  Copyright (c) 2000-2005 Vojtech Pavlik <vojtech@suse.cz>
 *  Copyright (c) 2005 Michael Haboustak <mike-@cinci.rr.com> for Concept2, Inc
 *  Copyright (c) 2006-2007 Jiri Kosina
 *  Copyright (c) 2007 Paul Walmsley
 *  Copyright (c) 2008 Jiri Slaby
 */

/*
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the Free
 * Software Foundation; either version 2 of the License, or (at your option)
 * any later version.
 */

#include <linux/device.h>
#include <linux/hid.h>
#include <linux/module.h>

#include "aureal-id.h"

static void aureal_report_fixup(struct hid_device *hdev, __u8 *rdesc, unsigned int rsize)
{
	printk(KERN_CRIT "QQ: aureal_report_fixup\n");
	dev_info(&hdev->dev, "aureal_report_fixup called, rsize == %d\n", rsize);
	if (rsize >= 54 && rdesc[52] == 0x25 && rdesc[53] == 0x01) {
		dev_info(&hdev->dev, "fixing Aureal Cy se W-01RN USB_V3.1 "
				"report descriptor. Keyboard Logical Maximum = 101\n");
		rdesc[53] = 0x65;
	}
}

static const struct hid_device_id aureal_devices[] = {
	{ HID_USB_DEVICE(USB_VENDOR_ID_AUREAL, USB_DEVICE_ID_AUREAL_W01RN) },
	{ }
};
MODULE_DEVICE_TABLE(hid, aureal_devices);

static struct hid_driver aureal_driver = {
	.name = "aureal",
	.id_table = aureal_devices,
	.report_fixup = aureal_report_fixup,
};

static int __init aureal_init(void)
{
	printk(KERN_CRIT "QQ: aureal_init\n");
	return hid_register_driver(&aureal_driver);
}

static void __exit aureal_exit(void)
{
	hid_unregister_driver(&aureal_driver);
}

module_init(aureal_init);
module_exit(aureal_exit);
MODULE_LICENSE("GPL");
