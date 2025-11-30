#include <stdio.h>
#include <string.h>
#include <time.h>

struct Employee{
    int id;
    char name[50];
    int department;
    int designation;
    float salary;
    int joinDay, joinMonth, joinYear;
    char phone[20];
    char email[50];
};

struct Employee emp[100];
int count = 0;

char *department[]  = {"IT", "HR", "Finance", "Marketing", "Operations"};
char *designation[] = {"Intern", "Junior", "Senior", "Manager", "Director"};

int yearsOfExperience(int d, int m, int y){
    time_t t = time(NULL);
    struct tm *now = localtime(&t);
    int Y = now->tm_year + 1900;
    int M = now->tm_mon + 1;
    int D = now->tm_mday;
    int exp = Y - y;
    if (M < m || (M == m && D < d)){
    	exp--;
	}
	
    return exp;
}

void addEmployee(){
    printf("Enter Employee ID: ");
    scanf("%d", &emp[count].id);

    printf("Enter Name: ");
    scanf(" %[^\n]", emp[count].name);

    printf("Department Codes: 0-IT 1-HR 2-Finance 3-Marketing 4-Operations\n");
    printf("Enter Department: ");
    scanf("%d", &emp[count].department);

    printf("Designation Codes: 0-Intern 1-Junior 2-Senior 3-Manager 4-Director\n");
    printf("Enter Designation: ");
    scanf("%d", &emp[count].designation);

    printf("Enter Salary: ");
    scanf("%f", &emp[count].salary);

    printf("Enter Joining Date-onebyone (dd mm yyyy): ");
    scanf("%d %d %d", &emp[count].joinDay, &emp[count].joinMonth, &emp[count].joinYear);

    printf("Enter Phone Number: ");
    scanf(" %[^\n]", emp[count].phone);

    printf("Enter Email: ");
    scanf(" %[^\n]", emp[count].email);

    count++;
    printf("Employee Added.\n");
}

void displayAll(){
	int i;
    if (count == 0){
        printf("No records.\n");
        return;
    }

    for (i = 0; i < count; i++){
        printf("\nID: %d\n", emp[i].id);
        printf("Name: %s\n", emp[i].name);
        printf("Department: %s\n", department[emp[i].department]);
        printf("Designation: %s\n", designation[emp[i].designation]);
        printf("Salary: %.2f\n", emp[i].salary);
        printf("Joining Date: %d/%d/%d\n", emp[i].joinDay, emp[i].joinMonth, emp[i].joinYear);
        printf("Experience: %d years\n", yearsOfExperience(emp[i].joinDay, emp[i].joinMonth, emp[i].joinYear));
        printf("Phone: %s\n", emp[i].phone);
        printf("Email: %s\n", emp[i].email);
    }
}

void salaryStats(){
    int i;
    float sum[5] = {0};
    int num[5] = {0};

    for (i = 0; i < count; i++){
        sum[emp[i].department] += emp[i].salary;
        num[emp[i].department]++;
    }

    for (i = 0; i < 5; i++){
        if (num[i] > 0){
            printf("%s Average Salary: %.2f\n", department[i], sum[i] / num[i]);
		}
        else{
            printf("%s: No Employees\n", department[i]);
		}
    }
}

void applyAppraisal(){
    int percent, i;
    printf("Enter appraisal percent (5-15): ");
    scanf("%d", &percent);

    if (percent < 5 || percent > 15){
        printf("Invalid.\n");
        return;
    }

    for(i = 0; i < count; i++){
        emp[i].salary += emp[i].salary * percent / 100.0;
    }
    printf("Appraisal Applied.\n");
}

void search(){
    int i, ch, key;
    printf("1. Department\n2. Designation\n3. Experience\nEnter choice: ");
    scanf("%d", &ch);

    if (ch == 1){
        printf("Enter Department (0-4): ");
        scanf("%d", &key);
        for(i = 0; i < count; i++){
            if (emp[i].department == key){
                printf("%s\n", emp[i].name);
            }
        }
    }

    else if (ch == 2){
        printf("Enter Designation (0-4): ");
        scanf("%d", &key);
        for (i = 0; i < count; i++){
            if (emp[i].designation == key){
                printf("%s\n", emp[i].name);
            }
        }
    }

    else if (ch == 3){
        printf("Minimum Experience: ");
        scanf("%d", &key);
        for (i = 0; i < count; i++){
            if (yearsOfExperience(emp[i].joinDay, emp[i].joinMonth, emp[i].joinYear) >= key){
                printf("%s\n", emp[i].name);
            }
        }
    }
}

void promotionEligible(){
	int i;
    for (i = 0; i < count; i++){
        int exp = yearsOfExperience(emp[i].joinDay, emp[i].joinMonth, emp[i].joinYear);
        if (exp > 3){
            printf("%s (%d years)\n", emp[i].name, exp);
        }
    }
}

int main(){
    int choice;

    while (1) {
        printf("\n1. Add Employee\n");
        printf("2. Display All\n");
        printf("3. Salary Stats\n");
        printf("4. Apply Appraisal\n");
        printf("5. Search\n");
        printf("6. Promotion Eligibility\n");
        printf("7. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        if (choice == 1) addEmployee();
        else if (choice == 2) displayAll();
        else if (choice == 3) salaryStats();
        else if (choice == 4) applyAppraisal();
        else if (choice == 5) search();
        else if (choice == 6) promotionEligible();
        else if (choice == 7) return 0;
        else printf("Invalid.\n");
    }
}

