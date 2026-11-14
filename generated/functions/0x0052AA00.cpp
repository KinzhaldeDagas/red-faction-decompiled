// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0052AA00 rf_plane_set_from_three_world_points
// UNREALRED VERIFIED [lightmap-shadows-20261028]: Thispoints to4-floatplane; three stackpointpointers p0,p1,p2. Assemblypushes outputnormal,p0,p1,p2 to0x559A30 despite incomplete decompilerprototype. Computes cross(p1-p0,p2-p1),normalizes reciprocal-sqrt,sets planeD=-dot(normal,p0). No explicit collinearity/degeneracy guard; helperdefines degenerate normalization. Writes exactly normalXYZ,D. ReturnEAX incidental,not establishedsuccess.
int __thiscall rf_plane_set_from_three_world_points(float *this, float *a2, float *a3, float *a4)
{
  int result; // eax

  rf_triangle_cross_from_three_points(this, a2, a3, a4);
  rf_vector_normalize_reciprocal_sqrt(this);
  *(this + 3) = rf_vector_dot(this, a2) * -1.0;
  return result;
}

