/******************************************
 * Centroid guider API
 *          (c)2015 Rumen G.Bogdanovski
 ******************************************/
#ifndef __CENTROID_GUIDE_H
#define __CENTROID_GUIDE_H

#include <guider_math.h>

#ifdef __cplusplus
extern "C" {
#endif

int cg_new_frame_digest(const double *fdata, const int width, const int height, frame_digest *c);
int cg_calculate_corrections(const frame_digest *ref, const frame_digest *new, corrections *c);
int cg_delete_frame_digest(frame_digest *fdigest);

#ifdef __cplusplus
}
#endif

#endif /* __CENTROID_GUIDE_H */
