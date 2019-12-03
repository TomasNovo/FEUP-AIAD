#ifndef AEDA_P1_SHOP_H
#define AEDA_P1_SHOP_H

#include <iostream>
#include <queue>
#include <vector>
#include <string>

using namespace std;

enum bike_t {UB, US, RC, CH};
typedef pair<bike_t, int> bike_stock;

class Shop
{
    string name;
    int reputation;
    vector< bike_stock > stock;

public:
    Shop();
	Shop(int rep, string name, vector<bike_stock> bikest);
    Shop(int rep, string name);
    bike_stock CreateBikeStock(bike_t bike, int stock);

    //GET FUNCS
    string getName() const;
    int getReputation() const;
    vector< bike_stock > getStock() const;

    //SET FUNCS
    void setName(string new_name);
    void setReputation(int rep);
    void setStock(vector< bike_stock > stock_bikes);

    //STOCK FUNCS
    void addtoStock(bike_t type, int number);
    bool checkStock(vector<bike_stock> purchase_request) const;
    int removeStock(vector<bike_stock> purchase_req);

    //PURCHASE FUNCS
    int makePurchase(vector<bike_stock> purchase);

    //PRINT SHOPS FUNCS
    void showShop() const;

    //REPUTATION FUNCS
    void updateReputation();
    int calculateReputation(int old_rep, int buyer_rating);

    //TEST FUNCTION
    void print_test();

    //Operator Overloading
    friend ostream& operator<< (ostream& out, const bike_t& bike);
    bool operator< (const Shop &s1) const;

};

string enumtostr(bike_t type);
bike_t strtoenum(string type);

#endif