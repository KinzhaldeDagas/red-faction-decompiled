// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005B8980 rf_v3c_mesh_metadata100_read_binary
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, mesh initializers, binary reader stores, caller layouts and signature classification): ECX metadata100; stack(stream,mesh-read context,mesh144), RET12. NULL stream returns-1 before object writes. Otherwise saves mesh pointer at+4 and delegates mesh/material reader5B82C0; negative result propagates without rollback. On nonnegative result reads signed count to+0, loops i<count reading24 raw bytes at52+24*i and one float at16+4*i, then stores FLT_MAX at16+4*count. Copies mesh name from mesh144+0 into metadata+28 through NUL with no length bound and returns0. No count range, object-capacity, stream-status or name bound check. Constructor supplies only3 float slots16..24 and3 blocks28..99; count>=3 or a long name can overwrite fields/beyond object; negative count still indexes sentinel store. Does not free or validate mesh
// pointer.
int __thiscall rf_v3c_mesh_metadata100_read_binary(char *this, int *a2, int a3, char *a4)
{
  char v5; // cl
  char *v6; // [esp+Ch] [ebp-14h]
  char *v7; // [esp+10h] [ebp-10h]
  int i; // [esp+18h] [ebp-8h]
  int geometry_materials; // [esp+1Ch] [ebp-4h]

  if ( !a2 )
    return -1;
  *((_DWORD *)this + 1) = a4;
  geometry_materials = rf_model_mesh144_read_geometry_materials(a4, a2, a3);
  if ( geometry_materials < 0 )
    return geometry_materials;
  *(_DWORD *)this = rf_binary_stream_read_int32_versioned(a2, 0, 0);
  for ( i = 0; i < *(_DWORD *)this; ++i )
  {
    rf_binary_stream_serialize_raw_bytes(a2, this + 24 * i + 52, 0x18u, 0);
    *((float *)this + i + 4) = rf_binary_stream_read_float_versioned(a2, 0, 0.0);
  }
  *((float *)this + *(_DWORD *)this + 4) = 3.4028235e38;
  v7 = a4;
  v6 = this + 28;
  do
  {
    v5 = *v7;
    *v6++ = *v7++;
  }
  while ( v5 );
  return 0;
}

