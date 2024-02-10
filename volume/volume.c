#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

// Size of WAV file header
#define HEADER_SIZE 44

// Function prototypes
void change_volume(FILE *input_file, FILE *output_file, float factor);

int main(int argc, char *argv[])
{
    // Check for correct command-line arguments
    if (argc != 4)
    {
        printf("Usage: ./volume input.wav output.wav factor\n");
        return 1;
    }

    // Open input and output files
    FILE *input_file = fopen(argv[1], "rb");
    if (input_file == NULL)
    {
        printf("Could not open input file.\n");
        return 1;
    }

    FILE *output_file = fopen(argv[2], "wb");
    if (output_file == NULL)
    {
        printf("Could not open output file.\n");
        fclose(input_file);
        return 1;
    }

    // Read factor from command-line arguments
    float factor = atof(argv[3]);

    // Change volume of audio file
    change_volume(input_file, output_file, factor);

    // Close files
    fclose(input_file);
    fclose(output_file);

    return 0;
}

void change_volume(FILE *input_file, FILE *output_file, float factor)
{
    // Create buffer to store audio samples
    int16_t buffer;

    // Read and write WAV file header
    uint8_t header[HEADER_SIZE];
    fread(header, sizeof(uint8_t), HEADER_SIZE, input_file);
    fwrite(header, sizeof(uint8_t), HEADER_SIZE, output_file);

    // Read audio samples from input file, scale them by the factor, and write to output file
    while (fread(&buffer, sizeof(int16_t), 1, input_file) == 1)
    {
        buffer *= factor;
        fwrite(&buffer, sizeof(int16_t), 1, output_file);
    }
}
