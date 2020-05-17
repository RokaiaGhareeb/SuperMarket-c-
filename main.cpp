#include <iostream>
#include <fstream>
using namespace std;

void menu();

//** class for the products**//
class product
{
public:
    int code;
    char pro_name[10];
    int price;
};


//Function for add products**//
void create()
{
    char c;
    product pr;
    do
    {
        cout << "Enter product code " << endl;
        cin >> pr.code;
        cout << "Enter product name" << endl;
        cin >> pr.pro_name;
        cout << "Enter product price" << endl;
        cin >> pr.price;
        ofstream file;
        file.open("Shop.txt", ios :: out | ios :: app);
        file.write((char*) &pr, sizeof(pr));
        file.close();
        cout << "Product added successfully" << endl;
        cout << "To add new product press 'y': ";
        cin >> c;
    }
    while(c == 'y');
}

//*Function to view all records of product*//
void display_all()
{
    product pr;
    cout << "\n\n\n\t\tDISPLAY ALL RECORD !!!\n\n";
    ifstream file;
    file.open("Shop.txt", ios :: in);
    if(file.is_open())
    {
        cout << "Product code \t Product name \t Product price" << endl;
        while(file.read((char*)&pr,sizeof(product)))
        {
            cout << pr.code << "\t\t" << pr.pro_name << "\t\t" << pr.price << endl;
        }
        file.close();
    }
    else
    {
        cout << "ERROR, Cannot find the file" << endl;
    }
}

//*Function to modify product by code*//
void modify()
{
    product pr;
    fstream file;
    int code;
    cout << "Enter the code of the product to be update" << endl;
    cin >> code;
    file.open("Shop.txt");
    if(file.is_open())
    {
        while(file.read((char*)&pr, sizeof(pr)))
        {
            if(code == pr.code)
            {
                cout << "Enter new data" << endl;
                cin >> pr.pro_name >> pr.price;
                int sizeOfrec = file.tellg() - sizeof(pr);
                file.seekp(sizeOfrec, ios :: beg);
                file.write((char*)&pr, sizeof(pr));
                break;
            }
        }
        file.close();
        cout << "Product updated successfully" << endl;
    }
    else
    {
        cout << "ERROR, Cannot find the file" << endl;
    }
}

//*function to delete record of file*//
void delete_product()
{
    ifstream file1("Shop.txt");
    ofstream file2("Temp.txt");
    product pr;
    int code;
    cout << "\n\nPlease Enter The product code of The Product You Want To Delete";
    cin >> code;
    if(file1.is_open())
    {
        while(file1.read((char*)&pr,sizeof(product)))
        {
            if(pr.code != code)
            {
                file2.write((char*)&pr,sizeof(product));
            }
        }
        file1.close();
        file2.close();
        remove("Shop.txt");
        rename("Temp.txt","Shop.txt");
        cout << "\n\n\tRecord Deleted ..";
    }
    else
    {
        cout << "ERROR, Cannot find the file" << endl;
    }


}

//**order billing**//
void place_order()
{
    int code, quan;
    float total = 0;
    char ch = 'Y';
    cout << "\n============================";
    cout << "\n PLACE YOUR ORDER";
    cout << "\n============================\n";
    do
    {
        cout << "\n\nEnter The Product code Of The Product : " << endl;
        cin >> code;
        cout << "\nQuantity in number : ";
        cin >> quan;
        ifstream file("Shop.txt");
        product pr;
        while(file.read((char*)&pr,sizeof(product)))
        {
            if(pr.code == code)
            {
                total += pr.price * quan;
                break;
            }
        }
        file.close();
        cout << "\nDo You Want To Order Another Product ? (y/n)";
        cin >> ch;
    }
    while(ch == 'y');
    cout << "\n\nThank You For Placing The Order" << endl;
    cout << "\n********************************INVOICE************************\n" << endl;
    cout << "\n\n\t\t\t\t\tTOTAL = " << total;
}

//**function to choose customer or admin**//
void menu()
{
    int enter;
    cout << "To Get bill enter 1" << endl << "Admin options enter 2" << endl;
    cin >> enter;
    switch(enter)
    {
    case 1:
        place_order();
        break;
    case 2:
        int admch;
        cout << "Choose what you need to do : " << endl;
        cout << "TO add new product enter (1)" << endl;
        cout << "TO modify product enter (2)" << endl;
        cout << "TO View Product enter (3)" << endl;
        cout << "TO delete product enter (4)" << endl;
        cin >> admch;
        switch(admch)
        {
        case 1:
            create();
            break;
        case 2:
            modify();
            break;
        case 3:
            display_all();
            break;
        case 4:
            delete_product();
            break;
        }
    }

}


int main()
{
    cout << "           == Welcome Darling ==" << endl <<"  To close the program press  (ctrl + z) TO SHOW options press c for every time" << endl;
    char close;
    while(cin >> close)
    {
        if(close == EOF)
            break;
        else
            menu();
    }
    return 0;
}
