/******************************************
 * Centroid guider API
 *          (c)2015 Rumen G.Bogdanovski
 ******************************************/
#include <stdio.h>
#include <centroid_guide.h>

int cg_new_frame_digest(const double *fdata, const int width, const int height, frame_digest *c) {
	int i, ci, li, max;
	double m10, m01, m00;

	if ((width < 3) || (height < 3)) return -1;
	if ((fdata == NULL) || (c == NULL)) return -1;

	m10 = 0;
	m01 = 0;
	m00 = 0;
	ci = 0;
	li = 0;
	max = width * height;
	for(i=0; i < max; i++) {
		m10 += ci * fdata[i];
		m01 += li * fdata[i];
		m00 += fdata[i];
		ci++;
		if (ci == width) {
			ci = 0;
			li++;
		}
	}
	c->centroid_x = m10 / m00;
	c->centroid_y = m01 / m00;
	c->algorithm = centroid;

#ifdef DEBUG
	printf("c->centroid_x =%5.2f, c->centroid_y =%5.2f\n", c->centroid_x, c->centroid_y);
#endif

	return 0;
}

int cg_calculate_corrections(const frame_digest *ref, const frame_digest *new, corrections *c) {
	if ((ref == NULL) || (new == NULL) || (c == NULL)) return -1;
	if ((ref->algorithm != centroid) || (new->algorithm != centroid)) return -1;
	c->x = ref->centroid_x - new->centroid_x;
	c->y = ref->centroid_y - new->centroid_y;
	return 0;
}

int cg_delete_frame_digest(frame_digest *fdigest) {
	if (fdigest || (fdigest->algorithm != centroid)) {
		fdigest->width = 0;
		fdigest->height = 0;
		fdigest->algorithm = none;
		return 0;
	} else {
		return -1;
	}
}
