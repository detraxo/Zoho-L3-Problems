#include<bits/stdc++.h>
using namespace std;
 
class Mail{
	private:
		string from; 
		string to;
		string subject;
		string content;
	public:
		void setFrom(string from)
		{
			this->from = from;
		}
		void setTo(string to)
		{
			this->to = to;
		}
		void setSubject(string subject)
		{
			this->subject = subject;
		}
		void setContent(string content)
		{
			this->content= content;
		}
		string getFrom()
		{
			return from;
		}
		string getTo()
		{
			return to;
		}
		string getContent()
		{
			return content;
		}
		string getSubject()
		{
			return subject;
		}

};

class User{
	private:
		string username;
		string email;
		string password;
	public:
		vector<Mail> receivedMails;
		vector<Mail> sentMails;	
		void setUserName(string username)
		{
			this->username = username;
		}
		void setEmail(string email)
		{
			this->email = email;
		}
		void setPassword(string password)
		{
			this->password = password;
		}
		string getUserName()
		{
			return this->username;
		}
		string getPassword()
		{
			return this->password;
		}
		string getEmail()
		{
			return this->email;
		}
};
class Group{
	private:
		string username;
		string email;
		string password;
		string description;
	public:
		vector<Mail> receivedMails;
		vector<Mail> sentMails;	
		unordered_map<string , User> users;
		void setUserName(string username)
		{
			this->username = username;
		}
		void setEmail(string email)
		{
			this->email = email;
		}
		void setPassword(string password)
		{
			this->password = password;
		}
		void setDescription(string description)
		{
			this->description = description;
		}
		string getUserName()
		{
			return this->username;
		}
		string getPassword()
		{
			return this->password;
		}
		string getEmail()
		{
			return this->email;
		}
};


class UserManagement{
	private:
		set<string> emails;
	public:
		unordered_map<string , User> users;

		void createUser()
		{
			string name , email , password;
			cout<<"Enter User Name: ";
			cin>>name;
			cout<<"Enter Emaile Id: ";
			cin>>email;
			cout<<"Enter Password : ";
			cin>>password;

			User user;
			user.setUserName(name);
			user.setEmail(email);
			user.setPassword(password);
			if(users.find(name) != users.end())
			{
				cout<<"User Name already taken"<<endl<<endl;
				return;
			}
			if(emails.find(email) != emails.end())
			{
				cout<<"Email already taken"<<endl<<endl;
				return;
			}

			users[name] = user;
			emails.insert(email);
			cout<<"User Created"<<endl<<endl;
		}
		void printUsers()
		{
			cout<<endl<<"Printing users : "<<endl;
			for(auto it: this->users)
			{
				cout<<"Username : "<<it.first<<endl;
				cout<<"Email : "<<it.second.getEmail()<<endl;
				cout<<endl;
			}
		}

}userManagement;

class GroupManagement{
	private:
		set<string> emails;
	public:
		unordered_map<string , Group> groups;
		void createGroup()
		{
			string name , email , password ,description;
			cout<<"Enter Group Name: ";
			cin>>name;
			cout<<"Enter Group Mail Id: ";
			cin>>email;
			cout<<"Enter Group Mail Password : ";
			cin>>password;
			cout<<"Enter Group Description : ";
			cin>>description;
			
			Group group;
			group.setUserName(name);
			group.setEmail(email);
			group.setPassword(password);
			group.setDescription(description);
			if(groups.find(name) != groups.end())
			{
				cout<<"Group Name already taken"<<endl<<endl;
				return;
			}
			if(emails.find(email) != emails.end())
			{
				cout<<"Group Email already taken"<<endl<<endl;
				return;
			}

			groups[name] = group;
			emails.insert(email);
			cout<<"Group Created"<<endl<<endl;
		}
		void groupAssignment()
		{
			string groupName , userName , option;
			cout<<"Enter Group Name: ";
			cin>>groupName;
			cout<<"Enter User : ";
			cin>>userName;
			cout<<"Add / Remove	: ";
			cin>>option;
			if(userManagement.users.find(userName) == userManagement.users.end())
			{
				cout<<"User does not exist"<<endl<<endl;
				return;
			}
			if(groups.find(groupName) == groups.end())
			{
				cout<<"Group does not exist"<<endl;
				return;
			}
			if(option == "Add")
			{
				if(groups[groupName].users.find(userName) != groups[groupName].users.end())
				{
					cout<<"User already present in the group"<<endl<<endl;
					return;
				}
				groups[groupName].users[userName] = userManagement.users[userName];
				cout<<"User added to group."<<endl<<endl;
			}
			else if(option == "Remove")
			{
				if(groups[groupName].users.find(userName) == groups[groupName].users.end())
				{
					cout<<"User not present present in the group"<<endl<<endl;
					return;
				}
				groups[groupName].users.erase(userName);
				cout<<endl<<"Removed the user"<<endl<<endl;
			}
			cout<<"All users present int the group : "<<endl;
			for(auto it : groups[groupName].users)
			{
				cout<<"UserName : "<<it.first<<endl;
				cout<<"Email : "<<it.second.getEmail()<<endl;
			}
			cout<<endl<<endl;
		}
		void printGroups()
		{
			cout<<endl<<"Printing groups : "<<endl;
			for(auto it: this->groups)
			{
				cout<<"Group Username : "<<it.first<<endl;
				cout<<"Group Email : "<<it.second.getEmail()<<endl;
				cout<<endl;
			}
		}
		
}groupManagement;

class MailManagement{
	private:
		vector<Mail> mails;
	public:
		void compose()
		{
			string user , toAddress, subject ,content , to;
			cout<<"Enter the user : ";
			cin>>user;
			cout<<"Enter to address : ";
			cin>>toAddress;
			cout<<"Enter subject : ";
			cin>>subject;
			cout<<"Enter content : ";
			cin>>content;
			Mail tempMail;
			bool userFrom = false, userTo = false;
			if(userManagement.users.find(user) != userManagement.users.end())
				userFrom = true;
			if(!userFrom)
			{
				if(groupManagement.groups.find(user) == groupManagement.groups.end())
				{
					cout<<"From user not found !"<<endl<<endl;			
					return;
				}
			}
			for(auto it : userManagement.users)
			{
				if(it.second.getEmail() == toAddress)
				{
					to = it.first;
					userTo = true;
					break;
				}
			}
			if(!userTo)
			{
				bool found = false;
				for(auto it : groupManagement.groups)
				{
					if(it.second.getEmail() == toAddress)
					{
						to = it.first;
						found = true;
						break;
					}
				}
				if(!found)
				{
					cout<<"To user not found"<<endl<<endl;
					return;
				}
			}

			tempMail.setContent(content);
			tempMail.setFrom(userManagement.users[user].getEmail());
			tempMail.setTo(toAddress);
			tempMail.setSubject(subject);
			if(userFrom)
				userManagement.users[user].sentMails.push_back(tempMail);
			else
				groupManagement.groups[user].sentMails.push_back(tempMail);
			if(userTo)
				userManagement.users[to].receivedMails.push_back(tempMail);
			else
			{
				groupManagement.groups[to].receivedMails.push_back(tempMail);
				for(auto it : groupManagement.groups[to].users)
				{
					it.second.receivedMails.push_back(tempMail);
					userManagement.users[it.first].receivedMails.push_back(tempMail);
				}
			}
			
			cout<<"Mail sent"<<endl<<endl;
		}
		void inbox()
		{
			string user;
			cout<<"Enter the User Name : ";
			cin>>user;
			bool userFrom = false;
			if(userManagement.users.find(user) != userManagement.users.end())
				userFrom = true;
			if(!userFrom)
			{
				if(groupManagement.groups.find(user) == groupManagement.groups.end())
				{
					cout<<"From user not found !"<<endl<<endl;			
					return;
				}
			}
			if(userFrom)
			{
				int i = 1;
				cout<<"S.No.\t\tFrom\t\tTo\t\tSubject\t\tContent"<<endl;
				cout<<"------------------------------------------------------------------------------"<<endl;
				vector<Mail> tempMails = userManagement.users[user].receivedMails;
				for(auto it = tempMails.rbegin() ; it  != tempMails.rend() ; it++)
				{
					cout<<i<<"\t\t"<<it->getFrom()<<"\t\t"<<it->getTo()<<"\t\t"<<it->getSubject()<<"\t\t"<<it->getContent()<<endl;
					i++;
				}
				cout<<endl;
			}
			else
			{
				int i = 1;
				cout<<"S.No.\t\tFrom\t\tTo\t\tSubject\t\tContent"<<endl;
				cout<<"------------------------------------------------------------------------------"<<endl;
				vector<Mail> tempMails = groupManagement.groups[user].receivedMails;
				for(auto it = tempMails.rbegin() ; it  != tempMails.rend() ; it++)
				{
					cout<<i<<"\t\t"<<it->getFrom()<<"\t\t"<<it->getTo()<<"\t\t"<<it->getSubject()<<"\t\t"<<it->getContent()<<endl;
					i++;
				}
				cout<<endl;
			}

		}
		void sentMail()
		{
			string user;
			cout<<"Enter user name : ";
			cin>>user;	
			bool userFrom = false;
			if(userManagement.users.find(user) != userManagement.users.end())
				userFrom = true;
			if(!userFrom)
			{
				if(groupManagement.groups.find(user) == groupManagement.groups.end())
				{
					cout<<"From user not found !"<<endl<<endl;			
					return;
				}
			}
			if(userFrom)
			{
				int i = 1;
				cout<<"S.No.\t\tTo\t\tSubject\t\tContent"<<endl;
				cout<<"------------------------------------------------------------------------------"<<endl;
				vector<Mail> tempMails = userManagement.users[user].sentMails;
				for(auto it = tempMails.rbegin() ; it  != tempMails.rend() ; it++)
				{
					cout<<i<<"\t\t"<<it->getTo()<<"\t\t"<<it->getSubject()<<"\t\t"<<it->getContent()<<endl;
					i++;
				}
				cout<<endl;
			}
			else
			{
				int i = 1;
				cout<<"S.No.\t\tTo\t\tSubject\t\tContent"<<endl;
				cout<<"------------------------------------------------------------------------------"<<endl;
				vector<Mail> tempMails = groupManagement.groups[user].sentMails;
				for(auto it = tempMails.rbegin() ; it  != tempMails.rend() ; it++)
				{
					cout<<i<<"\t\t"<<it->getTo()<<"\t\t"<<it->getSubject()<<"\t\t"<<it->getContent()<<endl;
					i++;
				}
				cout<<endl;
			}
		}
		void deleteMail()
		{
			string user ,option;
			int n;
			cout<<"Enter the username : ";
			cin>>user;
			cout<<"From Inbox/Sent : ";
			cin>>option;
			cout<<"Enter serial number : ";
			cin>>n;
			bool userFrom = false;
			if(userManagement.users.find(user) != userManagement.users.end())
				userFrom = true;
			if(!userFrom)
			{
				if(groupManagement.groups.find(user) == groupManagement.groups.end())
				{
					cout<<"From user not found !"<<endl<<endl;			
					return;
				}
			}
			if(option == "Inbox")
			{
				if(userFrom)
				{
					vector<Mail> tempMails = userManagement.users[user].receivedMails;
					if(n > tempMails.size())
					{
						cout<<"Index not present"<<endl;
						return;
					}
					userManagement.users[user].receivedMails.erase(userManagement.users[user].receivedMails.end() - n);
					
					int i = 1;
					cout<<"S.No.\t\tFrom\t\tTo\t\tSubject\t\tContent"<<endl;
					cout<<"------------------------------------------------------------------------------"<<endl;
					tempMails = userManagement.users[user].receivedMails;
					for(auto it = tempMails.rbegin() ; it  != tempMails.rend() ; it++)
					{
						cout<<i<<"\t\t"<<it->getFrom()<<"\t\t"<<it->getTo()<<"\t\t"<<it->getSubject()<<"\t\t"<<it->getContent()<<endl;
						i++;
					}
					cout<<endl;
				}
				else
				{
					vector<Mail> tempMails = groupManagement.groups[user].receivedMails;
					if(n > tempMails.size())
					{
						cout<<"Index not present"<<endl;
						return;
					}
					groupManagement.groups[user].receivedMails.erase(groupManagement.groups[user].receivedMails.end() - n);
					int i = 1;
					cout<<"S.No.\t\tFrom\t\tTo\t\tSubject\t\tContent"<<endl;
					cout<<"------------------------------------------------------------------------------"<<endl;
					tempMails = groupManagement.groups[user].receivedMails;
					for(auto it = tempMails.rbegin() ; it  != tempMails.rend() ; it++)
					{
						cout<<i<<"\t\t"<<it->getFrom()<<"\t\t"<<it->getTo()<<"\t\t"<<it->getSubject()<<"\t\t"<<it->getContent()<<endl;
						i++;
					}
					cout<<endl;
				}
			}
			else
			{
				if(userFrom)
				{
					vector<Mail> tempMails = userManagement.users[user].sentMails;
					if(n > tempMails.size())
					{
						cout<<"Index not present"<<endl;
						return;
					}
					userManagement.users[user].sentMails.erase(userManagement.users[user].sentMails.end() - n);
					int i = 1;
					cout<<"S.No.\t\tTo\t\tSubject\t\tContent"<<endl;
					cout<<"------------------------------------------------------------------------------"<<endl;
					 tempMails = userManagement.users[user].sentMails;
					for(auto it = tempMails.rbegin() ; it  != tempMails.rend() ; it++)
					{
						cout<<i<<"\t\t"<<it->getTo()<<"\t\t"<<it->getSubject()<<"\t\t"<<it->getContent()<<endl;
						i++;
					}
					cout<<endl;
				}
				else
				{
					vector<Mail> tempMails = groupManagement.groups[user].sentMails;
					if(n > tempMails.size())
					{
						cout<<"Index not present"<<endl;
						return;
					}
					groupManagement.groups[user].sentMails.erase(groupManagement.groups[user].sentMails.end() - n);
					int i = 1;
					cout<<"S.No.\t\tTo\t\tSubject\t\tContent"<<endl;
					cout<<"------------------------------------------------------------------------------"<<endl;
					tempMails = groupManagement.groups[user].sentMails;
					for(auto it = tempMails.rbegin() ; it  != tempMails.rend() ; it++)
					{
						cout<<i<<"\t\t"<<it->getTo()<<"\t\t"<<it->getSubject()<<"\t\t"<<it->getContent()<<endl;
						i++;
					}
					cout<<endl;
				}
			}
		}

}mailManagement;

int main()
{
	int option = 11;
	while(option != 10)
	{
		cout<<"1)Create User\n2)Create Group\n3)Group Assignment\n4)Compose\n5)Inbox\n6)Sent Mail\n7)Delete Mail\n8)Recall\n9)Recall\n10)Exit";
		cout<<endl;
		cout<<"Select any option: ";
		cin>>option;
		if(option > 10 || option < 1)
		{
			cout<<"Improper input"<<endl;
			return 0;
		}
		if(option == 1)
		{
			userManagement.createUser();
			userManagement.printUsers();
		}
		else if(option == 2)
		{
			groupManagement.createGroup();
			groupManagement.printGroups();
		}
		else if(option == 3)
		{
			groupManagement.groupAssignment();
		}
		else if(option == 4)
		{
			mailManagement.compose();
		}
		else if(option == 5)
		{
			mailManagement.inbox();
		}
		else if(option == 6)
		{
			mailManagement.sentMail();
		}
		else if(option == 7)
		{
			mailManagement.deleteMail();
		}

	}

}