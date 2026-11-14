// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0060E979 ?CallCatchBlock@@YAPAXPAUEHExceptionRecord@@PAUEHRegistrationNode@@PAU_CONTEXT@@PBU_s_FuncInfo@@PAXHK@Z
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, native control-flow and ABI review): Mixed ABI ECX=catchCodePC plus six caller-popped
// stack slots {exception*,registration*,context*,const FuncInfo*,signed catchDepth,unsigned notifyCode}; EAX continuation pointer/NULL. Corrected missing ECX argument. SEH4
// scope65EBA0 outer finally0->60EA99, inner filter1->60EA09 calling ExFilterRethrow(EAX=exceptionPointers), handler60EA12. Save ECX catchCode in EBX/result local; initialize local
// suppressionDWORD0. Save raw DWORD[registration-4] (NOT registration.state+8). Create/push two-DWORD frame-info for exception.object via CreateFrameInfo. Separately fetch
// PTD+88h/+8Ch prior exception/context and publish supplied values with separate getptd calls. Only AFTER this setup arm scopes; setup failures do not have armed outer-finally
// protection. Reuse original context stack slot as cleanup flag1, invoke CallCatchBlock2(registration,FuncInfo,catchCode,catchDepth,notifyCode); normal result replaces saved
// catchCode. Normal exit sets cleanup flag0 then calls finally. Accepted rethrow-marker handler restoresESP, clears PTD+20Ch, reads registration.state as fullDWORD iff signed
// maxState>128, else signed lowBYTE. Scan try map20-byte entries, unsigned index<nTryBlocks: first signed tryHigh<state<=catchHigh selects unwindMap[tryHigh+1].toState as target;
// absent match keeps state. Call FrameUnwindToState(registration,NULL,FuncInfo,target), set resultNULL, then normal finally. Other exceptions continue search and run outer finally
// with cleanup flag1; local result can still be initial catchCode on such unwind. Finally: restore saved DWORD[registration-4], unlink own frame-info, independently restore
// PTD+88h/+8Ch. Then destructor eligibility requires exception codeE06D7363,parameterCount EXACTLY3,magic19930520/21/22,local suppressionDWORD==0,result pointer!=NULL,and
// IsExceptionObjectToBeDestroyed(object) nonzero (no remaining tracking node). Call DestructExceptionObject(exception,cleanupFlag): flag0 permits destructor exception to propagate;
// flag1 makes destructor-throw filter terminate. Local suppression flag initialized0 with no further own store. Rethrow resultNULL suppresses destruction. No own free/object copy,
// pointer/map/catch-address validation, recursion bounds or transactional setup rollback. Preserve parent stack slot and thread context through explicit native finally; pseudocode
// omits handler path and ECX input.
void *__usercall CallCatchBlock@<eax>(
        void *a1@<ecx>,
        struct EHExceptionRecord *a2,
        struct EHRegistrationNode *a3,
        struct _CONTEXT *a4,
        const struct _s_FuncInfo *a5,
        int a6,
        unsigned int a7)
{
  unsigned int magicNumber; // eax
  int v10; // [esp+10h] [ebp-3Ch] BYREF
  int v11; // [esp+18h] [ebp-34h]
  DWORD v12; // [esp+1Ch] [ebp-30h]
  DWORD v13; // [esp+20h] [ebp-2Ch]
  _DWORD *v14; // [esp+24h] [ebp-28h]
  __ehstate_t state; // [esp+28h] [ebp-24h]
  void *v16; // [esp+30h] [ebp-1Ch]
  CPPEH_RECORD ms_exc; // [esp+34h] [ebp-18h]

  v16 = a1;
  v11 = 0;
  state = a3[-1].state;
  v14 = _CreateFrameInfo(&v10, (int)a2->params.pExceptionObject);
  v13 = _getptd()[34];
  v12 = _getptd()[35];
  _getptd()[34] = (DWORD)a2;
  _getptd()[35] = (DWORD)a4;
  ms_exc.registration.TryLevel = 1;
  v16 = _CallCatchBlock2(a3, a5, a1, a6, a7);
  ms_exc.registration.TryLevel = -2;
  a3[-1].state = state;
  _FindAndUnlinkFrame(v14);
  _getptd()[34] = v13;
  _getptd()[35] = v12;
  if ( a2->ExceptionCode == -529697949 && a2->NumberParameters == 3 )
  {
    magicNumber = a2->params.magicNumber;
    if ( (magicNumber == 429065504 || magicNumber == 429065505 || magicNumber == 429065506)
      && !v11
      && v16
      && _IsExceptionObjectToBeDestroyed((int)a2->params.pExceptionObject) )
    {
      __DestructExceptionObject(a2, 0);
    }
  }
  return v16;
}

