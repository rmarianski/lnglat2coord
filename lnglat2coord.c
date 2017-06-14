#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <futile.h>

void die_with_usage(char *progname) {
    fprintf(stderr, "%s: <longitude> <latitude> <zoom>\n", progname);
    fprintf(stderr, "%s: z/x/y\n", progname);
}

#define die_if(cond, err_str, ...) if (cond) { fprintf(stderr, err_str, ##__VA_ARGS__); exit(EXIT_FAILURE); }

bool parse_double(char *s, double *out) {
    double result = false;
    char *t = s;
    double d = strtod(s, &t);

    if (s != t && *t == 0) {
        result = true;
        *out = d;
    }

    return result;
}

bool parse_zoom(char *s, unsigned int *out) {
    bool result = false;
    char *t = s;
    long int li = strtol(s, &t, 10);

    if (s != t && *t == 0) {
        if (li >= 0 && li < 20) {
            result = true;
            *out = (unsigned int)li;
        }
    }

    return result;
}

int main(int argc, char *argv[]) {
    char *progname = argv[0];
    unsigned int zoom;
    futile_coord_s coord;
    futile_point_s lnglat;

    if (argc == 4) {

        // NOTE: convert lng lat to coord

        die_if(!parse_double(argv[1], &lnglat.x),
               "%s: Invalid longitude: %s\n", progname, argv[1]);
        die_if(!parse_double(argv[2], &lnglat.y),
               "%s: Invalid latitude: %s\n", progname, argv[2]);
        die_if(!parse_zoom(argv[3], &zoom),
               "%s: Invalid zoom: %s\n", progname, argv[3]);

        futile_lnglat_to_coord(&lnglat, zoom, &coord);
        futile_coord_println(&coord, stdout);

    } else if (argc == 2) {

        // NOTE: convert coord to lng lat

        die_if(!futile_coord_deserialize(argv[1], &coord),
               "%s: invalid coord: %s\n", progname, argv[1]);

        futile_point_s lnglat;
        futile_coord_to_lnglat(&coord, &lnglat);
        printf("%.16f %.16f\n", lnglat.x, lnglat.y);

    } else {
        die_with_usage(progname);
    }

    return 0;
}
