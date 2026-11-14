// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00486A80 rf_geomod_debris_material_sound_select
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, monitor lifetime, debris lifecycle/contact audio, native render ABI and mixed spawn descriptor): Cdecl signed materialA,materialB,float size. Signed A>B swaps indices; looks up a 12-byte vector header in the 10x10 pair grid at global pair-vectors+12*(10*A+B). No material bounds checks. Nonpositive count returns -1. Otherwise k=floor(float(count*float(1-size))), clamped to0..count-1, then returns base[k] via unchecked accessor. Deterministic size-ranked selection, no random draw, finite/size validation or row allocation.
int __cdecl rf_geomod_debris_material_sound_select(int material_a, int material_b, float size_factor)
{
  int *v3; // eax
  float value; // [esp+4h] [ebp-10h]
  int v6; // [esp+8h] [ebp-Ch]
  int v7; // [esp+Ch] [ebp-8h]
  int first_dword; // [esp+10h] [ebp-4h]
  float size_factora; // [esp+24h] [ebp+10h]

  if ( material_a > material_b )
  {
    v7 = material_a;
    material_a = material_b;
    material_b = v7;
  }
  size_factora = 1.0 - size_factor;
  first_dword = rf_receiver_get_first_dword(&rf_material_hit_sound_pair_vectors[30 * material_a + 3 * material_b]);
  if ( first_dword <= 0 )
    return -1;
  value = (double)first_dword * size_factora;
  v6 = (int)rf_floor_float(value);
  if ( v6 >= 0 )
  {
    if ( v6 >= first_dword )
      v6 = first_dword - 1;
    v3 = (int *)sub_552200(&rf_material_hit_sound_pair_vectors[30 * material_a + 3 * material_b], v6);
  }
  else
  {
    v3 = (int *)sub_552200(&rf_material_hit_sound_pair_vectors[30 * material_a + 3 * material_b], 0);
  }
  return *v3;
}

