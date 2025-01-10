/**
  ******************************************************************************
  * @file    imx335_reg.h
  * @author  MCD Application Team
  * @brief   Header of imx335_reg.c
  *
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2022 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef IMX335_REG_H
#define IMX335_REG_H

#include <cmsis_compiler.h>

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
/** @addtogroup BSP
  * @{
  */

/** @addtogroup Components
  * @{
  */

/** @addtogroup IMX335
  * @{
  */

/** @defgroup IMX335_Exported_Types
  * @{
  */

/**
  * @}
  */

/** @defgroup IMX335_Exported_Constants IMX335 Exported Constants
  * @{
  */
#define IMX335_REG_MODE_SELECT    0x3000
#define IMX335_MODE_STREAMING       0x00
#define IMX335_MODE_STANDBY         0x01

#define IMX335_REG_HOLD           0x3001
#define IMX335_REG_LPFR           0x3030
#define IMX335_REG_SHUTTER        0x3058
#define IMX335_REG_AGAIN          0x30e8

#define IMX335_REG_ID             0x3912
#define IMX335_CHIP_ID            0x00

#define IMX335_EXPOSURE_MIN       1
#define IMX335_EXPOSURE_OFFSET    9
#define IMX335_EXPOSURE_DEFAULT   0x648

#define IMX335_AGAIN_MIN          0
#define IMX335_AGAIN_MAX          240
 /* TODO: Value quite arbitrary */
#define IMX335_AGAIN_DEFAULT      (IMX335_AGAIN_MAX / 8)

/* For 2592x1940 */
#define IMX335_WIDTH              2592
#define IMX335_HEIGHT             1940
#define IMX335_VBLANK_MIN         2560
#define IMX335_VBLANK_MAX         133060
#define IMX335_VBLANK_DEF         IMX335_VBLANK_MIN
#define IMX335_PCLK               396000000

/**
  * @}
  */

/************** Generic Function  *******************/

typedef int32_t (*IMX335_Write_Func)(void *, uint16_t, uint8_t*, uint16_t);
typedef int32_t (*IMX335_Read_Func) (void *, uint16_t, uint8_t*, uint16_t);

typedef struct
{
  IMX335_Write_Func   WriteReg;
  IMX335_Read_Func    ReadReg;
  void                *handle;
} imx335_ctx_t;

/*******************************************************************************
* Register      : Generic - All
* Address       : Generic - All
* Bit Group Name: None
* Permission    : W
*******************************************************************************/
int32_t imx335_write_reg(imx335_ctx_t *ctx, uint16_t reg, uint8_t *pdata, uint16_t length);
int32_t imx335_read_reg(imx335_ctx_t *ctx, uint16_t reg, uint8_t *pdata, uint16_t length);

int32_t imx335_register_set(imx335_ctx_t *ctx, uint16_t reg, uint8_t value);


/**
  * @}
  */
#ifdef __cplusplus
}
#endif

#endif /* IMX335_REG_H */
/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
