#include	<iostream>
#include <stdexcept>
#include	"GroceryCheckout.h"

using namespace std;

bool GroceryInventory::AddItem(const string& name, int quantity,
							   float price, bool taxable)
{
	//	TO BE COMPLETED.
	GroceryItem tempItem = new GroceryItem(name, quantity, price, taxable); // create a new grocery item struct-instance w/ given parameters 

}

void GroceryInventory::CreateFromFile(const string& fileName)
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
	//	TO BE COMPLETED.
}

GroceryItem*	GroceryInventory::FindItem(const string& name)
{
	//	TO BE COMPLETED.
}

bool GroceryInventory::RemoveItem(const string& name)
{
	//	TO BE COMPLETED.
}

void GroceryInventory::SetTaxRate(float taxRate)
{
	//	TO BE COMPLETED.
}

size_t GroceryInventory::Size()
{
	//	TO BE COMPLETED.
}