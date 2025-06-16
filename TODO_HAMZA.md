## Quotes for expansion:

<!-- ! of course you must split by space here -->
> echo "g g"r$USER geg
COMPLETE_COMMAND
  SIMPLE_COMMAND: [ echo ,  "g g"r$USER geg ]  ❌
  SIMPLE_COMMAND: [ echo ,  "g g"r$USER ,  geg ]      ✅

> ls "-"i -a
COMPLETE_COMMAND
  SIMPLE_COMMAND: [ ls ,  "-"i -a ]   ❌
  SIMPLE_COMMAND: [ ls ,  "-"i, -a ]  ✅

> echo "T"O* 'mi''n'*
COMPLETE_COMMAND
  SIMPLE_COMMAND: [ echo ,  "T"O* 'mi''n'* ]    ❌
  SIMPLE_COMMAND: [ echo ,  "T"O*, 'mi''n'* ]   ✅

> echo "\"TO* \""
syntax error: unclosed quote `"`
COMPLETE_COMMAND
  SIMPLE_COMMAND: [ echo ,  "\"TO* \" ,  " ] ❌
  SIMPLE_COMMAND: [ echo ,  "\"TO* ,  \"" ]  ✅

>  daf "E"F "EG"
COMPLETE_COMMAND
  SIMPLE_COMMAND: [ daf ,  "E"F " ,  EG" ] ❌
  SIMPLE_COMMAND: [ daf ,  "E"F ,  "EG" ]  ✅

# Error msg:
✅> (((((((((()))))))))
syntax error: empty subshell or invalid content
syntax error: empty subshell or invalid content
syntax error: empty subshell or invalid content
syntax error: empty subshell or invalid content
syntax error: empty subshell or invalid content
syntax error: empty subshell or invalid content
syntax error: empty subshell or invalid content
syntax error: empty subshell or invalid content
syntax error: empty subshell or invalid content
syntax error: empty subshell or invalid content

# Missing newline in error
> |
syntax error near unexpected token `|'>
> &&
syntax error near unexpected token `&&'>
> ||
syntax error near unexpected token `||'>

# After each error you must set the exit code to 2, use this:
g_sh.exit_code = FAILURE;

# Leaks:
> cat <<
syntax error near unexpected token `newline'
> 
exit
==1930201== 
==1930201== FILE DESCRIPTORS: 3 open (3 std) at exit.
==1930201== 
==1930201== HEAP SUMMARY:
==1930201==     in use at exit: 208,238 bytes in 223 blocks
==1930201==   total heap usage: 602 allocs, 379 frees, 259,372 bytes allocated
==1930201== 
==1930201== 48 bytes in 1 blocks are definitely lost in loss record 16 of 64
==1930201==    at 0x4848899: malloc (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==1930201==    by 0x402B84: new_tree_node (tree_array.c:20)
==1930201==    by 0x402768: handle_redirect (parser2.c:45)
==1930201==    by 0x402925: collect_words_and_redirects (parser2.c:85)
==1930201==    by 0x402A98: parse_simple_command (parser2.c:127)
==1930201==    by 0x4021DA: parse_command (parser.c:23)
==1930201==    by 0x402204: parse_pipe (parser.c:33)
==1930201==    by 0x40239B: parse_compound_command (parser.c:73)
==1930201==    by 0x4024B4: parse_command_list (parser.c:102)
==1930201==    by 0x4025B3: parse_complete_command (parser.c:126)
==1930201==    by 0x409B3A: parsing (lancher.c:53)
==1930201==    by 0x40992B: launch_shell (lancher.c:100)
==1930201== 
==1930201== LEAK SUMMARY:
==1930201==    definitely lost: 48 bytes in 1 blocks
==1930201==    indirectly lost: 0 bytes in 0 blocks
==1930201==      possibly lost: 0 bytes in 0 blocks
==1930201==    still reachable: 0 bytes in 0 blocks
==1930201==         suppressed: 208,190 bytes in 222 blocks
==1930201== 
==1930201== For lists of detected and suppressed errors, rerun with: -s
==1930201== ERROR SUMMARY: 1 errors from 1 contexts (suppressed: 0 from 0)

# Leaks:
fwefwefwfwef ef wef wef |f wef wef |f wefw fw && th rth && yt ty | (thrh | (hrt hrt | thrh | htr (((thr || yjt)) | ytjt) | jytj) | ytj t && ytjt) | rewg < rgeg > reg > reg > reg
- This is syntax error, but there is leaks

# Check after each syntax error to properly free all allocated memory
