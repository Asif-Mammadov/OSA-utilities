
#include<sys/types.h>
#include<dirent.h>
#include<stdio.h>

void read_dir(char *path);

int main(int argc, char *argv[]){
  if(argc == 1){
    read_dir(".");
    printf("\n");
  }
  else {
    for(int i = 1; i < argc; i++){
      printf("%s :\n", argv[i]);
      read_dir(argv[i]);
      printf("\n");
    }
  }
}

void read_dir(char *path){
  DIR *dp;
  struct dirent *d;
  dp = opendir(path);
  if(dp == NULL){
    perror("opendir failed");
    return;
  }
  while((d = readdir(dp)) != NULL){
    if(d->d_name[0] == '.')
      continue;
    printf("%s ", d->d_name);
  }
}
