# To fix:
- Just check the quotes is correctly ended, but dont split or remove any of them :
- 
## Quotes for expansion:
> export a=".md i"
COMPLETE_COMMAND
  SIMPLE_COMMAND: [ export ,  a=".md ,  i" ] ❌
  SIMPLE_COMMAND: [ export ,  a=".md i" ]    ✅

> echo "g g"r$USER geg      <!--TODO: of course you must split by space here  -->
COMPLETE_COMMAND
  SIMPLE_COMMAND: [ echo ,  "g g" ,  r$USER ,  geg ]  ❌
  SIMPLE_COMMAND: [ echo ,  "g g"r$USER ,  geg ]      ✅

> ls 'gfdg gfg gfdg gdfg'gdfg"5"fdg
COMPLETE_COMMAND
  SIMPLE_COMMAND: [ ls ,  'gfdg gfg gfdg gdfg' ,  gdfg"5"fdg ]  ❌
  SIMPLE_COMMAND: [ ls ,  'gfdg gfg gfdg gdfg'gdfg"5"fdg ]      ✅

# Heredoc limiter and file:
HEREDOCK -> limiter

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

# Quotes:
> echo -n" "- -n -n --n
syntax error: unclosed quote `"`

COMPLETE_COMMAND
  SIMPLE_COMMAND: [ echo ,  -n" ,  "- -n -n --n ]

==313486== Invalid read of size 1
==313486==    at 0x407062: process_arg (expand.c:27)
==313486==    by 0x407219: expand_cmd_node (expand.c:91)
==313486==    by 0x40810D: execute_simple_cmd (exec_cmd.c:78)
==313486==    by 0x407EB8: run_executor (executor.c:41)
==313486==    by 0x407F0D: executor (executor.c:57)
==313486==    by 0x407E7E: run_executor (executor.c:28)
==313486==    by 0x407F0D: executor (executor.c:57)
==313486==    by 0x401ACC: execution (minishell.c:212)
==313486==    by 0x401B4F: main (minishell.c:236)
==313486==  Address 0x4ba9054 is 0 bytes after a block of size 4 alloc'd
==313486==    at 0x4848899: malloc (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==313486==    by 0x49C758E: strdup (strdup.c:42)
==313486==    by 0x403691: fill_words_array (parsing_command.c:36)
==313486==    by 0x40383B: fill_args (parsing_command.c:75)
==313486==    by 0x4032D8: parse_simple_command (parser2.c:139)
==313486==    by 0x4029AA: parse_command (parser.c:23)
==313486==    by 0x4029D4: parse_pipe (parser.c:33)
==313486==    by 0x402B6B: parse_compound_command (parser.c:73)
==313486==    by 0x402C84: parse_command_list (parser.c:102)
==313486==    by 0x402D83: parse_complete_command (parser.c:126)
==313486==    by 0x401A7A: parsing (minishell.c:202)
==313486==    by 0x401B3C: main (minishell.c:234)


> " "
syntax error: unclosed quote `"`
COMPLETE_COMMAND
  SIMPLE_COMMAND: [ " ,  " ]

==389727== Invalid read of size 1
==389727==    at 0x4070C2: process_arg (expand.c:27)
==389727==    by 0x407279: expand_cmd_node (expand.c:91)
==389727==    by 0x40816D: execute_simple_cmd (exec_cmd.c:76)
==389727==    by 0x407F18: run_executor (executor.c:41)
==389727==    by 0x407F6D: executor (executor.c:57)
==389727==    by 0x407EDE: run_executor (executor.c:28)
==389727==    by 0x407F6D: executor (executor.c:57)
==389727==    by 0x401AD1: execution (minishell.c:212)
==389727==    by 0x401B54: main (minishell.c:235)
==389727==  Address 0x4b97c72 is 0 bytes after a block of size 2 alloc'd
==389727==    at 0x4848899: malloc (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==389727==    by 0x49C758E: strdup (strdup.c:42)
==389727==    by 0x403691: fill_words_array (parsing_command.c:36)
==389727==    by 0x40383B: fill_args (parsing_command.c:75)
==389727==    by 0x4032D8: parse_simple_command (parser2.c:139)
==389727==    by 0x4029AA: parse_command (parser.c:23)
==389727==    by 0x4029D4: parse_pipe (parser.c:33)
==389727==    by 0x402B6B: parse_compound_command (parser.c:73)
==389727==    by 0x402C84: parse_command_list (parser.c:102)
==389727==    by 0x402D83: parse_complete_command (parser.c:126)
==389727==    by 0x401A3A: parsing (minishell.c:200)
==389727==    by 0x401B41: main (minishell.c:233)


# Error msg:
- Missing newline ...
> w | w|w|
syntax error: unexpected token after '|'>

# Leaks:
fwefwefwfwef ef wef wef |f wef wef |f wefw fw && th rth && yt ty | (thrh | (hrt hrt | thrh | htr (((thr || yjt)) | ytjt) | jytj) | ytj t && ytjt) | rewg < rgeg > reg > reg > reg
- This is syntax error, but there is leaks
