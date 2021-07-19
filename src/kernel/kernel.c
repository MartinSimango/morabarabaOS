void _start() {
    unsigned char *VGA_MEMORY = (unsigned char*) (0xb8000);
    VGA_MEMORY[0] = 'H';
    VGA_MEMORY[2] = 'E';
    VGA_MEMORY[4] = 'L';
    VGA_MEMORY[6] = 'L';
    VGA_MEMORY[8] = 'O';
    VGA_MEMORY[10] = 'W';
    VGA_MEMORY[12] = 'O';
    VGA_MEMORY[14] = 'R';
    VGA_MEMORY[16] = 'L';
    VGA_MEMORY[18] = 'D';
    VGA_MEMORY[20] = '!';
    for(;;){}


}

// int main() {
//     return 0;
// }