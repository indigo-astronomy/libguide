/******************************************
 * DONUTS guider test application
 *          (c)2015 Rumen G.Bogdanovski
 ******************************************/
#include <stdio.h>
#include <donuts_guide.h>
#include <centroid_guide.h>

//#include <frames1.h> /* the frame background is 1 */
#include <frames0.h> /* the frame background is 0 */

int main() {
	frame_digest dg_ref, dg_guide, cg_ref, cg_guide;
	corrections d_cor, c_cor;

	/* digest reference frame */
	dg_new_frame_digest(ref, 8, 8, &dg_ref);
	cg_new_frame_digest(ref, 8, 8, &cg_ref);

	/* Compare guide1 to reference DONUTS */
	dg_new_frame_digest(guide1, 8, 8, &dg_guide);
	dg_calculate_corrections(&dg_ref, &dg_guide, &d_cor);
	dg_delete_frame_digest(&dg_guide);

	printf("Frame 1 DONUTS: d_cor.x = %.2f d_cor.y = %.2f\n", d_cor.x, d_cor.y);

	/* Compare guide1 to reference CENTROID */
	cg_new_frame_digest(guide1, 8, 8, &cg_guide);
	cg_calculate_corrections(&cg_ref, &cg_guide, &c_cor);
	cg_delete_frame_digest(&cg_guide);

	printf("Frame 1 CENTRO: c_cor.x = %.2f c_cor.y = %.2f\n", c_cor.x, c_cor.y);

	/* Compare guide2 to reference DONUTS */
	dg_new_frame_digest(guide2, 8, 8, &dg_guide);
	dg_calculate_corrections(&dg_ref, &dg_guide, &d_cor);
	dg_delete_frame_digest(&dg_guide);

	printf("Frame 2 DONUTS: d_cor.x = %.2f d_cor.y = %.2f\n", d_cor.x, d_cor.y);

	/* Compare guide2 to reference CENTROID*/
	cg_new_frame_digest(guide2, 8, 8, &cg_guide);
	cg_calculate_corrections(&cg_ref, &cg_guide, &c_cor);
	cg_delete_frame_digest(&cg_guide);

	printf("Frame 2 CENTRO: c_cor.x = %.2f c_cor.y = %.2f\n", c_cor.x, c_cor.y);

	/* release delete frame digest */
	dg_delete_frame_digest(&dg_ref);
	cg_delete_frame_digest(&cg_ref);
}
