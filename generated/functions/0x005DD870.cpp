// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005DD870 rf_renderer_draw_face_wire_outline
// UNREALRED VERIFIED [renderer-lighting-20261028]: Arguments context(unused),face. Walks circularcornerlistface+64,transforms positions into25 local48-byte clipvertices,then draws closedlineedges with state0x182ABA0 via0x57E710. Emptyface emits none; no count<=25 guard or colorchange. Uses currentrenderercolor; drawresults ignored.
void __cdecl rf_renderer_draw_face_wire_outline(int a1, int a2)
{
  int v2; // [esp+0h] [ebp-4C4h]
  int j; // [esp+8h] [ebp-4BCh]
  int i; // [esp+Ch] [ebp-4B8h]
  int v5; // [esp+10h] [ebp-4B4h]
  char v6[1200]; // [esp+14h] [ebp-4B0h] BYREF

  rf_vector_construct_no_unwind(v6, 0x30u, 25, rf_vector_prefix_construct_noop);
  v5 = 0;
  for ( i = *(_DWORD *)(a2 + 64); i; i = v2 )
  {
    rf_renderer_transform_world_point_backend_wrapper((int)&v6[48 * v5++], *(float **)i);
    if ( *(_DWORD *)(i + 20) == *(_DWORD *)(a2 + 64) )
      v2 = 0;
    else
      v2 = *(_DWORD *)(i + 20);
  }
  for ( j = 0; j < v5; ++j )
    rf_renderer_draw_projected_line_backend_wrapper((int)&v6[48 * j], (int)&v6[48 * ((j + 1) % v5)], dword_182ABA0);
}

