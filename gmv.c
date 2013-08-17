/**
* © Youtube Sonic TAS Community
* http://ystc.ru
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "gmv.h"

void readMovieHeader(FILE *handle, MovieHeader *header) {
	fseek(handle, 0, SEEK_SET);
	fread(header, sizeof(MovieHeader), 1, handle);
}

MovieFrame *loadInput(FILE *handle, uint32_t length) {
	fseek(handle, 0x40, SEEK_SET);
	MovieFrame *buffer = (MovieFrame *) calloc(length, sizeof(MovieFrame));
	fread(buffer, sizeof(MovieHeader), length, handle);
	return buffer;
}

uint32_t getInputLength(FILE *handle) {
    fseek(handle, 0, SEEK_END);
    return (ftell(handle) - 0x40) / 3;
}

void disposeInput(MovieFrame *movie) {
	free(movie);
}

MovieFile *loadGMV(const char *filename) {
	// Trying to open an input file, which may not exist. We assume it’s a valid gmv file.
	FILE *gmv = fopen(filename, "r");
	if(!gmv) return 0;

	// Allocating memory. Since input files are not large, we can store them in RAM entirely
	MovieFile *buffer = (MovieFile *) malloc(sizeof(MovieFile));

	// Loading the header (step 1)
	readMovieHeader(gmv, &(buffer->header));

    // Determining movie length (step 2)
    buffer->length = getInputLength(gmv);
	
    // Loading frame data (step 3)
    buffer->frames = loadInput(gmv, buffer->length);
	
	// Closing the opened input file
	fclose(gmv);
	
	// Return the resulting memory block
	return buffer;
}

void disposeGMV(MovieFile *gmv) {
	disposeInput(gmv->frames);
	free(gmv);
}

void saveGMV(MovieFile *gmv, const char *filename) {
    FILE *file = fopen(filename, "w");
    ftruncate(file, 0);
    fseek(file, 0, SEEK_SET);
    fwrite(&(gmv->header), 0x40, 1, file);
    fseek(file, 0x40, SEEK_SET);
    fwrite(gmv->frames, 0x40 + (gmv->length * sizeof(MovieFrame)), 1, file);
    fclose(file);
}
