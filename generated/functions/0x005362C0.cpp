// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005362C0 rf_geomod_corner_pool_allocate_raw
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, collision cache/traversal,strict AABBs,face/corner ownership,signed area and reset-on-read pool peaks,original ECX/stack flow and PE bytes): Thiscall pool, raw28-byte corner orNULL. Embedded150000 records occupy4200000 bytes. Pop nonNULL freeHead4200000 via record.firstDWORD and decrement freeCount4200012; else globalBYTE spillflagzero returnsNULL, or operator-new28 then increment spillLive4200008 and signed-max spillPeak4200016. Increment active4200024 and signed-max activePeak4200020 on accepted branch. No payload initialization or allocationNULL handling. IDA loc_401640/loc_401654 terms here are numeric receiver OFFSETS (0x401640/0x401654), not jumps/code-object pointers.
_DWORD *__thiscall rf_geomod_corner_pool_allocate_raw(_DWORD *this)
{
  _DWORD *v3; // [esp+8h] [ebp-4h]

  if ( *(_DWORD *)((char *)&loc_401640 + (_DWORD)this) )
  {
    v3 = *(_DWORD **)((char *)&loc_401640 + (_DWORD)this);
    *(_DWORD *)((char *)&loc_401640 + (_DWORD)this) = *v3;
    --*(this + 1050003);
  }
  else
  {
    if ( !rf_fixed_pool_heap_spill_enabled[0] )
      return nullptr;
    v3 = operator new(0x1Cu);
    if ( ++*(this + 1050002) > *(this + 1050004) )
      *(this + 1050004) = *(this + 1050002);
  }
  if ( ++*(this + 1050006) > *(_DWORD *)((char *)&loc_401654 + (_DWORD)this) )
    *(_DWORD *)((char *)&loc_401654 + (_DWORD)this) = *(this + 1050006);
  return v3;
}

