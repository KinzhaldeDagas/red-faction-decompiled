// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00615D6E ?_Type_info_dtor@type_info@@CAXPAV1@@Z
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, native control-flow and ABI review): Cdecl(type_info*),void; native cache/list behavior
// independently checked against original PE, not assumed standard traversal. SEH4 original65EE60 finally0->615DD5 unlock14. Call lock14 BEFORE arming scope; then read self+4
// cached-name pointer. NULL cache skips frees,finally unlock. NonNULL: EAX=global headDWORD2021C6C,EDX=&sentinel2021C68,ECX=cached pointer. At615D9A store EAX into local,TEST EAX;
// NULL ->free current self+4,zero self+4. Head DWORD0==cached pointer ->previous.next+4=head.next+4,free node,then free fresh self+4 and zero self+4. If head DWORD0 differs:615DD1
// MOV EDX,EAX;615DD3 JMP615D9A, with NO EAX=next or other advance. With unchanged head/cache data this cycle repeats indefinitely while lock held; it does NOT search later nodes or
// reach free/unlock. Only first node is examined by native loop. External unwind still uses finally to unlock; no own break/retry on stable mismatch. No NULL self/list
// corruption/cycle guard, object deallocation, type descriptor/vtable/name+8 mutation or allocation. Node/key comparisons use raw pointer identity. Normal path disarms-2 and
// explicitly calls unlock finally, then SEH epilog. Record actual nonadvancing path, not normalized pseudocode list-search intent.
void __cdecl type_info::_Type_info_dtor(struct type_info *a1)
{
  int v1; // ecx
  void *v2; // eax
  _DWORD *v3; // edx

  _lock(14);
  v1 = *((_DWORD *)a1 + 1);
  if ( v1 )
  {
    v2 = unk_2021C6C;
    v3 = &unk_2021C68;
    while ( unk_2021C6C )
    {
      if ( *(_DWORD *)unk_2021C6C == v1 )
      {
        v3[1] = *((_DWORD *)unk_2021C6C + 1);
        free(v2);
        break;
      }
      v3 = unk_2021C6C;
    }
    free(*((void **)a1 + 1));
    *((_DWORD *)a1 + 1) = 0;
  }
  _unlock(14);
}

