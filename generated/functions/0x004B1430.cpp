// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004B1430 rf_glare_definition52_construct_members
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, glare visibility/reflection and cached-query initialization, native flags/x87 gates and static ownership): False Concurrency NumaInformation library identity. Thiscall record, no stack args: constructs empty RFString+0/+4, calls NO-WRITE RGBA constructor at+8, returns receiver. No initialization of color bytes, bitmap/scalar fields+12..48, no allocation for those fields or count update. Original startup0x629AC0 passes this and destructor0x4873C0 to EH vector constructor iterator with BASE680DD8,STRIDE52,COUNT64. This is an application glare-definition member constructor; corrected its function type and false library flag while retaining existing local type definitions.
void *__thiscall rf_glare_definition52_construct_members(void *this)
{
  rf_string_construct_empty(this);
  rf_rgba8_default_construct_noop((char *)this + 8);
  return this;
}

