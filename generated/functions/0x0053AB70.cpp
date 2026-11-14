// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0053AB70 rf_geomod_count_incident_edge_uses
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, solid/room construction,primitive topology and centering,lightmap wire/preset/marking paths,shared ownership helpers,original ECX/stack ABI and PE bytes): Cdecl unused solid/context DWORD,vertexA,vertexB;caller pops12. Creates temporary dynamic pointer array,uniquely gathers incident face pointers from BOTH vertices arrays+32. Walks each face circular corners64 via next20 and counts every directed occurrence A->B OR B->A. Returns occurrence count after destroying temporary pointer storage. Does not count distinct geometric edges,reject repeated/degenerate/non-manifold topology or use first argument. A==B can count matching degenerate corner edge once,not twice. No vertex/face/ring validation. Importer545180 computes min/max of these values but does not enforce them.
int __cdecl rf_geomod_count_incident_edge_uses(int a1, int a2, int a3)
{
  int first_dword; // eax
  int *v4; // eax
  int v5; // eax
  int *v6; // eax
  int v7; // eax
  _DWORD *v9; // [esp+4h] [ebp-34h]
  int v10; // [esp+8h] [ebp-30h]
  _DWORD *j; // [esp+10h] [ebp-28h]
  int v12; // [esp+14h] [ebp-24h]
  void *v13[3]; // [esp+18h] [ebp-20h] BYREF
  int i; // [esp+24h] [ebp-14h]
  int v15; // [esp+28h] [ebp-10h]
  int v16; // [esp+34h] [ebp-4h]

  v15 = 0;
  rf_dword_array_construct_capacity(v13, 0);
  v16 = 0;
  for ( i = 0; ; ++i )
  {
    first_dword = rf_receiver_get_first_dword((void *)(a2 + 32));
    if ( i >= first_dword )
      break;
    v4 = (int *)sub_552200((_DWORD *)(a2 + 32), i);
    rf_pointer_array_append_unique(v13, *v4);
  }
  for ( i = 0; ; ++i )
  {
    v5 = rf_receiver_get_first_dword((void *)(a3 + 32));
    if ( i >= v5 )
      break;
    v6 = (int *)sub_552200((_DWORD *)(a3 + 32), i);
    rf_pointer_array_append_unique(v13, *v6);
  }
  for ( i = 0; ; ++i )
  {
    v7 = rf_receiver_get_first_dword(v13);
    if ( i >= v7 )
      break;
    v12 = *(_DWORD *)sub_552200(v13, i);
    for ( j = *(_DWORD **)(v12 + 64); j; j = v9 )
    {
      if ( j[5] == *(_DWORD *)(v12 + 64) )
        v9 = nullptr;
      else
        v9 = (_DWORD *)j[5];
      if ( *j == a2 && *(_DWORD *)j[5] == a3 )
      {
        ++v15;
      }
      else if ( *j == a3 && *(_DWORD *)j[5] == a2 )
      {
        ++v15;
      }
    }
  }
  v10 = v15;
  v16 = -1;
  rf_pointer_array_destroy_backing_storage(v13);
  return v10;
}

