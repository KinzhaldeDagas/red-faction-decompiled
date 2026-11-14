// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005F7A00 rf_model_geometry_release_lod_if_owned
// UNREALRED VERIFIED (2026-10-29; original PE bytes, fresh disassembly/decompilation and callers): Cdecl76-byte LOD pointer. Only if pointer!=NULL,raw allocation+4!=NULL,and(flags64&8)==0,operator delete(raw) then operator delete(LOD header). When raw NULL or flag8 set,does NOT delete even header. Does not free bitmap assets,separately walk embedded pointers,clear fields or modify reference counts. Describes exact ownership gate,not unconditional destructor.
void __cdecl rf_model_geometry_release_lod_if_owned(int a1)
{
  if ( a1 && *(_DWORD *)(a1 + 4) && (*(_DWORD *)(a1 + 64) & 8) == 0 )
  {
    operator delete(*(void **)(a1 + 4));
    operator delete((void *)a1);
  }
}

