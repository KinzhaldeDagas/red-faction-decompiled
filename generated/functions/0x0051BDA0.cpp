// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0051BDA0 rf_solid_insert_existing_edge_vertices_until_stable
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, shared-edge insertion,component classification/extraction,finite epsilon tests,original ECX/stack flow and PE bytes): Recovered existing code range51BDA0..51BEC0, not new bytes. Thiscall ECX solid with no stack args, plainRET. Repeat full vertex-array120 scans while summed51BB30 face-helper success counts for pass>0. Skip any source vertex having ANY incident face metadata bit8 set; empty incidence passes vacuously. For every remaining vertex call51BB30(solid,vertex), accumulate per-pass and total counts; since helper can report success without insertion, no general termination guarantee or iteration cap. Add total to global DWORD92DE2C, then invoke52ACE0(solid,solid+112 face-list header). Return final helper EAX residue, not accumulated insertion count. No new vertex creation, welding or distance test in this wrapper.
// No code xrefs were present in baseline, but complete prologue/receiver flow/calls/loop/epilogue and independent PE byte identity establish function boundary.
void *__thiscall rf_solid_insert_existing_edge_vertices_until_stable(void *solid)
{
  int v1; // eax
  int v2; // eax
  int v3; // eax
  float **v4; // eax
  int v7; // [esp+4h] [ebp-1Ch]
  int first_dword; // [esp+Ch] [ebp-14h]
  int j; // [esp+10h] [ebp-10h]
  int v10; // [esp+14h] [ebp-Ch]
  int i; // [esp+18h] [ebp-8h]
  int v12; // [esp+1Ch] [ebp-4h]

  v12 = 0;
  do
  {
    v10 = 0;
    for ( i = 0; i < rf_receiver_get_first_dword((char *)solid + 120); ++i )
    {
      v1 = sub_552200((_DWORD *)solid + 30, i);
      first_dword = rf_receiver_get_first_dword((void *)(*(_DWORD *)v1 + 32));
      for ( j = 0; j < first_dword; ++j )
      {
        v2 = sub_552200((_DWORD *)solid + 30, i);
        v3 = sub_552200((_DWORD *)(*(_DWORD *)v2 + 32), j);
        if ( rf_face_metadata_has_flag8((_DWORD *)(*(_DWORD *)v3 + 40)) )
          goto LABEL_9;
      }
      v4 = (float **)sub_552200((_DWORD *)solid + 30, i);
      v7 = rf_solid_split_existing_vertex_into_face_edges((int)solid, *v4);
      v12 += v7;
      v10 += v7;
LABEL_9:
      ;
    }
  }
  while ( v10 > 0 );
  dword_92DE2C += v12;
  return sub_52ACE0((int)solid, (char *)solid + 112);
}

