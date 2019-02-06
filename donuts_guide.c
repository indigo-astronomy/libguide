/******************************************
 * DONUTS guider API
 *          (c)2015 Rumen G.Bogdanovski
 ******************************************/
#include <stdio.h>
#include <stdlib.h>
#include <guider_math.h>
#include <donuts_guide.h>

int dg_new_frame_digest(const double *fdata, const int width, const int height, frame_digest *fdigest) {
	int i, ci, li, max;
	double (*col_x)[2];
	double (*col_y)[2];

	if ((width < 3) || (height < 3)) return -1;
	if ((fdata == NULL) || (fdigest == NULL)) return -1;

	fdigest->width = next_power_2(width);
	fdigest->height = next_power_2(height);
	fdigest->fft_x = malloc(2 * fdigest->width * sizeof(double));
	fdigest->fft_y = malloc(2 * fdigest->height * sizeof(double));

	col_x = calloc(2 * fdigest->width * sizeof(double), 1);
	col_y = calloc(2 * fdigest->height * sizeof(double), 1);

	/* collapse the frame in X and Y directions */
	ci = 0;
	li = 0;
	max = width * height;
	for(i=0; i < max; i++) {
		col_x[ci][RE] += fdata[i];
		col_y[li][RE] += fdata[i];
		ci++;
		if (ci == width) {
			ci = 0;
			li++;
		}
	}

#ifdef DEBUG
	printf("col_x:");
	for(i=0; i < fdigest->width; i++) {
		printf(" %5.2f",col_x[i][RE]);
	}
	printf("\n");

	printf("col_y:");
	for(i=0; i < fdigest->height; i++) {
		printf(" %5.2f",col_y[i][RE]);
	}
	printf("\n");
#endif

	fft(fdigest->width, col_x, fdigest->fft_x);
	fft(fdigest->height, col_y, fdigest->fft_y);
	fdigest->algorithm = donuts;

	free(col_x);
	free(col_y);
	return 0;
}


int dg_calculate_corrections(const frame_digest *ref, const frame_digest *new, corrections *c) {
	double (*c_buf)[2];
	int max_dim;

	if ((ref == NULL) || (new == NULL) || (c == NULL)) return -1;
	if ((ref->algorithm != donuts) || (new->algorithm != donuts)) return -1;
	if ((ref->width != new->width) || (ref->height != new->height)) return -1;

	max_dim = (ref->width > ref->height) ? ref->width : ref->height;

	c_buf = malloc(2 * max_dim * sizeof(double));

	/* find X correction */
	corellate_fft(ref->width, ref->fft_x, new->fft_x, c_buf);
	c->x = find_distance(ref->width, c_buf);

	/* find Y correction */
	corellate_fft(ref->height, ref->fft_y, new->fft_y, c_buf);
	c->y = find_distance(ref->height, c_buf);

	free(c_buf);
	return 0;
}


int dg_delete_frame_digest(frame_digest *fdigest) {
	if (fdigest || (fdigest->algorithm != donuts)) {
		free(fdigest->fft_x);
		free(fdigest->fft_y);
		fdigest->width = 0;
		fdigest->height = 0;
		fdigest->algorithm = none;
		return 0;
	} else {
		return -1;
	}
}
