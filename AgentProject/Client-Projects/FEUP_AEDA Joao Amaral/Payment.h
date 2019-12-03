/*
 * Payment.h
 *
 *  Created on: 17/11/2017
 *      Author: Francisco Maria / João Gama Amaral
 */

#ifndef PAYMENT_H_
#define PAYMENT_H_

#include "Libraries.h"
#include "Date.h"

const float TAX_ATM = 0;
const float TAX_CREDIT_CARD = 0.05;
const float TAX_BANK_TRANSFER = 0;
const float TAX_END_OF_MONTH = 0;

typedef enum status {PENDING, RECEIVED} PaymentStatus;

/**
 * @brief Abstract Class that stores all payment information
 */
class Payment{
	float paymentTax;
	PaymentStatus status;
public:
	/**
	 * @brief Default constructor
	 */
	Payment();

	/**
	 * @brief Payment Constructor
	 */
	Payment(float value);

	/**
	 * @brief gets payment tax
	 * @return payment tax
	 */
	float getPaymentTax() const;

	/**
	 * @brief gets payment status
	 * @return payment status
	 */
	std::string getPaymentStatus() const;

	/**
	 * @brief validates payment
	 */
	void validate();

	/**
	 * @brief virtual funtion to get payment type
	 */
	virtual std::string getPaymentType() const = 0;
};

/**
 * @brief Class that represents an ATM payment
 */
class ATM: public Payment{
	std::string entity;
	int reference;
public:
	/**
	 * ATM default constructor
	 */
	ATM(std::string e);

	/**
	 * @brief gets entity of the company to pay by ATM transfer
	 * @return company's entity
	 */
	std::string getEntity() const;

	/**
	 * @brief gets reference of the service
	 * @return reference
	 */
	int getReference() const;

	/**
	 * @return "ATM"
	 */
	std::string getPaymentType() const;
};

/**
 * @brief Class that represents a Credit Card payment
 */
class CreditCard: public Payment{ //Permitido apenas a clientes empresariais registados taxa de 5%
	std::string cardNumber;
	static float tax;
public:
	/**
	 * Credit Card Default Constructor
	 */
	CreditCard();

	/**
	 * Credit Card Default Destructor
	 */
	~CreditCard(){};

	/**
	 * Credit Card Constructor
	 */
	CreditCard(std::string creditCardID);

	/**
	 * @brief gets credit card number
	 * @return credit card number
	 */
	std::string getCardNumber() const;

	/**
	 * @return credit card tax
	 */
	static float getTax();

	/**
	 * @return "Credit Card"
	 */
	std::string getPaymentType() const;

};

/**
 * @brief Class that represents a Bank Transfer payment
 */
class BankTransfer: public Payment{
	std::string IBAN;
public:
	/**
	 * Bank Transfer Default Constructor
	 */
	BankTransfer();

	/**
	 * Bank Transfer Constructor
	 */
	BankTransfer(std::string iban);

	/**
	 * @brief gets company IBAN to make payment
	 * @return company's IBAN
	 */
	std::string getIBAN() const;

	/**
	 * @return "Bank Transfer"
	 */
	std::string getPaymentType() const;
};

/**
 * @brief Class that represents a payment payable until the end of the month
 */
class EndOfMonth: public Payment{
	int endMonth;
public:
	/**
	 * End of Month Default Constructor
	 */
	EndOfMonth();

	/**
	 * End Of Month Constructor
	 */
	EndOfMonth(int month);

	/**
	 * @brief gets month to pay
	 * @return month to pay
	 */
	int getEndMonth() const;

	/**
	 * @return "Payable until the end of month"
	 */
	std::string getPaymentType() const;
};




#endif /* PAYMENT_H_ */
