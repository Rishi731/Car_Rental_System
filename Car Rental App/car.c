#include "car.h"
#include <stdio.h>
#include <string.h>
#include "conio2.h"

void addAdmin(){

    FILE *fp = fopen("admin.bin","rb");

    if(fp == NULL){

        fp = fopen("admin.bin","wb");
        User u[2] = {{"admin","abc","lok"},{"super","abc","loken"}};
        fwrite(u,sizeof(u),1,fp);
    }

    fclose(fp);
}

User * getInput(){
    int i;
    static User u;
    clrscr();
    gotoxy(32,1);
    textcolor(YELLOW);
    printf("CAR RENTAL SYSTEM\n");
    for(i=1;i<=80;i++){
        printf("%c",247);
    }
    gotoxy(32,4);
    printf("* LOGIN PANEL *");
    gotoxy(1,7);
    textcolor(LIGHTCYAN);

    for(i=1;i<=80;i++){
        printf("%c",247);
    }

    gotoxy(1,15);

    for(i=1;i<=80;i++){
        printf("%c",247);
    }

    gotoxy(60,8);

    textcolor(WHITE);
    printf("Press 0 to exit");

    gotoxy(25,10);

    textcolor(LIGHTCYAN);
    printf("Enter user id :");
    fflush(stdin);
    textcolor(WHITE);
    fgets(u.userid,20,stdin);
    char *pos;

    pos = strchr(u.userid,'\n');
    if(pos != NULL){
        *pos = '\0';
    }

    if((strcmp(u.userid,"0"))==0){
        textcolor(LIGHTRED);
        gotoxy(30,17);
        printf("Login Cancelled !");
        fflush(stdin);
        getch();
        return NULL;
    }

    gotoxy(25,11);
    textcolor(LIGHTCYAN);
    printf("Enter Password :");
    fflush(stdin);
    i = 0;
    for(;;){
        u.pwd[i] = getch();

        if(u.pwd[i] == 13){
            u.pwd[i] = '\0';
            break;
        }

        if(u.pwd[i]==8){
            i-=1;
            printf("\b \b");
            continue;
        }
        else{
            printf("*");
            i++;
        }
    }


    if((strcmp(u.pwd,"0"))==0){
        textcolor(LIGHTRED);
        gotoxy(30,17);
        printf("Login Cancelled !");
        fflush(stdin);
        getch();
        textcolor(YELLOW);
        return NULL;
    }

    return &u;
}


int checkUserExist(User u,char * usertype){

    if(strlen(u.userid)==0 || strlen(u.pwd)==0){
        textcolor(LIGHTRED);
        gotoxy(28,20);
        printf("Both fields are Mandatory. Try Again !");
        getch();
        gotoxy(28,20);
        printf("\t\t\t\t\t\t");
        return 0;
    }

    FILE *fp;

    if( (strcmp(usertype,"admin"))==0 ){
        fp=fopen("admin.bin","rb");
    }else{
        fp=fopen("emp.bin","rb");
    }
    if(fp == NULL){
        gotoxy(28,20);
        textcolor(LIGHTRED);
        printf("Sorry ! cannot open the file");
        getch();
        gotoxy(28,20);
        printf("\t\t\t\t\t");
        return -1;
    }

    int found = 0;
    User user;

    while(fread(&user,sizeof(user),1,fp) == 1){

        if((strcmp(u.userid,user.userid) == 0) && (strcmp(u.pwd,user.pwd) == 0)){
            found = 1;
            break;
        }
    }

    if(found == 0){
        gotoxy(28,20);
        textcolor(LIGHTRED);
        printf("Invalid userid/password . Try Again");
        getch();
        gotoxy(28,20);
        printf("\t\t\t\t\t\t");
    }else{
        gotoxy(28,20);
        textcolor(LIGHTGREEN);
        printf("Login successful !");
        getch();
        gotoxy(28,20);
        printf("\t\t\t\t\t\t");
    }

    fclose(fp);
    return found;
}

int adminMenu(){
    int i,choice;
    textcolor(LIGHTRED);
    gotoxy(32,2);
    printf("CAR RENTAL SYSTEM");
    textcolor(LIGHTGREEN);
    gotoxy(35,6);
    printf("ADMIN MENU\n");
    for(i = 1; i<= 80 ; i++){
        printf("*");
    }
    textcolor(YELLOW);
    gotoxy(32,8);
    printf("1. Add Employee");
    gotoxy(32,9);
    printf("2. Add Car Details");
    gotoxy(32,10);
    printf("3. Show Employee");
    gotoxy(32,11);
    printf("4. Show Car Details");
    gotoxy(32,12);
    printf("5. Delete Employee");
    gotoxy(32,13);
    printf("6. Delete Car Details");
    gotoxy(32,14);
    printf("7. Exit");
    gotoxy(32,16);
    printf("Enter Choice : ");
    scanf("%d",&choice);
    return choice;
}
void addEmployee()
{
    char empid[10] ={"EMP-"};
    char temp[20];
    char choice;
    char *pos;
    User u;
    FILE *fp = fopen("emp.bin","ab+");
    fseek(fp,0,SEEK_END);
    long total_rec = ftell(fp)/sizeof(User);

    if(total_rec != 0){
        fseek(fp,-60,SEEK_END);
        fread(temp,sizeof(temp),1,fp);
        pos = strchr(temp,'-');
        total_rec = atoi(pos+1);
    }

    total_rec++;
    sprintf(temp,"%d",total_rec);
    strcat(empid,temp);
    strcpy(u.userid,empid);
    fseek(fp,0,SEEK_END);
    do{
        clrscr();
        int i;
        textcolor(LIGHTRED);
        gotoxy(32,2);
        printf("CAR RENTAL APP");
        gotoxy(1,3);
        textcolor(LIGHTGREEN);
        for(i = 1; i <= 80 ; i++)
            printf("~");
        gotoxy(25,5);
        textcolor(WHITE);
        printf("***** ADD EMPLOYEE DETAILS *****");
        gotoxy(1,8);
        textcolor(YELLOW);
        printf("Enter Employee Name :");
        fflush(stdin);
        fgets(u.name,20,stdin);

        pos =strchr(u.name,'\n');
        if(pos != NULL){
            *pos = '\0';
        }
        textcolor(YELLOW);
        printf("Enter Employee Pwd :");
        fflush(stdin);
        textcolor(WHITE);
        fgets(u.pwd,20,stdin);
        pos = strchr(u.pwd,'\n');
        if(pos != NULL){
            *pos = '\0';
        }
        fwrite(&u,sizeof(u),1,fp);
        gotoxy(30,15);
        textcolor(LIGHTGREEN);
        printf("EMPLOYEE ADDED SUCCESSFULLY !!!");
        printf("\nEMPLOYEE ID is %s",u.userid);
        getch();
        textcolor(LIGHTRED);
        gotoxy(1,20);
        printf("Do you want to add more employees (Y/N)?");
        textcolor(WHITE);
        fflush(stdin);
        scanf("%c",&choice);
        if(choice == 'N' || choice == 'n')
            break;
        total_rec++;
        sprintf(u.userid,"EMP-%d",total_rec);
    }while(1);
    fclose(fp);
}

void addCarDetails()
{
    FILE * fp = fopen("car.bin","ab+");
    Car c;
    long total_car;

    if(fp == NULL){
    }

    fseek(fp,0,SEEK_END);
    total_car = ftell(fp)/sizeof(c);


    int last_car_id;

    if(total_car != 0){
        fseek(fp,-68,SEEK_END);
        fread(&c,sizeof(c),1,fp);
        last_car_id = c.car_id;
        total_car = last_car_id;
    }

    total_car++;

    do{
        int i;
        char ch;
        clrscr();
        c.car_id = total_car;

        gotoxy(32,2);
        textcolor(LIGHTRED);
        printf("CAR RENTAL APP\n");

        textcolor(LIGHTGREEN);
        for( i = 1 ; i<= 80 ; i++)
            printf("~");

        gotoxy(25,5);
        textcolor(WHITE);
        printf("***** ADD CAR DETAILS *****");
        gotoxy(1,8);
        textcolor(YELLOW);
        printf("Enter Car Model : ");
        fflush(stdin);
        textcolor(WHITE);

        fgets(&c.car_name,50,stdin);
        char *pos;
        pos = strchr(c.car_name,'\n');
        if(pos != NULL){
            pos == '\0';

        }

        textcolor(YELLOW);
        printf("Enter Car Capicity : ");
        textcolor(WHITE);
        scanf("%d",&c.capacity);

        textcolor(YELLOW);
        printf("Enter Car Count : ");
        textcolor(WHITE);
        scanf("%d",&c.car_count);

        textcolor(YELLOW);
        printf("Enter Car Price for per Day : ");
        textcolor(WHITE);
        scanf("%d",&c.price);

        textcolor(LIGHTGREEN);
        gotoxy(30,15);
        printf("CAR ADD SUCCESSFULLY");
        printf("\nCAR ID IS : %d",c.car_id);

        gotoxy(1,20);
        textcolor(LIGHTRED);

        fseek(fp,0,SEEK_END);
        fwrite(&c,sizeof(c),1,fp);

        printf("DO YOU WANT TO ADD MORE CAR (Y/N) : ");
        fflush(stdin);
        scanf("%c",&ch);
        if(ch == 'N' || ch == 'n')
            break;

        total_car++;
    }while(1);

    fclose(fp);
}

void viewEmployee(){
    clrscr();
    int i,row;

    textcolor(YELLOW);
    gotoxy(32,1);
    printf("CAR RENTAL SYSTEM");

    gotoxy(1,2);
    for(i=1;i<=80;i++)
        printf("%c",247);

    gotoxy(31,5);
    printf("* EMPLOYEE DETAILS *");

    textcolor(LIGHTGREEN);
    gotoxy(1,7);
    for(i=1;i<=80;i++)
        printf("%c",247);

    FILE * fp = fopen("emp.bin","rb");

    if(fp == NULL){
        gotoxy(27,9);
        textcolor(LIGHTRED);
        printf("Sorry ! No Employee added yet.");
        getch();
        return;
    }

    printf("Employee ID\t\t\tName\t\t\tPassword");

    gotoxy(1,9);
    for(i=1;i<=80;i++)
        printf("%c",247);

    User u;
    row = 10;
    fseek(fp,0,SEEK_SET);
    while(fread(&u,sizeof(u),1,fp)==1){
        gotoxy(1,row);
        printf("%s",u.userid);
        gotoxy(33,row);
        printf("%s",u.name);
        gotoxy(57,row);
        printf("%s",u.pwd);
        row++;
    }
    fclose(fp);
    getch();
}

void showCarDetails(){
    clrscr();
    int i,row;
    textcolor(YELLOW);
    gotoxy(32,1);
    printf("CAR RENTAL SYSTEM");

    gotoxy(1,2);
    for(i=1;i<=80;i++)
        printf("%c",247);

    gotoxy(31,5);
    printf("* ALL CAR DETAILS *");

    textcolor(LIGHTGREEN);
    gotoxy(1,7);
    for(i=1;i<=80;i++)
        printf("%c",247);

    FILE * fp = fopen("car.bin","rb");
    if(fp == NULL){
        gotoxy(27,11);
        textcolor(LIGHTRED);
        printf("Sorry ! No Car added yet.");
        getch();
        return;
    }

    printf("CAR ID\t\tModel\t\tCapicity\tAvailable\tPrice/Day");

    gotoxy(1,9);
    for(i=1;i<=80;i++)
        printf("%c",247);

    Car c;
    row = 10;
    fseek(fp,0,SEEK_SET);
    while(fread(&c,sizeof(c),1,fp)==1){
        gotoxy(1,row);
        printf("%d",c.car_id);
        gotoxy(17,row);
        printf("%s",c.car_name);
        gotoxy(33,row);
        printf("%d",c.capacity);
        gotoxy(49,row);
        printf("%d",c.car_count);
        gotoxy(65,row);
        printf("%d",c.price);
        row++;
    }
    fclose(fp);
    getch();
}

int deleteEmp()
{
    FILE *fp1 = fopen("emp.bin","rb");
    int i,result;
    char empid[20];
    textcolor(YELLOW);
    gotoxy(32,1);
    printf("CAR RENTAL SYSTEM");

    gotoxy(1,2);
    for(i = 1 ; i <= 80 ; i++)
        printf("%c",247);

    gotoxy(27,5);
    printf("* DELETE EMPLOYEE RECORD *");

    textcolor(LIGHTGREEN);
    gotoxy(1,7);
    for(i = 1; i<= 80 ; i++)
        printf("%c",247);

    gotoxy(1,12);
    for( i = 1 ; i <= 80 ; i++)
        printf("%c",247);

    if(fp1 == NULL){
        textcolor(LIGHTRED);
        gotoxy(30,9);
        printf("No Employee Added Yet!");
        return -1;
    }
    FILE *fp2 = fopen("temp.bin","wb+");
    gotoxy(10,9);
    textcolor(YELLOW);
    printf("Enter Employee Id to delete the record :");
    textcolor(WHITE);
    fflush(stdin);
    scanf("%s",empid);
    User u;
    int found = 0;
    while(fread(&u,sizeof(u),1,fp1) == 1){
        if(strcmp(u.userid,empid) != 0)
            fwrite(&u,sizeof(u),1,fp2);
        else
            found = 1;
    }
    fclose(fp1);
    fclose(fp2);
    if(found == 0)
        remove("temp.bin");
    else{
        result = remove("emp.bin");
        if(result != 0 )
            return 2;
        result = rename("temp.bin","emp.bin");
        if(result != 0)
            return 2;
    }
    return found;
}

int deleteCarModel()
{
    FILE *fp1 = fopen("car.bin","rb");
    int i,result;
    int carid;
    textcolor(YELLOW);
    gotoxy(32,1);
    printf("CAR RENTAL SYSTEM");

    gotoxy(1,2);
    for(i = 1 ; i <= 80 ; i++)
        printf("%c",247);

    gotoxy(29,5);
    printf("* DELETE CAR MODEL *");

    textcolor(LIGHTGREEN);
    gotoxy(1,7);
    for(i = 1; i<= 80 ; i++)
        printf("%c",247);

    gotoxy(1,12);
    for( i = 1 ; i <= 80 ; i++)
        printf("%c",247);

    if(fp1 == NULL){
        textcolor(LIGHTRED);
        gotoxy(32,9);
        printf("No Car Added Yet!");
        return -1;
    }

    FILE *fp2 = fopen("temp.bin","wb+");

    gotoxy(10,9);
    textcolor(YELLOW);
    printf("Enter Car Id to delete the record :");
    textcolor(WHITE);
    scanf("%d",&carid);
    Car c;

    int found = 0;

    while(fread(&c,sizeof(c),1,fp1) == 1){

        if(carid != c.car_id)
            fwrite(&c,sizeof(c),1,fp2);
        else
            found = 1;
    }
    fclose(fp1);
    fclose(fp2);

    if(found == 0)
        remove("temp.bin");
    else{
        result = remove("car.bin");
        if(result != 0 )
            return 2;
        result = rename("temp.bin","car.bin");
        if(result != 0)
            return 2;
    }
    return found;
}

int empMenu()
{
    int choice,i;
    textcolor(LIGHTRED);
    gotoxy(32,2);
    printf("CAR RENTAL SYSTEM");

    textcolor(LIGHTGREEN);
    gotoxy(34,6);
    printf("EMPLOYEE MENU\n");

    for(i = 1 ; i <= 80 ; i++)
        printf("*");

    gotoxy(32,8);
    printf("1. Rent A CAR");

    gotoxy(32,9);
    printf("2. Booking Details");

    gotoxy(32,10);
    printf("3. Available Car Details");

    gotoxy(32,11);
    printf("4. Show All Car Details");

    gotoxy(32,12);
    printf("5. Exit");

    gotoxy(32,15);
    printf("Enter Choice : ");
    scanf("%d",&choice);

    return choice;
}

int selectCarModel()
{
    FILE *fp = fopen("car.bin","rb");
    int flag;
    int choice,rowno = 9;
    Car C;

    gotoxy(34,rowno);
    int carcount = 0;
    while(fread(&C,sizeof(C),1,fp) == 1){
        if(C.car_count > 0)
        {
            printf("%d . %s",C.car_id,C.car_name);
            gotoxy(34,++rowno);
            ++carcount;
        }
    }

    if(carcount == 0)
        return -2;

    gotoxy(34,rowno + 2);
    printf("Enter Your Choice(0 to quit) : ");

    while(1)
    {
        flag = 0;
        scanf("%d",&choice);
        if(choice == 0)
        {
            fclose(fp);
            return 0;
        }
        rewind(fp);

        while(fread(&C,sizeof(C),1,fp) == 1)
        {
            if(C.car_id == choice && C.car_count > 0)
            {
                flag = 1;
                break;
            }
        }
        if(flag == 1)
        {
            fclose(fp);
            return flag;
        }

        gotoxy(37,rowno + 4);
        textcolor(LIGHTRED);
        printf("Wrong Input");
        getch();

        gotoxy(37,rowno + 4);
        printf("\t\t\t");

        gotoxy(53,rowno + 2);
        printf("\t\t\t");

        gotoxy(53,rowno + 2);
        textcolor(WHITE);
    }
}

char * getCarName(int c_id)
{
    FILE * fp = fopen("car.bin","rb");
    if(fp==NULL)
    {
        printf("Sorry ! File cannot be opened");
        return NULL;
    }
    static Car C;
    while(fread(&C,sizeof(C),1,fp) == 1)
    {
        if(C.car_id == c_id)
        {
            break;
        }
        fclose(fp);
    }
    return C.car_name;
}

int isValidDate(struct tm dt)
{
    if(dt.tm_year >= 2021 && dt.tm_year <= 2022)
    {
        if(dt.tm_mon >= 1 && dt.tm_mon <=12)
        {
            if((dt.tm_mday >= 1 && dt.tm_mday <= 31) && (dt.tm_mon == 1 || dt.tm_mon == 3 || dt.tm_mon == 5 || dt.tm_mon == 7 || dt.tm_mon == 8 || dt.tm_mon == 10 || dt.tm_mon == 12))
            {
                return 1;
            }
            else if((dt.tm_mday >= 1 && dt.tm_mday <= 30) && (dt.tm_mon == 4 || dt.tm_mon == 6 || dt.tm_mon == 9 || dt.tm_mon == 11))
            {
                return 1;
            }
            else if((dt.tm_mday >= 1 && dt.tm_mday <= 28) && (dt.tm_mon == 2 ))
            {
                return 1;
            }
            else if((dt.tm_mday >= 1 && dt.tm_mday <= 29) && (dt.tm_mon == 2) && (dt.tm_year % 400 ||(dt.tm_year % 4==0 && dt.tm_year % 100 != 0)))
            {
                return 1;
            }
        }
    }
    return 0;
}

int rentCar()
{
    Customer_Car_Details CC;
    int c,i;

    return_car();
    return_car_delete();

    textcolor(LIGHTRED);
    gotoxy(32,2);

    printf("CAR RENTAL SYSTEM\n");
    textcolor(LIGHTGREEN);

    gotoxy(35,6);
    printf("EMPLOYEE MENU\n");

    for(i = 1; i <= 80 ; i++)
        printf("*");

    textcolor(YELLOW);
    gotoxy(32,8);

    c = selectCarModel();
    if(c == 0)
        return 0;
    clrscr();
    CC.car_id = c;

    textcolor(LIGHTRED);
    gotoxy(32,2);
    printf("CAR RENTAL SYSTEM\n");

    textcolor(LIGHTGREEN);
    gotoxy(35,6);
    printf("EMPLOYEE MENU\n");

    for(i = 1; i <= 80 ; i++)
        printf("*");

    gotoxy(1,17);
    textcolor(YELLOW);

    gotoxy(27,9);
    printf("Enter Customer Name:");
    fflush(stdin);
    textcolor(WHITE);
    fgets(CC.cust_name,30,stdin);
    char *pos;
    pos = strchr(CC.cust_name,'\n');
    if(pos != NULL)
        *pos = '\0';
    textcolor(YELLOW);

    gotoxy(27,10);
    printf("Enter Pickup Point:");
    textcolor(WHITE);
    fgets(CC.pickup,30,stdin);
    pos = strchr(CC.pickup,'\n');
    if(pos != NULL)
        *pos = '\0';

    textcolor(YELLOW);
    gotoxy(27,11);
    printf("Enter drop point:");
    textcolor(WHITE);
     fgets(CC.drop,30,stdin);
    pos = strchr(CC.drop,'\n');
    if(pos != NULL)
        *pos = '\0';

    gotoxy(27,12);
    textcolor(YELLOW);
    printf("Enter start date(dd/mm/yyyy):");
    textcolor(WHITE);
    do
    {
        scanf("%d %d %d",&CC.sd.tm_mday,&CC.sd.tm_mon,&CC.sd.tm_year);
        int datevalid = isValidDate(CC.sd);
        if(datevalid == 1)
            break;
        gotoxy(27,18);
        textcolor(LIGHTRED);
        printf("Wrong Date!");
        getch();
        gotoxy(27,18);
        printf("\t\t\t");
        gotoxy(56,12);
        printf("\t\t\t");
        gotoxy(56,12);
        textcolor(WHITE);
    }while(1);

    textcolor(YELLOW);
    gotoxy(27,13);
    printf("Enter end date(dd/mm/yyyy):");
    textcolor(WHITE);
    do
    {
        scanf("%d %d %d",&CC.ed.tm_mday,&CC.ed.tm_mon,&CC.ed.tm_year);
        int datevalid = isValidDate(CC.sd);
        if(datevalid == 1)
            break;
        gotoxy(27,18);
        textcolor(LIGHTRED);
        printf("Wrong Date!");
        getch();
        gotoxy(27,18);
        printf("\t\t\t");
        gotoxy(54,13);
        printf("\t\t\t");
        gotoxy(54,13);
        textcolor(WHITE);
    }while(1);

    int valid = checkDate(CC.sd,CC.ed);
    if(valid != 1)
    {
        while(valid != 1)
        {
            gotoxy(20,22);
            textcolor(LIGHTRED);
            printf("!!!  Booked Date must be Greater Than Current Date  !!!");
            gotoxy(23,23);
            printf("!!!  End Date must be Greater Than Start Date  !!!");
            getch();

            gotoxy(20,22);
            printf("\t\t\t\t\t\t\t\t\t");

            gotoxy(23,23);
            printf("\t\t\t\t\t\t\t\t\t");

            gotoxy(27,12);
            printf("\t\t\t\t\t");

            gotoxy(27,13);
            printf("\t\t\t\t\t");

            gotoxy(27,12);
            textcolor(YELLOW);
            printf("Enter start date(dd/mm/yyyy):");
            textcolor(WHITE);
            do
            {
                scanf("%d %d %d",&CC.sd.tm_mday,&CC.sd.tm_mon,&CC.sd.tm_year);
                int datevalid = isValidDate(CC.sd);
                if(datevalid == 1)
                    break;
                gotoxy(27,18);
                textcolor(LIGHTRED);
                printf("Wrong Date!");
                getch();
                gotoxy(27,18);
                printf("\t\t\t");
                gotoxy(56,12);
                printf("\t\t\t");
                gotoxy(56,12);
                textcolor(WHITE);
            }while(1);

            textcolor(YELLOW);
            gotoxy(27,13);
            printf("Enter end date(dd/mm/yyyy):");
            textcolor(WHITE);
            do
            {
                scanf("%d %d %d",&CC.ed.tm_mday,&CC.ed.tm_mon,&CC.ed.tm_year);
                int datevalid = isValidDate(CC.sd);
                if(datevalid == 1)
                    break;
                gotoxy(27,18);
                textcolor(LIGHTRED);
                printf("Wrong Date!");
                getch();
                gotoxy(27,18);
                printf("\t\t\t");
                gotoxy(54,13);
                printf("\t\t\t");
                gotoxy(54,13);
                textcolor(WHITE);
            }while(1);

            valid = checkDate(CC.sd,CC.ed);
        }
    }


    FILE *fp;
    fp = fopen("customer.bin","ab");
    if(fp == NULL)
    {
        gotoxy(27,18);
        printf("Sorry! File cannot be opened");
        return -1;
    }
    fwrite(&CC,sizeof(Customer_Car_Details),1,fp);
    gotoxy(27,18);
    textcolor(WHITE);
    printf("Booking Done!");
    printf("\nPress any key to continue");
    getch();
    updateCarCount(CC.car_id);
    fclose(fp);
    return 1;
}

void availCarDetails()
{
    return_car();
    return_car_delete();
    clrscr();
    FILE * fp = fopen("car.bin","rb");
    Car C;
    int i;
    textcolor(YELLOW);
    gotoxy(32,1);
    printf("CAR RENTAL SYSTEM\n");
    textcolor(LIGHTGREEN);
    for(i = 1 ; i<= 80; i++)
        printf("%c",247);
    gotoxy(32,5);
    textcolor(YELLOW);
    printf("* AVAILABLE CAR DETAILS *");
    gotoxy(1,7);
    textcolor(LIGHTGREEN);
    for ( i = 1; i <= 80; i++)
        printf("%c",247);
    if(fp == NULL)
    {
        gotoxy(32,8);
        textcolor(LIGHTRED);
        printf("Sorry! File cannot be opened!");
        getch();
        return;
    }
    gotoxy(1,8);
    printf("Car ID");
    gotoxy(15,8);
    printf("Model");
    gotoxy(35,8);
    printf("Capacity");
    gotoxy(50,8);
    printf("Availabe");
    gotoxy(65,8);
    printf("Price/Day");

    gotoxy(1,9);
    for(i = 1; i<= 80; i++)
        printf("%c",247);
    int row = 10;
    textcolor(YELLOW);
    while(fread(&C,sizeof(C),1,fp) == 1)
    {
        if(C.car_count > 0)
        {
            gotoxy(2,row);
            printf("%d",C.car_id);

            gotoxy(15,row);
            printf("%s",C.car_name);

            gotoxy(35,row);
            printf("%d",C.capacity);

            gotoxy(50,row);
            printf("%d",C.car_count);

            gotoxy(65,row);
            printf("%d",C.price);

            row++;
        }
    }
    fclose(fp);
    getch();
}

void updateCarCount(int c_id)
{
    FILE * fp = fopen("car.bin","rb+");
    if(fp == NULL)
    {
        textcolor(LIGHTRED);
        return ;
    }
    Car C;
    while(fread(&C,sizeof(C),1,fp) == 1)
    {
        if(C.car_id == c_id)
        {
            int x = C.car_count;
            x--;
            fseek(fp,-8,SEEK_CUR);
            fwrite(&x,sizeof(int),1,fp);
            break;
        }
    }
    fclose(fp);
}

void bookedCarDetail()
{
    return_car();
    return_car_delete();
    return_car();
    return_car_delete();
    clrscr();
    FILE * fp =  fopen("customer.bin","rb");
    if(fp == NULL)
    {

        textcolor(LIGHTRED);
        gotoxy(32,22);
        printf("File cannot opened !!!");
        return;
    }
    Customer_Car_Details CC;
    int i;
    textcolor(YELLOW);
    gotoxy(31,1);
    printf("CAR RENTAL SYSTEM\n");
    for(i = 1; i <= 80 ; i++)
    {
        printf("%c",247);
    }
    gotoxy(31,5);
    printf("* BOOKED CAR DETAILS *");
    gotoxy(1,7);
    textcolor(LIGHTGREEN);
    for( i = 1; i<= 80  ; i++)
        printf("%c",247);

    gotoxy(1,8);
    printf("Model");

    gotoxy(14,8);
    printf("Cust Name");

    gotoxy(28,8);
    printf("PickUp");

    gotoxy(42,8);
    printf("Drop");

    gotoxy(56,8);
    printf("Start_Date");

    gotoxy(68,8);
    printf("End_Date");

    gotoxy(1,9);
    for(i = 1; i<= 80 ; i++)
        printf("%c",247);

    int row = 10;

    textcolor(YELLOW);
    while(fread(&CC,sizeof(Customer_Car_Details),1,fp) == 1)
    {
        gotoxy(1,row);
        printf("%s",getCarName(CC.car_id));
        gotoxy(14 ,row);
        printf("%s",CC.cust_name);
        gotoxy(28,row);
        printf("%s",CC.pickup);
        gotoxy(42,row);
        printf("%s",CC.drop);
        gotoxy(56,row);
        printf("%d-%d-%d",CC.sd.tm_mday,CC.sd.tm_mon,CC.sd.tm_year);
        gotoxy(68,row);
        printf("%d-%d-%d",CC.ed.tm_mday,CC.ed.tm_mon,CC.ed.tm_year);

        row++;
    }
    fclose(fp);
    getch();
}

int checkDate(struct tm sd, struct tm ed)
{
    int i,month_days,current = 0,start = 0,end = 0;
    int arr[] = {31,28,31,30,31,30,31,31,30,31,30,31};

    time_t now = time(0);
    struct tm *ptr_now = localtime(&now);

    current = ptr_now->tm_yday;
    current += 1;

    for(i = 0 ; i <= sd.tm_mon-2 ;i++)
        start += arr[i];

    start += sd.tm_mday;

    for(i = 0 ; i <= ed.tm_mon-2 ;i++)
        end += arr[i];

    end += ed.tm_mday;

    if((current <= start) && (current < end) && (start <= end))
        return 1 ;
    else
        return 0;
}

void returnUpdateCarCount(int c_id)
{
    FILE * fp = fopen("car.bin","rb+");
    if(fp == NULL)
    {
        textcolor(LIGHTRED);
        return ;
    }
    Car C;
    while(fread(&C,sizeof(C),1,fp) == 1)
    {
        if(C.car_id == c_id)
        {
            int x = C.car_count;
            ++x;
            fseek(fp,-8,SEEK_CUR);
            fwrite(&x,sizeof(int),1,fp);
            break;
        }
    }
    fclose(fp);
}


void return_car()
{
    FILE * fp = fopen("customer.bin","rb");
    if(fp == NULL)
    {
        //message
    }
    int arr[] = {31,28,31,30,31,30,31,31,30,31,30,31};
    time_t now = time(0);
    struct tm *ptr_now = localtime(&now);
    struct tm temp;
    int i;
    int id;

    int current_day = ptr_now->tm_yday;
    int current_year = ptr_now->tm_year + 1900;
    int end_day;
    Customer_Car_Details cc;
    while( fread(&cc,sizeof(cc),1,fp) == 1)
    {
        end_day = 0;
        temp= cc.ed;
        id = cc.car_id;

        for(i = 0 ; i <= temp.tm_mon-2 ; i++)
            end_day += arr[i];

        end_day += temp.tm_mday;


        if((current_day >= end_day ) && (current_year == temp.tm_year))
        {
            returnUpdateCarCount(cc.car_id);
        }
        else if(current_year > temp.tm_year)
        {
            returnUpdateCarCount(cc.car_id);
        }

    }
    fclose(fp);
}

void return_car_delete()
{
    FILE *fp1 = fopen("customer.bin","rb");
    FILE *fp2 = fopen("temp.bin","wb+");

    Customer_Car_Details cc;

    while(fread(&cc,sizeof(cc),1,fp1) == 1)
    {
        fwrite(&cc,sizeof(cc),1,fp2);
        //printf("%d %s %s %s",cc.car_id,cc.cust_name,cc.pick,cc.drop);
        //getch();
    }
    fclose(fp1);
    fclose(fp2);

    FILE * temp1 = fopen("temp.bin","rb");
    FILE *temp2 = fopen("temp2.bin","wb");

    int found = 0;
    int result;

    int arr[] = {31,28,31,30,31,30,31,31,30,31,30,31};
    time_t now = time(0);
    struct tm *ptr_now = localtime(&now);
    struct tm temp;
    int i;
    int id;

    int current_day = ptr_now->tm_yday;
    int current_year = ptr_now->tm_year + 1900;
    int end_day;

    while( fread(&cc,sizeof(cc),1,temp1) == 1)
    {
        end_day = 0;
        temp= cc.ed;
        id = cc.car_id;

        for(i = 0 ; i <= temp.tm_mon-2 ; i++)
            end_day += arr[i];

        end_day += temp.tm_mday;
        if(((current_day >= end_day ) && (current_year == temp.tm_year)) ||(current_year > temp.tm_year))
        {
            found = 1;
            //printf("\nfound\n");
            //getch();
        }
        else
        {
            fwrite(&cc,sizeof(cc),1,temp2);
            //printf("\nNot Match Date\n");
            //getch();
        }
    }
        fclose(temp1);
        fclose(temp2);


    if(found == 0)
    {
        remove("temp2.bin");
        remove("temp.bin");
    }
    else{
        result = remove("temp1.bin");
        remove("customer.bin");
        if(result != 0 )
        {
            //printf("\nremove\n");
            //getch();
        }
        result = rename("temp2.bin","customer.bin");
        if(result != 0)
        {
            //printf("\nremove\n");
            //getch();
        }
    }
}
