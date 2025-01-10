/**
  ******************************************************************************
  * @file    imx335.h
  * @author  MCD Application Team
  * @brief   This file contains all the functions prototypes for the imx335.c
  *          driver.
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
#ifndef IMX335_H
#define IMX335_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "imx335_reg.h"
#include <stddef.h>

/** @addtogroup BSP
  * @{
  */

/** @addtogroup Components
  * @{
  */

/** @addtogroup imx335
  * @{
  */

/** @defgroup IMX335_Exported_Types
  * @{
  */

typedef int32_t (*IMX335_Init_Func)    (void);
typedef int32_t (*IMX335_DeInit_Func)  (void);
typedef int32_t (*IMX335_GetTick_Func) (void);
typedef int32_t (*IMX335_Delay_Func)   (uint32_t);
typedef int32_t (*IMX335_WriteReg_Func)(uint16_t, uint16_t, uint8_t*, uint16_t);
typedef int32_t (*IMX335_ReadReg_Func) (uint16_t, uint16_t, uint8_t*, uint16_t);

typedef struct
{
  IMX335_Init_Func          Init;
  IMX335_DeInit_Func        DeInit;
  uint16_t                  Address;
  IMX335_WriteReg_Func      WriteReg;
  IMX335_ReadReg_Func       ReadReg;
  IMX335_GetTick_Func       GetTick;
} IMX335_IO_t;

typedef struct
{
  IMX335_IO_t         IO;
  imx335_ctx_t        Ctx;
  uint8_t             IsInitialized;
} IMX335_Object_t;

typedef struct
{
  uint32_t Config_Resolution;
  uint32_t Config_LightMode;
  uint32_t Config_SpecialEffect;
  uint32_t Config_Brightness;
  uint32_t Config_Saturation;
  uint32_t Config_Contrast;
  uint32_t Config_HueDegree;
  uint32_t Config_MirrorFlip;
  uint32_t Config_Zoom;
  uint32_t Config_NightMode;
} IMX335_Capabilities_t;

typedef struct
{
  int32_t  (*Init              )(IMX335_Object_t*, uint32_t, uint32_t);
  int32_t  (*DeInit            )(IMX335_Object_t*);
  int32_t  (*ReadID            )(IMX335_Object_t*, uint32_t*);
  int32_t  (*GetCapabilities   )(IMX335_Object_t*, IMX335_Capabilities_t*);
  int32_t  (*SetLightMode      )(IMX335_Object_t*, uint32_t);
  int32_t  (*SetColorEffect    )(IMX335_Object_t*, uint32_t);
  int32_t  (*SetBrightness     )(IMX335_Object_t*, int32_t);
  int32_t  (*SetSaturation     )(IMX335_Object_t*, int32_t);
  int32_t  (*SetContrast       )(IMX335_Object_t*, int32_t);
  int32_t  (*SetHueDegree      )(IMX335_Object_t*, int32_t);
  int32_t  (*MirrorFlipConfig  )(IMX335_Object_t*, uint32_t);
  int32_t  (*ZoomConfig        )(IMX335_Object_t*, uint32_t);
  int32_t  (*SetResolution     )(IMX335_Object_t*, uint32_t);
  int32_t  (*GetResolution     )(IMX335_Object_t*, uint32_t*);
  int32_t  (*SetPixelFormat    )(IMX335_Object_t*, uint32_t);
  int32_t  (*GetPixelFormat    )(IMX335_Object_t*, uint32_t*);
  int32_t  (*NightModeConfig   )(IMX335_Object_t*, uint32_t);
}IMX335_CAMERA_Drv_t;
/**
  * @}
  */

/** @defgroup IMX335_Exported_Constants
  * @{
  */
#define IMX335_OK                      (0)
#define IMX335_ERROR                   (-1)
/**
 * @brief  IMX335 Features Parameters
 */
/* Camera resolutions */
#define IMX335_R2592_1940               10U	/* 2592x1940 Resolution       */

/* Camera Pixel Format */
#define IMX335_RAW_RGGB10               10U    /* Pixel Format RAW_RGGB10    */

/**
  * @}
  */

/** @defgroup IMX335_Exported_Functions IMX335 Exported Functions
  * @{
  */
int32_t IMX335_RegisterBusIO(IMX335_Object_t *pObj, IMX335_IO_t *pIO);
int32_t IMX335_Init(IMX335_Object_t *pObj, uint32_t Resolution, uint32_t PixelFormat);
int32_t IMX335_DeInit(IMX335_Object_t *pObj);
int32_t IMX335_ReadID(IMX335_Object_t *pObj, uint32_t *Id);
int32_t IMX335_GetCapabilities(IMX335_Object_t *pObj, IMX335_Capabilities_t *Capabilities);
int32_t IMX335_Set_Exposure_Gain(IMX335_Object_t *pObj, uint32_t exposure, uint32_t gain);

/* CAMERA driver structure */
extern IMX335_CAMERA_Drv_t   IMX335_CAMERA_Driver;
/**
  * @}
  */
#ifdef __cplusplus
}
#endif

#endif
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
