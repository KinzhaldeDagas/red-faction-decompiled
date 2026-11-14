// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0045DBF0 rf_two_rfstring_copy_construct
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, multiplayer level catalog/control call chains, native header/string ABI, original setup tables, slider
// arithmetic, callback stack reuse and RFString array ownership): ECX destination two-RFString16-byte record,one source pointer stack arg,RET4. Copy-construct native RFString at0
// then at8,return destination. SEH cleanup destroys first string if second construction unwinds. No integer fields,metadata copy,lambda invocation,SDK concurrency/NUMA semantics or
// memcpy;both strings own independent copies. False library flag cleared:actual calls are native RFString copy constructors;old mangled lambda name was not a reliable class identity.
// Existing local type and prototype retained rather than inventing a struct layout beyond verified two8-byte fields.
_lambda_8b695f9820225e821433c25f6ed27cb8_ *__thiscall rf_two_rfstring_copy_construct(
        _lambda_8b695f9820225e821433c25f6ed27cb8_ *this,
        char **a2)
{
  rf_string_copy_construct_from_object(this, a2);
  rf_string_copy_construct_from_object((_DWORD *)this + 2, a2 + 2);
  return this;
}

