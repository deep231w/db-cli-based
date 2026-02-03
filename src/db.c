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

//add to file 
void addUserToFile(int lid , char *lname , int lage){
	printf("inside file writing");
	FILE *fp=fopen("database.txt","a");

	if(fp==NULL){
		perror("error / file not opened");
		return;
	}
	
	fprintf(fp, "%d %s %d\n", lid, lname, lage);
	printf("added user to file successfully!!");
	fclose(fp);
}
//add user to db
void addUserTodb(int lid , char *lname , int lage){
    User *ptr= (User *)malloc(sizeof(User));
    if(ptr ==NULL){
    	printf("memory allocation failed!\n");
	return;
    }  
	
    for(int i=0; i<db_users ;i++){
    	if(db[i]->id==lid){
	   printf("the same id is already exist already , please add different id\n");
	   free(ptr);
	   return;
	}
    }

    ptr->id=lid;
    //for(int i=0; i<sizeof(lname);i++){
    //	ptr->name[i]=lname[i];
    //}
    strcpy(ptr->name,lname);
    ptr->age=lage;
    
    db[db_users++]=ptr;

    addUserToFile(lid ,lname ,lage);
    printf("user data inside addusertodb func- %d %s %d\n", lid , lname , lage); 

    printf("user added to db successfully!\n");
}

void ListAllUsers(){
	printf("inside list all users func.\n");
	for(int i=0; i<db_users; i++){
		printf("%d %s %d\n", db[i]->id ,db[i]->name, db[i]->age);
	}
}

//find from db
void findById(int lid){
	for(int i=0; i<db_users;i++){
		if(db[i]->id == lid){
			printf("id=%d ,name:%s , age:%d \n", db[i]->id, db[i]->name ,db[i]->age);
			return;
		}
	}
}
//delete/remove user  by id
void deleteById(int lid){
	printf("inside delete fun id is %d", lid);
	int index=-1;
	for(int i=0; i<db_users; i++){
		if(db[i]->id == lid){
			index=i;
		}
		
	}

	if(index==-1){
		printf("id: %d not found , ",lid);
	}

	//free(db[index]);
	for(int i=index; i<db_users; i++){
		db[i]=db[i+1];
	}
	db_users --;

	printf("id:%d , user deleted susccessfuly !\n", lid);
}
//update by id
int updateById(){
	while(1){
		int lid;
		int input;
		char buf[32];

		printf("please enter id to update user\n");
		//scanf("%d",&lid);
		fgets(buf, sizeof(buf),stdin);
		lid=atoi(buf);
		if(!lid){
			continue;
		}

	
		int index;
		int found=0;
		for (int i=0; i<db_users; i++){
			if(db[i]->id ==lid){
				printf("current user ID: %d , NAME: %s , AGE: %d\n", db[i]->id , db[i]->name , db[i]->age);
				index=i;
				found=1;
				break;
			}
		}

		if(found==0){
			printf("user not found!\n");
			continue;
		}

		printf("please enter command to continue- \n");
		printf("(1)name\n");
		printf("(2)age\n");
		printf("(0)exit\n");
		fgets(buf, sizeof(buf), stdin);
		input=atoi(buf);

		//scanf("%d",&input);
		if(input==1){
			char lname[20];
			printf("please enter new Name: ");
			//scanf("%s",&lname);
			fgets(lname , sizeof(lname), stdin);
			lname[strcspn(lname, "\n")]=0;

			strcpy(db[index]->name,lname);
			printf("name updated\n");
			continue;
		}
		else if(input==2){
			int lage;
			printf("please enter new Age:");
			//scanf("%d", &lage);
			fgets(buf, sizeof(buf), stdin);
			lage=atoi(buf);
			db[index]->age=lage;
			printf("age updated successfully! \n");
			continue;
		}
		else if(input==0){
			printf("exiting ....\n");
			return 0;
		}
		else{
			printf("wrong command please try again!\n");
			continue;
		}
	}
	return 0;


}

//load from file to memory
void loadFromFile(){
	FILE *fp=fopen("database.txt", "r");
	if(fp==NULL){
		perror("file opening failed!");
		return;

	}
	char line[250];

	while(fgets(line, sizeof(line), fp)){
		if(db_users>=MAX_USERS){
			printf("db full");
			return;
		}

		int id , age;
		char name[20];

		if(sscanf(line , "%d %19s %d", &id ,name , &age)!=3){
			printf("invaid line skipped - %s", line);
			continue;
		}



		User *ptr =(User *)malloc(sizeof(User));

		if(ptr==NULL){
			printf("error allocating memory !");
			return;
		}

		ptr->id=id;
		ptr->age=age;
		strcpy(ptr->name, name);

		db[db_users++]=ptr;
	}
	fclose(fp);
	printf("loaded data from file to memory\n");
	return;	
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
            continue;
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

	if(strcmp(token, "find")== 0){
		char *id_str= strtok(NULL, " ");
		int id=atoi(id_str);
		findById(id);
	}
	//delete by id
	if(strcmp(token , "delete")==0){
		char *id_str= strtok(NULL, " ");
		
		int id=atoi(id_str);
		deleteById(id);
	}

	if(strcmp(token, "update")==0){
		updateById();
	}

	

	//load to memoey from file
	if(strcmp(token,"load")==0){
		loadFromFile();
	}
    }
    
    return 0;
}
