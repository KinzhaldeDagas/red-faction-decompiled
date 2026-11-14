// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0060E7F2 ?ExFilterRethrow@@YAHPAU_EXCEPTION_POINTERS@@@Z
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, native control-flow and ABI review): Register ABI EAX=const EXCEPTION_POINTERS*, plain
// RET, EAX Boolean exactly0/1. Read record=*input. Accept ONLY codeE06D7363,NumberParameters DWORD+10h EXACTLY3, magicDWORD+14h EXACTLY19930520/21/22, and ThrowInfoDWORD+1Ch==NULL.
// Accepted rethrow marker: getptd, set DWORD PTD+20Ch=1,return1; every mismatch returns0 WITHOUT PTD access. Does not clear prior marker on mismatch, validate pointers/object
// slot/flags, destroy or rethrow itself. No stack input, local frame, own SEH or NULL guard. CallCatchBlock invokes via EAX from exception pointer local; accepted-handler path clears
// marker before its state unwind.
int __usercall ExFilterRethrow@<eax>(const struct _EXCEPTION_POINTERS *a1@<eax>)
{
  PEXCEPTION_RECORD ExceptionRecord; // eax
  ULONG_PTR v2; // ecx

  ExceptionRecord = a1->ExceptionRecord;
  if ( ExceptionRecord->ExceptionCode != -529697949 )
    return 0;
  if ( ExceptionRecord->NumberParameters != 3 )
    return 0;
  v2 = ExceptionRecord->ExceptionInformation[0];
  if ( v2 != 429065504 && v2 != 429065505 && v2 != 429065506 )
    return 0;
  if ( ExceptionRecord->ExceptionInformation[2] )
    return 0;
  _getptd()[131] = 1;
  return 1;
}

