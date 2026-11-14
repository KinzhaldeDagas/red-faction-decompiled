// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005DF890 rf_renderer_write_triangle_fan_indices_no_advance
// UNREALRED VERIFIED [renderer-helpers-20261028]: Writes(count-2) triples as16-bit indices into start of currently mapped IBO0x1DAEDBC: base0x18CCFBC,base+i+1,base+i+2. Ignores localindexcursor and does not advance any global vertex/index count. Returns pointer to last triple,or mapped start for count<=2. No capacity,count-validity or16-bit range checks; differs from advancing helper0x5DF7B0.
_WORD *__cdecl rf_renderer_write_triangle_fan_indices_no_advance(int a1)
{
  _WORD *result; // eax
  int i; // [esp+0h] [ebp-8h]
  _WORD *v3; // [esp+4h] [ebp-4h]

  result = (_WORD *)unk_1DAEDBC;
  v3 = (_WORD *)unk_1DAEDBC;
  for ( i = 0; i < a1 - 2; ++i )
  {
    *v3 = dword_18CCFBC;
    v3[1] = i + dword_18CCFBC + 1;
    result = v3;
    v3[2] = i + dword_18CCFBC + 2;
    v3 += 3;
  }
  return result;
}

