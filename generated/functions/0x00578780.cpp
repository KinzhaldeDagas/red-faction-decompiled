// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00578780 rf_memory_text_parser_construct_empty
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, bitmap records/animation rates, decoded-handle tag test, tile descriptor offsets and text-parser ownership): ECX parser receiver,no stack args,returns receiver. Writes buffer DWORD0=0,current cursor DWORD4=0,and filename first BYTE8=0 ONLY. Does not install vtable,allocate,clear rest of filename or initialize fields264/268. Open578EA0 uses buffer0,cursor4,filename8,field264,size268 (atleast272B object);all observed callers are text/table parsers including console scripts. Old std::exception name/type was misleading;corrected to opaque pointer receiver/result without inventing a full C++ class layout.
void *__thiscall rf_memory_text_parser_construct_empty(void *self)
{
  *(_DWORD *)self = 0;
  *((_DWORD *)self + 1) = 0;
  *((_BYTE *)self + 8) = 0;
  return self;
}

