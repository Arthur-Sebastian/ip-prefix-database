/*
	Author: A. S. Miller
*/
#include <stdio.h>
#include "lib/prefix.h"

int testSuite() {
	printf("%s", "\t[TEST] Empty access\n");
	list();
	check(0xAFFFFFF1); // expect no segmentation violations
	printf("%s", "\t[TEST] Addition:\n");
	list();
	add(0xFFFF0000, 16); // 255.255.0.0/16
	add(0x20408000, 24); // 32.64.128.0/24
	add(0x80FFFF00, 24); // 128.255.255.0/24
	add(0x80FF0000, 16); // 128.255.0.0/16
	add(0x0A140000, 32); // 10.20.0.0/32
	add(0x0A140000, 16); // 10.20.0.0/16
	add(0xFFFFFFF0, 28); // 255.255.255.240/28
	add(0xFF80FF00, 24); // 255.128.255.0/24
	add(0xFFFFF000, 20); // 255.255.240.0/20
	add(0xFFFFFFFF, 32); // 255.255.255.255/32
	add(0xFFFFFFFF, 32); // 255.255.255.255/32 - DUPLICATE
	list();
	printf("%i\n", add(0xFFFFFFFF, 36)); // invalid mask, expect -1
	printf("%s", "\t[TEST] Deletion:\n");
	del(0x0A140000, 32); // deletion from front of the list
	del(0xFF80FF00, 24); // deletion from middle of the list
	del(0xFFFFFFFF, 32); // deletion from end of the list
	del(0xFFFFFFFF, 32); // expect nothing, non-existent prefix
	list();
	printf("%i\n", del(0xFFFFFFFF, 36)); // invalid mask, expect -1
	printf("%s", "\t[TEST] Check:\n");
	printf("%i\n", check(0x0A1400F0)); // expect 16
	printf("%i\n", check(0x0A1400FF)); // expect 16
	printf("%i\n", check(0xFFFFFFF0)); // expect 28
	printf("%i\n", check(0x80FFFFF1)); // expect 24
	printf("%i\n", check(0xAFFFFFF1)); // expect -1
	printf("%s", "\t[TEST] Completed!\n");
	return 0;
}

int main() {
	// run tests
	testSuite();
	return 0;
}
