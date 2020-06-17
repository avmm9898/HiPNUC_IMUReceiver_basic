#include <string.h>
#include <stdio.h>

#include "packet.h"
#include "imu_data_decode.h"



static packet_t RxPkt; /* used for data receive */
/*
 **采用结构体来保存数据
 **将标志位都集中到一个32位的变量上，用位来表示
 **在复制数据时，在用户程序中直接调用一个memcpu函数
 **
 *
 *
 */

uint8_t bitmap;
uint32_t frame_count;
receive_imusol_packet_t receive_imusol;
receive_gwsol_packet_t receive_gwsol;

static int stream2int16(int *dest,uint8_t *src)
{
	dest[0] = (int16_t)(src[0] | src[1] << 8);
	dest[1] = (int16_t)(src[2] | src[3] << 8);
	dest[2] = (int16_t)(src[4] | src[5] << 8);	
	return 0;
}   


/*  callback function of  when recv a data frame successfully */
static void on_data_received(packet_t *pkt)
{
	int temp[3] = {0};
	int offset = 0;
	uint8_t *p = pkt->buf;


	if(pkt->type != 0xA5)
    {
        return;
    }

	while(offset < pkt->payload_len)
	{
		if(offset == 0)
		{
			frame_count++;	
   		    bitmap = 0;
		}
		switch(p[offset])
		{

		case KItemIMUSOL:
			bitmap = BIT_VALID_ALL;

			receive_imusol.id =p[offset + 1];
			memcpy(&receive_imusol.times, p + 8, sizeof(int)); 	
			memcpy(receive_imusol.acc, p + 12, sizeof(float) * 16);

			offset += 76;
			break;
		case KItemGWSOL:

			receive_gwsol.tag = p[offset];
			receive_gwsol.gw_id = p[offset + 1]; 
			receive_gwsol.n = p[offset + 2];
			offset += 8;
			for (int i = 0; i < receive_gwsol.n; i++)
			{
				bitmap = BIT_VALID_ALL;
				receive_gwsol.receive_imusol[i].tag = p[offset];
				receive_gwsol.receive_imusol[i].id = p[offset + 1];
				memcpy(&receive_gwsol.receive_imusol[i].acc, p + offset + 12 , sizeof(float) * 16);

				offset += 76;
			}
			break;
		default:
			offset++;

		}
    }
}


int imu_data_decode_init(void)
{
    packet_decode_init(&RxPkt, on_data_received);
    return 0;
}



