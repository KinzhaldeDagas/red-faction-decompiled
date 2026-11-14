// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0060E837 ___DestructExceptionObject
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, native control-flow and ABI review): Cdecl(exceptionRecord*,BYTE
// terminateOnDestructorThrow), previously missing second stack argument. SEH4 scope65EB28 encloses ONLY member destructor call; filter60E87A returns second argument lowBYTE!=0,
// higher bits ignored; nonzero executes handler60E883 restoringESP then terminate, zero continue-search. Normal body: NULL record OR code!=E06D7363 OR record.ThrowInfo+1Ch NULL OR
// ThrowInfo destructor DWORD+4 NULL ->no destructor call. No magic/parameter-count/exception-object NULL check. Otherwise arm try0 and invoke native two-slot adapter605B30(object
// record+18h,destructorPC); adapter consumes8 and tail-transfers member target with ECX=object, no explicit member args. Ignore member EAX; normal disarm and SEH epilog. No object
// free, tracking-list unlink, reference counter, pointer decoding or lock. Throw policy is caller flag, not unconditional swallowing/termination. Own prolog exists even for NULL
// record; prolog/epilog behavior delegated.
void __cdecl __DestructExceptionObject(struct EHExceptionRecord *a1, unsigned __int8 a2)
{
  ThrowInfo *pThrowInfo; // eax
  int pmfnUnwind; // eax

  if ( a1 )
  {
    if ( a1->ExceptionCode == -529697949 )
    {
      pThrowInfo = a1->params.pThrowInfo;
      if ( pThrowInfo )
      {
        pmfnUnwind = (int)pThrowInfo->pmfnUnwind;
        if ( pmfnUnwind )
          crt_tail_call_member0_with_ecx_receiver((int)a1->params.pExceptionObject, pmfnUnwind);
      }
    }
  }
}

