/*
 * ----------------------------------------------------------------------
 * File:      Mutex.c
 * Project:   Mutex
 * Author:    Sanjay Vyas
 * 
 * Description:
 *  Implementing mutex in C language 
 * ----------------------------------------------------------------------
 * Revision History:
 * 2020-Aug-10	[SV]: Created
 * ----------------------------------------------------------------------
 */

#include <stdio.h>   // printf()
#include <unistd.h>  // sleep()
#include <pthread.h> // pthread_xxx() functions
#include <stdlib.h>  // rand()

// Define a shared resource
int itemsSold = 0;

// Define a mutex to access itemsSold
pthread_mutex_t salesCounter = PTHREAD_MUTEX_INITIALIZER;

void *sellItems(void *salesPersonName)
{
    int i;
    int takeBreak;

    takeBreak = (rand() % 5) + 5;
    printf("\n%s will start selling in %d sec\n", (char *)salesPersonName, takeBreak);
    sleep(takeBreak);

    // The seller must acquire the mutex, sell some items and release the lock
    pthread_mutex_lock(&salesCounter);
    printf("\n%s has taken the counter\n", (char *)salesPersonName);
    for (i = 0; i < 3; i++)
    {
        itemsSold++;
        printf("Salesperson %s selling item %d\n", (char *)salesPersonName, itemsSold);
        sleep(2);
    }
    pthread_mutex_unlock(&salesCounter);
}

int main()
{
    // Hire two sales people
    pthread_t salesPerson1;
    pthread_t salesPerson2;

    // Number of shifts
    int shift;

    // Ask them to use the same counter to sell items in multiple shifts
    printf("Waiting for sales people to finish selling...\n");
    for (shift = 1; shift < 4; shift++)
    {
        pthread_create(&salesPerson1, NULL, sellItems, "Ram");
        pthread_create(&salesPerson2, NULL, sellItems, "Lakhan");

        // Wait for them to finish
        pthread_join(salesPerson1, NULL);
        pthread_join(salesPerson2, NULL);
    }

    printf("\nSales teams has sold %d items\n", itemsSold);

    return 0;
}