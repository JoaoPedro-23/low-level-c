![C](https://img.shields.io/badge/language-C-blue)

# Check File Type
*My version of a check file type app in C*  
An implementation of a check file type.  
Created for academic purposes.

## Learning goals
- Practice pointers and file I/O
- Inspired by CS50 Week 04 Lecture and Section
- Verify file types through magic numbers

## How it works
It opens the file in `binary read` mode and stores the first four hexadecimal bytes into a buffer.  Then it compares them with each `FileSignature` entry, printing out the file type and possible extensions.

### What are the `magic numbers`?
Magic numbers are a sequence of bytes at the beginning of a file that uniquely identifies its format. Through this sequence of numbers we can figure it out the type of a file.

### Opening file and reading magic numbers
```
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
```

### matches_signature function

```
FileSignature *matches_signature(uint8_t *buffer){

    static FileSignature signatures[] = {
        {"PDF document", ".pdf", {0x25, 0x50, 0x44, 0x46}, 4},
        {"JPG image", ".jpg .jpeg", {0xFF, 0xD8, 0xFF, 0xE0}, 4}, // simplified due to academic purposes
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
```

## Execution
```
$ ./signature ima.png or ./signature.exe img.png
Detected: PNG image (extensions: .png)
```

Made to better understand how file formats are recognized by operating systems and forensic tools.  
And got a little carried away after watching David Malan Lecture.