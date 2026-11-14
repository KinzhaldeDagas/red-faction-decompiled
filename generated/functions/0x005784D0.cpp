// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005784D0 rf_bitmap_probe_dimensions_and_nonzero_format
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, bitmap records/animation rates, decoded-handle tag test, tile descriptor offsets and text-parser ownership): cdecl(name,outWidth,outHeight),returns32bitBOOL. Calls575790 header probe with caller dimension outputs and local format/mip/frame/rate/etc outputs plus default context9999999. Returns1 only when returned FILE TYPE!=0 AND local FORMAT!=0;does not validate positive dimensions,power-of-two or frame count. USERBMAP type3 header branch leaves local format uninitialized and caller dimensions unchanged,so this wrapper can test an uninitialized format local for that input. Other header fatal/error semantics inherited;no own file/pixel loading or NULL checks.
BOOL __cdecl rf_bitmap_probe_dimensions_and_nonzero_format(char *a1, int *a2, int *a3)
{
  int v4; // [esp+0h] [ebp-20h] BYREF
  int v5; // [esp+4h] [ebp-1Ch] BYREF
  int v6; // [esp+8h] [ebp-18h] BYREF
  int v7; // [esp+Ch] [ebp-14h] BYREF
  int v8; // [esp+10h] [ebp-10h] BYREF
  int v9; // [esp+14h] [ebp-Ch]
  int v10; // [esp+18h] [ebp-8h] BYREF
  int v11; // [esp+1Ch] [ebp-4h] BYREF

  v9 = rf_bitmap_probe_header_by_file_type(a1, a2, a3, &v6, &v7, &v11, &v8, &v4, &v10, &v5, byte_98967F);
  return v9 && v6;
}

