#include<stdio.h>
#include<stdlib.h>
#include<string.h>


#define MAX_INPUT 1024
#define MAX_USERS 100

typedef struct 
{
    int id;
    char name[20];
    int age;
}User;

User *db[MAX_USERS];
int db_users=0;

void addUserTodb(int lid , char *lname , int lage){
    User *ptr= (User *)malloc(sizeof(User));
    if(ptr ==NULL){
    	printf("memory allocation failed!\n");
	return;
    }  

    ptr->id=lid;
    //for(int i=0; i<sizeof(lname);i++){
    //	ptr->name[i]=lname[i];
    //}
    strcpy(ptr->name,lname);
    ptr->age=lage;
    
    db[db_users++]=ptr;
    printf("user data inside addusertodb func- %d %s %d", lid , lname , lage);

    printf("user added to db successfully!\n");
}

void ListAllUsers(){
	printf("inside list all users func.\n");
	for(int i=0; i<db_users; i++){
		printf("%d %s %d\n", db[i]->id ,db[i]->name, db[i]->age);
	}
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

        char *token = strtok(input , " \n");
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
            char *id_str = strtok(NULL , " ");
            char *name= strtok(NULL , " ");
            char *age_str= strtok(NULL , " ");

	    if(!id_str || !name || !age_str){
	    	printf("usage :add <id> <name><age>\n");
		continue;
	    }
	    int id= atoi(id_str);
	    int age=atoi(age_str);


            addUserTodb(id , name , age);
        }
        
	if(strcmp(token, "list")==0){
		printf("inside list ");
		ListAllUsers();
	}
    }
    
    return 0;
}
