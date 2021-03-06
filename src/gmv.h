
/**
* © Youtube Sonic TAS Community
* http://ystc.ru
*/


#include <stdint.h>

typedef struct {
	uint8_t signature[15];
	uint8_t gmv_version;
	uint32_t rerecords;
	uint8_t joypad_keys[2];
    uint8_t flags;
    uint8_t ext_flags;
	uint8_t comment[40];
} MovieHeader;

typedef struct {
	uint8_t first;
	uint8_t second;
	uint8_t mode;
} MovieFrame;

typedef struct {
	MovieHeader header;
	MovieFrame *frames;
    uint32_t length;
} MovieFile;

MovieFile *loadGMV(const char *filename);

void disposeInput(MovieFrame *movie);

uint32_t getInputLength(FILE *handle);

MovieFrame *loadInput(FILE *handle, uint32_t length);

void readMovieHeader(FILE *handle, MovieHeader *header);

void disposeGMV(MovieFile *gmv);

void saveGMV(MovieFile *gmv, const char *filename);

uint8_t getInputFrameRate(MovieFile *movie);

uint8_t movieRequiresSavestate(MovieFile *movie);

uint8_t getInputControllerNumber(MovieFile *movie);

void setInputFrameRate(MovieFile *movie, uint8_t rate);

void requireSavestate(MovieFile *movie, uint8_t savestate_is_required);

void setInputControllerNumber(MovieFile *movie, uint8_t controller_number);
