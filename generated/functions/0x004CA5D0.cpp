// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004CA5D0 rf_glass_debug_draw_last_tessellation_grid
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, full rectangular/general quad tessellation, ordered edge selection and stale loop indices, native UV/grid coordinates, pool freshness and delayed launch semantics): 
// Cdecl no args. Sets renderer color RGBA(255,255,0,255) and leaves it set. Reads last globals Nx822308,Ny8222C8 and WORLD grid822768 stride320*i+20*j; draws all column-adjacent
// edges for i0..Nx-1,j0..Ny-2 then row-adjacent for i0..Nx-2,j0..Ny-1 via debug line backend with global182ABA0. No diagonals, active shard iteration, recomputation,
// bounds/finite/view filtering or color restore. Ordinary positive counts produce Nx*(Ny-1)+(Nx-1)*Ny line calls; EAXNx-1 loop artifact, not line count.
int rf_glass_debug_draw_last_tessellation_grid()
{
  int result; // eax
  int j; // [esp+0h] [ebp-8h]
  int m; // [esp+0h] [ebp-8h]
  int i; // [esp+4h] [ebp-4h]
  int k; // [esp+4h] [ebp-4h]

  rf_render_color_set_rgba8(255, 255, 0, 255);
  for ( i = 0; i < dword_822308; ++i )
  {
    for ( j = 0; j < dword_8222C8 - 1; ++j )
      rf_debug_draw_world_line_backend_dispatch(
        (int)&unk_822768[80 * i + 5 * j],
        (int)&unk_822768[80 * i + 5 + 5 * j],
        dword_182ABA0);
  }
  for ( k = 0; ; ++k )
  {
    result = dword_822308 - 1;
    if ( k >= dword_822308 - 1 )
      break;
    for ( m = 0; m < dword_8222C8; ++m )
      rf_debug_draw_world_line_backend_dispatch(
        (int)&unk_822768[80 * k + 5 * m],
        (int)&unk_822768[80 * k + 80 + 5 * m],
        dword_182ABA0);
  }
  return result;
}

