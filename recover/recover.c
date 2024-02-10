#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

typedef uint8_t BYTE;

#define BLOCK_SIZE 512

bool is_jpeg_signature(BYTE buffer[])
{
    return buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0;
}

int main(int argc, char *argv[])
{
    // Check command-line arguments
    if (argc != 2)
    {
        printf("Usage: ./recover IMAGE\n");
        return 1;
    }

    // Open forensic image file
    FILE *file = fopen(argv[1], "r");
    if (file == NULL)
    {
        printf("Could not open %s for reading.\n", argv[1]);
        return 1;
    }

    BYTE buffer[BLOCK_SIZE];
    FILE *jpeg = NULL;
    int jpeg_count = 0;

    while (fread(buffer, sizeof(BYTE), BLOCK_SIZE, file) == BLOCK_SIZE)
    {
        // Check if the block starts a new JPEG
        if (is_jpeg_signature(buffer))
        {
            // Close the previous JPEG file (if any)
            if (jpeg != NULL)
            {
                fclose(jpeg);
            }

            // Create a new JPEG file
            char filename[8];
            sprintf(filename, "%03d.jpg", jpeg_count);
            jpeg = fopen(filename, "w");
            jpeg_count++;
        }

        // Write block data to the current JPEG file (if any)
        if (jpeg != NULL)
        {
            fwrite(buffer, sizeof(BYTE), BLOCK_SIZE, jpeg);
        }
    }

    // Close the forensic image file and the last JPEG file (if any)
    fclose(file);
    if (jpeg != NULL)
    {
        fclose(jpeg);
    }

    return 0;
}
