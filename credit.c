//Get length of card
//Check if card ends in 0
//  yes? -> proceed
//  no? -> invalid
//Get first two numbers of card
//  begin with 4? length 13 or 16? -> visa
//  begin with 34 or 37? length 15? -> AMEX
//  begin with 51, 52, 53, 54, 55? length 16? -> MC

#include <cs50.h>
#include <math.h>
#include <stdio.h>

/*FUNCTION PROTOTYPES*/
void validateCard(long long card);
int getLength(long long card);
bool isValidNumber(long long card, int length);
bool getCardType(long long card, int length);


int main(void)
{
    long long card = get_long_long("Credit Card Number: ");
    validateCard(card);
}


/*FUNCTIONS*/

//Calls various functions to check if a credit card is valid
//Prints INVALID if it is not
void validateCard(long long card)
{
    int length = getLength(card);

    //Checks if length is 13, 15, or 16
    if (!length)
        printf("INVALID\n");
    else
    {
        //Checks if card is valid
        if(!isValidNumber(card, length))
            printf("INVALID\n");
        else
        {
            //Gets card type
            if(!getCardType(card, length))
            {
                printf("INVALID\n");
            }
        }
    }
}

//Checks for 13, 15, and 16 digit cards by comparing values to const numbers
//Returns length if card length is valid
//Returns 0 if invalid
int getLength(long long card)
{
    const long long THIRTEEN_MIN = 1000000000000;
    const long long THIRTEEN_MAX = 9999999999999;
    const int THIRTEEN = 13;
    const long long FIFTEEN_MIN = 100000000000000;
    const long long FIFTEEN_MAX = 999999999999999;
    const int FIFTEEN = 15;
    const long long SIXTEEN_MIN = 1000000000000000;
    const long long SIXTEEN_MAX = 9999999999999999;
    const int SIXTEEN = 16;
    const int INVALID = 0;

    if (card >= THIRTEEN_MIN && card <= THIRTEEN_MAX)
        return THIRTEEN;
    else if (card >= FIFTEEN_MIN && card <= FIFTEEN_MAX)
        return FIFTEEN;
    else if (card >= SIXTEEN_MIN && card <= SIXTEEN_MAX)
        return SIXTEEN;
    else
        return INVALID;
}

//Checks each digit in card number
//Digits at 10 ^ x where x is even: get doubled. If that doubled number is two digits,
//  the two digits are added together, then put into the evenNums int. Otherwise
//  the doubled number (that's a single digit) gets added into evenNums.
//Digits at 10 ^ x where x is odd: Nothing special happens, they get added into oddNums.
//Once all numbers are added into oddNums and evenNums, they are added together and stored in
//  totalNums
//If totalNums 10 ^ 1 digit is 0, the card is valid
bool isValidNumber(long long card, int length)
{
    int evenNums = 0; //gets multiplied by two and if two digits, those digits are added
    int oddNums = 0; //nothing special happens, just gets added to total
    int totalNums = 0;

    //Cycles through each digit
    for (int i = 1; i <= length; i++)
    {
        if (i == 1)
            oddNums += card % 10;
        else
        {
            //Single out digit by doing with modulus fun stuff
            long long currNum = card % (long long)pow(10, i);
            long long prevNum = card % (long long)pow(10, i - 1);
            int singNum = (currNum - prevNum) / (long long)pow(10, i - 1);

            //check if digit is odd
            if (i % 2)
            {
                oddNums += singNum;
            }
            else
            {
                int doubledNum = singNum * 2;

                //Checks if doubledNum is two digits
                if (doubledNum >= 10)
                {
                    //Singles out tens place
                    int tens = (doubledNum - (doubledNum % 10)) / 10;
                    //Singles out ones place
                    int ones = doubledNum % 10;

                    //Adds the additive of tens and ones to the evenNums pool
                    evenNums += tens + ones;
                }
                else
                    evenNums += doubledNum;
            }
        }

    }
    //Combine evenNums and oddNums
    totalNums = evenNums + oddNums;

    //Check if the ones digit of totalNums is anything but 0
    //I know I don't need the == 0, but it seemed to self-explain better
    if (totalNums % 10 == 0)
        return true;
    else
        return false;
}

//Gets the first two numbers and checks if they fit
//the criteria for a VISA, AMEX, or MASTERCARD card
bool getCardType(long long card, int length)
{
    int twoNums;
    int firstNum;

    //Get first two numbers
    twoNums = (card - (card % (long long)pow(10, length - 2))) / (long long)pow(10, length - 2);
    //Get first number for Visa
    firstNum = (twoNums - (twoNums % 10)) / 10;

    //Checks for VISA requirements
    if (length == 13)
    {
        if (firstNum == 4)
        {
            printf("VISA\n");
            return true;
        }
        else
            return false;
    }
    //Checks for AMEX requirements
    else if (length == 15)
    {
        if (twoNums == 34 || twoNums == 37)
        {
            printf("AMEX\n");
            return true;
        }
        else
            return false;
    }
    //Checks for MASTERCARD or VISA requirements
    else if (length == 16)
    {
        //Checks for Visa
        if (firstNum == 4)
        {
            printf("VISA\n");
            return true;
        }
        //checks for MASTERCARD
        else if (twoNums >= 51 && twoNums <= 55)
        {
            printf("MASTERCARD\n");
            return true;
        }
        else
            return false;
    }
    else
        return false;
}