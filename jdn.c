#include <stdio.h>
#include <stdlib.h>

struct date {
	int year;
	int month;
	int day;
};

const struct date GREGORIAN_CHANGE = { .year = 1582, .month = 10, .day = 4 };

int date_cmp(const struct date *a, const struct date *b)
{
	if (a->year != b->year)
		return (a->year - b->year);
	if (a->month != b->month)
		return (a->month - b->month);
	return (a->day - b->day);
}

int julian_day_number(const struct date *d)
{
	// Convert Gregorian or Julian calendar year to Julian Day Number year.
	int year = (d->year < 0)?(d->year+1):(d->year);

	// The following algorithm comes from Wikipedia. The operations and
	// magic constants here do not depend on the value of GREGORIAN_CHANGE.
	int a = (14 - d->month)/12;
	int y = year + 4800 - a;
	int m = d->month + 12*a - 3;

	int jdn = d->day + (153*m + 2)/5 + 365*y + y/4 - 32083;
	if (date_cmp(d, &GREGORIAN_CHANGE) > 0)
		jdn += -y/100 + y/400 + 38;

	return jdn;
}

void usage_and_die(const char *p)
{
	fprintf(stderr, "Usage: %s YYYY-MM-DD [YYYY-MM-DD]\n", p);
	exit(EXIT_FAILURE);
}

void scan_date_or_usage(const char *p, const char *s, struct date *d)
{
	if (sscanf(s, "%d-%d-%d", &(d->year), &(d->month), &(d->day)) != 3)
		usage_and_die(p);
}

int main(int argc, char *argv[])
{
	struct date a, b;

	// When given one date, output the Julian Day Number.
	// When given two, output the number of days elapsed between both.
	switch (argc) {
	case 2:
		scan_date_or_usage(argv[0], argv[1], &a);
		printf("%d\n", julian_day_number(&a));
		break;
	case 3:
		scan_date_or_usage(argv[0], argv[1], &a);
		scan_date_or_usage(argv[0], argv[2], &b);
		printf("%d days elapsed\n", julian_day_number(&b) - julian_day_number(&a));
		break;
	default:
		usage_and_die(argv[0]);
		break;
	}

	return 0;
}
