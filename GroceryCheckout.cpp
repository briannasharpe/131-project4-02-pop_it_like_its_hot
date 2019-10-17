#include	<iostream>
#include <stdexcept>
#include	"GroceryCheckout.h"

using namespace std;

bool GroceryInventory::AddItem(const string& name, int quantity, float price, bool taxable) {
	if (aMap.find(name) != aMap.end()) { //check for duplicate
		return false;
	} else {
		GroceryItem item(name, quantity, price, taxable);
		aMap[name] = item;
		return true;
	} //if
} //AddItem

void GroceryInventory::CreateFromFile(const string& fileName) {
    ifstream	file(fileName);
	string		name;
	float		price;
	int			quantity;
	bool		taxable;
	
	if (file.is_open()) {
		while (true) {
			file >> name >> quantity >> price >> taxable;
			if (!file.fail()) {
				AddItem(name, quantity, price, taxable);
			} else {
				break;
			}
         }
        file.close();
    } else {
        cout << "Could not open file " + fileName << endl;
    }
	
	return;
}

Receipt GroceryInventory::CreateReceipt(const string& fileName) {
	Receipt receipt;
	
	ifstream	file(fileName);
	string name;
	//add file's components to the item vector of the receipt
		if (file.is_open()) {
		while (true) {
			file >> name;
			if (!file.fail()) {
				map<string,GroceryItem>::iterator it = aMap.find(name); //find the item in the map
				receipt.item_.push_back(ReceiptItem(name, it->second.price_)); //add to item vector
				receipt.subtotal_ += it->second.price_; //add price to subtotal
				it->second.quantity_--; //decrease quantity by one
				
				if (it->second.taxable_ == true) { //if taxable
					receipt.taxAmount_ += it->second.price_ * taxRate_; //calculate tax
				} //if
			} else {
				break;
			} //if
         } //while
        file.close();
    } else {
        cout << "Could not open file " + fileName << endl;
    } //if file
	
	receipt.total_ = receipt.subtotal_ + receipt.taxAmount_; //calculate total
	
	return receipt;
} //CreateReceipt

GroceryItem*	GroceryInventory::FindItem(const string& name) {
	if (aMap.find(name) == aMap.end()) { //if not found
		return nullptr;
	} else { //find and return
		map<string,GroceryItem>::iterator it = aMap.find(name);
		return &it->second;
	} //if
} //FindItem

bool GroceryInventory::RemoveItem(const string& name) {
	if (aMap.find(name) == aMap.end()) { //if not found
		return false;
	} else { //find and erase
		map<string,GroceryItem>::iterator it = aMap.find(name);
		aMap.erase(it);
		return true;
	} //if
} //RemoveIt

void GroceryInventory::SetTaxRate(float taxRate) {
	 taxRate_ = taxRate / 100;
}

size_t GroceryInventory::Size() {
	return aMap.size();
}