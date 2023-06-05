#include "print.h"
#include "console.h"
#include "vc.h"

void printk(const char *string){
    vc_consoles[0].tty->tty_driver->write(vc_consoles[0].tty, string, strlen(string));
    vc_con_write(&vc_consoles[0]);
    vc_con_set(&vc_consoles[0],default_console);
}