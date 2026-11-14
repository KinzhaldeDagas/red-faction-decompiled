// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00525CA0 rf_decal_polygon_pool_acquire
// UNREALRED VERIFIED [decal-updates-20261028]: Pool stores2000 inline1332-byte records (0x534); free head at pool+2664000. If free headnonnull pops firstword next and decrements free count at+2664012. If empty and rf_fixed_pool_heap_spill_enabled false returns0. Else operator-new1332 bytes and increments spill allocation count+2664008/high-water+2664016. Then increments active count+2664024/high-water+2664020 and returns record, without initializing payload or checking allocation result. Spill records returned later join same free list.
_DWORD *__thiscall rf_decal_polygon_pool_acquire(_DWORD *this)
{
  _DWORD *v3; // [esp+8h] [ebp-4h]

  if ( *(this + 666000) )
  {
    v3 = (_DWORD *)*(this + 666000);
    *(this + 666000) = *v3;
    --*(this + 666003);
  }
  else
  {
    if ( !rf_fixed_pool_heap_spill_enabled )
      return nullptr;
    v3 = operator new(0x534u);
    if ( ++*(this + 666002) > *(this + 666004) )
      *(this + 666004) = *(this + 666002);
  }
  if ( ++*(this + 666006) > *(this + 666005) )
    *(this + 666005) = *(this + 666006);
  return v3;
}

