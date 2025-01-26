namespace ntt {
  const int mod=998244353;
  const int root=15311432;
  const int inv_root=469870224;
  const int root_pw=1<<23;
   
  int reverse(int mask, int LG) {
    int r = 0;
    for(int i = 0; i < LG; i++) r|=((mask&(1<<i))>>i)<<(LG-i-1);
    return r;
  }
  int powmod(int a, int k, int m) {
   	int ans=1;
    while(k){
      if(k&1) ans=(int)(1ll*ans*a%m);
      a=(int)(1ll*a*a%m);
      k/=2;
    }
    return ans;
  }
  void ntt(vector<int> &a, int LG, bool inv=0){
  	int _n=(int)a.size();
    vector<int> b=a;
    for(int i=0; i<_n; i++) b[i]=a[reverse(i,LG)];
    for(int iter=0; iter<LG; iter++){
      int len=1<<iter;
      int w=inv?inv_root:root;
      for(int _x=iter+1; _x<23; _x++) w=(int)(1ll*w*w%mod);
      int i=0,j=0;
      for(int cnt=(_n>>(iter+1)); cnt--; ){
        i=j;
        j=i+len;
        int t=1;
        for(int l=len; l--; ){
      	  int u=(int)(1ll*t*b[j]%mod);
          a[i]=b[i]+u<mod?b[i]+u:b[i]+u-mod;
          a[j]=b[i]-u<0?b[i]-u+mod:b[i]-u;
          t=(int)(1ll*t*w%mod);
          i++;
          j++;
        }
      }
      swap(a,b);
    }
   	a=b;
    if(inv){
    	int inv_n=powmod(_n,mod-2,mod);
    	for(int i=0; i<_n; i++) a[i]=(int)(1ll*a[i]*inv_n%mod);
    }
  }
  vector<int> conv(vector<int> &a, vector<int> &b) {
  	int na=a.size(),nb=b.size();
  	int N=1,logn=0;
  	while(N<max(na,nb)) N<<=1,logn++;
  	N<<=1;
  	logn++;
  	vector<int> fa(a.begin(),a.end());
  	vector<int> fb(b.begin(),b.end());
  	fa.resize(N);
  	fb.resize(N);
  	ntt(fa,logn);
  	ntt(fb,logn);
  	for(int i=0; i<N; ++i) fa[i]=(int)(1ll*fa[i]*fb[i]%mod);
  	ntt(fa,logn,1);
  	vector<int> c;
  	for(int i=0; i<na+nb-1; i++) c.push_back(fa[i]);
  	return c;
  }
  void bpow(vector <int> &a, int k){
  	vector <int> ans;
  	while(k){
  		if(k&1){
  			if(ans.empty()) ans=a;
  			else ans=conv(ans,a);
  		}
  		k/=2;
  		a=conv(a,a);
  	}
  	a=ans;
  }
}
