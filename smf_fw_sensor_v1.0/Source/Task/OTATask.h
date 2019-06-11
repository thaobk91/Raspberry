/*
 * OTATask.h
 *
 *  Created on: Jun 5, 2019
 *      Author: Thao
 */

#ifndef TASK_OTATASK_H_
#define TASK_OTATASK_H_


typedef enum
{
	OTA_STOP = 0,
	OTA_START,
	OTA_RECV_FW,
	OTA_REV_DONE,
	OTA_UPGRADE,
}OTA_State_t;


/******************************************************************************
 * Function		: void OTATask( void const *arg )
 * Description	: OTA task
 * Param		: None
 * Return		: None
 * ***************************************************************************/
void OTATask( void const *arg );


#endif /* TASK_OTATASK_H_ */
