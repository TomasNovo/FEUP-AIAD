#ifndef MENU_H
#define MENU_H

#include "praias.h"
#include <string>
#include <vector>



/**
 * @brief      Class for controlling the flow of the menu.
 */
class menu {

	std::string inputfilename; /*!< The filename of the input file */
	GestorPraias gestor; /*!< The object of the class that manages river beaches */
	unsigned int width = 100; /*!< The width of the console interface */
	unsigned int height = 30; /*!< The height of the console interface */
	std::vector<std::string> banner; /*!< The 2-dimentional array of chars of the banner */

public:

	/**
	 * @brief      The object contructor.
	 */
	menu();
	
	/**
	 * @brief      The object contructor with specified width and height.
	 *
	 * @param[in]  widht   The widht
	 * @param[in]  height  The height
	 */
	menu(unsigned int widht, unsigned int height);

	/**
	 * @brief      Function that calls PreMenu().
	 */
	void Begin();
	
	/**
	 * @brief      The menu that gets the filenames.
	 */
	void PreMenu();
	
	/**
	 * @brief      The main menu used to index and select functions.
	 */
	void MainMenu();
	
	/**
	 * @brief      Menu for adding a river beach to the BST.
	 */
	void AddPraia();
	
	/**
	 * @brief      Erases a river beach from the BST.
	 */
	void RemovePraia();
	
	/**
	 * @brief      Sets the bandeiraazul member variable of a praiaFluvial of the BST.
	 */
	void EditBandeira();
	
	/**
	 * @brief      Makes an inspection of a praiaFluvial servico.
	 */
	void MakeInspectionPraia();
	
	/**
	 * @brief      Closes a servicoForaDaPraia.
	 */
	void CloseService();
	
	/**
	 * @brief      Opens a servicoForaDaPraia.
	 */
	void OpenService();
	
	/**
	 * @brief      Lists praiaFluvial inside of the BST, by the specific order.
	 */
	void ListPraias();
	
	/**
	 * @brief      Lists praiaFluvial by conselho.
	 */
	void ListByConcelho();
	
	/**
	 * @brief      Prompts the user for the name or GPS of a praiaFluvial.
	 */
	void SearchPraia();
	
	/**
	 * @brief      Search nearest praiaFluvial to promtped GPS coordinates.
	 */
	void SearchNearestPraia();
	
	/**
	 * @brief      Lists the servicoForaDaPraia at less than 5 kilometers of the prompted praiaFluvial.
	 */
	void SearchServices();

	/**
	 * @brief      Gets the width of the console.
	 *
	 * @return     The width.
	 */
	unsigned int getWidth();
	
	/**
	 * @brief      Gets the height of the console.
	 *
	 * @return     The height.
	 */
	unsigned int getHeight();

	/**
	 * @brief      Sets the width of the console.
	 *
	 * @param[in]  width  The width
	 */
	void setWidth(unsigned int width);

	/**
	 * @brief      Sets the height of the console.
	 *
	 * @param[in]  height  The height
	 */
	void setHeight(unsigned int height);
	
	/**
	 * @brief      Loads the banner to the banner member variable.
	 *
	 * @param[in]  filename  The filename of the banner
	 *
	 * @return     True if file exits and False otherwise
	 */
	bool LoadBanner(std::string filename);
	
	/**
	 * @brief      Prints the banner to the standard output
	 */
	void PrintBanner();
	
	/**
	 * @brief      Prints the banner to the standard output with specified width
	 *
	 * @param[in]  width  The width
	 */
	void PrintBanner(unsigned int width);

};



#endif