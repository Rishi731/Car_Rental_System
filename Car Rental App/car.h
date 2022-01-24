#ifndef CAR_H_INCLUDED
#define CAR_H_INCLUDED
#include<time.h>

struct User
{
    char userid[20];
    char pwd[20];
    char name[20];
};
struct Car
{
    int car_id;
    char car_name[50];
    int capacity;
    int car_count;
    int price;
};
struct Customer_Car_Details
{
    int car_id;
    char cust_name[30];
    char pickup[30];
    char drop[30];
    struct tm sd,ed;
};
typedef struct User User;
typedef struct Car Car;
typedef struct Customer_Car_Details Customer_Car_Details;

void addAdmin();
User * getInput();
int checkUserExist(User,char *);
int adminMenu();
void addEmployee();
void viewEmployee();
void addCarDetails();
void showCarDetails();
int deleteEmp();
int deleteCarModel();
int empMenu();
int selectCarModel();
int isValidDate(struct tm);
void updateCarCount(int);
void bookedCarDetail();
char* getCarName();
int rentCar();
void availCarDetails();
void return_car();

#endif // CAR_H_INCLUDED
