// IDA pseudocode evidence; not yet portable or build-ready.
// 0x006065FA ??_L@YGXPAXIHP6EX0@Z1@Z
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, native control-flow and ABI review): Stdcall(base,unsigned stride,signed
// count,thiscallCtor,thiscallDtor),RET20,void. SEH4 original65E740 finally0->606647. Initialize completed0/success0 and arm scope before loop. While signed completed<count:
// ECX=current base,CALL ctor with no explicit stack args; ignore result. Only AFTER normal ctor return advance current pointer by raw stride modulo32 and increment completed.
// count<=0 performs no callbacks. On full success set success1,disarm-2,explicitly call finally (which does nothing when success1),SEH epilog/RET20. Escaping exception invokes
// finally with success0: stdcall ArrayUnwind(current pointer,stride,completed,dtor). Failed element not counted or destroyed; previously completed elements are traversed backward. No
// memory allocation/free, size/NULL/callback/overflow guard or ctor-result test. Zero stride repeats same address. Cleanup exception behavior belongs to ArrayUnwind; no promise of
// completing rollback after a destructor exception.
void __stdcall `eh vector constructor iterator'(
        char *a1,
        unsigned int a2,
        int a3,
        void (__thiscall *a4)(void *),
        void (__thiscall *a5)(void *))
{
  int i; // [esp+14h] [ebp-1Ch]

  for ( i = 0; i < a3; ++i )
  {
    a4(a1);
    a1 += a2;
  }
}

