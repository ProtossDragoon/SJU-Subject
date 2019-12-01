#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<Windows.h>

/*

문제에서 제시한 Cache size 는 , valid bit 과 tag bit 를 제외한 data 의 크기로 이해하고 작성했습니다.

함수 initcache 의 주석 네 줄을 제거하면, 입력받는 Cache size 를 valid bit 과 tag bit 를 포함한 size 로 이해합니다.

*/


#define PRINT_DATA 0

#define NONE 0
#define LEAST_RECENTLY_USED 1

#define VALID_BIT_SIZE 1

typedef unsigned int uint;
typedef struct cacheblock cacheblock;
typedef struct L1cache L1;
typedef struct address address;

struct L1cache{
	uint cachesize_bit;
	int cachesize_KByte;
	int blocksize_Byte;
	int associative_type;
	int block_replacement_policy;

	int _0_byteoffset_bit;
	int _1_blockoffset_bit;
	int _2_index_bit;
	int _3_tag_bit;

	int __count_of_set;
	cacheblock** __block;
};
struct cacheblock {
	int _0_validbit;
	uint _1_tagbit;
	uint _2_databit;
};
struct address {
	int _0_byteoffset;
	int _1_blockoffset;
	int _2_index;
	int _3_tag;
};

void valid_data_sorting_when_hit(cacheblock* selected_set, int hit_block_index, int ways) {
	// 가장 최근에 사용한 bit 을 배열의 맨 앞으로!

	cacheblock tmpblock;
	tmpblock = selected_set[hit_block_index];
	
	for (int i = hit_block_index; i > 0; i--) {
		selected_set[i] = selected_set[i - 1];
	}
	selected_set[0] = tmpblock;
}
int bitCount(uint hex) {
	// hex 를 표현하기 위해 필요한 bit 의 개수를 return

	int cnt = 0;
	hex -= 1;
	while (hex != 0) {
		hex = hex / 2;
		cnt++;
	}
	return cnt;
}
L1* initCache(int cachesize_KB, int blocksize_B, int ways, int block_replacement_policy) {
	// 캐시를 생성

	L1* newcache = NULL;
	newcache = (L1*)malloc(sizeof(L1) * 1);
	if (newcache == NULL) return NULL;

	newcache->cachesize_KByte = cachesize_KB;
	newcache->cachesize_bit = cachesize_KB * 1024 * 8;
	newcache->blocksize_Byte = blocksize_B;
	newcache->associative_type = ways;

	if (ways != 1) {
		newcache->block_replacement_policy = block_replacement_policy;
	}
	else {
		newcache->block_replacement_policy = NONE;
	}



	// 0. byte offset
	newcache->_0_byteoffset_bit = bitCount(4); // to process 1 word. 1word = 4byte(32bit) so 2 bit	

	// 1. block offset
	newcache->_1_blockoffset_bit = bitCount((newcache->blocksize_Byte) / 4); // to find a block, 몇 번째 block 인가! 4byte = 1 word 이므로..
	int remain_bit;
	remain_bit = 32 - newcache->_0_byteoffset_bit - newcache->_1_blockoffset_bit;


	// calculate and find proper index's bit count
	uint total_cache_size;
	total_cache_size = newcache->cachesize_bit;
	int count_of_set;
	int i;
	for (i = 1; i < remain_bit; i++) {
		count_of_set = (int)pow((double)2, i); // count_of_set 은 block offset 에 i bit 가 할당될때 set 의 (1 way 일경우 모두 다른 set) 개수.

#ifdef DEBUG
		printf("count-of-set : bit - %d, %d\n", i, count_of_set);
		printf("cache-size : with %d bit, %d bit\n", bitCount(
			(total_cache_size
				- (count_of_set * (newcache->associative_type * VALID_BIT_SIZE))
				- (count_of_set * (remain_bit - i) * newcache->associative_type)) // remain_bit - i == tag bits
			/ (newcache->blocksize_Byte * 8 * newcache->associative_type)),
			(total_cache_size
				- (count_of_set * (newcache->associative_type * VALID_BIT_SIZE))
				- (count_of_set * (remain_bit - i) * newcache->associative_type))
			/ (newcache->blocksize_Byte * 8 * newcache->associative_type)
		);
#endif // DEBUG


		if (i > bitCount(
			(total_cache_size
				- (count_of_set * VALID_BIT_SIZE * newcache->associative_type)
				- (count_of_set * (remain_bit - i) * newcache->associative_type) // remain_bit - i == tag bits
			)/ (newcache->blocksize_Byte * 8 * newcache->associative_type))) {
			break;
		}
	}
	i = i - 1;

	// 2. index
	newcache->_2_index_bit = i;

	// 3. tag
	newcache->_3_tag_bit = remain_bit - i;


	// final size of set
	count_of_set = newcache->cachesize_bit / (newcache->blocksize_Byte * 8
//		+ VALID_BIT_SIZE
//		+ newcache->_3_tag_bit
		);
	newcache->__count_of_set = count_of_set;


#ifdef DEBUG
	printf("count of set : %d\n", newcache->__count_of_set);
	printf("count of associative tyep : %d\n", newcache->associative_type);
#endif // DEBUG

	// alloate
	newcache->__block = (cacheblock**)malloc(sizeof(cacheblock*) * newcache->__count_of_set);
	if (newcache->__block == NULL) return;
	for (int j = 0; j < newcache->__count_of_set; j ++) {
		(newcache->__block[j]) = (cacheblock*)malloc(sizeof(cacheblock) * newcache->associative_type);
		if ((newcache->__block[j]) == NULL) return;
		for (int k = 0; k < newcache->associative_type; k++) { // init
			(newcache->__block[j][k])._0_validbit = 0;
			(newcache->__block[j][k])._1_tagbit = 0;
			(newcache->__block[j][k])._2_databit = 0;
		}
	}

	return newcache;
}
void print_cacheInfo(L1* cache, char* cachename) {
	// 캐시 정보를 예쁘게 출력

	system("cls");
	printf("\n--------------------------------------------------------\n");
	printf("            %s CACHE DATA           \n", cachename);
	
	printf("\n");
	printf("associative type : ");
	if (cache->associative_type != 1) {
		printf("%d way, replacement policy : LRU\n", cache->associative_type);
	}
	else {
		printf("1 Way\n");
	}
	printf("byte offset  : %d bit\n", cache->_0_byteoffset_bit);
	printf("block offset : %d bit\n", cache->_1_blockoffset_bit);
	printf("index _______: %d bit\n", cache->_2_index_bit);
	printf("tag   _______: %d bit\n", cache->_3_tag_bit);
	printf("total 32 bit\n\n");


	int cbcpe = (cache->associative_type * (int)pow((double)2, cache->_1_blockoffset_bit));
	printf("cache block cnt per entrance : %d \n", cbcpe);
	
	int cacheblocksize = ((int)pow((double)2, cache->_1_blockoffset_bit)) * 4;
	printf("cache block size ___________ : %d Byte (not include Tag and Valid)\n", cacheblocksize);
	
	int cachesetsize = cacheblocksize * cache->associative_type;
	printf("cache set size _____________ : %d Byte, %d way x %d block (not include Tag and Valid)\n", cachesetsize, cache->associative_type, cbcpe);
	
	int tagbitsize = cache->_3_tag_bit;
	printf("tag bit size _______________ : %d \n", tagbitsize);
	
	int validbitsize = VALID_BIT_SIZE;
	printf("valid Field size ___________ : %d \n", validbitsize);
	
	int number_of_block = (int)pow((double)2, cache->_2_index_bit) * cache->associative_type;
	printf("number of cache block ______ : %d \n", number_of_block);
	printf("number of cache block FINAL_ : %d \n", cache->__count_of_set);
	printf("\n");

	uint cache_size = number_of_block * (cacheblocksize * 8 + tagbitsize + validbitsize);
	uint cache_size_final = cache->__count_of_set * (cacheblocksize * 8 + tagbitsize + validbitsize);
	printf("containable data size (B) : %d\n", number_of_block * cacheblocksize * 8 / 8);
	printf("containable data size (KB): %d\n", number_of_block * cacheblocksize * 8 / (8 * 1024));

	printf("cache size (B) : %d \n", cache_size / 8);
	printf("cache size (KB): %d \n", cache_size / (8 * 1024));
	printf("caution : 이것은 bit 상 가장 크게 이용할 수 있는 경우일 뿐, 실제로 %d KB 를 이용할 수 있는 것은 아닐 수도 있음.\n", cache_size / (8 * 1024));

	printf("REAL cache size (B) : %d\n", cache_size_final / 8);
	printf("REAL cache size (KB): %d\n", cache_size_final / (8 * 1024));
	printf("caution : 따라서 tag bit 와 valid bit 을 모두 포함한 실제 캐시의 크기는 %lf KB 임.\n", cache_size_final / (double)(8 * 1024));
	printf("\n");

	printf("--------------------------------------------------------\n\n");
}
address parsing_address(uint address_query, L1* cache) {
	// input 을 바탕으로 address 전처리.


	//-----------------------------------------------------------
	int byte_modulo;
	byte_modulo = (int)pow((double)2, cache->_0_byteoffset_bit);
	// 물론 byte_modulo 관련 데이터는 이 문제에서 사용되지 않음.
	// 그리고 실제로도 byte offset 는 논리적으로 이 단계에서 비교하지 않음.

	int word_modulo;
	word_modulo = (int)pow((double)2, cache->_1_blockoffset_bit);

	int way_modulo;
	way_modulo = (int)pow((double)2, cache->_2_index_bit);
	

	int byte_index, word_index, way_index, tag;
	byte_index = address_query % byte_modulo;
	word_index = (address_query / byte_modulo) % word_modulo;
	way_index =	(address_query / (byte_modulo * word_modulo)) % way_modulo;
	tag = address_query / (byte_modulo * word_modulo * way_modulo);

	address parsed_address;
	parsed_address._0_byteoffset = byte_index;
	parsed_address._1_blockoffset = word_index;
	parsed_address._2_index = way_index;
	parsed_address._3_tag = tag;

	return parsed_address;
}
int read_data(uint address_query, L1* cache) {
	// 읽거나, 쓰거나.

	address parsed_address;
	parsed_address = parsing_address(address_query, cache);


	cacheblock* selected_set;
	selected_set = cache->__block[parsed_address._2_index];

	int hitflag = 0, hitindextmp = 0;
	for (int i = 0; i < cache->associative_type; i++) {
		if (selected_set[i]._0_validbit == 1) { // selected_set's i th block
			if (selected_set[i]._1_tagbit == parsed_address._3_tag) {
				// hit !
				hitflag = 1;
				hitindextmp = i;
			}
		}
		if (hitflag == 1) {
			// hit data sorting -- 맨 앞으로 보내기, 1 way 일 경우 조심하기!
			valid_data_sorting_when_hit(selected_set, hitindextmp, cache->associative_type);
			return 1;
		}
		hitflag = 0;
	}


	// 일단 1 way 라고 치고.. 하나만 있다고 치자고
	if (cache->block_replacement_policy == LEAST_RECENTLY_USED) {
		int i;
		for (i = 1; i < cache->associative_type; i++) {
			// valid 가 0인데 가장 앞에 있는 놈. 모든 valid 가 1일 경우에는, valid 중 가장 뒤에 있는 놈 (LRU).
			if (selected_set[i]._0_validbit == 0) { //대충 여기가 끝자락이라는 뜻.
				break;
			}
		}
		// 끝까지 차 있었을지도 모름. 1way 일때도 마찬가지.
		// 어 그런데 아니면.. 텅 비어있었으면 어떻게해? 1부터시작하지 뭐

		if (i >= cache->associative_type) {
			selected_set[i - 1]._0_validbit = 1;
			selected_set[i - 1]._1_tagbit = parsed_address._3_tag;
		}
		else {
			if (selected_set[i - 1]._0_validbit == 1) {
				selected_set[i]._0_validbit = 1;
				selected_set[i]._1_tagbit = parsed_address._3_tag;
			}
			else { // i - 1 block is invalid
				selected_set[i - 1]._0_validbit = 1;
				selected_set[i - 1]._1_tagbit = parsed_address._3_tag;
			}
		}
	}
	else {
		selected_set[0]._0_validbit = 1;
		selected_set[0]._1_tagbit = parsed_address._3_tag;
	}

	// miss
	return 0;
}

void _5_point(int print) {

	FILE* fp = NULL;
	char filename[101];


	// trace file name - user input
	printf("File : ");
	scanf("%s", filename);
	fp = fopen(filename, "r");
	if (fp == NULL)return;


	// cache size select - user input
	int cachesize;
	printf("Unified cache size (KB) : ");
	scanf("%d", &cachesize);
	printf("\n");


	// init cache
	L1* cache = NULL;
	cache = initCache(cachesize, 32, 1, LEAST_RECENTLY_USED);
	
	if (print == PRINT_DATA) 
		print_cacheInfo(cache, "Unified ");

	int label;
	uint address;
	int l1_instrn_cnt = 0, instrnhit = 0;
	int l1_data_cnt = 0, readcnt = 0, writecnt = 0, readhit = 0, writehit = 0;

	int total_cnt = 0, total_access = 0, total_miss = 0;
	float total_missratio = 0;

	while (!feof(fp)) {
		fscanf(fp, "%d %x", &label, &address);
		total_cnt++;

		if (label == 0) {
			// read data
			l1_data_cnt++;
			readcnt++;
			readhit += read_data(address, cache);
		}
		else if (label == 1) {
			// write data
			l1_data_cnt++;
			writecnt++;
			writehit += read_data(address, cache);
		}
		else { // label == 2
			// instruction fetch
			l1_instrn_cnt++;
			instrnhit += read_data(address, cache);
		}
	}

	if (print == PRINT_DATA) {
		printf("data      ------ total : %d ---- hit : %d ---- miss : %d\n", readcnt + writecnt, readhit + writehit, readcnt + writecnt - readhit - writehit);
		printf("readdata  ------ total : %d ---- hit : %d ---- miss : %d\n", readcnt, readhit, readcnt - readhit);
		printf("writedata ------ total : %d ---- hit : %d ---- miss : %d\n", writecnt, writehit, writecnt - writehit);
		printf("instrn    ------ total : %d ---- hit : %d ---- miss : %d\n", l1_instrn_cnt, instrnhit, l1_instrn_cnt - instrnhit);

		printf("l1-instrn cnt : %d\n", l1_instrn_cnt);
		printf("total data cnt : %d\n", l1_data_cnt);
		printf("total instrn cnt : %d\n", total_cnt);	
	}

	// output
	total_access = instrnhit + writehit + readhit;
	total_miss = total_cnt - total_access;
	total_missratio = (float)total_miss / total_cnt;
	printf("Access : %d\n", total_access);
	printf("Miss : %d\n", total_miss);
	printf("Miss ratio : %f\n", total_missratio);

	fclose(fp);
}
void _7_point(int print) {

	FILE* fp = NULL;
	char filename[101];


	// trace file name - user input
	printf("File : ");
	scanf("%s", filename);
	fp = fopen(filename, "r");
	if (fp == NULL)return;


	// cache size select - user input
	int instruction_cache_size, data_cache_size;
	int instruction_cache_block_size, data_cache_block_size;

	printf("Instruction cache size (KB) : ");
	scanf("%d", &instruction_cache_size);
	printf("Instruction cache block size (B) : ");
	scanf("%d", &instruction_cache_block_size);
	printf("Data cache size (KB) : ");
	scanf("%d", &data_cache_size);
	printf("Data cache block size (B) : ");
	scanf("%d", &data_cache_block_size);
	printf("\n");


	// init cache
	L1* instruction_cache = NULL, *data_cache = NULL;
	instruction_cache = initCache(instruction_cache_size, instruction_cache_block_size, 1, LEAST_RECENTLY_USED);
	data_cache = initCache(data_cache_size, data_cache_block_size, 1, LEAST_RECENTLY_USED);

	if (print == PRINT_DATA)
		print_cacheInfo(instruction_cache, "instruction ");
	if (print == PRINT_DATA)
		Sleep(5000);
	if (print == PRINT_DATA)
		print_cacheInfo(data_cache, "data ");



	int label;
	uint address;
	int l1_instrn_cnt = 0, instrnhit = 0;
	int l1_data_cnt = 0, readcnt = 0, writecnt = 0, readhit = 0, writehit = 0;

	int total_cnt = 0, total_access = 0, total_miss = 0;
	float total_missratio = 0;

	while (!feof(fp)) {
		fscanf(fp, "%d %x", &label, &address);
		total_cnt++;

		if (label == 0) {
			// read data
			l1_data_cnt++;
			readcnt++;
			readhit += read_data(address, data_cache);
		}
		else if (label == 1) {
			// write data	
			l1_data_cnt++;
			writecnt++;
			writehit += read_data(address, data_cache);
		}
		else { // label == 2
			// instruction fetch
			l1_instrn_cnt++;
			instrnhit += read_data(address, instruction_cache);
		}
	}

	if (print == PRINT_DATA) {
		printf("\n");
		printf("data      ------ total : %d ---- hit : %d ---- miss : %d\n", readcnt + writecnt, readhit + writehit, readcnt + writecnt - readhit - writehit);
		printf("readdata  ------ total : %d ---- hit : %d ---- miss : %d\n", readcnt, readhit, readcnt - readhit);
		printf("writedata ------ total : %d ---- hit : %d ---- miss : %d\n", writecnt, writehit, writecnt - writehit);
		printf("instrn    ------ total : %d ---- hit : %d ---- miss : %d\n", l1_instrn_cnt, instrnhit, l1_instrn_cnt - instrnhit);
		printf("\n");
	}

	// output
	printf("Instruction cache access : %d\n", l1_instrn_cnt);
	printf("Instruction cahce miss : %d\n", l1_instrn_cnt - instrnhit);
	printf("Instruction cache miss ratio : %f\n", (l1_instrn_cnt - instrnhit) / (float)l1_instrn_cnt);
	printf("Data cache access : %d\n", (readcnt + writecnt));
	printf("Data cache miss : %d\n", (readcnt + writecnt) - (readhit + writehit));
	printf("Data cache miss ratio : %f\n", (readcnt + writecnt - readhit - writehit) / (float)(readcnt + writecnt));

	fclose(fp);
}
void _10_point(int print) {

	FILE* fp = NULL;
	char filename[101];


	// trace file name - user input
	printf("File : ");
	scanf("%s", filename);
	fp = fopen(filename, "r");
	if (fp == NULL)return;


	// cache size and associativity select - user input
	int instruction_cache_size, data_cache_size;
	int instruction_cache_block_size, data_cache_block_size;
	int instruction_cache_associativity, data_cache_associativity;
	int instruction_block_replacement_policy = NONE, data_block_replacement_policy = NONE;

	printf("Instruction cache size (KB) : ");
	scanf("%d", &instruction_cache_size);
	printf("Instruction cache block size (B) : ");
	scanf("%d", &instruction_cache_block_size);
	printf("Data Associativity : ");
	scanf("%d", &instruction_cache_associativity);
	if (instruction_cache_associativity != 1) {
		instruction_block_replacement_policy = LEAST_RECENTLY_USED;
		printf("Work with Least Recently Used\n");
	}

	printf("Data cache size (KB) : ");
	scanf("%d", &data_cache_size);
	printf("Data cache block size (B) : ");
	scanf("%d", &data_cache_block_size);
	printf("Data Associativity : ");
	scanf("%d", &data_cache_associativity);
	if (data_cache_associativity != 1) {
		data_block_replacement_policy = LEAST_RECENTLY_USED;
		printf("Work with Least Recently Used\n");
	}
	printf("\n");


	// init cache
	L1* instruction_cache = NULL, * data_cache = NULL;
	instruction_cache = initCache(instruction_cache_size, instruction_cache_block_size, instruction_cache_associativity, instruction_block_replacement_policy);
	data_cache = initCache(data_cache_size, data_cache_block_size, data_cache_associativity, data_block_replacement_policy);



	// print data
	if (print == PRINT_DATA) {
		print_cacheInfo(instruction_cache, "instruction ");
		Sleep(5000);
		print_cacheInfo(data_cache, "data ");
	}


	// input data
	int label;
	uint address;


	// counters
	int l1_instrn_cnt = 0, instrnhit = 0;
	int l1_data_cnt = 0, readcnt = 0, writecnt = 0, readhit = 0, writehit = 0;
	int total_cnt = 0, total_access = 0, total_miss = 0;
	float total_missratio = 0;


	// loop
	while (!feof(fp)) {
		fscanf(fp, "%d %x", &label, &address);
		total_cnt++;

		if (label == 0) {
			// read data
			l1_data_cnt++;
			readcnt++;
			readhit += read_data(address, data_cache);
		}
		else if (label == 1) {
			// write data	
			l1_data_cnt++;
			writecnt++;
			writehit += read_data(address, data_cache);
		}
		else { // label == 2
			// instruction fetch
			l1_instrn_cnt++;
			instrnhit += read_data(address, instruction_cache);
		}
	}


	// print data
	if (print == PRINT_DATA) {
		printf("\n");
		printf("data      ------ total : %d ---- hit : %d ---- miss : %d\n", readcnt + writecnt, readhit + writehit, readcnt + writecnt - readhit - writehit);
		printf("readdata  ------ total : %d ---- hit : %d ---- miss : %d\n", readcnt, readhit, readcnt - readhit);
		printf("writedata ------ total : %d ---- hit : %d ---- miss : %d\n", writecnt, writehit, writecnt - writehit);
		printf("instrn    ------ total : %d ---- hit : %d ---- miss : %d\n", l1_instrn_cnt, instrnhit, l1_instrn_cnt - instrnhit);
		printf("\n");
	}

	// output
	printf("Instruction cache access : %d\n", l1_instrn_cnt);
	printf("Instruction cahce miss : %d\n", l1_instrn_cnt - instrnhit);
	printf("Instruction cache miss ratio : %f\n", (l1_instrn_cnt - instrnhit) / (float)l1_instrn_cnt);
	printf("Data cache access : %d\n", (readcnt + writecnt));
	printf("Data cache miss : %d\n", (readcnt + writecnt) - (readhit + writehit));
	printf("Data cache miss ratio : %f\n", (readcnt + writecnt - readhit - writehit) / (float)(readcnt + writecnt));

	fclose(fp);
}

int main() {
	
	// _5_point(PRINT_DATA);
	// system('cls');

	//_7_point(PRINT_DATA);
	// system('cls');


	_10_point(-1);
	// 인자로 PRINT_DATA (define 상수) 를 넣으면, 캐시정보를 출력합니다.

	return 0;
}