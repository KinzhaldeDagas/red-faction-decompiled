// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005DF7B0 rf_renderer_append_immediate_triangle_fan_indices
// UNREALRED VERIFIED [face-batch-20261028]: Uses locked index buffer0x1DAEDBC at indexcursor0x1E014EC,emits(count-2) triples(base vertex0x18CCFBC,base+i+1,base+i+2) as16-bit values. Advances vertex cursors0x18CCFBC/0x1E014E8 by count and indexcursor by3*(count-2),returns new indexcursor. No count>=3,buffer-capacity or16-bit overflow guard; callers reserve capacity.
int __cdecl rf_renderer_append_immediate_triangle_fan_indices(int a1)
{
  int result; // eax
  int i; // [esp+0h] [ebp-8h]
  _WORD *v3; // [esp+4h] [ebp-4h]

  v3 = (_WORD *)(unk_1DAEDBC + 2 * unk_1E014EC);
  for ( i = 0; i < a1 - 2; ++i )
  {
    *v3 = dword_18CCFBC;
    v3[1] = dword_18CCFBC + i + 1;
    v3[2] = dword_18CCFBC + i + 2;
    v3 += 3;
  }
  dword_18CCFBC += a1;
  unk_1E014E8 += a1;
  result = unk_1E014EC + 3 * (a1 - 2);
  unk_1E014EC = result;
  return result;
}

