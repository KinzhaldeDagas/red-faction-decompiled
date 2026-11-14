// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00456050 rf_record272_array_reallocate_shallow
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, caller/static-initializer ownership, complete native stack/x87/SEH paths and
// library-label review): Thiscall(receiver,raw capacityDWORD), RET4. Save old backing[+8], write requested capacity[+4] BEFORE allocation. Unsigned MUL capacity*272; high-product
// overflow (OF) forces allocation sizeFFFFFFFF via SETO/NEG/OR, otherwise low product; calls60615E operator new, then immediately replaces backing with returned pointer. Signed loop
// i0..<LIVE count[0] copies exactly68DWORDs/272bytes per element using REP MOVSD, from old+272*i to new+272*i. After loop deletes old backing via6060E9 iff nonnull. No element
// constructor/destructor, deep copy/refcount, count shrink, capacity>=count check, null-allocation check, or rollback. Count/capacity remain independent; excessive/negative capacity
// raw bits use literal unsigned size handling. If allocator throws, capacity has changed while old backing is still retained; after return new backing is visible before copying. Copy
// offsets/count increments wrap32 bits.
void __thiscall rf_record272_array_reallocate_shallow(_DWORD *this, int a2)
{
  int i; // [esp+14h] [ebp-8h]
  char *v4; // [esp+18h] [ebp-4h]

  v4 = (char *)*(this + 2);
  *(this + 1) = a2;
  *(this + 2) = operator new(272 * *(this + 1));
  for ( i = 0; i < *this; ++i )
    qmemcpy((void *)(272 * i + *(this + 2)), &v4[272 * i], 0x110u);
  if ( v4 )
    operator delete(v4);
}

