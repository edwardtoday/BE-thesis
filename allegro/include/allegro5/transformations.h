/* Title: Transformations
 */

#ifndef ALLEGRO_TRANSFORMATIONS_H
#define ALLEGRO_TRANSFORMATIONS_H

#ifdef __cplusplus
   extern "C" {
#endif

/* Type: ALLEGRO_TRANSFORM
 */
typedef struct ALLEGRO_TRANSFORM ALLEGRO_TRANSFORM;

struct ALLEGRO_TRANSFORM {
   float m[4][4];
};

/* Transformations*/
AL_FUNC(void, al_use_transform, (const ALLEGRO_TRANSFORM* trans));
AL_FUNC(void, al_copy_transform, (const ALLEGRO_TRANSFORM* src, ALLEGRO_TRANSFORM* dest));
AL_FUNC(void, al_identity_transform, (ALLEGRO_TRANSFORM* trans));
AL_FUNC(void, al_build_transform, (ALLEGRO_TRANSFORM* trans, float x, float y, float sx, float sy, float theta));
AL_FUNC(void, al_translate_transform, (ALLEGRO_TRANSFORM* trans, float x, float y));
AL_FUNC(void, al_rotate_transform, (ALLEGRO_TRANSFORM* trans, float theta));
AL_FUNC(void, al_scale_transform, (ALLEGRO_TRANSFORM* trans, float sx, float sy));
AL_FUNC(void, al_transform_coordinates, (const ALLEGRO_TRANSFORM* trans, float* x, float* y));
AL_FUNC(void, al_transform_transform, (const ALLEGRO_TRANSFORM* trans, ALLEGRO_TRANSFORM* trans2));
AL_FUNC(const ALLEGRO_TRANSFORM*, al_get_current_transform, (void));
AL_FUNC(void, al_invert_transform, (ALLEGRO_TRANSFORM *trans));
AL_FUNC(int, al_check_inverse, (const ALLEGRO_TRANSFORM *trans, float tol));

#ifdef __cplusplus
   }
#endif

#endif
