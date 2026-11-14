// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00555BC0 rf_solid_get_origin_inclusive_vertex_extents
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, solid boundary topology, generated UV modes, selection transforms and independently recovered routine boundaries): Initializes BOTH min and max vectors to zero, scans all solid vertices120 with per-axis if(value<min)min=value ELSE if(value>max)max=value, writes max-min. Thus bounding interval always includes origin and overestimates extents for coordinates all on one side; empty solid returns zero vector. No selection filtering. EAX incidental vector-copy destination behavior.
void __thiscall rf_solid_get_origin_inclusive_vertex_extents(const void *this, float *a2)
{
  int first_dword; // eax
  const float **v3; // eax
  float *v4; // eax
  float v6[3]; // [esp+4h] [ebp-4Ch] BYREF
  float out_vector[3]; // [esp+10h] [ebp-40h] BYREF
  float copy_result[3]; // [esp+1Ch] [ebp-34h] BYREF
  float rhs; // [esp+28h] [ebp-28h] BYREF
  float v10; // [esp+2Ch] [ebp-24h]
  float v11; // [esp+30h] [ebp-20h]
  float lhs; // [esp+34h] [ebp-1Ch] BYREF
  float v13; // [esp+38h] [ebp-18h]
  float v14; // [esp+3Ch] [ebp-14h]
  float destination; // [esp+40h] [ebp-10h] BYREF
  float v16; // [esp+44h] [ebp-Ch]
  float v17; // [esp+48h] [ebp-8h]
  int i; // [esp+4Ch] [ebp-4h]

  rf_vector3_default_construct_noop(&rhs);
  rf_vector3_default_construct_noop(&lhs);
  rf_vector3_default_construct_noop(&destination);
  rf_vector3_zero_return_destination(&rhs);
  rf_vector3_zero_return_destination(&lhs);
  for ( i = 0; ; ++i )
  {
    first_dword = rf_receiver_get_first_dword((char *)this + 120);
    if ( i >= first_dword )
      break;
    v3 = (const float **)sub_552200((_DWORD *)this + 30, i);
    rf_vector_copy(&destination, copy_result, *v3);
    if ( rhs <= (double)destination )
    {
      if ( lhs < (double)destination )
        lhs = destination;
    }
    else
    {
      rhs = destination;
    }
    if ( v10 <= (double)v16 )
    {
      if ( v13 < (double)v16 )
        v13 = v16;
    }
    else
    {
      v10 = v16;
    }
    if ( v11 <= (double)v17 )
    {
      if ( v14 < (double)v17 )
        v14 = v17;
    }
    else
    {
      v11 = v17;
    }
  }
  v4 = rf_vector_subtract(&lhs, out_vector, &rhs);
  rf_vector_copy(a2, v6, v4);
}

