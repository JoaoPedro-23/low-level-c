#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define MAX_SIGNATURE_LENGTH 4
#define READ_LENGTH 4

typedef struct {
    const char *name;
    const char *extensions;
    uint8_t bytes[MAX_SIGNATURE_LENGTH];
    size_t length;
} FileSignature;

FileSignature *matches_signature(uint8_t *buffer);

int main(int argc, char *argv[]){

    if(argc != 2){
        printf("Enter only one file.\n");
        return 1;
    }
    
    FILE *input = fopen(argv[1], "rb");

    if(input == NULL){
        printf("Error opening file.\n");
        return 1;
    }

    uint8_t buffer[MAX_SIGNATURE_LENGTH];

    int count = fread(buffer, sizeof(uint8_t), READ_LENGTH, input);

    if(count < READ_LENGTH){
        printf("Error reading file.\n");
        fclose(input);
        return 1;
    }

    FileSignature *signature = matches_signature(buffer);

    if(signature == NULL){
        printf("No match was found.\n");
        fclose(input);
        return 1;
    }

    printf("Detected: %s (extensions: %s)\n", signature->name, signature->extensions);

    fclose(input);
    return 0;
}


FileSignature *matches_signature(uint8_t *buffer){

    static FileSignature signatures[] = {
        {"PDF document", ".pdf", {0x25, 0x50, 0x44, 0x46}, 4},
        {"JPG image", ".jpg .jpeg", {0xFF, 0xD8, 0xFF, 0xE0}, 4}, //Simplificado para fins didáticos
        {"PNG image", ".png", {0x89, 0x50, 0x4E, 0x47}, 4}, 
        {"ZIP archive", ".zip .jar .docx .xlsx", {0x50, 0x4B, 0x03, 0x04}, 4}
    };

    size_t num_signatures = sizeof(signatures) / sizeof(signatures[0]);

    for(size_t i = 0; i < num_signatures; i++){
        int match = 1;

        for(size_t j = 0; j < signatures[i].length; j++){
            if(buffer[j] != signatures[i].bytes[j]){
                match = 0;
                break;
            }
        }

        if(match){
            return &signatures[i];
        }
    }
    return NULL;
}