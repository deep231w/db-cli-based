#include<stdio.h>
#include<string.h>
#define MAX_INPUT 1024


typedef struct 
{
    int id;
    char name[20];
    int age;
}user;


void addUserTodb(){
    
    printf("user added to db successfully!\n");
}

int main(){
    char input[MAX_INPUT];

    
    while (1)
    {
        printf("deep-db>");
        fflush(stdout);

        if(!fgets(input , MAX_INPUT , stdin)){
            break;
        }

        char *token = strtok(input , " ");
        printf("token- %s\n", token);

        // while (token != NULL)
        // {
        //     char *id= strtok(NULL ," ");
        //     char *name= strtok(NULL , " ");

        //     printf("%s\n", token);
        // }

        if(!token){
            return 0;
        }

        if(strcmp(token, "add")==0){
            char *id = strtok(NULL , " ");
            char *name= strtok(NULL , " ");
            char *age= strtok(NULL , " ");

            addUserTodb();
        }
        
    }
    
    return 0;
}