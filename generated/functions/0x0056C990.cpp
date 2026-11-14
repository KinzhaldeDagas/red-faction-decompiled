// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0056C990 rf_segments_intersect_2d_closed_nonparallel
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, ray candidate planes, normalized-direction sphere queries, frame timing, pause depths and x87 return flow): cdecl(A2,B2,Cx,Cy,Dx,Dy),returnsbyte. Float determinant=(Bx-Ax)*(Dy-Cy)-(By-Ay)*(Dx-Cx); exactzero rejects parallel AND collinear segments,including overlaps. First numerator=(Ay-Cy)*(Dx-Cx)-(Ax-Cx)*(Dy-Cy),requires parameter in inclusive[0,1]; recomputes determinant,then second numerator=(Ay-Cy)*(Bx-Ax)-(Ax-Cx)*(By-Ay),requires second parameter inclusive[0,1]. Thus nonparallel endpoint intersections accepted. No epsilon,intersection output,degenerate/finite handling or Z reads; determinant/numerators/ratios stored as floats.
bool __cdecl rf_segments_intersect_2d_closed_nonparallel(float *a1, float *a2, float a3, float a4, float a5, float a6)
{
  float v7; // [esp+0h] [ebp-10h]
  float v8; // [esp+4h] [ebp-Ch]
  float v9; // [esp+4h] [ebp-Ch]
  float v10; // [esp+8h] [ebp-8h]
  float v11; // [esp+Ch] [ebp-4h]
  float v12; // [esp+Ch] [ebp-4h]

  v11 = (*a2 - *a1) * (a6 - a4) - (a2[1] - a1[1]) * (a5 - a3);
  if ( v11 == 0.0 )
    return 0;
  v8 = (a1[1] - a4) * (a5 - a3) - (*a1 - a3) * (a6 - a4);
  v7 = v8 / v11;
  if ( v7 < 0.0 || v7 > 1.0 )
    return 0;
  v12 = (*a2 - *a1) * (a6 - a4) - (a2[1] - a1[1]) * (a5 - a3);
  if ( v12 == 0.0 )
    return 0;
  v9 = (a1[1] - a4) * (*a2 - *a1) - (*a1 - a3) * (a2[1] - a1[1]);
  v10 = v9 / v12;
  return v10 >= 0.0 && v10 <= 1.0;
}

