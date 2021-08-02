#include<bits/stdc++.h>
using namespace std;

class Passenger{
	private:
		string name;
		int age;
		char destination;
	public:

		Passenger(string name , int age , char destination)
		{
			this->name = name;
			this->age = age;
			this->destination = destination;	
		}
		string getName()
		{
			return this->name;
		}
		int getAge()
		{
			return this->age;
		}
		char getDestination()
		{
			return this->destination;
		}
};

class BookingManagement{
	private:
		vector<Passenger> passengers;
		priority_queue<pair<int , int>> passengerQueue;
		unordered_map<char , vector<char>> stations;
		char startingStation;

		void BFS(char destination)
		{
			queue<char> q;
			unordered_map<char , char> prev;
			set<char> visited;
			q.push(this->startingStation);
			while(!q.empty())
			{
				char node = q.front();
				q.pop();
				for(auto it : stations[node])
				{
					if(visited.find(it) == visited.end())
					{
						q.push(it);
						visited.insert(it);
						prev[it] = node;
					}
				}
			}
			vector<char> result;
			result.push_back(destination);
			while(destination != this->startingStation || prev.find(destination) == prev.end())
			{
				destination = prev[destination];
				result.push_back(destination);	
			}
			reverse(result.begin() , result.end());
			if(result[0] == this->startingStation)
			{
				for(auto it : result)
					cout<<it<<" ";
				cout<<endl;
			}
			else
				cout<<"No route present to the destination"<<endl;
		}
	public:
		static int noOfPassengers;
		static int noOfInterConnections;
		void init()
		{
			cin>>this->noOfInterConnections>>this->startingStation;
			char u , v;
			for(int i = 0 ; i < this->noOfInterConnections ; i++)
			{
				cin>>u>>v;
				stations[u].push_back(v);
				stations[v].push_back(u);
			}
		}
		void addPassenger()
		{
			int n;
			cin>>n;
			while(n--)
			{
				string name;
				int age;
				char destination;

				cin>>name>>age>>destination;
				Passenger passenger(name , age ,destination);
				passengers.push_back(passenger);
				passengerQueue.push(pair<int , int> (passenger.getAge() , this->noOfPassengers));
				this->noOfPassengers++;

			}
		} 
		void startPod()
		{
			int n;
			cin>>n;
			while(n--)
			{
				cout<<passengers[passengerQueue.top().second].getName()<<" ";
				BFS(passengers[passengerQueue.top().second].getDestination());
				passengerQueue.pop();
			}	
		}
		void printQueue()
		{
			cout<<passengerQueue.size()<<endl;
			priority_queue<pair<int , int>> passengerQueueCopy = passengerQueue;
			while(!passengerQueueCopy.empty())
			{
				cout<<passengers[passengerQueueCopy.top().second].getName()<<" "<<passengers[passengerQueueCopy.top().second].getAge()<<endl;
				passengerQueueCopy.pop();
			}
		}
};

int::BookingManagement::noOfPassengers = 0;
int::BookingManagement::noOfInterConnections = 0;
int main()
{
	BookingManagement bookingManagement;	
	while(1)
	{
		string input;
		cin>>input;
		if(input == "INIT")
			bookingManagement.init();
		else if(input == "ADD_PASSENGER")
		{
			bookingManagement.addPassenger();
			bookingManagement.printQueue();
		}
		else if(input == "START_POD")
			bookingManagement.startPod();
		else if(input == "PRINT_Q")
			bookingManagement.printQueue();
	}
}