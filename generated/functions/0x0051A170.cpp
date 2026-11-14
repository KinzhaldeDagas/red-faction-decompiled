// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0051A170 rf_solid_vertex_find_or_copy_append
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, byte arrays,navigation scratch/search/path costs,solid ownership and bounding sphere,vertex reuse,original ECX/stack/x87 flow and PE bytes): Thiscall solid,position3f,optional reused BYTE*,RET8;returns vertex pointer. Scans stored vertex array120 in order. Float-stored difference components must each have abs<=double0.00009999999747378752,then FLOAT squared distance must be STRICTLY<double9.999999051046871e-9. First match writes reused1 when output nonNULL and returns existing pointer. Boundary distance exactly epsilonSquared is NOT reused,even when per-axis gate passes. No nearest-best selection or coordinate snap. On miss writes reused0 BEFORE allocation,allocates/copies vertex via geomod pool helper,appends pointer to array120,returns it. No position/allocation/array guard;reuse flag does not prove allocation
// success. No topology/incidence/UV/bounds update here.
float *__thiscall rf_solid_vertex_find_or_copy_append(_DWORD *this, float *rhs, _BYTE *a3)
{
  int first_dword; // eax
  float v5; // [esp+0h] [ebp-2Ch]
  float v6; // [esp+4h] [ebp-28h]
  float v7; // [esp+8h] [ebp-24h]
  float v9; // [esp+10h] [ebp-1Ch]
  float out_vector[3]; // [esp+14h] [ebp-18h] BYREF
  float *lhs; // [esp+20h] [ebp-Ch]
  int i; // [esp+24h] [ebp-8h]
  float *v13; // [esp+28h] [ebp-4h]

  for ( i = 0; ; ++i )
  {
    first_dword = rf_receiver_get_first_dword(this + 30);
    if ( i >= first_dword )
      break;
    lhs = *(float **)sub_552200(this + 30, i);
    rf_vector_subtract(lhs, out_vector, rhs);
    v7 = fabs(out_vector[0]);
    if ( v7 <= 0.00009999999747378752 )
    {
      v6 = fabs(out_vector[1]);
      if ( v6 <= 0.00009999999747378752 )
      {
        v5 = fabs(out_vector[2]);
        if ( v5 <= 0.00009999999747378752 )
        {
          v9 = rf_vector_distance_squared(lhs, rhs);
          if ( v9 < 0.000000009999999051046871 )
          {
            if ( a3 )
              *a3 = 1;
            return lhs;
          }
        }
      }
    }
  }
  if ( a3 )
    *a3 = 0;
  v13 = rf_geomod_vertex_copy_allocate(rhs);
  rf_pointer_array_append_dword(this + 30, (int)v13);
  return v13;
}

