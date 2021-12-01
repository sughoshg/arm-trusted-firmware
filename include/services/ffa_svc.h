/*
 * Copyright (c) 2020-2022, Arm Limited. All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef FFA_SVC_H
#define FFA_SVC_H

#include <stdbool.h>

#include <lib/smccc.h>
#include <lib/utils_def.h>
#include <tools_share/uuid.h>

/* FFA error codes. */
#define FFA_ERROR_NOT_SUPPORTED		-1
#define FFA_ERROR_INVALID_PARAMETER	-2
#define FFA_ERROR_NO_MEMORY		-3
#define FFA_ERROR_BUSY			-4
#define FFA_ERROR_INTERRUPTED		-5
#define FFA_ERROR_DENIED		-6
#define FFA_ERROR_RETRY			-7

/* The macros below are used to identify FFA calls from the SMC function ID */
#define FFA_FNUM_MIN_VALUE	U(0x60)
#define FFA_FNUM_MAX_VALUE	U(0x87)
#define is_ffa_fid(fid) __extension__ ({		\
	__typeof__(fid) _fid = (fid);			\
	((GET_SMC_NUM(_fid) >= FFA_FNUM_MIN_VALUE) &&	\
	 (GET_SMC_NUM(_fid) <= FFA_FNUM_MAX_VALUE)); })

/* FFA_VERSION helpers */
#define FFA_VERSION_MAJOR		U(1)
#define FFA_VERSION_MAJOR_SHIFT		16
#define FFA_VERSION_MAJOR_MASK		U(0x7FFF)
#define FFA_VERSION_MINOR		U(1)
#define FFA_VERSION_MINOR_SHIFT		0
#define FFA_VERSION_MINOR_MASK		U(0xFFFF)
#define FFA_VERSION_BIT31_MASK 		U(0x1u << 31)


#define MAKE_FFA_VERSION(major, minor) 	\
	((((major) & FFA_VERSION_MAJOR_MASK) <<  FFA_VERSION_MAJOR_SHIFT) | \
	 (((minor) & FFA_VERSION_MINOR_MASK) << FFA_VERSION_MINOR_SHIFT))
#define FFA_VERSION_COMPILED		MAKE_FFA_VERSION(FFA_VERSION_MAJOR, \
							  FFA_VERSION_MINOR)

/* FFA_MSG_SEND helpers */
#define FFA_MSG_SEND_ATTRS_BLK_SHIFT	U(0)
#define FFA_MSG_SEND_ATTRS_BLK_MASK	U(0x1)
#define FFA_MSG_SEND_ATTRS_BLK		U(0)
#define FFA_MSG_SEND_ATTRS_BLK_NOT	U(1)
#define FFA_MSG_SEND_ATTRS(blk)		\
	(((blk) & FFA_MSG_SEND_ATTRS_BLK_MASK) \
	<< FFA_MSG_SEND_ATTRS_BLK_SHIFT)

/* Get FFA fastcall std FID from function number */
#define FFA_FID(smc_cc, func_num)			\
		((SMC_TYPE_FAST << FUNCID_TYPE_SHIFT) |	\
		 ((smc_cc) << FUNCID_CC_SHIFT) |	\
		 (OEN_STD_START << FUNCID_OEN_SHIFT) |	\
		 ((func_num) << FUNCID_NUM_SHIFT))

/* FFA function numbers */
#define FFA_FNUM_ERROR				U(0x60)
#define FFA_FNUM_SUCCESS			U(0x61)
#define FFA_FNUM_INTERRUPT			U(0x62)
#define FFA_FNUM_VERSION			U(0x63)
#define FFA_FNUM_FEATURES			U(0x64)
#define FFA_FNUM_RX_RELEASE			U(0x65)
#define FFA_FNUM_RXTX_MAP			U(0x66)
#define FFA_FNUM_RXTX_UNMAP			U(0x67)
#define FFA_FNUM_PARTITION_INFO_GET		U(0x68)
#define FFA_FNUM_ID_GET				U(0x69)
#define FFA_FNUM_MSG_POLL			U(0x6A) /* Legacy FF-A v1.0 */
#define FFA_FNUM_MSG_WAIT			U(0x6B)
#define FFA_FNUM_MSG_YIELD			U(0x6C)
#define FFA_FNUM_MSG_RUN			U(0x6D)
#define FFA_FNUM_MSG_SEND			U(0x6E) /* Legacy FF-A v1.0 */
#define FFA_FNUM_MSG_SEND_DIRECT_REQ		U(0x6F)
#define FFA_FNUM_MSG_SEND_DIRECT_RESP		U(0x70)
#define FFA_FNUM_MEM_DONATE			U(0x71)
#define FFA_FNUM_MEM_LEND			U(0x72)
#define FFA_FNUM_MEM_SHARE			U(0x73)
#define FFA_FNUM_MEM_RETRIEVE_REQ		U(0x74)
#define FFA_FNUM_MEM_RETRIEVE_RESP		U(0x75)
#define FFA_FNUM_MEM_RELINQUISH			U(0x76)
#define FFA_FNUM_MEM_RECLAIM			U(0x77)
#define FFA_FNUM_NORMAL_WORLD_RESUME		U(0x7C)

/* FF-A v1.1 */
#define FFA_FNUM_NOTIFICATION_BITMAP_CREATE	U(0x7D)
#define FFA_FNUM_NOTIFICATION_BITMAP_DESTROY	U(0x7E)
#define FFA_FNUM_NOTIFICATION_BIND		U(0x7F)
#define FFA_FNUM_NOTIFICATION_UNBIND		U(0x80)
#define FFA_FNUM_NOTIFICATION_SET		U(0x81)
#define FFA_FNUM_NOTIFICATION_GET		U(0x82)
#define FFA_FNUM_NOTIFICATION_INFO_GET		U(0x83)
#define FFA_FNUM_RX_ACQUIRE			U(0x84)
#define FFA_FNUM_SPM_ID_GET			U(0x85)
#define FFA_FNUM_MSG_SEND2			U(0x86)
#define FFA_FNUM_SECONDARY_EP_REGISTER		U(0x87)

/* FFA SMC32 FIDs */
#define FFA_ERROR		FFA_FID(SMC_32, FFA_FNUM_ERROR)
#define FFA_SUCCESS_SMC32	FFA_FID(SMC_32, FFA_FNUM_SUCCESS)
#define FFA_INTERRUPT		FFA_FID(SMC_32, FFA_FNUM_INTERRUPT)
#define FFA_VERSION		FFA_FID(SMC_32, FFA_FNUM_VERSION)
#define FFA_FEATURES		FFA_FID(SMC_32, FFA_FNUM_FEATURES)
#define FFA_RX_RELEASE		FFA_FID(SMC_32, FFA_FNUM_RX_RELEASE)
#define FFA_RXTX_MAP_SMC32	FFA_FID(SMC_32, FFA_FNUM_RXTX_MAP)
#define FFA_RXTX_UNMAP		FFA_FID(SMC_32, FFA_FNUM_RXTX_UNMAP)
#define FFA_PARTITION_INFO_GET	FFA_FID(SMC_32, FFA_FNUM_PARTITION_INFO_GET)
#define FFA_ID_GET		FFA_FID(SMC_32, FFA_FNUM_ID_GET)
#define FFA_MSG_POLL		FFA_FID(SMC_32, FFA_FNUM_MSG_POLL)
#define FFA_MSG_WAIT		FFA_FID(SMC_32, FFA_FNUM_MSG_WAIT)
#define FFA_MSG_YIELD		FFA_FID(SMC_32, FFA_FNUM_MSG_YIELD)
#define FFA_MSG_RUN		FFA_FID(SMC_32, FFA_FNUM_MSG_RUN)
#define FFA_MSG_SEND		FFA_FID(SMC_32, FFA_FNUM_MSG_SEND)
#define FFA_MSG_SEND2		FFA_FID(SMC_32, FFA_FNUM_MSG_SEND2)
#define FFA_MSG_SEND_DIRECT_REQ_SMC32 \
	FFA_FID(SMC_32, FFA_FNUM_MSG_SEND_DIRECT_REQ)
#define FFA_MSG_SEND_DIRECT_RESP_SMC32	\
	FFA_FID(SMC_32, FFA_FNUM_MSG_SEND_DIRECT_RESP)
#define FFA_MEM_DONATE_SMC32	FFA_FID(SMC_32, FFA_FNUM_MEM_DONATE)
#define FFA_MEM_LEND_SMC32	FFA_FID(SMC_32, FFA_FNUM_MEM_LEND)
#define FFA_MEM_SHARE_SMC32	FFA_FID(SMC_32, FFA_FNUM_MEM_SHARE)
#define FFA_MEM_RETRIEVE_REQ_SMC32 \
	FFA_FID(SMC_32, FFA_FNUM_MEM_RETRIEVE_REQ)
#define FFA_MEM_RETRIEVE_RESP	FFA_FID(SMC_32, FFA_FNUM_MEM_RETRIEVE_RESP)
#define FFA_MEM_RELINQUISH	FFA_FID(SMC_32, FFA_FNUM_MEM_RELINQUISH)
#define FFA_MEM_RECLAIM	FFA_FID(SMC_32, FFA_FNUM_MEM_RECLAIM)
#define FFA_NOTIFICATION_BITMAP_CREATE	\
	FFA_FID(SMC_32, FFA_FNUM_NOTIFICATION_BITMAP_CREATE)
#define FFA_NOTIFICATION_BITMAP_DESTROY	\
	FFA_FID(SMC_32, FFA_FNUM_NOTIFICATION_BITMAP_DESTROY)
#define FFA_NOTIFICATION_BIND	FFA_FID(SMC_32, FFA_FNUM_NOTIFICATION_BIND)
#define FFA_NOTIFICATION_UNBIND FFA_FID(SMC_32, FFA_FNUM_NOTIFICATION_UNBIND)
#define FFA_NOTIFICATION_SET 	FFA_FID(SMC_32, FFA_FNUM_NOTIFICATION_SET)
#define FFA_NOTIFICATION_GET 	FFA_FID(SMC_32, FFA_FNUM_NOTIFICATION_GET)
#define FFA_NOTIFICATION_INFO_GET \
	FFA_FID(SMC_32, FFA_FNUM_NOTIFICATION_INFO_GET)
#define FFA_SPM_ID_GET		FFA_FID(SMC_32, FFA_FNUM_SPM_ID_GET)
#define FFA_NORMAL_WORLD_RESUME	FFA_FID(SMC_32, FFA_FNUM_NORMAL_WORLD_RESUME)

/* FFA SMC64 FIDs */
#define FFA_ERROR_SMC64		FFA_FID(SMC_64, FFA_FNUM_ERROR)
#define FFA_SUCCESS_SMC64	FFA_FID(SMC_64, FFA_FNUM_SUCCESS)
#define FFA_RXTX_MAP_SMC64	FFA_FID(SMC_64, FFA_FNUM_RXTX_MAP)
#define FFA_MSG_SEND_DIRECT_REQ_SMC64 \
	FFA_FID(SMC_64, FFA_FNUM_MSG_SEND_DIRECT_REQ)
#define FFA_MSG_SEND_DIRECT_RESP_SMC64	\
	FFA_FID(SMC_64, FFA_FNUM_MSG_SEND_DIRECT_RESP)
#define FFA_MEM_DONATE_SMC64	FFA_FID(SMC_64, FFA_FNUM_MEM_DONATE)
#define FFA_MEM_LEND_SMC64	FFA_FID(SMC_64, FFA_FNUM_MEM_LEND)
#define FFA_MEM_SHARE_SMC64	FFA_FID(SMC_64, FFA_FNUM_MEM_SHARE)
#define FFA_MEM_RETRIEVE_REQ_SMC64 \
	FFA_FID(SMC_64, FFA_FNUM_MEM_RETRIEVE_REQ)
#define FFA_SECONDARY_EP_REGISTER_SMC64 \
	FFA_FID(SMC_64, FFA_FNUM_SECONDARY_EP_REGISTER)
#define FFA_NOTIFICATION_INFO_GET_SMC64 \
	FFA_FID(SMC_64, FFA_FNUM_NOTIFICATION_INFO_GET)

/*
 * Reserve a special value for traffic targeted to the Hypervisor or SPM.
 */
#define FFA_TARGET_INFO_MBZ		U(0x0)

/*
 * Reserve a special value for MBZ parameters.
 */
#define FFA_PARAM_MBZ			U(0x0)

/*
 * Maximum FF-A endpoint id value
 */
#define FFA_ENDPOINT_ID_MAX			U(1 << 16)

/*
 * Reserve endpoint id for the SPMD.
 */
#define SPMD_DIRECT_MSG_ENDPOINT_ID		U(FFA_ENDPOINT_ID_MAX - 1)

/* Mask and shift to check valid secure FF-A Endpoint ID. */
#define SPMC_SECURE_ID_MASK			U(1)
#define SPMC_SECURE_ID_SHIFT			U(15)

/*
 * Mask for source and destination endpoint id in
 * a direct message request/response.
 */
#define FFA_DIRECT_MSG_ENDPOINT_ID_MASK		U(0xffff)

/*
 * Bit shift for destination endpoint id in a direct message request/response.
 */
#define FFA_DIRECT_MSG_DESTINATION_SHIFT	U(0)

/*
 * Bit shift for source endpoint id in a direct message request/response.
 */
#define FFA_DIRECT_MSG_SOURCE_SHIFT		U(16)

/******************************************************************************
 * ffa_endpoint_destination
 *****************************************************************************/
static inline uint16_t ffa_endpoint_destination(unsigned int ep)
{
	return (ep >> FFA_DIRECT_MSG_DESTINATION_SHIFT) &
		FFA_DIRECT_MSG_ENDPOINT_ID_MASK;
}

/******************************************************************************
 * ffa_endpoint_source
 *****************************************************************************/
static inline uint16_t ffa_endpoint_source(unsigned int ep)
{
	return (ep >> FFA_DIRECT_MSG_SOURCE_SHIFT) &
		FFA_DIRECT_MSG_ENDPOINT_ID_MASK;
}

/******************************************************************************
 * FF-A helper functions to determine partition ID world.
 *****************************************************************************/

/*
 * Determine if provided ID is in the secure world.
 */
static inline bool ffa_is_secure_world_id(uint16_t id)
{
	return ((id >> SPMC_SECURE_ID_SHIFT) & SPMC_SECURE_ID_MASK) == 1;
}

/*
 * Determine if provided ID is in the normal world.
 */
static inline bool ffa_is_normal_world_id(uint16_t id)
{
	return !ffa_is_secure_world_id(id);
}

#endif /* FFA_SVC_H */
