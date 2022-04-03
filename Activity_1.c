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

  //After adding the new item, set the next item to NULL or end of the list
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
    //Get Process Name
    token = strtok(buffer, ", ");
    if (token != NULL){
      strcpy (newProcess->name, token);
    }
    else {
      break;
    }
    
    //sscanf(const char *str, const char *format, ...) used to get 
    //Get the priority value
    token = strtok(NULL, ", ");
    sscanf(token, "%d", &newProcess->priority);

    //Get the PID value
    token = strtok (NULL, ", ");
    sscanf(token, "%d", &newProcess->pid);

    //Get the runtime Value
    token = strtok(NULL, ", ");
    sscanf (token, "%d", &newProcess->runTime);
    
    //Push the new process to the linkedListHead
    push(newProcess);    
  }  
}

int main (void){
  linkedListHead = NULL;
  linkedListHead = malloc(sizeof(queue));
  
  printf("\n");
  readFile();
  printList();
}