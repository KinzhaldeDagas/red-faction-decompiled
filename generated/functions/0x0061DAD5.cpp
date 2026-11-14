// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0061DAD5 __isatty
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, native control-flow and ABI review): Descriptor record
// R=DWORD[2021E40+4*ARITHMETIC(fd>>5)]+64*(fd&31); handle DWORD+0, flags BYTE+4, lookahead BYTE+5, lock-init DWORD+8, critical section+12, encoding BYTE+36; fd limit DWORD2021E20.
// Invalid(E) means errno E plus invalid_parameter(NULL,NULL,NULL,0,0); stated status follows only if that handler returns. Cdecl(fd),returns recordflags&0x40 (0 or64), NOT Boolean.
// Fd-2 ->errno9/0 withoutinvalidhandler or doserrnoreset. Othernegative/outofrange ->invalid(9)/0, nodoserrnoreset. Anyinrangefd readsflags WITHOUT checkingopen1 orqueryingOS, so
// resultcanreflectrecordflags evenclosed. No lock, handlevalidation or terminal APIcall.
int __cdecl _isatty(int FileHandle)
{
  if ( FileHandle == -2 )
  {
    *_errno() = 9;
    return 0;
  }
  else if ( FileHandle >= 0 && FileHandle < MEMORY[0x2021E20] )
  {
    return *(_BYTE *)(unk_2021E40[FileHandle >> 5] + ((FileHandle & 0x1F) << 6) + 4) & 0x40;
  }
  else
  {
    *_errno() = 9;
    _invalid_parameter(nullptr, nullptr, nullptr, 0, 0);
    return 0;
  }
}

