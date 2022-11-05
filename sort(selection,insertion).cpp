#include<stdio.h>
void selection_sort(int arr[50],int n)
{
	int i, j, pos, temp;
    for (i = 0; i < n-1; i++) {
    	pos = i;//pos gives the smallest element
    	for (j = i + 1; j < n; j++) {
        	if (arr[pos] > arr[j])
            	pos = j;
    	}
      	if (pos != i) {
			temp = arr[i];
			arr[i] = arr[pos];
			arr[pos] = temp;
        }
    }
	for (i = 0; i < n; i++)
    	printf("%d\t", arr[i]);
}
void insertion_sort(int a[50],int n)
{
	int i, j, temp;  
    for (i = 1; i < n; i++) {  
        temp = a[i];  
        j = i - 1;  
        while(j>=0 && temp <= a[j])   
        {    
            a[j+1] = a[j];     
            j--;    
        }    
        a[j+1] = temp;    
    }
	for (i = 0; i < n; i++)
    	printf("%d\t", a[i]);    
}
int main()
{
	int arr[50],n;
	printf("enter the no. of elements u want :");
	scanf("%d",&n);
	for(int i=0;i<n;i++)
	{
		scanf("%d",&arr[i]);
	}
	selection_sort(arr, n);
	printf("\n");
	insertion_sort( arr, n);
}




















