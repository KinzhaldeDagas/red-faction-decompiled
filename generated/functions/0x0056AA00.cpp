// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0056AA00 rf_swept_sphere_polygon_edge_contacts
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, static/skinned V3C mesh callers, collision branch comparisons and primitive helpers): Cdecl outContact,start,delta,radius,vertexCount,vertexPointers,outT. Loops closed polygon edges;copies endpoints to static global vectors. Constructs swept AABB from start+/-radius then expands along signed delta via5B14B0;tests each edge against it. Calls56A540 with current internal bestT(initialFLT_MAX),retains strictly smaller accepted time and contact. At end bestT>1 returnsfalse;else stores outT,returns1. Output contact may be written by earlier candidates;outT only on success. Global scratch1809190..18091C0 and initialization flags18091CC make it nonreentrant without synchronization. No count>=3,finite/radius/endpoint validation;each edge start serves as endpoint candidate.
char __cdecl rf_swept_sphere_polygon_edge_contacts(
        float *destination,
        float *a2,
        float *a3,
        float a4,
        int a5,
        const float **a6,
        float *a7)
{
  float v8[3]; // [esp+18h] [ebp-64h] BYREF
  float v9[3]; // [esp+24h] [ebp-58h] BYREF
  float v10[3]; // [esp+30h] [ebp-4Ch] BYREF
  float copy_result[3]; // [esp+3Ch] [ebp-40h] BYREF
  int v12[3]; // [esp+48h] [ebp-34h] BYREF
  float v13; // [esp+54h] [ebp-28h] BYREF
  int v15[3]; // [esp+5Ch] [ebp-20h] BYREF
  int i; // [esp+68h] [ebp-14h]
  float v17; // [esp+6Ch] [ebp-10h]
  int v18; // [esp+78h] [ebp-4h]

  if ( (dword_18091CC & 1) == 0 )
  {
    dword_18091CC |= 1u;
    rf_vector3_default_construct_noop(unk_18091C0);
    v18 = -1;
  }
  if ( (dword_18091CC & 2) == 0 )
  {
    dword_18091CC |= 2u;
    rf_vector3_default_construct_noop(unk_18091B4);
    v18 = -1;
  }
  v17 = 3.4028235e38;
  for ( i = 0; i < a5; ++i )
  {
    rf_vector_copy(unk_18091C0, copy_result, a6[i]);
    if ( i + 1 == a5 )
      rf_vector_copy(unk_18091B4, v10, *a6);
    else
      rf_vector_copy(unk_18091B4, v9, a6[i + 1]);
    if ( (dword_18091CC & 4) == 0 )
    {
      dword_18091CC |= 4u;
      v18 = 2;
      rf_vector3_default_construct_noop(unk_18091A8);
      v18 = -1;
    }
    if ( (dword_18091CC & 8) == 0 )
    {
      dword_18091CC |= 8u;
      v18 = 3;
      rf_vector3_default_construct_noop(flt_180919C);
      v18 = -1;
    }
    if ( (dword_18091CC & 0x10) == 0 )
    {
      dword_18091CC |= 0x10u;
      v18 = 4;
      rf_vector3_default_construct_noop(flt_1809190);
      v18 = -1;
    }
    rf_vector3_subtract_scalar_from_components(a2, (float *)v15, a4);
    rf_vector3_add_scalar_to_components(a2, (float *)v12, a4);
    rf_segment_bounds_build(flt_180919C, flt_1809190, (float *)v15, (float *)v12);
    rf_aabb_expand_along_displacement(flt_180919C, flt_1809190, a3);
    if ( rf_segment_intersects_aabb(flt_180919C, flt_1809190, unk_18091C0, unk_18091B4, unk_18091A8) )
    {
      if ( rf_swept_sphere_edge_or_start_vertex_contact(unk_18091A8, a2, a3, a4, unk_18091C0, unk_18091B4, &v13, v17) )
      {
        if ( v17 > (double)v13 )
        {
          v17 = v13;
          rf_vector_copy(destination, v8, unk_18091A8);
        }
      }
    }
  }
  if ( v17 > 1.0 )
    return 0;
  *a7 = v17;
  return 1;
}

