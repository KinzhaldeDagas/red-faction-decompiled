// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0060E711 ___FrameUnwindToState
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, native control-flow and ABI review): Cdecl(registration*,unusedDispatcherSlot,const
// FuncInfo*,signed targetState), no semantic result; old PTD-pointer return was incidental. SEH4 prolog uses original40-byte scope65EB00: outer finally0 ->60E7D1; inner scope1
// enclosing0, filter60E793 delegates FrameUnwindFilter, handler60E79D restores savedESP/register locals then resumes loop. FuncInfo.maxState signed>128 loads full registration
// stateDWORD+8; otherwise SIGN-EXTEND lowBYTE (threshold128 included in byte path). Increment PTD+90h DWORD modulo32, arm outer scope. Until local state==target, require
// signed0<=state<signed maxState else noreturn inconsistency. Read unwindMap(+8)+8*state, load nextState. Arm inner scope; if action pointer nonNULL publish registration.state=next
// BEFORE stdcall CallSettingFrame(action,registration,103h), ignore EAX. NULL action advances only local state, not registration state until completion. Disarm inner scope and
// repeat; no cycle/progress bound or map validation. Normal end disarms scopes to-2, explicitly calls outer-finally body, rechecks state==target else inconsistency, publishes final
// registration.state, SEH epilog/plain RET. Equality at entry bypasses range/map checks, including out-of-range target. Outer finally also runs during escaping unwind: getptd, if
// signed counter+90h>0 getptd AGAIN/decrement. Filter may separately decrement/reset counter before this finally, so not unconditional one-for-one balancing. C++ action exception
// resets counter0/terminates via filter; other normal filter returns0/continue-search. Inner exception handler exists but cannot be selected by unchanged local filter's normal0
// result. No own second-slot read, target-range/NULL validation, pointer overflow/errno/lock or return status. Native exception/finally paths are authoritative where pseudocode
// flattens scopes.
void __cdecl __FrameUnwindToState(struct EHRegistrationNode *a1, void *a2, const struct _s_FuncInfo *a3, int a4)
{
  int state; // esi
  DWORD *v5; // eax
  int v6; // eax
  UnwindMapEntry *v7; // ecx
  DWORD *v8; // eax

  if ( a3->maxState > 128 )
    state = a1->state;
  else
    state = SLOBYTE(a1->state);
  v5 = _getptd();
  ++v5[36];
  while ( state != a4 )
  {
    if ( state <= -1 || state >= a3->maxState )
      _inconsistency();
    v6 = state;
    v7 = &a3->pUnwindMap[state];
    state = v7->toState;
    if ( v7->action )
    {
      a1->state = state;
      _CallSettingFrame(a3->pUnwindMap[v6].action, a1, 0x103u);
    }
  }
  if ( (int)_getptd()[36] > 0 )
  {
    v8 = _getptd();
    --v8[36];
  }
  if ( state != a4 )
    _inconsistency();
  a1->state = state;
}

