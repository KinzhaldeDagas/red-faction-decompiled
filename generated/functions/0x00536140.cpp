// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00536140 rf_geomod_face_pool_allocate_raw
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, collision cache/traversal,strict AABBs,face/corner ownership,signed area and reset-on-read pool peaks,original ECX/stack flow and PE bytes): Thiscall pool, return96-byte raw record orNULL. Embedded capacity30000, byte stride96, header after2880000 bytes. Nonempty freeHead2880000: pop record firstDWORD, decrement freeCount2880012. Empty: if globalBYTE rf_fixed_pool_heap_spill_enabled==0 returnNULL WITHOUT count changes; else operator-new96, increment spillLive2880008, update spillPeak2880016 if SIGNEDnew>old (no allocation failure guard). On either successful branch increment active2880024, update activePeak2880020 if signedgreater, returnrecord. No constructor/payload clearing, generation/ownership tracking, rollback or active-list operation.
_DWORD *__thiscall rf_geomod_face_pool_allocate_raw(_DWORD *this)
{
  _DWORD *v3; // [esp+8h] [ebp-4h]

  if ( *(this + 720000) )
  {
    v3 = (_DWORD *)*(this + 720000);
    *(this + 720000) = *v3;
    --*(this + 720003);
  }
  else
  {
    if ( !rf_fixed_pool_heap_spill_enabled[0] )
      return nullptr;
    v3 = operator new(0x60u);
    if ( ++*(this + 720002) > *(this + 720004) )
      *(this + 720004) = *(this + 720002);
  }
  if ( ++*(this + 720006) > *(this + 720005) )
    *(this + 720005) = *(this + 720006);
  return v3;
}

