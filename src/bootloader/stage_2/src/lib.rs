#![feature(lang_items)]
#![no_std]
#![allow(unused)]


use core::panic::PanicInfo;

extern crate rlibc;


#[no_mangle]
pub fn rust_main() {

      // ATTENTION: we have a very small stack and no guard page

      let hello = b"Hello World! From rust welcome to MSBL";
      let color_byte = 0x1f; // white foreground, blue background
      
      let j = hello.len()*2;
      let mut hello_colored = [color_byte;76];
      for (i, char_byte) in hello.into_iter().enumerate() {
          hello_colored[i*2] = *char_byte;
      }
  
      // write `Hello World!` to the center of the VGA text buffer
      let buffer_ptr = (0xb8000) as *mut _;
      unsafe { *buffer_ptr = hello_colored };

      loop{}
}


#[lang = "eh_personality"] #[no_mangle] pub extern fn eh_personality() {}
// #[lang = "panic_fmt"] #[no_mangle] pub extern fn panic_fmt() -> ! {loop{}}
#[panic_handler] #[no_mangle] pub extern fn panic_handler(x: &PanicInfo) -> !{loop{}}

#[no_mangle]
pub extern fn _GLOBAL_OFFSET_TABLE_() { } 