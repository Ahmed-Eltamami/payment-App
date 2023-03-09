#include <stdio.h>
#include <string.h>
#include "../Terminal/terminal.h"
#include "../Card/card.h"
#include "server.h"


ST_transaction_t transData[255] = {0};
int sequenceNumber = 0;



EN_transStat_t recieveTransactionData(ST_transaction_t* transData,ST_accountsDB_t * accountsDB){

    
    int size = sizeof(accountsDB);
    for (int i = 0; i < size; i++)
    {

        if (memcmp(&accountsDB[i].primaryAccountNumber, &transData->cardHolderData.primaryAccountNumber, 16) == 0)
        {
            if (accountsDB[i].balance > transData->terminalData.transAmount) {

                if (accountsDB[i].state == RUNNING) {

                    accountsDB[i].balance = accountsDB[i].balance - transData->terminalData.transAmount;
                    if (accountsDB[i].balance < 0) {
                        return INTERNAL_SERVER_ERROR;//4
                    }
                    else
                    {
                        return APPROVED;//0
                    }
                }
                else
                {
                    return DECLINED_STOLEN_CARD;//2
                }
            }
            else
            {
                return DECLINED_INSUFFECIENT_FUND;//1

            }

        }
        else 
        {
            if (i == size-1)
            {
                return FRAUD_CARD; //3
            }
        }

     } 
}
void recieveTransactionDataTest(void) {
    printf("Tester Name : Ahmed Hani \n");
    printf("Function Name : recieveTransactionData \n");
    printf("---------------------------------------- \n");

    struct inputCase
    {
        int id;
        char inputData1[30];
        float inputData2;
        int expectedResult;
        int actualResult;
    };
    ST_accountsDB_t accountRefrence[255] = {
    { 100.0   , RUNNING, "1234567891234567"} ,
    { 565000.0, RUNNING, "5456454821545487"} ,
    { 545000.0, RUNNING, "1256422542656555"} ,
    { 545000.0, RUNNING, "1245896541235458"} ,
    { 5.0     , RUNNING, "1254876254135258"} ,
    { 200.0  , RUNNING, "1111111111111111"} ,
    { 4000.0  , RUNNING, "1234567891234567"} ,
    { 100000.0, BLOCKED, "0000000000000000"} };

    ST_transaction_t transData;

    struct inputCase case1[4] =
    {
     {1,"1234567891234567",200,1,5} //over max
    ,{2,"1234567891234567",50,0,0}  // ok
    ,{3,"1256415586554545",100,3,0} //frad
    ,{4,"0000000000000000",100,2,0} //BLOCKED
    };

    for (int i = 0; i < 4; i++) {

        strncpy_s(transData.cardHolderData.primaryAccountNumber, sizeof(transData.cardHolderData.primaryAccountNumber),
            case1[i].inputData1,sizeof(transData.cardHolderData.primaryAccountNumber));
        transData.terminalData.transAmount = case1[i].inputData2;
        case1[i].actualResult = recieveTransactionData(&transData,&accountRefrence);


        printf("Test Case: %d \n", case1[i].id);
        printf("Input Data 1: %s \n", case1[i].inputData1);
        printf("Input Data 2: %f \n", case1[i].inputData2);
        printf("Expected Result : %d \n", case1[i].expectedResult);
        printf("Actual Result : %d \n", case1[i].actualResult);
    }
}

EN_serverError_t isValidAccount(ST_cardData_t* cardData, ST_accountsDB_t* accountRefrence) {
   
    int size = sizeof(accountRefrence);
    
    for (int i = 0; i < size; i++)
    {

        if (memcmp(accountRefrence[i].primaryAccountNumber, cardData->primaryAccountNumber, 20) == 0)
        {
            return isBlockedAccount(&accountRefrence[i]); //0
        }
        else
        {
            if (i == size - 1)
            {
                return ACCOUNT_NOT_FOUND; //3
            }
        }

    }

}
void isValidAccountTest(void) {
    printf("Tester Name : Ahmed Hani \n");
    printf("Function Name : isValidAccount \n");
    printf("---------------------------------------- \n");

    struct inputCase
    {
        int id;
        char inputData[30];
        int expectedResult;
        int actualResult;
    };
    ST_accountsDB_t accountRefrence[255] = {
    { 100.0   , RUNNING, "1234567891234567"} ,
    { 565000.0, RUNNING, "5456454821545487"} ,
    { 545000.0, RUNNING, "1256422542656555"} ,
    { 545000.0, RUNNING, "1245896541235458"} ,
    { 5.0     , RUNNING, "1254876254135258"} ,
    { 200.0   , RUNNING, "1111111111111111"} ,
    { 4000.0  , RUNNING, "1234567891234567"} ,
    { 100000.0, BLOCKED, "0000000000000000"} };

    ST_cardData_t cardData[2] = { {"aaaa","1256422542656555","22222"},{"aaaa","125642254264545","22222"} };

    struct inputCase case1[2] =
    {
     {0,"1256422542656555",0,5}
    ,{1,"125642254264545",3,0}
    };

    for (int i = 0; i < 2; i++) {

        case1[i].actualResult = isValidAccount(&cardData[i], &accountRefrence);


        printf("Test Case: %d \n", case1[i].id);
        printf("Input Data : %s \n", case1[i].inputData);
        printf("Expected Result : %d \n", case1[i].expectedResult);
        printf("Actual Result : %d \n", case1[i].actualResult);
    }
}


EN_serverError_t isBlockedAccount(ST_accountsDB_t* accountRefrence)
{
    if (accountRefrence->state == RUNNING) {

        return SERVER_OK;//0
    }
    else
    {
        return BLOCKED_ACCOUNT;//5
    }
    
}
void isBlockedAccountTest(void) {
    printf("Tester Name : Ahmed Hani \n");
    printf("Function Name : isBlockedAccount \n");
    printf("---------------------------------------- \n");

    struct inputCase
    {
        int id;
        int inputData;
        int expectedResult;
        int actualResult;
    };
    ST_accountsDB_t accountRefrence[255] = {
   { 100.0, RUNNING, "1234567891234567"} ,
   { 565000.0, BLOCKED, "5456454821545487"} ,
   { 545000.0, RUNNING, "1256422542656555"} ,
   { 545000.0, BLOCKED, "1245896541235458"} ,
   { 5.0     , RUNNING, "1254876254135258"} ,
   { 200.0   , BLOCKED, "1111111111111111"} ,
   { 4000.0  , RUNNING, "1234567891234567"} ,
   { 100000.0, BLOCKED, "0000000000000000"} };
    ST_cardData_t cardData = { "aaaa","123456789","22222" };

    struct inputCase case1[7] =
    {
     {0,0,0,0}
    ,{1,1,5,0}
    ,{2,2,0,0}
    ,{3,3,5,0}
    ,{4,4,0,0}
    ,{5,5,5,0}


    };

    for (int i = 0; i < 7; i++) {

        case1[i].actualResult = isBlockedAccount(&accountRefrence[case1[i].inputData]);


        printf("Test Case: %d \n", case1[i].id);
        printf("Input Data : %d \n", case1[i].inputData);
        printf("Expected Result : %d \n", case1[i].expectedResult);
        printf("Actual Result : %d \n", case1[i].actualResult);
    }
}  //done   //done

EN_serverError_t isAmountAvailable(ST_terminalData_t* termData, ST_accountsDB_t* accountRefrence) {
    if (accountRefrence->balance >= termData->transAmount) {

        return SERVER_OK;//0
    }
    else
    {
        return LOW_BALANCE;//4

    }
}
void isAmountAvailableTest(void) {
    printf("Tester Name : Ahmed Hani \n");
    printf("Function Name : isAmountAvailable \n");
    printf("---------------------------------------- \n");

    struct inputCase
    {
        int id;
        double inputData;
        int expectedResult;
        int actualResult;
    };
    ST_terminalData_t termDataTest = { 0.0,0.0,"0" };
    ST_accountsDB_t accountRefrence[255] = {
   { 100.0, RUNNING, "1234567891234567"} ,
   { 565000.0, BLOCKED, "5456454821545487"} ,
   { 545000.0, RUNNING, "1256422542656555"} ,
   { 545000.0, BLOCKED, "1245896541235458"} ,
   { 5.0     , RUNNING, "1254876254135258"} ,
   { 200.0   , BLOCKED, "1111111111111111"} ,
   { 4000.0  , RUNNING, "1234567891234567"} ,
   { 100000.0, BLOCKED, "0000000000000000"} };
    struct inputCase case1[3] =
    {
     {0,50,0,0}
    ,{1,100,0,0}
    ,{1,150,4,0}
    };

    for (int i = 0; i < 3; i++) {

        termDataTest.transAmount = case1[i].inputData;
        case1[i].actualResult = isAmountAvailable(&termDataTest,&accountRefrence[0]);


        printf("Test Case: %d \n", case1[i].id);
        printf("Input Data : %f \n", case1[i].inputData);
        printf("Expected Result : %d \n", case1[i].expectedResult);
        printf("Actual Result : %d \n", case1[i].actualResult);
    }
}

EN_serverError_t saveTransaction(ST_transaction_t* transData) {
    uint32_t transactionNumber = transData[0].transactionSequenceNumber + 1 ;
    if (transactionNumber < 255) {
        transData->transactionSequenceNumber = transactionNumber;
        return SERVER_OK;
    }
    else {
        return INTERNAL_SERVER_ERROR;
    }
}
void saveTransactionTest(void) 
{
    printf("Tester Name : Ahmed Hani \n");
    printf("Function Name : saveTransactionTest \n");
    printf("---------------------------------------- \n");

    ST_transaction_t transData = {0};


    transData.cardHolderData = (ST_cardData_t){ .cardHolderName = "ahmed hani mohamed el",
                                                .primaryAccountNumber = "1234567891234567",
                                                .cardExpirationDate = "05/20" };
    transData.terminalData = (ST_terminalData_t){ .transAmount = 2000,
                                                  .maxTransAmount = 20000,
                                                  .transactionDate = "31/12/2022" };
    transData.transState = FRAUD_CARD;
    printf("\nTest Case 1 : happy case\n");
    printf("Input Data: FRAUD_CARD \n");
    printf("Expected Result: %d \n", SERVER_OK);
    printf("Actual Result: %d \n", saveTransaction(&transData));
    printf("SequenceNumber: %d \n", transData.transactionSequenceNumber);

    transData.cardHolderData = (ST_cardData_t){ .cardHolderName = "ahmed hani eltamami",
                                                .primaryAccountNumber = "1234567891234567",
                                                .cardExpirationDate = "12/24" };
    transData.terminalData = (ST_terminalData_t){ .transAmount = 5000,
                                                .maxTransAmount = 20000,
                                                .transactionDate = "31/12/2022" };
    transData.transState = DECLINED_STOLEN_CARD;
    transData.transactionSequenceNumber = 256;
    printf("\nTest Case 2 : worst case\n");
    printf("Input Data: DECLINED_STOLEN_CARD\n");
    printf("Expected Result: %d \n", INTERNAL_SERVER_ERROR);
    printf("Actual Result: %d \n", saveTransaction(&transData));
    printf("SequenceNumber: %d \n", transData.transactionSequenceNumber);
}


int search(ST_cardData_t* cardData, ST_accountsDB_t* accountRefrence)
{
    int size = sizeof(accountRefrence);
    for (int i = 0; i < size; i++)
    {

        if (memcmp(accountRefrence[i].primaryAccountNumber, cardData->primaryAccountNumber, 20) == 0)
        {
            return i; //0
        }
        else
        {
            if (i == size - 1)
            {
                return -1; //3
            }
        }

    }
}

void listSavedTransactions(ST_transaction_t* transData) {
    for (int i = 0; i < sequenceNumber; i++)
    {
        printf("#########################\n");
        printf("Transaction Sequence Number : %d\n",transData[i].transactionSequenceNumber);
        printf("Transaction Date :%s\n", transData[i].terminalData.transactionDate);
        printf("Transaction Amount %f\n", transData[i].terminalData.transAmount);
        printf("Transaction State :%d\n", transData[i].transState);
        printf("Terminal Max Amount :%f\n", transData[i].terminalData.maxTransAmount);
        printf("Cardholder Name :%s\n", transData[i].cardHolderData.cardHolderName);
        printf("PAN:%s\n", transData[i].cardHolderData.primaryAccountNumber);
        printf("Card Expiration Date :%s\n", transData[i].cardHolderData.cardExpirationDate);
        printf("#########################\n");
    }
}
void listSavedTransactionsTest(void)
{
    printf("Tester Name : Ahmed Hani \n");
    printf("Function Name : listSavedTransactions \n");
    printf("---------------------------------------- \n");

    
    transData->cardHolderData = (ST_cardData_t){ .cardHolderName = "ahmed hani mohamed el",
                                                .primaryAccountNumber = "1234567891234567",
                                                .cardExpirationDate = "05/20" };
    transData->terminalData = (ST_terminalData_t){ .transAmount = 2000,
                                                  .maxTransAmount = 20000,
                                                  .transactionDate = "31/12/2022" };
    transData->transState = FRAUD_CARD;
    sequenceNumber++;

    transData[1].cardHolderData = (ST_cardData_t){.cardHolderName = "mohamed hani mohamed el",
                                            .primaryAccountNumber = "1234567891234567",
                                            .cardExpirationDate = "05/20" };
    transData[1].terminalData = (ST_terminalData_t){.transAmount = 2000,
                                                  .maxTransAmount = 20000,
                                                  .transactionDate = "31/12/2022" };
    transData[1].transState = FRAUD_CARD;
    sequenceNumber++;

    transData[2].cardHolderData = (ST_cardData_t){ .cardHolderName = "ali hani mohamed el",
                                            .primaryAccountNumber = "1234567891234567",
                                            .cardExpirationDate = "05/20" };
    transData[2].terminalData = (ST_terminalData_t){ .transAmount = 2000,
                                                  .maxTransAmount = 20000,
                                                  .transactionDate = "31/12/2022" };
    transData[2].transState = FRAUD_CARD;
    sequenceNumber++;

    listSavedTransactions(&transData);
}