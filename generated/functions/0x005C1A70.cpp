// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005C1A70 rf_sound_compute_max_audible_distance
// UNREALRED VERIFIED [sound-spatialization]: Returns min_distance * (volume/(rolloff*0.05) + 1 - 1/rolloff). For stock rolloff 1 this is 20*volume*min_distance, the distance where absolute gain reaches 0.05.
double __cdecl rf_sound_compute_max_audible_distance(float a1, float a2, float a3)
{
  return (float)(a3 * a1 / (a2 * 0.05000000074505806) + (1.0 - 1.0 / a2) * a1);
}

