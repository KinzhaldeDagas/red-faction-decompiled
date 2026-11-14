// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00559610 rf_random_unit_vector_from_z_and_azimuth
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, particle pool allocation, emission/integration branches, definition loader and original-PE math/constants): Chooses z from rf_random_float_range(-1,1),azimuth=(rand()/32768 roundedfloat)*2pi;radius=sqrt(1-z*z),x=cos(azimuth)*radius,y=sin(azimuth)*radius. Writes receiver vector,returns no meaningful EAX. Uses global CRT RNG,not cryptographic or explicit seed. No extra final normalization/clamp; used by spherical emitter spawn.
void __thiscall rf_random_unit_vector_from_z_and_azimuth(float *this)
{
  float v1; // [esp+8h] [ebp-10h]
  float v3; // [esp+10h] [ebp-8h]
  float v4; // [esp+14h] [ebp-4h]

  *(this + 2) = rf_random_float_range(-1.0, 1.0);
  v3 = sub_567730() * 6.283185482025146;
  v1 = 1.0 - *(this + 2) * *(this + 2);
  v4 = rf_sqrt_float(v1);
  *this = rf_cos_float(v3) * v4;
  *(this + 1) = rf_sin_float(v3) * v4;
}

