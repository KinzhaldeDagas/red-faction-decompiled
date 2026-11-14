// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005215D0 rf_world_decal_release_attached_polygons
// UNREALRED VERIFIED [resource-pools-20261028]: Traverses circular polygon list headed at decal+212 using polygon next+1320/prev+1324. Clears polygon+208, removes from owner structure through0x535A60(owner pointer+1312,polygon), clears owner pointer, unlinks from decal list, returns polygon through0x525D90(global0xA70648,polygon), decrements decal polygon count+216. No bitmap/decal free here.
int __cdecl rf_world_decal_release_attached_polygons(int a1)
{
  int result; // eax
  int v2; // [esp+0h] [ebp-Ch]
  int i; // [esp+8h] [ebp-4h]

  result = a1;
  for ( i = *(_DWORD *)(a1 + 212); i; i = v2 )
  {
    if ( *(_DWORD *)(i + 1320) == *(_DWORD *)(a1 + 212) )
      v2 = 0;
    else
      v2 = *(_DWORD *)(i + 1320);
    *(_DWORD *)(i + 208) = 0;
    rf_face_unlink_decal_polygon_link(*(_DWORD **)(i + 1312), i);
    *(_DWORD *)(i + 1312) = 0;
    if ( *(_DWORD *)(a1 + 212) == i )
    {
      if ( *(_DWORD *)(i + 1320) == i )
      {
        *(_DWORD *)(i + 1320) = 0;
        *(_DWORD *)(i + 1324) = 0;
        *(_DWORD *)(a1 + 212) = 0;
        goto LABEL_11;
      }
      *(_DWORD *)(a1 + 212) = *(_DWORD *)(i + 1320);
    }
    *(_DWORD *)(*(_DWORD *)(i + 1324) + 1320) = *(_DWORD *)(i + 1320);
    *(_DWORD *)(*(_DWORD *)(i + 1320) + 1324) = *(_DWORD *)(i + 1324);
    *(_DWORD *)(i + 1320) = 0;
    *(_DWORD *)(i + 1324) = 0;
LABEL_11:
    rf_decal_polygon_pool_release(dword_A70648, (_DWORD *)i);
    result = a1;
    --*(_DWORD *)(a1 + 216);
  }
  return result;
}

