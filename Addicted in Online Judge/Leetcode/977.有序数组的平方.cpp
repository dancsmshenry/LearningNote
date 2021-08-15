int* sortedSquares(int* a, int n, int* returnSize){
	*returnSize=n;
	if(n==0) return a;
	int p=0,q=-1;
	for(int i=0;i<n;i++){
		if(a[i]>=0) {
			p=i;
			q=i-1;
			break;
		}
	} 
	int k=0;
	int *res=(int *)malloc(sizeof(int)*n);
	while(p<n&&q>=0){
		if(a[p]*a[p]<a[q]*a[q]){
			res[k++]=a[p]*a[p];
			p++;
		}
		else{
			res[k++]=a[q]*a[q];
			q--;
		} 
	} 
	while(p<n) {
		res[k++]=a[p]*a[p];
		p++;
	}
	while(q>=0){
		res[k++]=a[q]*a[q];
		q--;
	}
	return res;
}
