// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005D9620 rf_renderer_clip_and_draw_projected_line
// UNREALRED VERIFIED [face-batch-20261028]: Input two48-byte projected-vertex records and packed state. Shared outcode AND at+24 nonzero returns0. ORnonzero calls0x5C8220 on LOCAL endpoint pointers,then rejects if resultingOR remainsnonzero. For accepted line projects endpoint if flags+25 bit1clear,then calls0x5D3D90; returns1 regardless renderer helper result. If clipping attempted,releases temporary endpoints whose flags+25 bit4set through0x5C76E0. Can mutate input projection caches; does not update caller endpoint pointers or restore state.
char __usercall rf_renderer_clip_and_draw_projected_line@<al>(double a1@<st0>, int a2, int a3, int a4)
{
  char v5; // [esp+3h] [ebp-11h]
  float *v6; // [esp+4h] [ebp-10h] BYREF
  unsigned __int8 v7; // [esp+Bh] [ebp-9h]
  float *v8; // [esp+Ch] [ebp-8h] BYREF
  char v9; // [esp+13h] [ebp-1h]

  v8 = (float *)a2;
  v6 = (float *)a3;
  if ( (*(_BYTE *)(a3 + 24) & *(_BYTE *)(a2 + 24)) != 0 )
    return 0;
  v7 = *((_BYTE *)v6 + 24) | *((_BYTE *)v8 + 24);
  v5 = 0;
  v9 = 1;
  if ( v7 )
  {
    rf_clip_line_vertex48_outcode_planes((int *)&v8, &v6, v7);
    v5 = 1;
    v7 = *((_BYTE *)v6 + 24) | *((_BYTE *)v8 + 24);
    if ( v7 )
      v9 = 0;
  }
  if ( v9 )
  {
    if ( (*((_BYTE *)v8 + 25) & 1) == 0 )
      rf_renderer_project_clip_vertex_backend_wrapper((int)v8);
    if ( (*((_BYTE *)v6 + 25) & 1) == 0 )
      rf_renderer_project_clip_vertex_backend_wrapper((int)v6);
    rf_renderer_draw_projected_line_backend_102(a1, v8, v6, a4);
  }
  if ( v5 )
  {
    if ( (*((_BYTE *)v8 + 25) & 4) != 0 )
      rf_clip_vertex48_pool_release((int)v8);
    if ( (*((_BYTE *)v6 + 25) & 4) != 0 )
      rf_clip_vertex48_pool_release((int)v6);
  }
  return v9;
}

