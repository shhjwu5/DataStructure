#include <iostream>
 
using namespace std;
 
int main()
{
	char a[100];
	char b[100];
	
	int lena = 0, lenb = 0;
	
	char tmp;
	tmp = getchar();
	while(tmp>='a' and tmp<='z'){
		a[lena] = tmp;
		lena++;
		tmp = getchar();
	}
	
	tmp = getchar();
	while(tmp>='a' and tmp<='z'){
		b[lenb] = tmp;
		lenb++;
		tmp = getchar();
	}
	
	int mid = 0;
	int add = 0;
	char result[100] = {0};
	if(lena > lenb){
		for(int i = 0;i<lenb;i++){
			mid = (a[lena-i-1]-'a')+(b[lenb-i-1]-'a')+add;
			tmp = mid%26+'a';
			result[lena-i-1] = tmp;
			add = mid/26;
		}
		for(int i = lena-lenb-1;i>=0;i--){
			mid = a[i]-'a'+add;
			tmp = mid%26+'a';
			add = mid/26;
			result[i] = tmp;
		}
		if(add){
			putchar(add+'a');
			for(int i = 0;i<lena;i++){
				putchar(result[i]);
			}
		}else{
			for(int i = 0;i<lena;i++){
				putchar(result[i]);
			}
		}
	}else{
		for(int i = 0;i<lena;i++){
			mid = (a[lena-i-1]-'a')+(b[lenb-i-1]-'a')+add;
			tmp = mid%26+'a';
			result[lenb-i-1] = tmp;
			add = mid/26;
		}
		for(int i = lenb-lena-1;i>=0;i--){
			mid = b[i]-'a'+add;
			tmp = mid%26+'a';
			add = mid/26;
			result[i] = tmp;
		}
		if(add){
			putchar(add+'a');
			for(int i = 0;i<lenb;i++){
				putchar(result[i]);
			}
		}else{
			for(int i = 0;i<lenb;i++){
				putchar(result[i]);
			}
		}
	}
	
	return 0;
}
