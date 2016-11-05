#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <futile.h>

void die_with_usage(char *progname) {
    fprintf(stderr, "%s: <longitude> <latitude> <zoom>\n", progname);
    fprintf(stderr, "%s: z/x/y\n", progname);
}

bool parse_double(char *s, double *out) {
    double result = false;
    char *t = s;
    double d = strtod(s, &t);

    if (s != t) {
        result = true;
        *out = d;
    }

    return result;
}

bool parse_zoom(char *s, unsigned int *out) {
    bool result = false;
    char *t = s;
    long int li = strtol(s, &t, 10);

    if (s != t) {
        if (li >= 0 && li < 20) {
            result = true;
            *out = (unsigned int)li;
        }
    }

    return result;
}

int main(int argc, char *argv[]) {
    char *progname = argv[0];
    double lng, lat;
    unsigned int zoom;
    futile_coord_s coord;

    if (argc == 4) {

        // NOTE: convert lng lat to coord

        if (!parse_double(argv[1], &lng)) {
            fprintf(stderr, "%s: Invalid longitude: %s\n", argv[0], argv[1]);
            exit(EXIT_FAILURE);
        }
        if (!parse_double(argv[2], &lat)) {
            fprintf(stderr, "%s: Invalid latitude: %s\n", argv[0], argv[2]);
            exit(EXIT_FAILURE);
        }
        if (!parse_zoom(argv[3], &zoom)) {
            fprintf(stderr, "%s: Invalid zoom: %s\n", argv[0], argv[3]);
            exit(EXIT_FAILURE);
        }

        futile_lnglat_to_coord(lng, lat, zoom, &coord);
        futile_coord_println(&coord, stdout);

    } else if (argc == 2) {

        // NOTE: convert coord to lng lat

        if (!futile_coord_deserialize(argv[1], &coord)) {
            fprintf(stderr, "%s: invalid coord: %s\n", progname, argv[1]);
            exit(EXIT_FAILURE);
        }
        futile_coord_to_lnglat(&coord, &lng, &lat);
        printf("%.16f %.16f\n", lng, lat);

    } else {
        die_with_usage(progname);
    }

    return 0;
}
