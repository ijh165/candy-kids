#include "stats.h"
#include <stdlib.h>
#include <stdio.h>
int num_factories = 0;

typedef struct statFactory
{
	int FactoryNum;
	int MadeNum;
	int EatenNum;
	double minDelay;
	double avgDelay;
	double maxDelay;
	double totalDelay;
}statistics;

statistics *statsAr;	

void stats_init(int num_producers)
{
/*
	num_factories = num_producers;
	statsAr = malloc(num_producers*sizeof(statistics));
	for(int i = 0; i< num_producers; i++){
		statsAr[i].FactoryNum = i;
		statsAr[i].MadeNum = 0;
		statsAr[i].EatenNum = 0;
		statsAr[i].minDelay = -1;	
		statsAr[i].avgDelay = -1;
		statsAr[i].maxDelay = -1;
		statsAr[i].totalDelay = 0;
	}
*/
	return;
}

void stats_cleanup(void)
{
	printf("clean up\n");
	free(statsAr);
	statsAr = NULL;
	return;
}

void stats_record_produced(int factory_number)
{
/*
	statsAr[factory_number].MadeNum++;
	//statsAr[factory_number] = malloc(sizeof(statistics));
	 	
	//printf("statsAr[%d] is %d\n", factory_number, statsAr[factory_number].FactoryNum);
*/
	return;
}

void stats_record_consumed(int factory_number, double delay_in_ms)
{
	/*
	statsAr[factory_number].EatenNum++;
	if(statsAr[factory_number].minDelay == -1){
		statsAr[factory_number].minDelay = delay_in_ms;
		statsAr[factory_number].avgDelay = delay_in_ms;
		statsAr[factory_number].maxDelay = delay_in_ms;
		statsAr[factory_number].totalDelay = delay_in_ms;
	}
	else{
		if(statsAr[factory_number].minDelay > delay_in_ms){
			statsAr[factory_number].minDelay = delay_in_ms;
		}
		if(statsAr[factory_number].maxDelay < delay_in_ms){
			statsAr[factory_number].maxDelay = delay_in_ms;	
		}
		statsAr[factory_number].totalDelay+= delay_in_ms;
		statsAr[factory_number].avgDelay = statsAr[factory_number].totalDelay/(double)statsAr[factory_number].EatenNum;	
	}
	*/
	return;
}

void stats_display(void)
{
	//fill me
	return;
}
