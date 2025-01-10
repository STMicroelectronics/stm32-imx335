/**
  ******************************************************************************
  * @file    imx335.c
  * @author  MCD Application Team
  * @brief   This file provides the IMX335 camera driver
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

/* Includes ------------------------------------------------------------------*/
#include "imx335.h"

/** @addtogroup BSP
  * @{
  */

/** @addtogroup Components
  * @{
  */

/** @addtogroup IMX335
  * @brief     This file provides a set of functions needed to drive the
  *            IMX335 Camera module.
  * @{
  */

/** @defgroup IMX335_Private_TypesDefinitions Private Types definition
  * @{
  */
#define ARRAY_SIZE(arr) (sizeof(arr) / sizeof((arr)[0]))

/**
  * @}
  */

/** @defgroup IMX335_Private_Variables Private Variables
  * @{
  */
IMX335_CAMERA_Drv_t   IMX335_CAMERA_Driver =
{
  .Init = IMX335_Init,
  .DeInit = IMX335_DeInit,
  .ReadID = IMX335_ReadID,
  .GetCapabilities = IMX335_GetCapabilities,
};
/**
  * @}
  */

/** @defgroup IMX335_Private_Constants Private Constants
  * @{
  */
struct regval {
  uint16_t addr;
  uint8_t val;
};

static const struct regval res_2592_1940_regs[] = {
  {0x3000, 0x01},
  {0x3002, 0x00},
  {0x300c, 0x3b},
  {0x300d, 0x2a},
  {0x3018, 0x04},
  {0x302c, 0x3c},
  {0x302e, 0x20},
  {0x3056, 0x94},
  {0x3074, 0xc8},
  {0x3076, 0x28},
  {0x304c, 0x00},
  {0x314c, 0xc6},
  {0x315a, 0x02},
  {0x3168, 0xa0},
  {0x316a, 0x7e},
  {0x31a1, 0x00},
  {0x3288, 0x21},
  {0x328a, 0x02},
  {0x3414, 0x05},
  {0x3416, 0x18},
  {0x3648, 0x01},
  {0x364a, 0x04},
  {0x364c, 0x04},
  {0x3678, 0x01},
  {0x367c, 0x31},
  {0x367e, 0x31},
  {0x3706, 0x10},
  {0x3708, 0x03},
  {0x3714, 0x02},
  {0x3715, 0x02},
  {0x3716, 0x01},
  {0x3717, 0x03},
  {0x371c, 0x3d},
  {0x371d, 0x3f},
  {0x372c, 0x00},
  {0x372d, 0x00},
  {0x372e, 0x46},
  {0x372f, 0x00},
  {0x3730, 0x89},
  {0x3731, 0x00},
  {0x3732, 0x08},
  {0x3733, 0x01},
  {0x3734, 0xfe},
  {0x3735, 0x05},
  {0x3740, 0x02},
  {0x375d, 0x00},
  {0x375e, 0x00},
  {0x375f, 0x11},
  {0x3760, 0x01},
  {0x3768, 0x1b},
  {0x3769, 0x1b},
  {0x376a, 0x1b},
  {0x376b, 0x1b},
  {0x376c, 0x1a},
  {0x376d, 0x17},
  {0x376e, 0x0f},
  {0x3776, 0x00},
  {0x3777, 0x00},
  {0x3778, 0x46},
  {0x3779, 0x00},
  {0x377a, 0x89},
  {0x377b, 0x00},
  {0x377c, 0x08},
  {0x377d, 0x01},
  {0x377e, 0x23},
  {0x377f, 0x02},
  {0x3780, 0xd9},
  {0x3781, 0x03},
  {0x3782, 0xf5},
  {0x3783, 0x06},
  {0x3784, 0xa5},
  {0x3788, 0x0f},
  {0x378a, 0xd9},
  {0x378b, 0x03},
  {0x378c, 0xeb},
  {0x378d, 0x05},
  {0x378e, 0x87},
  {0x378f, 0x06},
  {0x3790, 0xf5},
  {0x3792, 0x43},
  {0x3794, 0x7a},
  {0x3796, 0xa1},
  {0x37b0, 0x36},
  {0x3a00, 0x01},
};

static const struct regval mode_2l_10b_regs[] = {
  {0x3050, 0x00},
  {0x319D, 0x00},
  {0x341c, 0xff},
  {0x341d, 0x01},
  {0x3a01, 0x01},
};
/**
  * @}
  */

/** @defgroup IMX335_Private_Functions_Prototypes Private Functions Prototypes
  * @{
  */
static int32_t IMX335_WriteTable(IMX335_Object_t *pObj, const struct regval *regs, uint32_t size);
static int32_t IMX335_ReadRegWrap(void *handle, uint16_t Reg, uint8_t* Data, uint16_t Length);
static int32_t IMX335_WriteRegWrap(void *handle, uint16_t Reg, uint8_t* Data, uint16_t Length);
static int32_t IMX335_Delay(IMX335_Object_t *pObj, uint32_t Delay);

/**
  * @}
  */

/** @defgroup IMX335_Private_Functions Private Functions
  * @{
  */
static int32_t IMX335_WriteTable(IMX335_Object_t *pObj, const struct regval *regs, uint32_t size)
{
  uint32_t index;
  int32_t ret = IMX335_OK;

  /* Set registers */
  for(index=0; index<size ; index++)
  {
    if(ret != IMX335_ERROR)
    {
      if(imx335_write_reg(&pObj->Ctx, regs[index].addr, (uint8_t *)&(regs[index].val), 1) != IMX335_OK)
      {
        ret = IMX335_ERROR;
      }
    }
  }
  return ret;
}

/**
  * @brief This function provides accurate delay (in milliseconds)
  * @param pObj   pointer to component object
  * @param Delay  specifies the delay time length, in milliseconds
  * @retval IMX335_OK
  */
static int32_t IMX335_Delay(IMX335_Object_t *pObj, uint32_t Delay)
{
  uint32_t tickstart;
  tickstart = pObj->IO.GetTick();
  while((pObj->IO.GetTick() - tickstart) < Delay)
  {
  }
  return IMX335_OK;
}

/**
  * @brief  Wrap component ReadReg to Bus Read function
  * @param  handle  Component object handle
  * @param  Reg  The target register address to write
  * @param  pData  The target register value to be written
  * @param  Length  buffer size to be written
  * @retval error status
  */
static int32_t IMX335_ReadRegWrap(void *handle, uint16_t Reg, uint8_t* pData, uint16_t Length)
{
  IMX335_Object_t *pObj = (IMX335_Object_t *)handle;

  return pObj->IO.ReadReg(pObj->IO.Address, Reg, pData, Length);
}

/**
  * @brief  Wrap component WriteReg to Bus Write function
  * @param  handle  Component object handle
  * @param  Reg  The target register address to write
  * @param  pData  The target register value to be written
  * @param  Length  buffer size to be written
  * @retval error status
  */
static int32_t IMX335_WriteRegWrap(void *handle, uint16_t Reg, uint8_t* pData, uint16_t Length)
{
  IMX335_Object_t *pObj = (IMX335_Object_t *)handle;

  return pObj->IO.WriteReg(pObj->IO.Address, Reg, pData, Length);
}

/**
  * @}
  */

/** @defgroup IMX335_Exported_Functions IMX335 Exported Functions
  * @{
  */
/**
  * @brief  Register component IO bus
  * @param  Component object pointer
  * @retval Component status
  */
int32_t IMX335_RegisterBusIO(IMX335_Object_t *pObj, IMX335_IO_t *pIO)
{
  int32_t ret;

  if (pObj == NULL)
  {
    ret = IMX335_ERROR;
  }
  else
  {
    pObj->IO.Init      = pIO->Init;
    pObj->IO.DeInit    = pIO->DeInit;
    pObj->IO.Address   = pIO->Address;
    pObj->IO.WriteReg  = pIO->WriteReg;
    pObj->IO.ReadReg   = pIO->ReadReg;
    pObj->IO.GetTick   = pIO->GetTick;

    pObj->Ctx.ReadReg  = IMX335_ReadRegWrap;
    pObj->Ctx.WriteReg = IMX335_WriteRegWrap;
    pObj->Ctx.handle   = pObj;

    if(pObj->IO.Init != NULL)
    {
      ret = pObj->IO.Init();
    }
    else
    {
      ret = IMX335_ERROR;
    }
  }

  return ret;
}

/**
  * @brief  Initialize the exposure and gain
  * @param  pObj  pointer to component object
  * @param  Exposure  Exposure value
  * @param  Gain Gain value
  * @retval Component status
  */
int32_t IMX335_Set_Exposure_Gain(IMX335_Object_t *pObj, uint32_t exposure, uint32_t gain)
{
  int32_t ret = IMX335_OK;
  uint8_t tmp;
  uint32_t lpfr, shutter;

  /*
   * Hardcoded for the time being since VBLANK can't be changed and
   * there is only 1 resolution
   */
  lpfr = IMX335_VBLANK_DEF + IMX335_HEIGHT;

  if ((exposure > lpfr - IMX335_EXPOSURE_OFFSET) ||
      (gain > IMX335_AGAIN_MAX))
  {
    ret = IMX335_ERROR;
  }
  else
  {
    shutter = lpfr - exposure;

    tmp = 1;
    if(imx335_write_reg(&pObj->Ctx, IMX335_REG_HOLD, &tmp, 1) != IMX335_OK)
    {
      ret = IMX335_ERROR;
    }
    else
    {
      if(imx335_write_reg(&pObj->Ctx, IMX335_REG_LPFR, (uint8_t *)&lpfr, 3) != IMX335_OK)
      {
        ret = IMX335_ERROR;
      }
      else
      {
        if(imx335_write_reg(&pObj->Ctx, IMX335_REG_SHUTTER, (uint8_t *)&shutter, 3) != IMX335_OK)
        {
          ret = IMX335_ERROR;
        }
	else
	{
          if(imx335_write_reg(&pObj->Ctx, IMX335_REG_AGAIN, (uint8_t *)&gain, 2) != IMX335_OK)
          {
            ret = IMX335_ERROR;
          }
	}
      }
    } 
  }

  return ret;
}

/**
  * @brief  Initializes the IMX335 CAMERA component.
  * @param  pObj  pointer to component object
  * @param  Resolution  Camera resolution
  * @param  PixelFormat pixel format to be configured
  * @retval Component status
  */
int32_t IMX335_Init(IMX335_Object_t *pObj, uint32_t Resolution, uint32_t PixelFormat)
{
  int32_t ret = IMX335_OK;
  uint8_t tmp;

  if(pObj->IsInitialized == 0U)
  {
    /* Check if resolution is supported */
    if(Resolution != IMX335_R2592_1940)
    {
      ret = IMX335_ERROR;
    }
    else
    {
      if(IMX335_WriteTable(pObj, res_2592_1940_regs, ARRAY_SIZE(res_2592_1940_regs)) != IMX335_OK)
      {
          ret = IMX335_ERROR;
      }
      else
      {
        if(IMX335_WriteTable(pObj, mode_2l_10b_regs, ARRAY_SIZE(mode_2l_10b_regs)) != IMX335_OK)
        {
            ret = IMX335_ERROR;
        }
        else
        {
          if (IMX335_Set_Exposure_Gain(pObj, IMX335_EXPOSURE_DEFAULT, IMX335_AGAIN_DEFAULT) != IMX335_OK)
          {
            ret = IMX335_ERROR;
          }
	  else
	  {
            /* Start streaming */
            tmp = IMX335_MODE_STREAMING;
            if(imx335_write_reg(&pObj->Ctx, IMX335_REG_MODE_SELECT, &tmp, 1) != IMX335_OK)
            {
              ret = IMX335_ERROR;
            }
            else
            {
              IMX335_Delay(pObj, 20);
              pObj->IsInitialized = 1U;
            }
          }
        }
      }
    }
  }

  return ret;
}

/**
  * @brief  De-initializes the camera sensor.
  * @param  pObj  pointer to component object
  * @retval Component status
  */
int32_t IMX335_DeInit(IMX335_Object_t *pObj)
{
  if(pObj->IsInitialized == 1U)
  {
    /* De-initialize camera sensor interface */
    pObj->IsInitialized = 0U;
  }

  return IMX335_OK;
}

/**
  * @brief  Read the IMX335 Camera identity.
  * @param  pObj  pointer to component object
  * @param  Id    pointer to component ID
  * @retval Component status
  */
int32_t IMX335_ReadID(IMX335_Object_t *pObj, uint32_t *Id)
{
  int32_t ret;
  uint8_t tmp;

  /* Initialize I2C */
  pObj->IO.Init();

  if(imx335_read_reg(&pObj->Ctx, IMX335_REG_ID, &tmp, 1)!= IMX335_OK)
  {
    ret = IMX335_ERROR;
  }
  else
  {
    *Id = tmp;
    ret = IMX335_OK;
  }

  /* Component status */
  return ret;
}

/**
  * @brief  Read the IMX335 Camera Capabilities.
  * @param  pObj          pointer to component object
  * @param  Capabilities  pointer to component Capabilities
  * @retval Component status
  */
int32_t IMX335_GetCapabilities(IMX335_Object_t *pObj, IMX335_Capabilities_t *Capabilities)
{
  int32_t ret;

  if(pObj == NULL)
  {
    ret = IMX335_ERROR;
  }
  else
  {
    Capabilities->Config_Brightness    = 0;
    Capabilities->Config_Contrast      = 0;
    Capabilities->Config_HueDegree     = 0;
    Capabilities->Config_LightMode     = 0;
    Capabilities->Config_MirrorFlip    = 0;
    Capabilities->Config_NightMode     = 0;
    Capabilities->Config_Resolution    = 0;
    Capabilities->Config_Saturation    = 0;
    Capabilities->Config_SpecialEffect = 0;
    Capabilities->Config_Zoom          = 0;

    ret = IMX335_OK;
  }

  return ret;
}

/**
  * @}
  */

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
