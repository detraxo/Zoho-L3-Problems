#include<bits/stdc++.h>
using namespace std;

class BookingDetails{
	public:
		int bookingId;
		int customerId;
		char from;
		char to;
		int pickUpTime;
		int dropTime;
		int amount;
};

class Taxi{

	private:
		int relaxationTime;
		int earning;
		char currentLocation;
		vector<BookingDetails> bookingDetails;
	public:
		Taxi()
		{
			relaxationTime = 0;
			earning = 0;
			currentLocation = 'A';
		}
		void addBooking(int bookingId , int customerId, char from , char to , int pickUpTime , int dropTime ,int amount)
		{
			BookingDetails bookingDetail;
			bookingDetail.bookingId = bookingId;
			bookingDetail.customerId = customerId;
			bookingDetail.dropTime = dropTime;
			bookingDetail.from = from;
			bookingDetail.to = to;
			bookingDetail.pickUpTime = pickUpTime;
			bookingDetail.amount = amount;
			bookingDetails.push_back(bookingDetail);
		}
		int getEarning()
		{
			return earning;
		}
		void setEarning(int earning)
		{
			this->earning = earning;
		}
		int getRelaxationTime()
		{
			return relaxationTime;
		}
		void setRelaxationTime(int relaxationTime)
		{
			this->relaxationTime = relaxationTime;
		}
		int getCurrentLocation()
		{
			return currentLocation;
		}
		void setCurrentLocation(int currentLocation)
		{
			this->currentLocation = currentLocation;
		}
		vector<BookingDetails> getBookings()
		{
			return bookingDetails;
		}
};

class TaxiManagement{

	private:
		int noOfTaxis;
		vector<Taxi> taxi;
		int getDistanceBetweenPoints(char pointA , char pointB)
		{
			return abs( pointA - pointB);
		}
		
	public:
		static int currentTime;
		static int noOfBooknigs;
		TaxiManagement(int noOfTaxis)
		{
			this->noOfTaxis = noOfTaxis;
			taxi.resize(noOfTaxis);	
		}
		
		void bookTaxi()
		{
			int customerId , pickUpTime;
			char pickUpPoint , dropPoint;
			int closestDistance = INT_MAX;

			cout<<"Customer Id: ";
			cin>>customerId;
			cout<<"Pickup Point: ";
			cin>>pickUpPoint;
			cout<<"Drop Point: ";
			cin>>dropPoint;
			cout<<"Pickup Time: ";
			cin>>pickUpTime;
			
			currentTime = pickUpTime;

			for(int i = 0 ; i < noOfTaxis ; i++)			
				if(taxi[i].getRelaxationTime() <= pickUpTime)
					closestDistance = min(closestDistance , getDistanceBetweenPoints(taxi[i].getCurrentLocation() , pickUpPoint));
			int minimumEarning = INT_MAX;
			int bookedTaxiIndex = -1;
			for(int i = 0 ; i < noOfTaxis ; i++)
				if(getDistanceBetweenPoints(taxi[i].getCurrentLocation() , pickUpPoint) == closestDistance && 
				taxi[i].getEarning() < minimumEarning)
				{
					bookedTaxiIndex = i;
					minimumEarning = taxi[i].getEarning();
				}
			if(bookedTaxiIndex == -1)
			{
				cout<<"No taxis available as of now"<<endl;
				return;
			}

			noOfBooknigs++;

			cout<<"+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++";
			cout<<endl<<endl<<"Taxi can be alloted."<<endl;
			cout<<"Taxi-";cout<<bookedTaxiIndex + 1;cout<<" is alloted"<<endl<<endl;
			cout<<"It will be arriving in ";cout<<closestDistance;
			cout<<" hours"<<endl;
			cout<<"Total Fare : ";
			cout<<getDistanceBetweenPoints(pickUpPoint , dropPoint)*200<<endl<<endl;
			taxi[bookedTaxiIndex].setCurrentLocation(dropPoint);	
			taxi[bookedTaxiIndex].setEarning(taxi[bookedTaxiIndex].getEarning() + getDistanceBetweenPoints(pickUpPoint , dropPoint)*200);
			taxi[bookedTaxiIndex].setRelaxationTime(closestDistance + currentTime + getDistanceBetweenPoints(pickUpPoint , dropPoint));
			cout<<"Customer will reach the destination by ";
			cout<<taxi[bookedTaxiIndex].getRelaxationTime();
			cout<<":00 Hrs"<<endl<<endl<<endl;
			cout<<"+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++"<<endl<<endl;

			taxi[bookedTaxiIndex].addBooking(noOfBooknigs , customerId , pickUpPoint , dropPoint , pickUpTime ,taxi[bookedTaxiIndex].getRelaxationTime(),getDistanceBetweenPoints(pickUpPoint , dropPoint)*200);

			return;
		}
		void printBookingDetails()
		{
			int i = 0;
			for(auto it : taxi)
			{
				cout<<"Taxi No.\tTotal Earning"<<endl;
				cout<<"-------------------------------------------------------------"<<endl;
				cout<<"Taxi-";cout<<i + 1;cout<<"\t\t";cout<<it.getEarning()<<endl<<endl;
				if(it.getBookings().size() > 0)
					cout<<"BookingID\tCustomerID\tFrom\tTo\tPickupTime\tDropTime\tAmount"<<endl;
				for(auto itr : it.getBookings())
				{
					cout<<itr.bookingId<<"\t\t"<<itr.customerId<<"\t\t"<<itr.from<<"\t"<<itr.to<<"\t"<<itr.pickUpTime<<"\t\t"
						<<itr.dropTime<<"\t\t"<<itr.amount<<endl;
				}
				i++;
				cout<<endl<<endl;
			}
		}
};

int TaxiManagement::currentTime = 0; 
int TaxiManagement::noOfBooknigs = 0;

int main()
{
	TaxiManagement taxiManagement(4);
	while(1)
	{
		taxiManagement.bookTaxi();
		taxiManagement.printBookingDetails();
	}
}