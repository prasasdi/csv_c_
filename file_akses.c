#include <stdio.h>
#include <string.h>
#include <time.h>

typedef struct person {
  char name[255];
  int born_year;
  int age;
} person;

char* construct_csv_person(person* p)
{
  char csv_buffer[255];
  char* p_str = csv_buffer;
  //strncpy(csvish, p->name, sizeof(p->name));

  strtok(p->name, "\n");
  sprintf(csv_buffer, "%s,%d,%d", p->name, p->born_year, p->age);
  printf("%s\n",csv_buffer);
  return p_str;
}

// todo; write to a file
int read_file(person* p)
{
  FILE* fp;

  fp = fopen("dats.txt", "r+");

  if (fp == NULL)
  {
    printf("error opening file\n");
    return -1;
  }

  fseek(fp,0,SEEK_END);

  // current position
  long file_size = ftell(fp);
  if (file_size != 0)
  {
    fwrite(",", sizeof(char), 1, fp); 
  }
  
  // write file
  char csv_buffer[255];

  strtok(p->name, "\n");
  sprintf(csv_buffer, "%s,%d,%d", p->name, p->born_year, p->age); 
  printf("%s\n",csv_buffer);
  fwrite(csv_buffer, sizeof(char), strlen(csv_buffer), fp);
  fclose(fp);
  return 0;
}
int determine_age(int* year)
{
        time_t timer;
        struct tm* tm_info;

        time(&timer);
        tm_info=localtime(&timer);
        int current_y = tm_info->tm_year;
        return 1900+current_y-*year;
}

int main(void)
{
  struct person _person;

  printf("name: ");
  fgets(_person.name, 255, stdin);

  printf("\ntahun lahir: ");
  char buffer_tahun_lahir[5];
  if (scanf("%d", &_person.born_year) == 1 )
  {
    _person.age = determine_age(&_person.born_year);
    read_file(&_person);
    construct_csv_person(&_person);
  }
  else
  {
    printf("no ok\n");
  }
  


  return 0;
}
