// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0060EE88 ?FindHandler@@YAXPAUEHExceptionRecord@@PAUEHRegistrationNode@@PAU_CONTEXT@@PAXPBU_s_FuncInfo@@EH1@Z
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, native control-flow and ABI review):
// Cdecl(exception*,registration*,context*,dispatcherContext,const FuncInfo*,BYTE recursiveTranslated,signed catchDepth,optional targetFrameRegistration*), void. Corrected shifted
// context/dispatcher and pointer-typed catchDepth. First decode registration.state: fullDWORD iff signed maxState>128, otherwise SIGNED lowBYTE. Require signed -1<=state<maxState
// before any exception/rethrow handling, else inconsistency. Local matchedBYTE0. Ordinary foreign/unrecognized C++ records use foreign-dispatch path below. Rethrow marker requires
// codeE06D7363,parameterCount EXACTLY3,magic19930520/21/22,and ThrowInfoNULL. First PTD+88h NULL ->return immediately, bypassing final PTD+94h invariant check. Else getptd AGAIN,
// replace local exception pointer from currentException+88h and local context stack slot from separately fetched PTD+8Ch; nonzero-only predicate checks replacement, no memory probe.
// Replacement that is itself same valid rethrow marker ->inconsistency. If PTD+94h saved exception spec nonzero, fetch it again, clear PTD+94h BEFORE
// IsInExceptionSpec(EDI=spec,exception). Accepted ->continue search. Rejected ->scan signed spec count entries16bytes, use type_info::operator== (ECX=entry type
// descriptor,stack=&bad_exception RTTI6650CC; delegate compares strings at+9). Match: DestructExceptionObject(exception,1),construct12-byte local std::bad_exception from original
// string "bad exception",CxxThrowException(&local,original ThrowInfo65EC04). No matching descriptor ->terminate. No own NULL-type-descriptor guard in this rejection loop. Original
// ThrowInfo/RTTI/constructor source and byte identities independently verified. Eligible C++ search requires codeE06D7363,exact3parameters,magic one of three constants; no additional
// ThrowInfoNULL guard after rethrow resolution. If nTryBlocks nonzero get indexed range via GetRange(FuncInfo,catchDepth,original decoded state). For each signed-inclusive matching
// try interval, iterate HandlerType array16bytes with signed nCatches>0; for each handler restart signed-positive CatchableTypeArray count and pointer list from
// exception.ThrowInfo+1Ch ->array+0Ch. TypeMatch(handler,catchable,ThrowInfo) decides match. First match in this try sets matchedBYTE1 BEFORE
// CatchIt(EBX=handler,EDI=try,ESI=registration; seven native stack slots exception/context/dispatcher/FuncInfo/catchable/depth/target). If CatchIt returns, reload exception pointer
// and advance directly to NEXT TRY; do not scan remaining handlers in matched try. Search can continue even though matched already1; no global first-match return except nonlocal
// continuation. Callback mutability/table bounds not guarded. After C++ search, recursiveTranslated lowBYTE!=0 ->DestructExceptionObject(exception,1), independent of matched flag.
// Then iff matched0,masked FuncInfo magic&1FFFFFFF>=19930521,and pESTypeList+1Ch nonNULL: IsInExceptionSpec; rejected ->two unused getptd calls then separately publish current
// exception/context into PTD+88h/+8Ch, stdcall UnwindNestedFrames(target or registration,exception),FrameUnwindToState(registration,dispatcher,FuncInfo,-1),CallUnexpected(original
// spec pointer),noreturn. This publication has no own restoration/finally. Foreign/unrecognized path: only if FuncInfo.nTryBlocks nonzero, recursiveTranslated lowBYTE!=0 ->terminate;
// otherwise FindHandlerForForeignException with decoded state/depth/target. nTryBlocks0 skips foreign helper and recursive termination here. All ordinary returning paths except
// absent-current-exception rethrow early exit check PTD+94h==0 else inconsistency. No own SEH, exception-object free, errno, input/map/descriptor/array/overflow validation or
// rollback. Normal restore EBX/ESI/EDI/frame,RET; delegates may transfer/terminate/throw. TypeMatch/copy/translation/cleanup responsibilities remain in their reviewed helpers; own
// argument and branch order derived from native instructions.
void __cdecl FindHandler(
        struct EHExceptionRecord *ExceptionRecord,
        struct EHRegistrationNode *a2,
        struct _CONTEXT *a3,
        void *a4,
        const struct _s_FuncInfo *a5,
        unsigned __int8 a6,
        int a7,
        struct EHRegistrationNode *TargetFrame)
{
  const struct _s_FuncInfo *v8; // ebx
  __ehstate_t maxState; // eax
  __ehstate_t state; // ecx
  struct EHExceptionRecord *v11; // esi
  unsigned int magicNumber; // eax
  unsigned int v13; // eax
  DWORD v14; // edi
  int v15; // esi
  int v16; // ebx
  unsigned int v17; // eax
  const struct _s_FuncInfo *v18; // edi
  TryBlockMapEntry *v19; // edi
  CatchableTypeArray *pCatchableTypeArray; // eax
  CatchableType **arrayOfCatchableTypes; // ebx
  ESTypeList *pESTypeList; // edi
  const ThrowInfo *pThrowInfo; // [esp-4h] [ebp-3Ch]
  unsigned __int8 pExceptionObject[12]; // [esp+Ch] [ebp-2Ch] BYREF
  CatchableType *v25; // [esp+18h] [ebp-20h]
  unsigned int v26; // [esp+1Ch] [ebp-1Ch] BYREF
  int nCatches; // [esp+20h] [ebp-18h]
  int nCatchableTypes; // [esp+24h] [ebp-14h]
  unsigned int v29; // [esp+28h] [ebp-10h] BYREF
  HandlerType *pHandlerArray; // [esp+2Ch] [ebp-Ch]
  int v31; // [esp+30h] [ebp-8h]
  char v32; // [esp+37h] [ebp-1h]

  v8 = a5;
  maxState = a5->maxState;
  v32 = 0;
  if ( maxState > 128 )
    state = a2->state;
  else
    state = SLOBYTE(a2->state);
  v31 = state;
  if ( state < -1 || state >= maxState )
    _inconsistency();
  v11 = ExceptionRecord;
  if ( ExceptionRecord->ExceptionCode != -529697949 )
  {
LABEL_61:
    if ( v8->nTryBlocks )
    {
      if ( a6 )
        goto LABEL_28;
      FindHandlerForForeignException(v11, a2, a3, a4, v8, v31, a7, TargetFrame);
    }
    goto LABEL_64;
  }
  if ( ExceptionRecord->NumberParameters == 3 )
  {
    magicNumber = ExceptionRecord->params.magicNumber;
    if ( (magicNumber == 429065504 || magicNumber == 429065505 || magicNumber == 429065506)
      && !ExceptionRecord->params.pThrowInfo )
    {
      if ( !_getptd()[34] )
        return;
      v11 = (struct EHExceptionRecord *)_getptd()[34];
      ExceptionRecord = v11;
      a3 = (struct _CONTEXT *)_getptd()[35];
      if ( !crt_dword_is_nonzero_bool((int)v11) )
        _inconsistency();
      if ( v11->ExceptionCode == -529697949 && v11->NumberParameters == 3 )
      {
        v13 = v11->params.magicNumber;
        if ( (v13 == 429065504 || v13 == 429065505 || v13 == 429065506) && !v11->params.pThrowInfo )
          _inconsistency();
      }
      if ( _getptd()[37] )
      {
        v14 = _getptd()[37];
        v15 = 0;
        _getptd()[37] = 0;
        if ( !IsInExceptionSpec((const _DWORD *)v14, ExceptionRecord) )
        {
          v16 = 0;
          if ( *(int *)v14 > 0 )
          {
            do
            {
              if ( type_info::operator==(
                     *(const char **)(v16 + *(_DWORD *)(v14 + 4) + 4),
                     (int)&std::bad_exception `RTTI Type Descriptor') )
              {
                __DestructExceptionObject(ExceptionRecord, 1u);
                crt_bad_exception_construct_from_message((std::exception *)pExceptionObject, "bad exception");
                _CxxThrowException(pExceptionObject, (_ThrowInfo *)&_TI2_AVbad_exception_std__);
              }
              ++v15;
              v16 += 16;
            }
            while ( v15 < *(_DWORD *)v14 );
          }
LABEL_28:
          terminate();
        }
        v11 = ExceptionRecord;
      }
    }
  }
  if ( v11->ExceptionCode != -529697949
    || v11->NumberParameters != 3
    || (v17 = v11->params.magicNumber, v17 != 429065504) && v17 != 429065505 && v17 != 429065506 )
  {
    v8 = a5;
    goto LABEL_61;
  }
  v18 = a5;
  if ( a5->nTryBlocks )
  {
    v19 = _GetRangeOfTrysToCheck(a5, a7, v31, &v29, &v26);
    while ( v29 < v26 )
    {
      if ( v19->tryLow <= v31 && v31 <= v19->tryHigh )
      {
        pHandlerArray = (HandlerType *)v19->pHandlerArray;
        nCatches = v19->nCatches;
        if ( nCatches > 0 )
        {
          while ( 1 )
          {
            pCatchableTypeArray = v11->params.pThrowInfo->pCatchableTypeArray;
            arrayOfCatchableTypes = pCatchableTypeArray->arrayOfCatchableTypes;
            nCatchableTypes = pCatchableTypeArray->nCatchableTypes;
            if ( nCatchableTypes > 0 )
              break;
LABEL_45:
            --nCatches;
            ++pHandlerArray;
            if ( nCatches <= 0 )
              goto $NextTryBlock$27933;
          }
          while ( 1 )
          {
            pThrowInfo = v11->params.pThrowInfo;
            v25 = *arrayOfCatchableTypes;
            if ( __TypeMatch(pHandlerArray, v25, pThrowInfo) )
              break;
            --nCatchableTypes;
            ++arrayOfCatchableTypes;
            if ( nCatchableTypes <= 0 )
              goto LABEL_45;
          }
          v32 = 1;
          CatchIt(pHandlerArray, v19, a2, v11, a3, a4, a5, v25, a7, TargetFrame);
          v11 = ExceptionRecord;
        }
      }
$NextTryBlock$27933:
      ++v29;
      ++v19;
    }
    v18 = a5;
  }
  if ( a6 )
    __DestructExceptionObject(v11, 1u);
  if ( !v32 && (*(_DWORD *)v18 & 0x1FFFFFFFu) >= 0x19930521 )
  {
    pESTypeList = v18->pESTypeList;
    if ( pESTypeList )
    {
      if ( !IsInExceptionSpec(pESTypeList, v11) )
      {
        _getptd();
        _getptd();
        _getptd()[34] = (DWORD)v11;
        _getptd()[35] = (DWORD)a3;
        if ( TargetFrame )
          _UnwindNestedFrames(TargetFrame, v11);
        else
          _UnwindNestedFrames(a2, v11);
        __FrameUnwindToState(a2, a4, a5, -1);
        CallUnexpected(&a5->pESTypeList->nCount);
      }
    }
  }
LABEL_64:
  if ( _getptd()[37] )
    _inconsistency();
}

