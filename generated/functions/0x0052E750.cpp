// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0052E750 rf_geomod_boolean_stage_6_cleanup
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, Boolean stage dispatch and workspace ownership,class bits/action table,transforms and room-return ABI,original ECX/stack flow and PE bytes): Cdecl workspace. ResetglobalunusedVertexCountD4B7C4=0. Signedscan vertexarray120; if vertex.incidence32.count nonzero (evennegative),incrementindex; ifEXACTzero eraseindexfromarray, destroy/releasevertex, incrementglobalcounter,keepindex tocheckshiftedelement. ReturnFINALvertexcount EAX,not removedcount. No facecleanup, dedup, selected-array cleanup,bounds/sphere/tree rebuild or stage sentinel write.
int __cdecl rf_geomod_boolean_stage_6_cleanup(int a1)
{
  int result; // eax
  int v2; // [esp+0h] [ebp-8h]
  int v3; // [esp+4h] [ebp-4h]

  unk_D4B7C4 = 0;
  v3 = 0;
  while ( 1 )
  {
    result = rf_receiver_get_first_dword((void *)(a1 + 120));
    if ( v3 >= result )
      break;
    v2 = *(_DWORD *)sub_552200((_DWORD *)(a1 + 120), v3);
    if ( rf_receiver_get_first_dword((void *)(v2 + 32)) )
    {
      ++v3;
    }
    else
    {
      rf_pointer_array_erase_index_unchecked((_DWORD *)(a1 + 120), v3);
      rf_geomod_vertex_destroy_and_release_to_pool(v2);
      ++unk_D4B7C4;
    }
  }
  return result;
}

