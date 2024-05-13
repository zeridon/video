#pragma once

#include "tusb.h"
#include "config.h"

#define USB_ENABLED (USB_INSTANCE >= 0)

void usb_init(void);
void usb_task(void);
