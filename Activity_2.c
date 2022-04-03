#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Process Struct
typedef struct proc {
  char name[256];
  int priority;
  int pid; 
  int runTime; 
} proc;

//Queue Struct
typedef struct queue{
  proc process;
  struct queue *next;
} queue;

//Linked list
queue *linkedListHead;

//Returns the item at the end of the list and removes it from the list
proc *pop () {   
    proc *returnProcess = malloc(sizeof(proc));
    queue *nextNode = NULL;

    if(linkedListHead == NULL){
        return NULL;
    }

    nextNode = linkedListHead->next;
    *returnProcess = linkedListHead->process;
    linkedListHead = nextNode;

    return returnProcess;
}

void delete_name(char *name) {

}

void delete_pid(int pid) {

}

//Push a process into the end of the list
void push (proc *process){
  queue* current = linkedListHead;

  //Go through the list until the the last item
  while (current->next != NULL ){
    current = current->next;
  }

  //Add the new process
  current->next = malloc(sizeof(queue));
  current->process = *process;
  current->next->next = NULL;
}

//Print the list out
void printList () {
  queue *current = linkedListHead;
  while (current->next != NULL){
    //Print the value
    printf("Process Name: %s \n", current->process.name);
    printf("Process priority: %d \n", current->process.priority);
    printf("Process ID: %d \n", current->process.pid);
    printf("Process Runtime: %d \n\n", current->process.runTime);
    //Go to the next item in the list
    current = current->next;
  }
}

//Read the file and store the value into the struct proc
void readFile(){
   FILE *fp;
   char buffer[256]; 
  // Open file
  fp = fopen("processes.txt", "r");
  if (fp == NULL) {
      printf("Cannot open file \n");
      exit(0);
  }

  //Read each line from file until end of file
  while(fgets(buffer, 256, fp) != NULL) {
    proc* newProcess = malloc(sizeof(proc));
    char *token;

    //systemd, 0, 1, 5 
    //Get the process name
    token = strtok(buffer, ", ");
    strcpy (newProcess->name, token);
    token = strtok(NULL, ", ");
    
    //If the token is NULL, then no more data left
    if (token == NULL){
      break;
    }

    //Get the priority value
    sscanf(token, "%d", &newProcess->priority);
    token = strtok (NULL, ", ");

    //Get the PID value
    sscanf(token, "%d", &newProcess->pid);
    token = strtok(NULL, ", ");
    sscanf (token, "%d", &newProcess->runTime);
    
    //Push the new process to the linkedListHead
    push(newProcess);    
  }  
}

int main (void){
    linkedListHead = NULL;
    linkedListHead = malloc(sizeof(queue));

    readFile();
    printList();

    proc *poppedProcess = pop();

    printf("Popped Name: %s", poppedProcess->name);
}