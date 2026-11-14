// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00530EE0 rf_geomod_face_corner_move
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, collision cache/traversal,strict AABBs,face/corner ownership,signed area and reset-on-read pool peaks,original ECX/stack flow and PE bytes): Thiscall destinationFace,sourceFace,existingCorner RET8. Unlink exact corner from source ring, advancing source head if needed or clearing it for singleton; clear removed links. Remove FIRST sourceFace pointer from corner.vertex.incidence32 unconditionally, even if another source corner still references same vertex. Append existing corner at destination ring tail (or self-ring if empty), preserving vertex/attribute fields; append destinationFace uniquely to incidence and return resulting index (existing or newly appended). No allocation/payload copy, remaining-source-incidence check, plane/bounds update, or source/destination validation; destination==source not specially rejected.
int __thiscall rf_geomod_face_corner_move(_DWORD *this, int a2, _DWORD *a3)
{
  if ( *(_DWORD **)(a2 + 64) == a3 )
  {
    if ( (_DWORD *)a3[5] == a3 )
    {
      a3[5] = 0;
      a3[6] = 0;
      *(_DWORD *)(a2 + 64) = 0;
      goto LABEL_6;
    }
    *(_DWORD *)(a2 + 64) = a3[5];
  }
  *(_DWORD *)(a3[6] + 20) = a3[5];
  *(_DWORD *)(a3[5] + 24) = a3[6];
  a3[5] = 0;
  a3[6] = 0;
LABEL_6:
  rf_pointer_array_remove_first((int *)(*a3 + 32), a2);
  if ( *(this + 16) )
  {
    a3[6] = *(_DWORD *)(*(this + 16) + 24);
    a3[5] = *(this + 16);
    *(_DWORD *)(*(_DWORD *)(*(this + 16) + 24) + 20) = a3;
    *(_DWORD *)(*(this + 16) + 24) = a3;
  }
  else
  {
    a3[5] = a3;
    a3[6] = a3;
    *(this + 16) = a3;
  }
  return rf_pointer_array_append_unique((_DWORD *)(*a3 + 32), (int)this);
}

