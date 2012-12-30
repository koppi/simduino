#ifndef MY_STDLIB_H
#define MY_STDLIB_H

#include <stdlib.h>
#include <string.h>

char *utoa(unsigned value, char *digits, int base)
{
  char *p;

  const char *s = "0123456789abcdefghijklmnopqrstuvwxyz"; /* don't care if s is in

											   * read-only memory
											   */
  if (base == 0)
	base = 10;
  if (digits == NULL || base < 2 || base > 36)
	return NULL;
  if (value < (unsigned) base) {
	digits[0] = s[value];
	digits[1] = '\0';
  } else {
	for (p = utoa(value / ((unsigned)base), digits, base);
		 *p;
		 p++);
	utoa( value % ((unsigned)base), p, base);
  }
  return digits;
}

char *itoa(int value, char *digits, int base)
{
  char *d;
  unsigned u; /* assume unsigned is big enough to hold all the
			   * unsigned values -x could possibly be -- don't
			   * know how well this assumption holds on the
			   * DeathStation 9000, so beware of nasal demons
			   */

  d = digits;
  if (base == 0)
	base = 10;
  if (digits == NULL || base < 2 || base > 36)
	return NULL;
  if (value < 0) {
	*d++ = '-';
	u = -((unsigned)value);
  } else
	u = value;
  utoa(u, d, base);
  return digits;
}


#define BUFSIZE (sizeof(long) * 8 + 1)

char *ltoa(long N, char *str, int base)
{
  register int i = 2;
  long uarg;
  char *tail, *head = str, buf[BUFSIZE];

  if (36 < base || 2 > base) {
	base = 10;/* can only use 0-9, A-Z        */
  }
  tail = &buf[BUFSIZE - 1];   /* last character position      */
  *tail-- = '\0';

  if (10 == base && N < 0L) {
	*head++ = '-';
	uarg = -N;
  } else {
	uarg = N;
  }

  if (uarg) {
	for (i = 1; uarg; ++i) {
	  ldiv_t r;

	  r = ldiv(uarg, base);
	  *tail-- = (char)(r.rem + ((9L < r.rem) ? ('A' - 10L) : '0'));
	  uarg = r.quot;
	}
  } else {
	*tail-- = '0';
  }

  memcpy(head, ++tail, i);
  return str;
}

#endif

