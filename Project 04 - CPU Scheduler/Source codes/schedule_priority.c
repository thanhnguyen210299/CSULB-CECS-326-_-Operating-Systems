/*
 * Priority scheduling
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "task.h"
#include "list.h"
#include "CPU.h"
#include "schedulers.h"

static struct node* taskList = NULL;

// add a task to the list
void add(char* name, int priority, int burst)
{
	// create a new task based on the parameters
	Task* newTask = malloc(sizeof(Task));
	newTask->priority = priority;
	newTask->burst = burst;
	// copy the name of task to store in the list
	newTask->name = malloc(sizeof(char) * (strlen(name) + 1));
	strcpy(newTask->name, name);

	// add the new task to list, the new task will be placed before the head
	insert(&taskList, newTask);
}

// pick the next Task based on Priority algorithm
Task* pickNextTask()
{
	// get the task has the highest priority (smallest number)

	// assign the head is the task has highest priority
	struct node* currentTask = taskList;
	Task* highestPriorityTask = currentTask->task;

	// check the other tasks
	currentTask = currentTask->next;

	while (currentTask)
	{
		if (currentTask->task->priority < highestPriorityTask->priority)
			highestPriorityTask = currentTask->task;
		currentTask = currentTask->next;
	}

	return highestPriorityTask;
}

// invoke the scheduler
void schedule()
{
	while (taskList)
	{
		Task* nextTask = pickNextTask();
		run(nextTask, nextTask->burst);
		delete(&taskList, nextTask);
	}
}
