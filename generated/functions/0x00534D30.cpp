// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00534D30 rf_face_find_corner_for_vertex_unchecked
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, vertex selection, directed edge incidence, weld topology, corner UV copying and receiver ABI): Walks circular corner ring64 through next20 until corner vertex pointer equals requested pointer or loop exhausts. Then dereferences current corner UNCONDITIONALLY before equality check: empty ring or missing vertex dereferences null rather than reliably returning null. Intended successful path returns matching corner.
_DWORD *__thiscall rf_face_find_corner_for_vertex_unchecked(_DWORD *this, int a2)
{
  _DWORD *v3; // [esp+0h] [ebp-Ch]
  _DWORD *i; // [esp+8h] [ebp-4h]

  for ( i = (_DWORD *)*(this + 16); i && *i != a2; i = v3 )
  {
    if ( i[5] == *(this + 16) )
      v3 = nullptr;
    else
      v3 = (_DWORD *)i[5];
  }
  if ( *i == a2 )
    return i;
  else
    return nullptr;
}

