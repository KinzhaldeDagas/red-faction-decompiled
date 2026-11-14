// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00531270 rf_geomod_face_corner_count
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, atlas ownership, lightmap seam lifecycle, selected-face topology, SDK misidentification, x87 return ABI and PE bytes): Thiscall face,counts circular corner ring at face+64 through corner+20,ending when next==head. Empty head returns0. No capacity,cycle/malformed-link guard or dedup;counts nodes,not unique positions. Used by both selected-face fan operations.
int __thiscall rf_geomod_face_corner_count(_DWORD *this)
{
  int v2; // [esp+0h] [ebp-10h]
  int i; // [esp+8h] [ebp-8h]
  int v4; // [esp+Ch] [ebp-4h]

  v4 = 0;
  for ( i = *(this + 16); i; i = v2 )
  {
    ++v4;
    if ( *(_DWORD *)(i + 20) == *(this + 16) )
      v2 = 0;
    else
      v2 = *(_DWORD *)(i + 20);
  }
  return v4;
}

