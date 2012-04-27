#include "KMP.h"

int main(){
	printf("=========origin===========\n");
	KMP_search_origin("abacababa","aba");
	printf("=========origin===========\n");

	printf("=========normal===========\n");
	KMP_search("abacababa","aba");
	printf("=========normal===========\n");

	printf("=========enhanced===========\n");
	KMP_search_enhanced("abacababa","aba");
	printf("=========enhanced===========\n");
	return 0;
}