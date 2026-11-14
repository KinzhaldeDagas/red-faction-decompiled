// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00523000 rf_world_decal_visit_room_liquid_faces
// UNREALRED VERIFIED [decal-projection-20261028]: For each nonnull primary/secondary owner whose byte+388 is nonzero, traverses face list+40 via0x496170; only faces passing rf_face_is_liquid are sent to0x5230F0(decal,face,0). VERIFIED interaction:0x5230F0 immediately rejects same liquid predicate, so stable ordinary liquid face creates no polygon through this path. Does not reinterpret as successful liquid projection. No owner-neighbor traversal or context fallback here; branch-dependent return.
int __cdecl rf_world_decal_visit_room_liquid_faces(int a1)
{
  int result; // eax
  int v2; // edx
  int j; // [esp+0h] [ebp-8h]
  int i; // [esp+4h] [ebp-4h]

  result = a1;
  if ( *(_DWORD *)(a1 + 64) )
  {
    v2 = *(_DWORD *)(a1 + 64);
    result = *(unsigned __int8 *)(v2 + 388);
    if ( *(_BYTE *)(v2 + 388) )
    {
      result = rf_receiver_get_first_dword((void *)(*(_DWORD *)(a1 + 64) + 40));
      for ( i = result; i; i = result )
      {
        if ( rf_face_is_liquid((_DWORD *)(i + 40)) )
          rf_world_decal_clip_and_attach_face_polygon(a1, i, 0);
        result = rf_face_next_room_link(i);
      }
    }
  }
  if ( *(_DWORD *)(a1 + 68) )
  {
    result = *(_DWORD *)(a1 + 68);
    if ( *(_BYTE *)(result + 388) )
    {
      result = rf_receiver_get_first_dword((void *)(*(_DWORD *)(a1 + 68) + 40));
      for ( j = result; j; j = result )
      {
        if ( rf_face_is_liquid((_DWORD *)(j + 40)) )
          rf_world_decal_clip_and_attach_face_polygon(a1, j, 0);
        result = rf_face_next_room_link(j);
      }
    }
  }
  return result;
}

