#include "stats.h"
#include <stdlib.h>
#include <stdio.h>

int num_factories = 0;
sem_t statmutex;

typedef struct stats
{
	int factoryNum;
	int madeNum;
	int eatenNum;
	double minDelay;
	double avgDelay;
	double maxDelay;
	double totalDelay;
} stats_t;

stats_t* stats_arr;

void stats_init(int num_producers)
{
	num_factories = num_producers;
	stats_arr = malloc(num_producers*sizeof(stats_t));
	for(int i = 0; i< num_producers; i++) {
		stats_arr[i].factoryNum = i;
		stats_arr[i].madeNum = 0;
		stats_arr[i].eatenNum = 0;
		stats_arr[i].minDelay = -1;
		stats_arr[i].avgDelay = -1;
		stats_arr[i].maxDelay = -1;
		stats_arr[i].totalDelay = 0;
	}
    sem_init(&statmutex, 0, 1);

}

void stats_cleanup(void)
{
	free(stats_arr);
	stats_arr = NULL;
}

void stats_record_produced(int factory_number)
{
    sem_wait(&statmutex);
	stats_arr[factory_number].madeNum++;
    sem_post(&statmutex);

}

void stats_record_consumed(int factory_number, double delay_in_ms)
{
	stats_arr[factory_number].eatenNum++;
	if(stats_arr[factory_number].minDelay == -1) {
		stats_arr[factory_number].minDelay = delay_in_ms;
		stats_arr[factory_number].avgDelay = delay_in_ms;
		stats_arr[factory_number].maxDelay = delay_in_ms;
		stats_arr[factory_number].totalDelay = delay_in_ms;
	}
	else {
		if(stats_arr[factory_number].minDelay > delay_in_ms) {
			stats_arr[factory_number].minDelay = delay_in_ms;
		}
		if(stats_arr[factory_number].maxDelay < delay_in_ms) {
			stats_arr[factory_number].maxDelay = delay_in_ms;
		}
		stats_arr[factory_number].totalDelay += delay_in_ms;
		stats_arr[factory_number].avgDelay = stats_arr[factory_number].totalDelay/(double)stats_arr[factory_number].eatenNum;
	}
}

void stats_display(void)
{
	printf("\n=====================================Statistics=====================================\n");
	printf("%s%10s%11s%18s%18s%18s\n", "Factory #", "# Made", "# Eaten", "Min Delay [ms]", "Avg Delay [ms]", "Max Delay [ms]");
	for(int i=0; i<num_factories; i++) {
		printf("%5d%11d%11d%17.5f%18.5f%18.5f\n",
				stats_arr[i].factoryNum,
				stats_arr[i].madeNum,
				stats_arr[i].eatenNum,
				stats_arr[i].minDelay,
				stats_arr[i].avgDelay,
				stats_arr[i].maxDelay);
		if(stats_arr[i].madeNum != stats_arr[i].eatenNum) {
			printf("\tERROR: Mismatch between number made and eaten.\n");
		}
	}
	printf("\n");
}
