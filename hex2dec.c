#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

int main(int argc, char * argv[])
{
   if ( argc != 2 )
   {
      fprintf( stderr, "Invalid number of args: %d\n", argc );
      return 1;
   }

   char * endptr = memchr(argv[1], '\0', 15);
   if ( endptr == nullptr )
   {
      fprintf( stderr, "Number argument too long!\n" );
   }

   errno = 0;
   long int num = strtol(argv[1], &endptr, 16);
   if ( errno != 0 )
   {
      fprintf( stderr,
               "Unable to strtol()\n"
               "returned: %ld, errno: %s (%d): %s\n",
               num, strerrorname_np(errno), errno, strerror(errno) );
      return 2;
   }
   else if ( endptr == nullptr )
   {
      fprintf( stderr, "Somehow endptr is nullptr from strtol()...!\n" );
      return 3;
   }
   else if ( *endptr != '\0' )
   {
      fprintf( stderr,
               "Invalid character at: argv[1][%td] : %c\n",
               endptr - argv[1], *endptr );
      return 4;
   }

   printf("%ld\n", num);

   return 0;
}
