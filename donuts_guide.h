/******************************************
 * DONUTS guider API
 *          (c)2015 Rumen G.Bogdanovski
 ******************************************/
#ifndef __DONUTS_GUIDE_H
#define __DONUTS_GUIDE_H

#include <guider_math.h>

#ifdef __cplusplus
extern "C" {
#endif

/* analyze the frame and allocate, and set buffers in fdigest
 * NOTE: does not allocate *fdigest
 * input: *fdata, width, height
 * output: *fdigest
 * returns:
 */
int dg_new_frame_digest(const double *fdata, const int width, const int height, frame_digest *fdigest);

/* calculate guider corrections in pixels
 * input: *ref, *new
 * output: *c
 * returns:
 */
int dg_calculate_corrections(const frame_digest *ref, const frame_digest *new, corrections *c);

/* frees the buffers allocated by dg_digest_frame()
 * NOTE: does not free *fdigest
 * input: *ref,  *new
 * returns:
 */
int dg_delete_frame_digest(frame_digest *fdigest);

#ifdef __cplusplus
}
#endif

#endif /* __DONUTS_GUIDE_H */
