#include <stdio.h>
#include <string.h>
#include "../Terminal/terminal.h"
#include "../Card/card.h"
#include "../Server/server.h"
#include "app.h"

ST_cardData_t cardData;
ST_transaction_t transData[255];

ST_accountsDB_t accountRefrence[255] = {
	{ 100.0, RUNNING, "1234567892234567"} ,
	{ 565000.0, RUNNING, "5456454821545487"} ,
	{ 545000.0, RUNNING, "1256422542656555"} ,
	{ 545000.0, RUNNING, "1245896541235458"} ,
	{ 5.0     , RUNNING, "1254876254135258"} ,
	{ 200.0   , RUNNING, "1111111111111111"} ,
	{ 2000.0  , RUNNING, "1234567891234567"} ,
	{ 100000.0, BLOCKED, "0000000000000000"} };

ST_cardData_t cardData;
ST_terminalData_t termData = { 200.0, 3000.0 ,"12/22" };




void appStart(void)
{
	int app = 0;

	
	while (app == 0)
	{
		printf("please Enter Card Name Holder:");
		fgets(cardData.cardHolderName, sizeof(cardData.cardHolderName), stdin);
		printf("please Enter Card Expiry data (MM/YY) :");
		fgets(cardData.cardExpirationDate, sizeof(cardData.cardExpirationDate), stdin);
		fgetc(stdin);
		printf("please Enter Primary Account Number :");
		fgets(cardData.primaryAccountNumber, sizeof(cardData.primaryAccountNumber), stdin);
		

		if (getCardHolderName(&cardData) != 0 || getCardExpiryDate(&cardData) != 0 || getCardPAN(&cardData) != 0) {
			printf("wong card data\n");
		}
		else 
		{
			app = 1;
		}
	}

	while (app == 1) 
	{
		printf("please Enter transaction date (DD/MM/YYYY) :");
		fgets(termData.transactionDate, sizeof(termData.transactionDate), stdin);
		fgetc(stdin);

		if (getTransactionDate(&termData) != 0) {
			printf("please enter correct fromat \n");
		}

		else
		{
			app = 2;
		}

	}
	while (app == 2)
	{
		if (isCardExpired(&cardData, &termData) != 0)
		{
			printf("card is expier\n");
			break;
		}

		printf("please Enter transaction amount:");
		scanf_s("%f", &termData.transAmount);

		while (getTransactionAmount(&termData)!= 0)
		{
			printf("invalid Transaction Amount \n");
			break;
		}

		if (isBelowMaxAmount(&termData) != 0)
		{
			printf("declined amount exceeding limit \n");
			break;
		}
		cardData.primaryAccountNumber[strlen(cardData.primaryAccountNumber) - 1] = '\0';

		if (isValidAccount(&cardData,&accountRefrence) != 0 )
		{
			if (isValidAccount(&cardData,&accountRefrence) == 5)
			{
				printf("Blocked Account\n");
				break;
			}
			else 
			{
				printf("declined invalid account \n");
				break;
			}
			
		}
		int accountIndex = search(&cardData, &accountRefrence);
		if(isAmountAvailable(&termData,&accountRefrence[accountIndex]) !=0)
		{
			printf("declined insuffecient funds");
			break;
		}	


		transData->cardHolderData = cardData;
		transData->terminalData = termData;
		saveTransaction(&transData);
		transData->transState = recieveTransactionData(&transData, &accountRefrence);
		printf("accepted payment");
		printf("the account balance is : %f", accountRefrence[accountIndex].balance);
		app = 3;



	}





	

}
