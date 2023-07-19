#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "wav.h"

int check_format(WAVHEADER header);
int get_block_size(WAVHEADER header);

int main(int argc, char *argv[])
{
    // Ensure proper usage
    if (argc != 3)
    {
        printf("The program excepts two arguments\n");
        return 1;
    }

    // Open input file for reading
    char *wav_file_name = argv[1];
    FILE *wav_file = fopen(wav_file_name, "r");

    if (wav_file == NULL)
    {
        printf("Wrong file!\n");
        return 1;
    }

    // Read header
    WAVHEADER header;
    fread(&header, sizeof(WAVHEADER), 1, wav_file);

    // Use check_format to ensure WAV format
    if (check_format(header) == 1)
    {
        return 1;
    }

    // Open output file for writing
    char *output_file_name = argv[2];
    FILE *output_file = fopen(output_file_name, "w");

    // Write header to file
    fwrite(&header, sizeof(WAVHEADER), 1, output_file);

    // Use get_block_size to calculate size of block
    int block_size = get_block_size(header);

    // Write reversed audio to file
    // TODO #8

    BYTE buffer[block_size];

    fseek(wav_file, 0, SEEK_END);

    long audio_size = ftell(wav_file) - sizeof(WAVHEADER);
    int audio_block = (int) audio_size / block_size;

    for (int i = audio_block - 1; i >= 0; i--)
    {
        fseek(wav_file, sizeof(WAVHEADER) + i * block_size, SEEK_SET);
        fread(buffer, block_size, 1, wav_file);
        fwrite(buffer, block_size, 1, output_file);
    }

    fclose(wav_file);
    fclose(output_file);
}

int check_format(WAVHEADER header)
{
    // TODO #4
    BYTE format[] = {'W','A','V','E'};

    for (int i = 0; i < 4; i++)
    {
        if (header.format[i] != format[i])
        {
            return 1;
        }
    }
    return 0;
}

int get_block_size(WAVHEADER header)
{
    // TODO #7
    int block_size = header.numChannels * (header.bitsPerSample / 8);
    return block_size;
}