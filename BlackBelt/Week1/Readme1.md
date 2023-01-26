*Compiler Macros:*
_GLIBCXX_DEBUG
_GLIBCXX_DEBUG_PEDANTIC

*Debuggers:*
gdb 

*Sanitazer* (to catch runtime error, slows down program, but less than debuggers)

Program run with Sanitizer in debugger let us find code block wich are responsible for the runtime error

*Symbolizer* (can be run with sanitizer, to convert some memory locations where erroe occured to the corresponding line of code)

*Profiler* (to optimize program findning slowly running blovk of code)

*Test Frameworks* (e.g. Google, for testing parts of code, test-driven development)