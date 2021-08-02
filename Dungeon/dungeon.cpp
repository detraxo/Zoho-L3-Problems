#include<bits/stdc++.h>
using namespace std;

struct hash_pair {
    template <class T1, class T2>
    size_t operator()(const pair<T1, T2>& p) const
    {
        auto hash1 = hash<T1>{}(p.first);
        auto hash2 = hash<T2>{}(p.second);
        return hash1 ^ hash2;
    }
};

char dungeon[1001][1001];
vector<pair<int , int>> BFS(int n , int m , char starting , char ending , char block , char monster , bool hasGun)
{
	queue<int> qx , qy;
	unordered_map<pair<int , int>, pair<int , int>, hash_pair> prev;
	int sr , sc;
	int visited[n][m];
	memset(visited , 0 , sizeof(visited));

	for(int i = 0 ; i < n ; i++)
		for(int j = 0 ; j < m ; j++)
			if(dungeon[i][j] == starting)
			{
				sr = i;
				sc = j;
				break;
			}

	qx.push(sr);
	qy.push(sc);

	bool reachedEnd = false;
	int countLeft = 1;
	int countNext = 0;
	int count = 0;

	int er, ec;

	while(!qx.empty())
	{
		int r = qx.front();
		int c = qy.front();
		qx.pop();
		qy.pop();

		if(dungeon[r][c] == ending)
		{
			reachedEnd = true;
			er = r;
			ec = c;
			break;
		}

		int dr[8] = {-1 , 1 , 0 , 0 , -1 ,  1 , 1 , -1};
		int dc[8] = {0 , 0 , -1 , 1 ,  1 , -1 , 1 , -1};
		for(int i = 0 ; i < 8 ; i++)
		{
			int rr = r + dr[i];
			int cc = c + dc[i];
			if(rr < 0 || rr >= n || cc < 0 || cc >= m)
				continue;
			if(visited[rr][cc] || dungeon[rr][cc] == block)
				continue;
			if((!hasGun) && dungeon[rr][cc] == monster)
				continue;
			visited[rr][cc] = 1;
			
			prev[pair<int , int> (rr , cc)] = pair<int , int> (r , c);
			qx.push(rr);
			qy.push(cc);
			countNext++;

		}
		countLeft--;
		if(countLeft == 0)
		{
			countLeft = countNext;
			countNext = 0;
			count++;
		}
	}

	vector<pair<int , int>> result;

	if(reachedEnd)
	{
		result.push_back(pair<int , int> (count , count));
		while(count >= 1)
		{
			result.push_back(prev[pair<int , int> (er , ec)]);
			int temp = prev[pair<int , int> (er , ec)].first;
			ec = prev[pair<int , int> (er , ec)].second;
			er = temp;
			count--;
		}

	}
	else
		result.push_back(pair<int , int> (-1 , -1));
	
	return result;
}
int main()
{
	int n , m;
	cin>>n>>m;
	cout<<"\t. = free space\n\t# = block\n\tS = Starting Postion\n\tE = Destination\n\t8 = Monster\n\t^ = Gun"<<endl<<endl;
	for(int i = 0 ; i < n ; i++)
	{
		string input;
		cin>>input;
		for(int j = 0 ; j < m ; j++)
			dungeon[i][j] = input[j];
	}

	vector<pair<int , int>> routeWithoutGun = BFS(n , m , 'S' , 'E' , '#' , '8' , false);
	vector<pair<int , int>> routeTowardsGun = BFS(n , m , 'S' , '^' , '#' , '8' , false);
	vector<pair<int , int>> routeExitWithGun = BFS(n , m , '^' , 'E' , '#' , '8' , true);



	if(routeWithoutGun[0].first < routeTowardsGun[0].first + routeExitWithGun[0].first && routeWithoutGun[0].first >= 1)
	{
		for(int i = 1 ; i <= routeWithoutGun[0].first ; i++)
			dungeon[routeWithoutGun[i].first][routeWithoutGun[i].second] = '*';
	}
	else
	{
		for(int i = 1 ; i <= routeTowardsGun[0].first ; i++)
			dungeon[routeTowardsGun[i].first][routeTowardsGun[i].second] = '*';
		for(int i = 1 ; i <= routeExitWithGun[0].first ; i++)
			dungeon[routeExitWithGun[i].first][routeExitWithGun[i].second] = '*';
	}
	cout<<endl;
	for(int i = 0 ; i < n ; i++)
	{
		for(int j = 0 ; j < m ; j++)
			cout<<dungeon[i][j];
		cout<<endl;
	}
}