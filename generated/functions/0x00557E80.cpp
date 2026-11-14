// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00557E80 rf_room_find_first_portal_with_endpoint
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, spatial partitioning, strict/inclusive box tests, pool counters, portal registration and ABI verification): Recovered cdecl(room,endpoint). Scans room portal pointer array48 and returns FIRST portal whose endpoint0 OR endpoint4 equals requested pointer, elseNULL. Does not require other endpoint to equal input room, compare portal index, or check geometry.
void *__cdecl rf_room_find_first_portal_with_endpoint(const void *a1, const void *a2)
{
  int i; // [esp+0h] [ebp-4h]

  for ( i = 0; i < rf_receiver_get_first_dword((char *)a1 + 48); ++i )
  {
    if ( **(const void ***)sub_552200((_DWORD *)a1 + 12, i) == a2
      || *(const void **)(*(_DWORD *)sub_552200((_DWORD *)a1 + 12, i) + 4) == a2 )
    {
      return *(void **)sub_552200((_DWORD *)a1 + 12, i);
    }
  }
  return nullptr;
}

