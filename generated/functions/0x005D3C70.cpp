// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005D3C70 rf_renderer_setup_screen_line_endpoints
// UNREALRED VERIFIED [renderer-helpers-20261028]: Writes position/depth/rhw into two destination40-byte GPU vertices from four INTEGER screen coordinates. Adds viewport offsets0x187CCBC/0x187CCC0 and common floatpixelbias0x1DAEDD8; sets depth+8=0.99,rhw+12=1. For vertical line,adds0.5 to endpoint with larger y (ties first). Otherwise for horizontal line adds0.5 to endpoint with larger x (ties first). Diagonal lines have no halfpixel extension. Does not set colors,specular or UV fields; no clipping.
void __cdecl rf_renderer_setup_screen_line_endpoints(float *a1, float *a2, int a3, int a4, int a5, int a6)
{
  a1[3] = 1.0;
  a2[3] = 1.0;
  a1[2] = 0.99000001;
  a2[2] = 0.99000001;
  *a1 = (double)(unk_187CCBC + a3) + unk_1DAEDD8;
  a1[1] = (double)(unk_187CCC0 + a4) + unk_1DAEDD8;
  *a2 = (double)(unk_187CCBC + a5) + unk_1DAEDD8;
  a2[1] = (double)(unk_187CCC0 + a6) + unk_1DAEDD8;
  if ( a3 == a5 )
  {
    if ( a2[1] <= (double)a1[1] )
      a1[1] = a1[1] + 0.5;
    else
      a2[1] = a2[1] + 0.5;
  }
  else if ( a4 == a6 )
  {
    if ( *a2 <= (double)*a1 )
      *a1 = *a1 + 0.5;
    else
      *a2 = *a2 + 0.5;
  }
}

