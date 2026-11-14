// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00580BA0 rf_volume_sphere_sample_contribution
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, volume segment integration, clipping, renderer bridges and original call sites): Uses segment(camera18CD000,worldPoint) through sphere(center volume+8,radius+20),via56CCC0. Multiplies intersection length by cached72=strength*255/(2*radius),clamps float result to[0,255],returns ST0. This is path-length opacity/contribution,not point containment or distance attenuation. Cache must be prepared for current camera;no pointer/radius checks here.
double __cdecl rf_volume_sphere_sample_contribution(float *a1, float *a2)
{
  float v3; // [esp+8h] [ebp-8h]
  int v4; // [esp+Ch] [ebp-4h] BYREF

  v3 = rf_segment_sphere_intersection_length(&flt_18CD000, a2, a1 + 2, a1[5]);
  *(float *)&v4 = v3 * a1[18];
  rf_float_clamp_in_place((float *)&v4, 0.0, 255.0);
  return *(float *)&v4;
}

