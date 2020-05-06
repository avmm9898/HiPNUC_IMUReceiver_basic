#ifndef __IMU_DATA_DECODE_H__
#define __IMU_DATA_DECODE_H__

#include <stdint.h>
#include <stdbool.h>
#define MAX_LENGTH 16

extern uint32_t frame_count;
extern uint8_t bitmap;

#define BIT_VALID_ID   (0)
#define BIT_VALID_ACC  (1)
#define BIT_VALID_GYR  (2)
#define BIT_VALID_MAG  (3)
#define BIT_VALID_EUL  (4)
#define BIT_VALID_QUAT (5)
#define BIT_VALID_ALL  (0x3F)

typedef struct receive_imusol_packet_t{
	uint8_t tag;
	uint8_t id;
	float acc[3];
	float gyr[3];
	float mag[3];
	float eul[3];
	float quat[4];

}receive_imusol_packet_t;

typedef struct receive_gwsol_packet_t{
	uint8_t tag;
	uint8_t gw_id;
	uint8_t n;
	receive_imusol_packet_t receive_imusol[MAX_LENGTH];
}receive_gwsol_packet_t;
	 
extern receive_imusol_packet_t receive_imusol;
extern receive_gwsol_packet_t receive_gwsol;

typedef enum 
{
    kItemID =                   0x90,   /* user programed ID   */
    kItemAccRaw =               0xA0,   /* raw acc             */
    kItemGyrRaw =               0xB0,   /* raw gyro            */  
    kItemMagRaw =               0xC0,   /* raw mag             */
    kItemRotationEul =          0xD0,   /* eular angle         */
    kItemRotationQuat =         0xD1,   /* att q               */
    kItemPressure =             0xF0,   /* pressure            */
    kItemEnd =                  0x00,   
	KItemIMUSOL =               0x91,   /* IMUSOL  */
	KItemGWSOL =                0x62,   /* RFSOL  */
}ItemID_t;

int imu_data_decode_init(void);

#endif

 
