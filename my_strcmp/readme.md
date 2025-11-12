![C](https://img.shields.io/badge/language-C-blue)

# My strcmp
*My Version of strcmp from the C Standard Library*  
A manual implementation of the C 'strcmp( )' function to compare two strings.  
Created for academic purposes.

## Learning goals
- Practice pointer arithmetic
- Understand how `strcmp` works internally
- Manage memory safely using `malloc` and `free`

## How it works
It compares character by character until it finds a difference or the string ends.

```
while (*s1 && *s2 && *s1 == *s2){
    s1++;
    s2++;
}
return *s1 - *s2;
```

## Execution
```
$ ./my_strcmp or ./my_strcmp.exe
Enter s1: hello
Enter s2: hello
Same.
```