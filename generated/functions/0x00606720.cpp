// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00606720 ??__C@YGXPAX0IHP6EX00@ZP6EX0@Z@Z
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, native control-flow and ABI review): Stdcall(destination,source,unsigned stride,signed
// count,thiscallCopyCtor,thiscallDtor),RET24,void. SEH4 original65E7A0 finally0->606771. completed0/success0,arm scope. For signed completed<count: push current source,ECX=current
// destination,CALL copyCtor; no caller pop, target expected member RET4. On normal return advance BOTH pointers by same raw stride modulo32,completed++. No source advancement/count
// increment for failing ctor. count<=0 does no callbacks; stride0 repeatedly addresses same pair. Full success set success1,disarm/explicit finally no-op,epilog. Escaping exception
// triggers ArrayUnwind(current destination,stride,completed,dtor) only; source not destroyed/rolled back. No allocation/free,size/capacity/overlap/NULL/callback/overflow guards or
// constructor-result interpretation. Existing thiscall callback types retained; native finally omitted by flattened pseudocode.
void __stdcall `eh vector copy constructor iterator'(
        char *a1,
        char *a2,
        unsigned int a3,
        int a4,
        void (__thiscall *a5)(void *, void *),
        void (__thiscall *a6)(void *))
{
  int i; // [esp+14h] [ebp-1Ch]

  for ( i = 0; i < a4; ++i )
  {
    a5(a1, a2);
    a1 += a3;
    a2 += a3;
  }
}

