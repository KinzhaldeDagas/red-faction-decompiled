// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00486D70 rf_material_custom_sound_set_assign_all
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, material/foley parse and ownership, RFString input ABI, bitmap cache, property fallback and directional sound numbering): 
// Thiscall(set,source DWORD*,signed count), RET8. Caps count>4 to4, preserves negative count. Copies count handles ONLY into row0 at+0 (zero iterations when count<=0), writes count0
// at+160, sets BYTE+200=1, returns capped count in EAX. Does NOT replicate to rows1..9 or clear their counts/trailing handles. 'all' is an interpretation mode using stored row0, not
// eager per-row copying. No source/sound validation or backend ownership change.
int __thiscall rf_material_custom_sound_set_assign_all(int this, int a2, int a3)
{
  int i; // [esp+8h] [ebp-4h]

  if ( a3 > 4 )
    a3 = 4;
  for ( i = 0; i < a3; ++i )
    *(_DWORD *)(this + 4 * i) = *(_DWORD *)(a2 + 4 * i);
  *(_DWORD *)(this + 160) = a3;
  *(_BYTE *)(this + 200) = 1;
  return a3;
}

