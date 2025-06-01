# To fix:
- Just check the quotes is correctly ended, but dont split or remove any of them :
- 

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

