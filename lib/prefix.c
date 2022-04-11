/*
	Author: A. S. Miller
*/
#include "prefix.h"

/*
	Declared as a global variable, since function
	prototype parameters do not include a pointer
	to a database to be added/deleted/read from.
*/
Prefix* database = NULL;

int add(unsigned int base, char mask) {
	// argument check
	if(mask < 0 || mask > 32) {
		return -1;
	}
	// first element
	if(database == NULL) {
		// allocate and fill
		database = malloc(sizeof(Prefix));
		*database = (Prefix){base, mask, NULL};
		return 0;
	}
	// every next element
	Prefix* p_itr = NULL;
	Prefix* itr = database;
	// iterate until correct place for insertion
	while(itr != NULL) {
		// sort by base and then by masks
		if(itr -> base < base || (itr -> base == base && itr -> mask > mask)) {
			p_itr = itr;
			itr = itr -> next;
			continue;
		}
		//duplicate check
		else if(itr -> base == base && itr -> mask == mask) {
			return 0;
		}
		break;
	}
	// insert at the beginning of the list
	if(p_itr == NULL) {
		Prefix* new = malloc(sizeof(Prefix));
		*new = (Prefix){base, mask, database};
		database = new;
		return 0;
	}
	// end or the middle of the list
	Prefix* new = malloc(sizeof(Prefix));
	*new = (Prefix){base, mask, p_itr -> next};
	p_itr -> next = new;
	return 0;
}

int del(unsigned int base, char mask) {
	// argument check
	if(mask < 0 || mask > 32) {
		return -1;
	}
	//search through ordered list
	Prefix* p_itr = NULL;
	Prefix* itr = database;
	while(itr != NULL) {
		// found a match, break
		if(base == itr -> base && mask == itr -> mask) {
			break;
		}
		// match will not be found
		if(itr -> next == NULL || base < itr -> base) {
			return 0;
		}
		// advance iterator to next element
		p_itr = itr;
		itr = itr -> next;
	}
	//delete first element
	if(p_itr == NULL) {
		database = itr -> next;
		free(itr);
		return 0;
	}
	//delete any other element
	p_itr -> next = itr -> next;
	free(itr);
	return 0;
}

char check(unsigned int ip) {
	// for every item in sorted database
	Prefix* itr = database;
	while(itr != NULL) {
		// advance until found >= ip
		Prefix* next = itr -> next;
		if(next != NULL && next -> base <= ip) {
			itr = itr -> next;
			continue;
		}
		// compare by address prefixes, truncate bits outside mask
		uint8_t shift = 32 - (itr -> mask);
		if( !(itr -> base >> shift ^ ip >> shift) ) {
			return itr -> mask;
		}
		break;
	}
	return -1;
}

void ddec(uint32_t ipa) {
	// split integer into char array for displaying
	uint8_t ip[4];
	// bitmask, and shift for dotted decimal notation
	ip[0] = ((0xFF000000) & ipa) >> 24;
	ip[1] = ((0x00FF0000) & ipa) >> 16;
	ip[2] = ((0x0000FF00) & ipa) >> 8;
	ip[3] = ((0x000000FF) & ipa);
	// display into standard output
	printf("%u.%u.%u.%u", ip[0], ip[1], ip[2], ip[3]);
}

void list() {
	// iterate through all elements in database
	Prefix* itr = database;
	while(itr != NULL) {
		//display in dotted decimal
		ddec(itr -> base);
		printf("/%d\n", itr -> mask);
		// move to the next prefix in set
		itr = itr -> next;
	}
	return;
}

