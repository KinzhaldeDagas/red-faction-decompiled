// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00507800 rf_vclip_get_definition_damage
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, VClip initialization/preloads,byte occupancy and physical array sizes,trigger suppression/member cleanup and constructor ABI,original ECX/stack flow and PE bytes): Cdecl signed definition index. Requires0<=index<loaded count90B820; invalid returns ST0+0. Valid loads F32 definition+8 at90DC80+224*index and returns unchanged in x87 ST0. Parser506AF0 maps this to optional $damage:, default0. No fixed64 cap, positive/finite clamp, scaling, runtime effect lookup or mutation; negative/NaN authored values are returned as stored.
double __cdecl rf_vclip_get_definition_damage(int a1)
{
  if ( a1 < 0 || a1 >= unk_90B820 )
    return 0.0;
  else
    return *((float *)&unk_90DC88 + 56 * a1);
}

