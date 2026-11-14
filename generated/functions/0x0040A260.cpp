// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0040A260 sub_40A260
// UNREALRED VERIFIED [ai-authored-startup-20261028] Stores caller mode to AI+0x284 and caller secondary to AI+0x2B8, overriding saved secondary to 4 when saved mode is 5. This does not write current mode or current secondary. RFL entity loader passes translated mode and secondary 0.
int __cdecl sub_40A260(int a1, int a2, int a3)
{
  int result; // eax

  *(_DWORD *)(a1 + 644) = a2;
  result = a3;
  *(_DWORD *)(a1 + 696) = a3;
  if ( *(_DWORD *)(a1 + 644) == 5 )
    *(_DWORD *)(a1 + 696) = 4;
  return result;
}

