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

//Delete a process with the process name
proc *delete_name(char *name) {
  int found = 0;
  proc *DeletedProcess = malloc(sizeof(proc));
  queue *current = linkedListHead;

  //Check if the list is empty, and if empty then name not found
  if (current->next == NULL) {
    found = 0;
  }

  //Keep traversing through the linked list until its empty
  while (current->next != NULL){
    char *currentName = current->next->process.name;
    //If the strings match then it returns 0
    if (strcmp (currentName, name) == 0) {
      *DeletedProcess = current->next->process;
      current->next = current->next->next;
      found = 1;
    }
    current = current->next;
  }

  //If the name is not found, then change deleted process to NULL
  if (found == 0) {
    DeletedProcess = NULL;
  }

  return DeletedProcess;
}

//Delete a process with process ID
proc* delete_pid(int pid) {
  int found = 0;
  proc *DeletedProcess = malloc(sizeof(proc));
  queue *current = linkedListHead;

  //Check if the list is empty, and if empty then name not found
  if (current->next == NULL) {
    found = 0;
  }

  //Keep traversing through the linked list until its empty
  while (current->next != NULL){
    int currentPID = current->next->process.pid;
    //If the strings match then it returns 0
    if (currentPID == pid) {
      *DeletedProcess = current->next->process;
      current->next = current->next->next;
      found = 1;
    }
    current = current->next;
  }

  //If the name is not found, then change deleted process to NULL
  if (found == 0) {
    DeletedProcess = NULL;
  }

  return DeletedProcess;
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

//Print out the deleted process from the list
void printDeleted (proc *deletedProc) {
  if (deletedProc != NULL){  
    printf("Deleted Process: %s with PID: %d\n", deletedProc->name, deletedProc->pid);
  }
  else {
    printf("Process NOT FOUND! \n");
  }
}

//Print the process values
void printProcess (proc *process){  
  printf("Process Name: %s \n", process->name);
  printf("Process Priority: %d \n", process->priority);
  printf("Process ID: %d \n", process->pid);
  printf("Process Runtime: %d \n\n", process->runTime);
}

int main (void){
  //Start the linkedListHead from NULL (Empty List)
  linkedListHead = NULL;
  linkedListHead = malloc(sizeof(queue));

  //Initialization 
  proc *deletedProc;
  int counter = 1;
  char deleteName[6] = "emacs";
  int deletePID = 12235;
  
  printf("\n");
  readFile();
  
  //Delete process emacs and PID = 12235
  deletedProc = delete_name(deleteName);
  printDeleted(deletedProc);
  deletedProc = delete_pid(deletePID);
  printDeleted(deletedProc);
  printf("\n");

  //Keep going through the list until its null (end of the list)
  while (linkedListHead->next != NULL) {
    printf("Process Popped %d \n", counter);
    deletedProc = pop();
    printProcess(deletedProc);
    counter++;
  }
}