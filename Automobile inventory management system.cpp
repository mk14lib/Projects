/*
* Title: Automobile inventory managemen system to carry out maintenance checks
* Author:Koona Maheswararao
* Date: 12/04/2023
*/

#include<iostream>
#include<iomanip>
#include<vector>
using namespace std;

// three fuel types
enum Type{GAS, DIESEL, ELECTRIC};

// base class
class vehicle
{
protected:
    string make, model;
    int year, odometer;
    
public:  
    vehicle() {make = ""; model = ""; year = 0; odometer = 0;}
    vehicle(string m, string mo, int y, int o) {make = m; model = mo; year = y; odometer = o;}
    string getMake() {return make;}
    string getModel() {return model;}
    int getYear() {return year;}
    int getOdometer() {return odometer;}
    void setMake(string m) {make = m;}
    void setModel(string mo) {model = mo;}
    void setYear(int y) {year = y;}
    void setOdometer(int o) {odometer = o;}
    virtual Type getType() = 0;
    virtual ~vehicle() {}
};

// gascar derived class
class gascar : public vehicle
{
public:
    Type type = GAS;
    gascar(string a, string b, int c, int d)
    {
        make = a;
        model = b;
        year = c;
        odometer = d;
    }

    Type getType() {return type;}
    string getFuelType() {return "GAS";}
};

// diesel car derived class
class dieselcar : public vehicle
{
public:
    Type type = DIESEL;
    dieselcar(string a, string b, int c, int d)
    {
        make = a;
        model = b;
        year = c;
        odometer = d;
    }

    Type getType() {return type;}
    string getFuelType() {return "Diesel";}
};

// electric car derived class
class electriccar :  public vehicle
{
public:
    Type type = ELECTRIC;
    electriccar(string a, string b, int c, int d)
    {
        make = a;
        model = b;
        year = c;
        odometer = d;
    }

    Type getType() {return type;}   
    string getFuelType() {return "Electric";}
    
    // maintenance activity #1
    void CheckTireRotation(int distance)
    {
        if(distance >= 50000) cout<<" Tire need rotation"<<endl;
        else cout<<" Tires are good to go"<<endl;
    }
    
    // maintenance activity #2
    void checkChargerPower(int distance)
    {
        if(distance >= 400) cout<<" Battery requires a recharging"<<endl;
        else cout<<" Battery charging is good to go"<<endl;
    }
};

// Fuel Vehicle derived class
class FuelVehicle : public vehicle
{
public:
    virtual string getFuelType() = 0;
    // checks for oil level
    void checkOil(int level) 
    {
        if(level == 1) cout<<" Oil needs immediate top up"<<endl;
        else if(level == 2) cout<<" Oil is at medium level"<<endl;
        else if(level == 3) cout<<" Oil level is good"<<endl;
    }
};

// function prototypes
void listInventory();
void addVehicle();
void updateVehicle();
void removeVehicle();
void tireRotation();
void oilChange();
void Recharge();


// global vector container
vector<vehicle*> v;


// main() function: execution begins from here
int main()
{
    // presets for cars inventory
    v.push_back(new dieselcar("BMW", "5series", 2017, 324234));
    v.push_back(new dieselcar("Chevrolet", "Cruze", 2019, 34235));
    v.push_back(new gascar("Honda", "Civic", 2022, 14145));
    v.push_back(new electriccar("Tesla", "Model S" , 2021, 5142));
    
    int userInput;
    // controlled infinite loop
    while(true)
    {
        cout<< "\n\n\t"<<" "<<" _____________________"<<endl;
        cout<<"\t |________ MENU _______|"<<endl;
        cout<< "\t |"<<setw(22)<<"|"<<endl;
        cout<< "\t |  0. Quit"<<setw(14)<<"|\n";
        cout<< "\t |  1. List inventory"<<setw(4)<<"|\n";
        cout<< "\t |  2. Add vehicle"<<setw(7)<<"|\n";
        cout<< "\t |  3. Update vehicle"<<setw(4)<<"|\n";
        cout<< "\t |  4. Remove vehicle"<<setw(4)<<"|\n";
        cout<< "\t |  5. Tire Rotation"<<setw(5)<<"|\n";
        cout<< "\t |  6. Oil Change"<<setw(8)<<"|\n";
        cout<< "\t |  7. Recharge"<<setw(10)<<"|\n";
        cout<< "\t |_____________________|"<<endl;
        cout<<"\n Enter Your Choice: ";
        
        cin>>userInput;
        if(userInput == 0) break;
        else if(userInput == 1) listInventory();
        else if(userInput == 2) addVehicle();
        else if(userInput == 3) updateVehicle();
        else if(userInput == 4) removeVehicle();
        else if(userInput == 5) tireRotation();
        else if(userInput == 6) oilChange();
        else if(userInput == 7) Recharge();
    }
    
    for(vehicle* obj: v) delete obj;
    return 0;
}

// function to list all the vehicles
void listInventory()
{
    system("clear");
    cout<<"\n SNo."<<setw(10)<<"Make"<<setw(10)<<"Model"<<setw(10)<<"Year"<<setw(10)<<"Odometer"<<setw(10)<<"FuelType"<<endl;
    cout<<" ------------------------------------------------------"<<endl;
    for(int i=0; i<v.size(); ++i)
    {
        string str;
        if(v[i]->getType() == GAS) str = "GAS";
        else if(v[i]->getType() == DIESEL) str = "DIESEL";
        else if(v[i]->getType() == ELECTRIC) str = "ELECTRIC";
        cout<<" "<<setw(3)<<i+1<<setw(11)<<v[i]->getMake()<<setw(10)<<v[i]->getModel()<<setw(10)<<v[i]->getYear()<<setw(10)<<v[i]->getOdometer()<<setw(10)<<str<<endl;
    }
    cout<<" ------------------------------------------------------"<<endl;
}

// function to add new vehicles
void addVehicle()
{
    string make, model;
    int year, odometer;
    int type;
    
    cout<<" Enter Make: "; cin>>make;
    cout<<" Enter Model: "; cin>>model;
    cout<<" Enter Year: "; cin>>year;
    cout<<" Enter Odometer: "; cin>>odometer;
    top:
    cout<<" Enter Type (0 - GAS, 1 - DIESEL, 2 - ELECTRIC): "; cin>>type;
    
    if((Type)type == GAS)
    {
        gascar* car = new gascar(make , model, year, odometer);
        v.push_back(car);
    }
    else if((Type)type == DIESEL)
    {
        dieselcar* car = new dieselcar(make , model, year, odometer);
        v.push_back(car);
    }
    else if((Type)type == ELECTRIC)
    {
        electriccar* car = new electriccar(make , model, year, odometer);
        v.push_back(car);
    }
    else
    { 
        cout<<"Try Again!"<<endl;
        goto top;
    }
}

// function to update vehicle details
void updateVehicle()
{
    int index;
    cout<<" Select Vehicle to update: ";
    cin>>index;
    --index;
    string make, model;
    int year, odometer;
    
    if(index < v.size())
    {
        cout<<" Enter new Make: ";
        cin>>make;
        v[index]->setMake(make);
        
        cout<<" Enter new Model: ";
        cin>>model;
        v[index]->setModel(model);
        
        cout<<" Enter new Year: ";
        cin>>year;
        v[index]->setYear(year);
        
        cout<<" Enter new Odometer: ";
        cin>>odometer;
        v[index]->setOdometer(odometer);
    }
    else cout<<" Index out of bounds!"<<endl;
}

// function to remove vehicle of choice
void removeVehicle()
{
    int index;
    cout<<" Select Vehicle to remove: ";
    cin>>index;
    --index;
    if(index < v.size()) v.erase(v.begin()+index);
    else cout<<" Index out of bounds!"<<endl;
}

// function to check for the requirement of tire rotation
void tireRotation()
{
    int index;
    cout<<" Select Vehicle to check tire rotation: ";
    cin>>index;
    --index;
    if(index < v.size())
    {
        if(v[index]->getOdometer() >= 50000) 
        cout<<" Vehicle needs tire rotation\n";
    }
    else cout<<" Index out of bounds!"<<endl;
}

// function to check for oil level
void oilChange()
{
    int index;
    cout<<" Select Vehicle to check oil level: ";
    cin>>index;
    --index;
    if(index < v.size())
    {
        int level = 1;
        if(level >= 1) cout<<" Oil level is good to go"<<endl;
        else cout<<" Oil level is zero\n";
    }
    else cout<<" Index out of bounds!"<<endl;
}

// function to check for recharge of battery only for electric vehicle
void Recharge()
{
    int index;
    cout<<" Select Vehicle to check Battery recharge: ";
    cin>>index;
    --index;
    if(index < v.size() && v[index]->getType() == ELECTRIC)
    {
        if(v[index]->getOdometer() >= 400)
        cout<<" Battery recharge is advised"<<endl;
        else
        cout<<" Battery is good to go"<<endl;
    }
    else cout<<" Not valid to this car/Index out of bounds!"<<endl;
}
