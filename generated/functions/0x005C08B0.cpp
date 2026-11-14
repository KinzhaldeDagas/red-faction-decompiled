// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005C08B0 rf_sound_compute_scaled_group_gain
// UNREALRED VERIFIED (2026-10-29; original PE bytes, fresh disassembly, x87 return flow and callers): Returns record[index].base_gain(+32) * scale * group_gain[record.group(+52)]. No ready check, record bounds check, group bounds check, distance attenuation, or clamp.
double __cdecl rf_sound_compute_scaled_group_gain(int a1, float a2)
{
  return (float)(*(float *)&rf_sound_resource_registry[64 * a1 + 32]
               * a2
               * unk_1DAE7B8[*(_DWORD *)&rf_sound_resource_registry[64 * a1 + 52]]);
}

