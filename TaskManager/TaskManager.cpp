/***************************************************************************
 *=====================      Copyright by novartsoft.com      ===============
 ****************************************************************************
 * Title        : TaskManager.cpp
 *
 * Description  : This module is responsable of scheduling
 *                the tasks on the FreeRTOS system
 *
 * Environment  : ESP32
 *
 * Responsible  : Catalin Gyorgy
 *
 * History:
 * 10.06.2021    CatGyo  Initial revision
 */

#include "TaskManagerI.h"
#include "TaskManagerE.h"
#include <Arduino.h>
#include "CommonDataE.h"
void TaskManager_setup()
{
  xTaskCreatePinnedToCore(
      TaskManager__DisplayTask, /* Function to be called */
      "Display Task",           /* Name of the task */
      11776,                    /* Stack size */
      NULL,                     /* Parameters to pass to function */
      2,                        /* Task priority (0 to configMAX_PRIORITIES - 1) */
      NULL,                     /* Task handle */
      1                         /* Run on one core */
  );
  xTaskCreatePinnedToCore(
      TaskManager__ReadQueue, /* Function to be called */
      "CommonData read task", /* Name of the task */
      6144,                   /* Stack size */
      NULL,                   /* Parameters to pass to function */
      4,                      /* Task priority (0 to configMAX_PRIORITIES - 1) */
      NULL,                   /* Task handle */
      1                       /* Run on one core */
  );
  xTaskCreatePinnedToCore(
      TaskManager__Task10ms, /* Function to be called */
      "Task 10ms Manager",   /* Name of the task */
      4096,                  /* Stack size */
      NULL,                  /* Parameters to pass to function */
      3,                     /* Task priority (0 to configMAX_PRIORITIES - 1) */
      NULL,                  /* Task handle */
      0                      /* Run on one core */
  );

  xTaskCreatePinnedToCore(
      TaskManager__Task50ms, /* Function to be called */
      "Task 50ms Manager",   /* Name of the task */
      4096,                  /* Stack size */
      NULL,                  /* Parameters to pass to function */
      1,                     /* Task priority (0 to configMAX_PRIORITIES - 1) */
      NULL,                  /* Task handle */
      0                      /* Run on one core */
  );

  xTaskCreatePinnedToCore(
      TaskManager__Task100ms, /* Function to be called */
      "Task 100ms Manager",   /* Name of the task */
      4096,                   /* Stack size */
      NULL,                   /* Parameters to pass to function */
      1,                      /* Task priority (0 to configMAX_PRIORITIES - 1) */
      NULL,                   /* Task handle */
      0                       /* Run on one core */
  );
  Serial.println("1.Temperature");
  Serial.println("0101 -> C||0102 -> F");
  Serial.println("2.Time");
  Serial.println("0201 -> 24h||0202 -> 12h");
  Serial.println("3.Speed");
  Serial.println("0301 -> KM/h||0302 -> Mph");
  Serial.println("Select what format would you like to change");
}
void TaskManager__ReadQueue(void *parameter)
{
  TickType_t xLastWakeTime;

  xLastWakeTime = xTaskGetTickCount();

  TaskManager__InitReadQueue;

  while (1)
  {
    vTaskDelayUntil(&xLastWakeTime, TaskManager__Delay10);
    TaskManager__ReadQueueContainer;
  }
}

void TaskManager__DisplayTask(void *parameter)
{
  TickType_t xLastWakeTime;

  xLastWakeTime = xTaskGetTickCount();

  TaskManager__InitDisplay;

  while (1)
  {
    vTaskDelayUntil(&xLastWakeTime, TaskManager__Delay50);
    TaskManager__DisplayContainer;
  }
}

void TaskManager__Task10ms(void *parameter)
{

  TickType_t xLastWakeTime;

  xLastWakeTime = xTaskGetTickCount();

  while (1)
  {
    vTaskDelayUntil(&xLastWakeTime, TaskManager__Delay10);
    TaskManager__10msContainer;
  }
}

void TaskManager__Task50ms(void *parameter)
{

  TickType_t xLastWakeTime;

  xLastWakeTime = xTaskGetTickCount();

  TaskManager__Init50ms;

  while (1)
  {
    vTaskDelayUntil(&xLastWakeTime, TaskManager__Delay50);
    TaskManager__50msContainer;
  }
}

void TaskManager__Task100ms(void *parameter)
{

  TickType_t xLastWakeTime;

  xLastWakeTime = xTaskGetTickCount();

  TaskManager__Init100ms;

  while (1)
  {
    vTaskDelayUntil(&xLastWakeTime, TaskManager__Delay100);
    TaskManager__100msContainer;
  }
}