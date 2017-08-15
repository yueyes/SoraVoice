#include "ed_voice.h"

#ifndef ZA

#include <string>
#include <fstream>
#include <cstring>

#define PATH_SN "voice/scena/"
#define MAX_NAME_LEN 12

#define BUFF_SIZE 0x10000

#define SCN_NUM 8
struct PScns {
	char unk1[0x10];
	char* first;
	char unk2[0x18];
	//0x2C
	char* scn_buff[SCN_NUM];
};

using namespace std;

int SVCALL LoadScn(const char* name, char* buff) {
	char path[sizeof(PATH_SN) + MAX_NAME_LEN] = PATH_SN;
	path[sizeof(path) - 1] = '\0';

	strncpy(path + sizeof(PATH_SN) - 1, name, MAX_NAME_LEN);

	FILE* f = fopen(path, "rb");
	if (!f) return 0;

	fseek(f, 0, SEEK_END);
	int size = ftell(f);
	if (size > BUFF_SIZE) size = BUFF_SIZE;
	fseek(f, 0, SEEK_SET);

	size = fread(buff, 1, size, f);
	fclose(f);

	return size;
}

int SVCALL LoadScns(void* p_PScns, int id, char **pp_t) {
	PScns* ps = (PScns*)p_PScns;

	for (unsigned i = 0; i < SCN_NUM; i++) {
		memset(ps->scn_buff[i], 0, BUFF_SIZE);
	}

	char* sn_name = *(pp_t + (id >> 16)) + 36 * (id & 0xFFFF);
	if (LoadScn(sn_name, ps->scn_buff[0]) < 0x40) return 0;
	ps->first = ps->scn_buff[0];

	for (unsigned i = 1; i < SCN_NUM; i++) {
		int id_tmp = *(int*)(ps->scn_buff[0] + 0x20 + 4 * i);
		if (id_tmp != -1) {
			char* sn_name_tmp = *(pp_t + (id_tmp >> 16)) + 36 * (id_tmp & 0xFFFF);
			if (!LoadScn(sn_name_tmp, ps->scn_buff[i])) {
				return 0;
			};
		}
	}
	return 1;
}

#endif // !ZA
