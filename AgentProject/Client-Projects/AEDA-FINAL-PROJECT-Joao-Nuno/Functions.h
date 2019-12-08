/*
 * Functions.h
 *
 *  Created on: 14/11/2017
 *      Author: nl
 */

#ifndef FUNCTIONS_H_
#define FUNCTIONS_H_


/**
 * @brief - Initializes the full program with information from .txt files
 *
 */
void initialize();


/**
 * @brief - Initializes the full program with new information,
 * erasing any older information. Creates an association and
 * network from scratch
 *
 */
void initialize2();

/**
 * @brief - Shows a menu with all the functions concerning the year
 */
void ano();


//-----------------------FILES--------------------------//

/**
 * @brief - Read data from the area's files and create them,
 * storing them in the association
 *
 */
void lerficheiroAreas();

/**
 * @brief - Read data from the association's files and create them,
 * storing them in the association
 *
 */
void lerficheiroAssociacao();

/**
 * @brief - Read data from the associate's files and create them,
 * storing them in the association
 *
 */
void lerficheiroAssociados();

/**
 * @brief - Read data from the event's files and create them,
 * storing them in the association
 *
 */
void lerficheiroEventos();

/**
 * @brief - Read data from the mails' files and create them,
 * storing them in the association
 *
 */
void lerficheiroMails();

/**
 * @brief - Saves the new information made during running time about
 * areas to it's respective file
 */
void guardarficheiroAreas();

/**
 * @brief - Saves the new information made during running time about
 * the association to it's respective file
 */
void guardarficheiroAssociacao();

/**
 * @brief - Saves the new information made during running time about
 * associates to it's respective file
 */
void guardarficheiroAssociados();

/**
 * @brief - Saves the new information made during running time about
 * events to it's respective file
 */
void guardarficheiroEventos();

/**
 * @brief - Saves the new information made during running time about
 * mails to it's respective file
 */
void guardarficheiroMails();

/**
 * @brief - Cleans all the files, erasing all the older information,
 * thus enabling the possibilty of a fresh start
 *
 */
void limparficheiros();


//----------------------ASSOCIATES---------------------//

/**
 * @brief - Deals with user input, through iostream, in order
 * to create and add a new associate.
 *
 */
void adicionarAssociado();

/**
 * @brief - Deals with user input, through iostream, in order
 * to remove an existing associate.
 *
 */
void removerAssociado();

/**
 * @brief - Deals with user input, through iostream, in order
 * to change some information about an existing associate.
 *
 */
void alterarAssociado();

/**
 * @brief - Allows the user to see information regarding the associates
 * in several always, asking him for several criteria.
 *
 */
void verInfoAssociado();


//----------------------EVENTS-------------------------//
/**
 * @brief - Deals with user input, through iostream, in order
 * to create and add a new event.
 *
 */
void criarEvento();

/**
 * @brief - Deals with user input, through iostream, in order
 * to remove an existing event.
 *
 */
void removerEvento();

/**
 * @brief - Deals with user input, through iostream, in order
 * to change some information about an existing event.
 *
 */
void alterarEvento();

/**
 * @brief - Allows the user to see information regarding the events
 * in several always, asking him for several criteria.
 *
 */
void verInfoEvento();

/**
 * @brief - Organizes the vector containing all the events accordingly to some
 * criteria specified by the user.
 *
 */
void organizarEventos();


//-----------------------COTAS-------------------------//


/**
 * @brief - Manages the payment of an associate's bill, through user input.
 *
 */
void pagarCotas();


/**
 * @brief - Calls an association's function to make the automatic payment for all the associates.
 * Shows on the screen the information about the payments that could not be done, and why.
 *
 */
void pagarTodasCotas();


/**
 * @brief - Allows the user to see information about the associate's bills and payments
 */

void verAssociadosCotas();


//-----------------------REDE--------------------------//

/**
 * @brief - Publishes a new Mail to the network through user input.
 * The user becomes a certain associate, given that only some of them
 * can actually publish in the network;
 *
 */
void divulgarEmail();

/**
 * @brief - Allows the user to see the Mails present in the Network.
 * The user briefly becomes a certain associate, given that only some of them
 * can actually see into network;
 */

void verEmails();


/**
 * @brief - Organizes the vector containing all the mails accordingly to some
 * criteria specified by the user.
 *
 */
void organizarMails();



#endif /* FUNCTIONS_H_ */
