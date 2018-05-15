#ifndef HAL_CONFIG_H
#define HAL_CONFIG_H

#include "board_features.h"
#include "hal-config-board.h"
#include "hal-config-app-common.h"

#define HAL_VCOM_ENABLE                   (0)
#define HAL_I2CSENSOR_ENABLE              (0)
#define HAL_SPIDISPLAY_ENABLE                         (1)
#define HAL_SPIDISPLAY_EXTCOMIN_CALLBACK
#if defined(FEATURE_IOEXPANDER)
#define HAL_SPIDISPLAY_EXTMODE_EXTCOMIN               (0)
#else
#define HAL_SPIDISPLAY_EXTMODE_EXTCOMIN               (1)
#endif
#define HAL_SPIDISPLAY_EXTMODE_SPI                    (0)
#define HAL_SPIDISPLAY_EXTCOMIN_USE_PRS               (0)
#define HAL_SPIDISPLAY_EXTCOMIN_USE_CALLBACK          (0)
#define HAL_SPIDISPLAY_FREQUENCY                      (1000000)
#endif
