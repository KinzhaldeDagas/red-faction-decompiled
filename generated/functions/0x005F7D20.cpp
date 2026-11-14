// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005F7D20 rf_model_geometry_read_lod_allocation
// UNREALRED VERIFIED (2026-10-29; original PE bytes, fresh disassembly/decompilation and callers): Cdecl vfile. Allocates76-byte LOD header;NULL allocation returnsNULL. Initializes flags64=0,reads16-byte descriptor on stack via0x5F7D80,then loads/fixes raw block0x5F7DD0. Success returns header;failure returnsNULL WITHOUT freeing allocated header. Other fields uninitialized until loader writes;no vfile error check.
_DWORD *__cdecl rf_model_geometry_read_lod_allocation(void *a1)
{
  _BYTE v2[16]; // [esp+4h] [ebp-14h] BYREF
  _DWORD *v3; // [esp+14h] [ebp-4h]

  v3 = operator new(0x4Cu);
  if ( !v3 )
    return nullptr;
  v3[16] = 0;
  rf_model_geometry_read_lod_descriptor(a1, (int)v2);
  if ( rf_model_geometry_load_lod_raw_block((int)a1, (int)v3, (int)v2) )
    return v3;
  else
    return nullptr;
}

