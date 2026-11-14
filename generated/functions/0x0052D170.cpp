// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0052D170 rf_geomod_fragments_classify_linear
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, Boolean stage dispatch and workspace ownership,class bits/action table,transforms and room-return ABI,original ECX/stack flow and PE bytes): Cdecl workspace,mode. ResetD4B7EC,clearONLYBYTE28 onALLworkspacevertices120. Modes5 OR6 forceclass1 onALLactivefaces. Firstpass class0 faces trycoplanar-adjacencyclassifier,incrementD4B7EC ontrue. Secondpass floods fromEVERYalreadyclassifiedface (nonzero). ResetD4B7F4/E0,thirdpass remainingclass0 incrementsattempts;operand1 uses spatial-ray helper ifauthoredroomarray144.count nonzero,else linearray(flag0);operand0 alwayslinearray(flag0). Truequery incrementsE0 andfloodfills. Thus thislinearstage can stilluse room-spatial queryforcutter. Record activecount+backupcount fragmenttotal,return backupcountEAX,not totalorstatus. Does NOTmerge/destroytempRoot,
// applyactiontable,extractgeometry or clear finalvertexvisited.
int __cdecl rf_geomod_fragments_classify_linear(float *a1, int a2)
{
  int v2; // esi
  int result; // eax
  int j; // [esp+4h] [ebp-8h]
  _DWORD *k; // [esp+4h] [ebp-8h]
  _DWORD *m; // [esp+4h] [ebp-8h]
  float *n; // [esp+4h] [ebp-8h]
  int i; // [esp+8h] [ebp-4h]

  unk_D4B7EC = 0;
  for ( i = 0; i < rf_receiver_get_first_dword(a1 + 30); ++i )
    *(_BYTE *)(*(_DWORD *)sub_552200((_DWORD *)a1 + 30, i) + 28) = 0;
  if ( a2 == 5 || a2 == 6 )
  {
    for ( j = rf_receiver_get_first_dword(a1 + 28); j; j = rf_solid_face_next_link(j) )
      rf_geomod_face_boolean_class_set((int *)(j + 40), 1);
  }
  for ( k = (_DWORD *)rf_receiver_get_first_dword(a1 + 28); k; k = (_DWORD *)rf_solid_face_next_link((int)k) )
  {
    if ( !rf_geomod_face_boolean_class_get(k + 10) )
    {
      if ( rf_geomod_coplanar_fragment_classify_from_adjacency(k, (int)a1) )
        ++unk_D4B7EC;
    }
  }
  for ( m = (_DWORD *)rf_receiver_get_first_dword(a1 + 28); m; m = (_DWORD *)rf_solid_face_next_link((int)m) )
  {
    if ( rf_geomod_face_boolean_class_get(m + 10) )
      rf_geomod_fragment_class_flood_fill(m);
  }
  unk_D4B7F4 = 0;
  unk_D4B8E0 = 0;
  for ( n = (float *)rf_receiver_get_first_dword(a1 + 28); n; n = (float *)rf_solid_face_next_link((int)n) )
  {
    if ( !rf_geomod_face_boolean_class_get((_DWORD *)n + 10) )
    {
      ++unk_D4B7F4;
      if ( rf_geomod_face_operand_get((_DWORD *)n + 10) )
      {
        if ( rf_receiver_get_first_dword(a1 + 36) )
        {
          if ( rf_geomod_fragment_classify_spatial_ray(n, a1) )
          {
            ++unk_D4B8E0;
            rf_geomod_fragment_class_flood_fill(n);
          }
        }
        else if ( rf_geomod_fragment_classify_linear_ray(n, a1, 0) )
        {
          ++unk_D4B8E0;
          rf_geomod_fragment_class_flood_fill(n);
        }
      }
      else if ( rf_geomod_fragment_classify_linear_ray(n, a1, 0) )
      {
        ++unk_D4B8E0;
        rf_geomod_fragment_class_flood_fill(n);
      }
    }
  }
  v2 = rf_shared_second_dword_getter_518050((_DWORD *)a1 + 28);
  result = rf_shared_second_dword_getter_518050(&dword_D4C528);
  rf_geomod_boolean_fragment_count = result + v2;
  return result;
}

