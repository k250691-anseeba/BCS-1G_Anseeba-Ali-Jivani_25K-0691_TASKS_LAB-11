#include <stdio.h>
#include <string.h>
#include <time.h>

#define MAX_ACCOUNTS 10
#define MAX_TX 20

struct Transaction{
    char type[10];  
    float amount;
    char date[20];
};

struct Account{
    int no;                // Account number
    char name[50];         // Account holder
    char type[20];         // "Savings", "Current", "Fixed"
    float balance;         // Current balance
    float min;             // Minimum balance
    float rate;            // Interest rate
    char created[20];      // Account creation date
    char last[20];         // Last transaction date
    struct Transaction tx[MAX_TX];
    int txCount;
};

struct Account bank[MAX_ACCOUNTS];
int totalAccounts = 0;


void today(char d[]){
    time_t t;
    time(&t);
    struct tm *tm = localtime(&t);
    strftime(d, 20, "%Y-%m-%d", tm);
}


void newAccount(){
    if(totalAccounts >= MAX_ACCOUNTS){
        printf("Cannot create more accounts!\n");
        return;
    }

    struct Account a;
    a.txCount = 0;
    a.no = 1000 + totalAccounts;

    printf("Enter Name: ");
    scanf(" %[^\n]", a.name);

    int t;
    printf("Account Type: 1.Savings 2.Current 3.Fixed: ");
    scanf("%d", &t);

    if(t==1){
        strcpy(a.type,"Savings"); 
		a.min=1000; a.rate=4;
    }
    else if(t==2){
        strcpy(a.type,"Current"); 
		a.min=5000; a.rate=0;
    }
    else if(t==3){
        strcpy(a.type,"Fixed"); 
		a.min=10000; a.rate=7;
    }
    else{
        printf("Invalid type!\n"); 
		return;
    }

    float b;
    do{
        printf("Initial deposit (min %.2f): ", a.min);
        scanf("%f",&b);
        if(b<a.min) printf("Too low!\n");
        
    }while(b<a.min);

    a.balance = b;
    today(a.created);
    strcpy(a.last,a.created);

    strcpy(a.tx[a.txCount].type,"Deposit");
    a.tx[a.txCount].amount = b;
    strcpy(a.tx[a.txCount].date,a.created);
    a.txCount++;

    bank[totalAccounts] = a;
    totalAccounts++;

    printf("Account created! No: %d\n", a.no);
}

void deposit(){
    int n, i; 
	float amt;
    printf("Account No: "); 
	scanf("%d",&n);
    int found=0;
    for(i=0;i<totalAccounts;i++){
        if(bank[i].no==n){
            printf("Amount to deposit: "); 
			scanf("%f",&amt);
            bank[i].balance += amt;
            today(bank[i].last);
            strcpy(bank[i].tx[bank[i].txCount].type,"Deposit");
            bank[i].tx[bank[i].txCount].amount = amt;
            strcpy(bank[i].tx[bank[i].txCount].date,bank[i].last);
            bank[i].txCount++;
            printf("Deposited %.2f. New Balance: %.2f\n", amt, bank[i].balance);
            found=1; 
			break;
        }
    }
    if(!found) printf("Account not found!\n");
}


void withdraw(){
    int n, i; 
	float amt;
    printf("Account No: "); 
	scanf("%d",&n);
    int found=0;
    for(i=0;i<totalAccounts;i++){
        if(bank[i].no==n){
            printf("Amount to withdraw: "); 
			scanf("%f",&amt);
            if(bank[i].balance - amt < bank[i].min){
                printf("Cannot withdraw! Minimum balance %.2f required.\n", bank[i].min);
            }
            else{
                bank[i].balance -= amt;
                today(bank[i].last);
                strcpy(bank[i].tx[bank[i].txCount].type,"Withdraw");
                bank[i].tx[bank[i].txCount].amount = amt;
                strcpy(bank[i].tx[bank[i].txCount].date, bank[i].last);
                bank[i].txCount++;
                printf("Withdrawn %.2f. New Balance: %.2f\n", amt, bank[i].balance);
            }
            found=1; break;
        }
    }
    if(!found){
        printf("Account not found!\n");	
	}
}


void showAccount(){
    int i, j, n; 
	printf("Account No: "); 
	scanf("%d",&n);
    int found=0;
    for(i=0;i<totalAccounts;i++){
        if(bank[i].no==n){
            printf("\nNo:%d Name:%s Type:%s Balance:%.2f Min:%.2f Rate:%.2f%% Created:%s Last:%s\n", bank[i].no, bank[i].name, bank[i].type, bank[i].balance, bank[i].min, bank[i].rate, bank[i].created, bank[i].last);
            printf("Transactions:\nType        Amount      Date\n---------------------------\n");
            for(j=0;j<bank[i].txCount;j++){
                printf("%-10s %-10.2f %s\n", bank[i].tx[j].type, bank[i].tx[j].amount, bank[i].tx[j].date);
            }
            found=1; 
			break;
        }
    }
    if(!found){
    	printf("Account not found!\n");
	}
}


void showAll(){
	int i;
    if(totalAccounts==0){ 
	    printf("No accounts yet!\n"); 
		return; 
	}
    printf("\nNo   Name           Type         Balance     Min        Rate\n");
    printf("-----------------------------------------------------------\n");
    for(i=0;i<totalAccounts;i++){
        printf("%-4d %-14s %-12s %-10.2f %-10.2f %-5.2f\n", bank[i].no, bank[i].name, bank[i].type, bank[i].balance, bank[i].min, bank[i].rate);
    }
}


int main(){
    int choice;
    while(1){
        printf("\n1.New Account \n2.Deposit \n3.Withdraw \n4.Show Account \n5.Show All \n6.Exit\nChoice: ");
        scanf("%d",&choice);
        if(choice==1){ 
		    newAccount();
		}
        else if(choice==2){ 
		    deposit(); 
		}
        else if(choice==3){ 
		    withdraw(); 
		}
        else if(choice==4){ 
		    showAccount(); 
		}
        else if(choice==5){ 
		    showAll(); 
		}
        else if(choice==6){ 
		    break; 
		}
        else{ 
		    printf("Invalid choice!\n"); 
		}
	}
	
	
    return 0;
}

