#include	<iostream>
#include <stdexcept>
#include <string>
#include	"GroceryCheckout.h"

using namespace std;

//Default Constructor implementation
GroceryInventory::GroceryInventory() {
	invSize = 0; //initialize size to 0;
	myIterator = myInventory.begin(); // set iterator to beginning of myInventory;
	myTaxRate = 0.0; //initialize tax rate variable
}

bool GroceryInventory::AddItem(const string& name, int quantity, float price, bool taxable)
{
	//Check if myInventory already contains the name. If it does, return false. Otherwise continue AddItem function.
	if(myInventory.find(name) != myInventory.end())
	{
		return false;
	}
	// create a new grocery item struct-instance w/ given parameters
	GroceryItem tempItem = GroceryItem(name, quantity, price, taxable);
	//insert the tempItem into map with key = name
	myInventory.insert({name, tempItem});
	invSize++; //increment size variable
	//return true to indicate successful insert
	return true;
}

void GroceryInventory::CreateFromFile(const string& fileName) //given function. Did not touch.
{
    ifstream	file(fileName);
	string		name;
	float		price;
	int			quantity;
	bool		taxable;

	if (file.is_open())
	{
		while (true)
		{
			file >> name >> quantity >> price >> taxable;
			if (!file.fail())
			{
				AddItem(name, quantity, price, taxable);
			}
			else
			{
				break;
			}
         }
        file.close();
    }
	else
	{
        cout << "Could not open file " + fileName << endl;
    }

	return;
}

Receipt GroceryInventory::CreateReceipt(const string& fileName)
{
		Receipt myReceipt; //final receipt object to return
		ReceiptItem tempRItem; // receipt item that will be inserted into the vector inside myReceipt
		ifstream file(fileName);
		string fName;
		float subtotal = 0.0;
		float taxableAmt = 0.0;
		while(true){
			file >> fName;
			if(!file.fail()) //read until file >> fname failes.
			{
				myIterator = myInventory.begin(); //reset the iterator
				myIterator = myInventory.find(fName); // find the Item by the key from file
				myIterator->second.quantity_ -= 1; // reduce the quantity of that item
				tempRItem = ReceiptItem(fName, myIterator->second.price_); //make the tempRItem object
				subtotal += myIterator->second.price_; // add price to subtotal
				if(myIterator->second.taxable_)// add price to taxable amt if item is taxable
					taxableAmt += myIterator->second.price_;
				myReceipt.item_.push_back(tempRItem); // push tempRItem into the item_ vector inside the receipt
			}
			else{
				break; //break out of while loop when end of file is reached.
			}
		}
		file.close(); //close the file
		myReceipt.subtotal_ = subtotal; //put subtotal into myReceipt
		myReceipt.taxAmount_ =  taxableAmt * (myTaxRate/100); // calculate tax taxAmount and insert into myReceipt
		myReceipt.total_ = subtotal + myReceipt.taxAmount_; //calculate total and insert into myReceipt
		return myReceipt; //return the completed receipt
}

GroceryItem*	GroceryInventory::FindItem(const string& name)
{
		myIterator = myInventory.begin();
		myIterator = myInventory.find(name);
		if(myIterator == myInventory.end())
			return nullptr;
		return &myIterator->second;
}

bool GroceryInventory::RemoveItem(const string& name)
{
	myIterator = myInventory.find(name); // look for key
	if(myIterator == myInventory.end())// if key is not found return false
		return false;
	// if key is found erase the key. Iterator must have stopped at the key we are looking for
	myInventory.erase(myIterator);
	invSize--;//decrement size variable.
	return true; //return true to signify success
}

void GroceryInventory::SetTaxRate(float taxRate)
{
		myTaxRate = taxRate;
}

size_t GroceryInventory::Size()
{
	return invSize;
}
