#include <stdio.h>
#include <string.h>

struct record{
    char name[100];
    int rollno;
    float marks[3];
    float percentage;
    char grade[3];
};

struct record students[10];
int count=0;

void calculateGrade(struct record *s){
    float p = s->percentage;
    if(p >= 90){
	    strcpy(s->grade,"A+");
	}
    else if(p >= 80){
	    strcpy(s->grade,"A");
	}
    else if(p >= 70){
    	strcpy(s->grade,"B+");
	} 
    else if(p >= 60){
    	strcpy(s->grade,"B");
	} 
    else if(p >= 50){
    	strcpy(s->grade,"C");
	}    
	else{
		strcpy(s->grade,"F");
	}	
}

int main(){
    int choice,i,j;
    while(1){
        printf("\n1.Add Student\n2.Display All\n3.Find by Grade\n4.Class Average and Above/Below\n5.Search by Roll Number\n6.Search by Name\n7.Exit\nChoice: ");
        scanf("%d",&choice);
        
        if(choice==1){  
            if(count>=10){
                printf("Full!\n");
                continue;
            }
            printf("Name: ");
            scanf(" %[^\n]",students[count].name);
            printf("Roll Number: ");
            scanf("%d",&students[count].rollno);
            
            j=0;
            while(j<3){
                printf("Marks for Subject %d (0-100): ",j+1);
                scanf("%f",&students[count].marks[j]);
                if(students[count].marks[j]<0 || students[count].marks[j]>100){
                    printf("Invalid marks! Must be 0-100.\n");
                } 
				else{
                	j++;
				}
            }
            
            students[count].percentage=(students[count].marks[0]+students[count].marks[1]+students[count].marks[2])/3.0;
            calculateGrade(&students[count]);
            count++;
            printf("Added!\n");
        }
        
        
        else if(choice==2){
            if(count==0){
                printf("No students!\n");
            } else{
                printf("\n%-15s %-8s %-8s %-8s %-8s %-10s %-6s\n","Name","RollNo","Sub1","Sub2","Sub3","Percentage","Grade");
                printf("----------------------------------------------------------------------\n");
                for(i=0;i<count;i++){
                    printf("%-15s %-8d %-8.2f %-8.2f %-8.2f %-10.2f %-6s\n",
                           students[i].name,students[i].rollno,
                           students[i].marks[0],students[i].marks[1],students[i].marks[2],
                           students[i].percentage,students[i].grade);
                }
            }
        }
        
        
        else if(choice==3){
            char g[3];
            printf("Grade (A+, A, B+, B, C, F): ");
            scanf(" %2s",g);
            int found=0;
            for(i=0;i<count;i++){
                if(strcmp(students[i].grade,g)==0){
                    if(!found){
                        printf("\n%-15s %-8s %-10s\n","Name","RollNo","Percentage");
                        printf("----------------------------------------\n");
                    }
                    printf("%-15s %-8d %-10.2f\n",students[i].name,students[i].rollno,students[i].percentage);
                    found=1;
                }
            }
            if(!found){
            	printf("No student with grade %s found.\n",g);
			}
        }
        
        
        else if(choice==4){
            if(count==0){
                printf("No students!\n");
                continue;
            }
            
            float total=0;
            for(i=0;i<count;i++) total+=students[i].percentage;
            float avg=total/count;
            printf("Class Average: %.2f\n",avg);
            
            printf("Above Average:\n");
            printf("%-15s %-8s %-10s\n","Name","RollNo","Percentage");
            printf("----------------------------------------\n");
            for(i=0;i<count;i++){
                if(students[i].percentage>avg){
                    printf("%-15s %-8d %-10.2f\n",students[i].name,students[i].rollno,students[i].percentage);
                }
            }
            
            printf("Below Average:\n");
            printf("%-15s %-8s %-10s\n","Name","RollNo","Percentage");
            printf("----------------------------------------\n");
            for(i=0;i<count;i++){
                if(students[i].percentage<avg){
                    printf("%-15s %-8d %-10.2f\n",students[i].name,students[i].rollno,students[i].percentage);
                }
            }
        }
        
        
        else if(choice==5){
            int roll;
            printf("Roll Number: ");
            scanf("%d",&roll);
            int found=0;
            for(i=0;i<count;i++){
                if(students[i].rollno==roll){
                    printf("\n%-15s %-8s %-8s %-8s %-8s %-10s %-6s\n","Name","RollNo","Sub1","Sub2","Sub3","Percentage","Grade");
                    printf("----------------------------------------------------------------------\n");
                    printf("%-15s %-8d %-8.2f %-8.2f %-8.2f %-10.2f %-6s\n",
                           students[i].name,students[i].rollno,
                           students[i].marks[0],students[i].marks[1],students[i].marks[2],
                           students[i].percentage,students[i].grade);
                    found=1;
                    break;
                }
            }
            if(!found){
            	 printf("Student not found.\n");
			}
        }
        
        
        else if(choice==6){
            char n[100];
            printf("Name: ");
            scanf(" %[^\n]",n);
            int found=0;
            for(i=0;i<count;i++){
                if(strcmp(students[i].name,n)==0){
                    printf("\n%-15s %-8s %-8s %-8s %-8s %-10s %-6s\n","Name","RollNo","Sub1","Sub2","Sub3","Percentage","Grade");
                    printf("----------------------------------------------------------------------\n");
                    printf("%-15s %-8d %-8.2f %-8.2f %-8.2f %-10.2f %-6s\n",
                           students[i].name,students[i].rollno,
                           students[i].marks[0],students[i].marks[1],students[i].marks[2],
                           students[i].percentage,students[i].grade);
                    found=1;
                    break;
                }
            }
            if(!found){
            	printf("Student not found.\n");
			}
        }
        
        else if(choice==7){
            break;
        }
        else{
            printf("Invalid!\n");
        }
    }
    
    
    return 0;
}

