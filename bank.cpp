#include<iostream>
#include <cstring>
#include<stdio.h>
#include <fstream>
#include <string.h>
#include <sstream>

using namespace std;

static int recordNo=0;

class customer{
private:
     int recordNo;
    char depositorName[30];
    int accNo;
    char typeOfAcc[10];
    int balance;
    char address[30];
    

public:
    customer()
    {
        recordNo;
       strcpy(depositorName,"Garbage Name");
        accNo=0;
        strcpy(typeOfAcc,"Garbage type");
        balance=0;
        strcpy(address,"Paradise");
    }
    
    // float getBal()
    // {
    //     return balance;
    // }
    // string getName()
    // {
    //     return depositorName;
    // }

    // int getAccNo()
    // {
    //     return accNo;
    // }
    // string accType()
    // {
    //     return typeOfAcc;
    // }
    
    // void setBal(float bal)
    // {
    //     balance=bal;
    // }
    // void setName(char* name)
    // {
    //     depositorName=name;
    // }

    // void setAccNo(int acc)
    // {
    //     accNo=acc;
    // }
    // void setAccType(string typeAcc)
    // {
    //     typeOfAcc=typeAcc;
    // }
    
    //void deleteCustomer(char*);
    
    void viewAllData();
   
    void getBankData()
    {
        cout<<"Enter your Name ,accnumber,typeOfAcc,balance,Address\n";
        cout<<"\n Enter depositor name\n";
          cin.ignore();
        cin.getline(depositorName,29);
        cout<<"\n Enter account Number\n";
         cin.ignore();
        cin>>accNo;       
        cout<<"\n Enter type of Account\n";
         cin.ignore();
        cin.getline(typeOfAcc,9);
       
        cout<<"\n Enter Address\n";
        cin>>address;
        
    }
     
    void showBankData(){
        cout<<"\n"<<recordNo<<" "<<depositorName<<" "<<accNo<<" "<<typeOfAcc<<" "<<balance<<" "<<address<<endl;
    }
    
    int storeData();
    void deleteCustomer(char*);
    int searchCustomer(int);
    void depositMoney(int,int);
    void withdrawMoney(int,int);
    void displayLastAccNo();
    int searchCustomerReturnAddress(int);
    int searchCustomerReturnDepoistorName(int);
    int searchCustomerReturnBalance(int);
    int searchCustomerReturnAll(int );
    void searchCustomerReturnRecord(int );
};

int customer::storeData()
{

    if(accNo==0 ||accNo<0 )
    {    
        cout<<"\nBank Data not initialized"<<endl;
        return 0;    
    }    


    ofstream fout;
    fout.open("CustomerDataFile.dat",ios::app|ios::binary);
    fout.write((char*)this,sizeof(*this));
    fout.close();
    return(1);
}

void customer::viewAllData()
{
    ifstream fin;
    fin.open("CustomerDataFile.dat",ios::in|ios::binary);
    if(!fin)
        cout<<"\n File not found"<<endl;
    else
    {
    fin.read((char*)this,sizeof(*this));
    while(!fin.eof())
    {
        showBankData();
        fin.read((char*)this,sizeof(*this));
    }
    
    fin.close();
    }
}

void customer::deleteCustomer(char* t)
{
    ifstream ifs;
    ofstream ofs;
    int flag =0;
    
    ifs.open("CustomerDataFile.dat", ios::in|ios::binary);
    if(!ifs)
        cout<<"\n File not found"<<endl;
    else
    {
    ofs.open("Tempfile.dat",ios::out|ios::binary);
    ifs.read((char*)this,sizeof(*this));
    
    while(!ifs.eof())
    {
        if(strcmp(depositorName,t))
            ofs.write((char*)this,sizeof(*this));
             flag =1;
        ifs.read((char*)this,sizeof(*this));
    }
    ifs.close();
    ofs.close();
    remove("CustomerDataFile.dat");
    rename("Tempfile.dat","CustomerDataFile.dat");
    if(flag=0){
        cout<<"\n No such record exist";
    }
    if(flag=1)
        cout<<"\n delete successfull";
    }
}
int customer::searchCustomer(int t)
{
    ifstream ifs;
        
    ifs.open("CustomerDataFile.dat", ios::in|ios::binary);
    if(!ifs)
        cout<<"\n File not found";
    else
    {
    ifs.read((char*)this,sizeof(*this));
    
    while(!ifs.eof())
    {
        if(accNo==t)
        { 
            ifs.close();
               return 1;
        }
        ifs.read((char*)this,sizeof(*this));
    }
    ifs.close();
    return 0;
    
    }
}
int customer::searchCustomerReturnAll(int t)
{
    ifstream ifs;
        
    ifs.open("CustomerDataFile.dat", ios::in|ios::binary);
    if(!ifs)
        cout<<"\n File not found"<<endl;
    else
    {
    ifs.read((char*)this,sizeof(*this));
    
    while(!ifs.eof())
    {
        if(accNo==t)
        { 
            ifs.close();
            cout<<"\n Account Holder Name is "<<depositorName;
              cout<<"\n Account Number is  "<<accNo;
              cout<<"\n Account Balance is  "<<balance;
            cout<<"\n Account Holder Address is "<<address<<endl;

            

               return 1;
        }
        ifs.read((char*)this,sizeof(*this));
    }
    ifs.close();
    return 0;
    
    }

}


void customer::depositMoney(int money,int acc)
{
    fstream file;
    

    file.open("CustomerDataFile.dat",ios::in|ios::out|ios::ate|ios::binary);
    file.seekg(0); //g/p pointer points to last by default so we're setting it to beginning of file
    file.read((char*)this,sizeof(*this));

    while(!file.eof())
    {
        if(accNo==acc)
         {
             file.seekp(file.tellp() - sizeof(*this));
             balance = balance + money;
             file.write((char*)this,sizeof(*this));
             return;
         }
        file.read((char*)this,sizeof(*this));
    }
    

}
void customer::withdrawMoney(int money,int t)
{
    fstream file;
    
    file.open("CustomerDataFile.dat",ios::in|ios::out|ios::ate|ios::binary);
    file.seekg(0); //g/p pointer points to last by default so we're setting it to beginning of file
    file.read((char*)this,sizeof(*this));

    while(!file.eof())
    {
        if(accNo==t)
         {
             file.seekp(file.tellp() - sizeof(*this));
             balance-=money;
             if(balance<0)
             {
                 cout<<"\nSorry Your account has insufficient funds"<<endl;
                 break;
             }
             file.write((char*)this,sizeof(*this));
             break;
         }
        file.read((char*)this,sizeof(*this));
    }
}

void customer::displayLastAccNo()
{
     ifstream fin;
    fin.open("CustomerDataFile.dat", ios::in|ios::binary);

   string result = "";
    

    if(fin.is_open()) {
        fin.seekg(0,std::ios_base::end);      //Start at end of file
        char ch = ' ';                        //Init ch not equal to '\n'
        while(ch != '\n'){
            fin.seekg(-2,std::ios_base::cur); //Two steps back, this means we
                                              //will NOT check the last character
            if((int)fin.tellg() <= 0){        //If passed the start of the file,
                fin.seekg(0);                 //this is the start of the line
                break;
            }
            fin.get(ch);                      //Check the next character
        }

        std::getline(fin,result);
        fin.close();

        std::cout << "final line length: " << result.size() <<std::endl;
        std::cout << "final line character codes: ";
        for(size_t i =0; i<result.size(); i++){
            std::cout << std::hex << (int)result[i] << " ";
        }
        std::cout << std::endl;
        std::cout << "final line: " << result <<std::endl;
    }

}

int customer::searchCustomerReturnDepoistorName(int t)
{
    ifstream ifs;
        
    ifs.open("CustomerDataFile.dat", ios::in|ios::binary);
    if(!ifs)
        cout<<"\n File not found"<<endl;
    else
    {
    ifs.read((char*)this,sizeof(*this));
    
    while(!ifs.eof())
    {
        if(accNo==t)
        { 
            ifs.close();
            cout<<"\n Account Holder Name is "<<depositorName<<endl;
               return 1;
        }
        ifs.read((char*)this,sizeof(*this));
    }
    ifs.close();
    return 0;
    
    }

}
int customer::searchCustomerReturnAddress(int t)
{
    ifstream ifs;
        
    ifs.open("CustomerDataFile.dat", ios::in|ios::binary);
    if(!ifs)
        cout<<"\n File not found";
    else
    {
    ifs.read((char*)this,sizeof(*this));
    
    while(!ifs.eof())
    {
        if(accNo==t)
        { 
            ifs.close();
            cout<<"\n Account Holder Address is "<<address<<endl;
               return 1;
        }
        ifs.read((char*)this,sizeof(*this));
    }
    ifs.close();
    return 0;
    
    }

}
int customer::searchCustomerReturnBalance(int t)
{
    ifstream ifs;
        
    ifs.open("CustomerDataFile.dat", ios::in|ios::binary);
    if(!ifs)
        cout<<"\n File not found\n";
    else
    {
    ifs.read((char*)this,sizeof(*this));
    
    while(!ifs.eof())
    {
        if(accNo==t)
        { 
            ifs.close();
            cout<<"\n Account Balance is \n "<<balance<<endl;
               return 1;
        }
        ifs.read((char*)this,sizeof(*this));
    }
    ifs.close();
    return 0;
    
    }

}

void customer::searchCustomerReturnRecord(int acc10)
{
    ifstream ifs;
        
    ifs.open("CustomerDataFile.dat", ios::in|ios::binary);
    if(!ifs)
        cout<<"\n File not found\n";
    else
    {
    ifs.read((char*)this,sizeof(*this));
    
    while(!ifs.eof())
    {
        if(accNo==acc10)
        { 
            ifs.close();
            cout<<"\n Record Number  is \n "<<recordNo<<endl;
               return ;
        }
        ifs.read((char*)this,sizeof(*this));
    }
    ifs.close();

    }


}

void display()
{
    cout<<"1. Add new customers to the bank who become an account holder.\n"<<
"2. Display a list of all the account holders of the bank along with their account numbers and balance.\n"<<
"3. Delete the information related to the account holder from the customer data file\n"<<
"4. Update the balance after customer has performed a deposit or withdraw transaction\n"<<
"5. display the account number of the last entry \n"<<
"6. check whether an account exists or not \n"<<
"7. retrieve the name of the account holder\n"<<
"8. retrieve the address of the account holder\n"<<
"9. retrieve the balance of the account holder\n"<<
"10. returns the record number from the customer file when an employee of the bank enters"<<
"the account number related to an account holder(Transaction details along with the"<<
"account information)\n"<<
"11. displays all the information related to an account holder from the customer file on the"<<
"basis of specified account number.\n"<<
"12. Calculate the interest to date on the deposit if a particular customer has not withdrawn"<<
"for more than a month\n"<<
"13. To exit the program\n";
}



int main()
{
    display();
    int i;
    
while(true)
{
    cin>>i;
    switch(i)
    {

        case 1:
            {
            cout<<"********Enter Your details********\n";
            customer c1;
             c1.getBankData();
             c1.storeData();
             cout<<"\n";
             display();
             
             }
             break;
           
        case 2:     
            {customer c2;
                cout<<"\n ********Display all the details of all account holders ********\n";
            c2.viewAllData();
             cout<<"\n";
            display();
           
            }
            break;

            //3. Delete the information related to the account holder from the customer data file
            case 3:
            {
                customer c3;
                cout<<"\n Enter the name of account holder to delete its details\n";
            char name[30];
            cin>>name;
            c3.deleteCustomer(name);
            display();
            
            }
                 break;     
            
            // 4. Update the balance after customer has performed a deposit or withdraw transaction

            case 4:
            {
                customer c4;
            int acc;
            cout<<"\n enter your account number to continue with deposit or withdrawal\n";
            cin>>acc;
            int flag = c4.searchCustomer(acc);
           
           if(flag)
         { 
              cout<<"\n 1.Deposit \n 2.Withdraw \n";
            int i,money;
            cin>>i;
            switch(i)
            {
                case 1:
                        cout<<"\n Enter how much you want to deposit\n";
                        cin>>money;
                        c4.depositMoney(money,acc);
                        cout<<"\n Balance update successfull\n ";
                        break;
                case 2:
                        cout<<"\n Enter how much you want to withdraw\n";
                        cin>>money;
                        c4.withdrawMoney(money,acc);
                        cout<<"\nBalance update successfull\n ";
                        break;
                default:
                        cout<<"\n enter valid number\n";
                        break;
            }
         }
         else
         {
                cout<<"\n Not a valid person";
         }
            c4.viewAllData();
             cout<<"\n";
            display();
           

            }
            break;         
       

            //5. display the account number of the last entry

            case 5:            
                   { 
                       customer c5;
                       c5.displayLastAccNo();
                       cout<<"\n";
                       display();
                       cout<<"\n";
                    }
                    break;

            //6. check whether an account exists or not
            case 6:
            { 
                customer c6;
                int acc6;
            cout<<"\n Enter account number to check if account exists or not\n";
            cin>>acc6;
            int flag2 = c6.searchCustomer(acc6);
            if(flag2)
                cout<<"\n Account exists";
            else
                cout<<"\n No account exists";

                cout<<"\n";
                display();
                cout<<"\n";
            }
            break;

            // 7. retrieve the name of the account holder

            case 7:
            {
            customer c7;
            int acc7;
            cout<<"\n Enter ACCOUNT NUMBER to retreive its account holders name\n";
            cin>>acc7;

            int flag7 = c7.searchCustomerReturnDepoistorName(acc7);
            if(flag7==0)
            cout<<"\nNo account present";
            cout<<"\n";
            display();
            cout<<"\n";
            }
            break;

            
            //8. retrieve the address of the account holder
            case 8:
            {
             customer c8;
            int acc8;
            cout<<"\n Enter ACCOUNT NUMBER to retreive its account holders ADDRESS\n";
            cin>>acc8;

            int flag7 = c8.searchCustomerReturnAddress(acc8);
            if(flag7==0)
            cout<<"\nNo account present";
            cout<<"\n";
            display();
            cout<<"\n";
            }
            break;

            //9. retrieve the balance of the account holder
           case 9:
           { cout<<"\n Enter ACCOUNT NUMBER to retreive its ACCOUNT BALANCE\n";
            
             customer c9;
            int acc9;
            cin>>acc9;

            int flag7 = c9.searchCustomerReturnBalance(acc9);
            if(flag7==0)
            cout<<"\nNo account present";
            cout<<"\n";
            display();
            cout<<"\n";
            }
            break;


//             10. returns the record number from the customer file when an employee of the bank enters
// the account number related to an account holder(Transaction details along with the
// account information)

            case 10:
            {
                cout<<"\n Enter ACCOUNT NUMBER to retreive its Record Number \n";
            int flag10;
             customer c10;
            int acc10;
            cin>>acc10;

            c10.searchCustomerReturnRecord(acc10);
            if(flag10==0)
            cout<<"\nNo account present";
            cout<<"\n";
            display();
            cout<<"\n";

            }



    // 11. displays all the information related to an account holder from the customer file on the
    // basis of specified account number.

                case 11:
                {
                    int acc11;
                customer c11;
                cout<<"\n Enter Account number to check your details\n";
                cin>>acc11;
                c11.searchCustomerReturnAll(acc11);
                cout<<"\n";
                display();
                }
                break;
        // 12. Calculate the interest to date on the deposit if a particular customer has not withdrawn
        // for more than a month

        // case 12:
        //         {
        //             //got some errors while solving this section
                    
        //         }
        //         break;


                case 13:
                        exit(0);
                        break;
            default:
                cout<<"\n enter valid number\n";
                break;
            
    }

}

    return 0;
}




