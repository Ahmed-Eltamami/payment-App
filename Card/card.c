#include <stdio.h>
#include <string.h>
#include "card.h"


// get card holder name

EN_cardError_t getCardHolderName(ST_cardData_t *cardData) {
	int inputLenght = strlen(cardData->cardHolderName) - 1;

	if (inputLenght < 20 || inputLenght > 24)
	{
			return WRONG_NAME;
			memset(cardData->cardHolderName[0], 0, sizeof(cardData->cardHolderName));
	}
	else
	{
		for (int i = 0; i < inputLenght; i++)
		{

				if (isalpha(cardData->cardHolderName[i])|| 
					isblank(cardData->cardHolderName[i])) 
				{
					continue;
				}
				else 
				{
					return WRONG_NAME;
				}
		}
		return CARD_OK;
			
	}
	

	
}

//test getCardHolderName
void getCardHolderNameTest(void) {
	printf("Tester Name : Ahmed Hani \n");
	printf("Function Name : getCardHolderName \n");
	printf("---------------------------------------- \n");

	struct inputCase
	{
		int id;
		char inputData[30];
		int expectedResult;
		int actualResult;
	};
	ST_cardData_t cardData = {"aaaa","123456789","22222"};
	
	struct inputCase case1[7] = 
	{	
	 {0,"mohamed hani",1,0}   
	,{1,"ahmed hani",1,0}
	,{1,"ahmed/*///*// hani",1,0}
	,{1,"ahmed 2131128 hani",1,0}
	,{1,"ahmed hani eltamai",0,0}
	,{2,"zxcasdqwezxcasdqwezxca",0,0}
	
	
	};

	for (int i = 0; i < 7; i++) {

		strncpy_s(cardData.cardHolderName, sizeof(cardData.cardHolderName),case1[i].inputData,sizeof( cardData.cardHolderName));
		case1[i].actualResult = getCardHolderName(&cardData);

		
		printf("Test Case: %d \n", case1[i].id);
		printf("Input Data : %s \n", case1[i].inputData);
		printf("Expected Result : %d \n", case1[i].expectedResult);
		printf("Actual Result : %d \n", case1[i].actualResult);
	}
}

// get card expiry data

EN_cardError_t getCardExpiryDate(ST_cardData_t* cardData) {


	if (strlen(cardData->cardExpirationDate) == 5 &&
		isdigit(cardData->cardExpirationDate[0]) != 0 &&
		isdigit(cardData->cardExpirationDate[1]) != 0 &&
		cardData->cardExpirationDate[2] == '/' &&
		isdigit(cardData->cardExpirationDate[3]) != 0 &&
		isdigit(cardData->cardExpirationDate[4]) != 0 
		)
	{
		//printf("card data good");

		return CARD_OK;
		
	}
	else
	{ 
		//printf("error");

		return WRONG_EXP_DATE;
	}



}

// test getCardHolderName
void getCardExpiryDateTest(void) {
	printf("Tester Name : Ahmed Hani \n");
	printf("Function Name :getCardExpiryDateTest \n");
	printf("---------------------------------------- \n");

	struct inputCase
	{
		int id;
		char inputData[30];
		int expectedResult;
		int actualResult;
	};
	ST_cardData_t cardData = { "aaaa","123456789","22222" };

	struct inputCase case1[4] =
	{
	 {1,"12-25",2,0}
	,{2,"a125",2,0} //2= WRONG_EXP_DATE
	,{3,"12315",2,0}
	,{4,"12/25",0,1}//0= CARD_OK
	};

	for (int i = 0; i < 4; i++) {

		strncpy_s(cardData.cardExpirationDate, sizeof(cardData.cardExpirationDate), case1[i].inputData,
			      sizeof(cardData.cardExpirationDate));
		case1[i].actualResult = getCardExpiryDate(&cardData);


		printf("Test Case: %d \n", case1[i].id);
		printf("Input Data : %s \n", case1[i].inputData);
		printf("Expected Result : %d \n", case1[i].expectedResult);
		printf("Actual Result : %d \n", case1[i].actualResult);
	}
}
// get card PAN

EN_cardError_t getCardPAN(ST_cardData_t* cardData) {
	
	int inputLenght = strlen(cardData->primaryAccountNumber)-1;


	if (inputLenght < 16 || inputLenght > 19 )
	{
		return WRONG_PAN;
		memset(cardData->primaryAccountNumber[0], 0, sizeof(cardData->primaryAccountNumber));
	}
	else
	{
			for (int i = 0; i < inputLenght; i++)
			{

				if (isdigit(cardData->primaryAccountNumber[i]))
				{
					continue;
				}
				else
				{
					return WRONG_PAN;
				}
			}

		return CARD_OK;
		
	}
	

}

// test getCardHolderName
void getCardPANTest(void) {
	printf("Tester Name : Ahmed Hani \n");
	printf("Function Name : getCardPANTest \n");
	printf("---------------------------------------- \n");

	struct inputCase
	{
		int id;
		char inputData[30];
		int expectedResult;
		int actualResult;
	};
	ST_cardData_t cardData = { "aaaa","123456789","22222" };

	struct inputCase case1[5] =
	{
	 {1,"sdasdfagsdf123",3,0}
	,{2,"11213544sdsadd",3,0}
	,{3,"123",3,0}
	,{4,"*-*5*56541",3,0}
	,{5,"123456789122334567",0,1}
	};

	for (int i = 0; i < 5; i++) {

		strncpy_s(cardData.primaryAccountNumber, sizeof(cardData.primaryAccountNumber), case1[i].inputData,
			      sizeof(cardData.primaryAccountNumber));
		case1[i].actualResult = getCardPAN(&cardData);


		printf("Test Case: %d \n", case1[i].id);
		printf("Input Data : %s \n", case1[i].inputData);
		printf("Expected Result : %d \n", case1[i].expectedResult);
		printf("Actual Result : %d \n", case1[i].actualResult);
	}
}












