#include <stdio.h>
#include <string.h>
#include "terminal.h"
#include "../Card/card.h"


//get transaction date
EN_terminalError_t getTransactionDate(ST_terminalData_t* termData) {

	if (strlen(termData->transactionDate) == 10    &&
		isdigit(termData->transactionDate[0]) != 0 &&
		isdigit(termData->transactionDate[1]) != 0 &&
		termData->transactionDate[2] == '/'        &&
		isdigit(termData->transactionDate[3]) != 0 &&
		isdigit(termData->transactionDate[4]) != 0 &&
		termData->transactionDate[5] == '/'        &&
		isdigit(termData->transactionDate[6]) != 0 &&
		isdigit(termData->transactionDate[7]) != 0 &&
		isdigit(termData->transactionDate[8]) != 0 &&
		isdigit(termData->transactionDate[9]) != 0 

		)
	{
		//printf(" data good");

		return TERMINAL_OK;

	}
	else
	{
		//printf("error");

		return WRONG_DATE;
	}
}

void getTransactionDateTest(void) {
	printf("Tester Name : Ahmed Hani \n");
	printf("Function Name : getTransactionDateTest \n");
	printf("---------------------------------------- \n");

	struct inputCase
	{
		int id;
		char inputData[30];
		int expectedResult;
		int actualResult;
	};
	ST_terminalData_t termDataTest = { 0.0,0.0,"0" };

	struct inputCase casetest[5] =
	{
	 {1,"sdasdfa",1,0}
	,{2,"12-12-2022",1,0}
	,{3,"12/30",1,0}
	,{4,"12/12/*022",1,0}
	,{5,"12/12/2022",0,1}
	};

	for (int i = 0; i < 5; i++) {

		strncpy_s(termDataTest.transactionDate, sizeof(termDataTest.transactionDate), casetest[i].inputData,
			sizeof(termDataTest.transactionDate));
		casetest[i].actualResult = getTransactionDate(&termDataTest);


		printf("Test Case: %d \n", casetest[i].id);
		printf("Input Data : %s \n", casetest[i].inputData);
		printf("Expected Result : %d \n", casetest[i].expectedResult);
		printf("Actual Result : %d \n", casetest[i].actualResult);
	}
}

EN_terminalError_t isCardExpired(ST_cardData_t* cardData, ST_terminalData_t* termData) {
	int mmcard = (cardData->cardExpirationDate[1] - 48) + ((cardData->cardExpirationDate[0] - 48) * 10);
	int yycard = (cardData->cardExpirationDate[4] - 48) + ((cardData->cardExpirationDate[3] - 48) * 10);
	int yytermdate = (termData->transactionDate[9] - 48) + ((termData->transactionDate[8] - 48) * 10);
	int mmtermdate = (termData->transactionDate[4]-48) + ((termData->transactionDate[3]-48)*10);
	
	if (yycard < yytermdate) {
		return EXPIRED_CARD;
	}
	else if(yycard == yytermdate)
	{
		if (mmcard > mmtermdate)
		{
			return TERMINAL_OK;
		}
		else 
		{
			return EXPIRED_CARD;
		}

	}
	else
	{
		return TERMINAL_OK;
	}




}

void isCardExpiredTest(void) {
	printf("Tester Name : Ahmed Hani \n");
	printf("Function Name : isCardExpiredTest \n");
	printf("---------------------------------------- \n");

	struct inputCase
	{
		int id;
		char inputData[30];
		int expectedResult;
		int actualResult;
	};
	ST_terminalData_t termDataTest = { 0.0,0.0,"12/12/2022" };
	ST_cardData_t cardDatatest = { "aaaa","123456789","12/25" };

	struct inputCase casetest[3] =
	{
	 {1,"12/21",2,0}
	,{2,"12/22",2,0}
	,{3,"12/25",0,1}
	};

	for (int i = 0; i < 3; i++) {

		strncpy_s(cardDatatest.cardExpirationDate, sizeof(cardDatatest.cardExpirationDate), casetest[i].inputData,
			sizeof(cardDatatest.cardExpirationDate));
		casetest[i].actualResult = isCardExpired(&cardDatatest,&termDataTest);


		printf("Test Case: %d \n", casetest[i].id);
		printf("Input Data : %s \n", casetest[i].inputData);
		printf("Expected Result : %d \n", casetest[i].expectedResult);
		printf("Actual Result : %d \n", casetest[i].actualResult);
	}
}

EN_terminalError_t getTransactionAmount(ST_terminalData_t* termData) {
	if (termData->transAmount <= 0) {
		return INVALID_AMOUNT;
	}
	else
	{
		return TERMINAL_OK;
	}
}

void getTransactionAmountTest(void) {
	printf("Tester Name : Ahmed Hani \n");
	printf("Function Name : getTransactionDateTest \n");
	printf("---------------------------------------- \n");

	struct inputCase
	{
		int id;
		float inputData;
		int expectedResult;
		int actualResult;
	};
	ST_terminalData_t termDataTest = { 0.0,0.0,"0" };

	struct inputCase casetest[3] =
	{
	 {1,0.0,4,0}
	,{2,-11.0,4,0}
	,{3,500.0,0,0}
	};

	for (int i = 0; i < 3; i++) {

		termDataTest.transAmount = casetest[i].inputData;
		casetest[i].actualResult = getTransactionAmount(&termDataTest);


		printf("Test Case: %d \n", casetest[i].id);
		printf("Input Data : %f \n", casetest[i].inputData);
		printf("Expected Result : %d \n", casetest[i].expectedResult);
		printf("Actual Result : %d \n", casetest[i].actualResult);
	}
}


EN_terminalError_t isBelowMaxAmount(ST_terminalData_t* termData) {
	if (termData->transAmount > termData->maxTransAmount) {
		return EXCEED_MAX_AMOUNT;
	}
	else
	{
		return TERMINAL_OK;
	}

}

void isBelowMaxAmountTest(void) {
	printf("Tester Name : Ahmed Hani \n");
	printf("Function Name : isBelowMaxAmountTest \n");
	printf("---------------------------------------- \n");

	struct inputCase
	{
		int id;
		float inputData;
		int expectedResult;
		int actualResult;
	};
	ST_terminalData_t termDataTest = { 0.0,100,"0" };

	struct inputCase casetest[3] =
	{
	 {1,100.0,0,1}   // equal max
	,{2,350.0,5,0}   //over max
	,{3,50.0,0,1}   //blow max
	};

	for (int i = 0; i < 3; i++) {

		termDataTest.transAmount = casetest[i].inputData;
		casetest[i].actualResult = isBelowMaxAmount(&termDataTest);


		printf("Test Case: %d \n", casetest[i].id);
		printf("Input Data : %f \n", casetest[i].inputData);
		printf("Expected Result : %d \n", casetest[i].expectedResult);
		printf("Actual Result : %d \n", casetest[i].actualResult);
	}
}

EN_terminalError_t setMaxAmount(ST_terminalData_t* termData, float maxAmount) {
	if (maxAmount > 0) 
	{
		termData->maxTransAmount = maxAmount;
		return TERMINAL_OK;
	}
	else
	{
		return INVALID_MAX_AMOUNT;
	}
}

void setMaxAmountTest(void) {
	printf("Tester Name : Ahmed Hani \n");
	printf("Function Name : setMaxAmountTest \n");
	printf("---------------------------------------- \n");

	struct inputCase
	{
		int id;
		float inputData;
		int expectedResult;
		int actualResult;
	};
	ST_terminalData_t termDataTest = { 0.0,0.0,"0" };

	struct inputCase casetest[3] =
	{
	 {1,-50.0,6,0}
	,{2,0.0,6,0}
	,{3,200.0,0,1}
	};

	for (int i = 0; i < 3; i++) {

		casetest[i].actualResult = setMaxAmount(&termDataTest, casetest[i].inputData);

		printf("Test Case: %d \n", casetest[i].id);
		printf("Input Data : %f \n", casetest[i].inputData);
		printf("Expected Result : %d \n", casetest[i].expectedResult);
		printf("Actual Result : %d \n", casetest[i].actualResult);
	}
}

