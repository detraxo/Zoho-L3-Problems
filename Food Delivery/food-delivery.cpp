#include<bits/stdc++.h>
using namespace std;

struct Booking{
	string executive;
	char restraunt;
	char destinationPoint;
	int orders;
	int pickUpTime;
	int deliveryTime;
	int deliveryCharge;
};

class Executive{
	private:

		int earning;
		int totalEarning;
		int allowance;
		int noOfTrips;
		char restrauntLocation;
		char deliveryLocation;
		int pickUpTime;
		int relaxationTime;

	public:
		Executive()
		{
			this->earning = 0;
			this->totalEarning = 0;
			this->allowance = 0;
			this->noOfTrips = 0;
			this->pickUpTime = 0;
			this->relaxationTime = 0;
			this->deliveryLocation = '$';
			this->restrauntLocation = '$';
		}
		void setPickUpTime(int pickUpTime)
		{
			this->pickUpTime = pickUpTime;
		}
		int getPickUpTime()
		{
			return this->pickUpTime;
		}
		void setRelaxationTime(int relaxationTime)
		{
			this->relaxationTime = relaxationTime;
		}
		int getRelaxationTime()
		{
			return this->relaxationTime;
		}
		void addToEarning(int fare)
		{
			this->earning += fare;
		}
		int getEarning()
		{
			return this->earning;
		}
		void addNoOfTrips()
		{
			this->noOfTrips += 1;
		}
		int getNoOfTrips()
		{
			return this->noOfTrips;
		}
		int getAllowance()
		{
			this->allowance = 10*this->noOfTrips;
			return this->allowance;
		}
		int getTotalEarning()
		{
			this->totalEarning = this->allowance + this->earning;
			return this->totalEarning;
		}
		void setRestrauntAndDelivery(char restrauntLocation , char deliveryLocation)
		{
			this->restrauntLocation = restrauntLocation;
			this->deliveryLocation = deliveryLocation;
		}
		char getRestraunt()
		{
			return this->restrauntLocation;
		}
		char getDeliveryLocation()
		{
			return this->deliveryLocation;
		}
};

class DeliveryManagement{
	private:
		vector<Executive> executive;	
		int noOfExecutives;
		vector<Booking> bookings;
	public:
		int convertToMinutes(string time)
		{
			int timeInMinutes = 0;
			if(time.size() == 7)
				time = "0" + time;
			if(time[time.size() - 2] == 'P' || time[time.size() - 2] == 'p')
				timeInMinutes += 12*60;
			timeInMinutes += ((time[0] - '0' )*10 + (time[1] - '0'))*60;
			timeInMinutes += (time[3] - '0')*10 + (time[4] - '0');
			return timeInMinutes;
		}
		string convertToHours(int time)
		{
			string result = "";
			string suffix;
			if(time/60 >= 12)
			{
				time -= 12*60;
				suffix = "PM";
			}
			else
				suffix = "AM";
			result += (time/60)/10 + '0';
			result += (time/60)%10 + '0';
			result += ":";
			result += (time%60)/10 + '0';
			result += (time%60)%10 + '0';
			result += " " + suffix;
			return result;
		}
		static int currentTime;
		static int noOfDeliveries;

		DeliveryManagement(int noOfExecutives)
		{
			this->noOfExecutives = noOfExecutives;
			executive.resize(noOfExecutives);
		}

		void printAvailableExecutives()
		{
			cout<<"Available Executives"<<endl<<endl;
			cout<<"Executive\tDelivery Charge Earned"<<endl;
			int i = 0;
			for(auto it : executive)
			{
				cout<<"DE"<<i + 1<<"\t\t"<<it.getEarning()<<endl;
				i++;
			}
		}

		void foodDelivery()
		{
			int customerId;
			char restraunt , destinationPoint;
			string time;
			cout<<"\nCustomer ID : ";
			cin>>customerId;
			cout<<"Restraunt : ";
			cin>>restraunt;
			cout<<"Destination Point : ";
			cin>>destinationPoint;
			cout<<"Time : ";
			cin.ignore();
			getline(cin , time);
			currentTime = convertToMinutes(time);

			bool alreadGoing = false;
			int minimumEarning = INT_MAX;
			int bookedIndex;
			int i = 0;
			for(Executive it : executive)
			{
				if(it.getRestraunt() == restraunt && it.getDeliveryLocation() == destinationPoint 
					&& it.getEarning() < minimumEarning && it.getPickUpTime() >= currentTime)
				{
					alreadGoing = true;
					minimumEarning = it.getEarning();
					bookedIndex = i;
				}
				i++;
			}

			if(alreadGoing)
			{
				cout<<"\n\nBooking Id : "<<noOfDeliveries<<endl;
				printAvailableExecutives();
				cout<<"Alloted Delivery Executive: DE"<<bookedIndex + 1<<"(because same location within 15 minutes"<<endl<<endl;
				executive[bookedIndex].addToEarning(5);

				bookings[noOfDeliveries - 1].orders++;
				bookings[noOfDeliveries - 1].deliveryCharge += 5;
				return;
			}

			noOfDeliveries++;
			cout<<"\n\nBooking Id : "<<noOfDeliveries<<endl;
			printAvailableExecutives();

			minimumEarning = INT_MAX;
			i = noOfExecutives - 1;
			for(auto it = executive.rbegin() ; it != executive.rend() ; it++)
			{
				if(it->getRelaxationTime() <= currentTime && it->getEarning() <= minimumEarning)
				{
					minimumEarning = it->getEarning();
					bookedIndex = i;
				}
				i--;
			}
			cout<<"Alloted Delivery Executive: DE"<<bookedIndex + 1<<endl;

			executive[bookedIndex].addToEarning(50);
			executive[bookedIndex].addNoOfTrips();
			executive[bookedIndex].setPickUpTime(currentTime + 15);
			executive[bookedIndex].setRelaxationTime(currentTime + 45);
			executive[bookedIndex].setRestrauntAndDelivery(restraunt , destinationPoint);

			Booking booking;
			booking.deliveryCharge = executive[bookedIndex].getEarning();
			booking.deliveryTime = executive[bookedIndex].getRelaxationTime();
			booking.orders = 1;
			booking.pickUpTime = executive[bookedIndex].getPickUpTime();
			booking.executive = "DE";
			booking.executive += (bookedIndex + 1 +'0');
			booking.destinationPoint = executive[bookedIndex].getDeliveryLocation();
			booking.restraunt = executive[bookedIndex].getRestraunt();

			bookings.push_back(booking);
		}

		void printDeliveryDetails()
		{
			cout<<"\n\nDelivery History"<<endl;
			cout<<"Trip\tExecutive\tRestraunt\tDestination Point\tOrders\tPick Up Time\tDelivery Time\tDelivery Charge\n";
			int i = 0;
			for(auto it : bookings)
			{
				cout<<i + 1<<"\t\t"<<it.executive<<"\t\t"<<it.restraunt<<"\t\t"<<it.destinationPoint<<"\t\t"<<it.orders
					<<"\t"<<convertToHours(it.pickUpTime)<<"\t"<<convertToHours(it.deliveryTime)<<"\t\t"<<it.deliveryCharge<<endl;
				i++;
			}
		}

		void printTotalEarned()
		{
			int i = 0;
			cout<<"\n\nTotal Earning\n";
			cout<<"Executive\tAllowance\tDelivery Charge\tTotal\n";

			for(auto it : executive)
			{
				cout<<"DE"<<i+1<<"\t\t"<<it.getAllowance()<<"\t\t"<<it.getEarning()<<"\t\t"<<it.getTotalEarning()<<endl;				
				i++;
			}
		}
};

int DeliveryManagement::currentTime = 0;
int DeliveryManagement::noOfDeliveries = 0;

int main()
{
	DeliveryManagement deliveryManagement(5);
	while(1)
	{
		cout<<"\nChoose from the following options : "<<endl;
		cout<<"1. Handle Delivery\n2. Print Delivery Details\n3. Print Executive Details\n";
		int choice;
		cout<<endl<<"Your Choice : ";
		cin>>choice;
		if(choice == 1)
			deliveryManagement.foodDelivery();
		else if (choice == 2)
			deliveryManagement.printDeliveryDetails();
		else if (choice == 3)
			deliveryManagement.printTotalEarned();
		else
			break;
	}
}