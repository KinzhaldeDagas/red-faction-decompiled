// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005B1C40 rf_record16_shell_sort_descending
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, character state/action time advancement, hold/event/ownership edges, AABB support/corner math, sort comparator and original x87/stack ABI): Cdecl mutable16-byte record buffer,signed record count,low BYTE mode,12-byte caller cleanup. count<=0 no-op. Shell-sort gap sequence count/2 then integer halve until0; for j=gap..count-1 repeatedly compare records k andk+gap using5B1D60 and swap all4 DWORDs when comparator true,then k-=gap. Fourth DWORD travels as opaque payload; no allocation or copying outside4-DWORD swaps. Mode0 sorts descending first float; nonzero comparator is multi-axis improvement heuristic,NOT lexicographic/strict-weak ordering and can returntrue in both directions. Sorting is not stable. No buffer/count*16 overflow,alignment,capacity or float validation. Existing D3D8 face-submission caller chooses mode;
// function does not know face semantics.
void __cdecl rf_record16_shell_sort_descending(int a1, int a2, char a3)
{
  int *v3; // eax
  _DWORD *v4; // eax
  _DWORD *v5; // ecx
  int k; // [esp+0h] [ebp-1Ch]
  int i; // [esp+4h] [ebp-18h]
  int v8; // [esp+8h] [ebp-14h]
  int v9; // [esp+Ch] [ebp-10h]
  int v10; // [esp+10h] [ebp-Ch]
  int v11; // [esp+14h] [ebp-8h]
  int j; // [esp+18h] [ebp-4h]

  if ( a2 > 0 )
  {
    for ( i = a2 / 2; i > 0; i /= 2 )
    {
      for ( j = i; j < a2; ++j )
      {
        for ( k = j - i;
              k >= 0 && rf_record16_should_swap_descending((float *)(a1 + 16 * k), (float *)(16 * i + a1 + 16 * k), a3);
              k -= i )
        {
          v3 = (int *)(a1 + 16 * k);
          v8 = *v3;
          v9 = v3[1];
          v10 = v3[2];
          v11 = v3[3];
          v4 = (_DWORD *)(a1 + 16 * (i + k));
          v5 = (_DWORD *)(a1 + 16 * k);
          *v5 = *v4;
          v5[1] = v4[1];
          v5[2] = v4[2];
          v5[3] = v4[3];
          *v4 = v8;
          v4[1] = v9;
          v4[2] = v10;
          v4[3] = v11;
        }
      }
    }
  }
}

