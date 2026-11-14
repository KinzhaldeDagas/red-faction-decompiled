// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00486D00 rf_material_custom_sound_set_assign_row
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, material/foley parse and ownership, RFString input ABI, bitmap cache, property fallback and directional sound numbering): 
// Thiscall(set,signed material_id,source DWORD*,signed count), RET12. First caps count above4 to4 but does not clamp negative values. Only signed id0..9 accepted; otherwise no writes
// and EAX is not a defined success return. Valid id copies count handles to row offset16*id (zero iterations for count<=0), stores signed capped count at160+4*id. Leaves trailing old
// handles and all/default BYTE200 unchanged. Valid branch EAX retains receiver from last count store. No source NULL guard when copying positive count; no sound-id validation or
// release of replaced handles.
_DWORD *__thiscall rf_material_custom_sound_set_assign_row(_DWORD *this, unsigned int a2, int a3, int a4)
{
  _DWORD *result; // eax
  int i; // [esp+8h] [ebp-4h]

  if ( a4 > 4 )
    a4 = 4;
  if ( a2 <= 9 )
  {
    for ( i = 0; i < a4; ++i )
      *(this + 4 * a2 + i) = *(_DWORD *)(a3 + 4 * i);
    *(this + a2 + 40) = a4;
    return this;
  }
  return result;
}

