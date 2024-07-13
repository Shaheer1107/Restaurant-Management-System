
#include <iostream>
#include <Windows.h>
#include <chrono>
#include <thread>
#include <conio.h>
#include <stdio.h>
#include <cstring>
#include <fstream>
#include <sstream>
#include<string>
using namespace std;

class Node
{
public:
	float price;
	string catogory;
	string ItemName;
	Node* left;
	Node* right;

	Node()
	{
		catogory = "";
		ItemName = "";
		price = NULL;
		left = NULL;
		right = NULL;
	}

};
class stack;
class CustomerDetails
{
public:
	string Name;
	int Family_Number;
	string Phone_Number;
	float bill;
	CustomerDetails() {}

	CustomerDetails(string n, int f, string p)
	{
		Name = n;
		Family_Number = f;
		Phone_Number = p;
		bill = 0;
	}

	void ReserveTable(int option, char** arr)
	{
		bool check_regular = 0, check_VIP = 0;
		if (option == 1)
		{
			int i = 0, j = 0;
			while (i < 5)
			{
				if (arr[i][j] == 'A')
				{
					arr[i][j] = 'P';
					break;
				}
				j++;
				if (j == 5)
				{
					j = 0;
					i++;
				}
			}

		}

		else
		{
			int i = 5, j = 0;
			while (i < 10)
			{
				if (arr[i][j] == 'A')
				{
					arr[i][j] = 'P';
					break;
				}
				j++;
				if (j == 5)
				{
					j = 0;
					i++;
				}
			}

		}
	}

	void Display()
	{
			cout << "\t\t\t\tCHECKOUT...\n";
			cout << "\t\t\tCustomer Name: " << Name << endl;
			cout << "\t\t\tFamily Member: " << Family_Number << endl;
			cout << "\t\t\tPhone Number: " << Phone_Number << endl;
			
	}
};
void cost(Node* root,string i,float &temp)
{
	if (root)
	{
		if (root->ItemName == i)
		{
			temp = root->price;
			return;
		}
		cost(root->left, i,temp);
		cost(root->right, i,temp);
	}
}
class kitchen_queue
{
	public:
		int* order; string* order_name;
		int front, size,rear;
		kitchen_queue()
		{
			order = new int[12];
			order_name = new string[12];
			front= -1;
			rear = -1;
			size = 12;
		}
		void insertorder(int id,string n)
		{
			rear++;
			if (front == -1)
			{
				front++;
				order[front] = id;
				order_name[front] = n;
			}
			else
			{
				order[rear] = id;
				order_name[rear] = n;
			}
		}
		void dequeue()
		{
			front++;
		}
		void orderskitchen()
		{
			if (front == -1)
			{
				cout << "\tNO ORDER IN PROCESS.\n";
			}
			else
			{
				cout << "\t\tORDERS IN PROOCESS...\n";
				cout << "\tID\tName\n";
				for (int i = front; i <= rear; i++)
				{
					cout << "\t" << order[i] << "\t" << order_name[i] << endl;
				}
			}
		}
};
void Menu(Node* root)
{
	if (root)
	{
		cout << "\t\t" << root->ItemName << "\t\t" <<"Rs "<< root->price << endl;
		Menu(root->left);
		Menu(root->right);
	}
}
class stack
{
public:
	float* arr; float* undo_arr;
	int* quant; int* undo_quant;
	int top, size,undo_top;
	string* item_s; string* undo_item;
	stack()
	{
		arr = new float[12];
		item_s = new string[12];
		quant = new int[12];
		undo_arr = new float[12];
		undo_quant = new int[12];
		undo_item = new string[12];
		undo_top = -1;
		top = -1;
		size = 12;
	}
	void insert(CustomerDetails& obj,Node *root)
	{
		string food; int quantity;
		cout << "\nWhat will you like to choose?:\t";
		cin >> food;
		cout << "Enter Quantity of "<<food<<":\t";
		cin >> quantity;
		float blnce;
		cost(root->left, food,blnce);
		blnce = blnce * quantity;
		obj.bill = obj.bill + blnce;
		top++;
		arr[top] = blnce;
		item_s[top] = food;       //2  Biryani   400
		quant[top] = quantity;
		string cont;
		cout << "Do you want to order any other item?:\t";
		cin >> cont;
		while (cont == "yes")
		{
			cout << "What will you like to choose?:\t";
			cin >> food;
			cout << "Enter Quantity of " << food << ":\t";
			cin >> quantity;
			float check;
			cost(root->left, food,check);
			check = check * quantity;
			obj.bill = obj.bill + check;
			top++;
			arr[top] = check;
			item_s[top] = food;       //2  Biryani   400
			quant[top] = quantity;
			cout << "Do you want to order any other item?:\t";
			cin >> cont;
		}
		system("cls");
		cout << "\t\t\tDESSERT\n\n";
		Menu(root->right);
		
		cout << "\nDo you want to order Dessert?:\t";
		cin >> cont;
		while (cont == "yes")
		{
			cout << "What will you like to choose?:\t";
			cin >> food;
			cout << "Enter Quantity of " << food << ":\t";
			cin >> quantity;
			float check;
			cost(root->right, food, check);
			check = check * quantity;
			obj.bill = obj.bill + check;
			top++;
			arr[top] = check;
			item_s[top] = food;       //2  Biryani   400
			quant[top] = quantity;
			cout << "Do you want to order any other item?:\t";
			cin >> cont;
		}
		display(obj);
	}
	void seeorder()
	{
		cout << "Quantity\tItem\n\n";
		for (int i = 0; i <= top; i++)
		{
			cout << quant[i] << "\t\t" << item_s[i] << endl;
		}
	}
	void final_display()
	{
		cout << "\t\tQuantity\tItem\t\tPrice\n\n";
		for (int i = 0; i <= top; i++)
		{
			cout <<"\t\t"<< quant[i] << "\t\t" << item_s[i] << "\t\tRs " << arr[i] << endl;
		}
		
		cout << endl;
	}
	void kitchen(CustomerDetails& obj)
	{
		cout << "\t\tQuantity\tItem\t\tPrice\n\n";
		for (int i = 0; i <= top; i++)
		{
			cout <<"\t\t"<< quant[i] << "\t\t\t" << item_s[i] << "\t\tRs " << arr[i] << endl;
		}
	}
	void display(CustomerDetails& obj)
	{
		system("cls");
		cout << "\t\tYOUR ORDER..." << endl;
		cout << "\tQuantity\tItem\tPrice\n\n";
		for (int i = 0; i <= top; i++)
		{
			cout <<"\t"<< quant[i] << "\t\t" << item_s[i] << "\t" << arr[i] << endl;
		}
		cout << endl;
		cout << "\tChoose one operation..\n\tCONFIRM \tUNDO\tREDO\n";
		string select;
		cin >> select;
		if (select == "Undo" || select == "UNDO")
		{
			undo_top++;
			undo_arr[undo_top] = arr[top];
			undo_quant[undo_top] = quant[top];
			undo_item[undo_top] = item_s[top];
			obj.bill = obj.bill - arr[top];
			top--;
			display(obj);
		}
		else if (select == "Redo" || select == "REDO")
		{
			if (undo_top == -1)
			{
				cout << "You can't Redo at this moment.\n";
			}
			else
			{
				top++;
				arr[top] = undo_arr[undo_top];
				quant[top] = undo_quant[undo_top];
				item_s[top] = undo_item[undo_top];
				obj.bill = obj.bill + undo_arr[undo_top];
				undo_top--;
				display(obj);
			}
		}
		else
		{
			system("cls");
			system("color 72");
			cout << "Your order has been placed successfully.\n";
			obj.Display();
			final_display();
			cout << endl;
			cout << "\t\t\t\tTotal Bill: Rs " << obj.bill << endl;
			cout << "Press any key to continue...";
			_getch();
			system("cls");
		}
		
	}

};
void categoryadd(string n, string c, float p, Node* root)
{
	if (p > root->price)
	{
		if (root->right == NULL)
		{
			Node* ptr = new Node();
			ptr->catogory = c;
			ptr->ItemName = n;
			ptr->price = p;
			root->right = ptr;
			return;
		}
		else
		{
			categoryadd(n, c, p, root->right);
		}
	}
	else if (p < root->price)
	{
		if (root->left == NULL)
		{
			Node* ptr = new Node();
			ptr->catogory = c;
			ptr->ItemName = n;
			ptr->price = p;
			root->left = ptr;
			return;
		}
		else
		{
			categoryadd(n, c, p, root->left);
		}

	}
}


void AddItem(string n, string c, float p, Node* root)
{
	if (c == "Menu" && n == "Menu")
	{
		root->catogory = c;
		root->ItemName = n;
		root->price = p;
		return;
	}
	else if (root->left==NULL && c == "Main-Course")
	{
		Node* ptr = new Node();
		ptr->catogory = c;
		ptr->ItemName = n;
		ptr->price = p;
		root->left = ptr;
		return;
	}
	else if (root->left != NULL && c == "Main-Course")
	{
		categoryadd(n, c, p, root->left);
		return;
	}
	else if (root->right==NULL && c == "Dessert")
	{
		Node* ptr = new Node();
		ptr->catogory = c;
		ptr->ItemName = n;
		ptr->price = p;
		root->right = ptr;
		return;
	}
	else if (root->right != NULL && c == "Dessert")
	{
		categoryadd(n, c, p, root->right);
		return;
	}

}


void table_show(char** arr, int cap_r, int cap_c)
{
	system("cls");
	cout << "\t\t\t\tTABLE RESERVATION\n\n";
	cout << "\t\t\t";
	for (int i = 0; i < cap_r; i++)
	{
		for (int j = 0; j < cap_c; j++)
		{
			if (arr[i][j] == 'P')
			{
				system("color 07");
				cout << arr[i][j] << "\t";
			}
			else
			{
				system("color F4");
				cout << arr[i][j] << "\t";
			}
			
		}
		cout << endl<<"\t\t\t";
	}
	cout << endl;
}

void seeinkitchen(stack* object,kitchen_queue &k)
{
	string opt;
	cout << "\n\tDo you want to see order items?:\t";
	cin >> opt;
	while (opt == "yes")
	{
		int n;
		cout << "\nEnter id of order:\t";
		cin >> n;
		object[n - 1].seeorder();
		cout << "\n\tDo you want to see another order items?:\t";
		cin >> opt;
	}
	cout << "\n\tIs the order ready?:\t";
	cin >> opt;
	if(opt=="yes")
	{
		k.dequeue();
		cout<<"Order Done.\n";
	}
	cout<<"Press any key to continue...\n";
	_getch();
	system("cls");
}
void signup()
{
	system("cls");
	cout << "\t\t\tSIGNUP" << endl;
	fstream file("Customer.txt", ios::in | ios::out | ios::app);
	if (file.is_open())
	{
		string email, password, n; int age;
		cout << "Enter your Name:\t";
		cin >> n;
		cout << "Enter your Age:\t";
		cin >> age;
		int x = 0;
		cout << "Enter your e-mail:\t";
		cin >> email;
		cout << "Enter your Password:\t";
		cin >> password;
		file.seekp(0, ios::end);
		file << email << "\t" << password <<"\t"<<n<<"\t"<<age<< endl;
		cout << "Successfully SignUp...\n";
		file.close();
    } 
	else 
	{
        cerr << "Error opening the file!" << endl;
    }
}
void login_check()
{
	string email, password;
	
	cout << "Enter your e-mail:\t";
	cin >> email;
	cout << "Enter your Password:\t";
	cin >> password;
	int x = 0; string line, mail,pass;
	while (x != 1)
	{
		fstream file("Customer.txt", fstream::in | fstream::out);
		while (getline(file, line)) {
			stringstream ss(line);
			ss >> mail>>pass;
			if (mail == email)
			{
				if (pass == password)
				{
					x = 1;
					break;
				}
			}
		}
		if (mail == email && pass == password)
		{
			x = 1;
			cout << "Successfully Login...\n";
			file.close();
		}
		else
		{
			cout << "Wrong credentials, try again.\n";
			cout << "Enter your e-mail:\t";
			cin >> email;
			cout << "Enter your Password:\t";
			cin >> password;
			file.close();
		}
	}
	
}
void login()
{
	system("cls");
	cout << "\n\t\t---------------------\t---------------------\n";
	cout << "\t\t|                   |\t|                   |\n";
	cout << "\t\t|      Login        |\t|      Sign Up      |\n";
	cout << "\t\t|\t\t    |\t|\t\t    |\n";
	cout << "\t\t---------------------\t---------------------";
	cout << "\nPress 1 for Login OR 2 for Sign Up\t";
	int choose;
	cin >> choose;
	if (choose == 2)
	{
		signup();
	}
	else if (choose == 1)
	{
		login_check();
	}
}
void admin(string a,string b,Node *root,CustomerDetails *obj,int i,stack *menu)
{
	string x,y;
	int check=0;
	while(check!=1)
	{
		cout<<"Enter username:\t";
		cin>>x;
		cout<<"Enter password:\t";
		cin>>y;
		if(x==a && y==b)
		{
			cout<<"Successfully Login...\n";
			check=1;
			cout<<"\nPress any key to continue...";
			_getch();
		}
		else
		{
			cout<<"Wrong Credentials...\n";
			check=0;
		}
	}
	system("cls");
	cout <<"\t\t\tAdmin\n\n";
	cout<<"\t\tChoose any operation to perform\n\n";
	cout<<"\t1\tAdd Item\n\t2\tCustomer Details"<<endl;
	cout<<"Select option:\t";
	int m;
	cin>>m;
	if(m==1)
	{
		string i,c;float p;
		cout<<"Enter item name:\t";
		cin>>i;
		cout<<"Enter item category:\t";
		cin>>c;
		cout<<"Enter item price:\t";
		cin>>p;
		AddItem(i, c,p, root);
		cout<<"Item Successfully Added.\n";
		cout<<"\nPress any key to continue...";
		_getch();
	}
	else if(m==2)
	{
		cout<<"ALL CUSTOMERS...\n";
		cout<<"\t\tID\tNAME\n\n";
		for(int j=0;j<i;j++)
		{
			cout<<"\t\t"<<j+1<<"\t"<<obj[j].Name<<endl;
		}
		cout<<"\nDo you want to see any customer bill?;\t";
		string g;
		cin>>g;
		while(g=="yes")
		{
			cout<<"Enter id of customer:\t";
			cin>>m;
			obj[m-1].Display();
			menu[m-1].final_display();
			cout << "\t\t\t\tTotal Bill: Rs " << obj[m-1].bill << endl;
			cout<<"\nDo you want to see any customer bill?;\t";
			cin>>g;
		}
	}
}
void feedback()
{
	cout<<"Would you like to give Feedback?:\t";
	string opt;
	cin>>opt;
	if(opt=="yes")
	{
		fstream file("Feedback.txt", ios::in | ios::out | ios::app);
		string feed;
		cout<<"Enter your feedback:\t";
		cin.ignore();
		getline(cin, feed);
		int star;
		cout<<"Rate out of 5 stars?:\t";
		cin>>star;
		file.seekp(0,ios::end);
		file<<feed<<"\t"<<star<<endl;
		file.close();
	}
}
int main()
{
	system("cls");
	system("color F4");
	kitchen_queue kitchen;
	int c = 0;
	string admin_user="admin";
	string admin_pass="admin";
	while (c <= 4)
	{
		for (int i = 0; i < c; i++)
		{
			cout << "\t\t";
		}
		cout << "WELCOME TO BTS RESTAURANT...";
		this_thread::sleep_for(std::chrono::seconds(1));
		c++;
		system("cls");
	}
	//HANDLE color = GetStdHandle(STD_OUTPUT_HANDLE);
	//SetConsoleTextAttribute(color, 23);
	system("color 91");
	cout << "\t\t\t\t\tWELCOME TO BTS RESTAURANT...\n";
	system("color F4");
	cout << "\n\t\t---------------------\t---------------------\t---------------------\t---------------------\n";
	cout << "\t\t|                   |\t|                   |\t|                   |\t|                   |\n";
	cout << "\t\t| Table Reservation!|\t|   Online Order!   |\t|      Kitchen      |\t|      Admin        |\n";
	cout << "\t\t|\t\t    |\t|\t\t    |\t|\t\t    |\t|\t\t    |\n";
	cout << "\t\t---------------------\t---------------------\t---------------------\t---------------------\n";

	int fno, option;
	string c_name, phone;
	cout << "\nPress 1 for Table Reservation , 2 for Online Order ,3 for Kitchen ,4 for admin and any other number to exit:\t";
	int choose;
	cin >> choose;
	int cap_row = 10;
	int cap_col = 5;
	char** table = new char* [cap_row];
	for (int i = 0; i < cap_row; i++)
	{
		table[i] = new char[cap_col];
		for (int j = 0; j < cap_col; j++)
		{
			table[i][j] = 'A';
		}
	}
	CustomerDetails obj[15];
	stack menuss[15];
	int i = 0,count=0;
	Node* root = new Node();
	AddItem("Menu", "Menu", 0, root);
	AddItem("Biryani", "Main-Course", 250, root);
	AddItem("Karahi", "Main-Course", 400, root);
	AddItem("Burger", "Main-Course", 450, root);
	AddItem("Fries", "Main-Course", 150, root);
	AddItem("Pizza", "Main-Course", 500, root);
	AddItem("Broast", "Main-Course", 600, root);
	AddItem("Nuggets", "Main-Course", 450, root);
	AddItem("Katakat", "Main-Course", 200, root);
	AddItem("Roll", "Main-Course", 375, root);
	AddItem("Chargha", "Main-Course", 550, root);
	AddItem("Pasta", "Main-Course", 750, root);
	AddItem("Pulao", "Main-Course", 300, root);
	AddItem("Custard", "Dessert", 650, root);
	AddItem("Kheer", "Dessert", 700, root);
	AddItem("Cake", "Dessert", 800, root);
	AddItem("Pudding", "Dessert", 600, root);
	AddItem("Kulfi", "Dessert", 300, root);
	AddItem("Kunafa", "Dessert", 850, root);
	AddItem("Rabri", "Dessert", 1000, root);
	AddItem("Baklava", "Dessert", 750, root);

	while (choose == 1 || choose == 2 || choose==3 || choose==4)
	{
		if (choose == 1)
		{
			table_show(table, cap_row, cap_col);
			cout << "Enter your Name: ";
			cin >> c_name;
			cout << "Enter number of family members: ";
			cin >> fno;
			cout << "Enter your Phone Number: ";
			cin >> phone;
			cout << "Enter 1 for regular table, 2 for VIP table: ";
			cin >> option;

			CustomerDetails o(c_name, fno, phone);
			o.ReserveTable(option, table);

			obj[i] = o;
			table_show(table, cap_row, cap_col);




			system("cls");

			cout << "\t\tMENU CATEGORIES...\n\n\t 1\tMain Course\n\t 2\tDessert\n\t\n";
			cin >> choose;
			while (choose != 1 && choose != 2 && choose != 3)
			{
				cout << "You entered the wrong key, Please try again.\n";
				cout << "\t\tMENU CATEGORIES...\n\n\t 1\tMain Course\n\t2\tDessert\n\t3Beverages\n";
				cin >> choose;
			}
			if (choose == 1)
			{
				system("cls");
				system("color 07");
				cout << "\t\t\tMENU\n\n";
				cout << "\t\tITEM\t\tPrice\n";
				Menu(root->left);
				menuss[i].insert(obj[i], root);
			}
			else if (choose == 2)
			{
				Menu(root->right);
			}
			//0 
			kitchen.insertorder(i + 1, c_name);
			i++;
			count++;
			feedback();
			cout<<"Press any key to continue..."<<endl;
			_getch();
			system("cls");
		}
		else if (choose == 2)
		{
			login();
			cout << "Press any key to continue...";
			_getch();
			system("cls");
				cout << "Enter your Name: ";
				cin >> c_name;
				cout << "Enter number of family members: ";
				cin >> fno;
				cout << "Enter your Phone Number: ";
				cin >> phone;

				CustomerDetails o(c_name, fno, phone);

				obj[i] = o;
				system("cls");
			cout << "\t\tMENU CATEGORIES...\n\n\t 1\tMain Course\n\t 2\tDessert\n\t\n";
			cin >> choose;
			while (choose != 1 && choose != 2 && choose != 3)
			{
				cout << "You entered the wrong key, Please try again.\n";
				cout << "\t\tMENU CATEGORIES...\n\n\t 1\tMain Course\n\t2\tDessert\n\t3Beverages\n";
				cin >> choose;
			}

			if (choose == 1)
			{
				system("cls");
				system("color 07");
				cout << "\t\t\tMENU\n\n";
				cout << "\t\tITEM\t\tPrice\n";
				Menu(root->left);
				menuss[i].insert(obj[i], root);
			}
			else if (choose == 2)
			{
				Menu(root->right);
			}
			//0 
			kitchen.insertorder(i + 1, c_name);
			i++;
			count++;
			feedback();
			cout<<"Press any key to continue..."<<endl;
			_getch();
			system("cls");

		}
		else if (choose == 3)
		{
			kitchen.orderskitchen();
			seeinkitchen(menuss,kitchen);
		}
		else if(choose==4)
		{
			system("cls");
			admin(admin_user,admin_pass,root,obj,i,menuss);
			cout<<"Press any key to continue...\n";
			_getch();
			system("cls");
		}
		//system("cls");
		system("color F4");
		cout << "\n\t\t---------------------\t---------------------\t---------------------\t---------------------\n";
		cout << "\t\t|                   |\t|                   |\t|                   |\t|                   |\n";
		cout << "\t\t| Table Reservation!|\t|   Online Order!   |\t|      Kitchen      |\t|      Admin        |\n";
		cout << "\t\t|\t\t    |\t|\t\t    |\t|\t\t    |\t|\t\t    |\n";
		cout << "\t\t---------------------\t---------------------\t---------------------\t---------------------\n";
		cout << "\nPress 1 for Table Reservation , 2 for Online Order ,3 for Kitchen ,4 for admin and any other number to exit:\t";
		cin >> choose;
	}
}
