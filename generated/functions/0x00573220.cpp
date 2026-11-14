// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00573220 rf_renderer_draw_preprojected_polygon_backend_wrapper
// UNREALRED VERIFIED [renderer-mesh-20261028]: If backendselector0x187CC9C==102,delegates count,vertexpointerarray,attributemaskbyte,packedstate to rf_d3d8_draw_immediate_polygon. Other backends return lowbyte of selector,which may be nonzero despite no draw. No clipping or pointer validation here.
char __cdecl rf_renderer_draw_preprojected_polygon_backend_wrapper(
        int a1,
        void **a2,
        unsigned __int8 a3,
        unsigned int a4)
{
  char result; // al

  result = dword_187CC9C;
  if ( dword_187CC9C == 102 )
    return rf_d3d8_draw_immediate_polygon(a1, (const void *const *)a2, a3, a4);
  return result;
}

