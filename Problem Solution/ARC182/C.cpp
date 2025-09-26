// By Luogu _ANIG_
#include <bits/stdc++.h>
using namespace std;
#define int long long
const int mods=998244353,N=66,M=20,T=6,p[6]={2,3,5,7,11,13};
struct node{
    int w[N][N];
    friend node operator*(node a,node b){
        node c;
        for(int i=0;i<N;i++){
            for(int j=0;j<N;j++){
                c.w[i][j]=0;
                for(int k=0;k<N;k++){
                    c.w[i][j]+=a.w[i][k]*b.w[k][j];
                    c.w[i][j]%=mods; 
                }
            }
        }
        return c;
    }
}cs,zy;
node pows(node a,int b){
    if(b==1)return a;
    node res=pows(a,b>>1);
    res=res*res;
    if(b&1)res=res*a;
    return res;
}
int n,m,sm[M][6],res;
signed main(){
    cin>>n>>m;
    for(int i=1;i<=m;i++){
        for(int j=0;j<6;j++){
            int x=i;
            while(x%p[j]==0)x/=p[j],sm[i][j]++;
        }
    }
    for(int i=0;i<(1<<T);i++)cs.w[0][i]=1;
    for(int j=1;j<=m;j++){
        for(int k=0;k<(1<<T);k++){
            zy.w[k][k]++;
            for(int l=k;l;l=l-1&k){
                int ans=1;
                for(int r=0;r<6;r++){
                    if(l>>r&1^1)continue;
                    ans=ans*sm[j][r]%mods;
                }
                zy.w[k^l][k]+=ans;
                zy.w[k^l][k]%=mods;
            }
        }
    }
    zy.w[(1<<T)-1][1<<T]=zy.w[1<<T][1<<T]=1;
    cs=cs*pows(zy,n);
    cout<<(cs.w[0][1<<T]-1+cs.w[0][(1<<T)-1])%mods;
}
