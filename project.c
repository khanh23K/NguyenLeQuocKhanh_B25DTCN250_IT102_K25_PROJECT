#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <ctype.h>
#define MAX 100
#define PAGE 6
#define MAX_TIMESHEET 1000
struct Employee {
	char empId[20];
	char name[50];
	char position[15];
	double baseSalary;
	int workDay;
};

struct timeSheet{
	int logId;
	char empId[20];
	char date[20];
	char status[10];
};
	struct timeSheet timeSheets[MAX_TIMESHEET];
	int timeSheetCount = 0;
	struct Employee Employees;
	struct Employee employees[MAX];
int empCount =0 ;
int isValidDate(const char *s) {

    if (strlen(s) != 10) return 0;
    if (s[2] != '/' || s[5] != '/') return 0;

    char ddStr[3], mmStr[3], yyStr[5];
    ddStr[0] = s[0]; ddStr[1] = s[1]; ddStr[2] = '\0';
    mmStr[0] = s[3]; mmStr[1] = s[4]; mmStr[2] = '\0';
    yyStr[0] = s[6]; yyStr[1] = s[7]; yyStr[2] = s[8]; yyStr[3] = s[9]; yyStr[4] = '\0';

    int d = atoi(ddStr);
    int m = atoi(mmStr);
    int y = atoi(yyStr);

    if (d <= 0 || m <= 0 || y <= 0) return 0;
    if (m < 1 || m > 12) return 0;

    int maxDay;
    switch (m) {
        case 1: case 3: case 5: case 7:
        case 8: case 10: case 12:
            maxDay = 31; break;
        case 4: case 6: case 9: case 11:
            maxDay = 30; break;
        case 2:
            maxDay = 29; break;
        default:
            return 0;
    }
    if (d < 1 || d > maxDay) return 0;

    return 1;
}
void printEmployee(const struct Employee *e){
	printf("|%-10s|%-20s|%-16s|%-18.2lf|%-15d|\n",e->empId,e->name,e->position,e->baseSalary,e->workDay);
	printf("+----------+--------------------+----------------+------------------+---------------+\n");
}

void printMenu();
void deleteEmployee();
void addEmployee();
void updateEmployee();
void searchEmployeeByName();
void sortEmployeesBySalary();
void printAllEmployee();
void recordWorkDays();
void defaultEmployee();
void pageEmployeeList();
void viewPersonalTimeSheet();
void indEmployeeIndexById();


int findEmployeeIndexById(struct Employee a[], int n, const char *empId) {
    for (int i = 0; i < n; ++i) {
        if (strcmp(a[i].empId, empId) == 0)
		 return i;
    }
    return -1;
}
int main(){
	int choice;
	char buffer[100];
	defaultEmployee(employees,&empCount);
    while (1) {
    	printMenu();
    	fflush (stdin);
    	printf("Nhap lua chon cua ban:");
    	fgets(buffer,sizeof(buffer),stdin);
    	if(sscanf(buffer,"%d",&choice)!= 1){
    		printf("Khong co lua chon nay.Vui long nhap lai!!!");
    		continue;
		}
	switch(choice){
		case 1:{
			addEmployee(employees,&empCount);
			break;
		}
		case 2:{
			updateEmployee(employees,empCount);
			break;
		}
		case 3:{
			deleteEmployee(employees,&empCount);
			break;
		}
		case 4:{
			pageEmployeeList(employees, empCount);
			break;
		}
		case 5:{
			searchEmployeeByName(employees, empCount);
			break;
		}
		case 6:{
			sortEmployeesBySalary(employees,empCount);
			break;
		}
		case 7:{
			recordWorkDays(employees,empCount);
			break;
		}
		case 8:{
			viewPersonalTimeSheet(employees,&empCount);
			break;
		}
		case 9:{
			printf("                ___________                     ___________       \n");	
			printf("           ___--           --____         ____--           --___  \n");
			printf("          /                      __     __                      \\ \n");
			printf("        /                          _   _                         \\ \n");
			printf("       |                             _                            | \n");
			printf("       |                                                          | \n");
			printf("       |                                                          | \n");
			printf("        \\                                                        / \n");
			printf("          \\                                                    / \n");
			printf("            \\             CAM ON VI DA SU DUNG               / \n");
			printf("              \\                                            / \n");
			printf("                \\                                        / \n");
			printf("                  \\                                    / \n");
			printf("                    \\                                / \n");
			printf("                      \\                            / \n");
			printf("                        \\                        / \n");
			printf("                          \\                    / \n");
			printf("                            \\                / \n");
			printf("                              \\            / \n");
			printf("                                \\        / \n");
			printf("                                  \\    / \n");
			printf("                                    \\/ \n");	
			return 0;
		}
		default:
			printf("Lua chon cua ban ko co.Vui long nhap lai !!!\n");
			break;
	}
}
}
void printMenu(){
		system ("cls");
		printf("\n+--------------MENU QUAN LY NHAN VIEN--------------+\n");
        printf("|%-50s|\n","1. Them nhan vien moi");
        printf("|%-50s|\n","2. Cap nhat ho so nhan vien");
        printf("|%-50s|\n","3. Sa thai/Nghi viec");
        printf("|%-50s|\n","4. Hien thi danh sach nhan vien");
        printf("|%-50s|\n","5. tra cuu thong tin");
        printf("|%-50s|\n","6. sap xep danh sach");
        printf("|%-50s|\n","7. cham cong ngay");
        printf("|%-50s|\n","8. xem bang cong");
        printf("|%-50s|\n","9. Thoat");
        printf("+--------------------------------------------------+\n");
}
void addEmployee(struct Employee a[],int *n){
		if(*n>=MAX){
			printf("Danh sach da day, ko the them!!!\n");
			return ;
		}
	
	while (1){
		printf("Nhap Ma sinh vien: ");
		fgets(Employees.empId, sizeof(Employees.empId),stdin);
		Employees.empId[strcspn(Employees.empId,"\n")]='\0';
		
		if(strlen(Employees.empId)==0){
			printf("Gia tri rong.vui long nhap lai!!!\n");
			continue;
		}
		if (findEmployeeIndexById(a, *n, Employees.empId) != -1){
			printf("ko hop le. Vui long nhap lai!!!\n");
			continue;
		}
		break;
	}
	while (1){
		printf("Nhap ten sinh vien: ");
		fgets(Employees.name, sizeof(Employees.name),stdin);
		Employees.name[strcspn(Employees.name,"\n")]='\0';
		if(strlen(Employees.name)==0){
			printf("Ten ko dc de rong.Vui long nhap lai!!!\n");
			continue;
		}
		break;
	}
	while(1){
	
	printf("Nhap chuc vu cua ban: ");
	fgets(Employees.position, sizeof(Employees.position),stdin);
	Employees.position[strcspn(Employees.position,"\n")]='\0';
	if(strlen(Employees.position == 0)){
		printf("Chuc vu ko dc de rong.Vui long nhap lai!!!\n");
		continue;
	}
	break;
}

	while(1){
	printf("Nhap luong cua ban: ");
	scanf("%lf",&Employees.baseSalary);
	
	
	break;
	}
	
		Employees.workDay =0;
    a[*n] = Employees;
    (*n)++;
	printf(">>>Them nhan vien thanh cong<<<\n");

}






void updateEmployee(struct Employee a[], int n){
	if(n == 0){
		printf("Danh sach trong, khong co gi de cap nhat!\n");
	}
	char empId[20];
	char buffer[100];
	
	printf("Nhap ma sinh vien can cap nhat: ");
	fgets(empId,sizeof(empId),stdin);
	empId[strcspn(empId,"\n")]='\0';
	
 int m = findEmployeeIndexById(a, n, empId);{
	
	if (m == -1){
		printf("Khong tim thay ma sinh vien %s",empId);
		return ;
	}
	struct Employee *Employees = &a[m];
	printf("Thong tin hien tai:\n");
	printf("EmpId              :%s\n",Employees->empId);
	printf("Ten                :%s\n",Employees->name);
	printf("Chuc vu            :%s\n",Employees->position);
	printf("Tien luong cua ban :%.1lf\n",Employees->baseSalary);
	
	
	printf("Nhap chuc vu moi:");
	fgets(buffer,sizeof(buffer),stdin);
	buffer[strcspn(buffer,"\n")]='\0';
	
	if(strlen(buffer) > 0){
		strncpy(Employees->position,buffer,sizeof(Employees->position)-1);
		Employees->position[strcspn(Employees->position,"\n")] = '\0';
	}
	
	printf("Nhap muc luong cua ban moi: ");
    fgets(buffer, sizeof(buffer), stdin);
    double newBaseSalary;
    if (sscanf(buffer, "%lf", &newBaseSalary) == 1 && newBaseSalary > 0) {
        Employees->baseSalary = newBaseSalary;
    }

    printf(">> Cap nhat ho so thanh cong!\n");

}
}






void defaultEmployee(struct Employee employees[], int *empCount){
	  struct Employee EmployeeList[MAX]={
		{"001", "Nguyen Le Quoc Khanh", "QUAN LY",     15000000, 6},
        {"002", "Nguyen Van Binh",   "NHAN VIEN",        9000000, 7},
        {"003", "Le Thi Cao",     "THU KI",        8500000,  7},
        {"004", "Pham Thi Duyen",   "QUAN LY",  12000000, 11},
        {"005", "Hoang Van Em",  "BAO VE",        7000000, 12},
        {"006", "Vu Thi Phuong",     "LE TAN", 8000000,  8},
        {"007", "Nguyen Van Giang", "NHAN VIEN",        9500000, 10},
        {"008", "Tran Thi Huyen",   "TUYEN DUNG",          11000000, 12},
        {"009", "Le Van Inh",     "LAI XE",       7500000,  9},
        {"010", "Pham Thi Khang",   "LAO CONG",      6000000, 12},
        {"011", "Le Thi Lan",     "NHAN VIEN",        9000000, 10},
        {"012", "Nguyen Van Minh", "QUAN LY",     16000000, 11},
        {"013", "Tran Thi Nguyen",   "QUAN LY",  12500000, 12},
        {"014", "Hoang Van Phuc",  "NHAN VIEN",        8800000,  9},
        {"015", "Vu Thi Quyen",     "PHUC VU", 8200000, 10},
        {"016","Nguyen Cao Cuong","NHAN VIEN",7200000,12}
};
 int size = 16;
 for (int i = 0; i < size && *empCount < MAX; i++) {
        employees[(*empCount)++] = EmployeeList[i];
    }
    
}
void printAllEmployee(struct Employee a[],int n){
	if(n == 0){
		printf("Chua co ho so nao!!!\n");
		return;
	}
	printf("+----------+--------------------+----------------+------------------+---------------+\n");
	printf("|%-10s|%-20s|%-16s|%-18s|%-15s|\n","EmpId","Ten","Chuc vu","Tien luong cua ban","Ngay cong");
	printf("+----------+--------------------+----------------+------------------+---------------+\n");
	for(int i=0;i<n;i++){
		printEmployee(&a[i]);
	}
	
	fflush(stdin);
	getchar ();
	
}






void pageEmployeeList(struct Employee a[], int n) {
    if (n == 0) {
        printf("\nKhong co Nhan vien nao ca!!!\n");
        printf("Nhan phim bat ky de quay lai menu...");
        getchar();
        system("cls");
        return;
    }

    int page = 1; 
    int totalPage = (n + PAGE - 1) / PAGE;
    char input[20];

    while (1) {
        system("cls");
        int start = (page - 1) * PAGE;
        int end = start + PAGE;
        if (end > n) end = n;

        printf("+-----------------------------------------------------------------------------------+\n");
        printf("|                           DANH SACH NHAN VIEN (Page %d / %d)                          |\n",
               page + 1, totalPage);
        printf("+----------+--------------------+----------------+------------------+---------------+\n");
        printf("|%-10s|%-20s|%-16s|%-18s|%-15s|\n",
               "EmpId","Ten","Chuc vu","Tien luong","Ngay cong");
        printf("+----------+--------------------+----------------+------------------+---------------+\n");

        for (int i = start; i < end; i++) {
            printf("|%-10s|%-20s|%-16s|%-18.0lf|%-15d|\n",
                   a[i].empId, a[i].name, a[i].position,
                   a[i].baseSalary, a[i].workDay);
        }

        printf("+-----------------------------------------------------------------------------------+\n");
        printf("Nhap so trang (1-%d), n = Next, p = Prev, q = Thoat\n", totalPage);
        printf("Lua chon: ");
        fgets(input, sizeof(input), stdin);
        if (input[0] == 'q' || input[0] == 'Q') {
            system("cls");
            return;
	}
        if (input[0] == 'n' || input[0] == 'N') {
            if (page < totalPage) page++;
            continue;
			}    
        if (input[0] == 'p' || input[0] == 'P') {
            if (page > 1) page--;
            continue;
        }
        if (isdigit(input[0])) {
            int newPage = atoi(input);
            if (newPage >= 1 && newPage <= totalPage) {
                page = newPage;
            } else {
                printf("Trang khong hop le!\n");
                printf("Nhan Enter de tiep tuc...");
                getchar();
            }
        }
    }
}





void deleteEmployee(struct Employee a[], int *n){
	if(*n == 0){
		printf("Chua co ho so nhan vien!!!");
		return;
	}
	char empId[20];
	char buffer[100];
	while (1) {
        printf("Nhap ma nhan vien can xoa: ");
        fgets(empId, sizeof(empId), stdin);
        empId[strcspn(empId,"\n")]='\0';

        if (strlen(empId) == 0) {
            printf(" Ma nhan vien khong duoc rong. Vui long nhap lai!\n");
            continue;
        }
        break;
    }

    int m = findEmployeeIndexById(a, *n, empId);
    if (m == -1) {
        printf(" Nhan vien khong ton tai!\n");
        return;
    }
    printf("Ban co muon XOA nhan vien nay hay ko (y/n): ");
    fgets(buffer,sizeof(buffer),stdin);
    buffer[strcspn(buffer,"\n")]=0;
    
    if(buffer[0]!='y'&& buffer[0]!='Y'){
    	printf("Da huy bo XOA nhan vien");
    		return;
	}

    for (int i = m; i < *n - 1; i++) {
        a[i] = a[i + 1];
    }

    (*n)--;

    printf(">>> Da xoa nhan vien thanh cong! <<<\n");

}





void searchEmployeeByName(struct Employee a[],int n ){
	if(n == 0){
		printf("Khong tim thay nhan vien nay!!! ");
		return;
	}
	char name[50];
	int found=0;
	
	printf("Nhap ten nhan vien can tra cuu: ");
	fgets(name,sizeof(name),stdin);
	name[strcspn(name,"\n")];
	
	if(strlen(name) == 0){
		printf("Ten nhan vien can tra cuu: ");
		return;
	}
	printf("\nKet qua tra cuu theo ten %s",name);
	printf("\n+----------+--------------------+----------------+------------------+---------------+\n");
	printf("|%-10s|%-20s|%-16s|%-18s|%-15s|\n","EmpId","Ten","Chuc vu","Tien luong cua ban","Ngay cong");
	printf("+----------+--------------------+----------------+------------------+---------------+\n");
	
		for(int i=0;i<n;i++){
			if(strstr (a[i].name, name)!= NULL){
				printEmployee(&a[i]);
				found = 1;		
			}
		}
		if(!found){
			printf("Khong tim thay nhan vien nao co ten chua \"%s\".\n", name);
		}
}




void sortEmployeesBySalary(struct Employee a[],int n){
	if(n==0){
		printf("Danh sach nhan vien rong!!!");
	}
		int choice;
		char buffer[10];
		printf("Chon lua chon kieu sap xep:\n");
		printf("1. sap xep tang dan.\n");
		printf("2. sap xep giam dan.\n");
		fgets(buffer,sizeof(buffer),stdin);
		buffer[strcspn(buffer,"\n")]='\0';
		
		if(sscanf(buffer,"%d",&choice)!= 1 || (choice != 1 && choice != 2)){
			printf("Lua chon khong hop ly");
			return ;
		}	
			for(int i=0;i<n-1;i++){
			for(int j=0;j<n-1-i;j++){
			int condition = 0;
            if (choice == 1) {
                condition = (a[j].baseSalary > a[j + 1].baseSalary);
            } else {
                condition = (a[j].baseSalary < a[j + 1].baseSalary);
            }
            if (condition) {
                struct Employee tmp = a[j];
                a[j] = a[j + 1];
                a[j + 1] = tmp;
            }
        }
    }
    printf("Da sap xep danh sach nhan vien theo luong.\n");
   	printAllEmployee(a,n);
}





int getDaysInMonth(int month, int year) {
    if (month < 1 || month > 12) return 0;

    switch (month) {
        case 1: case 3: case 5: case 7:
        case 8: case 10: case 12:
            return 31;
        case 4: case 6: case 9: case 11:
            return 30;
        case 2: {
            int isLeap = ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0));
            return isLeap ? 29 : 28;
        }
        default:
            return 0;
    }
}



void recordWorkDays(struct Employee a[], int n) {
    if (n == 0) {
        printf("Danh sach nhan vien rong, khong the cham cong.\n");
        return;
    }

    char empId[20];
    char date[20];

    printf("Nhap ma nhan vien can cham cong: ");
    fgets(empId, sizeof(empId), stdin);
    empId[strcspn(empId,"\n")]='\0';

    if (strlen(empId) == 0) {
        printf(">> Ma nhan vien khong duoc rong.\n");
        return;
    }

    int m = findEmployeeIndexById(a, n, empId);
    if (m == -1) {
        printf(">> Khong tim thay nhan vien co ma %s.\n", empId);
        return;
    }

    printf("Nhap ngay cham cong (dd/mm/yyyy): ");
    fgets(date, sizeof(date), stdin);
    date[strcspn(date,"\n")]='\0';

    a[m].workDay++;

    strcpy(timeSheets[timeSheetCount].empId, empId);
    strcpy(timeSheets[timeSheetCount].date, date);
    timeSheetCount++;

    printf(">> Cham cong thanh cong!\n");
}




void viewPersonalTimeSheet(struct Employee a[], int n) {
    if (n == 0) {
        printf("Danh sach nhan vien rong, khong co bang cong de xem.\n");
        return;
    }

    if (timeSheetCount == 0) {
        printf("Chua co du lieu cham cong nao trong he thong.\n");
        return;
    }

    char empId[20];
    char buffer[32];
    int month, year;

    
    printf("Nhap ma nhan vien can xem bang cong: ");
    fgets(empId, sizeof(empId), stdin);
    empId[strcspn(empId,"\n")]='\0';
    if (strlen(empId) == 0) {
        printf(">> Ma nhan vien khong duoc rong.\n");
        return;
    }

    int idx = findEmployeeIndexById(a, n, empId);
    if (idx == -1) {
        printf(">> Khong tim thay nhan vien co ma %s trong danh sach.\n", empId);
        return;
    }

    
    while (1) {
        printf("Nhap THANG can xem (1-12): ");
        fgets(buffer, sizeof(buffer), stdin);
        if (sscanf(buffer, "%d", &month) != 1 || month < 1 || month > 12) {
            printf(">> Thang khong hop le. Vui long nhap lai!\n");
            continue;
        }
        break;
    }

  
    while (1) {
        printf("Nhap NAM can xem (VD: 2025): ");
        fgets(buffer, sizeof(buffer), stdin);
        if (sscanf(buffer, "%d", &year) != 1 || year < 1900 || year > 2100) {
            printf(">> Nam khong hop le. Vui long nhap lai!\n");
            continue;
        }
        break;
    }

    int daysInMonth = getDaysInMonth(month, year);
    if (daysInMonth == 0) {
        printf(">> Thang/nam khong hop le.\n");
        return;
    }

    int worked[32] = {0};   
    for (int i = 0; i < timeSheetCount; ++i) {
        if (strcmp(timeSheets[i].empId, empId) != 0) continue;

        int d, m, y;
        if (sscanf(timeSheets[i].date, "%d/%d/%d", &d, &m, &y) == 3) {
            if (m == month && y == year && d >= 1 && d <= daysInMonth) {
                worked[d] = 1;  
            }
        }
    }
int isDuplicatedTimeSheet(const char *empId, const char *date) {
    for (int i = 0; i < timeSheetCount; ++i) {
        if (strcmp(timeSheets[i].empId, empId) == 0 &&
            strcmp(timeSheets[i].date, date) == 0) {
            return 1; 
        }
    }
    return 0;
}

   
    system("cls");

    printf("=========== BANG CONG CA NHAN THANG %02d/%04d ===========\n",
           month, year);
    printf("Ma NV : %s\n", empId);
    printf("Ten   : %s\n", a[idx].name);
    printf("Chuc vu: %s\n", a[idx].position);
    printf("---------------------------------------------------------\n");
    printf("%-12s | %-10s\n", "Ngay", "Trang thai");
    printf("---------------------------------------------------------\n");

    int totalWork = 0;
    for (int d = 1; d <= daysInMonth; ++d) {
        const char *status = worked[d] ? "Di lam" : "Nghi";
        if (worked[d]) totalWork++;

        printf("%02d/%02d/%04d | %-10s\n", d, month, year, status);
    }

    int totalOff = daysInMonth - totalWork;
    printf("---------------------------------------------------------\n");
    printf("Tong ngay di lam : %d\n", totalWork);
    printf("Tong ngay nghi   : %d\n", totalOff);
    printf("---------------------------------------------------------\n");
    printf("Nhan phim bat ky de quay ve menu...");
    getchar();
    system("cls");
}

