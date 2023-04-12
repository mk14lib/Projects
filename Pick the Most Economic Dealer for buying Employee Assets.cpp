/*
* Title: Pick the Most Economic Dealer for buying Employee Assets
* Author: Koona Maheswararao
* Date: 12/04/2023
*/

#include <iostream>
#include <fstream>
using namespace std;

ofstream write;
void loop();
int** prices = new int*[5];
string *items = new string[5]
{
    "Laptop",
    "Mouse",
    "Headset",
    "Laptop Bag",
    "Adapter"
};

int* quantity = new int[5];
int** cost = new int*[2];

void bestPurchase(int* , int** );
bool userbestChoice(int *Q, int **p);

class ramu
{
    public:
    ramu()
    {
        int quantities[5] = {5, 15, 10, 5, 20};
        cout<<"Ramu ";
        bestPurchase(quantities, prices);
    }
};

class raju
{
    public:
    raju()
    {
        int quantities[5] = {10, 10, 25, 10, 15};
        cout<<"Raju ";
        bestPurchase(quantities, prices);
    }
};

class shyam
{
    public:
    shyam()
    {
        int quantities[5] = {3, 5, 6, 3, 10};
        cout<<"Shyam ";
        bestPurchase(quantities, prices);
    }
};

int main()
{
    for (int i = 0; i < 5; i++)
    {
        prices[i] = new int[2];
    }
        
    prices[0][0] = 45000;
    prices[1][0] = 1500;
    prices[2][0] = 2500;
    prices[3][0] = 1200;
    prices[4][0] = 1600;
        
    prices[0][1] = 43000;
    prices[1][1] = 1200;
    prices[2][1] = 3000;
    prices[3][1] = 1000;
    prices[4][1] = 1500;
    cout<<"Commodity\tVendor1 Vendor-2"<<endl;
    cout<<"---------\t------- --------"<<endl;
    for(int i=0; i<5; i++){
        if(i != 1){
        cout<<items[i]<<"  \t";
        }
        else{
            cout<<items[i]<<"\t\t";
        }
        for(int j=0; j<2; j++){
            cout<<" "<<prices[i][j]<<" ";
            if(j == 1)
            cout<<endl;
        }
    }
    cout<<"--------------------------------\n"<<endl;
        
    ramu best1;
    raju best2;
    shyam best3;
    
    loop();
    
    for (int i = 0; i < 2; i++) {
    delete[] cost[i];
    }
    delete[] cost;
    
    delete[] prices;
    delete[] items;
    
    return 0;
}


void bestPurchase(int *Q, int **p)
{
    int sum1 = 0, sum2 = 0;
    for(int i = 0; i < 5; i++)
    {
        sum1 += Q[i]*p[i][0];
        sum2 += Q[i]*p[i][1];
    }
        
    
    if(sum1 > sum2)
        cout<<"\t: Purchase from Vendor-2"<<endl;
    else
        cout<<"\t: Purchase from Vendor-1"<<endl;
}

void loop()
{
    while(1)
    {
        
        write.open("data.txt", ios::out);
        
       
        for(int i=0; i<5; i++)
        {
            cost[i] = new int[2];
        }
        
        cout<<"\nEnter Commodities to be purchased: "<<endl;
        write<<"Commodity\tQty."<<endl;
        write<<"---------------"<<endl;
        for(int i=0; i<5; i++)
        {
            if(i==3)
            cout<<items[i]<<"\t"; 
            else
            cout<<items[i]<<"\t\t";
    
            cin>>quantity[i];
        }
            
        cout<<"\nEnter Vendor quotations: "<<endl;
        for(int i=0; i<2; i++){
            cout<<"\nVendor #"<<i+1<<":\n";
            for(int j=0; j<5; j++)
            {
                if(j==5)
                cout<<endl<<endl;
                
                if(j==3)
                cout<<items[j]<<"\t"; 
                else
                cout<<items[j]<<"\t\t";
                
                cin>>cost[i][j];
            }
        }
        
        for(int i=0; i<5; i++)
        {
            if(i==3)
            write<<items[i]<<"\t"<<quantity[i]<<endl;
            else
            write<<items[i]<<"\t\t"<<quantity[i]<<endl;
        }
        
        write<<endl;
        for(int i=0; i<2; i++){
            write<<"\nVendor #"<<i+1<<":\n";
            write<<"---------------------"<<endl;
            for(int j=0; j<5; j++)
            {
                if(j==5)
                write<<endl<<endl;
                    
                if(j==3)
                write<<items[j]<<"\t"<<"Rs. "<<cost[i][j]<<endl; 
                else
                write<<items[j]<<"\t\t"<<"Rs. "<<cost[i][j]<<endl;
            }
        }
        
        cout<<endl<<"You ";
        
        bool x = userbestChoice(quantity, cost);
        
        if(x == 0)
        write<<"\t: Purchase from Vendor-2"<<endl;
        else
        write<<"\t: Purchase from Vendor-1"<<endl;
        
        int y=2;
        cout<<"\nDo you want to repeat?\nPress '0' to exit! ";
        cin>>y;
        
        if(y==0)
        break;
        
        write.close();
    }
}

bool userbestChoice(int *Q, int **p)
{
    int sum1 = 0, sum2 = 0;
    
    for(int i = 0; i < 5; i++)
    {
        sum1 += Q[i]*p[0][i];
        sum2 += Q[i]*p[1][i];
    }
    
    write<<"\nVendor-1 Selling Price @Rs. "<<sum1<<endl;
    write<<"Vendor-2 Selling Price @Rs. "<<sum2<<endl;
    write<<endl<<"You ";
    
    if(sum1 > sum2){
        cout<<"\t: Purchase from Vendor-2"<<endl;
        return false;
    }
    else{
        cout<<"\t: Purchase from Vendor-1"<<endl;
        return true;
    }
}
