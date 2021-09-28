#include <stdlib.h>
#include <stdio.h>
#include <string.h>

struct userDetails
{
    char number[40];

    char password[40];

    double balance;

};

void printMenu(void) {

    printf("\n\n -- Enter 1 for login ");

    printf("\n\n -- Enter 2 for register ");

    printf("\n\n == Enter your choice: ");

}

void printLoggedMenu(void) {

    printf("\n\n -- Enter 1 for deposit");

    printf("\n\n -- Enter 2 for withdrawal");

    printf("\n\n -- Enter 3 for online transfer");

    printf("\n\n -- Enter 0 for Quit");

    printf("\n\n == Enter your choice: ");

}

int main() {

    struct userDetails user, user1;

    FILE *fp;

    int choice;

    int loggedChoice;

    double loggedSum; //variable for add sum to your account

    char contin[20];

    do {

        contin[0] = 'y';

        char fileName[40] = "";

        char fileName1[40] = "";

        char usr[40] = "";

        char pwd[40] = "";

        system("cls");

        printMenu();

        scanf("%d", &choice);

        if(choice == 1) {
            printf("\n\n -- Login into account");

            printf("\n\n == Enter your number: ");

            scanf("%s", &usr);

            printf("\n == Enter your password: ");

            scanf("%s", &pwd);

            strcpy(fileName, usr);

            strcat(fileName, ".txt");

            fp = fopen(fileName, "r");

            if(!fp == 0) {

                fread(&user, sizeof(struct userDetails), 1, fp );
                fclose(fp);
                if(strcmp(pwd, user.password) == 0) {

                    system("cls");

                    while(contin[0] != 'n') {

                    loggedSum = 0;

                    printf("\n\n == Your Bank Account == ");

                    printf("\n\n --     Hello, %s     -- ", user.number);

                    printf("\n\n  [ Current balance $ %.2f ]  ", user.balance);

                    printLoggedMenu();

                    scanf("%d", &loggedChoice);

                    if(loggedChoice == 0) {
                        printf("\n\n -- Bye!");
                        contin[0] = 'n';
                        break;
                    } else if(loggedChoice == 1) {

                        printf(" \n\n -- Deposit in US Dollars ($): ");

                        scanf("%lf", &loggedSum);

                        user.balance = user.balance + loggedSum;

                        fp = fopen(fileName, "w");

                        fwrite(&user, sizeof(struct userDetails), 1, fp);

                        fclose(fp);

                        if(fp != 0) {
                            printf("Succes deposit!");
                        } else {
                            printf("Error");
                        }

                    } else if(loggedChoice == 2) {

                        printf(" \n\n -- Withdrawal in US Dollars ($): ");

                        scanf("%lf", &loggedSum);

                        if(loggedSum > user.balance) {

                            printf("\n -- You don\'t have enough money ($)");
                        } else {

                           user.balance = user.balance - loggedSum;

                            fp = fopen(fileName, "w");

                            fwrite(&user, sizeof(struct userDetails), 1, fp);

                            fclose(fp);
                        }

                       } else if(loggedChoice == 3) {

                           printf("\n\n -- Enter number to deposit: ");

                           scanf("%s", &usr);

                           strcpy(fileName1, usr);

                           strcat(fileName1, ".txt");

                           fp = fopen(fileName1, "r");

                           if(fp != 0) {

                               printf("\n == Enter your amount to send to number [%s]: ", usr);

                               scanf("%lf", &loggedSum);

                               if(loggedSum <= user.balance) {
                                   //if you have this cash in your acc SEND IT TO number
                                   fread(&user1, sizeof(struct userDetails), 1,fp);
                                   fclose(fp);
                                   fp = fopen(fileName1,"w");
                                   user1.balance = user1.balance + loggedSum;
                                   fwrite(&user1, sizeof(struct userDetails), 1,fp);
                                   fclose(fp);
                                   if(fp) printf("\n\n -- Sucesfully transfer.");
                                   else printf("\n\n -- Error in transfer.");
                                   fclose(fp);
                                   fp = fopen(fileName, "w");
                                   user.balance = user.balance - loggedSum;
                                   fwrite(&user, sizeof(struct userDetails), 1,fp);
                                   fclose(fp);
                               } else {
                                   printf("\n\n -- You don\'t have enough money ($).");
                               }

                           }  else {
                               printf("\n\n -- invalid number");
                           }

                       }

                       printf("\n\n -- Do you want to continue with this transaction [y/n]: ");

                       scanf("%s", contin);

                       system("cls");

                    }
                 }

                 else {
                    printf("\n !! W r o n g p a s s w o r d !!");
                }

                fclose(fp);
            } else {
                printf("acc dont exist");
                fclose(fp);
            }

        } else if (choice == 2) {
            printf("\n\n -- New registration");

            printf("\n\n == Enter your number: ");

            scanf("%s", &user.number);

            printf("\n == Enter your password: ");

            scanf("%s", &user.password);

            strcpy(fileName, user.number);

            strcat(fileName, ".txt");

            fp = fopen(fileName, "r");

            if(!fp == 0) {
                printf("\n\n -- Account is already registered.");
                fclose(fp);
            } else {
                fclose(fp); //close file

                fp = fopen(fileName, "w"); //open file for writing and create it if dont exist.
                user.balance = 0.01;
                fwrite(&user, sizeof(struct userDetails), 1, fp);
                if(fp != 0) {
                   printf("\n\n -- Succesfully registered.");
                   fclose(fp);
                } else {
                   printf("\n\n -- Error. Contact with the administrator.");
                   fclose(fp);
                }
            }

        } else if (choice == 0) {
            printf("\n\n -- Bye Bye -- ");
        } else {
            printf("\n\n -- invalid choice --");
        }


    } while(choice != 0);

}
