//https://atcoder.jp/contests/arc076/tasks/arc076_b

//rohitaas_beri
// #include <ext/pb_ds/assoc_container.hpp>
// #include <ext/pb_ds/tree_policy.hpp>
// using namespace __gnu_pbds;
// #define ordered_set tree<int, null_type,less<int>, rb_tree_tag,tree_order_statistics_node_update>
#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define ull unsigned long long
#define int ll
#define dd long double
#define vi vector<int> 
#define vvi vector<vi> 
#define vvvi vector<vvi>
#define vpii vector<pair<int,int> > 
#define pii pair<int,int> 
#define vvpii vector<vpii> 
#define UB upper_bound
#define LB lower_bound
#define beg(v) v.begin()
#define en(v) v.end()
#define pb push_back
#define nl "\n"
#define con continue
#define br break
#define ret return
#define F first
#define S second
#define yes print("YES")
#define no print("NO")
#define rep(i,a,b) for(int i =(a);i<(b);i++)
#define all(v) v.begin(),v.end()
#define rev(v) reverse(all(v))
#define maxv(v) *max_element(all(v));
#define minv(v) *min_element(all(v));
#define sumv(v) accumulate(all(v),0ll)
#define print(value)  cout<<(value)<<nl
#define print2(v1,v2) cout<<(v1)<<" "<<(v2)<<nl
#define print3(v1,v2,v3) cout<<(v1)<<" "<<(v2)<<" "<<(v3)<<nl
#define print4(v1,v2,v3,v4) cout<<(v1)<<" "<<(v2)<<" "<<(v3)<<" "<<(v4)<<nl
#define printv(v)rep(it,0,v.size()){cout<<v[it]<<" ";}cout<<"\n"
#define printvv(v)rep(it,0,v.size()){rep(it2,0,v[0].size()){cout<<v[it][it2]<<" ";}cout<<"\n";}
#define sz(v) ((int)v.size())

#define bug(...)  __f (#__VA_ARGS__, __VA_ARGS__)

template <typename Arg1>
void __f (const char* name, Arg1&& arg1) { cout << name << " : " << arg1 << endl; }
template <typename Arg1, typename... Args>
void __f (const char* names, Arg1&& arg1, Args&&... args)
{
     #ifndef ONLINE_JUDGE 

     	const char* comma = strchr (names + 1, ',');
	    cout.write (names, comma - names) << ":" << arg1 << "|"; __f (comma + 1, args...);
                    
    #endif 
}
struct DSU{
  int n ;

  vi parent,rank;

  DSU(int N)
  {
    n = N;
    parent.resize(n+1,0);
    rank.resize(n+1,1);
    iota(all(parent),0ll);
  }

  int find(int x)
  {
    if(parent[x]==x)return x;

    //path compression

    return parent[x]= find(parent[x]);
  }

  void join(int x, int y)
  {
    int s1 = find(x);
    int s2= find(y);

    if(s1!=s2)
    {
      //union by rank
      if(rank[s1]>rank[s2])
      {
         parent[s2]=s1;
         rank[s1]+=rank[s2];
      }
      else
      {
        parent[s1]=s2;
        rank[s2]+=rank[s1];
      }
    }
  }

};



struct UGraph{
  int n;
  vvi adj; 
  vvpii wadj;//for weighted graph
  vi vis,val;

  UGraph(int N)
  {
     n = N;
    wadj.resize(n+1);
    adj.resize(n+1);
    vis.resize(n+1,0);
    val.resize(n+1,1);
  }


  void addEdge(int u, int v,bool weighted=false, int w=0)
  { 
    if(!weighted)
    {
      adj[u].pb(v);
      adj[v].pb(u);
    }
    else 
    {
      wadj[u].pb({v,w});
      wadj[v].pb({u,w});
    }
  }

  void dfs(int node)
  {
    vis[node]=1;
    for(auto i : adj[node])
    {
      if(!vis[i])
      {
        dfs(i);
      }
    }
  }

  void bfs(int node)
   {
     vis.clear();vis.resize(n+1,0);
     queue<int> q;
 
     q.push(node);
    
     vis[node]=1; 
     while(!q.empty())
     {
       int check = q.front(); q.pop();
       for(auto i : adj[check])
       {
         if(!vis[i])
         {
           vis[i]=1;
           q.push(i);
         }
       }
     }
   }

   int PrimsAlgo() //for weighted graph
   {
      priority_queue<pii,vpii, greater<pii>  > q;

      vis.clear();
      vis.resize(n+1,0);

      int source =1 ,ans=0;
      q.push({0,source});

      while(sz(q))
      {
        auto best = q.top();
        q.pop();

        if(vis[best.S])
        {
          con;
        }
        vis[best.S]=1;
        ans += best.F;

        for(auto i : wadj[best.S])
        {
          if(!vis[i.F])
          {
            q.push({i.S,i.F});
          }
        }
      }
      return ans;
   }

   int KruskalsAlgo()
   {
      vvi edges;
      
      rep(i,1,n+1)
      {
        for(auto j : wadj[i])
        {
           edges.pb({j.S,i,j.F});
        }
       
      }
      
      sort(all(edges));

      DSU dsu(n);

      int ans =0;

      for(auto i : edges)
      {
        if(dsu.find(i[1])!=dsu.find(i[2]))
        {
          ans +=i[0];
          dsu.join(i[1],i[2]);
        }
      }
      return ans;


   }
};

bool compare(pii &a, pii &b){

return a.S<b.S;
}

void solve()
{

  int n;cin>>n;
  vpii points;
  map<pii,int> comp;
  int cnt =1;
  rep(i,0,n)
  {
    int x, y;cin>>x>>y;

    if(comp.count({x,y}))
    {
      con;
    }
    points.pb({x,y});

    
    comp[{x,y}]=cnt++;
  }

  vpii x,y ;
  x = points, y = points;

  sort(all(x));
  sort(all(y),compare);
  UGraph g(n);

  rep(i,1,sz(x))
  {
    g.addEdge(comp[x[i]],comp[x[i-1]],1,min(abs(x[i].F-x[i-1].F),abs(x[i].S-x[i-1].S)));
  }

  rep(i,1,sz(y))
  {
    g.addEdge(comp[y[i]],comp[y[i-1]],1,min(abs(y[i].F-y[i-1].F),abs(y[i].S-y[i-1].S)));
  }

  print(g.PrimsAlgo());
 
 
}

signed main() {

    ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(0);
    clock_t printClock = clock();

    int T=1;
    //cin>>T;

   
    while(T--) solve();

    cerr<< "RUNTIME : "<<((double)clock()-printClock)/CLOCKS_PER_SEC<<"s";
}




/* notes:

1) Dont use vector.resize() without vector.clear() .

2) Range of long long is -2^63 to 2^63-1 , range of unsigned long long 
   is 0 to 2^64-1 .

3) Expected number of coin throws to get N consecutive heads is 2^(n+1) - 2 .

4) Upper bound of number of divisors of a number n is n^(1/3) .

5) GCD(x,y)=GCD(x-y,y) , The same applies for multiple arguments .

6) To meet the constraints int the question,  we can sometimes kick out one state of our dp.
  We can achieve that by a relatively common trick: turn the removed state into the value of the dp.


7) If we have N elements out of which we want to choose K elements and it is allowed
  to choose one element more than once, then number of ways are given by: nCr(n+k-1,k) .


*/


/* Good Questions :

1 ) https://www.codechef.com/submit/SECPLAYER

 */
