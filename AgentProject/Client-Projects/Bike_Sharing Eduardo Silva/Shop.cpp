#include "Shop.h"

//OPERATOR OVERLOADING
ostream& operator<< (ostream& out, const bike_t& bike) {

    out << enumtostr(bike);

    return out;

}

bool Shop::operator< (const Shop &s1) const
{
    return getReputation() < s1.getReputation();
}

string enumtostr(bike_t type) {

    string bike;

    switch(type) {
        case UB:
            bike = "UB";
            break;
        case US:
            bike = "US";
            break;
        case CH:
            bike = "CH";
            break;
        case RC:
            bike = "RC";
            break;
    }

    return bike;
}

bike_t strtoenum(string type) {

    bike_t bike;

	if (type == "US")
		bike = US;
	else
		if (type == "UB")
			bike = UB;
		else
			if (type == "CH")
				bike = CH;
			else
				bike = RC;

    return bike;
}

//SHOP
Shop::Shop() {
    bike_t bike;
    int bike_st = 0;

    this->stock.clear();

    bike = US;
    this->stock.push_back(CreateBikeStock(bike, bike_st));
    bike = UB;
    this->stock.push_back(CreateBikeStock(bike, bike_st));
    bike = CH;
    this->stock.push_back(CreateBikeStock(bike, bike_st));
    bike = RC;
    this->stock.push_back(CreateBikeStock(bike, bike_st));
}

Shop::Shop(int rep, string name, vector<bike_stock> bikest)
{
	this->reputation = rep;
	this->name = name;
	this->stock = bikest;
}

Shop::Shop(int rep, string name) 
{

    this->reputation = rep;
    this->name = name;

    bike_t bike;
    int bike_st = 0;

    this->stock.clear();

    bike = US;
    this->stock.push_back(CreateBikeStock(bike, bike_st));
    bike = UB;
    this->stock.push_back(CreateBikeStock(bike, bike_st));
    bike = CH;
    this->stock.push_back(CreateBikeStock(bike, bike_st));
    bike = RC;
    this->stock.push_back(CreateBikeStock(bike, bike_st));

}


bike_stock Shop::CreateBikeStock(bike_t bike, int stock) {

    bike_stock temp;

    temp.first = bike;
    temp.second = stock;

    return temp;

}

string Shop::getName() const{

    return this->name;
}

int Shop::getReputation() const {

    return this->reputation;
}
vector< bike_stock > Shop::getStock() const {

    return this->stock;
}

void Shop::setName(string new_name) {

    this->name = new_name;
}

void Shop::setReputation(int rep) {

    this->reputation = rep;
}

void Shop::setStock(vector< bike_stock > stock_bikes) {

    this->stock = stock_bikes;
}

int Shop::calculateReputation(int old_rep, int buyer_rating) {

    return (old_rep + buyer_rating) / 2;

}

void Shop::updateReputation() {

    int rat, rep;

    cout << "Purchase rating (number between 1 and 5): ";
    cin >> rat;

	while (cin.fail() || (rat < 1 || rat > 5))
	{
		cin.clear();
		cin.ignore(1000, '\n');
		cout << endl << "Invalid option! Please try again\n" << endl;
		cin >> rat;
	}

    rep = this->getReputation();
    this->setReputation(calculateReputation(rep, rat));


}

void Shop::addtoStock(bike_t type, int number) {

    vector<bike_stock> shop_stock = this->getStock();

    for(auto &biket: shop_stock) {

        if (biket.first == type) {
            biket.second += number;
            this->setStock(shop_stock);
            return;
        }
    }

}

void Shop::showShop() const 
{

    vector< bike_stock > temp = this->stock;

    cout << "________Shop " << this->name << "__________\n";
    cout << "Reputation: " << this->reputation << endl;
    cout << "Bike Stock:" << endl;

    for(unsigned int i = 0; i < temp.size(); i++) 
	{

        cout << temp.at(i).first << " - " << temp.at(i).second << endl;
    }

}

bool Shop::checkStock(vector<bike_stock> purchase_request) const 
{
    vector< bike_stock > temp = this->stock;

    for(const auto &bike_request : purchase_request) 
	{
        for(const auto &search : temp) 
		{

            if (search.first == bike_request.first && search.second < bike_request.second)
                return false;

        }
    }

    return true;
}

int Shop::removeStock(vector<bike_stock> purchase_req) 
{
    vector<bike_stock> temp_stock = this->getStock();

    for(const auto &bike_request : purchase_req) {

        for(auto &search : temp_stock) 
		{
			if (search.first == bike_request.first)
			{
				search.second -= bike_request.second;
				break;
			}

        }

    }

    this->setStock(temp_stock);

    return 0;

}

int Shop::makePurchase(vector<bike_stock> purchase) {

    if (this->checkStock(purchase))
	{
        this->removeStock(purchase);
        return 0;
    }

    return 1;

}

void Shop::print_test() {

    string name = "oi";
    Shop s(5, name);
    int five = 5;
    bike_stock bs = CreateBikeStock(UB, five);
    bike_stock bs2 = CreateBikeStock(US, five);

    bike_t b = UB;
    s.stock.push_back(bs);

    cout << bs.first << endl;

}
