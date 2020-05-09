#include <iostream>
#include <string>
#include <regex>
using namespace std;

class Card {

    public:
        void setCard(const string &cardNumber) {
            this->cardNumber = cardNumber;
            this->cardType = findCardType(cardNumber);
        }
        string getCardType() {
            return cardType;
        }
        string getCardNumber(){
            return cardNumber;
        }

    private:
        string cardType;
        string cardNumber;

        string findCardType(const string &cardNumber) {
            if (regex_match(cardNumber, regex("^4[0-9]{12}(?:[0-9]{3,6})?$")))
                return "Visa";
            else if (regex_match(cardNumber, regex("^(?:5[1-5][0-9]{2}|222[1-9]|22[3-9][0-9]|2[3-6][0-9]{2}|27[01][0-9]|2720)[0-9]{12}$")))
                return "MasterCard";
            else if (regex_match(cardNumber, regex("^3[47][0-9]{13}$")))
                return "American Express";
            else if (regex_match(cardNumber, regex("^3(?:0[0-5]|[68][0-9])[0-9]{11}$")))
                return "Diners Club";
            else if (regex_match(cardNumber, regex("^6(?:011|5[0-9]{2})[0-9]{12}$")))
                return "Discover";
            else if (regex_match(cardNumber, regex("^(?:2131|1800|35\d{3})\d{11}$")))
                return "JCB";
            else return "Invalid";
        }
};

bool checkLuhn(const string& cardNumber) {
    int nDigits = cardNumber.length();

    int sum = 0, isSecond = false;
    for (int i = nDigits - 1; i >= 0; i--) {

        int d = cardNumber[i] - '0';

        if (isSecond == true)
            d = d * 2;
        sum += d / 10;
        sum += d % 10;

        isSecond = !isSecond;
    }
    return (sum % 10 == 0);
}

bool validateCard(Card &card) {
    return (checkLuhn(card.getCardNumber()) && card.getCardType() != "Invalid");
}

int main() {
    Card card;
    string userInput;

    try {
        cout << "Enter credit card number to validate: ";
        cin >> userInput;
    } catch (exception e) {cout << "Invalid input";}
    card.setCard(userInput);
    if (validateCard(card)) cout << "Credit card is valid. \nCredit card type: " << card.getCardType();
    else cout << "Credit card is not valid/supported";
    return 0;
}
