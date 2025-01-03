#include <stdio.h>
#include <string.h>
#include <dirent.h>
#include <sys/types.h>
#include <errno.h>
#include <stdlib.h>

#define NOTES_FOLDER "/home/marcos/notes/journals/"
#define MAX_FILENAME 256
#define MAX_LINE 256  
#define TODO_PATTERN "- TODO" 
#define DONE_PATTERN "- DONE" 

struct ToDo {
    int todoType;
    char text[MAX_LINE];
    char path[MAX_FILENAME];
};

enum todoType {
    TODO,
    DONE
};

int getTodoType (char* todoText) {
    if(strstr(todoText,TODO_PATTERN) != NULL) // check if line is a TODO
        return TODO;
    else if(strstr(todoText,DONE_PATTERN) != NULL) // check if line is a TODO
        return DONE;
    else return -1;
}


int main(){
  DIR *d;

  d = opendir(NOTES_FOLDER);
  if (d == NULL) {
    perror("Error Opening Directory: ") ;
    return(EXIT_FAILURE);
  }

  struct dirent *dir;
  while ((dir = readdir(d)) != NULL) {
    //skipping "." and ".."
    if (strcmp(dir -> d_name,".")== 0 || strcmp(dir -> d_name , "..") == 0){ 
        continue;
    }
    
    char name_buffer[MAX_FILENAME];
    strcpy(name_buffer,NOTES_FOLDER); // is this even safe?
    strcat(name_buffer,dir -> d_name);// TODO: Make sure these arent too large 
    //printf("\nTODO's For: %s \n",name_buffer);

    FILE *file;
    file = fopen(name_buffer,"r");
    if (file == NULL) {
        perror("Error Opening file: ");
        return(EXIT_FAILURE);
    }        
    
    char line_buffer[MAX_LINE];

    while(fgets(line_buffer,sizeof(line_buffer),file)){
        if(getTodoType(line_buffer) >=  0) // check if line is a TODO
            printf("%s",line_buffer);
     }
   }
  
  if (errno) {
      perror("failed to read direcotry");
      return(EXIT_FAILURE);
  }

    return(EXIT_SUCCESS);
}
